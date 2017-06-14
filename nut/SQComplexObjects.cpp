#include	<nut/SQComplexObjects.hpp>

Nut::SQOuterType::SQOuterType(const Object* parent, const std::string& name)
  : Number(parent, "SQOuterType", name)
{}

void	Nut::SQOuterType::print(std::ostream& os) const
{
  os << (this->n ? "otOUTER" : "otLOCAL");
}

Nut::SQOuterVal::SQOuterVal(const Object* parent, const std::string& name)
  : SQObjectPtr(parent, "SQOuterVal", name)
{}

Nut::SQOuterVal::~SQOuterVal()
{
  delete this->type;
  delete this->object;
  delete this->name;
}

bool	Nut::SQOuterVal::readValue(Buffer& buf)
{
  this->type   = ActNut::Object::read<SQOuterType>(this, buf, "type");
  this->object = loadObject(this, buf, "object");
  this->name   = loadObject(this, buf, "name");
  return true;
}

void	Nut::SQOuterVal::print(std::ostream& os) const
{
  os << *this->type << ", " << *this->object << ", " << *this->name;
}





Nut::SQLocalVarInfo::SQLocalVarInfo(const Object* parent, const std::string& name)
  : SQObjectPtr(parent, "SQLocalVarInfo", name)
{
}

Nut::SQLocalVarInfo::~SQLocalVarInfo()
{
  delete this->name;
  delete this->pos;
  delete this->start_op;
  delete this->end_op;
}

bool	Nut::SQLocalVarInfo::readValue(Buffer& buf)
{
  this->name	= loadObject(this, buf, "name");
  this->pos	= ActNut::Object::read<SQUnsignedInteger>(this, buf, "pos");
  this->start_op= ActNut::Object::read<SQUnsignedInteger>(this, buf, "start_op");
  this->end_op	= ActNut::Object::read<SQUnsignedInteger>(this, buf, "end_op");
  return true;
}

void	Nut::SQLocalVarInfo::print(std::ostream& os) const
{
  os << *this->name << ", " << *this->pos << ", " << *this->start_op << ", " << *this->end_op;
}





Nut::SQLineInfo::SQLineInfo(const Object* parent, const std::string& name)
  : SQObjectPtr(parent, "SQLineInfo", name)
{}

Nut::SQLineInfo::~SQLineInfo()
{
  delete this->line;
  delete this->op;
}

bool	Nut::SQLineInfo::readValue(Buffer& buf)
{
  this->line	= ActNut::Object::read<SQInteger>(this, buf, "line");
  this->op	= ActNut::Object::read<SQInteger>(this, buf, "op");
  return true;
}

void	Nut::SQLineInfo::print(std::ostream& os) const
{
  os << *this->line << ", " << *this->op;
}
