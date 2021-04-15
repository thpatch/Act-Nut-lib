#include	"nut/SQInstruction.hpp"
#include	"nut/SQFunctionProto.hpp"

enum	ArgType
  {
    ARG_NONE		= 0x00,
    ARG_STACK		= 0x01,
    ARG_LITERAL		= 0x02,
    ARG_IMMEDIATE	= 0x04,
    ARG_UNKNOWN		= 0x04, // Just display its value

    MASK_FLOAT		= 0x10,
    MASK_CMP		= 0x20,
    MASK_BITWISE	= 0x40,

    ARG_FLOAT		= ARG_IMMEDIATE | MASK_FLOAT,
    ARG_CMP		= ARG_IMMEDIATE | MASK_CMP,
    ARG_BITWISE		= ARG_IMMEDIATE | MASK_BITWISE
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
  { "line",		ARG_NONE,	ARG_IMMEDIATE,	ARG_NONE,	ARG_NONE },
  { "load",		ARG_STACK,	ARG_LITERAL,	ARG_NONE,	ARG_NONE },
  { "loadint",		ARG_STACK,	ARG_IMMEDIATE,	ARG_NONE,	ARG_NONE },
  { "loadfloat",	ARG_STACK,	ARG_FLOAT,	ARG_NONE,	ARG_NONE },
  { "dload",		ARG_STACK,	ARG_LITERAL,	ARG_STACK,	ARG_LITERAL },
  { "tailcall",		ARG_UNKNOWN,	ARG_STACK,	ARG_STACK,	ARG_IMMEDIATE },
  { "call",		ARG_UNKNOWN,	ARG_STACK,	ARG_STACK,	ARG_UNKNOWN },
  { "prepcall",		ARG_STACK,	ARG_STACK,	ARG_STACK,	ARG_STACK },
  { "prepcallk",	ARG_STACK,	ARG_LITERAL,	ARG_STACK,	ARG_STACK },
  { "getk",		ARG_STACK,	ARG_LITERAL,	ARG_STACK,	ARG_NONE },
  { "move",		ARG_STACK,	ARG_STACK,	ARG_NONE,	ARG_NONE },
  { "newslot",		ARG_STACK,	ARG_STACK,	ARG_STACK,	ARG_STACK },
  { "delete",		ARG_STACK,	ARG_STACK,	ARG_STACK,	ARG_NONE },
  { "set",		ARG_STACK,	ARG_STACK,	ARG_STACK,	ARG_STACK },
  { "get",		ARG_STACK,	ARG_STACK,	ARG_STACK,	ARG_NONE },
  { "eq",		ARG_STACK,	ARG_UNKNOWN,	ARG_STACK,	ARG_IMMEDIATE },
  { "ne",		ARG_STACK,	ARG_UNKNOWN,	ARG_STACK,	ARG_IMMEDIATE },
  { "add",		ARG_STACK,	ARG_STACK,	ARG_STACK,	ARG_NONE },
  { "sub",		ARG_STACK,	ARG_STACK,	ARG_STACK,	ARG_NONE },
  { "mul",	        ARG_STACK,	ARG_STACK,	ARG_STACK,	ARG_NONE },
  { "div",	        ARG_STACK,	ARG_STACK,	ARG_STACK,	ARG_NONE },
  { "mod",	        ARG_STACK,	ARG_STACK,	ARG_STACK,	ARG_NONE },
  { "bitw",	        ARG_STACK,	ARG_STACK,	ARG_STACK,	ARG_BITWISE },
  { "return",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_NONE,	ARG_NONE },
  { "loadnulls",	ARG_STACK,	ARG_IMMEDIATE,	ARG_NONE,	ARG_NONE },
  { "loadroot",		ARG_STACK,	ARG_NONE,	ARG_NONE,	ARG_NONE },
  { "loadbool",		ARG_STACK,	ARG_IMMEDIATE,	ARG_NONE,	ARG_NONE },
  { "dmove",		ARG_STACK,	ARG_STACK,	ARG_STACK,	ARG_STACK },
  { "jmp",		ARG_NONE,	ARG_IMMEDIATE,	ARG_NONE,	ARG_NONE },
  { "jcmp",		ARG_STACK,	ARG_IMMEDIATE,	ARG_STACK,	ARG_CMP },
  { "jz",		ARG_STACK,	ARG_IMMEDIATE,	ARG_NONE,	ARG_NONE },
  { "setouter",		ARG_STACK,	ARG_IMMEDIATE,	ARG_STACK,	ARG_NONE },
  { "getouter",		ARG_STACK,	ARG_IMMEDIATE,	ARG_NONE,	ARG_NONE },
  { "newobj",		ARG_STACK,	ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_IMMEDIATE /* enum NewObjectType */ },
  { "appendarray",	ARG_STACK,	ARG_UNKNOWN,	ARG_IMMEDIATE,	ARG_NONE },
  { "comparith",	ARG_STACK,	ARG_UNKNOWN,	ARG_STACK,	ARG_UNKNOWN },
  { "inc",		ARG_STACK,	ARG_STACK,	ARG_STACK,	ARG_UNKNOWN },
  { "incl",		ARG_UNKNOWN,	ARG_STACK,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "pinc",		ARG_STACK,	ARG_STACK,	ARG_STACK,	ARG_UNKNOWN },
  { "pincl",		ARG_STACK,	ARG_STACK,	ARG_UNKNOWN,	ARG_UNKNOWN },
  { "cmp",		ARG_STACK,	ARG_STACK,	ARG_STACK,	ARG_CMP },
  { "exists",		ARG_STACK,	ARG_STACK,	ARG_STACK,	ARG_NONE },
  { "instanceof",	ARG_STACK,	ARG_STACK,	ARG_STACK,	ARG_NONE },
  { "and",		ARG_STACK,	ARG_UNKNOWN,	ARG_STACK,	ARG_NONE },
  { "or",		ARG_STACK,	ARG_UNKNOWN,	ARG_STACK,	ARG_NONE },
  { "neg",		ARG_STACK,	ARG_STACK,	ARG_NONE,	ARG_NONE },
  { "not",		ARG_STACK,	ARG_STACK,	ARG_NONE,	ARG_NONE },
  { "bwnot",		ARG_STACK,	ARG_STACK,	ARG_NONE,	ARG_NONE },
  { "closure",		ARG_STACK,	ARG_IMMEDIATE,	ARG_NONE,	ARG_NONE },
  { "yield",		ARG_UNKNOWN,	ARG_STACK,	ARG_UNKNOWN,	ARG_NONE },
  { "resume",		ARG_STACK,	ARG_STACK,	ARG_NONE,	ARG_NONE },
  { "foreach",		ARG_STACK,	ARG_STACK,	ARG_STACK,	ARG_NONE },
  { "postforeach",	ARG_STACK,	ARG_UNKNOWN,	ARG_NONE,	ARG_NONE },
  { "clone",		ARG_STACK,	ARG_STACK,	ARG_NONE,	ARG_NONE },
  { "typeof",		ARG_STACK,	ARG_STACK,	ARG_NONE,	ARG_NONE },
  { "pushtrap",		ARG_UNKNOWN,	ARG_UNKNOWN,	ARG_NONE,	ARG_NONE },
  { "poptrap",		ARG_IMMEDIATE,	ARG_NONE,	ARG_NONE,	ARG_NONE },
  { "throw",		ARG_STACK,	ARG_NONE,	ARG_NONE,	ARG_NONE },
  { "newslota",		ARG_UNKNOWN,	ARG_STACK,	ARG_STACK,	ARG_STACK },
  { "getbase",		ARG_STACK,	ARG_NONE,	ARG_NONE,	ARG_NONE },
  { "close",		ARG_NONE,	ARG_STACK,	ARG_NONE,	ARG_NONE }
};

