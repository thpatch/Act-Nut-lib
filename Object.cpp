#include	<sstream>
#include	<string.h>
#include	"Object.hpp"

bool	ActNut::Object::_printFullNames = false;

void	ActNut::Object::printFullNames(bool value)
{
  _printFullNames = value;
}

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

uint32_t	ActNut::Object::getNumType() const
{
  return 0xFFFFFFFF;
}

std::string	ActNut::Object::getFullName() const
{
  if (this->parent)
    return this->parent->getFullName() + "/" + this->name;
  else
    return "";
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

bool	ActNut::Object::writeToFile(const std::string& filename) const
{
  FileBuffer	buf(filename, std::ios_base::out);
  return this->writeValue(buf);
}

std::ostream& ActNut::operator<<(std::ostream& os, const Object& o)
{
  if (ActNut::Object::_printFullNames == false)
    {
      if (o.getName().empty() == false && o.getName()[0])
	os << o.getName() << ": ";
    }
  else
    os << o.getFullName() << ": ";
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

ActNut::Object*	ActNut::Object::getChild(const char* _path)
{
  char*			path = strdup(_path);
  char*			path_cur = path;
  char*			path_next;
  ActNut::Object*	obj;

  obj = this;
  while (path_cur)
    {
      while (*path_cur == '/')
	path_cur++;
      path_next = strchr(path_cur, '/');
      if (path_next)
	{
	  *path_next = '\0';
	  path_next++;
	}
      obj = (*obj)[path_cur];
      if (!obj)
	break ;
      path_cur = path_next;
    }
  free(path);
  return obj;
}

const ActNut::Object*	ActNut::Object::getChild(const char* _path) const
{
  char*			path = strdup(_path);
  char*			path_cur = path;
  char*			path_next;
  const ActNut::Object*	obj;

  obj = this;
  while (path_cur)
    {
      while (*path_cur == '/')
	path_cur++;
      path_next = strchr(path_cur, '/');
      if (path_next)
	{
	  *path_next = '\0';
	  path_next++;
	}
      obj = (*obj)[path_cur];
      if (!obj)
	break ;
      path_cur = path_next;
    }
  free(path);
  return obj;
}

const ActNut::Object&	ActNut::String::operator=(const std::string& new_value)
{
  this->value = new_value;
  return *this;
}


ActNut::String::String(const Object* parent, const char* type, const std::string& name)
  : Object(parent, type, name)
{}

bool	ActNut::String::readValue(IBuffer& buf)
{
  uint32_t	length = buf.readInt();
  char*		str = new char[length];
  buf.readBytes((uint8_t*)str, length);
  this->value = std::string(str, length);
  delete[] str;
  return true;
}

void	ActNut::String::print(std::ostream& os) const
{
  os << '"' << this->value << '"';
}

bool	ActNut::String::writeValue(IBuffer& buf) const
{
  buf.writeInt(this->value.length());
  return buf.writeBytes((const uint8_t*)this->value.c_str(), this->value.length());
}

const ActNut::Object&	ActNut::Object::operator=(const std::string&)
{
  Error::error(std::string(this->type) + " doesn't support operator=");
  return *this;
}



ActNut::vector::~vector()
{
  for (ActNut::Object* it : *this)
    delete it;
}

bool	ActNut::vector::readValue(IBuffer&)
{
  throw std::logic_error("Calling readValue doesn't make sense on an Act::vector");
}

bool	ActNut::vector::writeValue(IBuffer&) const
{
  throw std::logic_error("Calling writedValue doesn't make sense on an Act::vector");
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
