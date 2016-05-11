#include "concrete.hpp"

using namespace ConcreteSyntax;
using namespace token;

using std::invalid_argument;
using std::out_of_range;
using std::string;

SExpression* Parser::parse(token::TokenStream& tokens) {
    if (!tokens.hasNext()) { return NULL; }
    IToken* token = tokens.next();
    if (dynamic_cast<OpenParen*>(token)) {
        return parseList(tokens);
    } else if (dynamic_cast<Symbol*>(token)) {
        return parseSymbol(dynamic_cast<Symbol*>(token));
    } else if (dynamic_cast<CloseParen*>(token)) {
        throw invalid_syntax();
    } else if (dynamic_cast<String*>(token)) {
        return parseString(dynamic_cast<String*>(token));
    } else {
        return NULL;
    }
}

SExpression* Parser::parseList(token::TokenStream& tokens) {
    if (!tokens.hasNext()) { throw invalid_syntax(); }
    IToken* token = tokens.next();
    ListExpression* ret = new ListExpression();
    while (!dynamic_cast<CloseParen*>(token)) {
        tokens.retreat();
        ret->add(parse(tokens));
        if (tokens.hasNext()) {
            token = tokens.next();
        } else {
            throw invalid_syntax();
        }
    }
    return ret;
}

SExpression* Parser::parseSymbol(Symbol* token) {
    try {
        double d = stod(token->Value());
        return new NumberExpression(d);
    } catch (...) {
        if (token->Value() == "true" || token->Value() == "false") {
            return new BooleanExpression(token->Value() == "true");
        }
        return new SymbolExpression(token->Value());
    }
}

SExpression* Parser::parseString(String* token) {
    return new StringExpression(token->Value());
}
