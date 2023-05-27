;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname ejercicio1) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define ANCHO 200) ; Ancho de la escena.
(define ALTO ANCHO) ; Alto de la escena.
(define MITADX (/ ANCHO 2)) ; Mitad horizontal.
(define MITADY (/ ALTO 2)) ; Mitad vertical.
(define RADIO (/ ANCHO 20)) ; Radio del circulo.
(define ESCENA (empty-scene ANCHO ALTO)) ; Escena vacia.
(define RELLENO "solid") ; Relleno del circulo.

; Un Estado es un string que representa el color de un circulo
; en el medio de la pantalla.
(define INICIAL "blue") ; Color inicial del circulo.

; dibujar: Estado -> Image
; Dado un estado, devuelve la imagen a mostrar por el programa.
(define (dibujar estado)
  (place-image (circle RADIO RELLENO estado) MITADX MITADY ESCENA)
)

; teclado: Estado String -> Estado
; Dado un Estado y la tecla presionada, devuelve el nuevo
; Estado del programa.
(define (teclado estado tecla)
  (cond [(string=? tecla "a") "blue"]
        [(string=? tecla "r") "red"]
        [(string=? tecla "v") "green"]
        [else estado]
  )
)

(big-bang INICIAL
  [to-draw dibujar]
  [on-key teclado]
)