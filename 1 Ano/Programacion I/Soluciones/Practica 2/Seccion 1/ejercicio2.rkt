;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname ejercicio2) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define EPSILON 0.01) ; Tolerancia al error de los tests.

; Representamos una coordenada en un eje con un numero.

; distancia-puntos: Number Number Number Number -> Number
; Dadas las coordenadas x1 e y1 de un punto en el plano,
; y las coordenadas x2 e y2 de otro punto en el plano,
; determina la distancia del primer punto al segundo.
(define (distancia-puntos x1 y1 x2 y2)
  (sqrt (+ (sqr (- x1 x2)) (sqr (- y1 y2))))
)

(check-expect (distancia-puntos 0 0 0 0) 0)
(check-expect (distancia-puntos 3 4 6 8) 5)
(check-expect (distancia-puntos 1 1 6 13) 13)
(check-within (distancia-puntos 7 7 8 8) (sqrt 2) EPSILON)