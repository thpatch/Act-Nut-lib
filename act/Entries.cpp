#include	"act/Entries.hpp"

Act::NutStream::NutStream(const Object* parent, const std::string& name)
  : Entry(parent, "NutStream", name), stream(nullptr)
{}

Act::NutStream::~NutStream()
{
  if (this->stream)
    delete this->stream;
}

bool	Act::NutStream::readValue(IBuffer& buf)
{
  if (!this->Entry::readValue(buf))
    return false;

  uint32_t		nutSize = buf.readInt();
  uint8_t*		nutBytes = new uint8_t[nutSize];
  buf.readBytes(nutBytes, nutSize);
  ActNut::MemoryBuffer	nutBuf(nutBytes, nutSize, true);
  this->stream = Object::read<Nut::Stream>(this, nutBuf, "stream");
  if (!this->stream)
    return false; 
  addMember(stream);
  return true;
}

void	Act::NutStream::print(std::ostream& os) const
{
  this->Entry::print(os);
  os << printIndent() << *stream;
}

bool	Act::NutStream::writeValue(IBuffer& buf) const
{
  if (!this->Entry::writeValue(buf))
    return false;

  ActNut::MemoryBuffer	nutBuf;
  if (!this->stream->writeValue(nutBuf))
    return false;
  buf.writeInt(nutBuf.getSize());
  return buf.writeBytes(nutBuf.getBuffer(), nutBuf.getSize());
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
  if (this->nutstream)
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
  : Entry(parent, "Layer", name), keyframe(nullptr), nutstream(nullptr)
{}

Act::Layer::~Layer()
{
  if (this->keyframe)
    delete this->keyframe;
  if (this->nutstream)
    delete this->nutstream;
}

bool	Act::Layer::readValue(IBuffer& buf)
{
  if (!this->Entry::readValue(buf))
    return false;

  uint32_t	nbOfKeyframes = buf.readInt();
  if (nbOfKeyframes > 1)
    {
      std::cout << "[Layer] Only 0 and 1 keyframes are supported (got " << nbOfKeyframes << ")." << std::endl;
      return false;
    }

  if (nbOfKeyframes == 1)
    {
      this->keyframe = Act::Entry::read(this, buf, "keyframe");
      if (!this->keyframe)
	return false;
    }

  uint32_t nbOfSomething = buf.readInt();
  if (nbOfSomething != 0)
    {
      std::cout << "[Layer] nbOfSomething must be 0 (because I don't know what this 'something' is)." << std::endl;
      return false;
    }


  this->nutstream = Object::read<NutStream>(this, buf, "nutstream");
  if (!this->nutstream)
    return false;

  addMember(keyframe);
  addMember(nutstream);
  return true;
}

void	Act::Layer::print(std::ostream& os) const
{
  this->Entry::print(os);
  if (this->keyframe)
    os << printIndent() << "  " << *this->keyframe;
  os << printIndent() << "  " << *this->nutstream;
}

bool	Act::Layer::writeValue(IBuffer& buf) const
{
  if (!this->Entry::writeValue(buf))
    return false;

  if (this->keyframe)
    {
      buf.writeInt(1);
      if (this->keyframe->writeValue(buf) == false)
	return false;
    }
  else
    buf.writeInt(0);

  buf.writeInt(0);
  return this->nutstream->writeValue(buf);
}




Act::KeyFrame::KeyFrame(const Object* parent, const std::string& name)
  : Entry(parent, "KeyFrame", name), layout(nullptr)
{}

Act::KeyFrame::~KeyFrame()
{
  if (this->layout)
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

Act::Object*	Act::StringLayout::createObjectFromType(uint32_t type, const std::string& name)
{
  if (type == 5)
    return new Act::Array(this, name);
  else
    return this->Act::Entry::createObjectFromType(type, name);
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
	delete this->bitmapFontData[i];
      delete this->bitmapFontData;
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

Act::Object*	Act::BitmapFontResource::createObjectFromType(uint32_t type, const std::string& name)
{
  if (type == 5)
    return new Act::Integer5(this, name);
  else
    return this->Act::Entry::createObjectFromType(type, name);
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
