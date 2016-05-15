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
