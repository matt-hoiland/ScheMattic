#ifndef COMPARATOR_HPP_
#define COMPARATOR_HPP_

#include "AbstractSyntax.hpp"
#include "Arithmetic.hpp"
#include "Logic.hpp"

using AbstractSyntax::Arithmetic::Number;
using AbstractSyntax::Logic::Boolean;
using ResultSyntax::BooleanValue;
using ResultSyntax::NumberValue;
using ResultSyntax::Value;

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
            virtual Value* eval(Environment& env) {
                Value* sa = a->eval(env);
                Value* sb = b->eval(env);
                Value* sc = NULL;
                NumberValue *na = NULL, *nb = NULL;
                if ((na = dynamic_cast<NumberValue*>(sa)) != NULL &&
                    (nb = dynamic_cast<NumberValue*>(sb)) != NULL) {
                    double da = na->val();
                    double db = nb->val();
                    sc = new BooleanValue(compare(da, db));
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
            virtual Value* eval(Environment& env) {
                Value* sa = a->eval(env);
                Value* sb = b->eval(env);
                Value* sc = NULL;
                BooleanValue *ba = NULL, *bb = NULL;
                NumberValue *na = NULL, *nb = NULL;
                if ((ba = dynamic_cast<BooleanValue*>(sa)) != NULL &&
                    (bb = dynamic_cast<BooleanValue*>(sb)) != NULL) {
                    bool da = ba->val();
                    bool db = bb->val();
                    sc = new BooleanValue(da == db);
                } else if ((na = dynamic_cast<NumberValue*>(sa)) != NULL &&
                           (nb = dynamic_cast<NumberValue*>(sb)) != NULL) {
                    double da = na->val();
                    double db = nb->val();
                    sc = new BooleanValue(da == db);
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
