#ifndef SQFUNCTIONPROTO_HPP_
# define SQFUNCTIONPROTO_HPP

# include	<vector>
# include	"SQObject.hpp"
# include	"SQComplexObjects.hpp"
# include	"SQInstruction.hpp"

class	SQFunctionProto : public SQObjectPtr
{
private:
  // PART
  SQObjectPtr*	sourcename;
  SQObjectPtr*	name;
  // PART
  SQInteger*	nliterals;
  SQInteger*	nparameters;
  SQInteger*	noutervals;
  SQInteger*	nlocalvarinfos;
  SQInteger*	nlineinfos;
  SQInteger*	ndefaultparams;
  SQInteger*	ninstructions;
  SQInteger*	nfunctions;

  // For this block, there is a PART before each variable.
  std::vector<SQObjectPtr*>	literals;
  std::vector<SQObjectPtr*>	parameters;
  std::vector<SQOuterVal*>	outerValues;
  std::vector<SQLocalVarInfo*>	localVarInfos;
  std::vector<SQLineInfo*>	lineInfos;
  std::vector<SQInteger*>	defaultParams;
  std::vector<SQInstruction*>	instructions;
  std::vector<SQFunctionProto*>	functions;

  SQInteger*		stacksize;
  SQSingleByteBoolean*	bgenerator;
  SQInteger*		varparams;

public:
  SQFunctionProto(const uint8_t*& buf, std::string name = "");
  ~SQFunctionProto();
  void	print(std::ostream& os) const;

  const SQObjectPtr*	getLiteral(int idx) const;
};

#endif /* !SQFUNCTIONPROTO_HPP_ */
