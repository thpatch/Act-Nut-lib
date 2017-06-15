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
  using ActNut::IBuffer;
  using ActNut::Error;

  class	Entry : public Object
  {
  private:
    static const char*				type_names[];
    static std::map<uint32_t, const char*>	type_hashes;
    static uint32_t				type_name_to_hash(const char* name);
    static const char*				type_hash_to_name(uint32_t hash);

  protected:
    vector		array;

    Object*		readObject(IBuffer& buf);
    virtual Object*	createObjectFromType(uint32_t type, const std::string& name);
    bool		readArray(IBuffer& buf, vector& array);

  public:
    static void		init_hashes();
    static Entry*	read(const Object* parent, IBuffer& buf, const std::string& name);

    Entry(const Object* parent, const char* type, const std::string& name);

    bool	readValue(IBuffer& buf);
    void	print(std::ostream& os) const;

    virtual Object*		operator[](const char* key);
    virtual const Object*	operator[](const char* key) const;
  };

}

#endif /* !ACT_ENTRY_HPP_ */
