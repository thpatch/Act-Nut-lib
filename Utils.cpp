#include	<stdexcept>
#include	<iostream>
#include	<sstream>
#include	<iomanip>
#include	<string.h>
#include	"Utils.hpp"


uint32_t	ActNut::ABuffer::readInt()
{
  uint32_t	n;
  if (!this->readBytes((uint8_t*)&n, 4))
    return 0;
  return n;
}

uint8_t	ActNut::ABuffer::readByte()
{
  uint8_t	n;
  if (!this->readBytes(&n, 1))
    return 0;
  return n;
}

bool	ActNut::ABuffer::checkTag(uint32_t iTag)
{
  if (this->readInt() != iTag)
    {
      std::ostringstream ss;
      ss << "Wrong tag - should be 0x" << std::setfill('0') << std::setw(8) << std::hex << iTag;
      return Error::error(ss.str());
    }
  return true;
}



ActNut::MemoryBuffer::MemoryBuffer(uint8_t* buf, size_t buf_size, bool steal_buffer)
{
  if (steal_buffer == false)
    {
      this->buf = new uint8_t[buf_size];
      memcpy(this->buf, buf, buf_size);
    }
  else
    this->buf = buf;
  this->begin = this->buf;
  this->end = this->buf + buf_size;
}

ActNut::MemoryBuffer::MemoryBuffer(const uint8_t* buf, size_t buf_size)
{
  this->buf = new uint8_t[buf_size];
  memcpy(this->buf, buf, buf_size);
  this->begin = this->buf;
  this->end = this->buf + buf_size;
}

ActNut::MemoryBuffer::~MemoryBuffer()
{
  delete[] this->begin;
}

bool	ActNut::MemoryBuffer::readBytes(uint8_t* out, size_t n)
{
  if (this->buf + n > this->end)
    {
      Error::error("Not enough bytes.");
      return false;
    }
  memcpy(out, this->buf, n);
  this->buf += n;
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
