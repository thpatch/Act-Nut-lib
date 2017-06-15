#ifndef BUFFER_HPP_
# define BUFFER_HPP_

# include	<stddef.h>
# include	<stdint.h>

namespace ActNut
{

  class	IBuffer
  {
  public:
    ~IBuffer() {}

    virtual bool		readBytes(uint8_t* out, size_t n) = 0;
    virtual uint8_t		readByte() = 0;
    virtual uint32_t		readInt() = 0;
    virtual bool		checkTag(uint32_t iTag) = 0;
  };

  class	ABuffer : public IBuffer
  {
  public:
    ~ABuffer() {}

    uint8_t		readByte();
    uint32_t		readInt();
    bool		checkTag(uint32_t iTag);
  };

  class	MemoryBuffer : public ABuffer
  {
    uint8_t*	begin;
    uint8_t*	buf;
    uint8_t*	end;

  public:
    // If steal_buffer is true, buf will be used directly instead of being copied.
    // It must be allocated with the new operator, and must not be freed by the caller.
    // This class will take care of freeing it.
    MemoryBuffer(uint8_t* buf, size_t buf_size, bool steal_buffer);
    // If we don't steal the buffer, it can be const.
    MemoryBuffer(const uint8_t* buf, size_t buf_size);
    ~MemoryBuffer();

    bool		readBytes(uint8_t* out, size_t n);
  };



  class	Error
  {
  public:
    enum ErrorMode
      {
	SILENT,
	STDERR,
	EXCEPTION
      };

  private:
    static ErrorMode	errorMode;

  public:
    static void	setErrorMode(ErrorMode newMode);
    static bool	error(std::string msg);
  };
}

#endif /* !BUFFER_HPP_ */
