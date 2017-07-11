#include	"nut/SQComplexObjects.hpp"

Nut::SQOuterType::SQOuterType(const Object* parent, const std::string& name)
  : Number(parent, "SQOuterType", name, 0xFFFFFFFF)
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

bool	Nut::SQOuterVal::readValue(IBuffer& buf)
{
  this->type   = ActNut::Object::read<SQOuterType>(this, buf, "type");
  this->object = loadObject(this, buf, "object");
  this->name   = loadObject(this, buf, "name");
  addMember(this->type);
  addMember(this->object);
  addMember(this->name);
  return true;
}

void	Nut::SQOuterVal::print(std::ostream& os) const
{
  os << *this->type << ", " << *this->object << ", " << *this->name;
}

bool	Nut::SQOuterVal::writeValue(IBuffer& buf) const
{
  this->type->writeValue(buf);
  writeObject(buf, this->object);
  writeObject(buf, this->name);
  return true;
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

bool	Nut::SQLocalVarInfo::readValue(IBuffer& buf)
{
  this->name	= loadObject(this, buf, "name");
  this->pos	= ActNut::Object::read<SQUnsignedInteger>(this, buf, "pos");
  this->start_op= ActNut::Object::read<SQUnsignedInteger>(this, buf, "start_op");
  this->end_op	= ActNut::Object::read<SQUnsignedInteger>(this, buf, "end_op");
  addMember(this->name);
  addMember(this->pos);
  addMember(this->start_op);
  addMember(this->end_op);
  return true;
}

void	Nut::SQLocalVarInfo::print(std::ostream& os) const
{
  os << *this->name << ", " << *this->pos << ", " << *this->start_op << ", " << *this->end_op;
}

bool	Nut::SQLocalVarInfo::writeValue(IBuffer& buf) const
{
  writeObject(buf, this->name);
  this->pos->writeValue(buf);
  this->start_op->writeValue(buf);
  this->end_op->writeValue(buf);
  return true;
}




Nut::SQLineInfo::SQLineInfo(const Object* parent, const std::string& name)
  : SQObjectPtr(parent, "SQLineInfo", name)
{}

Nut::SQLineInfo::~SQLineInfo()
{
  delete this->line;
  delete this->op;
}

bool	Nut::SQLineInfo::readValue(IBuffer& buf)
{
  this->line	= ActNut::Object::read<SQInteger>(this, buf, "line");
  this->op	= ActNut::Object::read<SQInteger>(this, buf, "op");
  addMember(this->line);
  addMember(this->op);
  return true;
}

void	Nut::SQLineInfo::print(std::ostream& os) const
{
  os << *this->line << ", " << *this->op;
}

bool	Nut::SQLineInfo::writeValue(IBuffer& buf) const
{
  this->line->writeValue(buf);
  this->op->writeValue(buf);
  return true;
}
