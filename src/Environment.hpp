#ifndef ENVIRONMNET_HPP_
#define ENVIRONMNET_HPP_

#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;

#include "result.hpp"

namespace ResultSyntax {
    class Environment {
    private:
        struct Binding {
            string var;
            Value* bond;
            Binding* next;
            Binding(string k, Value *v, Binding *n = NULL)
                : var(k), bond(v), next(n) {}
            virtual ~Binding() { delete bond; }
        } *head = NULL;
    public:
        Environment() {}
        virtual ~Environment() {
            // // cout<< "Dying..." << endl;
            // while (head != NULL) {
            //     Binding *b = head;
            //     // cout<< "k: " << b->var << ", v: " << b->bond->toString() << endl;
            //     head = head->next;
            //     delete b;
            // }
        }

        void bind(string k, Value *v) {
            head = new Binding(k, v, head);
        }

        void unbind() {
            if (head == NULL) return;
            Binding *b = head;
            head = head->next;
            delete b;
        }

        Value* find(string k) {
            for (Binding *b = head; b != NULL; b = b->next) {
                if (b->var == k) { return b->bond; }
            }
            return NULL;
        }

        string toString() {
            ostringstream out;
            out << "(env";
            // cout<< "stringin' the environs" << endl;
            for (Binding *b = head; b != NULL; b = b->next) {
                // cout<< "k: " << b->var << ", v: " << (b->bond ? b->bond->toString() : "null") << endl;
                out << " {" << b->var << " " << b->bond->toString() << "}";
            }
            // cout<< "we finished: ";
            out << ")";
            // cout<< out.str() << endl;
            return out.str();
        }

        void clear() {
            while (head != NULL) unbind();
        }
    };

} // end namespace AbstractSyntax

#endif /* ENVIRONMNET_HPP_ */