/*
0x00 line: line number in the source file. Used only for debugging.
0x01 load: load the literal arg1 into arg0.
0x02 loadint: load the integer arg1 into arg0.
0x03 loadfloat: load the float arg1 into arg0.
0x04 dload: double load. Load the literal arg1 into arg0, and load the literal arg3 into arg2.
0x05 tailcall
0x06 call
0x07 prepcall
0x08 prepcallk: like prepcall, but arg1 is a literal.
0x09 getk: get a member (arg2) in the object arg1, and store it in arg0.
0x0a move: arg0 = arg1;
0x0b newslot
0x0c delete: delete a slot.
0x0d set
0x0e get
0x0f eq: test if arg1 == arg2. If arg3 is not 0, arg1 is a literal, otherwise it is a stack value.
0x10 ne: test if arg1 != arg2. If arg3 is not 0, arg1 is a literal, otherwise it is a stack value.
0x11 add: arg0 = arg2 + arg1
0x12 sub: arg0 = arg2 - arg1
0x13 mul: arg0 = arg2 * arg1
0x14 div: arg0 = arg2 / arg1
0x15 mod: arg0 = arg2 % arg1
0x16 bitw: bitwise operation: arg0 = arg2 op arg1. Op is arg3 and can be &, |, ^, <<, >> or an unsigned >>.
0x17 return
0x18 loadnulls: set the stack entries arg0 to arg0+arg1 to null.
0x19 loadroot
0x1a loadbool: load the boolean arg1 into arg0
0x1b dmove: double move. arg0 = arg1; arg2 = arg3;
0x1c jmp: skip arg1 instructions.
0x1d jcmp: skip arg1 instructions if arg0 op arg2. Op is arg3 and can be >, >=, <, <= or... something called 3W.
0x1e jz: skip arg1 instructions if arg0 is zero.
0x1f setouter: set the outer value pointed by arg1 to arg2. Also set arg0 to arg2.
0x20 getouter: load the outer value pointed by arg1 into arg0.
0x21 newobj
0x22 appendarray: append arg1 (whose type is in the enum AppendArrayType arg2) to the array in arg0.
0x23 comparith
0x24 inc
0x25 incl
0x26 pinc: post incrementation
0x27 pincl
0x28 cmp
0x29 exists
0x2a instanceof
0x2b and
0x2c or
0x2d neg
0x2e not
0x2f bwnot
0x30 closure
0x31 yield
0x32 resume
0x33 foreach
0x34 postforeach
0x35 clone
0x36 typeof
0x37 pushtrap
0x38 poptrap
0x39 throw
0x3a newslota
0x3b getbase
0x3c close
*/

