#ifndef ACT_ENTRY_HPP_
# define ACT_ENTRY_HPP_

# include	<vector>
# include	<map>
# include	<iostream>
# include	<Object.hpp>
# include	<Utils.hpp>

namespace Act
{

  using ActNut::Object;
  using ActNut::vector;
  using ActNut::Buffer;
  using ActNut::Error;

  class	Entry : public Object
  {
  private:
    static const char*				type_names[];
    static std::map<uint32_t, const char*>	type_hashes;
    static uint32_t				type_name_to_hash(const char* name);
    static const char*				type_hash_to_name(uint32_t hash);

  protected:
    vector			array;

    Object*		readObject(Buffer& buf);
    virtual Object*	createObjectFromType(uint32_t type, const std::string& name);
    bool		readArray(Buffer& buf, vector& array);

  public:
    static void		init_hashes();
    static Entry*	read(const Object* parent, Buffer& buf, const std::string& name);

    Entry(const Object* parent, const char* type, const std::string& name);

    bool	readValue(Buffer& buf);
    void	print(std::ostream& os) const;
  };

}

#endif /* !ACT_ENTRY_HPP_ */
