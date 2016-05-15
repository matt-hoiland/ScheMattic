#ifndef INTERPRETER_HPP_
#define INTERPRETER_HPP_

#include <iostream>
using std::istream;
using std::ostream;
#include <string>
using std::string;

#include "abstract.hpp"
#include "concrete.hpp"
#include "token.hpp"

namespace Interpreter {

    class LineInterpreter {
    public:
        string interpret(istream& in, ostream& out);
    };

    class FileInterpreter {
    private:
        string file_name;
    public:
        FileInterpreter (string file_name) : file_name(file_name) {}
        void interpret(ostream& out);
    };

} // end namespace Interpreter

#endif /* INTERPRETER_HPP_ */
