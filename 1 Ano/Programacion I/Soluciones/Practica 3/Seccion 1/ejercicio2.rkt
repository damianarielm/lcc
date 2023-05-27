;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname ejercicio2) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define ANCHO 1000) ; Ancho de la escena.
(define ALTO ANCHO) ; Alto de la escena.
(define MITADX (/ ANCHO 2)) ; Mitad horizontal.
(define MITADY (/ ALTO 2)) ; Mitad vertical.
(define ESCENA (empty-scene ANCHO ALTO)) ; Escena vacia.
(define RELLENO "solid") ; Relleno del circulo.
(define COLOR "blue") ; Color del circulo.

; Un Estado es un numero que representa el radio de un
; circulo azul en el medio de la pantalla.
(define INICIAL (/ ANCHO 10)) ; Radio inicial del circulo.

; dibujar: Estado -> Image
; Dado un estado, devuelve la imagen a mostrar por el programa.
(define (dibujar estado)
  (place-image (circle estado RELLENO COLOR) MITADX MITADY ESCENA)
)

; decrementar Estado -> Estado
; Decrementa el estado del programa.
; Si el estado es cero, devuelve el estado inicial.
(define (decrementar estado)
  (if (= estado 0) INICIAL (- estado 1))
)

; incrementar: Estado -> Estado
; Incrementar el estado del programa.
(define (incrementar estado) (+ estado 1))

(big-bang INICIAL
  [to-draw dibujar]
  [on-tick decrementar]
)