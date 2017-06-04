#include	<stdexcept>
#include	<iostream>
#include	<sstream>
#include	<iomanip>
#include	<string.h>
#include	"Buffer.hpp"

Buffer::Buffer(const uint8_t* buf, size_t buf_size, ErrorMode errorMode)
  : errorMode(errorMode), begin(buf), buf(buf), end(buf + buf_size)
{}

Buffer::~Buffer()
{}

bool	Buffer::error(std::string msg)
{
  if (this->errorMode == Buffer::EXCEPTION)
    throw std::runtime_error(msg);
  if (this->errorMode == STDERR)
    std::cerr << "Buffer error: " << msg << std::endl;
  return false;
}

void	Buffer::setErrorMode(ErrorMode newMode)
{
  this->errorMode = newMode;
}

const uint8_t*	Buffer::returnBytes(size_t n)
{
  if (this->buf + n > this->end)
    {
      this->error("Not enough bytes.");
      return nullptr;
    }
  const uint8_t*	ret = this->buf;
  this->buf += n;
  return ret;
}

bool	Buffer::readBytes(uint8_t* out, size_t n)
{
  const uint8_t*	in = this->returnBytes(n);
  if (!in)
    return false;
  memcpy(out, in, n);
  return true;
}

uint32_t	Buffer::readInt()
{
  uint32_t	n;
  if (!this->readBytes((uint8_t*)&n, 4))
    return 0;
  return n;
}

bool	Buffer::checkTag(uint32_t iTag)
{
  if (this->readInt() != iTag)
    {
      std::ostringstream ss;
      ss << "Wrong tag - should be 0x" << std::setfill('0') << std::setw(8) << std::hex << iTag;
      return this->error(ss.str());
    }
  return true;
}
