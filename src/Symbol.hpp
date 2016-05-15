#ifndef SYMBOL_HPP_
#define SYMBOL_HPP_

#include <string>
using std::string;

#include "abstract.hpp"
#include "Environment.hpp"

namespace AbstractSyntax {
    class Symbol: public SchemeExpression {
    private:
        string s;
    public:
        Symbol(string s) : s(s) {}
        virtual ~Symbol() {}
        string Value() { return s; }
        virtual SchemeExpression* clone() { return new Symbol(s); }
        virtual SchemeExpression* eval(Environment& env) {
            SchemeExpression* se = env.find(s);
            if (se) { return se->eval(env); }
            cout << "symbol: " << s << endl;
            return new Symbol(s);
        }
        virtual string toString() { return s; }
    };
} // end namespace AbstractSyntax

#endif /* SYMBOL_HPP_ */
