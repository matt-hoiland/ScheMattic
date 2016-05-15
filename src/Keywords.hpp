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

    } // end namespace Keyword
} // end namespace AbstractSyntax

#endif /* KEYWORDS_HPP_ */
