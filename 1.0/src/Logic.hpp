#ifndef LOGIC_HPP_
#define LOGIC_HPP_

#include "AbstractSyntax.hpp"

using ResultSyntax::BooleanValue;
using ResultSyntax::Value;

namespace AbstractSyntax {
    namespace Logic {

        class BE: public SchemeExpression {
        public:
            virtual ~BE() {}
        };

        class Boolean: public BE {
        private:
            bool b;
        public:
            Boolean(bool b) : b(b) {}
            virtual ~Boolean() {}
            bool data() { return b; }
            virtual Value* eval(Environment& env) { return new BooleanValue(b); }
            virtual SchemeExpression* clone() { return new Boolean(b); }
            virtual string toString() { return (b ? "true" : "false"); }
        };

        class Linop: public BE {
        public:
            SchemeExpression *a, *b;
        public:
            Linop(SchemeExpression *a, SchemeExpression *b) : a(a), b(b) {}
            virtual ~Linop() { delete a; delete b;}
            virtual Value* eval(Environment& env) {
                Value* arg1 = a->eval(env);
                Value* arg2 = b->eval(env);
                BooleanValue *b1 = NULL, *b2 = NULL;
                if (((b1 = dynamic_cast<BooleanValue*>(arg1)) != NULL) &&
                    ((b2 = dynamic_cast<BooleanValue*>(arg2)) != NULL)) {
                    bool r = op(b1->val(), b2->val());
                    delete b1;
                    delete b2;
                    return new BooleanValue(r);
                }
                delete arg1;
                delete arg2;
                return NULL;
            }
            virtual string toString() {
                return "(" + name() + " " + a->toString() + " " + b->toString() + ")";
            }
        protected:
            virtual bool op(bool a, bool b) = 0;
            virtual string name() = 0;
        };

        class And: public Linop {
        public:
            And(SchemeExpression *a, SchemeExpression *b) : Linop(a, b) {}
            virtual ~And() {}
            virtual SchemeExpression* clone() { return new And(a->clone(), b->clone()); }
        protected:
            virtual bool op(bool a, bool b) { return a && b; }
            virtual string name() { return "and"; }
        };

        class Or: public Linop {
        public:
            Or(SchemeExpression *a, SchemeExpression *b) : Linop(a, b) {}
            virtual ~Or() {}
            virtual SchemeExpression* clone() { return new And(a->clone(), b->clone()); }
        protected:
            virtual bool op(bool a, bool b) { return a || b; }
            virtual string name() { return "or"; }
        };

        class Not: public BE {
        private:
            SchemeExpression *a;
        public:
            Not(SchemeExpression *a) : a(a) {}
            virtual ~Not() { delete a; }
            virtual SchemeExpression* clone() { return new Not(a->clone()); }
            virtual Value* eval(Environment& env) {
                if (!a) return NULL;
                Value* arg1 = a->eval(env);
                BooleanValue *b1 = NULL;
                if (((b1 = dynamic_cast<BooleanValue*>(arg1)) != NULL)) {
                    bool b = !b1->val();
                    delete b1;
                    return new BooleanValue(b);
                }
                delete arg1;
                return NULL;
            }
            virtual string toString() {
                return "(not " + a->toString() + ")";
            }
        };

    } // end namespace Logic
} // end namespace AbstractSyntax

#endif /* LOGIC_HPP_ */
