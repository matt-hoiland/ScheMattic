#ifndef ARITHMETIC_HPP_
#define ARITHMETIC_HPP_

#include "AbstractSyntax.hpp"

using ResultSyntax::Environment;
using ResultSyntax::NumberValue;
using ResultSyntax::Value;

namespace AbstractSyntax {
    namespace Arithmetic {

        class AE: public SchemeExpression {
        public:
            virtual ~AE() {}
        };

        class Number: public AE {
        private:
            double d;
        public:
            virtual ~Number() {}
            Number(double d) : d(d) {}
            double data() { return d; }
            virtual Value* eval(Environment& env) { return new NumberValue(d); }
            virtual SchemeExpression* clone() { return new Number(d); }
            virtual string toString() {
                ostringstream out;
                out << d;
                return out.str();
            }
        };

        class Binop: public AE {
        protected:
            SchemeExpression *a, *b;
        public:
            Binop(SchemeExpression* a, SchemeExpression* b) : a(a), b(b) {}
            virtual ~Binop() {
                delete a;
                delete b;
            }
            virtual Value* eval(Environment& env) {
                Value *sa = a->eval(env), *sb = b->eval(env);
                NumberValue* A = dynamic_cast<NumberValue*>(sa);
                NumberValue* B = dynamic_cast<NumberValue*>(sb);
                Value* ret = NULL;
                if (A && B) {
                    ret = new NumberValue(operate(A->val(), B->val()));
                    delete A;
                    delete B;
                    return ret;
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
            Adder(SchemeExpression *a, SchemeExpression *b) : Binop(a, b) {}
            virtual SchemeExpression* clone() { return new Adder(a->clone(), b->clone()); }
            virtual double operate(double a, double b) {
                return a + b;
            }
            virtual string op() { return "+"; }
        };

        class Subtracter: public Binop {
        public:
            virtual ~Subtracter() {}
            Subtracter(SchemeExpression *a, SchemeExpression *b) : Binop(a, b) {}
            virtual SchemeExpression* clone() { return new Subtracter(a->clone(), b->clone()); }
            virtual double operate(double a, double b) {
                return a - b;
            }
            virtual string op() { return "-"; }
        };

        class Multiplier: public Binop {
        public:
            virtual ~Multiplier() {}
            Multiplier(SchemeExpression *a, SchemeExpression *b) : Binop(a, b) {}
            virtual SchemeExpression* clone() { return new Multiplier(a->clone(), b->clone()); }
            virtual double operate(double a, double b) {
                return a * b;
            }
            virtual string op() { return "*"; }
        };

        class Divider: public Binop {
        public:
            virtual ~Divider() {}
            Divider(SchemeExpression *a, SchemeExpression *b) : Binop(a, b) {}
            virtual SchemeExpression* clone() { return new Divider(a->clone(), b->clone()); }
            virtual double operate(double a, double b) {
                return a / b;
            }
            virtual string op() { return "/"; }
        };

    } // end namespace Arithmetic
} // end namespace AbstractSyntax

#endif /* ARITHMETIC_HPP_ */
