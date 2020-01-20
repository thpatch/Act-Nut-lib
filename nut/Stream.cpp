#include	<fstream>
#include	"nut/Stream.hpp"
#include	"nut/SQObject.hpp"

static_assert(sizeof(SQint_t) == sizeof(SQuint_t), "Size of SQint_t and SQuint_t must be identical");

Nut::Stream::Stream(const Object* parent, const std::string& name)
  : SQFunctionProto(parent, name)
{}

bool	Nut::Stream::readValue(IBuffer& buf)
{
  if (buf.readByte() != 0xFA || buf.readByte() != 0xFA)
    {
      Error::error("Wrong stream magic - should be 0xFAFA. You probably don't have a NUT file");
      return false;
    }

  if (!buf.checkTag('SQIR', "SQIR tag") ||
      !buf.checkTag(sizeof(char),      "SQChar size") ||
      !buf.checkTag(sizeof(SQint_t),   "SQInt size") ||
      !buf.checkTag(sizeof(SQfloat_t), "SQFloat size"))
    return false;

  if (!this->SQFunctionProto::readValue(buf))
    return false;

  return buf.checkTag('TAIL', "TAIL tag");
}

bool	Nut::Stream::writeValue(IBuffer& buf) const
{
  buf.writeByte(0xFA);
  buf.writeByte(0xFA);

  buf.writeInt('SQIR');
  buf.writeInt(sizeof(char));
  buf.writeInt(sizeof(SQint_t));
  buf.writeInt(sizeof(SQfloat_t));

  if (!this->SQFunctionProto::writeValue(buf))
    return false;

  return buf.writeInt('TAIL');
}

Nut::SQFunctionProto*	Nut::readStream(const std::string& filename)
{
  return ActNut::Object::read<Stream>(filename);
}
