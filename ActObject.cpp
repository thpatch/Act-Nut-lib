#include	<sstream>
#include	"ActObject.hpp"

Act::Object::Object(const Object* parent, uint32_t numType, const char* type, const std::string& name)
  : parent(parent), numType(numType), type(type), name(name)
{}

const std::string&	Act::Object::getName() const
{
  return this->name;
}

int	Act::Object::getIndentLevel() const
{
  if (this->parent)
    return this->parent->getIndentLevel() + 1;
  else
    return 0;
}

std::string	Act::Object::printIndent(int indentLevel) const
{
  if (indentLevel == -1)
    indentLevel = this->getIndentLevel();

  std::ostringstream ss;
  for (int i = 0; i < indentLevel; i++)
    ss << "    ";
  return ss.str();
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

bool	Act::vector::readValue(Buffer&)
{
  throw std::logic_error("Calling readValue doesn't make sense on an Act::vector");
}

void	Act::vector::print(std::ostream& os) const
{
  os << "[" << std::endl;
  for (Act::Object* it : *this)
    os << printIndent() << *it << std::endl;
  os << printIndent(this->getIndentLevel() - 1) << "  ]" << std::endl;
}
