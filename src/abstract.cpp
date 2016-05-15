#include "abstract.hpp"
#include "Arithmetic.hpp"
#include "Comparator.hpp"
#include "concrete.hpp"
using ConcreteSyntax::BooleanExpression;
using ConcreteSyntax::ListExpression;
using ConcreteSyntax::NumberExpression;
using ConcreteSyntax::StringExpression;
using ConcreteSyntax::SymbolExpression;
#include "Logic.hpp"
#include "Keywords.hpp"
#include "Symbol.hpp"

namespace AbstractSyntax {
    SchemeExpression* parse(ConcreteSyntax::SExpression* sexp) {
        if (dynamic_cast<ListExpression*>(sexp)) {
            ListExpression* li = (ListExpression*) sexp;
            if (li->size() == 3) {
                SchemeExpression* a = parse((*li)[1]);
                SchemeExpression* b = parse((*li)[2]);
                SymbolExpression* op = dynamic_cast<SymbolExpression*>((*li)[0]);
                if (op) {
                    string s = op->symbol();
                    switch (s[0]) {
                    case '+': return new Arithmetic::Adder(a, b);
                    case '-': return new Arithmetic::Subtracter(a, b);
                    case '*': return new Arithmetic::Multiplier(a, b);
                    case '/': return new Arithmetic::Divider(a, b);
                    }
                    if (s == "and") {
                        return new Logic::And(a, b);
                    } else if (s == "or") {
                        return new Logic::Or(a, b);
                    } else if (s == "<") {
                        return new Comparator::LessThan(a, b);
                    } else if (s == "<=") {
                        return new Comparator::LessEqual(a, b);
                    } else if (s == "=") {
                        return new Comparator::Equal(a, b);
                    } else if (s == ">=") {
                        return new Comparator::GreaterEqual(a, b);
                    } else if (s == ">") {
                        return new Comparator::GreaterThan(a, b);
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
                        return new Logic::Not(a);
                    } else if (s == "import") {
                        String* s = dynamic_cast<String*>(a);
                        if (a) { return new Keyword::Import(s); }
                    }
                }
            } else if (li->size() == 4) {
                SchemeExpression* cond = parse((*li)[1]);
                SchemeExpression* cons = parse((*li)[2]);
                SchemeExpression* alt = parse((*li)[3]);
                SymbolExpression* op = dynamic_cast<SymbolExpression*>((*li)[0]);
                if (op) {
                    string s = op->symbol();
                    if (s == "if") {
                        return new Keyword::Conditional(cond, cons, alt);
                    }
                }
            }
        } else if (dynamic_cast<SymbolExpression*>(sexp)) {
            return new Symbol(((SymbolExpression*)sexp)->symbol());
        } else if (dynamic_cast<NumberExpression*>(sexp)) {
            return new Arithmetic::Number(((NumberExpression*)sexp)->data());
        } else if (dynamic_cast<BooleanExpression*>(sexp)) {
            return new Logic::Boolean(((BooleanExpression*)sexp)->data());
        } else if (dynamic_cast<StringExpression*>(sexp)) {
            return new String(((StringExpression*)sexp)->data());
        } else {
            return NULL;
        }
        return NULL;
    }
}
