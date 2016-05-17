#ifndef SYMBOL_HPP_
#define SYMBOL_HPP_

#include "AbstractSyntax.hpp"
#include <string>

using ResultSyntax::Environment;
using ResultSyntax::Value;
using std::string;

namespace AbstractSyntax {
    class Symbol: public SchemeExpression {
    private:
        string s;
    public:
        Symbol(string s) : s(s) {}
        virtual ~Symbol() {}
        string data() { return s; }
        virtual SchemeExpression* clone() { return new Symbol(s); }
        virtual Value* eval(Environment& env) {
            if (env.find(s)) { return env.find(s)->clone(); }
            return NULL;
        }
        virtual string toString() { return s; }
    };
} // end namespace AbstractSyntax

#endif /* SYMBOL_HPP_ */
