#include	<sstream>
#include	<iomanip>
#include	<string.h>
#include	"SQObject.hpp"
#include	"utils.hpp"

int	SQObjectPtr::indentLevel = 0;

SQObjectPtr*	SQObjectPtr::Load(const uint8_t*& buf, std::string name)
{
  uint32_t	type = readInt(buf);

  switch (type)
    {
    case OT_STRING:
      return new SQString(buf, name);
    case OT_INTEGER:
      return new SQInteger(buf, name);
    case OT_BOOL:
      return new SQBoolean(buf, name);
    case OT_FLOAT:
      return new SQFloat(buf, name);
    case OT_NULL:
      return new SQNull(name);
    default:
      std::ostringstream ss;
      if (name.size() > 0)
	ss << "Could not create object " << name << ". ";
      ss << "Unknown object type 0x" << std::setfill('0') << std::setw(8) << std::hex << type;
      throw std::runtime_error(ss.str());
    }
}

std::string	SQObjectPtr::printIndent(bool printName) const
{
  std::ostringstream ss;
  for (int i = 0; i < SQObjectPtr::indentLevel * 2 - 2; i++)
    ss << " ";
  if (printName)
    {
      if (SQObjectPtr::indentLevel) ss << "- ";
      ss << this->type << ":";
      if (name.size() > 0)
	ss << name << "=";
    }
  else
    ss << "  ";
  return ss.str();
}

std::ostream& operator<<(std::ostream& os, const SQObjectPtr& o)
{
  o.print(os);
  return os;
}

SQString::SQString(const uint8_t*& buf, std::string name)
  : SQObjectPtr("SQString", name)
{
  this->len = readInt(buf);
  this->s = (char*)malloc(this->len + 1);
  readBytes(buf, (uint8_t*)this->s, this->len);
  this->s[this->len] = '\0';
}

SQString::~SQString()
{
  free(this->s);
}

void	SQString::print(std::ostream& os) const
{
  os << printIndent() << this->s;
}

void	SQNull::print(std::ostream& os) const
{
  os << printIndent();
}
