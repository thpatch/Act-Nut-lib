#include	<sstream>
#include	<iomanip>
#include	<string.h>
#include	"SQObject.hpp"

int	Nut::SQObjectPtr::indentLevel = 0;

Nut::SQObjectPtr*	Nut::SQObjectPtr::Load(Buffer& buf, std::string name)
{
  uint32_t	type = buf.readInt();

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
      Error::error(ss.str());
      return nullptr;
    }
}

std::string	Nut::SQObjectPtr::printIndent(bool printName) const
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

std::ostream& Nut::operator<<(std::ostream& os, const SQObjectPtr& o)
{
  o.print(os);
  return os;
}

Nut::SQString::SQString(Buffer& buf, std::string name)
  : SQObjectPtr("SQString", name)
{
  this->len = buf.readInt();
  this->s = new char[this->len + 1];
  buf.readBytes((uint8_t*)this->s, this->len);
  this->s[this->len] = '\0';
}

Nut::SQString::~SQString()
{
  delete this->s;
}

void	Nut::SQString::print(std::ostream& os) const
{
  os << printIndent() << this->s;
}

void	Nut::SQNull::print(std::ostream& os) const
{
  os << printIndent();
}
