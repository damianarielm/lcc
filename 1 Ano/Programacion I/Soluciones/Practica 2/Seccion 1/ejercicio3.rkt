;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname ejercicio3) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
; Representamos la longitud de una arista en metros con un numero.

; vol-cubo: Number -> Number
; Dada la longitud de una arista en metros, devuelve el volumen
; de un cubo de dicho tamaño en metros cubicos.
(define (vol-cubo arista) (expt arista 3))

(check-expect (vol-cubo 0) 0)
(check-expect (vol-cubo 1) 1)
(check-expect (vol-cubo 2) 8)
(check-expect (vol-cubo 3) 27)