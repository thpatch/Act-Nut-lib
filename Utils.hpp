#ifndef BUFFER_HPP_
# define BUFFER_HPP_

# include	<stddef.h>
# include	<stdint.h>

namespace ActNut
{

  class	Buffer
  {
    const uint8_t*	begin;
    const uint8_t*	buf;
    const uint8_t*	end;

  public:
    Buffer(const uint8_t* buf, size_t buf_size);
    ~Buffer();

    const uint8_t*	returnBytes(size_t n);
    bool		readBytes(uint8_t* out, size_t n);
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
