#ifndef OBJECT_HPP_
# define OBJECT_HPP_

# include	<iostream>
# include	<iomanip>
# include	<vector>
# include	<string.h>
# include	"Utils.hpp"

namespace ActNut
{

  class	Object
  {
  protected:
    const Object*		parent;
    const char*			type;
    std::string			name;

    std::vector<Object*>	members;
    void			addMember(Object* member);

  public:
    static bool			_printFullNames;
    static void	printFullNames(bool value);

    Object(const Object* parent, const char* type, const std::string& name);
    virtual ~Object() {}

    template<typename T>
    static T*	read(const Object* parent, IBuffer& buf, const std::string& name)
    {
      T*	obj = new T(parent, name);
      if (!obj->readValue(buf))
	{
	  delete obj;
	  return nullptr;
	}
      return obj;
    }

    template<typename T>
    static T*		read(const std::string& filename)
    {
      FileBuffer	buf(filename, std::ios_base::in);
      IBuffer*		oldBuffer = Error::setErrorBuffer(&buf);
      T* ret = read<T>(nullptr, buf, filename);
      Error::setErrorBuffer(oldBuffer);
      return ret;
    }

    const Object*		getParent() const;
    const std::string&		getName() const;
    virtual uint32_t		getNumType() const;
    std::string			getFullName() const;
    int				getIndentLevel() const;
    std::string			printIndent(int indentLevel = -1) const;

    virtual bool		readValue(IBuffer& buf) = 0;
    virtual void		print(std::ostream& os) const = 0;
    virtual bool		writeValue(IBuffer& buf) const = 0;
    virtual bool		writeToFile(const std::string& filename) const;

    virtual Object*		operator[](const char* key);
    virtual const Object*	operator[](const char* key) const;
    virtual Object*		getChild(const char* path);
    virtual const Object*	getChild(const char* path) const;
    virtual const Object&	operator=(const std::string& new_value);

    void		        setName(const std::string& name);
  };
  std::ostream& operator<<(std::ostream& os, const Object& o);


  template<typename T>
  class	Number : public Object
  {
  protected:
    enum class  Type
    {
      BOOLEAN,
      INTEGER,
      FLOAT
    };

    T			storage;
    T&			n;
    const uint32_t	numType;
    const Type		nType;

  public:
    // By default, the Number class will contain a number in storage.
    Number(const Object* parent, const char* type, const std::string& name, uint32_t numType = 0, Type nType = Type::INTEGER)
      : Object(parent, type, name), storage(0), n(storage), numType(numType), nType(nType)
    { }

    // We can also use the Number class to wrap a variable. In that case, storage is not used (because it is external to the class).
    Number(const Object* parent, const char* type, const std::string& name, T& ref, uint32_t numType = 0, Type nType = Type::INTEGER)
      : Object(parent, type, name), n(ref), numType(numType), nType(nType)
    { }

    uint32_t	getNumType() const
    { return numType; }

    bool	readValue(IBuffer& buf)
    { return buf.readBytes((uint8_t*)&this->n, sizeof(this->n)); }

    bool	writeValue(IBuffer& buf) const
    { return buf.writeBytes((uint8_t*)&this->n, sizeof(this->n)); }

    void	print(std::ostream& os) const
    {
      if (nType == Type::FLOAT)
	os << std::setprecision(2) << std::fixed;
      if (nType == Type::BOOLEAN)
	os << std::boolalpha;
      os << +this->n;
      if (nType == Type::FLOAT)
	os << std::defaultfloat;
      if (nType == Type::BOOLEAN)
	os << std::noboolalpha;
    }

    const Object&	operator=(const T& new_value)
    {
      this->n = new_value;
      return *this;
    }

    virtual const Object&	operator=(const std::string& new_value)
    {
      switch (nType)
	{
	case Type::INTEGER:
	  this->n = (T)stol(new_value, nullptr, 0);
	  break ;

	case Type::FLOAT:
	  this->n = (T)stod(new_value, nullptr);
	  break ;

	case Type::BOOLEAN:
	  if (!strcmp(new_value.c_str(), "true") || !strcmp(new_value.c_str(), "True") || !strcmp(new_value.c_str(), "TRUE"))
	    this->n = true;
	  else if (!strcmp(new_value.c_str(), "false") || !strcmp(new_value.c_str(), "False") || !strcmp(new_value.c_str(), "FALSE"))
	    this->n = false;
	  else if (stol(new_value, nullptr, 0) != 0)
	    this->n = true;
	  else
	    this->n = false;
	  break ;
	}
      return *this;
    }

    operator T() const { return this->n; }
  };


  class	String : public Object
  {
  protected:
    std::string	value;

  public:
    String(const Object* parent, const char* type, const std::string& name);

    bool		readValue(IBuffer& buf);
    void		print(std::ostream& os) const;
    bool		writeValue(IBuffer& buf) const;
    const Object&	operator=(const std::string& new_value);
  };

  class	vector : public Object, public std::vector<Object*>
  {
  public:
   vector(const Object* parent, const std::string& name)
      : Object(parent, "std::vector", name) {}
    ~vector();

    bool	readValue(IBuffer& buf);
    bool	writeValue(IBuffer& buf) const;
    template<typename T>
    bool	add(T* (*readerFunc)(const Object* parent, IBuffer& buf, const std::string& name), IBuffer& buf)
    {
      Object*	obj = readerFunc(this, buf, std::to_string(this->size()));
      if (!obj)
	return false;
      this->push_back(obj);
      return true;
    }
    void		print(std::ostream& os) const;
    Object*		operator[](size_type n);
    const Object*	operator[](size_type n) const;
    Object*		operator[](const char* key);
    const Object*	operator[](const char* key) const;
  };

}

#endif /* !OBJECT_HPP_ */
