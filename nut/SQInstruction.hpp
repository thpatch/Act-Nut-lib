#ifndef NUT_SQINSTRUCTIONS_HPP_
# define NUT_SQINSTRUCTIONS_HPP_

# include	<nut/SQObject.hpp>

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

  public:
    SQInstruction(const Object* parent, const std::string& name);
    ~SQInstruction();
    bool	readValue(IBuffer& buf);
    void	print(std::ostream& os) const;
    bool	writeValue(IBuffer& buf) const;
  };

}

#endif /* !NUT_SQINSTRUCTIONS_HPP_ */
