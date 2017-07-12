#ifndef EXPORTS_HPP_
# define EXPORTS_HPP_

# include	"Utils.hpp"
# include	"act/File.hpp"
# include	"nut/Stream.hpp"

extern "C" {
  namespace ActNut {
    MemoryBuffer*	new_MemoryBuffer(MemoryBuffer::BufferOwnership ownership, uint8_t* buf, size_t buf_size, bool fixed_size);
    void		delete_buffer(IBuffer *obj);
    void		delete_object(Object *obj);
  }
  namespace Act {
    Act::File*	read_act_from_bytes(const uint8_t* buf, size_t buf_size);
  }
  namespace Nut {
    Nut::Stream*	read_nut_from_bytes(const uint8_t* buf, size_t buf_size);
  }
}

#endif /* !EXPORTS_HPP_ */
