#include	<act/Object.hpp>

Act::Integer::Integer(  const Object* parent, const std::string& name) : Number(        parent, "int",    name) {}
Act::Float::Float(      const Object* parent, const std::string& name) : Number(        parent, "float",  name, DisplayType::FLOAT) {}
Act::Boolean::Boolean(  const Object* parent, const std::string& name) : Number(        parent, "bool",   name, DisplayType::BOOLEAN) {}
Act::Integer5::Integer5(const Object* parent, const std::string& name) : Number(        parent, "int",    name) {}
Act::String::String(    const Object* parent, const std::string& name) : ActNut::String(parent, "string", name) {}

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
