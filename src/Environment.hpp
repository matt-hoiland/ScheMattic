#ifndef ENVIRONMNET_HPP_
#define ENVIRONMNET_HPP_

#include <string>
using std::string;

#include "abstract.hpp"

namespace AbstractSyntax {

    class Environment {
    private:
        struct Binding {
            string var;
            SchemeExpression* bond;
            Binding *next;
            Binding(string k, SchemeExpression *v, Binding *n = NULL)
                : var(k), bond(v), next(n) {}
        } *head = NULL;
    public:
        Environment() {}
        virtual ~Environment() {
            while (head != NULL) {
                Binding *b = head;
                head = head->next;
                delete b;
            }
        }

        void bind(string k, SchemeExpression *v) {
            head = new Binding(k, v, head);
        }

        SchemeExpression* find(string k) {
            for (Binding *b = head; b != NULL; b = b->next) {
                if (b->var == k) { return b->bond; }
            }
            return NULL;
        }
    };

} // end namespace AbstractSyntax

#endif /* ENVIRONMNET_HPP_ */
