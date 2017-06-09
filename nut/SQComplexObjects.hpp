#ifndef NUT_SQCOMPLEXOBJECTS_HPP_
# define NUT_SQCOMPLEXOBJECTS_HPP_

# include	<nut/SQObject.hpp>

namespace Nut
{

  using ActNut::Buffer;

  class	SQOuterType : public SQNumber<int>
  {
  public:
    SQOuterType(Buffer& buf, std::string name = "") : SQNumber(buf, "SQOuterType", name) {}
    void	print(std::ostream& os) const;
  };

  class	SQOuterVal : public SQObjectPtr
  {
  private:
    SQOuterType*	type;
    SQObjectPtr*	object;
    SQObjectPtr*	name;

  public:
    SQOuterVal(Buffer& buf, std::string name = "");
    ~SQOuterVal();
    void	print(std::ostream& os) const;
  };

  class	SQLocalVarInfo : public SQObjectPtr
  {
  private:
    SQObjectPtr*	name;
    SQUnsignedInteger*	pos;
    SQUnsignedInteger*	start_op;
    SQUnsignedInteger*	end_op;

  public:
    SQLocalVarInfo(Buffer& buf, std::string name = "");
    ~SQLocalVarInfo();
    void	print(std::ostream& os) const;
  };

  class	SQLineInfo : public SQObjectPtr
  {
  private:
    SQInteger*	line;
    SQInteger*	op;

  public:
    SQLineInfo(Buffer& buf, std::string name = "");
    ~SQLineInfo();
    void	print(std::ostream& os) const;
  };

}

#endif /* !NUT_SQCOMPLEXOBJECTS_HPP_ */