Nut::SQInstruction::SQInstruction(const Object* parent, const std::string& name)
  : SQObjectPtr(parent, "SQInstruction", name), func(dynamic_cast<const SQFunctionProto&>(*parent->getParent())),
    opWrapper(  this,                           "op",   this->op),
    arg0Wrapper(this, "NativeWrapper<uint8_t>", "arg0", this->arg0),
    arg1Wrapper(this, "NativeWrapper<int32_t>", "arg1", this->arg1),
    arg2Wrapper(this, "NativeWrapper<uint8_t>", "arg2", this->arg2),
    arg3Wrapper(this, "NativeWrapper<uint8_t>", "arg3", this->arg3)
{}

bool	Nut::SQInstruction::readValue(IBuffer& buf)
{
  buf.readBytes((uint8_t*)&this->arg1, sizeof(this->arg1));
  this->op   = buf.readByte();
  this->arg0 = buf.readByte();
  this->arg2 = buf.readByte();
  this->arg3 = buf.readByte();
  return true;
}

Nut::SQInstruction::~SQInstruction()
{}

static void	printArgument(const Nut::SQFunctionProto& func, std::ostream& os, ArgType type, int arg)
{
  if (type == ARG_NONE)
    os << "-";
  else if (type & ARG_STACK)
    os << "s" << arg;
  else if (type & ARG_LITERAL)
    func.getLiteral(arg)->print(os);
  else if (type & ARG_IMMEDIATE)
    {
      if (type & MASK_FLOAT)
	{
	  float f;
	  memcpy(&f, &arg, 4);
	  os << f;
	}
      else if (type & MASK_CMP)
	{
	  const char *names[] = {
	    "CMP_G",
	    nullptr,
	    "CMP_GE",
	    "CMP_L",
	    "CMP_LE",
	    "CMP_3W"
	  };
	  const char* name = "UNKNOWN";
	  if (arg >= 0 && arg <= 5 && names[arg])
	    name = names[arg];
	  os << name;
	}
      else if (type & MASK_BITWISE)
	{
	  const char *names[] = {
	    "BW_AND",
	    nullptr,
	    "BW_OR",
	    "BW_XOR",
	    "BW_SHIFTL",
	    "BW_SHIFTR",
	    "BW_USHIFTR"
	  };
	  const char* name = "UNKNOWN";
	  if (arg >= 0 && arg <= 6 && names[arg])
	    name = names[arg];
	  os << name;
	}
      else
	os << arg;
    }
  else
    throw std::logic_error("SQInstruction.cpp: the opcodes array contain an invalid value.");
}

void	Nut::SQInstruction::print(std::ostream& os) const
{
  OpcodeDescriptor& op = opcodes[this->op];
  int nb_args;
  if (op.arg3 != ARG_NONE)
    nb_args = 4;
  else if (op.arg2 != ARG_NONE)
    nb_args = 3;
  else if (op.arg1 != ARG_NONE)
    nb_args = 2;
  else if (op.arg0 != ARG_NONE)
    nb_args = 1;
  else
    nb_args = 0;

  os << " " << op.name << "(";
  if (nb_args >= 1)
      printArgument(this->func, os, op.arg0, arg0);
  if (nb_args >= 2)
    {
      std::cout << ", ";
      printArgument(this->func, os, op.arg1, arg1);
    }
  if (nb_args >= 3)
    {
      std::cout << ", ";
      printArgument(this->func, os, op.arg2, arg2);
    }
  if (nb_args >= 4)
    {
      std::cout << ", ";
      printArgument(this->func, os, op.arg3, arg3);
    }
  os << ")";
}

