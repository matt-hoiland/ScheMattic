#include "Token.hpp"

bool token::StartState::process(char data, string sym, IState*& next, IToken*& emitted) {
    if (isspace(data)) {
        next = new WhiteSpaceState();
        emitted = NULL;
        return true;
    } else {
        switch (data) {
        case '(':
            next = new OpenParenState();
            break;
        case ')':
            next = new CloseParenState();
            break;
        case '$':
            next = new StopState();
            break;
        case '\"':
            next = new StringState();
            break;
        default:
            next = new SymbolState();
            break;
        }
        emitted = NULL;
        return true;
    }
}

bool token::WhiteSpaceState::process(char data, string sym, IState*& next, IToken*& emitted) {
    if (isspace(data)) { return false; }
    switch (data) {
    case '(':
        next = new OpenParenState();
        break;
    case ')':
        next = new CloseParenState();
        break;
    case '$':
        next = new StopState();
        break;
    case '\"':
        next = new StringState();
        break;
    default:
        next = new SymbolState();
        break;
    }
    emitted = NULL;
    return true;
}

bool token::OpenParenState::process(char data, string sym, IState*& next, IToken*& emitted) {
    emitted = new OpenParen();
    if (isspace(data)) {
        next = new WhiteSpaceState();
    } else if (data == '(') {
        next = new OpenParenState();
    } else if (data == ')') {
        next = new CloseParenState();
    } else if (data == '\"') {
        next = new StringState();
    } else if (data == '$') {
        next = new StopState();
    } else {
        next = new SymbolState();
    }
    return true;
}

bool token::CloseParenState::process(char data, string sym, IState*& next, IToken*& emitted) {
    emitted = new CloseParen();
    if (isspace(data)) {
        next = new WhiteSpaceState();
    } else if (data == '(') {
        next = new OpenParenState();
    } else if (data == ')') {
        next = new CloseParenState();
    } else if (data == '\"') {
        next = new StringState();
    } else if (data == '$') {
        next = new StopState();
    } else {
        next = new SymbolState();
    }
    return true;
}

bool token::SymbolState::process(char data, string sym, IState*& next, IToken*& emitted) {
    if (isspace(data)) {
        next = new WhiteSpaceState();
    } else if (data == '(') {
        next = new OpenParenState();
    } else if (data == ')') {
        next = new CloseParenState();
    } else if (data == '\"') {
        next = new StringState();
    } else if (data == '$') {
        next = new StopState();
    } else {
        return false;
    }
    emitted = new Symbol(sym);
    return true;
}

bool token::StopState::process(char data, string sym, IState*& next, IToken*& emitted) {
    return false;
}

bool token::StringState::process(char data, string sym, IState*& next, IToken*& emitted) {
    if (data == '$') {
        next = new StopState();
    } else if (data == '\"') {
        next = new StartState();
    } else {
        return false;
    }
    emitted = new String(sym.substr(1));
    return true;
}
