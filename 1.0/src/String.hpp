#ifndef STRING_HPP_
#define STRING_HPP_

#include "AbstractSyntax.hpp"

using ResultSyntax::StringValue;
using ResultSyntax::Value;

namespace AbstractSyntax {
    class String: public SchemeExpression {
    private:
        string s;
    public:
        String(string s) : s(s) {}
        virtual ~String() {}
        virtual string data() { return s; }
        virtual SchemeExpression* clone() { return new String(s); }
        virtual Value* eval(Environment& env) { return new StringValue(s); }
        virtual string toString() { return "\"" + s + "\""; }
    };
} // end namespace AbstractSyntax

#endif /* STRING_HPP_ */
