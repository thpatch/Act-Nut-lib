#include	<sstream>
#include	<iomanip>
#include	<string.h>
#include	<nut/SQObject.hpp>

Nut::SQObjectPtr*	Nut::SQObjectPtr::Load(const Object* parent, Buffer& buf, std::string name)
{
  uint32_t	type = buf.readInt();

  switch (type)
    {
    case OT_STRING:
      return Object::read<SQString>( parent, buf, name);
    case OT_INTEGER:
      return Object::read<SQInteger>(parent, buf, name);
    case OT_BOOL:
      return Object::read<SQBoolean>(parent, buf, name);
    case OT_FLOAT:
      return Object::read<SQFloat>(  parent, buf, name);
    case OT_NULL:
      return Object::read<SQNull>(   parent, buf, name);
    default:
      std::ostringstream ss;
      if (name.size() > 0)
	ss << "Could not create object " << name << ". ";
      ss << "Unknown object type 0x" << std::setfill('0') << std::setw(8) << std::hex << type;
      Error::error(ss.str());
      return nullptr;
    }
}

Nut::SQString::SQString(const Object* parent, std::string name)
  : SQObjectPtr(parent, "SQString", name)
{}

bool	Nut::SQString::readValue(Buffer& buf)
{
  uint32_t	length = buf.readInt();
  const char*	str = (const char*)buf.returnBytes(length);
  if (!str)
    return false;
  this->value = std::string(str, length);
  return true;
}

void	Nut::SQString::print(std::ostream& os) const
{
  os << this->value;
}
