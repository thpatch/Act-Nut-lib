#ifndef ACT_OBJECT_HPP_
# define ACT_OBJECT_HPP_

# include	<string>
# include	<vector>
# include	"Buffer.hpp"

namespace Act
{

  class	Object
  {
  protected:
    uint32_t	numType;
    const char*	type;
    std::string	name;

  public:
    static Object*	load(Buffer& buf);

    Object(uint32_t numType, const char* type, const std::string& name);
    virtual ~Object() {}
    const std::string&	getName() const;

    virtual bool	readValue(Buffer& buf) = 0;
    virtual void	print(std::ostream& os) const = 0;
  };
  std::ostream& operator<<(std::ostream& os, const Object& o);


  template<typename T>
  class	Number : public Object
  {
  protected:
    T		n;

  public:
    Number(uint32_t numType, const char* type, const std::string& name)
      : Object(numType, type, name), n(0)
    { }

    bool	readValue(Buffer& buf)
    { return buf.readBytes((uint8_t*)&this->n, sizeof(this->n)); }

    void	print(std::ostream& os) const
    { os << +this->n; }
  };

  class	Integer	: public Number<int32_t> { public: Integer(const std::string& name)  : Number(0, "int",   name) {}};
  class	Float	: public Number<float>   { public: Float(const std::string& name)    : Number(1, "float", name) {}};
  class	Boolean	: public Number<uint8_t> { public: Boolean(const std::string& name)  : Number(2, "bool",  name) {}};
  class	Integer5: public Number<int32_t> { public: Integer5(const std::string& name) : Number(5, "int",   name) {}};

  class	String : public Object
  {
  private:
    std::string	value;

  public:
    String(const std::string& name)
      : Object(3, "string", name) {}

    bool	readValue(Buffer& buf);
    void	print(std::ostream& os) const;
  };

  class	Array : public Object
  {
  private:
    uint32_t			nbEntries;
    std::vector<uint32_t>	entries;

  public:
    Array(const std::string& name)
      : Object(5, "array", name) {}

    bool	readValue(Buffer& buf);
    bool	readContent(Buffer& buf);
    void	print(std::ostream& os) const;
  };
}

#endif /* !ACT_OBJECT_HPP_ */
