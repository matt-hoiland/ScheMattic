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
using Token::CloseParen;
using Token::IToken;
using Token::OpenParen;
using Token::String;
using Token::Symbol;
using Token::TokenStream;

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
        SExpression* parse(TokenStream& Tokens) {
            if (!Tokens.hasNext()) { return NULL; }
            IToken* Token = Tokens.next();
            if (dynamic_cast<OpenParen*>(Token)) {
                return parseList(Tokens);
            } else if (dynamic_cast<Symbol*>(Token)) {
                return parseSymbol(dynamic_cast<Symbol*>(Token));
            } else if (dynamic_cast<CloseParen*>(Token)) {
                throw invalid_syntax();
            } else if (dynamic_cast<String*>(Token)) {
                return parseString(dynamic_cast<String*>(Token));
            } else {
                return NULL;
            }
        }

    private:
        SExpression* parseList(TokenStream& Tokens) {
            if (!Tokens.hasNext()) { throw invalid_syntax(); }
            IToken* Token = Tokens.next();
            ListExpression* ret = new ListExpression();
            while (!dynamic_cast<CloseParen*>(Token)) {
                Tokens.retreat();
                ret->add(parse(Tokens));
                if (Tokens.hasNext()) {
                    Token = Tokens.next();
                } else {
                    delete ret;
                    throw invalid_syntax();
                }
            }
            return ret;
        }

        SExpression* parseSymbol(Symbol* Token) {
            try {
                double d = stod(Token->Value());
                return new NumberExpression(d);
            } catch (...) {
                if (Token->Value() == "true" || Token->Value() == "false") {
                    return new BooleanExpression(Token->Value() == "true");
                }
                return new SymbolExpression(Token->Value());
            }
        }

        SExpression* parseString(String* Token) {
            return new StringExpression(Token->Value());
        }
    };
} // end namespace parser

#endif /* CONCRETE_HPP_ */
