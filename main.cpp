#include	<iostream>
#include	<string.h>
#include	<act/File.hpp>
#include	<nut/Stream.hpp>

int	main(int argc, char** argv)
{
  if (argc != 2)
    {
      std::cout << "Usage: " << argv[0] << " file.[act|nut]" << std::endl;
      return 0;
    }

  ActNut::Error::setErrorMode(ActNut::Error::STDERR);
  ActNut::Object::printFullNames(true);
  Act::Entry::init_hashes();
  try
    {
      ActNut::Object*	file;
      const char* ext = strrchr(argv[1], '.');
      if (ext && strcmp(ext, ".act") == 0)
	file = Act::File::read(argv[1]);
      else if (ext && strcmp(ext, ".nut") == 0)
	file = Nut::readStream(argv[1]);
      else
	{
	  std::cerr << "You must give a file with the act or nut extension." << std::endl;
	  return 1;
	}
      if (file)
	std::cout << *file << std::endl;
      else
	std::cerr << "File parsing failed." << std::endl;
      delete file;
    }
  catch (std::runtime_error& e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
      return 1;
    }

  return 0;
}
