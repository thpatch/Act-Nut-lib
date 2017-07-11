#ifndef NUT_STREAM_HPP_
# define NUT_STREAM_HPP_

# include	<string>
# include	"nut/SQFunctionProto.hpp"
# include	"../Utils.hpp"

namespace Nut
{

  using ActNut::IBuffer;
  using ActNut::Error;

  class	Stream : public SQFunctionProto
  {
  public:
    Stream(const Object* parent, const std::string& name);
    bool	readValue(IBuffer& buf);
    bool	writeValue(IBuffer& buf) const;
  };

  SQFunctionProto*	readStream(const std::string& filename);

}

#endif /* !NUT_STREAM_HPP_ */
