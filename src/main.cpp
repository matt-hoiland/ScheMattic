#include <iostream>

#include "token.hpp"

using namespace std;

const string OPENING = "Welcome! type (quit) to exit";
const string PROMPT = ">>> ";
const string CLOSING = "Exiting...";

int main() {
    cout << OPENING << endl;
    bool done = false;
    while (!done) {
        cout << PROMPT;
        string line;
        getline(cin, line);
        if (line == "(quit)") {
            done = true;
        }
        token::TokenStream stream(line);
        while (stream.hasNext()) {
            cout << stream.next()->Value() << endl;
        }
    }
    cout << CLOSING << endl;
    return 0;
}
