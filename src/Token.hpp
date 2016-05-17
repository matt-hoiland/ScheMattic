#ifndef TOKEN_HPP_
#define TOKEN_HPP_

#include <cctype>
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace Token {

    // Interfaces
    class IToken {
    private:
        string value;
    public:
        IToken(string v) : value(v) {}
        virtual ~IToken() {}
        string Value() { return value; }
    };
    class IState {
    public:
        IState() {}
        virtual ~IState() {}

        virtual bool process(char data, string sym, IState*& next, IToken*& emitted) = 0;
    };

    // Tokens
    class Symbol: public IToken {
    public:
        Symbol(string s) : IToken(s) {}
        virtual ~Symbol() {}
    };
    class OpenParen: public IToken {
    public:
        OpenParen() : IToken("(") {}
        virtual ~OpenParen() {}
    };
    class CloseParen: public IToken {
    public:
        CloseParen() : IToken(")") {}
        virtual ~CloseParen() {}
    };
    class String: public IToken {
    public:
        String(string s) : IToken(s) {}
        virtual ~String() {}
    };

    // States
    class StartState: public IState {
    public:
        virtual bool process(char data, string sym, IState*& next, IToken*& emitted);
    };
    class WhiteSpaceState: public IState {
    public:
        virtual bool process(char data, string sym, IState*& next, IToken*& emitted);
    };
    class OpenParenState: public IState {
    public:
        virtual bool process(char data, string sym, IState*& next, IToken*& emitted);
    };
    class CloseParenState: public IState {
    public:
        virtual bool process(char data, string sym, IState*& next, IToken*& emitted);
    };
    class SymbolState: public IState {
    public:
        virtual bool process(char data, string sym, IState*& next, IToken*& emitted);
    };
    class StringState: public IState {
    public:
        virtual bool process(char data, string sym, IState*& next, IToken*& emitted);
    };
    class StopState: public IState {
    public:
        virtual bool process(char data, string sym, IState*& next, IToken*& emitted);
    };

    class TokenStream {
    private:
        vector<IToken*> tokens;
        unsigned int i = 0;
    public:
        TokenStream(string line) {
            line += "$";
            IState* state = new StartState();
            IState* next = NULL;
            IToken* emitted = NULL;
            int last = 0;
            for (unsigned int i = 0; i < line.size(); i++) {
                if (state->process(line[i], line.substr(last, i - last), next, emitted)) {
                    delete state;
                    state = next;
                    last = i;
                    if (emitted) tokens.push_back(emitted);
                }
            }
            delete state;
        }
        virtual ~TokenStream() {
            for (auto t : tokens) {
                delete t;
            }
        }

        bool hasNext() { return i < tokens.size(); }
        IToken* next() { return tokens[i++]; }
        void advance() { i++; }
        void retreat() { i--; }
    };

} // end namespace Token

#endif /* TOKEN_HPP_ */
