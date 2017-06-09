#ifndef FILE_HPP_
# define FILE_HPP_

# include	<string>
# include	"Object.hpp"
# include	"ActEntry.hpp"
# include	"Utils.hpp"

namespace Act
{

  using ActNut::Object;
  using ActNut::vector;
  using ActNut::Buffer;
  using ActNut::Error;

  class	File : public Object
  {
  private:
    Act::Entry*	mainEntry;
    vector	sprites;
    vector	resources;

  public:
    static File*	read(const std::string& filename);
    // That function could also be put in ActNut::Object, by copy-pasting its implementation.

    File(const Act::Object* parent, const std::string& name);
    ~File();

    bool	readValue(Buffer& buf);
    void	print(std::ostream& os) const;
  };

}

#endif /* !FILE_HPP_ */
