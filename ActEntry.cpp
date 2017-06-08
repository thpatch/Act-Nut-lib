#include	<sstream>
#include	<string.h>
#include	"ActEntry.hpp"
#include	"ActEntries.hpp"

Act::Entry::Entry(const Act::Object* parent, const char* type_name, int flags)
  : Object(parent, 0xFFFFFFFF, "entry", type_name), flags(flags),
    array(this, "array"), subEntry(nullptr), nutInfo(this, "nutInfo"), nut(nullptr)
{}

Act::Entry::~Entry()
{
  for (Act::Object* it : this->array)
    delete it;
  if (this->subEntry)
    delete this->subEntry;
  for (Act::Object* it : this->nutInfo)
    delete it;
  if (this->nut)
    delete this->nut;
}

const char* Act::Entry::type_names[] = {
  ".?AVActFileResourceInfo@@",
  ".?AVC2DLayout@@",
  ".?AVC2DMapLayout@@",
  ".?AVCAct@@",
  ".?AVCActFileResource@@",
  ".?AVCActKey@@",
  ".?AVCActLayer@@",
  ".?AVCActLayout@@",
  ".?AVCActRenderTarget@@",
  ".?AVCActResource2D@@",
  ".?AVCActResourceChip@@",
  ".?AVCActScript@@",
  ".?AVCActTimeLine@@",
  ".?AVCPhysics2DWorldResource@@",
  ".?AVCReservedLayout@@",
  ".?AVCStringLayout@@",
  ".?AVIFSResourceInfo@@",
  ".?AVTextureResourceInfo@@",
  "ActData",
  "ActFileResource",
  "ActFileResourceInfo",
  "ActLayout",
  "BitmapFontResource",
  "ChipResource",
  "IFSMeshLayout",
  "IFSMeshResource",
  "IFSResourceInfo",
  "ImageResource",
  "KeyFrame",
  "Layer",
  "Manbow::Render1",
  "ManbowRenderLayout",
  "Map2DLayout",
  "Physics2DWorldResource",
  "RenderTarget",
  "ReservedLayout",
  "Script",
  "SpriteLayout",
  "StringLayout",
  "TextureResourceInfo",
  "TimeLine",
  nullptr
};
std::map<uint32_t, const char*>	Act::Entry::type_hashes;

void	Act::Entry::init_hashes()
{
  for (int i = 0; type_names[i]; i++)
    type_hashes[type_name_to_hash(type_names[i])] = type_names[i];
}

uint32_t	Act::Entry::type_name_to_hash(const char* name)
{
  uint32_t	hash;

  hash = 0;
  while (*name)
    {
      uint32_t	tmp = (hash >> 2) + (hash << 6);
      tmp += *name + 0x9E3779B9;
      hash ^= tmp;
      name++;
    }
  return hash;
}

const char*	Act::Entry::type_hash_to_name(uint32_t hash)
{
  if (hash == 0)
    return "Root";

  const auto&	it = type_hashes.find(hash);
  if (it != type_hashes.end())
    return it->second;
  else
    return "Unknown";
}

Act::Entry*	Act::Entry::read(Buffer& buf, const Act::Object* parent, int flags)
{
  uint32_t	type_hash = buf.readInt();
  const char*	type = Act::Entry::type_hash_to_name(type_hash);
  Act::Entry*	entry;

  // Root
  if (strcmp(type, "Root") == 0)
    entry = new Act::Root(parent);

  // Layer
  else if (strcmp(type, "Layer") == 0)
    entry = new Act::Layer(parent);
  else if (strcmp(type, "KeyFrame") == 0)
    entry = new Act::KeyFrame(parent);
  else if (strcmp(type, "SpriteLayout") == 0)
    entry = new Act::SpriteLayout(parent);
  else if (strcmp(type, "StringLayout") == 0)
    entry = new Act::StringLayout(parent);
  else if (strcmp(type, "ReservedLayout") == 0)
    entry = new Act::ReservedLayout(parent);

  // Resources
  else if (strcmp(type, "BitmapFontResource") == 0)
    entry = new Act::BitmapFontResource(parent);
  else if (strcmp(type, "ImageResource") == 0)
    entry = new Act::ImageResource(parent);
  else if (strcmp(type, "RenderTarget") == 0)
    entry = new Act::RenderTarget(parent);

  // Generic
  else
    {
      std::cout << "Warning: unknown type " << type << " (hash=" << type_hash << "). Defaulting to the generic Act::Entry." << std::endl;
      entry = new Act::Entry(parent, type, flags);
    }

  if (!entry->readValue(buf))
    {
      delete entry;
      return nullptr;
    }
  return entry;
}

bool	Act::Entry::readValue(Buffer& buf)
{
  return this->readArray(buf, this->array);
}

Act::Object*	Act::Entry::readObject(Buffer& buf)
{
  uint32_t	name_size = buf.readInt();
  const char*	name_str = (const char*)buf.returnBytes(name_size);
  if (!name_str)
    return nullptr;
  std::string	name(name_str, name_size);

  uint32_t	type = buf.readInt();
  return this->createObjectFromType(type, name);
}

Act::Object*	Act::Entry::createObjectFromType(uint32_t type, const std::string& name)
{
  switch (type)
    {
    case 0:
      return new Act::Integer(this, name);
    case 1:
      return new Act::Float(this, name);
    case 2:
      return new Act::Boolean(this, name);
    case 3:
      return new Act::String(this, name);
    default:
      std::ostringstream ss;
      ss << "Unknown type " << type;
      Error::error(ss.str());
      return nullptr;
    }
}

bool	Act::Entry::readArray(Buffer& buf, std::vector<Act::Object*>& array)
{
  uint8_t isArray = buf.readByte();
  if (isArray != 1)
    {
      std::cout << "Warning: not an array" << std::endl;
      return false;
    }

  uint32_t	nb_elems = buf.readInt();
  for (unsigned int i = 0; i < nb_elems; i++)
    {
      Act::Object*	obj = this->readObject(buf);
      if (!obj)
	return false;
      array.push_back(obj);
    }
  for (Act::Object* it : array)
    if (!it->readValue(buf))
      return false;
  return true;
}

bool	Act::Entry::readNut(Buffer& buf, std::vector<Act::Object*>& nutInfo)
{
  if (!this->readArray(buf, nutInfo))
    return false;

  uint32_t		nut_size = buf.readInt();
  const uint8_t*	nut_buf = buf.returnBytes(nut_size);
  (void)nut_buf;
  // this->nut = loadnut(nut_buf);
  return true;
}

void	Act::Entry::print(std::ostream& os) const
{
  os << std::endl;

  os << printIndent() << "  " << this->array;

  if (this->subEntry)
    os << printIndent() << "  " << *this->subEntry;

  if (this->flags & HAVE_NUT)
    os << printIndent() << "  " << this->nutInfo;
}
