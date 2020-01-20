#include	<iostream>
#include	<string.h>
#include	"act/File.hpp"
#include	"nut/Stream.hpp"

int	printUsage(const char* bin_name)
{
  std::cout << "Usage: " << bin_name << " [options] file.[act|nut]" << std::endl
	    << "Options:" << std::endl
	    << "--no-print-file:\tDoesn't print the content of the file, only prints errors." << std::endl
	    << "--print-full-names:\tWhen printing an object name, also prints its full path." << std::endl;
  return 0;
}

int	main(int argc, char** argv)
{
  if (argc < 2)
    return printUsage(argv[0]);

  ActNut::Error::setErrorMode(ActNut::Error::EXCEPTION);
  ActNut::Object::printFullNames(false);
  bool	print_file = true;

  // Parsing the command line
  const char*	filename = nullptr;
  for (int i = 1; i < argc; i++)
    {
      if (strcmp(argv[i], "--no-print-file") == 0)
	print_file = false;
      else if (strcmp(argv[i], "--print-full-names") == 0)
	ActNut::Object::printFullNames(true);
      else
	{
	  if (!filename)
	    filename = argv[i];
	  else
	    return printUsage(argv[0]);
	}
    }
  if (!filename)
    return printUsage(argv[0]);

  try
    {
      ActNut::Object*	file;
      const char* ext = strrchr(filename, '.');
      if (ext && strcmp(ext, ".act") == 0)
	file = Act::File::read(filename);
      else if (ext && strcmp(ext, ".nut") == 0)
	file = Nut::readStream(filename);
      else
	{
	  std::cerr << "You must give a file with the act or nut extension." << std::endl;
	  return 1;
	}
      if (file)
	{
	  if (print_file)
	    std::cout << *file << std::endl;
	}
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
