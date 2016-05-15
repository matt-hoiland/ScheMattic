#ifndef ARITHMETIC_H_
#define ARITHMETIC_H_

#include "abstract.hpp"

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
            double Value() { return d; }
            virtual SchemeExpression* eval() { return new Number(d); }
            virtual string toString() {
                ostringstream out;
                out << d;
                return out.str();
            }
        };

        class Binop: public AE {
        private:
            SchemeExpression *a, *b;
        public:
            Binop(SchemeExpression* a, SchemeExpression* b) : a(a), b(b) {}
            virtual ~Binop() {
                delete a;
                delete b;
            }
            virtual SchemeExpression* eval() {
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
            Adder(SchemeExpression *a, SchemeExpression *b) : Binop(a, b) {}
            virtual double operate(double a, double b) {
                return a + b;
            }
            virtual string op() { return "+"; }
        };

        class Subtracter: public Binop {
        public:
            virtual ~Subtracter() {}
            Subtracter(SchemeExpression *a, SchemeExpression *b) : Binop(a, b) {}
            virtual double operate(double a, double b) {
                return a - b;
            }
            virtual string op() { return "-"; }
        };

        class Multiplier: public Binop {
        public:
            virtual ~Multiplier() {}
            Multiplier(SchemeExpression *a, SchemeExpression *b) : Binop(a, b) {}
            virtual double operate(double a, double b) {
                return a * b;
            }
            virtual string op() { return "*"; }
        };

        class Divider: public Binop {
        public:
            virtual ~Divider() {}
            Divider(SchemeExpression *a, SchemeExpression *b) : Binop(a, b) {}
            virtual double operate(double a, double b) {
                return a / b;
            }
            virtual string op() { return "/"; }
        };

    } // end namespace Arithmetic
} // end namespace AbstractSyntax

#endif /* ARITHMETIC_H_ */
