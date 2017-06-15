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

  using ActNut::IBuffer;
  using ActNut::Error;
  using ActNut::Object;

  typedef ActNut::Object SQObjectPtr;
  SQObjectPtr*	loadObject(const Object* parent, IBuffer& buf, const std::string& name);

  class	SQInteger           : public ActNut::Number<int>      { public: SQInteger(          const Object* parent, const std::string& name); };
  class	SQUnsignedInteger   : public ActNut::Number<uint32_t> { public: SQUnsignedInteger(  const Object* parent, const std::string& name); };
  class	SQBoolean           : public ActNut::Number<int>      { public: SQBoolean(          const Object* parent, const std::string& name); };
  // SQBoolean is stored on 4 bytes, we need a custom one to handle single-byte booleans.
  class	SQSingleByteBoolean : public ActNut::Number<char>     { public: SQSingleByteBoolean(const Object* parent, const std::string& name); };
  class	SQFloat             : public ActNut::Number<float>    { public: SQFloat(            const Object* parent, const std::string& name); };
  class	SQString            : public ActNut::String           { public: SQString(           const Object* parent, const std::string& name); };
  class	SQNull              : public SQObjectPtr              { public: SQNull(             const Object* parent, const std::string& name);
    bool	readValue(IBuffer&);
    void	print(std::ostream&) const;
  };

}

#endif /* !NUT_SQOBJECT_HPP_ */
