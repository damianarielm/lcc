;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname ejercicio1) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define (f x) (+ x 1))
(define (doble x) (* x 2))
(define (h x y) (< x (doble y)))
(define (cuad-azul x) (square x "solid" "blue"))

(cuad-azul (doble 10))

(and (h 2 3) (h 3 4))
;#true

(= (f 1) (doble 1))
;#true