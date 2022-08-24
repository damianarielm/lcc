;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname pong) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
;----CONSTANTES DE DIMENSIONES----
(define ANCHO 600)
(define PROPORCION 0.75)
(define ALTO (* ANCHO PROPORCION))
(define CENTROX (/ ANCHO 2))
(define CENTROY (/ ALTO 2))
;---------------------------------

;-----------------------CONSTANTES DE IMAGENES------------------------
(define PELOTA (circle (/ ANCHO 95) "solid" "blue"))
(define IZQUIERDA (rectangle (/ ANCHO 90) (/ ALTO 7) "solid" "green"))
(define DERECHA (rectangle (/ ANCHO 90) (/ ALTO 7) "solid" "red"))
(define FONDO (empty-scene ANCHO ALTO))
;---------------------------------------------------------------------

;--------CONSTANTES DE TAMAÑOS-----------
(define RADIO (/ (image-width PELOTA) 2))
(define MARGEN (image-width IZQUIERDA))
(define MARGENI MARGEN)
(define MARGEND (- ANCHO MARGEN))
(define VELOCIDAD-TECLADO (* RADIO 1.7))
(define ACELERACION-PELOTA 1.05)
;----------------------------------------

;------------------------CONSTANTES ESTRUCTURA-------------------------
(define-struct estado [izquierda derecha pelota direccion])
(define CENTRO (make-posn CENTROX CENTROY))
(define DIRECCION-INICIAL (make-posn 3 3))
(define INICIAL (make-estado CENTROY CENTROY CENTRO DIRECCION-INICIAL))
;----------------------------------------------------------------------

;-------------------SETEADORES------------------
;setear-izquierda: Estado Number -> Estado
(define (setear-izquierda estado izquierda)
  (make-estado izquierda
               (estado-derecha estado)
               (estado-pelota estado)
               (estado-direccion estado)
  )
)

;setear-derecha: Estado Number -> Estado
(define (setear-derecha estado derecha)
  (make-estado (estado-izquierda estado)
               derecha
               (estado-pelota estado)
               (estado-direccion estado)
  )
)

;setear-direccion: Estado Direccion -> Estado
(define (setear-direccion estado direccion)
  (make-estado (estado-izquierda estado)
               (estado-derecha estado)
               (estado-pelota estado)
               direccion
  )
)

;setear-pelota: Estado Pelota -> Estado
(define (setear-pelota estado pelota)
  (make-estado (estado-izquierda estado)
               (estado-derecha estado)
               pelota
               (estado-direccion estado)
  )
)
;-----------------------------------------------

;----------------FUNCIONES DE VECTORES--------------
;mover-pelota: Pelota Direccion -> Pelota
(define (mover-pelota pelota direccion)
  (make-posn (+ (posn-x pelota) (posn-x direccion))
             (+ (posn-y pelota) (posn-y direccion))
  )
)

;rebotar-vertical: Direccion -> Direccion
(define (rebotar-vertical direccion)
  (make-posn (posn-x direccion)
             (- (posn-y direccion))
  )
)

;rebotar-horizontal: Direccion -> Direccion
(define (rebotar-horizontal direccion)
  (make-posn (- (posn-x direccion))
             (posn-y direccion)
  )
)

;acelerar-direccion: Escalar Direccion -> Direccion
(define (acelerar-direccion escalar direccion)
  (make-posn (* escalar (posn-x direccion))
             (* escalar (posn-y direccion))
  )
)
;---------------------------------------------------

;-----------------------------DETECCION DE COLISIONES-------------------------------------
;golpea-paleta-izquierda?: Pelota Number -> Bool
(define (golpea-paleta-izquierda? pelota izquierda)
  (and
    (<= (posn-x pelota) (+ MARGEN (/ (image-width IZQUIERDA) 2) RADIO))
    (>= (posn-y pelota) (- izquierda RADIO (/ (image-height IZQUIERDA) 2)))
    (<= (posn-y pelota) (+ izquierda RADIO (/ (image-height IZQUIERDA) 2)))
  )
)

