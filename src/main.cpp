#include <iostream>

#include "Environment.hpp"
#include "interpreter.hpp"

using namespace std;

const string OPENING = "Welcome! type (quit) to exit";
const string PROMPT = ">>> ";
const string CLOSING = "Exiting...";

int main() {
    cout << OPENING << endl;
    bool done = false;
    Interpreter::LineInterpreter interp;
    AbstractSyntax::Environment env;
    while (!done) {
        cout << PROMPT;
        string line = interp.interpret(cin, cout, env);
        if (line == "(quit)") {
            done = true;
        }
    }
    cout << CLOSING << endl;
    return 0;
}
