# Metacircular evaluator

## From "Roots of Lisp"

* [Explanation in "Roots of Lisp"](https://justine.lol/sectorlisp/jmc.pdf#page=8)
* [Explanation in bernsteinbear](https://bernsteinbear.com/blog/lisp/12_metacircular/)

```lisp
; The Lisp defined in McCarthy's 1960 paper, translated into CL.
; Assumes only quote, atom, eq, cons, car, cdr, cond.
; Bug reports to lispcode@paulgraham.com.

(defun null. (x)
  (eq x '()))

(defun and. (x y)
  (cond (x (cond (y 't) ('t '())))
        ('t '())))

(defun not. (x)
  (cond (x '())
        ('t 't)))

(defun append. (x y)
  (cond ((null. x) y)
        ('t (cons (car x) (append. (cdr x) y)))))

(defun list. (x y)
  (cons x (cons y '())))

(defun pair. (x y)
  (cond ((and. (null. x) (null. y)) '())
        ((and. (not. (atom x)) (not. (atom y)))
         (cons (list. (car x) (car y))
               (pair. (cdr x) (cdr y))))))

(defun assoc. (x y)
  (cond ((eq (caar y) x) (cadar y))
        ('t (assoc. x (cdr y)))))

(defun eval. (e a)
  (cond
    ((atom e) (assoc. e a))
    ((atom (car e))
     (cond
       ((eq (car e) 'quote) (cadr e))
       ((eq (car e) 'atom)  (atom   (eval. (cadr e) a)))
       ((eq (car e) 'eq)    (eq     (eval. (cadr e) a)
                                    (eval. (caddr e) a)))
       ((eq (car e) 'car)   (car    (eval. (cadr e) a)))
       ((eq (car e) 'cdr)   (cdr    (eval. (cadr e) a)))
       ((eq (car e) 'cons)  (cons   (eval. (cadr e) a)
                                    (eval. (caddr e) a)))
       ((eq (car e) 'cond)  (evcon. (cdr e) a))
       ('t (eval. (cons (assoc. (car e) a)
                        (cdr e))
                  a))))
    ((eq (caar e) 'label)
     (eval. (cons (caddar e) (cdr e))
            (cons (list. (cadar e) (car e)) a)))
    ((eq (caar e) 'lambda)
     (eval. (caddar e)
            (append. (pair. (cadar e) (evlis. (cdr e) a))
                     a)))))

(defun evcon. (c a)
  (cond ((eval. (caar c) a)
         (eval. (cadar c) a))
        ('t (evcon. (cdr c) a))))

(defun evlis. (m a)
  (cond ((null. m) '())
        ('t (cons (eval.  (car m) a)
                  (evlis. (cdr m) a)))))
```

### Bernsteinbear's version

```lisp
(define null. (x)
  (eq x '()))

(define and. (x y)
  (cond (x (cond (y #t)
                 (#t #f)))
        (#t #f)))

(define not. (x)
  (cond (x #f)
        (#t #t)))

(define append. (x y)
  (cond ((null. x) y)
        (#t (cons (car x)
                  (append. (cdr x) y)))))

(define list. (x y)
  (cons x (cons y '())))

; PG calls it "pair."
(define zip. (x y)
  (cond ((and. (null. x) (null. y)) '())
        ((and. (not. (atom? x)) (not. (atom? y)))
         (cons (list. (car x) (car y))
               (zip. (cdr x) (cdr y))))))

(define o (f g) (lambda (x) (f (g x))))
(val caar (o car car))
(val cadar (o car (o cdr car)))

; PG calls it "assoc."
(define lookup. (key alist)
  (cond ((eq (caar alist) key) (cadar alist))
        (#t (lookup. key (cdr alist)))))

; eval takes two parameters: an expression and an environment. It's like our
; evalexp.
(define eval. (e env)
  ; There are a lot of cases to consider. This is like our large match
  ; expression.
  (cond
    ; If it's a symbol, look it up. This is different from pg's Lisp in that
    ; he *only* has symbols to work with.
    ((sym? e) (lookup. e env))
    ; If it's some other type of atom, just leave it be. Let it self-evaluate.
    ((atom? e) e)
    ; If it's a list (the only alternative to being an atom), check if the
    ; first item is an atom.
    ((atom? (car e))
     ; What kind of form is it?
     (cond
       ; Quote accepts one argument, so just return that argument as an
       ; unevaluated expression (note the lack of a recursive call to eval.).
       ((eq (car e) 'quote) (cadr e))
       ; For atom?, eq, car, cdr, and cons, just evaluate the expression then
       ; pass it through to the built-in form.
       ((eq (car e) 'atom?) (atom? (eval. (cadr e)  env)))
       ((eq (car e) 'eq)    (eq    (eval. (cadr e)  env)
                                   (eval. (caddr e) env)))
       ((eq (car e) 'car)   (car   (eval. (cadr e)  env)))
       ((eq (car e) 'cdr)   (cdr   (eval. (cadr e)  env)))
       ((eq (car e) 'cons)  (cons  (eval. (cadr e)  env)
                                   (eval. (caddr e) env)))
       ; For cond, it's a wee bit tricker. We get to this function a bit later.
       ((eq (car e) 'cond)  (eval-cond. (cdr e) env))
       ; ...else, try and evaluate the function as a user-defined function,
       ; applying it to the arguments.
       (#t (eval. (cons (lookup. (car e) env)
                        (cdr e))
                  env))))
    ; If it's a compound expression in which the first element is a
    ; label-expression,
    ((eq (caar e) 'label)
     ; ...evaluate the expression in environment with a new recursive binding.
     (eval. (cons (caddar e) (cdr e))
            (cons (list. (cadar e) (car e)) env)))
    ; If it's a compound expression in which the first element is a
    ; lambda-expresison,
    ((eq (caar e) 'lambda)
     ; ...evaluate the application of the lambda to the given arguments,
     ; evaluating them.
     (eval. (caddar e)
            (append. (zip. (cadar e)
                           (map-eval. (cdr e) env))
                     env)))))

; Some helpers...

; cond works by evaluating each of the conditions in order until it encounters
; a truthy one.
(define eval-cond. (c env)
  ; If we have no more conditions left, there's an error.
  (cond ((null. c) 'error)
         ; If the current condition is true, evaluate that branch.
         (eval. (caar c) env)   (eval. (cadar c) env))
         ; Otherwise, keep going.
         (#t (eval-cond. (cdr c) env))))

; This is a manually curried form of map. It runs eval over every element in a
; list using the given environment.
(define map-eval. (exps env)
  (cond ((null. exps) '())
        (#t (cons (eval.  (car exps) env)
                  (map-eval. (cdr exps) env)))))
```

## LISP 1.5

<https://www.lispmachine.net/books/LISP_1.5_Programmers_Manual.pdf#page=21>

```lisp
apply[fn;x;a] =
   [atom[fn] →
       [eq[fn;CAR] → caar[x];
        eq[fn;CDR] → cdar[x];
        eq[fn;CONS] → cons[car[x];cadr[x]];
        eq[fn;ATOM] → atom[car[x]];
        eq[fn;EQ] → eq[car[x];cadr[x]];
        T → apply[eval[fn;a];x;a]];
    eq[car[fn];LAMBDA] → eval[caddr[fn];parlis[cadr[fn];x;a]];
    eq[car[fn];LABEL] → apply[caddr[fn];x;cons[cons[cadr[fn];caddr[fn]];a]]]

eval[e;a] =
   [atom[e] → cdr[assoc[e;a]];
    atom[car[e]] →
          [eq[car[e],QUOTE] → cadr[e];
           eq[car[e];COND] → evcon[cdr[e];a];
           T → apply[car[e];evlis[cdr[e];a];a]];
    T → apply[car[e];evlis[cdr[e];a];a]]


evcon[c;a] = [eval[caar[c];a] -> eval[cadar[c];a];
      T -> evcon[cdr[c];a]]

evlis[m;a] = [null[m] -> NIL;
      T -> cons[eval[car[m];a];evlis[cdr[m];a]]]
```

* [Explanation and Python version](https://zserge.com/posts/langs-lisp/)

## McCarthy's 1950s paper

It was taken from [sectorlisp2](https://justine.lol/sectorlisp2/).

```lisp
eval[e; a] = [
  atom[e] → assoc[e; a];
  atom[car[e]] → [
    eq[car[e]; QUOTE] → cadr[e];
    eq[car[e]; ATOM]  → atom[eval[cadr[e]; a]];
    eq[car[e]; EQ]    → [eval[cadr[e]; a] = eval[caddr[e]; a]];
    eq[car[e]; COND]  → evcon[cdr[e]; a];
    eq[car[e]; CAR]   → car[eval[cadr[e]; a]];
    eq[car[e]; CDR]   → cdr[eval[cadr[e]; a]];
    eq[car[e]; CONS]  → cons[eval[cadr[e]; a]; eval[caddr[e]; a]];
    T                 → eval[cons[assoc[car[e]; a]; evlis[cdr[e]; a]]; a]
  ];
  eq[caar[e]; LAMBDA] →
    eval[caddar[e]; append[pair[cadar[e]; evlis[cdr[e]; a]; a]]]
]
```

McCarthy's papers:
* ["Recursive functions of symbolic expressions and their computation by machine", 1959-03-23](https://justine.lol/sectorlisp2/aimemo8.txt)
* ["Recursive Functions of Symbolic Expressions and Their Computation by Machine, Part I", 1960-04](https://justine.lol/sectorlisp/lisp.pdf)
* ["A basis for a mathematical theory of computation", 1961~1963](https://justine.lol/sectorlisp2/JohnMcCarthyBasisForComputation.pdf)

## SectorLISP

* [source](https://justine.lol/sectorlisp2/)
* [an explanation](https://guitarvydas.github.io/2023/12/12/Lisp-Eval-and-Apply.html)

```js
function Evcon(c, a) {
  if (Eval(Car(Car(c)), a)) {
    return Eval(Car(Cdr(Car(c))), a);
  } else {
    return Evcon(Cdr(c), a);
  }
}

function Evlis(m, a) {
  return m ? Cons(Eval(Car(m), a),
                  Evlis(Cdr(m), a)) : m;
}

function Assoc(x, y) {
  if (x == Car(Car(y))) return Cdr(Car(y));
  return Assoc(x, Cdr(y));
}

function Pairlis(x, y, a) {
  return x ? Cons(Cons(Car(x), Car(y)),
                  Pairlis(Cdr(x), Cdr(y), a)) : a;
}

function Eval(e, a) {
  var A = cx;
  if (!e) return e;
  if (e > 0) return Assoc(e, a);
  if (Car(e) == kQuote) return Car(Cdr(e));
  if (Car(e) == kCond) return Evcon(Cdr(e), a);
  return Gc(A, Apply(Car(e), Evlis(Cdr(e), a), a));
}

function Apply(f, x, a) {
  if (f < 0)      return Eval(Car(Cdr(Cdr(f))), Pairlis(Car(Cdr(f)), x, a));
  if (f == kEq)   return Car(x) == Car(Cdr(x));
  if (f == kCons) return Cons(Car(x), Car(Cdr(x)));
  if (f == kAtom) return Car(x) >= 0;
  if (f == kCar)  return Car(Car(x));
  if (f == kCdr)  return Cdr(Car(x));
  return Apply(Assoc(f, a), x, a);
}
```

