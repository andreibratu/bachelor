;gnu clisp 2.49

; a Write a function to return the n-th element of a list,
;   or NIL if such an element does not exist

; Find nth element in a list
(defun nthelement (l n)
    (cond
        ((null l) nil)
        ((= n 0) (car l))
        (t (nthelement (cdr l) (- n 1)))
    )
)

(print (nthelement `(1 2 3 4) 8))

; b Write a function to check whether an atom E is a member
    of a list which is not necessarily linear

; Find atom 'e' in a liner list
(defun findelem (l e)
    (cond
        ((null l) nil)
        ((= (car l) e) t)
        (t (findelem (cdr l) e))
    )
)

; Find atom 'e' in a non-linear list
(defun findgen (l e)
    (cond
        ((null l) nil)
        ((listp (car l)) (or (findelem (car l) e) (findgen (cdr l) e)))
        (t (or (= (car l) e) (findgen (cdr l) e)))
    )
)

(print (findgen '(1 (4 5 7) 4 (2 3 8)) 3))

; c Write a function to determine the list of all
    sublists of a given list, on any level

; Return all sublists in a given list, including itself
(defun sublists (l)
    (cond
        ((null l) nil)
        ((listp (car l)) (cons (car l) (append (sublists (car l)) (sublists (cdr l)))))
        (t (sublists (cdr l)))
    )
)

; Wrap 'sublists' function to return the list itself in the list
(defun cwrapper (l) (cons l (sublists l)))


(print (cwrapper '(1 (2 (7 8 9) 5) (3 2) 4)))

; d Write a function to transform a linear list into a set

; Transform a linear list into a set
(defun linset (l)
    (cond
        ((null l) nil)
        ((findelem (cdr l) (car l)) (linset (cdr l)))
        (t (cons (car l) (linset (cdr l))))
    )
)

(print (linset '(1 3 3 1 4 6 4 7 6)))
