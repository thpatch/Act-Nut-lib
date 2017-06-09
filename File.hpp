#ifndef FILE_HPP_
# define FILE_HPP_

# include	<string>
# include	"ActEntry.hpp"
# include	"Utils.hpp"

namespace Act
{

  using ActNut::Buffer;
  using ActNut::Error;

  class	File : public Object
  {
  private:
    Act::Entry*	mainEntry;
    Act::vector	sprites;
    Act::vector	resources;

  public:
    static File*	read(Buffer& buf, const Object* parent);
    /* TODO:
    ** replace this function with:
    ** template<typename T>
    ** T*	Object::read(Buffer& buf, const Object* parent, const char* name)
    ** {
    **   T*	obj = new T(parent, name);
    **   if (!obj->readValue(buf))
    **     {
    **       delete obj;
    **       return nullptr;
    **     }
    **   return obj;
    ** }
    */
    static File*	read(const std::string& filename);
    // That function could also be put in ActNut::Object, by copy-pasting its implementation.

    File(const Act::Object* parent, const char* name);
    ~File();

    bool	readValue(Buffer& buf);
    void	print(std::ostream& os) const;
  };

}

#endif /* !FILE_HPP_ */
