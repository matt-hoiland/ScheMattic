#ifndef ARITHMETIC_HPP_
#define ARITHMETIC_HPP_

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
            virtual SchemeExpression* eval(Environment& env) { return new Number(d); }
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
            virtual SchemeExpression* eval(Environment& env) {
                SchemeExpression *sa = a->eval(env), *sb = b->eval(env);
                Number* A = dynamic_cast<Number*>(sa);
                Number* B = dynamic_cast<Number*>(sb);
                SchemeExpression* ret = NULL;
                if (A && B) {
                    ret = new Number(operate(A->Value(), B->Value()));
                    delete A;
                    delete B;
                    return ret;
                }
                return make(sa, sb);
            }
            virtual string toString() {
                ostringstream out;
                out << "(" << op() << " " << a->toString() << " " << b->toString() << ")";
                return out.str();
            }
        protected:
            virtual double operate(double a, double d) = 0;
            virtual string op() = 0;
            virtual SchemeExpression* make(SchemeExpression* a, SchemeExpression* b) = 0;
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
            virtual SchemeExpression* make(SchemeExpression* a, SchemeExpression* b) {
                cout << "new adder: a " << a->toString() << ", b " << b->toString() << endl;
                return new Adder(a, b);
            }
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
            virtual SchemeExpression* make(SchemeExpression* a, SchemeExpression* b) {
                return new Subtracter(a, b);
            }
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
            virtual SchemeExpression* make(SchemeExpression* a, SchemeExpression* b) {
                return new Multiplier(a, b);
            }
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
            virtual SchemeExpression* make(SchemeExpression* a, SchemeExpression* b) {
                return new Divider(a, b);
            }
        };

    } // end namespace Arithmetic
} // end namespace AbstractSyntax

#endif /* ARITHMETIC_HPP_ */
