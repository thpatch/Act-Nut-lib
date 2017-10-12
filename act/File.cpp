#include	<fstream>
#include	"act/File.hpp"

Act::File::File(const Act::Object* parent, const std::string& name)
  : Object(parent, "File", name), mainEntry(nullptr), sprites(this, "sprites"), resources(this, "resources")
{
  addMember(&sprites);
  addMember(&resources);
}

Act::File::~File()
{
  delete this->mainEntry;
}

Act::File*	Act::File::read(const std::string& filename)
{
  return ActNut::Object::read<Act::File>(filename);
}


bool	Act::File::readValue(IBuffer& buf)
{
  if (!buf.checkTag('1TCA') || // ACT1
      !buf.checkTag(1))
    return false;

  // Main entry
  this->mainEntry = Act::Entry::read(this, buf, "root");
  if (!this->mainEntry)
    return Error::error("Reading main entry failed.");
  addMember(this->mainEntry);

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

bool	Act::File::writeValue(IBuffer& buf) const
{
  if (!buf.writeInt('1TCA') || // ACT1
      !buf.writeInt(1))
    return false;

  // Main entry
  if (!this->mainEntry->writeValue(buf))
    return Error::error("Writing main entry failed.");

  // Sprites
  buf.writeInt(this->sprites.size());
  for (Object* it : this->sprites)
    if (!it->writeValue(buf))
      return Error::error("Writing sprite failed.");

  // Resources
  buf.writeInt(this->resources.size());
  for (Object* it : this->resources)
    if (!it->writeValue(buf))
      return Error::error("Writing resource failed.");

  return true;
}
