#ifndef LOGIC_H_
#define LOGIC_H_

#include "abstract.hpp"

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
            bool Value() { return b; }
            virtual SchemeExpression* eval() { return new Boolean(b); }
            virtual string toString() { return (b ? "true" : "false"); }
        };

        class Linop: public BE {
        private:
            SchemeExpression *a, *b;
        public:
            Linop(SchemeExpression *a, SchemeExpression *b) : a(a), b(b) {}
            virtual ~Linop() { delete a; delete b;}
            virtual SchemeExpression* eval() {
                SchemeExpression* arg1 = a->eval();
                SchemeExpression* arg2 = b->eval();
                Boolean *b1 = NULL, *b2 = NULL;
                if (((b1 = dynamic_cast<Boolean*>(arg1)) != NULL) &&
                    ((b2 = dynamic_cast<Boolean*>(arg2)) != NULL)) {
                    bool r = op(b1->Value(), b2->Value());
                    delete b1;
                    delete b2;
                    return new Boolean(r);
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
        protected:
            virtual bool op(bool a, bool b) { return a && b; }
            virtual string name() { return "and"; }
        };

        class Or: public Linop {
        public:
            Or(SchemeExpression *a, SchemeExpression *b) : Linop(a, b) {}
            virtual ~Or() {}
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
            virtual SchemeExpression* eval() {
                if (!a) return NULL;
                SchemeExpression* arg1 = a->eval();
                Boolean *b1 = NULL;
                if (((b1 = dynamic_cast<Boolean*>(arg1)) != NULL)) {
                    bool b = !b1->Value();
                    delete b1;
                    return new Boolean(b);
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

#endif /* LOGIC_H_ */
