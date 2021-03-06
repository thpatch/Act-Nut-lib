#include	"nut/SQFunctionProto.hpp"

Nut::SQFunctionProto::SQFunctionProto(const Object* parent, const std::string& name)
  : SQObjectPtr(parent, "SQFunctionProto", name),
    sourcename(nullptr), name(nullptr), nliterals(nullptr), nparameters(nullptr), noutervals(nullptr),
    nlocalvarinfos(nullptr), nlineinfos(nullptr), ndefaultparams(nullptr), ninstructions(nullptr), nfunctions(nullptr),
    literals(this, "Literals"), parameters(this, "Parameters"),
    outerValues(this, "Outer Values"), localVarInfos(this, "Local variables informations"), lineInfos(this, "Line Informations"),
    defaultParams(this, "Default Parameters"), instructions(this, "Instructions"), functions(this, "Functions"),
    stacksize(nullptr), bgenerator(nullptr), varparams(nullptr)
{
  addMember(&literals);
  addMember(&parameters);
  addMember(&outerValues);
  addMember(&localVarInfos);
  addMember(&lineInfos);
  addMember(&defaultParams);
  addMember(&instructions);
  addMember(&functions);
}

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

bool	Nut::SQFunctionProto::readValue(IBuffer& buf)
{
  buf.checkTag('PART', "PART tag");

  this->sourcename = loadObject(this, buf, "sourcename");
  this->name       = loadObject(this, buf, "name");
  addMember(sourcename);
  addMember(name);

  buf.checkTag('PART', "PART tag");
  this->nliterals	= ActNut::Object::read<SQInteger>(this, buf, "nliterals");
  this->nparameters	= ActNut::Object::read<SQInteger>(this, buf, "nparameters");
  this->noutervals	= ActNut::Object::read<SQInteger>(this, buf, "noutervals");
  this->nlocalvarinfos	= ActNut::Object::read<SQInteger>(this, buf, "nlocalvarinfos");
  this->nlineinfos	= ActNut::Object::read<SQInteger>(this, buf, "nlineinfos");
  this->ndefaultparams	= ActNut::Object::read<SQInteger>(this, buf, "ndefaultparams");
  this->ninstructions	= ActNut::Object::read<SQInteger>(this, buf, "ninstructions");
  this->nfunctions	= ActNut::Object::read<SQInteger>(this, buf, "nfunctions");

  this->readArray(Nut::loadObject,                       buf, this->literals,      this->nliterals);
  this->readArray(Nut::loadObject,                       buf, this->parameters,    this->nparameters);
  this->readArray(ActNut::Object::read<SQOuterVal>,      buf, this->outerValues,   this->noutervals);
  this->readArray(ActNut::Object::read<SQLocalVarInfo>,  buf, this->localVarInfos, this->nlocalvarinfos);
  this->readArray(ActNut::Object::read<SQLineInfo>,      buf, this->lineInfos,     this->nlineinfos);
  this->readArray(ActNut::Object::read<SQInteger>,       buf, this->defaultParams, this->ndefaultparams);
  this->readArray(ActNut::Object::read<SQInstruction>,   buf, this->instructions,  this->ninstructions);
  this->readArray(ActNut::Object::read<SQFunctionProto>, buf, this->functions,     this->nfunctions);

  this->stacksize	= ActNut::Object::read<SQInteger>          (this, buf, "stacksize");
  this->bgenerator	= ActNut::Object::read<SQSingleByteBoolean>(this, buf, "bgenerator");
  this->varparams	= ActNut::Object::read<SQInteger>          (this, buf, "varparams");
  addMember(stacksize);
  addMember(bgenerator);
  addMember(varparams);

  return true;
}

void	Nut::SQFunctionProto::print(std::ostream& os) const
{
  os << std::endl << printIndent() << *this->sourcename << std::endl;
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

bool	Nut::SQFunctionProto::writeValue(IBuffer& buf) const
{
  buf.writeInt('PART');

  writeObject(buf, this->sourcename);
  writeObject(buf, this->name);

  buf.writeInt('PART');
  this->nliterals->writeValue(buf);
  this->nparameters->writeValue(buf);
  this->noutervals->writeValue(buf);
  this->nlocalvarinfos->writeValue(buf);
  this->nlineinfos->writeValue(buf);
  this->ndefaultparams->writeValue(buf);
  this->ninstructions->writeValue(buf);
  this->nfunctions->writeValue(buf);

  this->writeArrayOfObjects(buf, this->literals);
  this->writeArrayOfObjects(buf, this->parameters);
  this->writeArray(         buf, this->outerValues);
  this->writeArray(         buf, this->localVarInfos);
  this->writeArray(         buf, this->lineInfos);
  this->writeArray(         buf, this->defaultParams);
  this->writeArray(         buf, this->instructions);
  this->writeArray(         buf, this->functions);

  this->stacksize->writeValue(buf);
  this->bgenerator->writeValue(buf);
  this->varparams->writeValue(buf);

  return true;
}

bool	Nut::SQFunctionProto::writeArray(IBuffer& buf, const vector& array) const
{
  buf.writeInt('PART');
  for (const Object* it : array)
    it->writeValue(buf);
  return true;
}

bool	Nut::SQFunctionProto::writeArrayOfObjects(IBuffer& buf, const vector& array) const
{
  buf.writeInt('PART');
  for (const Object* it : array)
    writeObject(buf, it);
  return true;
}


int	Nut::SQFunctionProto::getLiteralIdx(const std::string& value) const
{
  int i = 0;

  for (auto it : this->literals)
    {
      auto literal = dynamic_cast<SQString*>(it);
      if (literal && *literal == value)
	return i;
      i++;
    }
  return -1;
}

void	Nut::SQFunctionProto::addLiteral(const std::string& literal)
{
  auto newObj = new SQString(&this->literals, std::to_string(this->literals.size()));
  *newObj = literal;
  this->literals.push_back(newObj);
  *this->nliterals = *this->nliterals + 1;
}

void	Nut::SQFunctionProto::insertInstruction(size_t position, const std::string& instruction)
{
  if (position > this->instructions.size())
    {
      Error::error("Invalid value for SQInstruction::insertInstruction: position out of range");
      return ;
    }

  auto instructionObj = new SQInstruction(&this->instructions, std::to_string(position));
  *instructionObj = instruction;
  this->instructions.insert(this->instructions.begin() + position, instructionObj);
  *this->ninstructions = *this->ninstructions + 1;

  // Fix instruction names
  for (size_t n = position + 1; n < this->instructions.size(); n++)
    this->instructions[n]->setName(std::to_string(n));

  // Fix local var infos
  for (auto it : this->localVarInfos)
    {
      auto info = dynamic_cast<SQLocalVarInfo*>(it);
      info->updateForNewInstruction(position);
    }
}
