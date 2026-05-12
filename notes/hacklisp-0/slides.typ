#import "@preview/touying:0.6.1": *
#import themes.dewdrop: *

#import "@local/ethan-standard-style:0.1.0": *

#import "@preview/numbly:0.1.0": numbly

#let defname(name) = [_*#name*_]

// Units
#import "@preview/zero:0.5.0": zi

// Plotting
#import "@preview/cetz:0.4.0"
#import "@preview/cetz-plot:0.1.2"

// Theorems
#import cosmos.clouds: *
#show: show-theorion

// Slides metadata
#show: dewdrop-theme.with(
  aspect-ratio: "16-9",
  footer: self => self.info.institution,
  navigation: "none",
  config-info(
    title: [HackLISP-0],
    subtitle: [A simple programming language for the Hack computer],
    author: [Ethan Charoenpitaks],
    date: datetime.today(),
    institution: [HackLISP-0],
  ),
  config-common(frozen-counters: (theorem-counter,)),  // freeze theorem counter for animation
)

#title-slide()

// #outline-slide()

= Bootstrapping

== The problem

- Open-source software is built on other open-source operating systems
- Thus, we must trust that none of the open-source OSes we've used in the past 30 years is malicious
- Instead, let's try to bootstrap!
  - Start from a small binary seed
	- After that, only ever input human-readable source code
	- Eventually, get a modern OS
- Past efforts
	- x86_64 bootstrapping effort -- stage0, live-bootstrap, GNU Mes, GNU Guile
		- Actually successful!
		- Very long bootstrap chain
		- x86_64 processors are not trustable (Management Engine, very complex)

== Hack computer

- We made this last semester!
- As you know, understandable by high schoolers
	- ...at least compared to what's in your computers...
- Can build from scratch!
	- Small enough to be made out of vacuum tubes

== Hack assembly, Jack VM, Jack?

- So hard to parse!
- I don't want to do Projects 6, 7, 8, 10, 11 in assembly...
- Let's find a simpler language

== SectorLISP

- Minimal LISP that fits in 436 bytes of i8086 machine code
- No integers, no direct memory access
- But small, yet you can write readable code!

#image("image.png")

== What I did

- HackLISP-0 -- basic language
- Essentially an extension of SectorLISP
  - better documented
	- better-named keywords
- Has integers and arithmetic
- Can read and write memory
  - If we combine Hack's RAM and ROM, then we can use this to make a compiler
- Written in C/Jack polyglot
	- Too many things to figure out, I'm also lazy

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

A symbol is stored as a pointer to a null-terminated C string on the atom stack. It can represent whatever you want. 
A symbol evaluates to whatever value is bound to it. The program will crash if you evaluate a symbol that's not bound to it.

As an exception, *NIL* and *TRUE* evaluate to themselves. *()* and *NIL* are indistinguishable.

=== Integer

An integer represents, well, an integer. It evaluates to itself.

It's stored as three integers in memory. The first is *-1*, to make it clear it's not a symbol. The second is the actual value. The third is *0* to make it a null-terminated string.

#slide[

== Data storage

- Atom stack grows up from *NIL* (in our case 9312)
- Pair stack grows down
- Atom stack holds null-terminated C strings and integers.
- Image on the right -- an old version of SectorLISP
	- Unlike the image we use null-terminated C string instead of LISP list for the strings
][
#image("image-1.png")
]

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

= Metacircular interpreter

== Boilerplate

```lisp
((lambda (main nil? evcon evlis lookup pairlis eval apply prog)
		(main main (quote (NIL . NIL) (TRUE . TRUE)))
 )
  (quote (lambda-main (main builtins) (prog
		(print (quote HL0>))
		(print (eval (read)))
		(print)
    (main main builtins)
  )))
	(quote (lambda-nil? (x)
		(= x NIL)
	))
  (quote (lambda-prog (args...) NIL))
```

== pairlis

```lisp
; "Zips" two lists (x and y) together, and appends a.
	; 
	; Example:
	;   pairlis[(A B C); (U V W); ((D . X) (E . Y))] =
	;     ((A . U) (B . V) (C . W) (D . X) (E . Y))
	; 
	; From LISP 1.5 manual:
	;   This function gives the list of pairs of corresponding elements of
	;   the lists x and y, and appends this to the list a.
	(quote (lambda-pairlis (x y a)
		(cond
			((nil? x) a)
			(TRUE (cons (cons (head x) (head y)) (pairlis (tail x) (tail y) a)))
		)
	))
```

== lookup

```lisp
	; Searches an alist for a given key.
	; Returns the value for said key.
	;
	; Called "assoc" in some implementations.
	(quote (lambda-lookup (key alist)
		(cond
			((= key (head (head alist))) (tail (head alist)))
			(TRUE (lookup key (tail alist)))
		)
	))
```

== eval

```lisp
; Evaluates the expression e in the environment env.
	; env is an alist (association list) -- a list of (key . value) pairs
	(quote (lambda-eval (e env)
		(cond
			((nil? e) e)
			((integer? e) e)
			((atom? e) (lookup e env))

			; If e is a list (quote ___), return ___.
			; We use head(tail(e)) because it's actually (quote . (___ . NIL))
			((= (head e) (quote quote)) (head (tail e)))

			; If e is a conditional, punt to evcon to evaluate it.
			((= (head e) (quote cond)) (evcon (tail e) env))

			; If the above fails,
			;   head(e) is the first item (so the function name)
			;   use evlis to evaluate the rest of the items
			;   call apply to apply the function against the values
			(TRUE (apply (head e) (evlis (tail e) env) env))
		)
	))
```

