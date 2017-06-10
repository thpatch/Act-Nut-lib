#include	<nut/SQFunctionProto.hpp>

Nut::SQFunctionProto::SQFunctionProto(const Object* parent, std::string name)
  : SQObjectPtr(parent, "SQFunctionProto", name), literals(this, "Literals"), parameters(this, "Parameters"),
    outerValues(this, "Outer Values"), localVarInfos(this, "Local variables informations"), lineInfos(this, "Line Informations"),
    defaultParams(this, "Default Parameters"), instructions(this, "Instructions"), functions(this, "Functions")
{}

Nut::SQFunctionProto::~SQFunctionProto()
{
  delete this->sourcename;
  delete this->name;

  delete this->nliterals;
  delete this->nparameters;
  delete this->noutervals;
  delete this->nlocalvarinfos;
  delete this->nlineinfos;
  delete this->ndefaultparams;
  delete this->ninstructions;
  delete this->nfunctions;

  delete this->stacksize;
  delete this->bgenerator;
  delete this->varparams;
}

bool	Nut::SQFunctionProto::readValue(Buffer& buf)
{
  buf.checkTag('PART');

  this->sourcename = SQObjectPtr::Load(this, buf, "sourcename");
  this->name       = SQObjectPtr::Load(this, buf, "name");

  buf.checkTag('PART');
  this->nliterals	= ActNut::Object::read<SQInteger>(this, buf, "nliterals");
  this->nparameters	= ActNut::Object::read<SQInteger>(this, buf, "nparameters");
  this->noutervals	= ActNut::Object::read<SQInteger>(this, buf, "noutervals");
  this->nlocalvarinfos	= ActNut::Object::read<SQInteger>(this, buf, "nlocalvarinfos");
  this->nlineinfos	= ActNut::Object::read<SQInteger>(this, buf, "nlineinfos");
  this->ndefaultparams	= ActNut::Object::read<SQInteger>(this, buf, "ndefaultparams");
  this->ninstructions	= ActNut::Object::read<SQInteger>(this, buf, "ninstructions");
  this->nfunctions	= ActNut::Object::read<SQInteger>(this, buf, "nfunctions");

  buf.checkTag('PART');
  for (int i = 0; i < *this->nliterals; i++)
    this->literals.push_back(SQObjectPtr::Load(this, buf));

  buf.checkTag('PART');
  for (int i = 0; i < *this->nparameters; i++)
    this->parameters.push_back(SQObjectPtr::Load(this, buf));

  buf.checkTag('PART');
  for (int i = 0; i < *this->noutervals; i++)
    this->outerValues.push_back(ActNut::Object::read<SQOuterVal>(this, buf));

  buf.checkTag('PART');
  for (int i = 0; i < *this->nlocalvarinfos; i++)
    this->localVarInfos.push_back(ActNut::Object::read<SQLocalVarInfo>(this, buf));

  buf.checkTag('PART');
  for (int i = 0; i < *this->nlineinfos; i++)
    this->lineInfos.push_back(ActNut::Object::read<SQLineInfo>(this, buf));

  buf.checkTag('PART');
  for (int i = 0; i < *this->ndefaultparams; i++)
    this->defaultParams.push_back(ActNut::Object::read<SQInteger>(this, buf));

  buf.checkTag('PART');
  for (int i = 0; i < *this->ninstructions; i++)
    this->instructions.push_back(ActNut::Object::read<SQInstruction>(this, buf));

  buf.checkTag('PART');
  for (int i = 0; i < *this->nfunctions; i++)
    this->functions.push_back(ActNut::Object::read<SQFunctionProto>(this, buf));

  this->stacksize	= ActNut::Object::read<SQInteger>          (this, buf, "stacksize");
  this->bgenerator	= ActNut::Object::read<SQSingleByteBoolean>(this, buf, "bgenerator");
  this->varparams	= ActNut::Object::read<SQInteger>          (this, buf, "varparams");

  return true;
}

void	Nut::SQFunctionProto::print(std::ostream& os) const
{
  os << *this->sourcename << std::endl;
  os << printIndent() << *this->name << std::endl;

  os << printIndent() << *this->nliterals << std::endl;
  os << printIndent() << *this->nparameters << std::endl;
  os << printIndent() << *this->noutervals << std::endl;
  os << printIndent() << *this->nlocalvarinfos << std::endl;
  os << printIndent() << *this->nlineinfos << std::endl;
  os << printIndent() << *this->ndefaultparams << std::endl;
  os << printIndent() << *this->ninstructions << std::endl;
  os << printIndent() << *this->nfunctions << std::endl;

  os << printIndent() << this->literals;
  os << printIndent() << this->parameters;
  os << printIndent() << this->outerValues;
  os << printIndent() << this->localVarInfos;
  os << printIndent() << this->lineInfos;
  os << printIndent() << this->defaultParams;
  os << printIndent() << this->instructions;
  os << printIndent() << this->functions;

  os << printIndent() << *this->stacksize << std::endl;
  os << printIndent() << *this->bgenerator << std::endl;
  os << printIndent() << *this->varparams << std::endl;
}


const ActNut::Object*	Nut::SQFunctionProto::getLiteral(int idx) const
{
  return this->literals[idx];
}
