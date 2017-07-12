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
    virtual ~IBuffer() {}

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
  public:
    /*
    ** This enum is a parameter of the MemoryBuffer constructor.
    ** It tells to the MemoryBuffer how the input buffer should be used.
    ** - CREATE: The MemoryBuffer create its own buffer and ignore the buf parameter.
    **           buf_size is the size of the created buffer. It will be filled with 0.
    ** - COPY:   The MemoryBuffer create a copy of the input buffer. The input buffer
    **           will not be used by this class after the constructor is called.
    ** - STEAL:  The MemoryBuffer steals the input buffer.
    **           The input buffer must be allocated with the new[] operator.
    **           After the constructor is called, the input buffer belongs to the
    **           MemoryBuffer and must not be used or freed by the caller.
    ** - SHARE:  The MemoryBuffer writes directly to the input buffer, but doesn't
    **           take ownership of it.
    **           The caller should ensure the input buffer is valid while the
    **           MemoryBuffer object is alive, and it is the caller responsability
    **           to free the buffer.
    */
    enum	BufferOwnership
    {
      CREATE,
      COPY,
      STEAL,
      SHARE
    };

  private:
    BufferOwnership	ownership;
    uint8_t*		begin;
    uint8_t*		buf;
    uint8_t*		end;
    // Variables for writing
    uint8_t*		end_alloc;
    bool		fixed_size;

  public:
    // If fixed_size is false and ownership it not SHARE, when writing bytes after the end of the buffer,
    // the buffer will be dynamically allocated to fit the new bytes. Else, an error will be returned.
    MemoryBuffer(BufferOwnership ownership, uint8_t* buf, size_t buf_size, bool fixed_size);
    // With a COPY ownership, the input buffer can be const.
    MemoryBuffer(const uint8_t* buf, size_t buf_size, bool fixed_size);
    // Create an empty buffer, growing over time.
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
