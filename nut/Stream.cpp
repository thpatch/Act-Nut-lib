#include	<fstream>
#include	"nut/Stream.hpp"

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

  if (!buf.checkTag('SQIR') ||
      !buf.checkTag(1) ||
      !buf.checkTag(4) ||
      !buf.checkTag(4))
    return false;

  if (!this->SQFunctionProto::readValue(buf))
    return false;

  return buf.checkTag('TAIL');
}

bool	Nut::Stream::writeValue(IBuffer& buf) const
{
  buf.writeByte(0xFA);
  buf.writeByte(0xFA);

  buf.writeInt('SQIR');
  buf.writeInt(1);
  buf.writeInt(4);
  buf.writeInt(4);

  if (!this->SQFunctionProto::writeValue(buf))
    return false;

  return buf.writeInt('TAIL');
}

Nut::SQFunctionProto*	Nut::readStream(const std::string& filename)
{
  return ActNut::Object::read<Stream>(filename);
}
