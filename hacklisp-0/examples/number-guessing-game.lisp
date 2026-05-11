((lambda (
           MAIN GAMELOOP HELPMESSAGE - <= AND CMP PROGN ;;
         )
   ((lambda () (quote (THE GAME HAS FINISHED.)))
    (MAIN)))
 (quote
   (lambda ()
     (PROGN
       ;; (quote - PROGN IS IMPLEMENTED BY PASSING EXPRESSIONS AS ARGUMENTS
       ;;          TO AN EMPTY lambda, WHICH ARE EVALUATED SEQUENTIALLY.
       ;;        - NOTE THAT PROGN ALWAYS RETURNS NIL, NOT ITS FINAL VALUE.
       ;;          TO EXTRACT THE EVALUATION RESULTS WITHIN A SEQUENCE,
       ;;          cons CAN BE USED INSTEAD OF PROGN.
       ;;        - SINCE ALL VALUES ARE DISCARDED INSIDE PROGN,
       ;;          COMMENTS CAN BE WRITTEN IN THIS MANNER.
       ;;        - NOTE THAT `;;` IS A VALID VARIABLE BOUND TO NIL.)
       (print (quote (LET'S PLAY A NUMBER GUESSING GAME.
                      I'M THINKING OF A CERTAIN NUMBER BETWEEN 1 AND _10.
                      SAY A NUMBER, AND I'LL TELL YOU IF IT'S
                      LESS THAN, GREATER THAN, OR EQUAL TO MY NUMBER.
                      CAN YOU GUESS WHICH NUMBER I'M THINKING OF?)))
       ;; (quote - CALLING print WITHOUT ARGUMENTS printS A NEWLINE)
       (print)
       (HELPMESSAGE)
       (GAMELOOP ())
       (print)
       (print (quote (DO YOU WISH TO PLAY AGAIN? Y/N:)))
       (print)
       (print (quote >))
       (cond ((= (read) (quote Y))
              (PROGN (print (quote (ALRIGHT!)))
                     ;; (quote - INFINITE LOOPS ARE DONE USING RECURSION)
                     (MAIN)))
             (TRUE
              (PROGN (print (quote (THANK YOU FOR PLAYING!)))
                     (print)))))))
 (quote
   (lambda (NUMTRIES)
     (PROGN
       (print)
       (print (quote NUMBER>))
       ((lambda (GUESS ANSWER NUMTRIES)
          (cond ((atom? GUESS)
                 (PROGN
                   ;; (quote - WHEN THE USER INPUTS AN atom?, SHOW USAGE TEXT.
                   ;;          NUMTRIES DO NOT INCREASE IN THIS CASE.)
                   (HELPMESSAGE)
                   (GAMELOOP (tail NUMTRIES))))
                ((= (quote <) (CMP GUESS ANSWER))
                 (PROGN
                   (print (quote (YOUR GUESS IS LESS THAN MY NUMBER.)))
                   (GAMELOOP NUMTRIES)))
                ((= (quote >) (CMP GUESS ANSWER))
                 (PROGN
                   (print (quote (YOUR GUESS IS GREATER THAN MY NUMBER.)))
                   (GAMELOOP NUMTRIES)))
                (TRUE
                 (PROGN
                   (print (quote (THAT'S RIGHT! MY NUMBER IS:)))
                   (print ANSWER)
                   (print)
                   (print (quote (YOU GUESSED CORRECTLY! CONGRATULATIONS!)))
                   (print)
                   (print (quote (NUMBER OF TRIES:)))
                   (print NUMTRIES)
                   (print)))))
        (read)
        (quote (* * * * * * *))
        (cons (quote *) NUMTRIES)))))
 (quote (lambda ()
          (print (quote (PLEASE INPUT YOUR NUMBER IN UNARY.
                         FOR EXAMPLE, 1 IS (*), 3 IS (* * *), ETC.)))))
 (quote (lambda (N M)
          (cond ((= N NIL) NIL)
                ((= M NIL) N)
                (TRUE (- (tail N) (tail M))))))
 (quote (lambda (N M) (= NIL (- N M))))
 (quote (lambda (X Y) (cond (X Y) (TRUE NIL))))
 (quote (lambda (N M)
          (cond ((AND (<= N M) (<= M N)) (quote ==))
                ((<= N M) (quote <))
                ((<= M N) (quote >)))))
 (quote (lambda () NIL))
 NIL)
