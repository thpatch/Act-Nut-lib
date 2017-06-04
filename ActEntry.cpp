#include	"ActEntry.hpp"
#include	"nut/utils.hpp"

Act::Entry::Entry(const std::string& name, int flags)
  : Object(0xFFFFFFFF, "entry", name), flags(flags), subEntry(nullptr), nut(nullptr)
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

bool	Act::Entry::readValue(Buffer& buf)
{
  this->id = buf.readInt();

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
	this->subEntry = new Act::Entry("SubEntry", HAVE_SUB_ENTRY);
      else
	this->subEntry = new Act::Entry("SubEntry", 0);
      if (!this->subEntry->readValue(buf))
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
  os << "id: " << this->id << std::endl;

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
