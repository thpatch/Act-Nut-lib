#ifndef ACT_ENTRIES_HPP_
# define ACT_ENTRIES_HPP_

# include	<Object.hpp>
# include	<act/Object.hpp>
# include	<act/Entry.hpp>
# include	<nut/Stream.hpp>

namespace Act
{

  using ActNut::Object;
  using ActNut::vector;
  using ActNut::Buffer;


  class	NutStream : public Entry
  {
  private:
    Nut::SQFunctionProto*	stream;
  public:
    NutStream(const Object* parent, const std::string& name);
    ~NutStream();
    bool	readValue(Buffer& buf);
    void	print(std::ostream& os) const;
  };



  class	Root : public Entry
  {
  private:
    NutStream*	nutstream;
  public:
    Root(const Object* parent, const std::string& name);
    ~Root();
    bool	readValue(Buffer& buf);
    void	print(std::ostream& os) const;
  };

  class	Layer : public Entry
  {
  private:
    Entry*	keyframe;
    NutStream*	nutstream;
  public:
    Layer(const Object* parent, const std::string& name);
    ~Layer();
    bool	readValue(Buffer& buf);
    void	print(std::ostream& os) const;
  };

  class	KeyFrame : public Entry
  {
  private:
    Entry*	layout;
  public:
    KeyFrame(const Object* parent, const std::string& name);
    ~KeyFrame();
    bool	readValue(Buffer& buf);
    void	print(std::ostream& os) const;
  };

  class	SpriteLayout : public Entry
  {
  public:
    SpriteLayout(const Object* parent, const std::string& name);
  };

  class	StringLayout : public Entry
  {
  public:
    StringLayout(const Object* parent, const std::string& name);
    bool	readValue(Buffer& buf);
    Object*	createObjectFromType(uint32_t type, const std::string& name);
  };

  class	ReservedLayout : public Entry
  {
  public:
    ReservedLayout(const Object* parent, const std::string& name);
  };

  class	BitmapFontResource : public Entry
  {
  private:
    vector	bitmapInfo;
    uint32_t	width;
    uint32_t	height;
    uint8_t	**bitmapFontData;

  public:
    BitmapFontResource(const Object* parent, const std::string& name);
    ~BitmapFontResource();
    bool	readValue(Buffer& buf);
    Object*	createObjectFromType(uint32_t type, const std::string& name);
    void	print(std::ostream& os) const;
  };

  class	ImageResource : public Entry
  {
  public:
    ImageResource(const Object* parent, const std::string& name);
  };

  class	RenderTarget : public Entry
  {
  public:
    RenderTarget(const Object* parent, const std::string& name);
  };

}

#endif /* !ACT_ENTRIES_HPP_ */
