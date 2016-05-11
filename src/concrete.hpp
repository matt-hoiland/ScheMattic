#ifndef LISTPARSER_HPP_
#define LISTPARSER_HPP_

#include <iostream>
using std::endl;
#include <string>
using std::string;
#include <sstream>
using std::ostringstream;
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
        void add(SExpression* expr) { exprs.push_back(expr); }
        virtual string toString() { return toString(""); }
        virtual string toString(string m) {
            ostringstream out;
            out << m << "(" << (exprs.size() > 0 ? exprs[0]->toString() : "");
            for (int i = 1; i < exprs.size(); i++) {
                out << endl << exprs[i]->toString(m + " ");
            }
            out << ")";
            return out.str();
        }
    };
    class SymbolExpression: public SExpression {
    private:
        string value;
    public:
        SymbolExpression(string v) : value(v) {}
        virtual ~SymbolExpression() {}
        virtual string toString() { return value; }
        virtual string toString(string m) { return m + value; }
    };

    class Parser {
    public:
        static SExpression* parse(token::TokenStream& tokens);
    private:
        static ListExpression* parseList(token::TokenStream& tokens);
        static SymbolExpression* parseSymbol(token::Symbol* token);
    };
} // end namespace parser

#endif /* LISTPARSER_HPP_ */
