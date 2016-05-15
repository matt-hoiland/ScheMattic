#include <iostream>

#include "interpreter.hpp"

using namespace std;

const string OPENING = "Welcome! type (quit) to exit";
const string PROMPT = ">>> ";
const string CLOSING = "Exiting...";

int main() {
    cout << OPENING << endl;
    bool done = false;
    Interpreter::LineInterpreter interp;
    while (!done) {
        cout << PROMPT;
        string line = interp.interpret(cin,cout);
        if (line == "(quit)") {
            done = true;
        }
    }
    cout << CLOSING << endl;
    return 0;
}
