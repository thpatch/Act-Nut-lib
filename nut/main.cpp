#include	<fstream>
#include	"SQFunctionProto.hpp"
#include	"Utils.hpp"

Nut::SQFunctionProto*	readStream(ActNut::Buffer& buf)
{
  if (buf.readByte() != 0xFA || buf.readByte() != 0xFA)
    throw std::runtime_error("Wrong stream magic - should be 0xFAFA. You probably don't have a NUT file");

  buf.checkTag('SQIR');
  buf.checkTag(1);
  buf.checkTag(4);
  buf.checkTag(4);

  Nut::SQFunctionProto *func = new Nut::SQFunctionProto(buf);
  if (!func)
    return NULL;

  buf.checkTag('TAIL');
  return func;
}

int	main(int argc, char** argv)
{
  if (argc != 2)
    {
      std::cout << "Usage: " << argv[0] << " file.nut" << std::endl;
      return 0;
    }

  std::ifstream f(argv[1]);
  f.seekg(0, std::ios::end);
  int len = f.tellg();
  f.seekg(0, std::ios::beg);

  uint8_t* buf = (uint8_t*)malloc(len);
  f.read((char*)buf, len);
  f.close();
  ActNut::Buffer buffer(buf, len);
  ActNut::Error::setErrorMode(ActNut::Error::STDERR);

  try
    {
      Nut::SQFunctionProto* func = readStream(buffer);
      std::cout << *func << std::endl;
      delete func;
    }
  catch (std::runtime_error e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
      free(buf);
      return 1;
    }

  free(buf);
  return 0;
}
