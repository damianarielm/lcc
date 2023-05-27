;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname ejercicio4) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define ANCHO 1000) ; Ancho de la escena.
(define ALTO ANCHO) ; Alto de la escena.
(define MITADX (/ ANCHO 2)) ; Mitad horizontal.
(define MITADY (/ ALTO 2)) ; Mitad vertical.
(define ESCENA (empty-scene ANCHO ALTO)) ; Escena vacia.
(define RELLENO "solid") ; Relleno del circulo.
(define COLOR "blue") ; Color del circulo.
(define RADIO (/ ANCHO 20)) ; Radio del circulo.
(define DELTA RADIO) ; Desplazamiento del circulo.

; Un Estado es un numero que representa la posicion
; vertical de un circulo azul en el medio de la pantalla.
(define INICIAL MITADY) ; Posicion inicial del circulo.

; dibujar: Estado -> Image
; Dado un estado, devuelve la imagen a mostrar por el programa.
(define (dibujar estado)
  (place-image (circle RADIO RELLENO COLOR) MITADX estado ESCENA)
)

; mover-arriba: Estado -> Estado
; Dado un estado, lo desplaza hacia arriba si el circulo no
; queda afuera de la pantalla.
(define (mover-arriba estado)
  (if (>= estado (* RADIO 2))
      (- estado DELTA)
      estado
  )
)

; mover-abajo: Estado -> Estado
; Dado un estado, lo desplaza hacia abajo si el circulo no
; queda afuera de la pantalla.
(define (mover-abajo estado)
  (if (<= estado (- ALTO (* RADIO 2)))
      (+ estado DELTA)
      estado
  )
)

; teclado: Estado String -> Estado
; Dado un Estado y la tecla presionada, devuelve el nuevo
; Estado del programa.
(define (teclado estado tecla)
  (cond [(string=? tecla " ") INICIAL]
        [(string=? tecla "up") (mover-arriba estado)]
        [(string=? tecla "down") (mover-abajo estado)]
        [else estado]
  )
)

; mouse: Estado Number Number String -> Estado
; Dado un estado, dos numeros que representan la posicion
; del mouse y una cadena que representa el evento que se produjo,
; devuelve la posicion vertical del mouse.
(define (mouse estado x y evento)
   (cond [(string=? evento "button-down") y]
         [else estado]
   )
)

(big-bang INICIAL
  [to-draw dibujar]
  [on-key teclado]
  [on-mouse mouse]
)