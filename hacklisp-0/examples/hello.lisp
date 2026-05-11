((lambda (main prog) (main))
  ; Note that they don't actually have to start with lambda-[name]
  ; Since we don't actually check for the lambda keyword we can do this
  (quote (lambda-main () (prog
    (print (quote (Hello world)))
    (print)
  )))
  (quote (lambda-prog () NIL))
)