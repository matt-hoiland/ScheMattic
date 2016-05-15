#include "interpreter.hpp"

using ResultSyntax::Environment;
using std::ifstream;
using std::istream;
using std::ostream;
using std::string;

string Interpreter::LineInterpreter::interpret(istream& in, ostream& out) {
    Environment env;
    return interpret(in, out, env);
}

string Interpreter::LineInterpreter::interpret(istream& in, ostream& out, Environment& env) {
    string line;
    getline(in, line);
    if (line == "") { return line; }
    token::TokenStream stream(line);
    try {
        ConcreteSyntax::SExpression* expr = ConcreteSyntax::Parser::parse(stream);
        if (expr) {
            out << expr->toString() << endl;
            AbstractSyntax::SchemeExpression* se = AbstractSyntax::parse(expr);
            if (se) {
                ResultSyntax::Value* result = se->eval(env);
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
    } catch (ConcreteSyntax::invalid_syntax& ex) {
        out << "!!! invalid syntax: \"" << line << "\"" << endl;
    }
    return line;
}

void Interpreter::FileInterpreter::interpret(ostream& out) {
    Environment env;
    interpret(out, env);
}

void Interpreter::FileInterpreter::interpret(ostream& out, Environment& env) {
    ifstream in(file_name);
    if (in.is_open()) {
        LineInterpreter liner;
        while (!in.eof()) {
            liner.interpret(in, out, env);
        }
    }
}
