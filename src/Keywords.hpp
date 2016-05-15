#ifndef KEYWORDS_HPP_
#define KEYWORDS_HPP_

#include "abstract.hpp"
#include "interpreter.hpp"
#include "String.hpp"
#include "Symbol.hpp"

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
            virtual SchemeExpression* eval(Environment& env) {
                Interpreter::FileInterpreter filer(file->Value() + ".scheme");
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
            virtual SchemeExpression* eval(Environment& env) {
                SchemeExpression* s = cond->eval(env);
                Boolean* b = dynamic_cast<Boolean*>(s);
                SchemeExpression* ret = NULL;
                if (b) {
                    if (b->Value()) {
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
            virtual SchemeExpression* eval(Environment& env) {
                Symbol *symbol = dynamic_cast<Symbol*>(sym);
                if (symbol) {
                    SchemeExpression* be = bond->eval(env);
                    env.bind(symbol->Value(), be);
                    return be->eval(env);
                } else {
                    return NULL;
                }
            }
            virtual string toString() {
                return "(define " + sym->toString() + " " + bond->toString() + ")";
            }
        };

        class Closure: public KE {
        private:
            Environment env;
            vector<string> params;
            SchemeExpression *body;
        public:
            Closure(Environment env, vector<string> params, SchemeExpression *body)
                : env(env), params(params), body(body) {}
            virtual ~Closure() { delete body; }
            virtual SchemeExpression* clone() { return new Closure(env, params, body->clone()); }
            Environment getEnv() { return env; }
            vector<string> getParams() { return params; }
            SchemeExpression* getBody() { return body; }
            virtual SchemeExpression* eval(Environment& env) {
                return new Closure(this->env, params, body->eval(env));
            }
            virtual string toString() {
                ostringstream out;
                out << "(closure (";
                for (unsigned int i = 0; i < params.size(); i++) {
                    out << params[i] << (i < params.size() - 1 ? " " : "");
                }
                out << ") " << body->toString() << " ";
                out << env.toString();
                out << ")";
                return out.str();
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
            virtual SchemeExpression* eval(Environment& env) {
                return new Closure(env, params, body->eval(env));
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
            virtual SchemeExpression* eval(Environment& env) {
                SchemeExpression* ret = NULL;
                if (exprs.size() == 0) { return NULL; }
                cout << "Application eval" << endl;
                cout << exprs[0]->toString() << endl;
                SchemeExpression *first = exprs[0]->eval(env);
                Closure *func = dynamic_cast<Closure*>(first);
                cout << first->toString() << endl;
                if (func) {
                    Environment boundEnv = func->getEnv();
                    vector<string> paramSyms = func->getParams();
                    SchemeExpression* boundBody = func->getBody();
                    if (paramSyms.size() == exprs.size() - 1) {
                        for (unsigned int i = 1; i < exprs.size(); i++) {
                            boundEnv.bind(paramSyms[i - 1], exprs[i]->eval(env));
                        }
                        cout << boundEnv.toString() << endl;
                        cout << boundBody->toString() << endl;
                        ret = boundBody->eval(boundEnv);
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
