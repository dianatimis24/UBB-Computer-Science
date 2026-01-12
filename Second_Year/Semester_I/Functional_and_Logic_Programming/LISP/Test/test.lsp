(print "Practical Exam - Lisp")

; count-occ(l1l2...ln, e) =
;   = 0, if n == 0
;   = 1 + count-occ(l2l3...ln, e), if l1 is a numerical atom and l1 == e
;   = count-occ(l2l3...ln, e), if l1 is not a numerical atom
;   = count-occ(l1, e) + count-occ(l2l3...ln, e), otherwise
(defun count-occ (L e)
  (cond
    ((null L) 0)
    ((and (numberp (car L)) (= (car L) e)) (+ 1 (count-occ (cdr L) e)))
    ((atom (car L)) (count-occ (cdr L) e))
    (T (+ (count-occ (car L) e) (count-occ (cdr L) e)))
  )
)

; remove-elem(l1l2...ln, e) =
;   = [], if n == 0
;   = remove-elem(l2l3...ln, e), if l1 is an atom and l1 == e 
;   = l1 U remove-elem(l2l3...ln, e), if l1 is an atom and l1 != e 
;   = remove-elem(l1, e) U remove-elem(l2l3...ln, e), otherwise
(defun remove-elem (L e)
  (cond
    ((null L) nil)
    ((atom (car L))
     (if (eql (car L) e)
         (remove-elem (cdr L) e)
         (cons (car L) (remove-elem (cdr L) e))))
    (t
     (cons (remove-elem (car L) e)
           (remove-elem (cdr L) e)))))

; remove-empty(L) =
; = nil, l == null
; = remove-empty(l2l3...ln), if l1 = ()
; = remove-empty(l1) U remove-empty(l2l3...ln), l1 not empty 
; = l1 U remove-empty(l2l3...ln), otherwise
(defun remove-empty (L)
  (cond
    ((null L) nil)
    ((and (listp (car L)) (null (car L)))
     (remove-empty (cdr L)))
    ((listp (car L))
     (cons (remove-empty (car L))
           (remove-empty (cdr L))))
    (T
     (cons (car L) (remove-empty (cdr L))))))

; my_remove(l, ogL) = 
;  = nil, if l == null
;  = L, if L atom
;  = remove-empty(my_remove(remove-elem(L, (car L)))), L numeric with even appearances in ogL
;  = my_remove(l1, ogL) U my_remove(l2l3...ln, ogL), otherwise
(defun my_remove (L ogL)
  (cond
    ((null L) nil)
    ((atom L) L)
    ((and (numberp (car L))
          (= (mod (count-occ ogL (car L)) 2) 0))
     (remove-empty
      (my_remove (remove-elem L (car L)) ogL)))
    (T
     (cons (my_remove (car L) ogL)
           (my_remove (cdr L) ogL)))))
           
           
; solve(l1l2...ln) = remove-elem(my_remove(l1l2...ln, l1l2...ln), nil)
(defun solve (L) (remove-elem (my_remove L L) nil))



(print (solve '(1 g (1 h 8 e (2)))))
(print (solve '((1) g (1 h 8 e (2)))))
(print (solve '(1 2 3 4 5 1)))
(print (solve '(1 (A B 2 (1 2 T) C 3) 3)))
(print (solve '(A 4 (5 5 F) 1 G)))
