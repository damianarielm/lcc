;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname ejercicio2) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(/ 1 (sin (sqrt 3)))
;#i1.0131438751684085

(* (sqrt 2) (sin pi))
;#i1.7319121124709868e-16

(+ 3 (sqrt (- 4)))
;3+2i

(* (sqrt 5) (sqrt (/ 3 (cos pi))))
;#i0.0+3.872983346207417i

;(/ (sqrt 5) (sin (* 3 0)))
;/: division by zero

;(/ (+ 3) (* 2 4))
;+: expects at least 2 arguments, but found only 1

(* 1 2 3 4 5 6 7 8)
;40320

(/ 120 2 3 2 2 5)
;1