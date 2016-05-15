#ifndef COMPARATOR_HPP_
#define COMPARATOR_HPP_

#include "abstract.hpp"
#include "Arithmetic.hpp"
using AbstractSyntax::Arithmetic::Number;
#include "Logic.hpp"
using AbstractSyntax::Logic::Boolean;

namespace AbstractSyntax {
    namespace Comparator {

        class CE: public SchemeExpression {
        public:
            virtual ~CE() {}
        };

        class NumericComparator: public CE {
        protected:
            SchemeExpression *a, *b;
        public:
            NumericComparator(SchemeExpression* a, SchemeExpression* b) : a(a), b(b) {}
            virtual ~NumericComparator() { delete a; delete b; }
            virtual SchemeExpression* eval(Environment& env) {
                SchemeExpression* sa = a->eval(env);
                SchemeExpression* sb = b->eval(env);
                SchemeExpression* sc = NULL;
                Number *na = NULL, *nb = NULL;
                if ((na = dynamic_cast<Number*>(sa)) != NULL &&
                    (nb = dynamic_cast<Number*>(sb)) != NULL) {
                    double da = na->Value();
                    double db = nb->Value();
                    sc = new Boolean(compare(da, db));
                }
                delete sb;
                delete sa;
                return sc;
            }
            virtual string toString() {
                return "(" + name() + " " + a->toString() + " " + b->toString() + ")";
            }
        protected:
            virtual bool compare(double a, double b) = 0;
            virtual string name() = 0;
        };

        class LessThan: public NumericComparator {
        public:
            LessThan(SchemeExpression* a, SchemeExpression* b) : NumericComparator(a, b) {}
            virtual ~LessThan() {}
            virtual SchemeExpression* clone() { return new LessThan(a->clone(), b->clone()); }
        protected:
            virtual bool compare(double a, double b) { return a < b; }
            virtual string name() { return "<"; }
        };

        class LessEqual: public NumericComparator {
        public:
            LessEqual(SchemeExpression* a, SchemeExpression* b) : NumericComparator(a, b) {}
            virtual ~LessEqual() {}
            virtual SchemeExpression* clone() { return new LessEqual(a->clone(), b->clone()); }
        protected:
            virtual bool compare(double a, double b) { return a <= b; }
            virtual string name() { return "<="; }
        };

        class GreaterEqual: public NumericComparator {
        public:
            GreaterEqual(SchemeExpression* a, SchemeExpression* b) : NumericComparator(a, b) {}
            virtual ~GreaterEqual() {}
            virtual SchemeExpression* clone() { return new GreaterEqual(a->clone(), b->clone()); }
        protected:
            virtual bool compare(double a, double b) { return a >= b; }
            virtual string name() { return ">="; }
        };

        class GreaterThan: public NumericComparator {
        public:
            GreaterThan(SchemeExpression* a, SchemeExpression* b) : NumericComparator(a, b) {}
            virtual ~GreaterThan() {}
            virtual SchemeExpression* clone() { return new GreaterThan(a->clone(), b->clone()); }
        protected:
            virtual bool compare(double a, double b) { return a > b; }
            virtual string name() { return ">"; }
        };

        class Equal: public CE {
        private:
            SchemeExpression *a, *b;
        public:
            Equal(SchemeExpression* a, SchemeExpression* b) : a(a), b(b) {}
            virtual ~Equal() { delete a; delete b; }
            virtual SchemeExpression* clone() { return new Equal(a->clone(), b->clone()); }
            virtual SchemeExpression* eval(Environment& env) {
                SchemeExpression* sa = a->eval(env);
                SchemeExpression* sb = b->eval(env);
                SchemeExpression* sc = NULL;
                Boolean *ba = NULL, *bb = NULL;
                Number *na = NULL, *nb = NULL;
                if ((ba = dynamic_cast<Boolean*>(sa)) != NULL &&
                    (bb = dynamic_cast<Boolean*>(sb)) != NULL) {
                    bool da = ba->Value();
                    bool db = bb->Value();
                    sc = new Boolean(da == db);
                } else if ((na = dynamic_cast<Number*>(sa)) != NULL &&
                           (nb = dynamic_cast<Number*>(sb)) != NULL) {
                    double da = na->Value();
                    double db = nb->Value();
                    sc = new Boolean(da == db);
               }
                delete sb;
                delete sa;
                return sc;
            }
            virtual string toString() {
                return "(= " + a->toString() + " " + b->toString() + ")";
            }
        };

    } // end namespace Comparator
} // end namespace AbstractSyntax

#endif /* COMPARATOR_HPP_ */
