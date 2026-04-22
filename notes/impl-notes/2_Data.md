# 2 - Data

## SectorLISP

### Representation of atoms

<https://justine.lol/sectorlisp2/#memory>

Pointers are s.t. 0 is defined as an arbitrary location, which is not what the hardware considers 0.

The only kind of atom allowed in SectorLISP is a symbol. (NIL is a symbol, whose address is 0.) Atoms are stored as null-terminated strings (linked lists) on the atom stack, which grows up from 0.

Pairs are stored on the pair stack, as pairs of ints; one car and one cdr. Each of its two ints are pointers to elsewhere on either on the pair stack or the atom stack.

## lwhjp

<https://www.lwh.jp/lisp/data.html>

Atoms are stored as tagged enums, which are passed by value around:

```c
struct Atom {
	enum {
		AtomType_Nil,
		AtomType_Pair,
		AtomType_Symbol,
		AtomType_Integer
	} type;

	union {
		struct Pair *pair;
		const char *symbol;
		long integer;
	} value;
};
```

Pairs are stored as arrays allocated on the heap:

```c
struct Pair {
	struct Atom atom[2];
};

typedef struct Atom Atom;
```

Symbols are stored in a symbol table, which is a linked list like so:

```
[baz | →] → [bar | →] → [foo | →] → nil
```

Each node is a pair whose car stores a pointer to the symbol's string and cdr is a pointer to the next node.

## tinylisp

<https://raw.githubusercontent.com/Robert-van-Engelen/tinylisp/main/tinylisp.pdf#page=8>

Note that this representation is not actually used; instead, NaN boxing is used.

```c
struct Expr {
	enum { NMBR, ATOM, STRG, PRIM, CONS, CLOS, NIL } tag;
	union {
		double number; /* NMBR: double precision float number */
		const char *atom; /* ATOM: pointer to atom name on the heap */
		const char *string; /* STRG: pointer to string on the heap */
		struct Expr (*fn)(struct Expr, struct Expr); /* PRIM: built-in primitive */
		struct Expr *cons; /* CONS: pointer to (car,cdr) pair on the heap */
		struct Expr *closure; /* CLOS: pointer to closure pairs on the heap */
	} value;
};
```

