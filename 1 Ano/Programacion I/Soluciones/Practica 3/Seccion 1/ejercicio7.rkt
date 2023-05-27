;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname ejercicio7) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define ANCHO 1000) ; Ancho de la escena.
(define ALTO (/ ANCHO 10)) ; Alto de la escena.
(define MITADY (/ ALTO 2)) ; Mitad vertical.
(define ESCENA (empty-scene ANCHO ALTO)) ; Escena vacia.
(define AUTO (rectangle (/ ANCHO 10) (/ ALTO 2) "solid" "yellow")) ; Dibujo del auto.
(define TAMANO (image-width AUTO)) ; Ancho del auto.
(define DELTA (/ ANCHO 100)) ; Velocidad del auto.

; Un Estado es un numero que representa la posicion
; horizontal de un auto en la pantalla.
(define INICIAL (/ TAMANO 2)) ; Posicion inicial.

; dibujar: Estado -> Image
; Dado un estado, devuelve la imagen a mostrar por el programa.
(define (dibujar estado)
   (place-image AUTO estado MITADY ESCENA)
)

; tiempo: Estado -> Estado
(define (tiempo estado)
  (if (<= estado (- ANCHO (/ TAMANO 2)))
      (+ estado DELTA)
      estado
  )
)

; teclado: Estado String -> Estado
(define (teclado estado tecla)
  (cond [(string=? tecla " ") INICIAL]
        [(string=? tecla "right") (+ estado (* DELTA 10))]
        [(string=? tecla "left") (- estado (* DELTA 10))]
        [else estado]
  )
)

; mouse: Estado Number Number String -> Estado
(define (mouse estado x y evento)
  (if (string=? evento "button-down") x estado)
)

(big-bang INICIAL
  [to-draw dibujar]
  [on-key teclado]
  [on-mouse mouse]
  [on-tick tiempo]
)