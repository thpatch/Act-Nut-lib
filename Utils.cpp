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

bool	ActNut::ABuffer::writeInt(uint32_t n)
{
  return this->writeBytes((uint8_t*)&n, 4);
}

bool	ActNut::ABuffer::writeByte(uint8_t n)
{
  return this->writeBytes(&n, 1);
}



ActNut::MemoryBuffer::MemoryBuffer(BufferOwnership ownership, uint8_t* buf, size_t buf_size, bool fixed_size)
  : ownership(ownership), fixed_size(fixed_size)
{
  switch (ownership)
    {
    case CREATE:
      if (buf_size == 0)
	buf_size = 1024;
      this->buf = new uint8_t[buf_size];
      memset(this->buf, 0, buf_size);
      this->begin = this->buf;
      this->end = this->buf;
      this->end_alloc = this->end + buf_size;
      return ;

    case COPY:
      this->buf = new uint8_t[buf_size];
      memcpy(this->buf, buf, buf_size);
      break ;

    case STEAL:
    case SHARE:
      this->buf = buf;
      break ;
    }

  this->begin = this->buf;
  this->end = this->buf + buf_size;
  this->end_alloc = this->end;
}

ActNut::MemoryBuffer::MemoryBuffer(const uint8_t* buf, size_t buf_size, bool fixed_size)
  : ownership(COPY), fixed_size(fixed_size)
{
  this->buf = new uint8_t[buf_size];
  memcpy(this->buf, buf, buf_size);
  this->begin = this->buf;
  this->end = this->buf + buf_size;
  this->end_alloc = this->end;
}

ActNut::MemoryBuffer::MemoryBuffer()
  : MemoryBuffer(CREATE, nullptr, 0, false)
{}

ActNut::MemoryBuffer::~MemoryBuffer()
{
  if (this->ownership != SHARE)
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

bool	ActNut::MemoryBuffer::writeBytes(const uint8_t* in, size_t n)
{
  if (this->buf + n > this->end_alloc)
    {
      if (fixed_size == false)
	{
	  uint8_t*	new_buf = new uint8_t[this->end_alloc - this->begin + n + 1024];
	  memcpy(new_buf, this->begin, this->end - this->begin);
	  this->buf = this->buf - this->begin + new_buf;
	  this->end = this->end - this->begin + new_buf;
	  this->end_alloc = new_buf + (this->end_alloc - this->begin + n + 1024);
	  this->begin = new_buf;
	}
      else
	{
	  Error::error("Not enough bytes.");
	  return false;
	}
    }
  memcpy(this->buf, in, n);
  this->buf += n;
  if (this->buf > this->end)
    this->end = this->buf;
  return true;
}

const uint8_t*	ActNut::MemoryBuffer::getBuffer() const
{
  return this->begin;
}

size_t	ActNut::MemoryBuffer::getSize() const
{
  return this->end - this->begin;
}



ActNut::FileBuffer::FileBuffer(std::fstream&& fs)
  : fs(std::move(fs))
{}

ActNut::FileBuffer::FileBuffer(const std::string& filename, std::ios_base::openmode mode)
  : fs(filename.c_str(), mode)
{}

ActNut::FileBuffer::~FileBuffer()
{}

bool	ActNut::FileBuffer::readBytes(uint8_t* out, size_t n)
{
  this->fs.read((char*)out, n);
  return (bool)fs;
}

bool	ActNut::FileBuffer::writeBytes(const uint8_t* in, size_t n)
{
  this->fs.write((const char*)in, n);
  return (bool)fs;
}



ActNut::Error::ErrorMode	ActNut::Error::errorMode = ActNut::Error::SILENT;
ActNut::Error::Callback		ActNut::Error::callback = nullptr;

bool	ActNut::Error::error(std::string msg)
{
  if (callback)
    callback(msg.c_str());
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

void	ActNut::Error::setErrorCallback(Callback callback)
{
  Error::callback = callback;
}
