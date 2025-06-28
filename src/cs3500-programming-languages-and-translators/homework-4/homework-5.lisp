;;
;;  myhw4.lisp
;;  src
;;
;;  Created by Illya Starikov on 03/07/18.
;;  Copyright 2018. Illya Starikov. All rights reserved.
;;

; Evaluates to the last element of list L.
; eg.  `(myLast ‘(p a e g)) → g`
(defun myLast (L)
    (cond
        ((null L) nil)
        ((null (cdr L)) (car L))
        (t (myLast (cdr L)))
    )
)


; Evaluates to the number of occurrences of atom X in list L.
; eg.  `(myCount ‘a ‘(p k a t p a e g)) → 2`
(defun myCount (X L)
    (cond
        ((null L) 0)
        ((eq X (car L)) (+ 1 (myCount X (cdr L))))
        (t (myCount X (cdr L)))
    )
)


; Evaluates to `true` if X is an atom in list L, `false` otherwise.
; eg.   `(myMember ‘a ‘(p a e g)) → t`
(defun myMember (X L)
    (cond
        ((null L) nil)
        ((eq X (car L)) t)
        (t (myMember X (cdr L)))
    )
)


; Evaluates to a list with all elements of  L without repetition.
; eg.   `(myPurge ‘(p a c e p c)) → (a e p c)`
(defun myPurge (L)
    (cond
        ((null L) nil)
        ((myMember (car L) (cdr L)) (myPurge (cdr L)))
        (t (cons (car L) (myPurge (cdr L))))
    )
)


; Evaluates to a list of elements that are common in both lists L1 and L2.
(defun myCommon (L1 L2)
    (cond
        ((null L1) nil)
        ((null L2) nil)
        ((myMember (car L1) L2) (cons (car L1) (myCommon (cdr L1) L2)))
        (t (myCommon (cdr L1) L2))
    )
)

; Evaluates to a list of increasing integers, between X and Y inclusive, with Z as the increment (or to nil if such list does not exist).
(defun myGen (X Y Z)
    (cond
        ((null X) nil)
        ((null Y) nil)
        ((null Z) nil)
        ((> X Y) nil)
        ((= X Y) (list X))
        (t (cons X (myGen (+ X Z) Y Z)))
    )
)

; Evaluates to the list which results from applying function F to every element of list L.
(defun myMap (F L)
    (cond
        ((null F) nil)
        ((null L) nil)
        (t (cons (funcall F (car L)) (myMap F (cdr L))))
    )
)

; Evaluates to the results of applying aggregate function F to the elements of L.
(defun myReduce (F L)
        (cond
            ((null F) nil)
            ((null L) nil)
            ((null (cdr L)) (car L))
            (t (funcall F (car L) (myReduce F (cdr L))))
        )
)