== evlis

```lisp
	; Loops through each expression in exprs and evaluates it.
	; Returns a list of the evaluated expressions.
	; 
	; Examples:
	;   (evlis '(a b c) '((a . 1)(b . 2)(c . 3))) -> '(1 2 3)
	(quote (lambda-evlis (exprs env)
		(cond
			((nil? exprs) NIL)
			(TRUE (cons (eval (head exprs) env) (evlis (tail exprs) env)))
		)
	))
```

== apply

```lisp
; Applies the function f to the argument x, in the environment env.
	(quote (lambda-apply (f x env)
		(cond
			((atom? f) (cond
				((= f (quote =)) (= (head x) (head (tail x))))
				((= f (quote cons)) (cons (head x) (head (tail x))))
				((= f (quote integer?)) (integer? (head x)))
				((= f (quote atom?)) (atom? (head x)))
				((= f (quote head)) (head (head x)))
				((= f (quote tail)) (tail (head x)))
				((= f (quote read)) (read))
				((= f (quote print)) (print (head x)))
				((= f (quote +)) (+ (head x) (head (tail x))))
				((= f (quote 0)) (cond
					((nil? (tail x)) (- (head x)))
					(TRUE (- (head x) (head (tail x))))
				))
				((= f (quote *)) (* (head x) (head (tail x))))
				((= f (quote /)) (/ (head x) (head (tail x))))
				((= f (quote &)) (& (head x) (head (tail x))))
				((= f (quote |)) (| (head x) (head (tail x))))
				((= f (quote mem-get)) (mem-get (head x)))
				((= f (quote mem-put!)) (mem-put! (head x) (head (tail x))))
				; Otherwise assume f is a variable bound to some function or builtin.
				(TRUE (apply (lookup f env) x env))
			))
			
			; If the first element is a list...
			; We assume f is a lambda-expression of form
			;   (lambda ARGS RETVAL)
			; then run: (LISP 1.5)
			;   eval[RETVAL; pairlis[ARGS; x; env]]
			; i.e. we use pairlis to bind the args in the environment,
			; then evaluate it.
			;
			; We skip checking that it starts with `lambda` to reduce the code size
			; and the runtime.
			(TRUE (eval (head (tail (tail f))) (pairlis (head (tail f)) x env)))
		)
	))
```

== evcon

```lisp
	; Evaluates a conditional expression c, in the environment env.
	; c is a list of (TEST BODY) [non-dotted] lists
	;   i.e. (TEST . (BODY . NIL))
	; env is, of course, an environment specified as an alist.
	;
	; evcon iterates in order through the elements of c and 
	; evals the first expression of each pair. If it returns a nonnull
	; value, the body is evaluated and returned. 
	(quote (lambda-evcon (c env) 
		(cond
			((eval (head (head c)) env) 
				(eval (head (tail (head c))) env))
			(TRUE 
				(evcon (tail c) env))
		)
  ))
```

= Future steps

== Making HackLISP-0 useful for bootstrapping

- Combine Hack's RAM and ROM
	- Then we can put code into RAM and jump to it
	- allowing a compiler!
- Basic text editor in assembly
	- Current HackLISP-0 limits the program to only 60 characters
- Write a HackLISP-0 interpreter in assembly
	- Daunting task...

== HackLISP-$n$

- Why didn't the x86_64 compiler project use LISP?

#quote(block: true, attribution: [#link("https://github.com/oriansj/talk-notes/blob/master/bootstrappable.org")[Jeremiah Orians]])[
	LISP primitives defined in McCarthy’s 1960 paper \[Turns out he missed many essential things\] with some modern improvements like Lexical scope, let expressions and raw string support. Turns out you need proper LISP macros in order to produce something useful in bootstrapping. Adding LISP macros in assembly simply is a task no one wants to do.  
]

- So we need to add these kinds of things!
	- Lexical scope
	- Let expressions
	- Raw strings
	- Macros
- We need a compiler
	- Otherwise it becomes slower, and slower, and slower...
	- and we'll run out of RAM!
- Garbage collection
- Mutable objects???
	- Might be a bad idea
	- But we might run out of RAM otherwise
- Try out nicer syntaxes (next slide)
- Get to Scheme or Common Lisp
	- Opens up a huge world of useful programs we can run
	- If we get to Scheme, we can use GNU Mes, a C compiler!

== Nicer syntaxes
#slide[
=== Wisp

#link("https://www.draketo.de/software/wisp")

```lisp
display "Hello World!"  ↦  (display "Hello World!")

define : factorial n    ↦  (define (factorial n)            
    if : zero? n              (if (zero? n)                
       . 1                        1                      
       * n : factorial {n - 1}    (* n (factorial {n - 1}))))
```
]

#slide[

=== Sweet-expressions

#link("https://srfi.schemers.org/srfi-110/srfi-110.html")

```lisp
define fibfast(n)   ; Typical function notation
  if {n < 2}        ; Indentation, infix {...}
     n              ; Single expr = no new list
     fibup n 2 1 0  ; Simple function calls

(define (fibfast n)
  (if (< n 2)
      n
      (fibup n 2 1 0)))
```
]

== Try it yourself

#link("https://github.com/ethanc8/hacklisp/")

#image("QR Code 2026-05-12 11-18-27.png")

