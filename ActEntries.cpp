#include	"ActEntries.hpp"

Act::Root::Root()
  : Entry("Root", Act::Entry::HAVE_NUT)
{}

bool	Act::Root::readValue(Buffer& buf)
{
  if (!this->readArray(buf, this->array))
    return false;

  return this->readNut(buf, this->nutInfo);
}




Act::Layer::Layer()
  : Entry("Layer", Act::Entry::HAVE_NUT | Act::Entry::HAVE_SUB_ENTRY | Act::Entry::HAVE_SUB_ENTRY_COUNT)
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
      this->subEntry = Act::Entry::read(buf, HAVE_SUB_ENTRY);
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




Act::KeyFrame::KeyFrame()
  : Entry("KeyFrame", Act::Entry::HAVE_SUB_ENTRY)
{}

bool	Act::KeyFrame::readValue(Buffer& buf)
{
  if (!this->readArray(buf, this->array))
    return false;

  uint8_t isSubEntry;
  buf.readBytes(&isSubEntry, 1);
  if (isSubEntry != 1)
    {
      std::cout << "[KeyFrame] IsSubEntry == " << isSubEntry << " - should be 1" << std::endl;
      return false;
    }

  this->subEntry = Act::Entry::read(buf, 0);
  if (!this->subEntry)
    return false;
  return true;
}




Act::SpriteLayout::SpriteLayout()
  : Entry("SpriteLayout", 0)
{}




Act::StringLayout::StringLayout()
  : Entry("StringLayout", 0)
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
    return new Act::Array(name);
  else
    return this->Act::Entry::createObjectFromType(type, name);
}




Act::ReservedLayout::ReservedLayout()
  : Entry("ReservedLayout", 0)
{}




Act::BitmapFontResource::BitmapFontResource()
  : Entry("BitmapFontResource", 0), bitmapFontData(nullptr)
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
    return new Act::Integer5(name);
  else
    return this->Act::Entry::createObjectFromType(type, name);
}




Act::ImageResource::ImageResource()
  : Entry("ImageResource", 0)
{}




Act::RenderTarget::RenderTarget()
  : Entry("RenderTarget", 0)
{}
