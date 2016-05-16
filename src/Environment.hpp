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
            Binding* clone() {
                Binding *n = (next ? next->clone() : NULL);
                return new Binding(var, bond->clone(), n);
            }
        } *head = NULL;
    public:
        Environment() {}
        Environment(const Environment& env) {
            this->head = (env.head ? env.head->clone() : NULL);
        }
        virtual ~Environment() {
            while (head != NULL) {
                Binding *b = head;
                head = head->next;
                delete b;
            }
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
            for (Binding *b = head; b != NULL; b = b->next) {
                out << " {" << b->var << " " << b->bond->toString() << "}";
            }
            out << ")";
            return out.str();
        }

        void clear() {
            while (head != NULL) unbind();
        }
    };

} // end namespace AbstractSyntax

#endif /* ENVIRONMNET_HPP_ */
