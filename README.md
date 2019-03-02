# Sche{Matt}ic

A personal scheme interpreter

## Atomic Data Types:

- Double precision numbers ::= `AE`
- Strings ::= `STR`
- Boolean ::= `BE`
- Symbols ::= `SE`

## Core language features

- `define` ::= `(define SE E) -> None` -- Binds the result of the expression `E` to the symbolic expression `SE`. Ex:
    - `(define a 5)`
- `if` ::= `(if BE E E) -> E` -- evaluates to the first `E` (the consequent) if the condition is `true`, otherwise evaluates to the second `E` (the alternate). Ex:
    - `(if true 5 4)`
- `import` ::= `(import STR) -> None` -- imports and interprets the given filename into the current environment line by line.
    - `(import "arithmetic")`

## Arithmetic

- `+` ::= `(+ AE AE) -> AE`
- `-` ::= `(- AE AE) -> AE`
- `*` ::= `(* AE AE) -> AE`
- `/` ::= `(/ AE AE) -> AE`

## Boolean logic

- `and` ::= `(and BE BE) -> BE`
- `or` ::= `(or BE BE) -> BE`
- `not` ::= `(not BE) -> BE`

## Arithmetic comparison

- `<` ::= `(< AE AE) -> BE`
- `<=` ::= `(<= AE AE) -> BE`
- `==` ::= `(== AE AE) -> BE`
- `>=` ::= `(>= AE AE) -> BE`
- `>` ::= `(> AE AE) -> BE`

---

# 2017.06.02 -- ScheMattic 2.0

## Syntax

```
expr ::= sexpr | literal
sexpr ::= "(" SYMBOL expr* ")"
literal ::= NUMBER | SYMBOL | BOOLEAN | STRING | CHARACTER
SYMBOL ::= /[A-Za-z_][0-9A-Za-z_]*/
NUMBER ::= /[-+]?([0-9]*\.?[0-9]+|[0-9]+)/
BOOLEAN ::= /true/ | /false/
STRING ::= <traditional c-string syntax, including escapes>
CHARACTER ::= /'\c'/
```

## Value types:

- Number
- Boolean
- String
- Character
- Pair
- Closure

## Reserved symbols

### Core structure makers

- bind ::=
    - (bind SYMBOL expr) -> binds the value of the given sexpr to the given SYMBOL in the env
    - (bind sexpr expr) -> creates a function whose named binding is the first SYMBOL of the sexpr given.
- lambda
- print ::=
    - (print expr) -> prints the value of the given expression
- import
- true
- false
- and
- or
- not
- if
- cons
- car
- cdr
- null
