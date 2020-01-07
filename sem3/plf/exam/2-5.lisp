; Flatten a list to check problem's condition no matter the list's depth
; Seminar 6 advises to flatten the list in order to check if it is valid
; IMO this will be needed a lot at subject 5
(defun flatten (lst)
  (mapcan
     #'(lambda (a)
         (cond
           ((atom a) (list a))
           (T (flatten a))))
     lst
   )
)

; Extract only numeric atoms
(defun numeric (l)
    (cond
     ((null l) nil)
     ((numberp (car l)) (cons (car l) (numeric (cdr l))))
     (t (numeric (cdr l)))
 )
)

; My own max(a, b)
(defun foo (a b)
    (cond
        ((<= a b) b)
        (t a)
    )
)

; Max over list; equivalent to (reduce #'foo l) 
(defun bar (l)
    (cond
        ((equal (cdr l) nil) (car l))
        (t (foo (car l) (bar (cdr l))))
    )
)

; Check the problem condition
; Extra care - numeric can result in empty list
(defun check (l) 
    (cond
        ((null (numeric (flatten l))) nil)
        ((equal (mod (bar (numeric (flatten l) ) ) 2) 0))
    )
)

; The function to analyse the tree
; If current list checks condition add 1 to the mapping over its members
; Check seminar 6 for inspiration
(defun baz (l level)
    (cond
        ((atom l) 0)
        ((and (check l) (equal (mod level 2) 1)) (+ 1 (apply '+ (mapcar #'(lambda (a) (baz a (+ level 1))) l))))
        (t (apply '+ (mapcar #'(lambda (a) (baz a (+ level 1))) l)))
    )
)

; Main call
(write (baz '(A (B 2) (1 C 4) (1 (6 F)) (((G) 4) 6)) 0))