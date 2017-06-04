#include	<fstream>
#include	"SQFunctionProto.hpp"
#include	"utils.hpp"

SQFunctionProto*	readStream(const uint8_t* buf)
{
  if (buf[0] != 0xFA || buf[1] != 0xFA)
    throw std::runtime_error("Wrong stream magic - should be 0xFAFA. You probably don't have a NUT file");
  buf += 2;

  checkTag(buf, 'SQIR');
  checkTag(buf, 1);
  checkTag(buf, 4);
  checkTag(buf, 4);

  SQFunctionProto *func = new SQFunctionProto(buf);
  if (!func)
    return NULL;

  checkTag(buf, 'TAIL');
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

  try
    {
      SQFunctionProto* func = readStream(buf);
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
