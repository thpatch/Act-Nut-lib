#include	"exports.hpp"

Act::File*	read_act_from_bytes(const uint8_t* buf, size_t buf_size)
{
  ActNut::MemoryBuffer	mbuf(buf, buf_size, true);
  return ActNut::Object::read<Act::File>(nullptr, mbuf, "");
}

Nut::Stream*	read_nut_from_bytes(const uint8_t* buf, size_t buf_size)
{
  ActNut::MemoryBuffer	mbuf(buf, buf_size, true);
  return ActNut::Object::read<Nut::Stream>(nullptr, mbuf, "");
}
