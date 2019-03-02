#ifndef ABSTRACT_HPP_
#define ABSTRACT_HPP_

#include "ConcreteSyntax.hpp"
#include "Environment.hpp"

#include <iostream>
#include <sstream>
#include <string>

using ConcreteSyntax::SExpression;
using ResultSyntax::Environment;
using ResultSyntax::Value;
using std::string;

namespace AbstractSyntax {

    class SchemeExpression {
    public:
        virtual ~SchemeExpression() {}
        virtual Value* eval(Environment& env) = 0;
        virtual SchemeExpression* clone() = 0;
        virtual string toString() = 0;
    };

    class Parser {
    public:
        SchemeExpression* parse(SExpression* sexp);
    };
} // end namespace AbstractSyntax

#endif /* ABSTRACT_HPP_ */
