#ifndef NUT_SQINSTRUCTIONS_HPP_
# define NUT_SQINSTRUCTIONS_HPP_

# include	"nut/SQObject.hpp"

namespace Nut
{

  using ActNut::IBuffer;

  class	SQFunctionProto;

  class	SQInstruction : public SQObjectPtr
  {
    class OpWrapper : public ActNut::Number<uint8_t>
    {
    public:
      OpWrapper(const Object* parent, const std::string& name, uint8_t& ref);
      const Object&	operator=(const std::string& new_value);
    };

  private:
    const SQFunctionProto&	func;
    int32_t	arg1;
    uint8_t	op;
    uint8_t	arg0;
    uint8_t	arg2;
    uint8_t	arg3;

    // For operator= support
    OpWrapper			opWrapper;
    ActNut::Number<uint8_t>	arg0Wrapper;
    ActNut::Number<int32_t>	arg1Wrapper;
    ActNut::Number<uint8_t>	arg2Wrapper;
    ActNut::Number<uint8_t>	arg3Wrapper;

    int32_t	parseArgument(const std::string& argument);

  public:
    SQInstruction(const Object* parent, const std::string& name);
    ~SQInstruction();
    bool	readValue(IBuffer& buf);
    void	print(std::ostream& os) const;
    bool	writeValue(IBuffer& buf) const;

    // Operator[] is used to access/edit the op and arguments.
    // key is assumed to be a digit - only the 1st character of the string is checked.
    // 0 returns the op. 1->4 returns arg0->arg3. That doesn't match their names,
    // but this is the order in which they are displayed, and so will probably
    // be the more logical for the end users.
    //
    // They all have an operator= that supports integer input. Op also supports instruction names.
    Object*		operator[](const char* key);
    const Object*	operator[](const char* key) const;
    const Object&	operator=(const std::string& new_value);
  };

}

#endif /* !NUT_SQINSTRUCTIONS_HPP_ */
