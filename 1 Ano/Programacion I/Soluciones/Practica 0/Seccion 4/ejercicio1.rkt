;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname ejercicio1) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
; Apartado a
(not #t)
;#false

; Apartado b
(or #t #f)
;#true

; Apartado c
(and #t #f)
;#false

; Apartado d
(and #t (or #f (not #f)) (not #t))
;#false

; Apartado e
(not (= 2 (* 1 3)))
;#true

; Apartado f
(or (= 2 (* 1 3)) (< 4 (+ 3 2)))
;#true