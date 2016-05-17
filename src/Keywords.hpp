#ifndef KEYWORDS_HPP_
#define KEYWORDS_HPP_

#include "AbstractSyntax.hpp"
#include "Closure.hpp"
#include "Interpreter.hpp"
#include "String.hpp"
#include "Symbol.hpp"

using Interpreter::FileInterpreter;
using ResultSyntax::BooleanValue;
using ResultSyntax::ClosureValue;
using ResultSyntax::Value;
using std::cout;

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
            virtual SchemeExpression* clone() { return new Import(file); }
            virtual Value* eval(Environment& env) {
                FileInterpreter filer(file->data() + ".scheme");
                filer.interpret(cout, env);
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
            virtual SchemeExpression* clone() { return new Conditional(cond->clone(), cons->clone(), alt->clone()); }
            virtual Value* eval(Environment& env) {
                Value* s = cond->eval(env);
                BooleanValue* b = dynamic_cast<BooleanValue*>(s);
                Value* ret = NULL;
                if (b) {
                    if (b->val()) {
                        ret = cons->eval(env);
                    } else {
                        ret = alt->eval(env);
                    }
                }
                delete s;
                return ret;
            }
            virtual string toString() {
                return "(if " + cond->toString() + " " + cons->toString() + " " + alt->toString() + ")";
            }
        };

        class Definition: public KE {
        private:
            SchemeExpression *sym, *bond;
        public:
            Definition(SchemeExpression *sym, SchemeExpression *bond) : sym(sym), bond(bond) {}
            virtual ~Definition() { delete sym; delete bond; }
            virtual SchemeExpression* clone() { return new Definition(sym->clone(), bond->clone()); }
            virtual Value* eval(Environment& env) {
                Symbol *symbol = dynamic_cast<Symbol*>(sym);
                if (symbol) {
                    Value* be = bond->eval(env);
                    env.bind(symbol->data(), be);
                    return be->clone();
                } else {
                    return NULL;
                }
            }
            virtual string toString() {
                return "(define " + sym->toString() + " " + bond->toString() + ")";
            }
        };

        class Lambda: public KE {
        private:
            vector<string> params;
            SchemeExpression *body;
        public:
            Lambda(vector<string> params, SchemeExpression* body) : params(params), body(body) {}
            virtual ~Lambda() { delete body; }
            virtual SchemeExpression* clone() { return new Lambda(params, body->clone()); }
            virtual Value* eval(Environment& env) {
                SchemeExpression* clone = body->clone();
                return new ClosureValue(env, params, clone);
            }
            virtual string toString() {
                ostringstream out;
                out << "(lambda (";
                for (unsigned int i = 0; i < params.size(); i++) {
                    out << params[i] << (i < params.size() - 1 ? " " : "");
                }
                out << ") " << body->toString() << ")";
                return out.str();
            }
        };

        class Application: public KE {
        private:
            vector<SchemeExpression*> exprs;
        public:
            Application(vector<SchemeExpression*> exprs) : exprs(exprs) {}
            virtual ~Application() {
                for (auto e : exprs) {
                    delete e;
                }
            }
            virtual SchemeExpression* clone() {
                vector<SchemeExpression*> clones;
                for (auto e : exprs) {
                    clones.push_back(e->clone());
                }
                return new Application(clones);
            }
            virtual Value* eval(Environment& env) {
                Value* ret = NULL;
                if (exprs.size() == 0) { return NULL; }
                Value *first = exprs[0]->eval(env);
                ClosureValue *func = dynamic_cast<ClosureValue*>(first);
                if (func) {
                    Environment boundEnv = func->getEnv();
                    vector<string> paramSyms = func->getParams();
                    SchemeExpression* boundBody = func->getBody();
                    if (paramSyms.size() == exprs.size() - 1) {
                        for (unsigned int i = 1; i < exprs.size(); i++) {
                            boundEnv.bind(paramSyms[i - 1], exprs[i]->eval(env));
                        }
                        ret = boundBody->eval(boundEnv);
                        for (unsigned int i = 0; i < paramSyms.size(); i++) {
                            boundEnv.unbind();
                        }
                    }
                }
                delete first;
                return ret;
            }
            virtual string toString() {
                ostringstream out;
                out << "(";
                for (unsigned int i = 0; i < exprs.size(); i++) {
                    out << exprs[i]->toString() << (i < exprs.size() - 1 ? " " : "");
                }
                out << ")";
                return out.str();
            }
        };

    } // end namespace Keyword
} // end namespace AbstractSyntax

#endif /* KEYWORDS_HPP_ */
