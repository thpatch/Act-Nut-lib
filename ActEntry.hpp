#ifndef ACT_ENTRY_HPP_
# define ACT_ENTRY_HPP_

# include	<vector>
# include	<map>
# include	<iostream>
# include	"Object.hpp"
# include	"nut/SQFunctionProto.hpp"
# include	"Utils.hpp"

namespace Act
{

  using ActNut::Object;
  using ActNut::vector;
  using ActNut::Buffer;
  using ActNut::Error;

  class	Entry : public Object
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

    vector			array;
    Entry*			subEntry;
    vector			nutInfo;
    Nut::SQFunctionProto*	nut;

    Object*		readObject(Buffer& buf);
    virtual Object*	createObjectFromType(uint32_t type, const std::string& name);
    bool		readArray(Buffer& buf, vector& array);
    bool		readNut(Buffer& buf, vector& nutInfo);

  public:
    static void		init_hashes();
    static Entry*	read(Buffer& buf, const Object* parent, int flags = 0);

    Entry(const Object* parent, const char* name, int flags = 0);
    ~Entry();

    bool	readValue(Buffer& buf);
    void	print(std::ostream& os) const;
  };

}

#endif /* !ACT_ENTRY_HPP_ */
