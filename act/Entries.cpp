#include	"act/Entries.hpp"

Act::NutStream::NutStream(const Object* parent, const std::string& name)
  : Entry(parent, "NutStream", name), nutSize(0), nutBytes(nullptr), stream(nullptr)
{}

Act::NutStream::~NutStream()
{
  delete this->nutBytes;
  delete this->stream;
}

bool	Act::NutStream::readValue(IBuffer& buf)
{
  if (!this->Entry::readValue(buf))
    return false;

  this->nutSize = buf.readInt();
  this->nutBytes = new uint8_t[nutSize];
  buf.readBytes(nutBytes, nutSize);

  Act::Boolean* compiled = dynamic_cast<Act::Boolean*>(this->array["compiled"]);
  if (compiled && *compiled != 0)
    {
      ActNut::MemoryBuffer	nutBuf(nutBytes, nutSize, true);
      ActNut::IBuffer* oldBuffer = ActNut::Error::setErrorBuffer(&nutBuf);
      this->stream = Object::read<Nut::Stream>(this, nutBuf, "stream");
      ActNut::Error::setErrorBuffer(oldBuffer);
      if (!this->stream)
	{
	  ActNut::Error::error(std::string("Parsing of embeeded NUT stream failed (stream size ") + std::to_string(nutSize) + ")");
	  return false;
	}
      addMember(stream);
    }

  return true;
}

void	Act::NutStream::print(std::ostream& os) const
{
  this->Entry::print(os);
  if (stream)
    os << printIndent() << *stream;
  else if (nutBytes)
    os.write((const char*)this->nutBytes, this->nutSize);
}

bool	Act::NutStream::writeValue(IBuffer& buf) const
{
  if (!this->Entry::writeValue(buf))
    return false;

  if (this->stream)
    {
      // Compiled script
      ActNut::MemoryBuffer	nutBuf;
      if (!this->stream->writeValue(nutBuf))
	return false;
      buf.writeInt(nutBuf.getSize());
      return buf.writeBytes(nutBuf.getBuffer(), nutBuf.getSize());
    }
  else
    {
      // Plaintext script
      buf.writeInt(this->nutSize);
      return buf.writeBytes(this->nutBytes, this->nutSize);
    }
}

bool	Act::NutStream::writeHash(IBuffer&) const
{
  return true;
}




Act::Root::Root(const Object* parent, const std::string& name)
  : Entry(parent, "Root", name), nutstream(nullptr)
{}

Act::Root::~Root()
{
  delete this->nutstream;
}

bool	Act::Root::readValue(IBuffer& buf)
{
  if (!this->Entry::readValue(buf))
    return false;

  this->nutstream = Object::read<NutStream>(this, buf, "nutstream");
  if (!this->nutstream)
    return false;
  addMember(nutstream);
  return true;
}

void	Act::Root::print(std::ostream& os) const
{
  this->Entry::print(os);
  os << printIndent() << *this->nutstream;
}

bool	Act::Root::writeValue(IBuffer& buf) const
{
  if (!this->Entry::writeValue(buf))
    return false;
  return this->nutstream->writeValue(buf);
}

bool	Act::Root::writeHash(IBuffer& buf) const
{
  return buf.writeInt(0);
}




Act::Layer::Layer(const Object* parent, const std::string& name)
  : Entry(parent, "Layer", name), keyframes(this, "keyframes"), weirdarray(this, "weirdarray"), nutstream(nullptr)
{
  addMember(&this->keyframes);
}

Act::Layer::~Layer()
{
  delete this->nutstream;
}

bool	Act::Layer::readValue(IBuffer& buf)
{
  if (!this->Entry::readValue(buf))
    return false;

  uint32_t	nbOfKeyframes = buf.readInt();
  for (unsigned int i = 0; i < nbOfKeyframes; i++)
    if (!this->keyframes.add(Act::Entry::read, buf))
      return false;

  // Zero-terminated array
  while (true)
    {
      uint32_t value = buf.readInt();
      if (value == 0)
        break;
      auto number = new ActNut::Number<uint32_t>(&weirdarray, "number", "");
      *number = value;
      weirdarray.push_back(number);
    }

  this->nutstream = Object::read<NutStream>(this, buf, "nutstream");
  if (!this->nutstream)
    return false;

  addMember(nutstream);
  return true;
}

void	Act::Layer::print(std::ostream& os) const
{
  this->Entry::print(os);
  os << printIndent() << "  " << this->keyframes;
  os << printIndent() << "  " << this->weirdarray;
  os << printIndent() << "  " << *this->nutstream;
}

bool	Act::Layer::writeValue(IBuffer& buf) const
{
  if (!this->Entry::writeValue(buf))
    return false;

  buf.writeInt(this->keyframes.size());
  for (Object* it : this->keyframes)
    if (!it->writeValue(buf))
      return false;

  // Zero-terminated array
  for (ActNut::Object *it : this->weirdarray)
    buf.writeInt(*dynamic_cast<ActNut::Number<uint32_t>* >(it));
  buf.writeInt(0);

  return this->nutstream->writeValue(buf);
}

// Compatibility: elem->keyframe used to return the 1st keyframe.
ActNut::Object*	Act::Layer::operator[](const char* key)
{
  if (strcmp(key, "keyframe") == 0 && this->keyframes.size() == 1)
    return this->keyframes["0"];
  return this->Entry::operator[](key);
}

