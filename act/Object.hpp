#ifndef ACT_OBJECT_HPP_
# define ACT_OBJECT_HPP_

# include	<string>
# include	<Object.hpp>
# include	<Utils.hpp>

namespace Act
{

  using ActNut::Buffer;
  using ActNut::Object;

  class	Integer	: public ActNut::Number<int32_t> { public: Integer( const Object* parent, const std::string& name); };
  class	Float	: public ActNut::Number<float>   { public: Float(   const Object* parent, const std::string& name); };
  class	Boolean	: public ActNut::Number<uint8_t> { public: Boolean( const Object* parent, const std::string& name); };
  class	Integer5: public ActNut::Number<int32_t> { public: Integer5(const Object* parent, const std::string& name); };
  class	String  : public ActNut::String          { public: String(  const Object* parent, const std::string& name); };

  class	Array : public Object
  {
  private:
    uint32_t			nbEntries;
    std::vector<uint32_t>	entries;

  public:
    Array(const Object* parent, const std::string& name)
      : Object(parent, "array", name) {}

    bool	readValue(Buffer& buf);
    bool	readContent(Buffer& buf);
    void	print(std::ostream& os) const;
  };
}

#endif /* !ACT_OBJECT_HPP_ */
