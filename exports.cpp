#include	"exports.hpp"

ActNut::MemoryBuffer*	ActNut::new_MemoryBuffer(MemoryBuffer::BufferOwnership ownership, uint8_t* buf, size_t buf_size, bool fixed_size)
{
  return new MemoryBuffer(ownership, buf, buf_size, fixed_size);
}

void	ActNut::delete_buffer(IBuffer *obj)
{
  delete obj;
}

void	ActNut::delete_object(Object *obj)
{
  delete obj;
}

Act::File*	Act::read_act_from_bytes(const uint8_t* buf, size_t buf_size)
{
  ActNut::MemoryBuffer	mbuf(buf, buf_size, true);
  return ActNut::Object::read<Act::File>(nullptr, mbuf, "");
}

Nut::Stream*	Nut::read_nut_from_bytes(const uint8_t* buf, size_t buf_size)
{
  ActNut::MemoryBuffer	mbuf(buf, buf_size, true);
  return ActNut::Object::read<Nut::Stream>(nullptr, mbuf, "");
}
