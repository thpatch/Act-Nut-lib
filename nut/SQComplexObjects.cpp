#include	"SQComplexObjects.hpp"
#include	"utils.hpp"

void	SQOuterType::print(std::ostream& os) const
{
  os << printIndent() << "SQOuterType:" << (this->n ? "otOUTER" : "otLOCAL") << std::endl;
}

SQOuterVal::SQOuterVal(const uint8_t*& buf, std::string name)
  : SQObjectPtr("SQOuterVal", name)
{
  this->type = new SQOuterType(buf, "type");
  this->object = SQObjectPtr::Load(buf, "object");
  this->name = SQObjectPtr::Load(buf, "name");
}

SQOuterVal::~SQOuterVal()
{
  delete this->type;
  delete this->object;
  delete this->name;
}

void	SQOuterVal::print(std::ostream& os) const
{
  os << printIndent() << std::endl;
  SQObjectPtr::indentLevel += 1;
  os << *this->type << std::endl;
  os << *this->object << std::endl;
  os << *this->name;
  SQObjectPtr::indentLevel -= 1;
}





SQLocalVarInfo::SQLocalVarInfo(const uint8_t*& buf, std::string name)
  : SQObjectPtr("SQLocalVarInfo", name)
{
  this->name	= SQObjectPtr::Load(buf, "name");
  this->pos	= new SQUnsignedInteger(buf, "pos");
  this->start_op= new SQUnsignedInteger(buf, "start_op");
  this->end_op	= new SQUnsignedInteger(buf, "end_op");
}

SQLocalVarInfo::~SQLocalVarInfo()
{
  delete this->name;
  delete this->pos;
  delete this->start_op;
  delete this->end_op;
}

void	SQLocalVarInfo::print(std::ostream& os) const
{
  os << printIndent() << std::endl;
  SQObjectPtr::indentLevel += 1;
  os << *this->name << std::endl;
  os << *this->pos << std::endl;
  os << *this->start_op << std::endl;
  os << *this->end_op;
  SQObjectPtr::indentLevel -= 1;
}





SQLineInfo::SQLineInfo(const uint8_t*& buf, std::string name)
  : SQObjectPtr("SQLineInfo", name)
{
  this->line = new SQInteger(buf, "line");
  this->op = new SQInteger(buf, "op");
}

SQLineInfo::~SQLineInfo()
{
  delete this->line;
  delete this->op;
}

void	SQLineInfo::print(std::ostream& os) const
{
  os << printIndent() << std::endl;
  SQObjectPtr::indentLevel += 1;
  os << *this->line << std::endl;
  os << *this->op;
  SQObjectPtr::indentLevel -= 1;
}
