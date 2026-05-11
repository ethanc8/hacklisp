((lambda (main lookup prog) (main))
  (quote (lambda-main () (prog
    (print (lookup (quote a) (quote ((a . 1)))))
    (print)
  )))
	
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

	; Runs all of the arguments in order.
	; Returns NIL.
  (quote (lambda-prog () NIL))
)