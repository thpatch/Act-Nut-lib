#include	<act/Object.hpp>

Act::Integer::Integer(  const Object* parent, const std::string& name) : Number(        parent, "int",    name, 0) {}
Act::Float::Float(      const Object* parent, const std::string& name) : Number(        parent, "float",  name, 1, DisplayType::FLOAT) {}
Act::Boolean::Boolean(  const Object* parent, const std::string& name) : Number(        parent, "bool",   name, 2, DisplayType::BOOLEAN) {}
Act::Integer5::Integer5(const Object* parent, const std::string& name) : Number(        parent, "int",    name, 5) {}
Act::String::String(    const Object* parent, const std::string& name) : ActNut::String(parent, "string", name) {}

uint32_t	Act::String::getNumType() const
{
  return 3;
}

uint32_t	Act::Array::getNumType() const
{
  return 5;
}

bool	Act::Array::readValue(IBuffer& buf)
{
  this->nbEntries = buf.readInt();
  return true;
}

bool	Act::Array::readContent(IBuffer& buf)
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

bool	Act::Array::writeValue(IBuffer& buf) const
{
  return buf.writeInt(this->nbEntries);
}

bool	Act::Array::writeContent(IBuffer& buf) const
{
  for (uint32_t i : this->entries)
    if (!buf.writeInt(i))
      return false;
  return true;
}
