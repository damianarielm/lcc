;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname ejercicio4) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define CARAS 6) ; Cantidad de caras en un cubo.

; Representamos la longitud de una arista en metros con un numero.

; area-cubo: Number -> Number
; Dada la longitud de una arista en metros, devuelve el area
; de un cubo de dicho tamaño en metros cuadrados.
(define (area-cubo arista) (* (sqr arista) CARAS))

(check-expect (area-cubo 0) 0)
(check-expect (area-cubo 1) 6)
(check-expect (area-cubo 2) 24)
(check-expect (area-cubo 3) 54)