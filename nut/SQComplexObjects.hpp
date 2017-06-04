#ifndef SQCOMPLEXOBJECTS_HPP_
# define SQCOMPLEXOBJECTS_HPP_

# include	"SQObject.hpp"

class	SQOuterType : public SQNumber<int>
{
public:
  SQOuterType(const uint8_t*& buf, std::string name = "") : SQNumber(buf, "SQOuterType", name) {}
  void	print(std::ostream& os) const;
};

class	SQOuterVal : public SQObjectPtr
{
private:
  SQOuterType*	type;
  SQObjectPtr*	object;
  SQObjectPtr*	name;

public:
  SQOuterVal(const uint8_t*& buf, std::string name = "");
  ~SQOuterVal();
  void	print(std::ostream& os) const;
};

class	SQLocalVarInfo : public SQObjectPtr
{
private:
  SQObjectPtr*		name;
  SQUnsignedInteger*	pos;
  SQUnsignedInteger*	start_op;
  SQUnsignedInteger*	end_op;

public:
  SQLocalVarInfo(const uint8_t*& buf, std::string name = "");
  ~SQLocalVarInfo();
  void	print(std::ostream& os) const;
};

class	SQLineInfo : public SQObjectPtr
{
private:
  SQInteger*	line;
  SQInteger*	op;

public:
  SQLineInfo(const uint8_t*& buf, std::string name = "");
  ~SQLineInfo();
  void	print(std::ostream& os) const;
};

#endif /* !SQCOMPLEXOBJECTS_HPP_ */
