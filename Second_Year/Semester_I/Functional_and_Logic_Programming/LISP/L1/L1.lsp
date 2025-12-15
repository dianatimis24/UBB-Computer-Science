; 9.
; a) Write a function that merges two sorted linear lists and keeps double values.
; b) Write a function to replace an element E by all elements of a list L1 at all levels of a given list L.
; c) Write a function to determines the sum of two numbers in list representation, and returns the 
; corresponding decimal number, without transforming the representation of the number from list to number.
; d) Write a function to return the greatest common divisor of all numbers in a linear list.


; a)
; merge_lists(a1a2...an, b1b2...bm) = 
;   [], if n == 0 and m == 0
;   b1b2...bm, if n == 0
;   a1a2...an, if m == 0
;   a1 U merge_lists(a2...an, b1b2...bm), if a1 < b1
;   b1 U merge_lists(a1a2...an, b2...bm), if a1 >= b1
(defun merge_lists(a b)
  (cond
    ((and (null a) (null b)) nil)
    ((null a) b)
    ((null b) a)
    ((< (car a) (car b)) (cons (car a) (merge_lists (cdr a) b)))
    (T (cons (car b) (merge_lists a (cdr b))))
  )
)

(print (merge_lists '(1 2 3 3 5 8 9) '(2 3 4 4 5 5 7 8)))


; b)
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

; replace_element(e, l1, L1...Ln) =
;   [], if n == 0
;   l1 U replace_element(e, l1, L2...Ln), if l1 is atom and e == L1
;   L1 U replace_element(e, 11, L2...Ln), if l1 is atom and e != L1
;   replace_element(e, l1, L1) U replace_element(e, l1, L2...Ln), otherwise
(defun replace_element(e l1 L)
  (cond
    ((null L) nil)
    ((atom (car L)) 
      (cond
        ((equal e (car L)) (my_append l1 (replace_element e l1 (cdr L))))
        (T (cons (car L) (replace_element e l1 (cdr L))))
      )
    )
    (T (cons (replace_element e l1 (car L)) (replace_element e l1 (cdr L))))
  )
)

(print (replace_element 'A '(1 2 3) '(A (B C) A ((A) B C (A D)) A D (((A))))))


; c)
; digit(l, k, c) = 
;   (k + c) % 10, if l is null
;   (l + c) % 10, if k is null
;   (l + k + c) % 10, otherwise
(defun digit(l k c)
  (cond
    ((null l) (mod (+ k c) 10))
    ((null k) (mod (+ l c) 10))
    (T (mod (+ l k c) 10))
  )
)

; carry(l, k, c) = 
;   (k + c) / 10, if l is null
;   (l + c) / 10, if k is null
;   (l + k + c) / 10, otherwise
(defun carry(l k c)
  (cond
    ((null l) (floor (+ k c) 10))
    ((null k) (floor (+ l c) 10))
    (T (floor (+ l k c) 10))
  )
)

; sum_lists(l1l2...ln, k1k2...km, c) = 
;   {1}, if n == 0 and m == 0 
;   sum_lists(l2l3...ln, k2k3...km, carry(l1, k1, c)) U digit(l1, k1, c), otherwise
(defun sum_lists(l k c)
  (cond
    ((and (null l) (null k)) (if (= 1 c) (list 1) nil))
    (T (my_append (sum_lists (cdr l) (cdr k) (carry (car l) (car k) c)) (list (digit (car l) (car k) c))))        
  )
)

; my_reverse(l1l2...ln) = 
;   [], if n == 0 
;   my_reverse(l2l3...ln) U l1, otherwise
(defun my_reverse(l)
  (cond
    ((null l) nil)
    (T (my_append (my_reverse (cdr l)) (list (car l))))
  )
)

; compute_sum(L1, L2) = sum_lists(my_reverse(L1), my_reverse(L2), 0)
(defun compute_sum(l1 l2)
  (cond
    (T (sum_lists (my_reverse l1) (my_reverse l2) 0))
  )
)

(print (compute_sum '(1 2 3) '(9 5 9)))


; d)
; my_gdc(a, b) = 
;   nil, if a not number and b not number
;   b, if a not number
;   a, if b not number
;   a, if b == 0 
;   my_gdc(b, a % b), otherwise
(defun my_gcd(a b)
  (cond
    ((and (not (numberp a)) (not (numberp b))) nil)
    ((not (numberp a)) b)
    ((not (numberp b)) a)
    ((= b 0) a)
    (T (my_gcd b (mod a b)))
  )
)

; gdc_list(l1l2...ln) = 
;   nil, if n == 0 
;   l1, if n == 1 
;   my_gdc(l1, gdc_list(l2l3...ln)), otherwise
(defun gcd_list(l)
  (cond
    ((null l) nil)
    ((null (cdr l)) (car l))
    (T (my_gcd (car l) (gcd_list (cdr l))))
  )
)

(print (gcd_list '(72 16 24 D B 12 A)))