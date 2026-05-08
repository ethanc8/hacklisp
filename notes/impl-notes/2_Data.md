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

## HackLISP-0

Following SectorLISP, we choose some arbitrary point in memory as `NIL`. We have two stacks growing up and down from `NIL` -- the one going up is the atom stack, and the one going down is the pair stack.

Pairs are stored on the pair stack, as two consecutive tagged words; one car and one cdr. Each of its two words are pointers to elsewhere on either on the pair stack or the atom stack.

Symbols are stored on the atom stack as null-terminated strings of characters.

Integers are stored on the atom stack as the integer and then a null. Thus, integers and single-character symbols are indistinguishable. In fact, to make the implementation simpler, adding an integer to a string will probably just return the integer plus the first character of the string.

### Past bad idea -- tagged pointer

The highest allowed memory location in Hack is 16383 (`0b0011 1111 1111 1111`). Thus, we'll use a tagged pointer, so that we can represent both 14-bit signed integers and pointers.

Since we want it to work in two's complement representation, `00` and `11` must be the leading digits of the integers. Then, we have `01` and `10` left -- any 16-bit number starting with those bits doesn't take on the same value when chopped to a 14-bit number.

Let's go assign the meanings of the first two bits then:
* `00` - positive integer
* `11` - negative integer
* `01` - pointer
* `10` - reserved

Following SectorLISP, we choose some arbitrary point in memory as `NIL`. We have two stacks growing up and down from `NIL` -- the one going up is the symbol stack, and the one going down is the pair stack.

Pairs are stored on the pair stack, as two consecutive tagged words; one car and one cdr. Each of its two words are pointers to elsewhere on either on the pair stack or the atom stack.

Symbols are stored on the symbol stack as linked-lists of characters. The car is the character, and the cdr is the pointer to the next item. If the cdr is `NIL`, then it's the end of the linked-list.

A value is either a symbol, a pair, or an integer. Symbols and pairs are stored as pointers to values on the pair stack, and integers are stored as 16-bit signed integers, but their valid values are restricted to what can be represented in a 14-bit signed integer -- this way, we can use the top two words as tags.

Actually, this doesn't work because 24576 (`0b0110 0000 0000 0000`) is the address of Keyboard, and takes up 15 bits. This is the highest allowed address.

