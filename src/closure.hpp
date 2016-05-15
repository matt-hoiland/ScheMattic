#ifndef CLOSURE_HPP_
#define CLOSURE_HPP_

#include "result.hpp"
#include "Environment.hpp"
#include "abstract.hpp"

namespace ResultSyntax {
    class ClosureValue: public Value {
    private:
        Environment env;
        vector<string> params;
        AbstractSyntax::SchemeExpression* body;
    public:
        ClosureValue(Environment env, vector<string> params, AbstractSyntax::SchemeExpression* body)
            : env(env), params(params), body(body) {}
        virtual ~ClosureValue() { delete body; }
        virtual Value* clone() { return new ClosureValue(env, params, body->clone()); }
        Environment getEnv() { return env; }
        vector<string> getParams() { return params; }
        AbstractSyntax::SchemeExpression* getBody() { return body; }
        virtual string toString() {
            // cout<< "making bacon pancakes" << endl;
            ostringstream out;
            out << "(closure (";
            for (unsigned int i = 0; i < params.size(); i++) {
                out << params[i] << (i < params.size() - 1 ? " " : "");
            }
            // cout<< "body: " << (body ? body->toString() : "null") << endl;
            out << ") " << body->toString() << " ";
            out << env.toString();
            // cout<< "env to string didn't fail us now" << endl;
            out << ")";
            return out.str();
        }
    };
} // end namespace ResultSyntax

#endif
