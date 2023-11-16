#include	<iostream>
#include	<memory>
#include	<string.h>
#include	"act/File.hpp"
#include	"nut/Stream.hpp"

int	printUsage(const char* bin_name)
{
  std::cout << "Usage: " << bin_name << " [options] file.(act|nut) [name new_value]..." << std::endl
	    << "With only an input file, print the file in a somewhat human-readable format." << std::endl
	    << "You can add any number of name/value pairs to edit the file. The file will be" << std::endl
	    << "edited in place." << std::endl
	    << "'name' is the full name of an element, as printed with --print-full-names." << std::endl
	    << "'new_value' is a new value of the same type as the original value." << std::endl
	    << "Options:" << std::endl
	    << "--no-print-file:\tDoesn't print the content of the file, only prints errors." << std::endl
	    << "--print-full-names:\tWhen printing an object name, also prints its full path." << std::endl;
  return 0;
}

bool	editFile(ActNut::Object& file, char **args, size_t count)
{
  // Edit mode
  for (size_t i = 0; i < count; i += 2)
    {
      if (i + 1 >= count)
        {
	  std::cerr << "Invalid parameters: no value for " << args[i] << std::endl;
	  return false;
        }
      *file.getChild(args[i]) = args[i + 1]; // Let the exception handler in main() handle this
    }
    return true;
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
  int i;
  for (i = 1; i < argc; i++)
    {
      if (strcmp(argv[i], "--no-print-file") == 0)
	print_file = false;
      else if (strcmp(argv[i], "--print-full-names") == 0)
	ActNut::Object::printFullNames(true);
      else
	{
	  if (!filename) {
	    filename = argv[i];
	    i++;
	    break;
	  }
	  else
	    return printUsage(argv[0]);
	}
    }
  if (!filename)
    return printUsage(argv[0]);
  if (i < argc) // Edit mode
    print_file = false;

  try
    {
      std::unique_ptr<ActNut::Object>	file;
      const char* ext = strrchr(filename, '.');
      if (ext && strcmp(ext, ".act") == 0)
	file.reset(Act::File::read(filename));
      else if (ext && strcmp(ext, ".nut") == 0)
	file.reset(Nut::readStream(filename));
      else
	{
	  std::cerr << "You must give a file with the act or nut extension." << std::endl;
	  return 1;
	}
      if (file)
	{
	  if (print_file)
	    std::cout << *file << std::endl;
	  if (i < argc)
	    {
	      if (editFile(*file, argv + i, argc - i))
	        file->writeToFile(filename);
	      else
	        return 1;
	    }
	}
      else
	std::cerr << "File parsing failed." << std::endl;
    }
  catch (std::runtime_error& e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
      return 1;
    }

  return 0;
}
