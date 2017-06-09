#ifndef OBJECT_HPP_
# define OBJECT_HPP_

# include	<iostream>
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
    static T*	read(Buffer& buf, const Object* parent, const std::string& name)
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


  class	vector : public Object, public std::vector<Object*>
  {
  public:
   vector(Object* parent, const std::string& name)
      : Object(parent, "std::vector", name) {}
    ~vector();

    bool	readValue(Buffer& buf);
    void	print(std::ostream& os) const;
  };

}

#endif /* !OBJECT_HPP_ */
