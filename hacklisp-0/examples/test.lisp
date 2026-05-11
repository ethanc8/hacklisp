((lambda (main prog) (main))
  (quote (lambda-main () (prog
    (print (+ 1 2))
    (print)
  )))

	; Runs all of the arguments in order.
	; Returns NIL.
  (quote (lambda-prog (args...) NIL))
)