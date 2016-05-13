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
using ConcreteSyntax::BooleanExpression;
using ConcreteSyntax::ListExpression;
using ConcreteSyntax::NumberExpression;
using ConcreteSyntax::StringExpression;
using ConcreteSyntax::SymbolExpression;

namespace AbstractSyntax {

    class AE {
    public:
        virtual ~AE() {}
        virtual AE* eval() = 0;
        virtual string toString() = 0;
    };

    class Number: public AE {
    private:
        double d;
    public:
        virtual ~Number() {}
        Number(double d) : d(d) {}
        double Value() { return d; }
        virtual AE* eval() { return new Number(d); }
        virtual string toString() {
            ostringstream out;
            out << d;
            return out.str();
        }
    };

    class Binop: public AE {
    private:
        AE *a, *b;
    public:
        Binop(AE *a, AE* b) : a(a), b(b) {}
        virtual ~Binop() {
            delete a;
            delete b;
        }
        virtual AE* eval() {
            Number* A = dynamic_cast<Number*>(a->eval());
            Number* B = dynamic_cast<Number*>(b->eval());
            if (A && B) {
                Number* n = new Number(operate(A->Value(), B->Value()));
                delete A;
                delete B;
                return n;
            }
            return NULL;
        }
        virtual string toString() {
            ostringstream out;
            out << "(" << op() << " " << a->toString() << " " << b->toString() << ")";
            return out.str();
        }
    protected:
        virtual double operate(double a, double d) = 0;
        virtual string op() = 0;
    };

    class Adder: public Binop {
    public:
        virtual ~Adder() {}
        Adder(AE *a, AE *b) : Binop(a, b) {}
        virtual double operate(double a, double b) {
            return a + b;
        }
        virtual string op() { return "+"; }
    };

    class Subtracter: public Binop {
    public:
        virtual ~Subtracter() {}
        Subtracter(AE *a, AE *b) : Binop(a, b) {}
        virtual double operate(double a, double b) {
            return a - b;
        }
        virtual string op() { return "-"; }
    };

    class Multiplier: public Binop {
    public:
        virtual ~Multiplier() {}
        Multiplier(AE *a, AE *b) : Binop(a, b) {}
        virtual double operate(double a, double b) {
            return a * b;
        }
        virtual string op() { return "*"; }
    };

    class Divider: public Binop {
    public:
        virtual ~Divider() {}
        Divider(AE *a, AE *b) : Binop(a, b) {}
        virtual double operate(double a, double b) {
            return a / b;
        }
        virtual string op() { return "/"; }
    };

    AE* parse(ConcreteSyntax::SExpression* sexp) {
        if (dynamic_cast<ListExpression*>(sexp)) {
            ListExpression* li = (ListExpression*) sexp;
            if (li->size() == 3) {
                AE* a = parse((*li)[1]);
                AE* b = parse((*li)[2]);
                SymbolExpression* op = dynamic_cast<SymbolExpression*>((*li)[0]);
                if (op) {
                    string s = op->symbol();
                    switch (s[0]) {
                    case '+': return new Adder(a, b);
                    case '-': return new Subtracter(a, b);
                    case '*': return new Multiplier(a, b);
                    case '/': return new Divider(a, b);
                    }
                }
                delete a;
                delete b;
            }
        } else if (dynamic_cast<SymbolExpression*>(sexp)) {
            return NULL;
        } else if (dynamic_cast<NumberExpression*>(sexp)) {
            return new Number(((NumberExpression*)sexp)->data());
        } else if (dynamic_cast<BooleanExpression*>(sexp)) {
            return NULL;
        } else if (dynamic_cast<StringExpression*>(sexp)) {
            return NULL;
        } else {
            return NULL;
        }
        return NULL;
    }

} // end namespace AbstractSyntax

#endif /* ABSTRACT_H_ */
