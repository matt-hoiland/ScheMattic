#ifndef RESULT_HPP_
#define RESULT_HPP_

#include <sstream>
#include <string>

using std::string;
using std::ostringstream;

namespace ResultSyntax {
    class Value {
    public:
        virtual ~Value() {}
        virtual Value* clone() = 0;
        virtual string toString() = 0;
    };

    class NumberValue: public Value {
    private:
        double d;
    public:
        NumberValue(double d) : d(d) {}
        virtual ~NumberValue() {}
        double val() { return d; }
        virtual Value* clone() { return new NumberValue(d); }
        virtual string toString() {
            ostringstream out;
            out << d;
            return out.str();
        }
    };

    class BooleanValue: public Value {
    private:
        bool b;
    public:
        BooleanValue(bool b) : b(b) {}
        virtual ~BooleanValue() {}
        bool val() { return b; }
        virtual Value* clone() { return new BooleanValue(b); }
        virtual string toString() { return (b ? "true" : "false"); }
    };

    class StringValue: public Value {
    private:
        string s;
    public:
        StringValue(string s) : s(s) {}
        virtual ~StringValue() {}
        string val() { return s; }
        virtual Value* clone() { return new StringValue(s); }
        virtual string toString() { return "\"" + s + "\""; }
    };
} // end namesapce ResultSyntax

#endif /* RESULT_HPP_ */
