#include	<sstream>
#include	<iomanip>
#include	<string.h>
#include	<nut/SQObject.hpp>

Nut::SQObjectPtr*	Nut::loadObject(const Object* parent, IBuffer& buf, const std::string& name)
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

bool	Nut::writeObject(IBuffer& buf, const Object* obj)
{
  buf.writeInt(obj->getNumType());
  return obj->writeValue(buf);
}

Nut::SQInteger::SQInteger(                    const Object* parent, const std::string& name) : Number(parent,      "SQInteger",         name, OT_INTEGER) {}
Nut::SQUnsignedInteger::SQUnsignedInteger(    const Object* parent, const std::string& name) : Number(parent,      "SQUnsignedInteger", name, 0xFFFFFFFF) {}
Nut::SQBoolean::SQBoolean(                    const Object* parent, const std::string& name) : Number(parent,      "SQBoolean",         name, OT_BOOL,    Number::DisplayType::BOOLEAN) {}
Nut::SQSingleByteBoolean::SQSingleByteBoolean(const Object* parent, const std::string& name) : Number(parent,      "bool",              name, 0xFFFFFFFF, Number::DisplayType::BOOLEAN) {}
Nut::SQFloat::SQFloat(                        const Object* parent, const std::string& name) : Number(parent,      "SQFloat",           name, OT_FLOAT,   Number::DisplayType::FLOAT) {}
Nut::SQString::SQString(                      const Object* parent, const std::string& name) : String(parent,      "SQString",          name) {}
Nut::SQNull::SQNull(                          const Object* parent, const std::string& name) : SQObjectPtr(parent, "SQNull",            name) {}

uint32_t	Nut::SQString::getNumType() const { return OT_STRING; }
uint32_t	Nut::SQNull::getNumType() const { return OT_NULL; }
bool		Nut::SQNull::readValue(IBuffer&) { return true; }
void		Nut::SQNull::print(std::ostream&) const {}
bool		Nut::SQNull::writeValue(IBuffer&) const { return true; }
