#ifndef STRING_HPP_
#define STRING_HPP_

#include "abstract.hpp"
#include "Environment.hpp"
#include "result.hpp"
using ResultSyntax::StringValue;

namespace AbstractSyntax {
    class String: public SchemeExpression {
    private:
        string s;
    public:
        String(string s) : s(s) {}
        virtual ~String() {}
        virtual string Value() { return s; }
        virtual SchemeExpression* clone() { return new String(s); }
        virtual ResultSyntax::Value* eval(Environment& env) { return new StringValue(s); }
        virtual string toString() { return "\"" + s + "\""; }
    };
} // end namespace AbstractSyntax

#endif /* STRING_HPP_ */
