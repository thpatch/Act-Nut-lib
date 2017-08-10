#ifndef NUT_SQINSTRUCTIONS_HPP_
# define NUT_SQINSTRUCTIONS_HPP_

# include	"nut/SQObject.hpp"

namespace Nut
{

  using ActNut::IBuffer;

  class	SQFunctionProto;

  class	SQInstruction : public SQObjectPtr
  {
  private:
    const SQFunctionProto&	func;
    SQInteger*	arg1;
    uint8_t	op;
    uint8_t	arg0;
    uint8_t	arg2;
    uint8_t	arg3;

    // For operator= support
    ActNut::Number<uint8_t> opWrapper;
    ActNut::Number<uint8_t> arg0Wrapper;
    ActNut::Number<uint8_t> arg2Wrapper;
    ActNut::Number<uint8_t> arg3Wrapper;

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
    Object*		operator[](const char* key);
    const Object*	operator[](const char* key) const;
  };

}

#endif /* !NUT_SQINSTRUCTIONS_HPP_ */