;golpea-paleta-derecha?: Pelota Number -> Bool
(define (golpea-paleta-derecha? pelota derecha)
  (and
    (>= (posn-x pelota) (- ANCHO MARGEN (/ (image-width DERECHA) 2) RADIO))
    (>= (posn-y pelota) (- derecha RADIO (/ (image-height DERECHA) 2)))
    (<= (posn-y pelota) (+ derecha RADIO (/ (image-height DERECHA) 2)))
  )
)

;golpea-paleta?: Estado -> Bool
(define (golpea-paleta? estado)
  (or (golpea-paleta-izquierda? (estado-pelota estado) (estado-izquierda estado))
      (golpea-paleta-derecha? (estado-pelota estado) (estado-derecha estado))
  )
)

;golpea-borde-izquierdo?: Pelota -> Bool
(define (golpea-borde-izquierdo? pelota)
  (<= (posn-x pelota) (/ (image-width PELOTA) 2))
)

;golpea-borde-derecho?: Pelota -> Bool
(define (golpea-borde-derecho? pelota)
  (>= (posn-x pelota) (- ANCHO (/ (image-width PELOTA) 2)))
)

;golpea-borde-superior?: Pelota -> Bool
(define (golpea-borde-superior? pelota)
  (<= (posn-y pelota) (/ (image-width PELOTA) 2))
)

;golpea-borde-inferior?: Pelota -> Bool
(define (golpea-borde-inferior? pelota)
  (>= (posn-y pelota) (- ALTO (/ (image-width PELOTA) 2)))
)

;golpea-borde?: Pelota -> Bool
(define (golpea-borde? pelota)
  (or (golpea-borde-izquierdo? pelota)
      (golpea-borde-derecho? pelota)
      (golpea-borde-superior? pelota)
      (golpea-borde-inferior? pelota)
  )
)

;colision?: Estado -> Bool
(define (colision? estado) (or (golpea-paleta? estado) (golpea-borde? (estado-pelota estado))))
;----------------------------------------------------------------------------------------------

;---------------------------------------------CODIGO PRINCIPAL-----------------------------------------------
;dibujar: Estado -> Imagen
(define (dibujar estado)
  (place-image IZQUIERDA MARGENI (estado-izquierda estado)
  (place-image DERECHA MARGEND (estado-derecha estado)
  (place-image PELOTA (posn-x (estado-pelota estado)) (posn-y (estado-pelota estado))
  FONDO)))
)

;punto?: Pelota -> Bool
(define (punto? pelota)
  (or (golpea-borde-derecho? pelota) (golpea-borde-izquierdo? pelota))
)

;rebotar-direccion: Estado -> Estado
(define (rebotar-direccion estado)
  (setear-direccion estado 
                   (if (golpea-borde? (estado-pelota estado))
                       (rebotar-vertical (estado-direccion estado))
                       (rebotar-horizontal (estado-direccion estado))
                   )
  )
)

;rebotar: Estado -> Estado
(define (rebotar estado)
  (setear-pelota estado
                 (mover-pelota (estado-pelota estado) (estado-direccion estado))
  )
)

;manejar-colision: Estado -> Estado
(define (manejar-colision estado)
  (if (punto? (estado-pelota estado))
      INICIAL
      (rebotar (rebotar-direccion (setear-direccion estado
                                           (acelerar-direccion ACELERACION-PELOTA
                                                               (estado-direccion estado)
                                           )
                                  )
               )
      )
  )
)

;tiempo: Estado -> Estado
(define (tiempo estado)
  (if (colision? estado)
      (manejar-colision estado)
      (setear-pelota estado (mover-pelota (estado-pelota estado)
                                          (estado-direccion estado)
                            )
      )
  )
)

;teclado: Estado String -> Estado
(define (teclado estado tecla)
  (setear-izquierda estado
                    (+ (estado-izquierda estado)
                       (cond [(string=? tecla "up")  (- VELOCIDAD-TECLADO)]
                             [(string=? tecla "down") VELOCIDAD-TECLADO]
                             [else 0]
                       )
                    )
  )
)

;mouse: Estado Number Number String -> Estado
(define (mouse estado x y evento) (setear-derecha estado y))

(big-bang INICIAL
  [to-draw dibujar]
  [on-tick tiempo]
  [on-key teclado]
  [on-mouse mouse]
)