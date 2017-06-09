#include	<act/Entries.hpp>

Act::Root::Root(const Object* parent)
  : Entry(parent, "Root", Act::Entry::HAVE_NUT)
{}

bool	Act::Root::readValue(Buffer& buf)
{
  if (!this->readArray(buf, this->array))
    return false;

  return this->readNut(buf, this->nutInfo);
}




Act::Layer::Layer(const Object* parent)
  : Entry(parent, "Layer", Act::Entry::HAVE_NUT | Act::Entry::HAVE_SUB_ENTRY | Act::Entry::HAVE_SUB_ENTRY_COUNT)
{}

bool	Act::Layer::readValue(Buffer& buf)
{
  if (!this->readArray(buf, this->array))
    return false;

  uint32_t	nbOfSubEntries = buf.readInt();
  if (nbOfSubEntries > 1)
    {
      std::cout << "[Layer] Only 0 and 1 sub entries are supported (got " << nbOfSubEntries << ")." << std::endl;
      return false;
    }

  if (nbOfSubEntries)
    {
      this->subEntry = Act::Entry::read(buf, this, HAVE_SUB_ENTRY);
      if (!this->subEntry)
	return false;
    }

  uint32_t nbOfSubEntries2 = buf.readInt();
  if (nbOfSubEntries2 != 0)
    {
      std::cout << "[Layer] SubEntries2 is not supported yet." << std::endl;
      return false;
    }

  return this->readNut(buf, this->nutInfo);
}




Act::KeyFrame::KeyFrame(const Object* parent)
  : Entry(parent, "KeyFrame", Act::Entry::HAVE_SUB_ENTRY)
{}

bool	Act::KeyFrame::readValue(Buffer& buf)
{
  if (!this->readArray(buf, this->array))
    return false;

  uint8_t isSubEntry = buf.readByte();
  if (isSubEntry != 1)
    {
      std::cout << "[KeyFrame] IsSubEntry == " << isSubEntry << " - should be 1" << std::endl;
      return false;
    }

  this->subEntry = Act::Entry::read(buf, this, 0);
  if (!this->subEntry)
    return false;
  return true;
}




Act::SpriteLayout::SpriteLayout(const Object* parent)
  : Entry(parent, "SpriteLayout", 0)
{}




Act::StringLayout::StringLayout(const Object* parent)
  : Entry(parent, "StringLayout", 0)
{}

bool	Act::StringLayout::readValue(Buffer& buf)
{
  if (!this->readArray(buf, this->array))
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




Act::ReservedLayout::ReservedLayout(const Object* parent)
  : Entry(parent, "ReservedLayout", 0)
{}




Act::BitmapFontResource::BitmapFontResource(const Object* parent)
  : Entry(parent, "BitmapFontResource", 0), subArray(this, "subArray"), bitmapFontData(nullptr)
{}

Act::BitmapFontResource::~BitmapFontResource()
{
  if (this->bitmapFontData)
    {
      for (uint32_t i = 0; i < this->height; i++)
	delete this->bitmapFontData[i];
      delete this->bitmapFontData;
    }
}

bool	Act::BitmapFontResource::readValue(Buffer& buf)
{
  if (!this->readArray(buf, this->array) || !this->readArray(buf, this->subArray))
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




Act::ImageResource::ImageResource(const Object* parent)
  : Entry(parent, "ImageResource", 0)
{}




Act::RenderTarget::RenderTarget(const Object* parent)
  : Entry(parent, "RenderTarget", 0)
{}
