#ifndef CONCRETE_HPP_
#define CONCRETE_HPP_

#include <iostream>
using std::endl;
#include <sstream>
using std::ostringstream;
#include <stdexcept>
using std::exception;
#include <string>
using std::string;
#include <vector>
using std::vector;

#include "token.hpp"

namespace ConcreteSyntax {
    class SExpression {
    public:
        SExpression() {}
        virtual ~SExpression() {}
        virtual string toString() = 0;
        virtual string toString(string m) = 0;
    };
    class ListExpression: public SExpression {
    private:
        vector<SExpression*> exprs;
    public:
        virtual ~ListExpression() {
            for (auto e : exprs) { delete e; }
        }
        void add(SExpression* expr) { exprs.push_back(expr); }
        unsigned int size() { return exprs.size(); }
        SExpression*& operator[](unsigned int i) { return exprs[i]; }
        virtual string toString() { return toString(""); }
        virtual string toString(string m) {
            ostringstream out;
            out << "\033[37;1m(\033[37;0m";
            for (unsigned int i = 0; i < exprs.size(); i++) {
                out << (i > 0 ? " " : "") << (exprs[i] ? exprs[i]->toString() : "NULL");
            }
            out << "\033[37;1m)\033[37;0m";
            return out.str();
        }
    };
    class SymbolExpression: public SExpression {
    private:
        string value;
    public:
        SymbolExpression(string v) : value(v) {}
        virtual ~SymbolExpression() {}
        string symbol() { return value; }
        virtual string toString() { return toString(""); }
        virtual string toString(string m) {
            ostringstream out;
            out << m << "\033[35;1m" << value << "\033[37;0m";
            return out.str();
        }
    };
    class NumberExpression: public SExpression {
    private:
        double value;
    public:
        NumberExpression(double d): value(d) {}
        double data() { return value; }
        virtual string toString() { return toString(""); }
        virtual string toString(string m) {
            ostringstream out;
            out << m << "\033[36;1m" << value << "\033[37;0m";
            return out.str();
        }
    };
    class BooleanExpression: public SExpression {
    private:
        bool value;
    public:
        BooleanExpression(bool b): value(b) {}
        bool data() { return value; }
        virtual string toString() { return toString(""); }
        virtual string toString(string m) {
            ostringstream out;
            out << m << "\033[33;1m" << (value ? "true" : "false") << "\033[37;0m";
            return out.str();
        }
    };
    class StringExpression: public SExpression {
    private:
        string value;
    public:
        StringExpression(string s): value(s) {}
        string data() { return value; }
        virtual string toString() { return toString(""); }
        virtual string toString(string m) {
            ostringstream out;
            out << m << "\033[32;1m\"" << value << "\"\033[37;0m";
            return out.str();
        }
    };

    class invalid_syntax: public exception {};

    class Parser {
    public:
        static SExpression* parse(token::TokenStream& tokens);
    private:
        static SExpression* parseList(token::TokenStream& tokens);
        static SExpression* parseSymbol(token::Symbol* token);
        static SExpression* parseString(token::String* token);
    };
} // end namespace parser

#endif /* CONCRETE_HPP_ */
