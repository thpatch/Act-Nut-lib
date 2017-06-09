#ifndef STREAM_HPP_
# define STREAM_HPP_

# include	<string>
# include	"SQFunctionProto.hpp"
# include	"Utils.hpp"

namespace Nut
{

  using ActNut::Buffer;
  using ActNut::Error;

  SQFunctionProto*	readStream(Buffer& buf);
  SQFunctionProto*	readStream(const std::string& filename);

}

#endif /* !STREAM_HPP_ */
