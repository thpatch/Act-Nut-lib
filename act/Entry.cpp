#include	<string.h>
#include	"act/Entry.hpp"
#include	"act/Entries.hpp"
#include	"act/Object.hpp"

Act::Entry::Entry(const Object* parent, const char* type, const std::string& name)
  : Object(parent, type, name), array(this, "members")
{
  addMember(&array);
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

  if (type_hashes.size() == 0)
    init_hashes();
  const auto&	it = type_hashes.find(hash);
  if (it != type_hashes.end())
    return it->second;
  else
    return "Unknown";
}

Act::Entry*	Act::Entry::read(const Object* parent, IBuffer& buf, const std::string& name)
{
  uint32_t	type_hash = buf.readInt();
  const char*	type = Entry::type_hash_to_name(type_hash);
  Entry*	entry;

  // Root
  if (strcmp(type, "Root") == 0)
    entry = new Act::Root(parent, name);

  // Layer
  else if (strcmp(type, "Layer") == 0)
    entry = new Act::Layer(parent, name);
  else if (strcmp(type, "KeyFrame") == 0)
    entry = new Act::KeyFrame(parent, name);
  else if (strcmp(type, "SpriteLayout") == 0)
    entry = new Act::SpriteLayout(parent, name);
  else if (strcmp(type, "IFSMeshLayout") == 0)
    entry = new Act::IFSMeshLayout(parent, name);
  else if (strcmp(type, "StringLayout") == 0)
    entry = new Act::StringLayout(parent, name);
  else if (strcmp(type, "ReservedLayout") == 0)
    entry = new Act::ReservedLayout(parent, name);

  // Resources
  else if (strcmp(type, "BitmapFontResource") == 0)
    entry = new Act::BitmapFontResource(parent, name);
  else if (strcmp(type, "ImageResource") == 0)
    entry = new Act::ImageResource(parent, name);
  else if (strcmp(type, "RenderTarget") == 0)
    entry = new Act::RenderTarget(parent, name);

  // Generic
  else
    {
      std::cout << "Warning: unknown type " << type << " (hash=" << type_hash << "). Defaulting to the generic Act::Entry." << std::endl;
      entry = new Act::Entry(parent, type, name);
    }

  if (!entry->readValue(buf))
    {
      delete entry;
      return nullptr;
    }
  return entry;
}

bool	Act::Entry::readValue(IBuffer& buf)
{
  return this->readArray(buf, this->array);
}

bool	Act::Entry::writeValue(IBuffer& buf) const
{
  return this->writeHash(buf) && this->writeArray(buf, this->array);
}

Act::Object*	Act::Entry::readObject(const Object* parent, IBuffer& buf)
{
  uint32_t	name_size = buf.readInt();
  char*		name_str = new char[name_size];
  buf.readBytes((uint8_t*)name_str, name_size);
  std::string	name(name_str, name_size);
  delete[] name_str;

  uint32_t	type = buf.readInt();
  return this->createObjectFromType(type, parent, name);
}

bool	Act::Entry::writeObject(IBuffer& buf, Object* obj) const
{
  const std::string& name = obj->getName();
  buf.writeInt(name.length());
  buf.writeBytes((const uint8_t*)name.c_str(), name.length());
  buf.writeInt(obj->getNumType());
  return true;
}

Act::Object*	Act::Entry::createObjectFromType(uint32_t type, const Object* parent, const std::string& name)
{
  switch (type)
    {
    case 0:
      return new Act::Integer(parent, name);
    case 1:
      return new Act::Float(parent, name);
    case 2:
      return new Act::Boolean(parent, name);
    case 3:
      return new Act::String(parent, name);
    default:
      Error::error(std::string("Unknown type ") + std::to_string(type));
      return nullptr;
    }
}

bool	Act::Entry::readArray(IBuffer& buf, vector& array)
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
      Act::Object*	obj = this->readObject(&array, buf);
      if (!obj)
	return false;
      array.push_back(obj);
    }
  for (Act::Object* it : array)
    if (!it->readValue(buf))
      return false;
  return true;
}

bool	Act::Entry::writeArray(IBuffer& buf, const vector& array) const
{
  buf.writeByte(1);
  buf.writeInt(array.size());
  for (Act::Object* it : array)
    if (this->writeObject(buf, it) == false)
      return false;
  for (Act::Object* it : array)
    if (it->writeValue(buf) == false)
      return false;
  return true;
}

bool	Act::Entry::writeHash(IBuffer& buf) const
{
  return buf.writeInt(type_name_to_hash(this->type));
}

void	Act::Entry::print(std::ostream& os) const
{
  os << std::endl;
  os << printIndent() << "  " << this->array;
}

ActNut::Object*	Act::Entry::operator[](const char* key)
{
  Object*	obj = this->Object::operator[](key);
  if (obj != nullptr)
    return obj;

  for (Object* it : this->array)
    if (it->getName() == key)
      return it;

  return nullptr;
}

const ActNut::Object*	Act::Entry::operator[](const char* key) const
{
  const Object*	obj = this->Object::operator[](key);
  if (obj != nullptr)
    return obj;

  for (Object* it : this->array)
    if (it->getName() == key)
      return it;

  return nullptr;
}
