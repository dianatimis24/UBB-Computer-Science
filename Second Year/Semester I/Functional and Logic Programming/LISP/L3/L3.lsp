; 9. Write a function that removes all occurrences of an atom from any level of a list.

; my_remove(l1...ln, e)
;   = [], if n == 0
;   = my_remove(l2...ln), if l1 == e 
;   = l1 U my_remove(l2...ln), otherwise
(defun my_remove (l e)
  (cond
    ((null l) nil)
    ((eq (car l) e) (my_remove (cdr l) e))
    (T (cons (car l) (my_remove (cdr l) e)))
  )
)


; remove_atoms(l, at)
;   = nil, if l == null
;   = nil, if l is an atom and l == at
;   = l, if l is an atom and l != at
;   = my_remove(remove_atoms(l1, at) U remove_atoms(l2, at) U ... U remove_atoms(ln, at), nil), otherwise, where l = (l1l2...ln)
(defun remove_atom (l at)
  (cond
    ((null l) nil)
    ((and (eq l at) (atom l)) nil)
    ((atom l) l)
    (T (my_remove (mapcar #'(lambda (parameter) (remove_atom parameter at)) l) nil))
  )
)

(print (remove_atom '(A B (C (B D (B A (A)) A (B C D A)) D A)) 'A))