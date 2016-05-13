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
