#include <iostream>

#include "abstract.hpp"
#include "concrete.hpp"
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
            ConcreteSyntax::SExpression* expr = ConcreteSyntax::Parser::parse(stream);
            if (expr) {
                cout << expr->toString() << endl;
                AbstractSyntax::AE* ae = AbstractSyntax::parse(expr);
                if (ae) {
                    AbstractSyntax::AE* result = ae->eval();
                    cout << result->toString() << endl;
                    delete result;
                } else {
                    cout << "not arithmetic" << endl;
                }
                delete ae;
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
