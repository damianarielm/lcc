;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname kaboom) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
;-------CONSTANTES DE DIMENSIONES-------
(define ALTO 600)
(define DISTANCIA (/ ALTO 10))
(define VELOCIDAD (/ ALTO 100))
(define RELACION (/ 16 9))
(define ANCHO (floor (* ALTO RELACION)))
(define CENTROX (/ ANCHO 2))
(define CENTROY (/ ALTO 2))
(define CANASTAY (- ALTO (/ ALTO 15)))
;---------------------------------------

;---------------CONSTANTES DE IMAGENES----------------
(define ESCENA (empty-scene ANCHO ALTO))
(define CANASTA (square (/ ALTO 10) "solid" "blue"))
(define PELOTA (circle (/ ALTO 50) "solid" "yellow"))
;-----------------------------------------------------

;-----------------------FUNCIONES AUXILIARES-----------------------
;generar-pelota: Number Number -> Posn
(define (generar-pelota x y) (make-posn (random x) (- (random y))))
;distancia: Posn Posn -> Number
(define (distancia posn1 posn2)
  (sqrt (+ (sqr (- (posn-x posn1) (posn-x posn2)))
           (sqr (- (posn-y posn1) (posn-y posn2)))))
)
;-------------------------------------------------------------------

;-------------CONSTANTES DE ESTRUCTURA-------------------
;estado: Number Posn Posn Posn -> Estado
(define-struct estado [canastax pelota1 pelota2 pelota3])
(define INICIAL (make-estado CENTROX
                             (generar-pelota ANCHO ALTO)
                             (generar-pelota ANCHO ALTO)
                             (generar-pelota ANCHO ALTO))
)
;--------------------------------------------------------

;----------------SETEADORES---------------
;setear-canastax: Estado Number -> Estado
(define (setear-canastax estado canastax)
  (make-estado canastax
               (estado-pelota1 estado)
               (estado-pelota2 estado)
               (estado-pelota3 estado))
)
;setear-pelota1: Estado Posn -> Estado
(define (setear-pelota1 estado pelota)
  (make-estado (estado-canastax estado)
               pelota
               (estado-pelota2 estado)
               (estado-pelota3 estado))
)
;setear-pelota2: Estado Posn -> Estado
(define (setear-pelota2 estado pelota)
  (make-estado (estado-canastax estado)
               (estado-pelota1 estado)
               pelota
               (estado-pelota3 estado))
)
;setear-pelota3: Estado Posn -> Estado
(define (setear-pelota3 estado pelota)
  (make-estado (estado-canastax estado)
               (estado-pelota1 estado)
               (estado-pelota2 estado)
               pelota)
)
;------------------------------------------

;------------------------------------CODIGO PRINCIPAL-----------------------------------
;dibujar: Estado -> Imagen
(define (dibujar estado)
  (place-image CANASTA (estado-canastax estado) CANASTAY
  (place-image PELOTA (posn-x (estado-pelota1 estado)) (posn-y (estado-pelota1 estado))
  (place-image PELOTA (posn-x (estado-pelota2 estado)) (posn-y (estado-pelota2 estado))
  (place-image PELOTA (posn-x (estado-pelota3 estado)) (posn-y (estado-pelota3 estado))
  ESCENA))))
)

;mouse: Estado Number Number String -> Estado
(define (mouse estado x y evento) (setear-canastax estado x))

;mover-pelota: Posn -> Posn
(define (mover-pelota pelota)
  (if (> (posn-y pelota) ALTO)
      (generar-pelota ANCHO ALTO)
      (make-posn (posn-x pelota) (+ (posn-y pelota) VELOCIDAD)))
)

;pelota-atrapada?: Number Posn -> Boolean
(define (pelota-atrapada? canasta pelota)
  (< (distancia (make-posn canasta CANASTAY) pelota) DISTANCIA)
)

;tiempo: Estado -> Estado
(define (tiempo estado)
  (cond [(pelota-atrapada? (estado-canastax estado) (estado-pelota1 estado))
         (setear-pelota1 estado (generar-pelota ANCHO ALTO))]
        [(pelota-atrapada? (estado-canastax estado) (estado-pelota2 estado))
         (setear-pelota2 estado (generar-pelota ANCHO ALTO))]
        [(pelota-atrapada? (estado-canastax estado) (estado-pelota3 estado))
         (setear-pelota3 estado (generar-pelota ANCHO ALTO))]
        [else (make-estado (estado-canastax estado)
                           (mover-pelota (estado-pelota1 estado))
                           (mover-pelota (estado-pelota2 estado))
                           (mover-pelota (estado-pelota3 estado)))])
)

(big-bang INICIAL
  [to-draw dibujar]
  [on-mouse mouse]
  [on-tick tiempo])
;---------------------------------------------------------------------