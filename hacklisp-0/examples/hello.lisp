((lambda (main progn) (main))
  (quote (lambda () (progn
    (quote (main function))
    (print (quote (Hello world)))
    (print)
  )))
  (quote (lambda () NIL))
)