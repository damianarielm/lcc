;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname ejercicio3) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define ANCHO 1000) ; Ancho de la escena.
(define ALTO ANCHO) ; Alto de la escena.
(define MITADX (/ ANCHO 2)) ; Mitad horizontal.
(define MITADY (/ ALTO 2)) ; Mitad vertical.
(define ESCENA (empty-scene ANCHO ALTO)) ; Escena vacia.
(define RELLENO "solid") ; Relleno del circulo.
(define COLOR-CHICO "yellow") ; Color de un circulo chico.
(define COLOR-MEDIANO "red") ; Color de un circulo mediano.
(define COLOR-GRANDE "green") ; Color de un circulo grande.

; Un Estado es un numero que representa el radio de un
; circulo en el medio de la pantalla.
(define INICIAL (/ ANCHO 20)) ; Radio inicial del circulo.

; elegir-color: Estado -> String
; Dado un estado, determina el color del circulo.
(define (elegir-color estado)
  (cond [(and (>= estado 0) (<= estado 50)) COLOR-CHICO]
        [(and (>= estado 51) (<= estado 100)) COLOR-MEDIANO]
        [else COLOR-GRANDE]
  )
)

; dibujar: Estado -> Image
; Dado un estado, devuelve la imagen a mostrar por el programa.
(define (dibujar estado)
  (place-image (circle estado RELLENO (elegir-color estado)) MITADX MITADY ESCENA)
)

; teclado: Estado String -> Estado
; Dado un Estado y la tecla presionada, devuelve el nuevo
; Estado del programa.
(define (teclado estado tecla)
  (cond [(string=? tecla "1") (* 10 (string->number tecla))]
        [(string=? tecla "2") (* 10 (string->number tecla))]
        [(string=? tecla "3") (* 10 (string->number tecla))]
        [(string=? tecla "4") (* 10 (string->number tecla))]
        [(string=? tecla "5") (* 10 (string->number tecla))]
        [(string=? tecla "6") (* 10 (string->number tecla))]
        [(string=? tecla "7") (* 10 (string->number tecla))]
        [(string=? tecla "8") (* 10 (string->number tecla))]
        [(string=? tecla "9") (* 10 (string->number tecla))]
        [else 0]
  )
)

; incrementar: Estado -> Estado
; Incrementar el estado del programa.
(define (incrementar estado)
  (if (< estado (/ ANCHO 2)) (+ estado 1) 0)
)

; terminar?: Estado -> Boolean
; Dado un estado, determina si el programa debe terminar.
(define (terminar? estado)
  (or (> estado 110) (< estado 10))
)

(big-bang INICIAL
  [to-draw dibujar]
  [on-tick incrementar]
  [on-key teclado]
  [stop-when terminar?]
)