bool	Nut::SQInstruction::writeValue(IBuffer& buf) const
{
  buf.writeBytes((uint8_t*)&this->arg1, sizeof(this->arg1));
  buf.writeByte(this->op);
  buf.writeByte(this->arg0);
  buf.writeByte(this->arg2);
  buf.writeByte(this->arg3);
  return true;
}

ActNut::Object*	Nut::SQInstruction::operator[](const char* key)
{
  switch (key[0])
    {
    case '0':
      return &this->opWrapper;
    case '1':
      return &this->arg0Wrapper;
    case '2':
      return &this->arg1Wrapper;
    case '3':
      return &this->arg2Wrapper;
    case '4':
      return &this->arg3Wrapper;
    default:
      return nullptr;
    }
}

const ActNut::Object*	Nut::SQInstruction::operator[](const char* key) const
{
  switch (key[0])
    {
    case '0':
      return &this->opWrapper;
    case '1':
      return &this->arg0Wrapper;
    case '2':
      return &this->arg1Wrapper;
    case '3':
      return &this->arg2Wrapper;
    case '4':
      return &this->arg3Wrapper;
    default:
      return nullptr;
    }
}

Nut::SQInstruction::OpWrapper::OpWrapper(const Object* parent, const std::string& name, uint8_t& ref)
  : Number(parent, "OpWrapper", name, ref)
{}

const ActNut::Object&	Nut::SQInstruction::OpWrapper::operator=(const std::string& new_value)
{
  // Try instructions list
  for (uint8_t i = 0; i < opcodes.size(); i++)
    if (new_value == opcodes[i].name)
      {
	this->n = i;
	return *this;
      }
  return this->Number::operator=(new_value);
}

int32_t	Nut::SQInstruction::parseArgument(const std::string& argument)
{
  size_t pos;

  // Try as a string literal
  pos = argument.find('"');
  if (pos != std::string::npos)
    {
      size_t end = argument.find('"', pos + 1);
      if (end != std::string::npos)
	{
	  std::string argContent = argument.substr(pos + 1, end - pos - 1);
	  int idx = this->func.getLiteralIdx(argContent);
	  if (idx != -1)
	    return idx;
	}
    }

  // Try as a stack index
  pos = argument.find('s');
  if (pos != std::string::npos)
    return atoi(argument.c_str() + pos + 1);


  // Try as a float
  pos = argument.find('.');
  if (pos != std::string::npos)
    {
      float f = static_cast<float>(atof(argument.c_str()));
      float *fp = &f;
      return *(int32_t*)fp;
    }

  // Try as an int (with hex support)
  return strtol(argument.c_str(), nullptr, 0);
}

const ActNut::Object&	Nut::SQInstruction::operator=(const std::string& new_value)
{
  std::vector<std::string>      values;
  std::string			arguments;
  size_t pos;

  pos = new_value.find('(');
  if (pos == std::string::npos)
    {
      Error::error("Invalid value for SQInstruction::operator= : missing '('");
      return *this;
    }
  values.push_back(new_value.substr(0, pos));
  arguments = new_value.substr(pos + 1);
  pos = arguments.find(')');
  if (pos == std::string::npos)
    {
      Error::error("Invalid value for SQInstruction::operator= : missing ')'");
      return *this;
    }
  arguments = arguments.substr(0, pos);

  if (arguments.length() > 0)
    {
      while ((pos = arguments.find(',')) != std::string::npos)
	{
	  values.push_back(arguments.substr(0, pos));
	  arguments = arguments.substr(pos + 1);
	}
      values.push_back(arguments);
    }
  if (values.size() > 5)
    {
      Error::error("Invalid value for SQInstruction::operator= : too many arguments (4 maximum)");
      return *this;
    }

  this->opWrapper = values[0];
  if (values.size() >= 2) this->arg0Wrapper = parseArgument(values[1]);
  if (values.size() >= 3) this->arg1Wrapper = parseArgument(values[2]);
  if (values.size() >= 4) this->arg2Wrapper = parseArgument(values[3]);
  if (values.size() >= 5) this->arg3Wrapper = parseArgument(values[4]);

  return *this;
}
