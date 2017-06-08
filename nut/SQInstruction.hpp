#ifndef SQINSTRUCTIONS_HPP_
# define SQINSTRUCTIONS_HPP_

# include	"SQObject.hpp"

namespace Nut
{

  using ActNut::Buffer;

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
    SQInstruction(const SQFunctionProto& func, Buffer& buf, std::string name = "");
    ~SQInstruction();
    void	print(std::ostream& os) const;
  };

}

#endif /* !SQINSTRUCTIONS_HPP_ */
