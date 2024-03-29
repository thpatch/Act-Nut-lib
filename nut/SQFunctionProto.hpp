#ifndef NUT_SQFUNCTIONPROTO_HPP_
# define NUT_SQFUNCTIONPROTO_HPP_

# include	<vector>
# include	"nut/SQObject.hpp"
# include	"nut/SQComplexObjects.hpp"
# include	"nut/SQInstruction.hpp"

namespace Nut
{

  using ActNut::IBuffer;
  using ActNut::vector;

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
    vector		literals;	// SQObjectPtr
    vector		parameters;	// SQObjectPtr
    vector		outerValues;	// SQOuterVar
    vector		localVarInfos;	// SQLocalVarInfo
    vector		lineInfos;	// SQLineInfo
    vector		defaultParams;	// SQInteger
    vector		instructions;	// SQInstruction
    vector		functions;	// SQFunctionProto

    SQInteger*			stacksize;
    SQSingleByteBoolean*	bgenerator;
    SQInteger*			varparams;

    template<typename T>
    void	readArray(T* (*readerFunc)(const Object* parent, IBuffer& buf, const std::string& name), IBuffer& buf, vector& array, const SQInteger* size)
    {
      buf.checkTag('PART', "PART tag");
      for (int i = 0; i < *size; i++)
	array.add(readerFunc, buf);
    }
    bool	writeArray(IBuffer& buf, const vector& array) const;
    bool	writeArrayOfObjects(IBuffer& buf, const vector& array) const;

  public:
    SQFunctionProto(const Object* parent, const std::string& name);
    ~SQFunctionProto();
	SQFunctionProto& operator=(const SQFunctionProto&);
	using	ActNut::Object::operator=;
    bool	readValue(IBuffer& buf);
    void	print(std::ostream& os) const;
    bool	writeValue(IBuffer& buf) const;

    const Object*	getLiteral(int idx) const;
    int			getLiteralIdx(const std::string& value) const;

    virtual void	addLiteral(const std::string& literal);
    virtual void	insertInstruction(size_t position, const std::string& instruction);
  };

}

#endif /* !NUT_SQFUNCTIONPROTO_HPP_ */
