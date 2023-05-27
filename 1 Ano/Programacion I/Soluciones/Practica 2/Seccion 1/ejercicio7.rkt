;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname ejercicio6) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
; string-remove-last: String -> String
; Dada una palabra, devuelve la palabra sin la ultima letra.
(define (string-remove-last cadena)
  (substring cadena 0 (- (string-length cadena) 1))
)

(check-expect (string-remove-last "Damian") "Damia")
(check-expect (string-remove-last "Ariel") "Arie")
