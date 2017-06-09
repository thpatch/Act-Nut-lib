#include	"ActObject.hpp"

bool	Act::String::readValue(Buffer& buf)
{
  uint32_t	length = buf.readInt();
  const char*	str = (const char*)buf.returnBytes(length);
  if (!str)
    return false;
  this->value = std::string(str, length);
  return true;
}

void	Act::String::print(std::ostream& os) const
{
  os << this->value;
}

bool	Act::Array::readValue(Buffer& buf)
{
  this->nbEntries = buf.readInt();
  return true;
}

bool	Act::Array::readContent(Buffer& buf)
{
  for (uint32_t i = 0; i < this->nbEntries; i++)
    this->entries.push_back(buf.readInt());
  return true;
}

void	Act::Array::print(std::ostream& os) const
{
  os << "[";
  for (auto it = this->entries.begin(); it != this->entries.end(); it++)
    {
      if (it != this->entries.begin())
        os << ", ";
      os << *it;
    }
  os << "]";
}
