#include	"SQFunctionProto.hpp"
#include	"Stream.hpp"

int	main(int argc, char** argv)
{
  if (argc != 2)
    {
      std::cout << "Usage: " << argv[0] << " file.nut" << std::endl;
      return 0;
    }

  ActNut::Error::setErrorMode(ActNut::Error::STDERR);
  try
    {
      Nut::SQFunctionProto* func = Nut::readStream(argv[1]);
      std::cout << *func << std::endl;
      delete func;
    }
  catch (std::runtime_error e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
      return 1;
    }

  return 0;
}
