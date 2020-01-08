; Flatten non-linear list
(defun flatten (lst)
  (mapcan
     #'(lambda (a)
         (cond
           ((atom a) (list a))
           (T (flatten a))))
     lst
   )
)

; Count non number atoms
(defun countnon (at)
    (cond
        ((numberp at) 0)
        (t 1)
    )
)

; Check problem condition
(defun check (lst) (equal (mod (apply '+ (mapcar #'countnon (flatten lst))) 2) 1))

; Helper functions
(defun even (nr) (equal (mod nr 2) 0))
(defun odd (nr) (not (even nr)))

; Tree processing
(defun process (tree level)
    (cond
        ((atom tree) 0)
        ((and (check tree) (even level)) (+ 1 (apply '+ (mapcar #'(lambda (a) (process a (+ level 1))) tree))))
        (t (apply '+ (mapcar #'(lambda (a) (process a (+ level 1))) tree)))
    )
)

; Main call
(write (process '(A (B 2) (1 C 4) (1 (6 F)) (((G) 4) 6)) 0)))
