#include	"SQFunctionProto.hpp"
#include	"utils.hpp"

SQFunctionProto::SQFunctionProto(const uint8_t*& buf, std::string name)
  : SQObjectPtr("SQFunctionProto", name)
{
  checkTag(buf, 'PART');

  this->sourcename = SQObjectPtr::Load(buf, "sourcename");
  this->name = SQObjectPtr::Load(buf, "name");

  checkTag(buf, 'PART');
  this->nliterals	= new SQInteger(buf, "nliterals");
  this->nparameters	= new SQInteger(buf, "nparameters");
  this->noutervals	= new SQInteger(buf, "noutervals");
  this->nlocalvarinfos	= new SQInteger(buf, "nlocalvarinfos");
  this->nlineinfos	= new SQInteger(buf, "nlineinfos");
  this->ndefaultparams	= new SQInteger(buf, "ndefaultparams");
  this->ninstructions	= new SQInteger(buf, "ninstructions");
  this->nfunctions	= new SQInteger(buf, "nfunctions");

  checkTag(buf, 'PART');
  for (int i = 0; i < *this->nliterals; i++)
    this->literals.push_back(SQObjectPtr::Load(buf));

  checkTag(buf, 'PART');
  for (int i = 0; i < *this->nparameters; i++)
    this->parameters.push_back(SQObjectPtr::Load(buf));

  checkTag(buf, 'PART');
  for (int i = 0; i < *this->noutervals; i++)
    this->outerValues.push_back(new SQOuterVal(buf));

  checkTag(buf, 'PART');
  for (int i = 0; i < *this->nlocalvarinfos; i++)
    this->localVarInfos.push_back(new SQLocalVarInfo(buf));

  checkTag(buf, 'PART');
  for (int i = 0; i < *this->nlineinfos; i++)
    this->lineInfos.push_back(new SQLineInfo(buf));

  checkTag(buf, 'PART');
  for (int i = 0; i < *this->ndefaultparams; i++)
    this->defaultParams.push_back(new SQInteger(buf));

  checkTag(buf, 'PART');
  for (int i = 0; i < *this->ninstructions; i++)
    this->instructions.push_back(new SQInstruction(*this, buf));

  checkTag(buf, 'PART');
  for (int i = 0; i < *this->nfunctions; i++)
    this->functions.push_back(new SQFunctionProto(buf));

  this->stacksize	= new SQInteger(buf, "stacksize");
  this->bgenerator	= new SQSingleByteBoolean(buf, "bgenerator");
  this->varparams	= new SQInteger(buf, "varparams");
}

SQFunctionProto::~SQFunctionProto()
{
  delete this->sourcename;
  delete this->name;
}

void	SQFunctionProto::print(std::ostream& os) const
{
  os << printIndent() << std::endl;
  SQObjectPtr::indentLevel += 1;
  os << *this->sourcename << std::endl;
  os << *this->name << std::endl;

  os << *this->nliterals << std::endl;
  os << *this->nparameters << std::endl;
  os << *this->noutervals << std::endl;
  os << *this->nlocalvarinfos << std::endl;
  os << *this->nlineinfos << std::endl;
  os << *this->ndefaultparams << std::endl;
  os << *this->ninstructions << std::endl;
  os << *this->nfunctions << std::endl;

  os << printIndent(false) << "Literals:" << std::endl << this->literals;
  os << printIndent(false) << "Parameters:" << std::endl << this->parameters;
  os << printIndent(false) << "Outer values:" << std::endl << this->outerValues;
  os << printIndent(false) << "Local variables informations:" << std::endl << this->localVarInfos;
  os << printIndent(false) << "Line informations:" << std::endl << this->lineInfos;
  os << printIndent(false) << "Default parameters:" << std::endl << this->defaultParams;
  os << printIndent(false) << "Instructions:" << std::endl << this->instructions;
  os << printIndent(false) << "Functions:" << std::endl << this->functions;

  os << *this->stacksize << std::endl;
  os << *this->bgenerator << std::endl;
  os << *this->varparams;

  SQObjectPtr::indentLevel -= 1;
}


const SQObjectPtr*	SQFunctionProto::getLiteral(int idx) const
{
  return this->literals[idx];
}
