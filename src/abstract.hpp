#ifndef ABSTRACT_HPP_
#define ABSTRACT_HPP_

#include <iostream>
using std::cout;
using std::endl;
#include <sstream>
using std::ostringstream;
#include <string>
using std::string;

#include "concrete.hpp"

namespace AbstractSyntax {

    class Environment;

    class SchemeExpression {
    public:
        virtual ~SchemeExpression() {}
        virtual SchemeExpression* eval(Environment& env) = 0;
        virtual string toString() = 0;
    };

    SchemeExpression* parse(ConcreteSyntax::SExpression* sexp);

} // end namespace AbstractSyntax

#endif /* ABSTRACT_HPP_ */
