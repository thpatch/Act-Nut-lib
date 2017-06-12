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
  using ActNut::Number;

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

  class	SQInteger           : public Number<int>      { public: SQInteger(          const Object* parent, std::string name = "") : Number(parent,      "SQInteger",         name) {}  };
  class	SQUnsignedInteger   : public Number<uint32_t> { public: SQUnsignedInteger(  const Object* parent, std::string name = "") : Number(parent,      "SQUnsignedInteger", name) {}  };
  class	SQBoolean           : public Number<int>      { public: SQBoolean(          const Object* parent, std::string name = "") : Number(parent,      "SQBoolean",         name, Number::DisplayType::BOOLEAN) {}  };
  // SQBoolean is stored on 4 bytes, we need a custom one to handle single-byte booleans.
  class	SQSingleByteBoolean : public Number<char>     { public: SQSingleByteBoolean(const Object* parent, std::string name = "") : Number(parent,      "bool",              name, Number::DisplayType::BOOLEAN) {}  };
  class	SQFloat             : public Number<float>    { public: SQFloat(            const Object* parent, std::string name = "") : Number(parent,      "SQFloat",           name, Number::DisplayType::FLOAT) {}  };
  class	SQNull              : public SQObjectPtr      { public: SQNull(             const Object* parent, std::string name = "") : SQObjectPtr(parent, "SQNull",            name) {}
    bool	readValue(Buffer&) { return true; }
    void	print(std::ostream&) const {}
  };

}

#endif /* !NUT_SQOBJECT_HPP_ */
