#include	<iostream>
#include	<fstream>
#include	"ActEntry.hpp"

std::vector<Act::Entry*>	readAct(Buffer& buf)
{
  buf.checkTag('1TCA'); // ACT1
  buf.checkTag(1);

  std::vector<Act::Entry*>	entries;

  Act::Entry* mainEntry = new Act::Entry("Main Entry", Act::Entry::HAVE_NUT);
  if (!mainEntry->readValue(buf))
    std::cerr << "Reading main entry failed." << std::endl;
  entries.push_back(mainEntry);

  uint32_t nbScripts = buf.readInt();
  for (uint32_t i = 0; i < nbScripts; i++)
    {
      Act::Entry* entry = new Act::Entry("Script", Act::Entry::HAVE_NUT | Act::Entry::HAVE_SUB_ENTRY | Act::Entry::HAVE_SUB_ENTRY_COUNT);
      if (!entry->readValue(buf))
	std::cerr << "Reading script " << i + 1 << " failed." << std::endl;
      entries.push_back(entry);
    }

  uint32_t nbResources = buf.readInt();
  for (uint32_t i = 0; i < nbResources; i++)
    {
      Act::Entry* entry = new Act::Entry("Resource", 0);
      if (!entry->readValue(buf))
	std::cerr << "Reading resource " << i + 1 << " failed." << std::endl;
      entries.push_back(entry);
    }

  return entries;
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
  Buffer buffer(buf, len, Buffer::STDERR);

  try
    {
      /*
	Act::Entry* entry = readAct(buf);
	std::cout << *entry << std::endl;
	delete entry;
      */
      std::vector<Act::Entry*> entries = readAct(buffer);
      //for (Act::Entry* it : entries)
      //std::cout << *it << std::endl << std::endl;
      for (Act::Entry* it : entries)
	delete it;
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
