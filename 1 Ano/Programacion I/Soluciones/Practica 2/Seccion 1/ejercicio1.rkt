;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname ejercicio1) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define EPSILON 0.01) ; Tolerancia al error de los tests.

; Representamos una coordenada en un eje con un numero.

; distancia-origen: Number Number -> Number
; Dadas las coordenadas x e y de un punto en el plano,
; determina la distancia del punto que representan
; al origen de coordenadas.
(define (distancia-origen x y)
  (sqrt (+ (sqr x) (sqr y)))
)

(check-expect (distancia-origen 0 0) 0)
(check-expect (distancia-origen 3 4) 5)
(check-expect (distancia-origen 5 12) 13)
(check-within (distancia-origen 1 1) (sqrt 2) EPSILON)