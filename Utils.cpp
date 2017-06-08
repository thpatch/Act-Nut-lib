#include	<stdexcept>
#include	<iostream>
#include	<sstream>
#include	<iomanip>
#include	<string.h>
#include	"Utils.hpp"

ActNut::Buffer::Buffer(const uint8_t* buf, size_t buf_size)
  : begin(buf), buf(buf), end(buf + buf_size)
{}

ActNut::Buffer::~Buffer()
{}

const uint8_t*	ActNut::Buffer::returnBytes(size_t n)
{
  if (this->buf + n > this->end)
    {
      Error::error("Not enough bytes.");
      return nullptr;
    }
  const uint8_t*	ret = this->buf;
  this->buf += n;
  return ret;
}

bool	ActNut::Buffer::readBytes(uint8_t* out, size_t n)
{
  const uint8_t*	in = this->returnBytes(n);
  if (!in)
    return false;
  memcpy(out, in, n);
  return true;
}

uint32_t	ActNut::Buffer::readInt()
{
  uint32_t	n;
  if (!this->readBytes((uint8_t*)&n, 4))
    return 0;
  return n;
}

uint8_t	ActNut::Buffer::readByte()
{
  uint8_t	n;
  if (!this->readBytes(&n, 1))
    return 0;
  return n;
}

bool	ActNut::Buffer::checkTag(uint32_t iTag)
{
  if (this->readInt() != iTag)
    {
      std::ostringstream ss;
      ss << "Wrong tag - should be 0x" << std::setfill('0') << std::setw(8) << std::hex << iTag;
      return Error::error(ss.str());
    }
  return true;
}



ActNut::Error::ErrorMode	ActNut::Error::errorMode = ActNut::Error::SILENT;

bool	ActNut::Error::error(std::string msg)
{
  if (errorMode == Error::EXCEPTION)
    throw std::runtime_error(msg);
  if (errorMode == Error::STDERR)
    std::cerr << msg << std::endl;
  return false;
}

void	ActNut::Error::setErrorMode(ErrorMode newMode)
{
  errorMode = newMode;
}
