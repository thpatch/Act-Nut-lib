#include	"ActObject.hpp"
#include	"nut/SQFunctionProto.hpp"
#include	"Buffer.hpp"

namespace Act
{

  class	Entry : public Act::Object
  {
  public:
    enum	Flags
      {
	HAVE_NUT		= 0x01,
	HAVE_SUB_ENTRY		= 0x02,
	HAVE_SUB_ENTRY_COUNT	= 0x04
      };

  private:
    const int			flags;

    uint32_t			id;
    std::vector<Act::Object*>	array;
    Act::Entry*			subEntry;
    Act::Entry*			subEntry2;
    std::vector<Act::Object*>	nutInfo;
    SQFunctionProto		*nut;

    bool	readArray(Buffer& buf, std::vector<Act::Object*>& array);

  public:
    Entry(const std::string& name, int flags = 0);
    ~Entry();

    bool	readValue(Buffer& buf);
    void	print(std::ostream& os) const;
  };

}
