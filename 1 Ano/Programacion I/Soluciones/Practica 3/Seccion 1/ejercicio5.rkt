;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname ejercicio5) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define ANCHO 1000) ; Ancho de la escena.
(define ALTO ANCHO) ; Alto de la escena.
(define MITADX (/ ANCHO 2)) ; Mitad horizontal.
(define MITADY (/ ALTO 2)) ; Mitad vertical.
(define ESCENA (empty-scene ANCHO ALTO)) ; Escena vacia.
(define RELLENO "solid") ; Relleno del circulo.
(define RADIO (/ ANCHO 20)) ; Radio del circulo.

; Un Estado es una cadena que representa color de un circulo
; dibujado en el centro de la pantalla.
(define INICIAL "yellow") ; Color inicial.

; dibujar: Estado -> Image
; Dado un estado, devuelve la imagen a mostrar por el programa.
(define (dibujar estado)
  (place-image (circle RADIO RELLENO estado) MITADX MITADY ESCENA)
)

; tiempo: Estado -> Estado
; Dado un estado, devuelve el estado al que debe transicionarse
; cada vez que el tiempo transcurre.
(define (tiempo estado)
  (cond [(string=? estado INICIAL) "red"]
        [(string=? estado "red") "green"]
        [(string=? estado "green") "blue"]
        [else INICIAL]
  )
)

(big-bang INICIAL
  [to-draw dibujar]
  [on-tick tiempo 1]
)