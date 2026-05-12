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

	; Runs all of the arguments in order.
	; Returns NIL.
  (quote (lambda-prog (args...) NIL))
)