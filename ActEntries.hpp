#ifndef ACT_ENTRIES_HPP_
# define ACT_ENTRIES_HPP_

# include	"ActEntry.hpp"

namespace Act
{
  
  class	Root : public Entry
  {
  public:
    Root();
    bool	readValue(Buffer& buf);
  };

  class	Layer : public Entry
  {
  public:
    Layer();
    bool	readValue(Buffer& buf);
  };

  class	KeyFrame : public Entry
  {
  public:
    KeyFrame();
    bool	readValue(Buffer& buf);
  };

  class	SpriteLayout : public Entry
  {
  public:
    SpriteLayout();
  };

  class	StringLayout : public Entry
  {
  public:
    StringLayout();
    bool		readValue(Buffer& buf);
    Act::Object*	createObjectFromType(uint32_t type, const std::string& name);
  };

  class	ReservedLayout : public Entry
  {
  public:
    ReservedLayout();
  };

  class	BitmapFontResource : public Entry
  {
  private:
    std::vector<Act::Object*>	subArray;
    uint32_t	width;
    uint32_t	height;
    uint8_t	**bitmapFontData;

  public:
    BitmapFontResource();
    ~BitmapFontResource();
    bool		readValue(Buffer& buf);
    Act::Object*	createObjectFromType(uint32_t type, const std::string& name);
  };

  class	ImageResource : public Entry
  {
  public:
    ImageResource();
  };

  class	RenderTarget : public Entry
  {
  public:
    RenderTarget();
  };

}

#endif /* !ACT_ENTRIES_HPP_ */
