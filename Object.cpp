#include	<sstream>
#include	"Object.hpp"

ActNut::Object::Object(const Object* parent, const char* type, const std::string& name)
  : parent(parent), type(type), name(name)
{}

void	ActNut::Object::addMember(Object* member)
{
  this->members.push_back(member);
}

const ActNut::Object*	ActNut::Object::getParent() const
{
  return this->parent;
}

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

ActNut::Object*	ActNut::Object::operator[](const char* key)
{
  for (Object* it : this->members)
    if (it->getName() == key)
      return it;
  return nullptr;
}

const ActNut::Object*	ActNut::Object::operator[](const char* key) const
{
  for (Object* it : this->members)
    if (it->getName() == key)
      return it;
  return nullptr;
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

ActNut::Object*	ActNut::vector::operator[](size_type n)
{
  return this->std::vector<Object*>::operator[](n);
}

const ActNut::Object*	ActNut::vector::operator[](size_type n) const
{
  return this->std::vector<Object*>::operator[](n);
}

ActNut::Object*	ActNut::vector::operator[](const char* key)
{
  // First, try by index
  char*	end;
  long	idx = strtol(key, &end, 10);
  if (!*end && 0 < idx && idx < (long)this->size())
    return (*this)[idx];

  // Then, search in our registered members (but we probably don't have any, we are a vector)
  Object*	obj = this->Object::operator[](key);
  if (obj != nullptr)
    return obj;

  // Finally, search if one of our elements has a key with this name
  for (Object* it : *this)
    if (it->getName() == key)
      return it;

  return nullptr;
}

const ActNut::Object*	ActNut::vector::operator[](const char* key) const
{
  // First, try by index
  char*	end;
  long	idx = strtol(key, &end, 10);
  if (!*end && 0 < idx && idx < (long)this->size())
    return (*this)[idx];

  // Then, search in our registered members (but we probably don't have any, we are a vector)
  const Object*	obj = this->Object::operator[](key);
  if (obj != nullptr)
    return obj;

  // Finally, search if one of our elements has a key with this name
  for (Object* it : *this)
    if (it->getName() == key)
      return it;

  return nullptr;
}
