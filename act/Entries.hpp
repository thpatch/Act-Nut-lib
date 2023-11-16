#ifndef ACT_ENTRIES_HPP_
# define ACT_ENTRIES_HPP_

# include	"../Object.hpp"
# include	"act/Object.hpp"
# include	"act/Entry.hpp"
# include	"nut/Stream.hpp"

namespace Act
{

  using ActNut::Object;
  using ActNut::vector;
  using ActNut::IBuffer;


  class	NutStream : public Entry
  {
  private:
    uint32_t			nutSize;
    uint8_t*			nutBytes;
    Nut::SQFunctionProto*	stream;
  protected:
    bool	writeHash(IBuffer& buf) const;
  public:
    NutStream(const Object* parent, const std::string& name);
    ~NutStream();
    NutStream&	operator=(const NutStream&) = delete;
    using	Object::operator=;
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
    Root&	operator=(const Root&) = delete;
    using	Object::operator=;
    bool	readValue(IBuffer& buf);
    void	print(std::ostream& os) const;
    bool	writeValue(IBuffer& buf) const;
  };

  class	Layer : public Entry
  {
  private:
    vector	keyframes;
    vector	weirdarray;
    NutStream*	nutstream;
  public:
    Layer(const Object* parent, const std::string& name);
    ~Layer();
    Layer&	operator=(const Layer&) = delete;
    using	Object::operator=;
    bool	readValue(IBuffer& buf);
    void	print(std::ostream& os) const;
    bool	writeValue(IBuffer& buf) const;
    Object*		operator[](const char* key);
    const Object*	operator[](const char* key) const;
  };

  class	KeyFrame : public Entry
  {
  private:
    Entry*	layout;
  public:
    KeyFrame(const Object* parent, const std::string& name);
    ~KeyFrame();
    KeyFrame&	operator=(const KeyFrame&) = delete;
    using	Object::operator=;
    bool	readValue(IBuffer& buf);
    void	print(std::ostream& os) const;
    bool	writeValue(IBuffer& buf) const;
  };

  class	SpriteLayout : public Entry
  {
  public:
    SpriteLayout(const Object* parent, const std::string& name);
    SpriteLayout&	operator=(const SpriteLayout&) = delete;
    using		Object::operator=;
  };

  class	IFSMeshLayout : public Entry
  {
  public:
    IFSMeshLayout(const Object* parent, const std::string& name);
    IFSMeshLayout&	operator=(const IFSMeshLayout&) = delete;
    using		Object::operator=;
  };

  class	StringLayout : public Entry
  {
  public:
    StringLayout(const Object* parent, const std::string& name);
    StringLayout&	operator=(const StringLayout&) = delete;
    using	Object::operator=;
    bool	readValue(IBuffer& buf);
    Object*	createObjectFromType(uint32_t type, const Object* parent, const std::string& name);
    bool	writeValue(IBuffer& buf) const;
  };

  class	ReservedLayout : public Entry
  {
  public:
    ReservedLayout(const Object* parent, const std::string& name);
    ReservedLayout&	operator=(const ReservedLayout&) = delete;
    using		Object::operator=;
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
    BitmapFontResource&	operator=(const BitmapFontResource&) = delete;
    using	Object::operator=;
    bool	readValue(IBuffer& buf);
    Object*	createObjectFromType(uint32_t type, const Object* parent, const std::string& name);
    void	print(std::ostream& os) const;
    bool	writeValue(IBuffer& buf) const;
  };

  class	ImageResource : public Entry
  {
  public:
    ImageResource(const Object* parent, const std::string& name);
    ImageResource&	operator=(const ImageResource&) = delete;
    using		Object::operator=;
  };

  class	RenderTarget : public Entry
  {
  public:
    RenderTarget(const Object* parent, const std::string& name);
    RenderTarget&	operator=(const RenderTarget&) = delete;
    using		Object::operator=;
  };

}

#endif /* !ACT_ENTRIES_HPP_ */
