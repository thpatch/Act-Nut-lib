#ifndef SQOBJECT_HPP_
# define SQOBJECT_HPP_

# include <iostream>
# include <string>
# include <vector>
# include "utils.hpp"

# define OT_STRING	0x08000010
# define OT_INTEGER	0x05000002
# define OT_BOOL	0x01000008
# define OT_FLOAT	0x05000004
# define OT_NULL	0x01000001

class	SQObjectPtr
{
private:
  std::string	type;
  std::string	name;
protected:
  std::string	printIndent(bool printName = true) const;

public:
  static int	indentLevel;

  SQObjectPtr(std::string type, std::string name) : type(type), name(name) {}
  virtual ~SQObjectPtr() {}
  static SQObjectPtr*	Load(const uint8_t*& buf, std::string name = "");

  virtual void	print(std::ostream& os) const = 0;
};
std::ostream& operator<<(std::ostream& os, const SQObjectPtr& o);
// Using SFINAE to make the template detection fail if the vector doesn't contain SQObjectPtr derivates.
template<typename T, int n = sizeof(T::indentLevel)>
std::ostream& operator<<(std::ostream& os, const std::vector<T*> v)
{
  SQObjectPtr::indentLevel += 2;
  for (SQObjectPtr* it : v)
    os << *it << std::endl;
  SQObjectPtr::indentLevel -= 2;
  return os;
}

class	SQString : public SQObjectPtr
{
  char*		s;
  uint32_t	len;
public:
  SQString(const uint8_t*& buf, std::string name = "");
  ~SQString();
  void	print(std::ostream& os) const;
};

template<typename T>
class	SQNumber : public SQObjectPtr
{
protected:
  T		n;

public:
  SQNumber(const uint8_t*& buf, std::string type, std::string name)
    : SQObjectPtr(type, name)
  { readBytes(buf, (uint8_t*)&this->n, sizeof(this->n)); }

  void	print(std::ostream& os) const
  { os << printIndent() << +this->n; }
};

class	SQInteger : public SQNumber<int>
{
public:
  SQInteger(const uint8_t*& buf, std::string name = "") : SQNumber(buf, "SQInteger", name) {}
  operator int() { return this->n; }
};

class	SQUnsignedInteger : public SQNumber<uint32_t>
{
public:
  SQUnsignedInteger(const uint8_t*& buf, std::string name = "") : SQNumber(buf, "SQUnsignedInteger", name) {}
};

class	SQBoolean : public SQNumber<int>
{
public:
  SQBoolean(const uint8_t*& buf, std::string name = "") : SQNumber(buf, "SQBoolean", name) {}
};

// SQBoolean is stored on 4 bytes, we need a custom one to handle single-byte booleans.
class	SQSingleByteBoolean : public SQNumber<char>
{
public:
  SQSingleByteBoolean(const uint8_t*& buf, std::string name = "") : SQNumber(buf, "bool", name) {}
};

class	SQFloat : public SQNumber<float>
{
public:
  SQFloat(const uint8_t*& buf, std::string name = "") : SQNumber(buf, "SQFloat", name) {}
};

class	SQNull : public SQObjectPtr
{
public:
  SQNull(std::string name = "") : SQObjectPtr("SQNull", name) {}
  void	print(std::ostream& os) const;
};

#endif /* !SQOBJECT_HPP_ */
