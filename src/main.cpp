#include <iostream>

#include "concrete.hpp"
using ConcreteSyntax::SExpression;
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
        try {
            SExpression* expr = ConcreteSyntax::Parser::parse(stream);
            if (expr) {
                cout << expr->toString() << endl;
            } else {
                cout << "NULL expression" << endl;
            }
            delete expr;
        } catch (ConcreteSyntax::invalid_syntax& ex) {
            cout << "!!! invalid syntax: \"" << line << "\"" << endl;
        }
    }
    cout << CLOSING << endl;
    return 0;
}
