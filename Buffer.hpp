#ifndef BUFFER_HPP_
# define BUFFER_HPP_

# include	<stddef.h>
# include	<stdint.h>

class	Buffer
{
public:
  enum ErrorMode
    {
      SILENT,
      STDERR,
      EXCEPTION
    };

private:
  ErrorMode		errorMode;

  const uint8_t*	begin;
  const uint8_t*	buf;
  const uint8_t*	end;

  bool	error(std::string msg);

public:
  Buffer(const uint8_t* buf, size_t buf_size, ErrorMode errorMode = Buffer::SILENT);
  ~Buffer();

  void			setErrorMode(ErrorMode newMode);

  const uint8_t*	returnBytes(size_t n);
  bool			readBytes(uint8_t* out, size_t n);
  uint32_t		readInt();
  bool			checkTag(uint32_t iTag);
};

#endif /* !BUFFER_HPP_ */
