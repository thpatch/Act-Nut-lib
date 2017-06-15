#ifndef BUFFER_HPP_
# define BUFFER_HPP_

# include	<fstream>
# include	<stddef.h>
# include	<stdint.h>

namespace ActNut
{

  class	IBuffer
  {
  public:
    ~IBuffer() {}

    virtual bool	readBytes(uint8_t* out, size_t n) = 0;
    virtual uint8_t	readByte() = 0;
    virtual uint32_t	readInt() = 0;
    virtual bool	checkTag(uint32_t iTag) = 0;
    virtual bool	writeBytes(const uint8_t* in, size_t n) = 0;
    virtual bool	writeByte(uint8_t n) = 0;
    virtual bool	writeInt(uint32_t n) = 0;
  };

  class	ABuffer : public IBuffer
  {
  public:
    ~ABuffer() {}

    uint8_t		readByte();
    uint32_t		readInt();
    bool		checkTag(uint32_t iTag);
    bool		writeByte(uint8_t n);
    bool		writeInt(uint32_t n);
  };

  class	MemoryBuffer : public ABuffer
  {
    uint8_t*	begin;
    uint8_t*	buf;
    uint8_t*	end;
    // Variables for writing
    uint8_t*	end_alloc;
    bool	fixed_size;

  public:
    // If steal_buffer is true, buf will be used directly instead of being copied.
    // It must be allocated with the new operator, and must not be freed by the caller.
    // This class will take care of freeing it.

    // If fixed_size is false, when writing bytes after the end of the buffer, the buffer will be dynamically
    // allocated to fit the new bytes. Else, an error will be returned.
    MemoryBuffer(uint8_t* buf, size_t buf_size, bool steal_buffer, bool fixed_size = false);
    // If we don't steal the buffer, it can be const.
    MemoryBuffer(const uint8_t* buf, size_t buf_size, bool fixed_size = false);
    // Use an empty buffer, growing over time.
    MemoryBuffer();
    ~MemoryBuffer();

    bool		readBytes(uint8_t* out, size_t n);
    bool		writeBytes(const uint8_t* in, size_t n);
    const uint8_t*	getBuffer() const;
    size_t		getSize() const;
  };

  class	FileBuffer : public ABuffer
  {
    std::fstream	fs;

  public:
    FileBuffer(std::fstream&& fs);
    FileBuffer(const std::string& filename, std::ios_base::openmode mode);
    ~FileBuffer();

    bool		readBytes(uint8_t* out, size_t n);
    bool		writeBytes(const uint8_t* in, size_t n);
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
