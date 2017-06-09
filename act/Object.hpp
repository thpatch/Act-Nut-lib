#ifndef ACT_OBJECT_HPP_
# define ACT_OBJECT_HPP_

# include	<string>
# include	<Object.hpp>
# include	<Utils.hpp>

namespace Act
{

  using ActNut::Buffer;
  using ActNut::Object;

  template<typename T>
  class	Number : public Object
  {
  protected:
    T		n;

  public:
    Number(Object* parent, const char* type, const std::string& name)
      : Object(parent, type, name), n(0)
    { }

    bool	readValue(Buffer& buf)
    { return buf.readBytes((uint8_t*)&this->n, sizeof(this->n)); }

    void	print(std::ostream& os) const
    { os << +this->n; }
  };

  class	Integer	: public Number<int32_t> { public: Integer( Object* parent, const std::string& name) : Number(parent, "int",   name) {}};
  class	Float	: public Number<float>   { public: Float(   Object* parent, const std::string& name) : Number(parent, "float", name) {}};
  class	Boolean	: public Number<uint8_t> { public: Boolean( Object* parent, const std::string& name) : Number(parent, "bool",  name) {}};
  class	Integer5: public Number<int32_t> { public: Integer5(Object* parent, const std::string& name) : Number(parent, "int",   name) {}};

  class	String : public Object
  {
  private:
    std::string	value;

  public:
    String(Object* parent, const std::string& name)
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
    Array(Object* parent, const std::string& name)
      : Object(parent, "array", name) {}

    bool	readValue(Buffer& buf);
    bool	readContent(Buffer& buf);
    void	print(std::ostream& os) const;
  };
}

#endif /* !ACT_OBJECT_HPP_ */
