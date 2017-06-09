#include	<nut/SQComplexObjects.hpp>

void	Nut::SQOuterType::print(std::ostream& os) const
{
  os << printIndent() << "SQOuterType:" << (this->n ? "otOUTER" : "otLOCAL") << std::endl;
}

Nut::SQOuterVal::SQOuterVal(Buffer& buf, std::string name)
  : SQObjectPtr("SQOuterVal", name)
{
  this->type = new SQOuterType(buf, "type");
  this->object = SQObjectPtr::Load(buf, "object");
  this->name = SQObjectPtr::Load(buf, "name");
}

Nut::SQOuterVal::~SQOuterVal()
{
  delete this->type;
  delete this->object;
  delete this->name;
}

void	Nut::SQOuterVal::print(std::ostream& os) const
{
  os << printIndent() << std::endl;
  SQObjectPtr::indentLevel += 1;
  os << *this->type << std::endl;
  os << *this->object << std::endl;
  os << *this->name;
  SQObjectPtr::indentLevel -= 1;
}





Nut::SQLocalVarInfo::SQLocalVarInfo(Buffer& buf, std::string name)
  : SQObjectPtr("SQLocalVarInfo", name)
{
  this->name	= SQObjectPtr::Load(buf, "name");
  this->pos	= new SQUnsignedInteger(buf, "pos");
  this->start_op= new SQUnsignedInteger(buf, "start_op");
  this->end_op	= new SQUnsignedInteger(buf, "end_op");
}

Nut::SQLocalVarInfo::~SQLocalVarInfo()
{
  delete this->name;
  delete this->pos;
  delete this->start_op;
  delete this->end_op;
}

void	Nut::SQLocalVarInfo::print(std::ostream& os) const
{
  os << printIndent() << std::endl;
  SQObjectPtr::indentLevel += 1;
  os << *this->name << std::endl;
  os << *this->pos << std::endl;
  os << *this->start_op << std::endl;
  os << *this->end_op;
  SQObjectPtr::indentLevel -= 1;
}





Nut::SQLineInfo::SQLineInfo(Buffer& buf, std::string name)
  : SQObjectPtr("SQLineInfo", name)
{
  this->line = new SQInteger(buf, "line");
  this->op = new SQInteger(buf, "op");
}

Nut::SQLineInfo::~SQLineInfo()
{
  delete this->line;
  delete this->op;
}

void	Nut::SQLineInfo::print(std::ostream& os) const
{
  os << printIndent() << std::endl;
  SQObjectPtr::indentLevel += 1;
  os << *this->line << std::endl;
  os << *this->op;
  SQObjectPtr::indentLevel -= 1;
}
