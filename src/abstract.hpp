#ifndef ABSTRACT_H_
#define ABSTRACT_H_

#include <iostream>
using std::cout;
using std::endl;
#include <sstream>
using std::ostringstream;
#include <string>
using std::string;

#include "concrete.hpp"

namespace AbstractSyntax {

    class SchemeExpression {
    public:
        virtual ~SchemeExpression() {}
        virtual SchemeExpression* eval() = 0;
        virtual string toString() = 0;
    };

    SchemeExpression* parse(ConcreteSyntax::SExpression* sexp);

} // end namespace AbstractSyntax

#endif /* ABSTRACT_H_ */
