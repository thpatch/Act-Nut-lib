#include	<sstream>
#include	"ActObject.hpp"

Act::Object::Object(uint32_t numType, const char* type, const std::string& name)
  : numType(numType), type(type), name(name)
{}

const std::string&	Act::Object::getName() const
{
  return this->name;
}

std::ostream& Act::operator<<(std::ostream& os, const Act::Object& o)
{
  os << o.getName() << ": ";
  o.print(os);
  return os;
}

bool	Act::String::readValue(Buffer& buf)
{
  uint32_t	length = buf.readInt();
  const char*	str = (const char*)buf.returnBytes(length);
  if (!str)
    return false;
  this->value = std::string(str, length);
  return true;
}

void	Act::String::print(std::ostream& os) const
{
  os << this->value;
}

bool	Act::Array::readValue(Buffer& buf)
{
  this->nbEntries = buf.readInt();
  return true;
}

bool	Act::Array::readContent(Buffer& buf)
{
  for (uint32_t i = 0; i < this->nbEntries; i++)
    this->entries.push_back(buf.readInt());
  return true;
}

void	Act::Array::print(std::ostream& os) const
{
  os << "[";
  for (auto it = this->entries.begin(); it != this->entries.end(); it++)
    {
      if (it != this->entries.begin())
        os << ", ";
      os << *it;
    }
  os << "]";
}
