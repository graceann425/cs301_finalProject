#include "ASMParser.h"

ASMParser::ASMParser(string filename)
  // Specify a text file containing MIPS assembly instructions. Function
  // checks syntactic correctness of file and creates a list of Instructions.
{
  Instruction i;
  myFormatCorrect = true;

  myLabelAddress = 0x400000;
  
  // Parse document for labels
  labels.addLabels(filename);

  //labels.printString();

  ifstream in;
  in.open(filename.c_str());
  if(in.fail()){
    myFormatCorrect = false;
      cout << "bad format " << endl;
  }
  else{
    string line;
    while( getline(in, line)){
      string opcode("");
      string operand[80];
      int operand_count = 0;

      if (line.size() == 0)
        continue;
      if (line.at(0) == '#')
        continue;

      // If line starts with a label, remove it before getting tokens
      string::size_type idx = line.find(':');
      if (idx != string::npos)
        line = line.substr(idx+1, string::npos);

      getTokens(i, line, opcode, operand, operand_count);

      if(opcode.length() == 0 && operand_count != 0){
	// No opcode but operands
	myFormatCorrect = false;
	break;
      }

      Opcode o = opcodes.getOpcode(opcode);
      if(o == UNDEFINED){
	// invalid opcode specified
	myFormatCorrect = false;
	break;
      }

      bool success = getOperands(i, o, operand, operand_count);
      if(!success){
	myFormatCorrect = false;
	break;
      }
      string encoding = encode(i);
      i.setEncoding(encoding);

      myInstructions.push_back(i);
      myLabelAddress += 4;
    }
  }

  myIndex = 0;
}


Instruction ASMParser::getNextInstruction()
  // Iterator that returns the next Instruction in the list of Instructions.
{
  if(myIndex < (int)(myInstructions.size())){
    myIndex++;
    return myInstructions[myIndex-1];
  }

  Instruction i;
  return i;

}

void ASMParser::getTokens(Instruction &inst, string line,
			       string &opcode,
			       string *operand,
			       int &numOperands)
  // Decomposes a line of assembly code into strings for the opcode field and operands,
  // checking for syntax errors and counting the number of operands.
{
    // locate the start of a comment
    string::size_type idx = line.find('#');
    if (idx != string::npos) // found a ';'
	     line = line.substr(0,idx);

    inst.setOriginalCode(line);

    int len = line.length();
    opcode = "";
    numOperands = 0;

    if (len == 0) return;
    int p = 0; // position in line

    // line.at(p) is whitespace or p >= len
    while (p < len && isWhitespace(line.at(p)))
	p++;
    // opcode starts
    while (p < len && !isWhitespace(line.at(p)))
    {
	opcode = opcode + line.at(p);
	p++;
    }
    //    for(int i = 0; i < 3; i++){
    int i = 0;
    while(p < len){
      while ( p < len && isWhitespace(line.at(p)))
	p++;

      // operand may start
      bool flag = false;
      while (p < len && !isWhitespace(line.at(p)))
	{
	  if(line.at(p) != ','){
	    operand[i] = operand[i] + line.at(p);
	    flag = true;
	    p++;
	  }
	  else{
	    p++;
	    break;
	  }
	}
      if(flag == true){
	numOperands++;
      }
      i++;
    }


    idx = operand[numOperands-1].find('(');
    string::size_type idx2 = operand[numOperands-1].find(')');

    if (idx == string::npos || idx2 == string::npos ||
	((idx2 - idx) < 2 )){ // no () found
    }
    else{ // split string
      string offset = operand[numOperands-1].substr(0,idx);
      string regStr = operand[numOperands-1].substr(idx+1, idx2-idx-1);

      operand[numOperands-1] = offset;
      operand[numOperands] = regStr;
      numOperands++;
    }



    // ignore anything after the whitespace after the operand
    // We could do a further look and generate an error message
    // but we'll save that for later.
    return;
}

bool ASMParser::isNumberString(string s)
  // Returns true if s represents a valid decimal integer
{
    int len = s.length();
    if (len == 0) return false;
    if ((isSign(s.at(0)) && len > 1) || isDigit(s.at(0)))
    {
	// check remaining characters
	for (int i=1; i < len; i++)
	{
	    if (!isdigit(s.at(i))) return false;
	}
	return true;
    }
    return false;
}


