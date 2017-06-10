#include	<sstream>
#include	<fstream>
#include	<act/File.hpp>

Act::File::File(const Act::Object* parent, const std::string& name)
  : Object(parent, "File", name), sprites(this, "sprites"), resources(this, "resources")
{}

Act::File::~File()
{
  delete this->mainEntry;
}

Act::File*	Act::File::read(const std::string& filename)
{
  std::ifstream	f(filename);
  size_t	len;
  uint8_t*	byteBuf;

  f.seekg(0, std::ios::end);
  len = f.tellg();
  f.seekg(0, std::ios::beg);

  byteBuf = new uint8_t[len];
  f.read((char*)byteBuf, len);
  f.close();

  Buffer	buf(byteBuf, len, true);
  return ActNut::Object::read<Act::File>(nullptr, buf, filename);
}


bool	Act::File::readValue(Buffer& buf)
{
  if (!buf.checkTag('1TCA') || // ACT1
      !buf.checkTag(1))
    return false;

  // Main entry
  this->mainEntry = Act::Entry::read(this, buf, Act::Entry::HAVE_NUT);
  if (!this->mainEntry)
    return Error::error("Reading main entry failed.");

  // Sprites
  uint32_t nbSprites = buf.readInt();
  for (uint32_t i = 0; i < nbSprites; i++)
    {
      Act::Entry* entry = Act::Entry::read(this, buf, Act::Entry::HAVE_NUT | Act::Entry::HAVE_SUB_ENTRY | Act::Entry::HAVE_SUB_ENTRY_COUNT);
      if (!entry)
	{
	  std::ostringstream ss;
	  ss << "Reading sprite " << i + 1 << " failed.";
	  return Error::error(ss.str());
	}
      this->sprites.push_back(entry);
    }

  // Resources
  uint32_t nbResources = buf.readInt();
  for (uint32_t i = 0; i < nbResources; i++)
    {
      Act::Entry* entry = Act::Entry::read(this, buf, 0);
      if (!entry)
	{
	  std::ostringstream ss;
	  ss << "Reading resource " << i + 1 << " failed.";
	  return Error::error(ss.str());
	}
      this->resources.push_back(entry);
    }

  return true;
}

void	Act::File::print(std::ostream& os) const
{
  os << printIndent() << *this->mainEntry << std::endl;
  os << printIndent() << this->sprites;
  os << printIndent() << this->resources;
}
