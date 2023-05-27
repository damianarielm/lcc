;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname ejercicio6) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define ANCHO 1000) ; Ancho de la escena.
(define ALTO (/ ANCHO 10)) ; Alto de la escena.
(define MITADY (/ ALTO 2)) ; Mitad vertical.
(define ESCENA (empty-scene ANCHO ALTO)) ; Escena vacia.
(define COLOR "indigo") ; Color del texto.
(define TAMANO (/ ALTO 2)) ; Tamaño del texto.

; Un Estado es una cadena que representa el texto
; escrito hasta el momento
(define INICIAL "") ; Texto inicial.

; dibujar: Estado -> Image
; Dado un estado, devuelve la imagen a mostrar por el programa.
(define (dibujar estado)
   (place-image/align (text estado TAMANO COLOR) 0 MITADY "left" "middle" ESCENA)
)

; teclado: Estado String -> Estado
; Dado el estado actual y la tecla presionada, agrega la letra al estado
; si corresponde, o elimina el ultimo caracter.
(define (teclado estado tecla)
  (cond [(string=? "\b" tecla) (if (= (string-length estado) 0)
                                   estado
                                   (substring estado 0 (- (string-length estado) 1))
                               )
        ]
        [else (string-append estado tecla)]
  )
)

(big-bang INICIAL
  [to-draw dibujar]
  [on-key teclado]
)