#include <iostream>
#include "Interpreter.hpp"

using Interpreter::LineInterpreter;
using ResultSyntax::Environment;
using std::cin;
using std::cout;
using std::endl;

const string OPENING = "Welcome! type (quit) to exit";
const string PROMPT = ">>> ";
const string CLOSING = "Exiting...";

int main() {
    cout << OPENING << endl;
    bool done = false;
    Interpreter::LineInterpreter interp;
    ResultSyntax::Environment env;
    while (!done) {
        cout << PROMPT;
        string line = interp.interpret(cin, cout, env);
        if (line == "(quit)") {
            done = true;
        }
        if (line == "env") {
            cout << env.toString() << endl;
        }
    }
    env.clear();
    cout << CLOSING << endl;
    return 0;
}
