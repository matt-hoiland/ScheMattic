#ifndef KEYWORDS_HPP_
#define KEYWORDS_HPP_

#include "abstract.hpp"
#include "interpreter.hpp"

namespace AbstractSyntax {
    namespace Keyword {

        class KE: public SchemeExpression {
        public:
            virtual ~KE () {}
        };

        class Import: public KE {
        private:
            String* file;
        public:
            Import(String* f) : file(f) {}
            virtual ~Import() { delete file; }

            virtual SchemeExpression* eval() {
                Interpreter::FileInterpreter filer(file->Value() + ".scheme");
                filer.interpret(cout);
                return NULL;
            }

            virtual string toString() {
                return "(import " + file->toString() + ")";
            }
        };

        class Conditional: public KE {
        private:
            SchemeExpression *cond, *cons, *alt;
        public:
            Conditional(SchemeExpression *b, SchemeExpression *c, SchemeExpression* a)
                : cond(b), cons(c), alt(a) {}
            virtual ~Conditional() { delete cond; delete cons; delete alt; }
            virtual SchemeExpression* eval() {
                SchemeExpression* s = cond->eval();
                Boolean* b = dynamic_cast<Boolean*>(s);
                SchemeExpression* ret = NULL;
                if (b) {
                    if (b->Value()) {
                        ret = cons->eval();
                    } else {
                        ret = alt->eval();
                    }
                }
                delete s;
                return ret;
            }
            virtual string toString() {
                return "(if " + cond->toString() + " " + cons->toString() + " " + alt->toString() + ")";
            }
        };

    } // end namespace Keyword
} // end namespace AbstractSyntax

#endif /* KEYWORDS_HPP_ */
