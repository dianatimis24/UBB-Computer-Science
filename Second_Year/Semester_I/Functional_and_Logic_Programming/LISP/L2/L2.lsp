; Write recursive Lisp functions for the following problems (optionally, you may use MAP functions):
; A binary tree is memorised in the following two ways:
; (node no-subtrees list-subtree-1 list-subtree-2 ...) (1)
; (node (list-subtree-1) (list-subtree-2) ...) (2)
; As an example, the tree
;     A
;    / \
;   B   C
;      / \
;     D   E
; is represented as follows:
; (A 2 B 0 C 2 D 0 E 0) (1)
; (A (B) (C (D) (E))) (2)


; 2. Return the list of nodes on the k-th level of a tree of type (1).


; left_traversal(l1l2...ln, nrVertices, nrEdges) = 
;   [], if n == 0
;   [], if nrVertices == 1 + nrEdges
;   l1 U l2 U left_traversal(l3...ln, nrVertices + 1, l2 + nrEdges), otherwise
(defun left_traversal(l n m)
  (cond
    ((null l) nil)
    ((= n (+ 1 m)) nil)
    (T (cons (car l) (cons (cadr l) (left_traversal (cddr l) (+ 1 n) (+ (cadr l) m)))))
  )
)

; left(l1l2...ln) = left_traversal(l3...ln, 0, 0)
(defun left(l)
  (left_traversal (cddr l) 0 0)
)


; right_traversal(l1l2...ln, nrVertices, nrEdges) =
;   [], if n == 0
;   l1l2...ln, if nrVertices == 1 + nrEdges
;   right_traversal(l3...ln, nrVertices + 1, l2 + nrEdges), otherwise
(defun right_traversal(l n m)
  (cond
    ((null l) nil)
    ((= n (+ 1 m)) l)
    (T (right_traversal (cddr l) (+ 1 n) (+ (cadr l) m)))
  )
)

; right(l1l2...ln) = right_traversal(l3...ln, 0, 0)
(defun right(l)
  (right_traversal (cddr l) 0 0)
)


; my_append(l1...ln, m1...mk) = 
;   m1...mk, n == 0
;   l1...ln, k == 0
;   l1 U my_append(l2...ln, m1...mk), otherwise
(defun my_append(l1 l2)
  (cond 
    ((null l1) l2)
    ((null l2) l1)
    (T (cons (car l1) (my_append (cdr l1) l2)))
  )
)


; nodes(l1l2...ln, counter, level) = 
;   [], if n == 0
;   {l1}, if counter == level
;   my_append(nodes(left(l1l2...ln), counter + 1, level) U nodes(right(l1l2...ln), counter + 1, level)), otherwise
(defun nodes(l counter level)
  (cond
    ((null l) nil)
    ((equal counter level) (list (car l)))
    (T (my_append (nodes (left l) (+ 1 counter) level) (nodes (right l) (+ 1 counter) level)))
  )
)

; main(l1l2...ln, level) = nodes(l1l2...ln, 0, level)
(defun main(l level)
  (nodes l 0 level)
)


(print (main '(A 2 B 0 C 2 D 0 E 0) 1))
(print (main '(A 2 B 1 C 2 D 0 E 0 F 0) 1))
(print (main '(A 2 B 1 C 2 D 0 E 0 F 2 G 1 H 0 I 2 J 1 K 0 L 0) 2))