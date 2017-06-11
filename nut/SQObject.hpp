#ifndef NUT_SQOBJECT_HPP_
# define NUT_SQOBJECT_HPP_

# include <iostream>
# include <string>
# include <vector>
# include <Object.hpp>
# include <Utils.hpp>

# define OT_STRING	0x08000010
# define OT_INTEGER	0x05000002
# define OT_BOOL	0x01000008
# define OT_FLOAT	0x05000004
# define OT_NULL	0x01000001

namespace Nut
{

  using ActNut::Buffer;
  using ActNut::Error;
  using ActNut::Object;

  typedef ActNut::Object SQObjectPtr;
  SQObjectPtr*	loadObject(const Object* parent, Buffer& buf, std::string name = "");

  class	SQString : public SQObjectPtr
  {
    std::string	value;

  public:
    SQString(const Object* parent, std::string name = "");

    bool	readValue(Buffer& buf);
    void	print(std::ostream& os) const;
  };

  template<typename T>
  class	SQNumber : public SQObjectPtr
  {
  protected:
    T		n;

  public:
    SQNumber(const Object* parent, const char* type, std::string name)
      : SQObjectPtr(parent, type, name), n(0)
    { }

    bool	readValue(Buffer& buf)
    { return buf.readBytes((uint8_t*)&this->n, sizeof(this->n)); }

    void	print(std::ostream& os) const
    { os << +this->n; }

    operator T() { return this->n; }
  };

  class	SQInteger           : public SQNumber<int>      { public: SQInteger(          const Object* parent, std::string name = "") : SQNumber(parent,    "SQInteger",         name) {}  };
  class	SQUnsignedInteger   : public SQNumber<uint32_t> { public: SQUnsignedInteger(  const Object* parent, std::string name = "") : SQNumber(parent,    "SQUnsignedInteger", name) {}  };
  class	SQBoolean           : public SQNumber<int>      { public: SQBoolean(          const Object* parent, std::string name = "") : SQNumber(parent,    "SQBoolean",         name) {}  };
  // SQBoolean is stored on 4 bytes, we need a custom one to handle single-byte booleans.
  class	SQSingleByteBoolean : public SQNumber<char>     { public: SQSingleByteBoolean(const Object* parent, std::string name = "") : SQNumber(parent,    "bool",              name) {}  };
  class	SQFloat             : public SQNumber<float>    { public: SQFloat(            const Object* parent, std::string name = "") : SQNumber(parent,    "SQFloat",           name) {}  };
  class	SQNull              : public SQObjectPtr        { public: SQNull(             const Object* parent, std::string name = "") : SQObjectPtr(parent, "SQNull",            name) {}
    bool	readValue(Buffer&) { return true; }
    void	print(std::ostream&) const {}
  };

}

#endif /* !NUT_SQOBJECT_HPP_ */
