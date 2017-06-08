#ifndef ACT_ENTRIES_HPP_
# define ACT_ENTRIES_HPP_

# include	"ActEntry.hpp"

namespace Act
{

  using ActNut::Buffer;

  class	Root : public Entry
  {
  public:
    Root(const Object* parent);
    bool	readValue(Buffer& buf);
  };

  class	Layer : public Entry
  {
  public:
    Layer(const Object* parent);
    bool	readValue(Buffer& buf);
  };

  class	KeyFrame : public Entry
  {
  public:
    KeyFrame(const Object* parent);
    bool	readValue(Buffer& buf);
  };

  class	SpriteLayout : public Entry
  {
  public:
    SpriteLayout(const Object* parent);
  };

  class	StringLayout : public Entry
  {
  public:
    StringLayout(const Object* parent);
    bool		readValue(Buffer& buf);
    Act::Object*	createObjectFromType(uint32_t type, const std::string& name);
  };

  class	ReservedLayout : public Entry
  {
  public:
    ReservedLayout(const Object* parent);
  };

  class	BitmapFontResource : public Entry
  {
  private:
    std::vector<Act::Object*>	subArray;
    uint32_t	width;
    uint32_t	height;
    uint8_t	**bitmapFontData;

  public:
    BitmapFontResource(const Object* parent);
    ~BitmapFontResource();
    bool		readValue(Buffer& buf);
    Act::Object*	createObjectFromType(uint32_t type, const std::string& name);
  };

  class	ImageResource : public Entry
  {
  public:
    ImageResource(const Object* parent);
  };

  class	RenderTarget : public Entry
  {
  public:
    RenderTarget(const Object* parent);
  };

}

#endif /* !ACT_ENTRIES_HPP_ */
