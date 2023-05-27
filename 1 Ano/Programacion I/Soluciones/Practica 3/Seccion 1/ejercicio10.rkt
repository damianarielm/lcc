;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname huella) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
;Constantes de escena
(define ANCHO 500) ;Ancho de la escena.
(define ALTO (/ ANCHO 6)) ;Alto de la escena.
(define CENTROY (/ ALTO 2)) ;Centro vertical.
(define FONDO (empty-scene ANCHO ALTO)) ;Escena de fondo.

;Constantes del pie
(define TAMANO (/ ANCHO 10)) ;Tamano del pie.
(define VELOCIDAD (floor (/ TAMANO 2))) ;Velocidad de avance (IMPAR).
(define PIE-DERECHO (rotate -90 (triangle TAMANO "solid" "red"))) ;Pie derecho.
(define PIE-IZQUIERDO (rotate -90 (triangle TAMANO "solid" "green"))) ;Pie izquierdo.

;Definimos el estado como un numero donde:
;- El signo indica el sentido del camino (positivo hacia la derecha).
;- La paridad indica el pie a dibujar (par para el pie derecho).
;- La magnitud indica la posicion en el eje x.
(define INICIAL (image-width PIE-DERECHO)) ;Estado inicial

;posicion: Estado -> Number
;Dado un estado, devuelve la coordenada x.
(define (posicion estado) (abs estado))

;derecha?: Estado -> Bool
;Dado un estado, determina si el sentido es hacia la derecha.
(define (derecha? estado) (>= (sgn estado) 0))

;izquierda?: Estado -> Bool
;Dado un estado, determina si el sentido es hacia la izquierda.
(define (izquierda? estado) (not (derecha? estado)))

;pie-derecho?: Estado -> Bool
;Dado un estado, determina si se debe dibujar el pie derecho.
(define (pie-derecho? estado) (even? estado))

;pie-izquierdo?: Estado -> Bool
;Dado un estado, determina si se debe dibujar el pie izquierdo.
(define (pie-izquierdo? estado) (not (pie-derecho? estado)))

;imagen: Estado -> Image
;Dado un estado, devuelve la imagen del pie a dibujar.
(define (imagen estado)
  (cond [(and (derecha? estado) (pie-derecho? estado)) PIE-DERECHO]
        [(and (derecha? estado) (pie-izquierdo? estado)) PIE-IZQUIERDO]
        [(and (izquierda? estado) (pie-derecho? estado)) (rotate 180 PIE-DERECHO)]
        [(and (izquierda? estado) (pie-izquierdo? estado)) (rotate 180 PIE-IZQUIERDO)]
  )
)

;dibujar: Estado -> Estado
;Dado un estado, dibuja la huella en la pantalla.
(define (dibujar estado)
  (place-image (imagen estado) (posicion estado) CENTROY FONDO)
)

;afuera?: Number -> Bool
;Dada una coordenada x, determina si esta afuera de la escena.
(define (afuera? x)
  (or (< x (image-width PIE-DERECHO))
      (> x (- ANCHO (image-width PIE-DERECHO)))
  )
)

;tiempo: Estado -> Estado
;Dado un estado, avanza o retrocede la posicion segun corresponda.
(define (tiempo estado)
  (if (afuera? (posicion (+ estado VELOCIDAD)))
      (- estado)
      (+ estado VELOCIDAD)
  )
)

;mouse: Estado Number Number String -> Estado
(define (mouse estado x y evento)
  (if (string=? evento "button-down")
      (* (sgn estado) x) ;Cambia la posicion conservando el signo.
      estado
  )
)

(big-bang INICIAL
  [to-draw dibujar]
  [on-mouse mouse]
  [on-tick tiempo 0.15]
)