int ASMParser::cvtNumString2Number(string s)
  // Converts a string to an integer.  Assumes s is something like "-231" and produces -231
{
    if (!isNumberString(s))
    {
	cerr << "Non-numberic string passed to cvtNumString2Number"
		  << endl;
	return 0;
    }
    int k = 1;
    int val = 0;
    for (int i = s.length()-1; i>0; i--)
    {
	char c = s.at(i);
	val = val + k*((int)(c - '0'));
	k = k*10;
    }
    if (isSign(s.at(0)))
    {
	if (s.at(0) == '-') val = -1*val;
    }
    else
    {
	val = val + k*((int)(s.at(0) - '0'));
    }
    return val;
}


bool ASMParser::getOperands(Instruction &i, Opcode o,
			    string *operand, int operand_count)
  // Given an Opcode, a string representing the operands, and the number of operands,
  // breaks operands apart and stores fields into Instruction.
{

  if(operand_count != opcodes.numOperands(o))
    return false;

  int rs, rt, rd, imm;
  imm = 0;
  rs = rt = rd = NumRegisters;

  int rs_p = opcodes.RSposition(o);
  int rt_p = opcodes.RTposition(o);
  int rd_p = opcodes.RDposition(o);
  int imm_p = opcodes.IMMposition(o);

  if(rs_p != -1){
    rs = registers.getNum(operand[rs_p]);
    if(rs == NumRegisters)
      return false;
  }

  if(rt_p != -1){
    rt = registers.getNum(operand[rt_p]);
    if(rt == NumRegisters)
      return false;

  }

  if(rd_p != -1){
    rd = registers.getNum(operand[rd_p]);
    if(rd == NumRegisters)
      return false;

  }

  if(imm_p != -1){
    if(isNumberString(operand[imm_p])){  // does it have a numeric immediate field?
      imm = cvtNumString2Number(operand[imm_p]);
      if(((abs(imm) & 0xFFFF0000)<<1))  // too big a number to fit
	      return false;

    // Check if immediate field is a hexadecimal address
    } else if(operand[imm_p].at(0) == '0' && operand[imm_p].at(1) == 'x'){
      //cout << "operand[imm_p]: " << operand[imm_p] << endl;
      // convert string to hexadecimal number
      imm = stoi(operand[imm_p], nullptr, 16);

      // if offset rather than address
      if (o == J && imm < 0x400000)
        imm = imm/0x100;

      // if beq instruction
      if (opcodes.getInstType(o) == ITYPE)
        imm = imm/0x100; // get rid off the two trailing 0's

    }
    else{
      // Check if immediate field is a label
      if(opcodes.isIMMLabel(o)){  // Can the operand be a label?
        imm = labels.getAddressOfLabel(operand[imm_p]);
        // if label not found, assign current address as default
        if (imm == -1)
          imm = myLabelAddress;

        // If I-Type (beq), find the correspoding offset for the address
        if (opcodes.getInstType(o) == ITYPE) {
          imm = (imm-myLabelAddress)/4;
        }

      }
      else  // There is an error
	return false;
    }

  }

  i.setValues(o, rs, rt, rd, imm);

  return true;
}


string ASMParser::encode(Instruction &i)
  // Given a valid instruction, returns a string representing the 32 bit MIPS binary encoding
  // of that instruction.
{

  //cout << "in encode " << endl;

  // Determine the instruction type
  Opcode o = i.getOpcode();
  InstType type = opcodes.getInstType(o);

  // Determine instruction type
  if (type == ITYPE) {
    return encodeIType(i, o);

  } else if (type == RTYPE) {
    return encodeRType(i, o);

  } else if (type == JTYPE) {
    return encodeJType(i, o);

  } else {
    return "";
  }
}


