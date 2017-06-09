#ifndef NUT_SQFUNCTIONPROTO_HPP_
# define NUT_SQFUNCTIONPROTO_HPP_

# include	<vector>
# include	<nut/SQObject.hpp>
# include	<nut/SQComplexObjects.hpp>
# include	<nut/SQInstruction.hpp>

namespace Nut
{

  using ActNut::Buffer;

  class	SQFunctionProto : public SQObjectPtr
  {
  private:
    // PART
    SQObjectPtr*	sourcename;
    SQObjectPtr*	name;
    // PART
    SQInteger*		nliterals;
    SQInteger*		nparameters;
    SQInteger*		noutervals;
    SQInteger*		nlocalvarinfos;
    SQInteger*		nlineinfos;
    SQInteger*		ndefaultparams;
    SQInteger*		ninstructions;
    SQInteger*		nfunctions;

    // For this block, there is a PART before each variable.
    std::vector<SQObjectPtr*>		literals;
    std::vector<SQObjectPtr*>		parameters;
    std::vector<SQOuterVal*>		outerValues;
    std::vector<SQLocalVarInfo*>	localVarInfos;
    std::vector<SQLineInfo*>		lineInfos;
    std::vector<SQInteger*>		defaultParams;
    std::vector<SQInstruction*>		instructions;
    std::vector<SQFunctionProto*>	functions;

    SQInteger*			stacksize;
    SQSingleByteBoolean*	bgenerator;
    SQInteger*			varparams;

  public:
    SQFunctionProto(Buffer& buf, std::string name = "");
    ~SQFunctionProto();
    void	print(std::ostream& os) const;

    const SQObjectPtr*	getLiteral(int idx) const;
  };

}

#endif /* !NUT_SQFUNCTIONPROTO_HPP_ */
