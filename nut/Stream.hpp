#ifndef NUT_STREAM_HPP_
# define NUT_STREAM_HPP_

# include	<string>
# include	<nut/SQFunctionProto.hpp>
# include	<Utils.hpp>

namespace Nut
{

  using ActNut::IBuffer;
  using ActNut::Error;

  SQFunctionProto*	readStream(IBuffer& buf, const ActNut::Object* parent = nullptr, const std::string& name = "");
  SQFunctionProto*	readStream(const std::string& filename);

}

#endif /* !NUT_STREAM_HPP_ */