string ASMParser::encodeIType(Instruction &i, Opcode o)
  // Encodes an I-Type MIPS instruction into its binary representation
  // I-Type Instruction:  op   rs   rt   offset
  //            bits:      6   5    5    16
{
  // Get op code
  encoded = opcodes.getOpcodeField(o);

  // Get rs, if any
  int rsp = opcodes.RSposition(o);
  if (rsp < 0) {
    encoded += "00000";
  } else {
    int rs = i.getRS();         // Convert Register to int
    encoded += decimalToBinary(rs, 5);  // Convert Register to 5-bit binary
  }

  // Get rt, if any
  int rtp = opcodes.RTposition(o);
  if (rtp < 0) {
    encoded += "00000";
  } else {
    int rt = i.getRT();
    encoded += decimalToBinary(rt, 5);
  }

  // Get offset
  int immp = opcodes.IMMposition(o);
  if (immp < 0) {
    encoded += "0000000000000000";
  } else {
    int imm = i.getImmediate();
    encoded += decimalToBinary(imm, 16);
  }
  return encoded;
}


string ASMParser::encodeRType(Instruction &i, Opcode o)
  // Encodes an R-Type MIPS instruction into its binary representation
  // R-Type Instruction:  op   rs   rt   rd   shamt   funct
  //            bits:     6    5    5    5    5       6
{
  // Get op code
  encoded = opcodes.getOpcodeField(o);

  // Get rs, if any
  int rsp = opcodes.RSposition(o);
  if (rsp < 0) {
    encoded += "00000";
  } else {
    int rs = i.getRS();         // Convert Register to int
    encoded += decimalToBinary(rs, 5);  // Convert Register to 5-bit binary
  }

  // Get rt, if any
  int rtp = opcodes.RTposition(o);
  if (rtp < 0) {
    encoded += "00000";
  } else {
    int rt = i.getRT();
    encoded += decimalToBinary(rt, 5);
  }

  // Get rd, if any
  int rdp = opcodes.RDposition(o);
  if (rdp < 0) {
    encoded += "00000";
  } else {
    int rd = i.getRD();
    encoded += decimalToBinary(rd, 5);
  }

  // Get shampt, if any
  int immp = opcodes.IMMposition(o);
  if (immp < 0) {
    encoded += "00000";
  } else {
    int imm = i.getImmediate();
    encoded += decimalToBinary(imm, 5);
  }

  // Get func and return from function
  encoded += opcodes.getFunctField(o);
  return encoded;
}


string ASMParser::encodeJType(Instruction &i, Opcode o)
  // Encodes an J-Type MIPS instruction into its binary representation
  // J-Type Instruction:  op   address
  //            bits:     6    26
{
  // get op code
  encoded = opcodes.getOpcodeField(o);

  // get immediate (address/label)
  int imm = i.getImmediate();

  // Get rid of the 2 rightmost bits
  imm = imm >> 2;

  // function gets rid of 4 leftmost bits
  encoded += decimalToBinary(imm, 26);
  return encoded;
}


string ASMParser::decimalToBinary(int n, int bits)
  // Converts a decimal number to binary. The parameter bits specifies
  // the number of bits the binary number should have.
{
  // If n is negative, use two's complement for binary representation
  if (n < 0)
    return negativeDecimalToBinary(n, bits);


  int count = 0;
  string result = "";
  while (n > 0) {

    // Return string if its the length of num of bits specified, regardless
    // if it has finished converting the entire number or not
    if (count == bits)
      return result;

    int rem = n % 2;
    n = n / 2;
    result = to_string(rem) + result;
    count++;
  }

  // Add extra 0s if needed in order to satisfy total number of bits
  while (count < bits) {
    result = "0" + result;
    count++;
  }
  return result;
}



string ASMParser::negativeDecimalToBinary(int n, int bits)
  // Use two's complement to convert a negative decimal number to binary
{
  // make number positive
  n = n * -1;

  int count = 0;
  string result = "";
  while (n > 0) {

    // Return string if its the length of num of bits specified, regardless
    // if it has finished converting the entire number or not
    if (count == bits)
      return result;

    int rem = n % 2;
    n = n / 2;

    // invert bits
    if (rem == 1) {
      result = "0" + result;
    } else {
      result = "1" + result;
    }
    count++;
  }

  // Add 1 to binary number
  int idx = result.size()-1;
  while (idx >= 0) {
    if (result.at(idx) == '1') {
      result.at(idx) = '0';
      idx--;
    } else {
      result.at(idx) = '1';
      break;
    }
  }

  // Add trailing 1s if needed in order to satisfy total number of bits
  while (count < bits) {
    result = "1" + result;
    count++;
  }
  return result;
}
