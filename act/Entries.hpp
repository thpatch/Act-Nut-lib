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
  using ActNut::IBuffer;


  class	NutStream : public Entry
  {
  private:
    Nut::SQFunctionProto*	stream;
  protected:
    bool	writeHash(IBuffer& buf) const;
  public:
    NutStream(const Object* parent, const std::string& name);
    ~NutStream();
    bool	readValue(IBuffer& buf);
    void	print(std::ostream& os) const;
    bool	writeValue(IBuffer& buf) const;
  };



  class	Root : public Entry
  {
  private:
    NutStream*	nutstream;
  protected:
    bool	writeHash(IBuffer& buf) const;
  public:
    Root(const Object* parent, const std::string& name);
    ~Root();
    bool	readValue(IBuffer& buf);
    void	print(std::ostream& os) const;
    bool	writeValue(IBuffer& buf) const;
  };

  class	Layer : public Entry
  {
  private:
    Entry*	keyframe;
    NutStream*	nutstream;
  public:
    Layer(const Object* parent, const std::string& name);
    ~Layer();
    bool	readValue(IBuffer& buf);
    void	print(std::ostream& os) const;
    bool	writeValue(IBuffer& buf) const;
  };

  class	KeyFrame : public Entry
  {
  private:
    Entry*	layout;
  public:
    KeyFrame(const Object* parent, const std::string& name);
    ~KeyFrame();
    bool	readValue(IBuffer& buf);
    void	print(std::ostream& os) const;
    bool	writeValue(IBuffer& buf) const;
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
    bool	readValue(IBuffer& buf);
    Object*	createObjectFromType(uint32_t type, const std::string& name);
    bool	writeValue(IBuffer& buf) const;
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
    bool	readValue(IBuffer& buf);
    Object*	createObjectFromType(uint32_t type, const std::string& name);
    void	print(std::ostream& os) const;
    bool	writeValue(IBuffer& buf) const;
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
