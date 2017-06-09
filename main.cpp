#include	<iostream>
#include	<fstream>
#include	"File.hpp"

int	main(int argc, char** argv)
{
  if (argc != 2)
    {
      std::cout << "Usage: " << argv[0] << " file.act" << std::endl;
      return 0;
    }

  ActNut::Error::setErrorMode(ActNut::Error::STDERR);
  Act::Entry::init_hashes();
  try
    {
	// Act::Entry* entry = readAct(buf);
	// std::cout << *entry << std::endl;
	// delete entry;
      /*std::vector<Act::Entry*> entries = readAct(buffer);
      for (Act::Entry* it : entries)
	std::cout << *it << std::endl << std::endl;
      for (Act::Entry* it : entries)
      delete it;*/
      Act::File*	file = Act::File::read(argv[1]);
      std::cout << *file << std::endl;
      delete file;
    }
  catch (std::runtime_error e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
      return 1;
    }

  return 0;
}
