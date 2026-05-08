# Grammar

```
program: object*

object: list | atom

list: `(` (object | `.`)* `)`

atom: symbol | integer

symbol: symbol-start symbol-middle*

symbol-start: All characters other than `(` `)`, integers, `.`, and whitespace

symbol-middle: All characters other than `(` `)` and whitespace

integer: (ASCII 48~57)
```

## Tokenization notes

Dots must be separated by whitespace, otherwise they're considered part of the symbol.

Integers must have a whitespace or a paren after them; you cannot have a symbol or dot immediately following.
