#import "@local/ethan-standard-style:0.1.0": *
#show: ethan-standard-style

#set text(
	font: "New Computer Modern",
	weight: 500,
	size: 11pt
)

#show math.equation: set text(
	font: "New Computer Modern Math",
	weight: 500,
	features: (
		// Round emptyset
		cv01: 1,
		// Blackboard bold from Computer Modern
		ss03: 1,
		// ss05: 1,
	)
)

#let title(arg) = [
	#set text(size: 17pt, weight: "bold")
	// #set align(center)

	#arg
]

#import "@preview/fletcher:0.5.8" as fletcher: diagram, node, edge
#import fletcher.shapes: diamond

#title[
	HackLISP-0 Programmer's Manual
]

= Grammar

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

== Tokenization notes

Dots must be separated by whitespace, otherwise they're considered part of the symbol.

Integers must have a whitespace or a paren after them; you cannot have a symbol or dot immediately following.

= Data types

== Cons cell

A cons cell is a pair, represented in text as an *_s_-expression*

#align(center)[
	( _head_ . _tail_ ).
]

Both _head_ and _tail_ are stored as pointers, to objects of any data type.

A cons cell evaluates to the result of calling its head with its tail as the arguments.

== List

A list is a list of things. It is represented as a cons cell, whose _tail_ is another cons cell. The last element of the list is represented by ( _head_ . NIL ). For example:

#align(center)[
	(A B C D E) = (A . (B . (C . (D . (E . NIL)))))
]

A list evaluates to the result of calling its head with its tail as the arguments.

== Atom

An _atom_ is a basic thing, it's not made out of any other Lisp objects.

=== Symbol

A symbol is stored as a pointer to a null-terminated C string on the atom stack. It can represent whatever you want. The following symbols are predefined; you cannot redefine them:

#align(center)[
	NIL #h(7pt) TRUE #h(7pt) quote #h(7pt) cond #h(7pt) = #h(7pt) cons #h(7pt) atom? #h(7pt) head #h(7pt) tail #h(7pt) lambda #h(7pt) read #h(7pt) print #h(7pt) integer? #h(7pt) + #h(7pt) $-$ #h(7pt) $*$ #h(7pt) / #h(7pt) & #h(7pt) | #h(7pt) mem-get #h(7pt) mem-put!
]

A symbol evaluates to whatever value is bound to it. The program will crash if you evaluate a symbol that's not bound to it.

As an exception, *NIL* and *TRUE* evaluate to themselves. *()* and *NIL* are indistinguishable.

=== Integer

An integer represents, well, an integer. It evaluates to itself.

= Basic builtins

These basically do the "list programming" part of LISP.

== quote

(*quote* _x_) returns _x_, without evaluating it.

```lisp
> (quote a)
a
> (quote (a b c))
(a b c)
```

*Important:* *quote* is the only builtin function which does not evaluate its arguments.

== cond

(*cond* $(p_1 e_1) ... (p_n e_n)$)

The $p_k$ are evaluated in order until one returns *TRUE*. When that happens, the value of $e_k$ is returned as the value of the whole expression.

```lisp
> (cond (NIL (quote no)) (TRUE (quote yes)))))
yes
> (cond (TRUE (quote first)) (TRUE (quote second)))))
first
```

== =

(*=* _x_ _y_) returns *TRUE* if $x$ and $y$ are both atoms and are the same, or if they are lists stored in the same memory position. Otherwise, it returns *NIL*.

```lisp
> (= (quote a) (quote a))
TRUE
> (= (quote b) (quote a))
NIL
```

== cons

(*cons* _x_ _y_) returns (_x_ . _y_).

```lisp
> (cons (quote a) (quote (b c)))
(a b c)
> (cons (quote a) (quote b))
(a . b)
```

== atom?

(*atom?* _x_) returns *TRUE* if _x_ is an atom, otherwise it returns *NIL*.

```lisp
> (atom? (quote (a b)))
NIL
> (atom? 3)
TRUE
> (atom? (quote atom?))
TRUE
```

== head

(*head* _x_) returns the head of _x_ (its first element).

```lisp
> (head (quote (a b)))
a
```

Most Lisps call it *car* (Contents of the Address Register). 

== tail

(*head* _x_) returns the tail of _x_:
- If it's a cons cell, its second element
- If it's a list, everything after the first element

```lisp
> (tail (quote (a b c)))
(b c)
> (tail (quote (a . b)))
b
```

Most Lisps call it *cdr* (Contents of the Decrement Register).

= Extra builtins

== read

(*read*) waits for the user to enter in an _s_-expression, then it parses the _s_-expression and returns it.

== print

(*print* _x_) prints the value _x_ (as an _s_-expression) to the screen.

(*print*) with no arguments makes a new line.

It returns the arguments.

== integer?

(*integer?* _x_) returns *TRUE* if _x_ is an integer and *NIL* if not.

== +

(*+* _x_ _y_) returns $x + y$.

== $-$

(*$-$* _x_) returns $-x$.

(*$-$* _x_ _y_) returns $x - y$.

== $*$

(*$*$* _x_ _y_) returns $x * y$.

== /

(*\/* _x_ _y_) returns $x / y$.

== &

(*&* _x_ _y_) returns the bitwise AND of $x$ and $y$.

== |

(*|* _x_ _y_) returns the bitwise OR of $x$ and $y$.

== mem-get

(*mem-get* _x_) returns the value at RAM[_x_].

== mem-put!

(*mem-put!* _x_ _y_) sets RAM[_x_] to _y_.

= Lambdas

A lambda is expressed as

#align(center)[
	(*lambda* $(p_1 ... p_n)$ $e$),
]

where $p_1 ... p_n$ are the *_parameters_* and $e$ is an expression. A *_function call_* is an expression
#align(center)[
	((*lambda* $(p_1 ... p_n)$ $e$) $a_1 ... a_n$).
]

Note that the keyword *lambda* is not actually a keyword; you can replace it by anything of your choosing and it will be ignored.

1. Each $a_i$ is evaluated.
2. A new environment, consisting of the outside environment plus the following bindings is created:

$ p_1 to a_1 \
p_2 to a_2 \
dots.v \
p_n to a_n $

3. $e$ is evaluated in said environment.
4. The expression returns the retval of $e$.

If an expression is of the form
#align(center)[
	($f$ $a_1 ... a_n$).
]

where $f$ is bound to a lambda, then $f$ is replaced by said lambda and evaluated.

The default environment, i.e. at the top level, is

$ "NIL" &to "NIL" \
"TRUE" &to "TRUE". $

*Key idea: lambas by themselves are Turing-complete! (see lambda calculus)*

But LISP's lists make it more convenient.

= Useful tricks

== Recursion and naming

```lisp
((lambda (a b) (a 1))
  ; Note that they don't actually have to start with lambda-[name]
  ; Since we don't actually check for the lambda keyword we can do this
  (quote (lambda-a (x) (cons x (b x))
  (quote (lambda-b (x) (cons x (a x))
)
```

== Imperative programming

```lisp
((lambda (main prog) (main))
  (quote (lambda-main () (prog
    (print (quote (Hello world)))
    (print)
		(print (quote (Goodbye)))
    (print)
  )))
	; It pretends to take no arguments,
	; but it actually takes infinitely many
  (quote (lambda-prog () NIL))
)
```


