#ifndef CONCRETE_HPP_
#define CONCRETE_HPP_

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "Token.hpp"
#include <vector>

using std::endl;
using std::exception;
using std::string;
using std::ostringstream;
using std::vector;
using token::CloseParen;
using token::IToken;
using token::OpenParen;
using token::String;
using token::Symbol;
using token::TokenStream;

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
        SExpression* parse(TokenStream& tokens) {
            if (!tokens.hasNext()) { return NULL; }
            IToken* token = tokens.next();
            if (dynamic_cast<OpenParen*>(token)) {
                return parseList(tokens);
            } else if (dynamic_cast<Symbol*>(token)) {
                return parseSymbol(dynamic_cast<Symbol*>(token));
            } else if (dynamic_cast<CloseParen*>(token)) {
                throw invalid_syntax();
            } else if (dynamic_cast<String*>(token)) {
                return parseString(dynamic_cast<String*>(token));
            } else {
                return NULL;
            }
        }

    private:
        SExpression* parseList(TokenStream& tokens) {
            if (!tokens.hasNext()) { throw invalid_syntax(); }
            IToken* token = tokens.next();
            ListExpression* ret = new ListExpression();
            while (!dynamic_cast<CloseParen*>(token)) {
                tokens.retreat();
                ret->add(parse(tokens));
                if (tokens.hasNext()) {
                    token = tokens.next();
                } else {
                    delete ret;
                    throw invalid_syntax();
                }
            }
            return ret;
        }

        SExpression* parseSymbol(Symbol* token) {
            try {
                double d = stod(token->Value());
                return new NumberExpression(d);
            } catch (...) {
                if (token->Value() == "true" || token->Value() == "false") {
                    return new BooleanExpression(token->Value() == "true");
                }
                return new SymbolExpression(token->Value());
            }
        }

        SExpression* parseString(String* token) {
            return new StringExpression(token->Value());
        }
    };
} // end namespace parser

#endif /* CONCRETE_HPP_ */
