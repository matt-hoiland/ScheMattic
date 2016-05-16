#ifndef SYMBOL_HPP_
#define SYMBOL_HPP_

#include <string>
using std::string;

#include "abstract.hpp"
#include "Environment.hpp"
using ResultSyntax::Environment;
using ResultSyntax::Value;

namespace AbstractSyntax {
    class Symbol: public SchemeExpression {
    private:
        string s;
    public:
        Symbol(string s) : s(s) {}
        virtual ~Symbol() {}
        string Value() { return s; }
        virtual SchemeExpression* clone() { return new Symbol(s); }
        virtual ResultSyntax::Value* eval(Environment& env) {
            if (env.find(s)) { return env.find(s)->clone(); }
            return NULL;
        }
        virtual string toString() { return s; }
    };
} // end namespace AbstractSyntax

#endif /* SYMBOL_HPP_ */
