#include	<fstream>
#include	<nut/Stream.hpp>

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
  /*
  SQFunctionProto *func = ActNut::Object::read<SQFunctionProto>(parent, buf, name);
  if (!func)
    return nullptr;
  */

  return buf.checkTag('TAIL');
}

Nut::SQFunctionProto*	Nut::readStream(const std::string& filename)
{
  return ActNut::Object::read<Stream>(filename);
}
