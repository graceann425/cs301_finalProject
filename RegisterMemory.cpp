

void RegisterMemory::readFileMemory(string filename) {
  ifstream in;
  in.open(filename.c_str());


  if (in.fail()) {
    cout << "bad format in file " << filename << endl;

  } else {

    string line;
    int regNum = 0;

    while (getline(in, line)) {

      // Skip line if it starts with a '#'
      if (line.at(0) == '#')
        continue;

      // Check for a ':'
      std::size_t start = line.find(':');

      if (start != string::npos) {
        // Check if a comment occurs later on the same line
        std::size_t end = line.find('#');

        // Add memory to register array
        registerArray[regNum++] = line.substr(start+1, end);
      }
    }
  }
  in.close();
}


string RegisterMemory::getRegister(int regNum) {
  if (regNum >= 32 || regNum < 0)
    return "";

  return registerArray[regNum];
}


void RegisterMemory::setRegisterData(int regNum, string data) {
  if (regNum >= 32 || regNum < 0)
    return;

  registerArray[regNum] = data;
}


void RegisterMemory::printRegisterMemory() {
  cout << "Register Memory: " << endl;

  for (int i = 0; i < 32; i++)
    cout << "R" << i.to_string() << ": " << registerArray[i] << endl;
}
