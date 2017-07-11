#ifndef ACT_FILE_HPP_
# define ACT_FILE_HPP_

# include	<string>
# include	"../Object.hpp"
# include	"../Utils.hpp"
# include	"act/Entry.hpp"

namespace Act
{

  using ActNut::Object;
  using ActNut::vector;
  using ActNut::IBuffer;
  using ActNut::Error;

  class	File : public Object
  {
  private:
    Act::Entry*	mainEntry;
    vector	sprites;
    vector	resources;

  public:
    static File*	read(const std::string& filename);

    File(const Act::Object* parent, const std::string& name);
    ~File();

    bool	readValue(IBuffer& buf);
    void	print(std::ostream& os) const;
    bool	writeValue(IBuffer& buf) const;
  };

}

#endif /* !ACT_FILE_HPP_ */
