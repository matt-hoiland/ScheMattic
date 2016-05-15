#ifndef INTERPRETER_HPP_
#define INTERPRETER_HPP_

#include <iostream>
using std::istream;
using std::ostream;
#include <fstream>
using std::ifstream;
#include <string>
using std::string;

#include "abstract.hpp"
#include "concrete.hpp"
#include "Environment.hpp"
using ResultSyntax::Environment;
#include "token.hpp"

namespace Interpreter {

    class LineInterpreter {
    public:
        string interpret(istream& in, ostream& out);
        string interpret(istream& in, ostream& out, Environment& env);
    };

    class FileInterpreter {
    private:
        string file_name;
    public:
        FileInterpreter (string file_name) : file_name(file_name) {}
        void interpret(ostream& out);
        void interpret(ostream& out, Environment& env);
    };

} // end namespace Interpreter

#endif /* INTERPRETER_HPP_ */
