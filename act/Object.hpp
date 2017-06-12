#ifndef ACT_OBJECT_HPP_
# define ACT_OBJECT_HPP_

# include	<string>
# include	<Object.hpp>
# include	<Utils.hpp>

namespace Act
{

  using ActNut::Buffer;
  using ActNut::Object;
  using ActNut::Number;

  class	Integer	: public Number<int32_t> { public: Integer( const Object* parent, const std::string& name) : Number(parent, "int",   name) {}};
  class	Float	: public Number<float>   { public: Float(   const Object* parent, const std::string& name) : Number(parent, "float", name, Number::DisplayType::FLOAT) {}};
  class	Boolean	: public Number<uint8_t> { public: Boolean( const Object* parent, const std::string& name) : Number(parent, "bool",  name, Number::DisplayType::BOOLEAN) {}};
  class	Integer5: public Number<int32_t> { public: Integer5(const Object* parent, const std::string& name) : Number(parent, "int",   name) {}};

  class	String : public Object
  {
  private:
    std::string	value;

  public:
    String(const Object* parent, const std::string& name)
      : Object(parent, "string", name) {}

    bool	readValue(Buffer& buf);
    void	print(std::ostream& os) const;
  };

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
