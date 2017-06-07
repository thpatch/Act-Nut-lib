#include	"ActEntry.hpp"
#include	"nut/utils.hpp"

Act::Entry::Entry(const char* type_name, int flags)
  : Object(0xFFFFFFFF, "entry", type_name), flags(flags), type_name(type_name), subEntry(nullptr), nut(nullptr)
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
  ".?AVCAct@@",
  ".?AVCActKey@@",
  ".?AVCActLayer@@",
  "ActData",
  "ActFileResource",
  "ActLayout",
  "ChipResource",
  "IFSMeshLayout",
  "IFSMeshResource",
  "IFSResourceInfo",
  "ImageResource",
  "KeyFrame",
  "Layer",
  "Manbow::Render1",
  "Map2DLayout",
  "RenderTarget",
  "ReservedLayout",
  "Script",
  "SpriteLayout",
  "StringLayout",
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
  const auto&	it = type_hashes.find(hash);
  if (it != type_hashes.end())
    return it->second;
  else
    return "Unknown";
}

Act::Entry*	Act::Entry::read(Buffer& buf, int flags)
{
  uint32_t	type_hash = buf.readInt();
  const char*	type = Act::Entry::type_hash_to_name(type_hash);
  Act::Entry*	entry = new Act::Entry(type, flags);
  if (!entry->readValue(buf))
    {
      delete entry;
      return nullptr;
    }
  return entry;
}

bool	Act::Entry::readValue(Buffer& buf)
{
  if (!this->readArray(buf, this->array))
    return false;

  if (this->flags & HAVE_SUB_ENTRY)
    {
      uint32_t		nbOfSubEntries;
      if (this->flags & HAVE_SUB_ENTRY_COUNT)
	nbOfSubEntries = buf.readInt();
      else
	{
	  uint8_t isSubEntry;
	  buf.readBytes(&isSubEntry, 1);
	  if (isSubEntry != 1)
	    {
	      std::cout << "IsSubEntry == " << isSubEntry << " - should be 1" << std::endl;
	      return false;
	    }
	  nbOfSubEntries = 1;
	}
      if (nbOfSubEntries > 1)
	{
	  std::cout << "Only 0 and 1 sub entries are supported (got " << nbOfSubEntries << ")." << std::endl;
	  return false;
	}

      if (this->flags & HAVE_SUB_ENTRY_COUNT)
	this->subEntry = Act::Entry::read(buf, HAVE_SUB_ENTRY);
      else
	this->subEntry = Act::Entry::read(buf, 0);
      if (!this->subEntry)
	return false;


      if (this->flags & HAVE_SUB_ENTRY_COUNT)
	{
	  uint32_t nbOfSubEntries2 = buf.readInt();
	  if (nbOfSubEntries2 != 0)
	    {
	      std::cout << "SubEntries2 is not supported yet." << std::endl;
	      return false;
	    }
	}
    }

  if (this->flags & HAVE_NUT)
    {
      if (!this->readArray(buf, this->nutInfo))
	return false;

      uint32_t		nut_size = buf.readInt();
      const uint8_t*	nut_buf = buf.returnBytes(nut_size);
      (void)nut_buf;
      // this->nut = loadnut(nut_buf);
    }

  return true;
}

bool	Act::Entry::readArray(Buffer& buf, std::vector<Act::Object*>& array)
{
  uint8_t isArray;
  if (!buf.readBytes(&isArray, 1))
    return false;
  if (isArray != 1)
    {
      std::cout << "Warning: not an array" << std::endl;
      return false;
    }

  uint32_t	nb_elems = buf.readInt();
  for (unsigned int i = 0; i < nb_elems; i++)
    {
      Act::Object*	obj = Act::Object::load(buf);
      if (!obj)
	return false;
      array.push_back(obj);
    }
  for (Act::Object* it : array)
    if (!it->readValue(buf))
      return false;
  return true;
}

void	Act::Entry::print(std::ostream& os) const
{
  os << "hash: " << this->type_hash << " - " << this->type_name << std::endl;

  os << "array: [" << std::endl;
  for (Act::Object* it : this->array)
    os << *it << std::endl;
  os << "]" << std::endl;

  if (this->subEntry)
    os << "subentry: " << *this->subEntry;

  if (this->flags & HAVE_NUT)
    {
      os << "nutInfo: [" << std::endl;
      for (Act::Object* it : this->nutInfo)
	os << *it << std::endl;
      os << "]" << std::endl;
    }
}
