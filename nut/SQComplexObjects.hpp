#ifndef NUT_SQCOMPLEXOBJECTS_HPP_
# define NUT_SQCOMPLEXOBJECTS_HPP_

# include	<nut/SQObject.hpp>

namespace Nut
{

  using ActNut::Buffer;

  class	SQOuterType : public Number<int>
  {
  public:
    SQOuterType(const Object* parent, std::string name = "") : Number(parent, "SQOuterType", name) {}
    void	print(std::ostream& os) const;
  };

  class	SQOuterVal : public SQObjectPtr
  {
  private:
    SQOuterType*	type;
    SQObjectPtr*	object;
    SQObjectPtr*	name;

  public:
    SQOuterVal(const Object* parent, std::string name = "");
    ~SQOuterVal();
    bool	readValue(Buffer& buf);
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
    SQLocalVarInfo(const Object* parent, std::string name = "");
    ~SQLocalVarInfo();
    bool	readValue(Buffer& buf);
    void	print(std::ostream& os) const;
  };

  class	SQLineInfo : public SQObjectPtr
  {
  private:
    SQInteger*	line;
    SQInteger*	op;

  public:
    SQLineInfo(const Object* parent, std::string name = "");
    ~SQLineInfo();
    bool	readValue(Buffer& buf);
    void	print(std::ostream& os) const;
  };

}

#endif /* !NUT_SQCOMPLEXOBJECTS_HPP_ */
