#ifndef INTERPRETER_HPP_
#define INTERPRETER_HPP_

#include "AbstractSyntax.hpp"
#include <fstream>
#include <iostream>
#include <string>

using AbstractSyntax::SchemeExpression;
using ConcreteSyntax::invalid_syntax;
using ConcreteSyntax::SExpression;
using ResultSyntax::Environment;
using ResultSyntax::Value;
using std::ifstream;
using std::istream;
using std::ostream;
using std::string;
using token::TokenStream;

namespace Interpreter {

    class LineInterpreter {
    public:
        string interpret(istream& in, ostream& out) {
            Environment env;
            return interpret(in, out, env);
        }

        string interpret(istream& in, ostream& out, Environment& env) {
            string line;
            getline(in, line);
            if (line == "") { return line; }
            TokenStream stream(line);
            try {
                ConcreteSyntax::Parser cparser;
                SExpression* expr = cparser.parse(stream);
                if (expr) {
                    out << expr->toString() << endl;
                    AbstractSyntax::Parser aparser;
                    SchemeExpression* se = aparser.parse(expr);
                    if (se) {
                        Value* result = se->eval(env);
                        out << (result != NULL ? result->toString() + "\n" : "");
                        delete result;
                        delete se;
                    } else {
                        out << "parse failed" << endl;
                    }
                } else {
                    out << "NULL expression" << endl;
                }
                delete expr;
            } catch (invalid_syntax& ex) {
                out << "!!! invalid syntax: \"" << line << "\"" << endl;
            }
            return line;
        }
    };

    class FileInterpreter {
    private:
        string file_name;
    public:
        FileInterpreter (string file_name) : file_name(file_name) {}

        void interpret(ostream& out) {
            Environment env;
            interpret(out, env);
        }

        void interpret(ostream& out, Environment& env) {
            ifstream in(file_name);
            if (in.is_open()) {
                LineInterpreter liner;
                while (!in.eof()) {
                    liner.interpret(in, out, env);
                }
            }
        }
    };

} // end namespace Interpreter

#endif /* INTERPRETER_HPP_ */
