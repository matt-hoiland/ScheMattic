#include "AbstractSyntax.hpp"
#include "Comparator.hpp"
#include "Keywords.hpp"

using AbstractSyntax::Arithmetic::Adder;
using AbstractSyntax::Arithmetic::Divider;
using AbstractSyntax::Arithmetic::Multiplier;
using AbstractSyntax::Arithmetic::Number;
using AbstractSyntax::Arithmetic::Subtracter;
using AbstractSyntax::Comparator::LessThan;
using AbstractSyntax::Comparator::LessEqual;
using AbstractSyntax::Comparator::Equal;
using AbstractSyntax::Comparator::GreaterEqual;
using AbstractSyntax::Comparator::GreaterThan;
using AbstractSyntax::Logic::And;
using AbstractSyntax::Logic::Boolean;
using AbstractSyntax::Logic::Or;
using AbstractSyntax::Logic::Not;
using AbstractSyntax::Keyword::Application;
using AbstractSyntax::Keyword::Conditional;
using AbstractSyntax::Keyword::Definition;
using AbstractSyntax::Keyword::Import;
using AbstractSyntax::Keyword::Lambda;
using ConcreteSyntax::BooleanExpression;
using ConcreteSyntax::ListExpression;
using ConcreteSyntax::NumberExpression;
using ConcreteSyntax::StringExpression;
using ConcreteSyntax::SymbolExpression;

namespace AbstractSyntax {
    SchemeExpression* Parser::parse(ConcreteSyntax::SExpression* sexp) {
        if (dynamic_cast<SymbolExpression*>(sexp)) {
            return new Symbol(((SymbolExpression*)sexp)->symbol());
        } else if (dynamic_cast<ListExpression*>(sexp)) {
            ListExpression* li = (ListExpression*) sexp;
            if (li->size() == 3) {
                SchemeExpression* a = parse((*li)[1]);
                SchemeExpression* b = parse((*li)[2]);
                SymbolExpression* op = dynamic_cast<SymbolExpression*>((*li)[0]);
                if (op) {
                    string s = op->symbol();
                    switch (s[0]) {
                    case '+': return new Adder(a, b);
                    case '-': return new Subtracter(a, b);
                    case '*': return new Multiplier(a, b);
                    case '/': return new Divider(a, b);
                    }
                    if (s == "and") {
                        return new And(a, b);
                    } else if (s == "or") {
                        return new Or(a, b);
                    } else if (s == "<") {
                        return new LessThan(a, b);
                    } else if (s == "<=") {
                        return new LessEqual(a, b);
                    } else if (s == "=") {
                        return new Equal(a, b);
                    } else if (s == ">=") {
                        return new GreaterEqual(a, b);
                    } else if (s == ">") {
                        return new GreaterThan(a, b);
                    } else if (s == "define") {
                        return new Definition(a, b);
                    } else if (s == "lambda") {
                        ListExpression* plist = dynamic_cast<ListExpression*>((*li)[1]);
                        if (plist) {
                            vector<string> params;
                            for (unsigned int i = 0; i < plist->size(); i++) {
                                SymbolExpression* sym = dynamic_cast<SymbolExpression*>((*plist)[i]);
                                if (sym) {
                                    params.push_back(sym->symbol());
                                } else {
                                    delete b;
                                    return NULL;
                                }
                            }
                            delete a;
                            return new Lambda(params, b);
                        }
                    }
                }
                delete a;
                delete b;
            } else if (li->size() == 2) {
                SchemeExpression* a = parse((*li)[1]);
                SymbolExpression* op = dynamic_cast<SymbolExpression*>((*li)[0]);
                if (op) {
                    string s = op->symbol();
                    if (s == "not") {
                        return new Not(a);
                    } else if (s == "import") {
                        String* s = dynamic_cast<String*>(a);
                        if (s) { return new Import(s); }
                    }
                }
                delete a;
            } else if (li->size() == 4) {
                SchemeExpression* cond = parse((*li)[1]);
                SchemeExpression* cons = parse((*li)[2]);
                SchemeExpression* alt = parse((*li)[3]);
                SymbolExpression* op = dynamic_cast<SymbolExpression*>((*li)[0]);
                if (op) {
                    string s = op->symbol();
                    if (s == "if") {
                        return new Conditional(cond, cons, alt);
                    }
                }
                delete cond;
                delete cons;
                delete alt;
            }
            if (li->size() > 1) {
                vector<SchemeExpression*> exprs;
                for (unsigned int i = 0; i < li->size(); i++) {
                    exprs.push_back(parse((*li)[i]));
                }
                return new Application(exprs);
            }
        } else if (dynamic_cast<NumberExpression*>(sexp)) {
            return new Number(((NumberExpression*)sexp)->data());
        } else if (dynamic_cast<BooleanExpression*>(sexp)) {
            return new Boolean(((BooleanExpression*)sexp)->data());
        } else if (dynamic_cast<StringExpression*>(sexp)) {
            return new String(((StringExpression*)sexp)->data());
        } else {
            return NULL;
        }
        return NULL;
    }
}
