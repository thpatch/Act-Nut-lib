#include	<fstream>
#include	<nut/Stream.hpp>

Nut::SQFunctionProto*	Nut::readStream(Buffer& buf)
{
  if (buf.readByte() != 0xFA || buf.readByte() != 0xFA)
    {
      Error::error("Wrong stream magic - should be 0xFAFA. You probably don't have a NUT file");
      return nullptr;
    }

  if (!buf.checkTag('SQIR') ||
      !buf.checkTag(1) ||
      !buf.checkTag(4) ||
      !buf.checkTag(4))
    return nullptr;

  SQFunctionProto *func = ActNut::Object::read<SQFunctionProto>(nullptr, buf);
  if (!func)
    return nullptr;

  if (!buf.checkTag('TAIL'))
    return nullptr;
  return func;
}

Nut::SQFunctionProto*	Nut::readStream(const std::string& filename)
{
  std::ifstream	f(filename);
  size_t	len;
  uint8_t*	byteBuf;

  f.seekg(0, std::ios::end);
  len = f.tellg();
  f.seekg(0, std::ios::beg);

  byteBuf = new uint8_t[len];
  f.read((char*)byteBuf, len);
  f.close();

  Buffer	buf(byteBuf, len, true);
  return readStream(buf);
}
