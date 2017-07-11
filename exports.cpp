#include	<exports.hpp>

Act::File*	read_act_from_bytes(const uint8_t* buf, size_t buf_size)
{
  return ActNut::Object::read<Act::File>(nullptr, ActNut::MemoryBuffer(buf, buf_size, true), "");
}

Nut::Stream*	read_nut_from_bytes(const uint8_t* buf, size_t buf_size)
{
  return ActNut::Object::read<Nut::Stream>(nullptr, ActNut::MemoryBuffer(buf, buf_size, true), "");
}
