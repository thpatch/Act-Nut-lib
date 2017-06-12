#include	<sstream>
#include	"Object.hpp"

ActNut::Object::Object(const Object* parent, const char* type, const std::string& name)
  : parent(parent), type(type), name(name)
{}

const std::string&	ActNut::Object::getName() const
{
  return this->name;
}

int	ActNut::Object::getIndentLevel() const
{
  if (this->parent)
    return this->parent->getIndentLevel() + 1;
  else
    return 0;
}

std::string	ActNut::Object::printIndent(int indentLevel) const
{
  if (indentLevel == -1)
    indentLevel = this->getIndentLevel();

  std::ostringstream ss;
  for (int i = 0; i < indentLevel; i++)
    ss << "    ";
  return ss.str();
}

std::ostream& ActNut::operator<<(std::ostream& os, const Object& o)
{
  if (o.getName().empty() == false && o.getName()[0])
    os << o.getName() << ": ";
  o.print(os);
  return os;
}



ActNut::String::String(const Object* parent, const char* type, const std::string& name)
  : Object(parent, type, name)
{}

bool	ActNut::String::readValue(Buffer& buf)
{
  uint32_t	length = buf.readInt();
  const char*	str = (const char*)buf.returnBytes(length);
  if (!str)
    return false;
  this->value = std::string(str, length);
  return true;
}

void	ActNut::String::print(std::ostream& os) const
{
  os << this->value;
}



ActNut::vector::~vector()
{
  for (ActNut::Object* it : *this)
    delete it;
}

bool	ActNut::vector::readValue(Buffer&)
{
  throw std::logic_error("Calling readValue doesn't make sense on an Act::vector");
}

void	ActNut::vector::print(std::ostream& os) const
{
  os << "[";
  if (this->size() != 0)
    os << std::endl;
  for (Object* it : *this)
    os << printIndent() << *it << std::endl;
  os << (this->size() != 0 ? printIndent(this->getIndentLevel() - 1) : "") << "  ]" << std::endl;
}
