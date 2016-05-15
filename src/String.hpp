#ifndef STRING_HPP_
#define STRING_HPP_

#include "abstract.hpp"
#include "Environment.hpp"

namespace AbstractSyntax {
    class String: public SchemeExpression {
    private:
        string s;
    public:
        String(string s) : s(s) {}
        virtual ~String() {}
        virtual string Value() { return s; }
        virtual SchemeExpression* eval(Environment& env) { return new String(s); }
        virtual string toString() { return "\"" + s + "\""; }
    };
} // end namespace AbstractSyntax

#endif /* STRING_HPP_ */