const ActNut::Object*	Act::Layer::operator[](const char* key) const
{
  if (strcmp(key, "keyframe") == 0 && this->keyframes.size() == 1)
    return this->keyframes["0"];
  return this->Entry::operator[](key);
}




Act::KeyFrame::KeyFrame(const Object* parent, const std::string& name)
  : Entry(parent, "KeyFrame", name), layout(nullptr)
{}

Act::KeyFrame::~KeyFrame()
{
  delete this->layout;
}

bool	Act::KeyFrame::readValue(IBuffer& buf)
{
  if (!this->Entry::readValue(buf))
    return false;

  uint8_t hasLayout = buf.readByte();
  if (hasLayout != 1)
    {
      std::cout << "[KeyFrame] HasLayout == " << hasLayout << " - should be 1" << std::endl;
      return false;
    }

  this->layout = Act::Entry::read(this, buf, "layout");
  if (!this->layout)
    return false;
  addMember(layout);
  return true;
}

void	Act::KeyFrame::print(std::ostream& os) const
{
  this->Entry::print(os);
  os << printIndent() << "  " << *this->layout;
}

bool	Act::KeyFrame::writeValue(IBuffer& buf) const
{
  if (!this->Entry::writeValue(buf))
    return false;
  buf.writeByte(1);
  return this->layout->writeValue(buf);
}




Act::SpriteLayout::SpriteLayout(const Object* parent, const std::string& name)
  : Entry(parent, "SpriteLayout", name)
{}




Act::IFSMeshLayout::IFSMeshLayout(const Object* parent, const std::string& name)
  : Entry(parent, "IFSMeshLayout", name)
{}




Act::StringLayout::StringLayout(const Object* parent, const std::string& name)
  : Entry(parent, "StringLayout", name)
{}

bool	Act::StringLayout::readValue(IBuffer& buf)
{
  if (!this->Entry::readValue(buf))
    return false;

  for (Act::Object* it : this->array)
    {
      Act::Array* array = dynamic_cast<Act::Array*>(it);
      if (array)
	array->readContent(buf);
    }
  return true;
}

Act::Object*	Act::StringLayout::createObjectFromType(uint32_t type, const Object* parent, const std::string& name)
{
  if (type == 5)
    return new Act::Array(parent, name);
  else
    return this->Act::Entry::createObjectFromType(type, parent, name);
}

bool	Act::StringLayout::writeValue(IBuffer& buf) const
{
  if (!this->Entry::writeValue(buf))
    return false;

  for (Act::Object* it : this->array)
    {
      Act::Array* array = dynamic_cast<Act::Array*>(it);
      if (array)
	if (array->writeContent(buf) == false)
	  return false;
    }
  return true;
}




Act::ReservedLayout::ReservedLayout(const Object* parent, const std::string& name)
  : Entry(parent, "ReservedLayout", name)
{}




Act::BitmapFontResource::BitmapFontResource(const Object* parent, const std::string& name)
  : Entry(parent, "BitmapFontResource", name), bitmapInfo(this, "bitmapinfo"), bitmapFontData(nullptr)
{
  addMember(&bitmapInfo);
}

Act::BitmapFontResource::~BitmapFontResource()
{
  if (this->bitmapFontData)
    {
      for (uint32_t i = 0; i < this->height; i++)
	delete[] this->bitmapFontData[i];
      delete[] this->bitmapFontData;
    }
}

bool	Act::BitmapFontResource::readValue(IBuffer& buf)
{
  if (!this->Entry::readValue(buf) || !this->readArray(buf, this->bitmapInfo))
    return false;

  this->width = buf.readInt();
  this->height = buf.readInt();
  this->bitmapFontData = new uint8_t*[this->height];
  for (uint32_t i = 0; i < this->height; i++)
    {
      this->bitmapFontData[i] = new uint8_t[this->width];
      if (!buf.readBytes(this->bitmapFontData[i], this->width))
	return false;
    }
  return true;
}

Act::Object*	Act::BitmapFontResource::createObjectFromType(uint32_t type, const Object* parent, const std::string& name)
{
  if (type == 5)
    return new Act::Integer5(parent, name);
  else
    return this->Act::Entry::createObjectFromType(type, parent, name);
}

void	Act::BitmapFontResource::print(std::ostream& os) const
{
  this->Entry::print(os);
  os << printIndent() << "  " << this->bitmapInfo;

  os << printIndent() << "  bitmapFontData:" << std::endl;
  for (uint32_t i = 0; i < this->height; i++)
    {
      os << printIndent(getIndentLevel() + 1) << "  [";
      for (uint32_t j = 0; j < this->width; j++)
	{
	  os << (int)this->bitmapFontData[i][j];
	  if (j != this->width - 1)
	    os << ", ";
	}
      os << "]";
      if (i != this->height - 1)
	os << ",";
      os << std::endl;
    }
}

bool	Act::BitmapFontResource::writeValue(IBuffer& buf) const
{
  if (!this->Entry::writeValue(buf) || !this->writeArray(buf, this->bitmapInfo))
    return false;

  buf.writeInt(this->width);
  buf.writeInt(this->height);
  for (uint32_t i = 0; i < this->height; i++)
    {
      if (!buf.writeBytes(this->bitmapFontData[i], this->width))
	return false;
    }
  return true;
}




Act::ImageResource::ImageResource(const Object* parent, const std::string& name)
  : Entry(parent, "ImageResource", name)
{}




Act::RenderTarget::RenderTarget(const Object* parent, const std::string& name)
  : Entry(parent, "RenderTarget", name)
{}
