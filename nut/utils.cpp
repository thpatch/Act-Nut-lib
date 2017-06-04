#include	<stdexcept>
#include	<sstream>
#include	<iomanip>
#include	<string.h>
#include	"utils.hpp"

void	readBytes(const uint8_t*& buf, uint8_t* out, int n)
{
  memcpy(out, buf, n);
  buf += n;
}

uint32_t	readInt(const uint8_t*& buf)
{
  uint32_t	n;
  readBytes(buf, (uint8_t*)&n, 4);
  return n;
}

void	checkTag(const uint8_t*& buf, uint32_t iTag)
{
  if (readInt(buf) != iTag)
    {
      std::ostringstream ss;
      ss << "Wrong tag - should be 0x" << std::setfill('0') << std::setw(8) << std::hex << iTag;
      throw std::runtime_error(ss.str());
    }
}
