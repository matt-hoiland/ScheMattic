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
                AbstractSyntax::SchemeExpression* se = AbstractSyntax::parse(expr);
                if (se) {
                    AbstractSyntax::SchemeExpression* result = se->eval();
                    cout << (result != NULL ? result->toString() : "eval failed") << endl;
                    delete result;
                    delete se;
                } else {
                    cout << "parse failed" << endl;
                }
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
