#ifndef NUT_STREAM_HPP_
# define NUT_STREAM_HPP_

# include	<string>
# include	<nut/SQFunctionProto.hpp>
# include	<Utils.hpp>

namespace Nut
{

  using ActNut::Buffer;
  using ActNut::Error;

  SQFunctionProto*	readStream(Buffer& buf);
  SQFunctionProto*	readStream(const std::string& filename);

}

#endif /* !NUT_STREAM_HPP_ */
