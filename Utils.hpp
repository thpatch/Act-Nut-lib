#ifndef BUFFER_HPP_
# define BUFFER_HPP_

# include	<stddef.h>
# include	<stdint.h>

namespace ActNut
{

  class	Buffer
  {
    uint8_t*	begin;
    uint8_t*	buf;
    uint8_t*	end;

  public:
    // If steal_buffer is true, buf will be used directly instead of being copied.
    // It must be allocated with the new operator, and must not be freed by the caller.
    // This class will take care of freeing it.
    Buffer(uint8_t* buf, size_t buf_size, bool steal_buffer);
    // If we don't steal the buffer, it can be const.
    Buffer(const uint8_t* buf, size_t buf_size);
    ~Buffer();

    const uint8_t*	returnBytes(size_t n);
    bool		readBytes(uint8_t* out, size_t n);
    uint8_t		readByte();
    uint32_t		readInt();
    bool		checkTag(uint32_t iTag);
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
