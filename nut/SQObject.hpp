#ifndef NUT_SQOBJECT_HPP_
# define NUT_SQOBJECT_HPP_

# include <iostream>
# include <string>
# include <vector>
# include "../Object.hpp"
# include "../Utils.hpp"

# define OT_STRING	0x08000010
# define OT_INTEGER	0x05000002
# define OT_BOOL	0x01000008
# define OT_FLOAT	0x05000004
# define OT_NULL	0x01000001

#ifdef SQ_INT64
typedef int64_t  SQint_t;
typedef uint64_t SQuint_t;
#else
typedef int32_t  SQint_t;
typedef uint32_t SQuint_t;
#endif

#ifdef SQ_DOUBLE
typedef double   SQfloat_t;
#else
typedef float    SQfloat_t;
#endif

namespace Nut
{

  using ActNut::IBuffer;
  using ActNut::Error;
  using ActNut::Object;

  typedef ActNut::Object SQObjectPtr;
  SQObjectPtr*	loadObject(const Object* parent, IBuffer& buf, const std::string& name);
  bool		writeObject(IBuffer& buf, const Object* obj);

  class	SQInteger           : public ActNut::Number<SQint_t>   { public: SQInteger(          const Object* parent, const std::string& name); using Number::operator=; };
  class	SQUnsignedInteger   : public ActNut::Number<SQuint_t>  { public: SQUnsignedInteger(  const Object* parent, const std::string& name); using Number::operator=; };
  class	SQBoolean           : public ActNut::Number<SQuint_t>  { public: SQBoolean(          const Object* parent, const std::string& name); using Number::operator=; };
  // SQBoolean is stored on 4 or 8 bytes, we need a custom one to handle single-byte booleans.
  class	SQSingleByteBoolean : public ActNut::Number<char>      { public: SQSingleByteBoolean(const Object* parent, const std::string& name); using Number::operator=; };
  class	SQFloat             : public ActNut::Number<SQfloat_t> { public: SQFloat(            const Object* parent, const std::string& name); using Number::operator=; };
  class	SQString            : public ActNut::String            { public: SQString(           const Object* parent, const std::string& name);
    uint32_t	getNumType() const;
    bool		readValue(IBuffer& buf);
    bool		writeValue(IBuffer& buf) const;
  };
  class	SQNull              : public SQObjectPtr               { public: SQNull(             const Object* parent, const std::string& name);
    uint32_t	getNumType() const;
    bool	readValue(IBuffer&);
    void	print(std::ostream&) const;
    bool	writeValue(IBuffer&) const;
  };

}

#endif /* !NUT_SQOBJECT_HPP_ */
