#include	<sstream>
#include	"ActObject.hpp"

Act::Object*	Act::Object::load(Buffer& buf)
{
  uint32_t	name_size = buf.readInt();
  const char*	name_str = (const char*)buf.returnBytes(name_size);
  if (!name_str)
    return nullptr;
  std::string	name(name_str, name_size);
  uint32_t	type = buf.readInt();

  switch (type)
    {
    case 0:
      return new Act::Integer(name);
    case 1:
      return new Act::Float(name);
    case 2:
      return new Act::Boolean(name);
    case 3:
      return new Act::String(name);
    default:
      std::ostringstream ss;
      ss << "Unknown type " << type;
      throw std::runtime_error(ss.str());
    }
}

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
