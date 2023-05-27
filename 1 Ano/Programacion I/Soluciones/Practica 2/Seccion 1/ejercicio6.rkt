;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname ejercicio7) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
; Representamos un caracter con un String de
; longitud 1.

; string-last: String -> String
; Dada una cadena, determina el ultimo caracter.
(define (string-last cadena)
  (string-ith cadena (- (string-length cadena) 1))
)

(check-expect (string-last "Damian") "n")
(check-expect (string-last "Ariel") "l")
