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
  os << o.getName() << ": ";
  o.print(os);
  return os;
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
  os << "[" << std::endl;
  for (Object* it : *this)
    os << printIndent() << *it << std::endl;
  os << printIndent(this->getIndentLevel() - 1) << "  ]" << std::endl;
}
