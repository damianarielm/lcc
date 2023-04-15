;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname estrellas) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define ALTO 600)                 ; Alto del dibujo
(define COLOR-CIELO "black")      ; Color del Cielo
(define RELLENO-CIELO "solid")    ; Relleno del cielo
(define COLOR-ESTRELLA "yellow")  ; Color de las estrellas
(define RELLENO-ESTRELLA "solid") ; Relleno de las estrellas
(define PROPORCION (/ 16 9))      ; Relacion de aspecto

(define ANCHO (* ALTO PROPORCION))
(define FONDO (empty-scene ANCHO ALTO COLOR-CIELO))
(define TAMAÑO-ESTRELLA (/ ALTO 20))
(define ESTRELLA (star TAMAÑO-ESTRELLA RELLENO-ESTRELLA COLOR-ESTRELLA))
(define RADIOH (/ (image-width ESTRELLA) 2))
(define RADIOV (/ (image-height ESTRELLA) 2))

; Un Estado es una imagen que se dibujara en la pantalla.

;sale-por-izquierda?: Numero -> Booleano
;Dada la coordenada x de una estrella, determina si
;esta se sale de la pantalla por la parte izquierda.
(define (sale-por-izquierda? x) (< x RADIOH))

;sale-por-derecha?: Numero -> Booleano
;Dada la coordenada x de una estrella, determina si
;esta se sale de la pantalla por la parte derecha.
(define (sale-por-derecha? x) (> x (- ANCHO RADIOH)))

;sale-por-arriba?: Numero -> Booleano
;Dada la coordenada y de una estrella, determina si
;esta se sale de la pantalla por la parte de arriba.
(define (sale-por-arriba? y) (< y RADIOV))

;sale-por-abajo?: Numero -> Booleano
;Dada la coordenada y de una estrella, determina si
;esta se sale de la pantalla por la parte de abajo.
(define (sale-por-abajo? y) (> y (- ALTO RADIOV)))

;entra-en-pantalla?: Numero Numero -> Booleano
;Dadas las coordenadas de una estrella, determina si
;esta entra en la pantalla.
(define (entra-en-pantalla? x y)
  (and (not (sale-por-izquierda? x))
       (not (sale-por-derecha? x))
       (not (sale-por-arriba? y))
       (not (sale-por-abajo? y))
  )
)

;dibujar: Estado -> Imagen
;Dado un estado, lo dibuja en la pantalla.
(define (dibujar estado) estado)

;mouse: Estado Numero Numero String -> Estado
;Si se produce un click con el mouse, agrega una estrella
;en la posicion correspondiente del estado.
(define (mouse estado x y evento)
  (if (and (string=? evento "button-down")
           (entra-en-pantalla? x y))
      (place-image ESTRELLA x y estado)
      estado
  )
)

;teclado: Estado String
;Al presionarse la tecla "backspace", se vuelve al estado inicial.
(define (teclado estado tecla)
  (if (string=? tecla "\b") FONDO estado)
)

(big-bang FONDO
  [to-draw dibujar] ; Dibuja el estado en la pantalla
  [on-mouse mouse]  ; Responde a eventos del mouse
  [on-key teclado]  ; Responde a eventos del teclado
)