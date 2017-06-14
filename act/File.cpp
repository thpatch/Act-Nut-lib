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
  this->mainEntry = Act::Entry::read(this, buf, "root");
  if (!this->mainEntry)
    return Error::error("Reading main entry failed.");

  // Sprites
  uint32_t nbSprites = buf.readInt();
  for (uint32_t i = 0; i < nbSprites; i++)
    if (!this->sprites.add(Act::Entry::read, buf))
      return Error::error(std::string("Reading sprite ") + std::to_string(i + 1) + " failed.");

  // Resources
  uint32_t nbResources = buf.readInt();
  for (uint32_t i = 0; i < nbResources; i++)
    if (!this->resources.add(Act::Entry::read, buf))
      return Error::error(std::string("Reading resource ") + std::to_string(i + 1) + " failed.");

  return true;
}

void	Act::File::print(std::ostream& os) const
{
  os << printIndent() << *this->mainEntry << std::endl;
  os << printIndent() << this->sprites;
  os << printIndent() << this->resources;
}
