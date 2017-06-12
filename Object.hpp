#ifndef OBJECT_HPP_
# define OBJECT_HPP_

# include	<iostream>
# include	<iomanip>
# include	<vector>
# include	"Utils.hpp"

namespace ActNut
{

  class	Object
  {
  protected:
    const Object*	parent;
    const char*		type;
    std::string		name;

  public:
    Object(const Object* parent, const char* type, const std::string& name);
    virtual ~Object() {}

    template<typename T>
    static T*	read(const Object* parent, Buffer& buf, const std::string& name = "")
    {
      T*	obj = new T(parent, name);
      if (!obj->readValue(buf))
	{
	  delete obj;
	  return nullptr;
	}
      return obj;
    }

    const std::string&	getName() const;
    int			getIndentLevel() const;
    std::string		printIndent(int indentLevel = -1) const;

    virtual bool	readValue(Buffer& buf) = 0;
    virtual void	print(std::ostream& os) const = 0;
  };
  std::ostream& operator<<(std::ostream& os, const Object& o);


  template<typename T>
  class	Number : public Object
  {
  protected:
    enum class	DisplayType
    {
      NONE,
      BOOLEAN,
      FLOAT
    };

    T		n;
    const DisplayType	displayType;

  public:
    Number(const Object* parent, const char* type, std::string name, DisplayType displayType = DisplayType::NONE)
      : Object(parent, type, name), n(0), displayType(displayType)
    { }

    bool	readValue(Buffer& buf)
    { return buf.readBytes((uint8_t*)&this->n, sizeof(this->n)); }

    void	print(std::ostream& os) const
    {
      if (displayType == DisplayType::FLOAT)
	os << std::setprecision(2) << std::fixed;
      if (displayType == DisplayType::BOOLEAN)
	os << std::boolalpha;
      os << +this->n;
      if (displayType == DisplayType::FLOAT)
	os << std::defaultfloat;
      if (displayType == DisplayType::BOOLEAN)
	os << std::noboolalpha;
    }

    operator T() { return this->n; }
  };


  class	vector : public Object, public std::vector<Object*>
  {
  public:
   vector(const Object* parent, const std::string& name)
      : Object(parent, "std::vector", name) {}
    ~vector();

    bool	readValue(Buffer& buf);
    void	print(std::ostream& os) const;
  };

}

#endif /* !OBJECT_HPP_ */
