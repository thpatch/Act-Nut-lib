#ifndef ACT_ENTRY_HPP_
# define ACT_ENTRY_HPP_

# include	<vector>
# include	<map>
# include	<iostream>
# include	"ActObject.hpp"
# include	"nut/SQFunctionProto.hpp"
# include	"Buffer.hpp"

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

    //private:
    static const char*				type_names[];
    static std::map<uint32_t, const char*>	type_hashes;
    static uint32_t				type_name_to_hash(const char* name);
    static const char*				type_hash_to_name(uint32_t hash);

    const int			flags;

    uint32_t			type_hash;
    const char*			type_name;

    std::vector<Act::Object*>	array;
    Act::Entry*			subEntry;
    Act::Entry*			subEntry2;
    std::vector<Act::Object*>	nutInfo;
    SQFunctionProto*		nut;

    Act::Object*		readObject(Buffer& buf);
    virtual Act::Object*	createObjectFromType(uint32_t type, const std::string& name);
    bool			readArray(Buffer& buf, std::vector<Act::Object*>& array);
    bool			readNut(Buffer& buf, std::vector<Act::Object*>& nutInfo);

  public:
    static void		init_hashes();
    static Entry*	read(Buffer& buf, int flags = 0);

    Entry(const char* name, int flags = 0);
    ~Entry();

    bool	readValue(Buffer& buf);
    void	print(std::ostream& os) const;
  };

}

#endif /* !ACT_ENTRY_HPP_ */
