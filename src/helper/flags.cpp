
#include "flags.hpp"
#include "../common.hpp"
#include "../lexer/lexer.hpp"
#include "../parser/parser.hpp"
#include "../typeChecker/type.hpp"
#include "../codegen/gen.hpp"
#include "error/error.hpp"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

char *Flags::readFile(const char *path) {
  ifstream file(path, ios::binary);
  if (!file) {
    cerr << "Error: Could not open file '" << path << "'" << endl;
    Exit(ExitValue::INVALID_FILE);
  }

  file.seekg(0, ios::end);
  size_t size = file.tellg();
  file.seekg(0, ios::beg);

  char *buffer = new char[size + 1];
  file.read(buffer, size);
  file.close();

  buffer[size] = 0;
  return buffer;
}

void Flags::runFile(const char *path, std::string outName, bool save) {
  const char *source = readFile(path);

  auto result = Parser::parse(source, path);
  ErrorClass::printError();

  // result->debug();

  TypeChecker::performCheck(result);
  ErrorClass::printError();
  // std::cout << "Passed Type Checking" << std::endl;

  codegen::gen(result, save, outName);

  delete[] source;
  delete result;
}
