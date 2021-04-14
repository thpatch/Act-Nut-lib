#ifndef NUT_SQCOMPLEXOBJECTS_HPP_
# define NUT_SQCOMPLEXOBJECTS_HPP_

# include	"nut/SQObject.hpp"

namespace Nut
{

  using ActNut::IBuffer;

  // The SQOuterType size isn't actually defined, it's just whichever size the compiler
  // decided to use for this enum.
  class	SQOuterType : public ActNut::Number<SQint_t>
  {
  public:
    SQOuterType(const Object* parent, const std::string& name);
    void	print(std::ostream& os) const;
  };

  class	SQOuterVal : public SQObjectPtr
  {
  private:
    SQOuterType*	type;
    SQObjectPtr*	object;
    SQObjectPtr*	name;

  public:
    SQOuterVal(const Object* parent, const std::string& name);
    ~SQOuterVal();
    bool	readValue(IBuffer& buf);
    void	print(std::ostream& os) const;
    bool	writeValue(IBuffer& buf) const;
  };

  class	SQLocalVarInfo : public SQObjectPtr
  {
  private:
    SQObjectPtr*	name;
    SQUnsignedInteger*	pos;
    SQUnsignedInteger*	start_op;
    SQUnsignedInteger*	end_op;

  public:
    SQLocalVarInfo(const Object* parent, const std::string& name);
    ~SQLocalVarInfo();
    bool	readValue(IBuffer& buf);
    void	print(std::ostream& os) const;
    bool	writeValue(IBuffer& buf) const;

    void        updateForNewInstruction(size_t newInstructionOffset);
  };

  class	SQLineInfo : public SQObjectPtr
  {
  private:
    SQInteger*	line;
    SQInteger*	op;

  public:
    SQLineInfo(const Object* parent, const std::string& name);
    ~SQLineInfo();
    bool	readValue(IBuffer& buf);
    void	print(std::ostream& os) const;
    bool	writeValue(IBuffer& buf) const;
  };

}

#endif /* !NUT_SQCOMPLEXOBJECTS_HPP_ */
