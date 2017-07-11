#include	"nut/SQInstruction.hpp"
#include	"nut/SQFunctionProto.hpp"

enum	ArgType
  {
    ARG_STACK,
    ARG_LITERAL,
    ARG_IMMEDIATE,
    ARG_UNKNOWN
  };

struct	OpcodeDescriptor
{
  const char*	name;
  ArgType	arg0;
  ArgType	arg1;
  ArgType	arg2;
  ArgType	arg3;
};

static std::vector<OpcodeDescriptor>	opcodes = {
  { "line",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "load",		ARG_STACK,	ARG_LITERAL,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "loadint",		ARG_STACK,	ARG_IMMEDIATE,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "loadfloat",	ARG_STACK,	ARG_IMMEDIATE,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "dload",		ARG_STACK,	ARG_LITERAL,	ARG_STACK,	ARG_LITERAL },
  { "tailcall",		ARG_UNKNOWN,	ARG_STACK,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "call",		ARG_UNKNOWN,	ARG_STACK,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "prepcall",		ARG_UNKNOWN,	ARG_STACK,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "prepcallk",	ARG_UNKNOWN,	ARG_LITERAL,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "getk",		ARG_UNKNOWN,	ARG_LITERAL,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "move",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "newslot",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "delete",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "set",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "get",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "eq",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "ne",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "add",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "sub",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "mul",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "div",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "mod",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "bitw",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "return",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "loadnulls",	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "loadroot",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "loadbool",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "dmove",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "jmp",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "jcmp",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "jz",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "setouter",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "getouter",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "newobj",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "appendarray",	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "comparith",	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "inc",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "incl",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "pinc",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "pincl",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "cmp",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "exists",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "instanceof",	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "and",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "or",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "neg",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "not",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "bwnot",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "closure",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "yield",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "resume",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "foreach",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "postforeach",	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "clone",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "typeof",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "pushtrap",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "poptrap",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "throw",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "newslota",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "getbase",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "close",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_UNKNOWN }
};

Nut::SQInstruction::SQInstruction(const Object* parent, const std::string& name)
  : SQObjectPtr(parent, "SQInstruction", name), func(dynamic_cast<const SQFunctionProto&>(*parent->getParent()))
{}

bool	Nut::SQInstruction::readValue(IBuffer& buf)
{
  this->arg1 = ActNut::Object::read<SQInteger>(this, buf, "arg1");
  this->op   = buf.readByte();
  this->arg0 = buf.readByte();
  this->arg2 = buf.readByte();
  this->arg3 = buf.readByte();
  return true;
}

Nut::SQInstruction::~SQInstruction()
{
  delete this->arg1;
}

void	Nut::SQInstruction::print(std::ostream& os) const
{
  OpcodeDescriptor& op = opcodes[this->op];

  os << " " << op.name << "(";
  // Remove the indent level for a nice result when displaying objects here.
  if (op.arg0 == ARG_LITERAL) func.getLiteral(arg0)->print(os) ; else os << (int)arg0 ; os << ", ";
  if (op.arg1 == ARG_LITERAL) func.getLiteral(*arg1)->print(os); else os << (int)*arg1; os << ", ";
  if (op.arg2 == ARG_LITERAL) func.getLiteral(arg2)->print(os) ; else os << (int)arg2 ; os << ", ";
  if (op.arg3 == ARG_LITERAL) func.getLiteral(arg3)->print(os) ; else os << (int)arg3 ; os << ")";
}

bool	Nut::SQInstruction::writeValue(IBuffer& buf) const
{
  this->arg1->writeValue(buf);
  buf.writeByte(this->op);
  buf.writeByte(this->arg0);
  buf.writeByte(this->arg2);
  buf.writeByte(this->arg3);
  return true;
}
