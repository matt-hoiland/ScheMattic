#include "concrete.hpp"

using namespace ConcreteSyntax;
using namespace token;

SExpression* Parser::parse(token::TokenStream& tokens) {
    if (!tokens.hasNext()) { return NULL; }
    IToken* token = tokens.next();
    if (dynamic_cast<OpenParen*>(token)) {
        return parseList(tokens);
    } else if (dynamic_cast<Symbol*>(token)) {
        return parseSymbol(dynamic_cast<Symbol*>(token));
    } else {
        return NULL;
    }
}

ListExpression* Parser::parseList(token::TokenStream& tokens) {
    if (!tokens.hasNext()) { return NULL; }
    IToken* token = tokens.next();
    ListExpression* ret = new ListExpression();
    while (!dynamic_cast<CloseParen*>(token)) {
        tokens.retreat();
        ret->add(parse(tokens));
        token = tokens.next();
    }
    return ret;
}

SymbolExpression* Parser::parseSymbol(Symbol* token) {
    return new SymbolExpression(token->Value());
}
