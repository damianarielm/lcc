;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname ejercicio1) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define RELLENO "solid")
(define ANCHO 90)
(define ALTO (/ ANCHO 1.5))
(define MITADX (/ ANCHO 2))
(define MITADY (/ ALTO 2))
(define ESCENA (empty-scene ANCHO ALTO))
(define ALTO-FRANJA (/ ALTO 3))
(define ANCHO-FRANJA (/ ANCHO 3))

; Apartado a
(place-image (beside (rectangle ANCHO-FRANJA ALTO RELLENO "red")
                     (rectangle ANCHO-FRANJA ALTO RELLENO "white")
                     (rectangle ANCHO-FRANJA ALTO RELLENO "red")
             )
             MITADX
             MITADY
             ESCENA
)

; Apartado b
(place-image (beside (rectangle ANCHO-FRANJA ALTO RELLENO "green")
                     (rectangle ANCHO-FRANJA ALTO RELLENO "white")
                     (rectangle ANCHO-FRANJA ALTO RELLENO "red")
             )
             MITADX
             MITADY
             ESCENA
)

; Apartado c
(define (bandera-vertical c1 c2 c3)
  (place-image (beside (rectangle ANCHO-FRANJA ALTO RELLENO c1)
                       (rectangle ANCHO-FRANJA ALTO RELLENO c2)
                       (rectangle ANCHO-FRANJA ALTO RELLENO c3)
               )
               MITADX
               MITADY
               ESCENA
  )
)

; Apartado d
(place-image (above (rectangle ANCHO ALTO-FRANJA RELLENO "black")
                    (rectangle ANCHO ALTO-FRANJA RELLENO "red")
                    (rectangle ANCHO ALTO-FRANJA RELLENO "yellow")
             )
             MITADX
             MITADY
             ESCENA
)

; Apartado e
(place-image (above (rectangle ANCHO ALTO-FRANJA RELLENO "red")
                    (rectangle ANCHO ALTO-FRANJA RELLENO "white")
                    (rectangle ANCHO ALTO-FRANJA RELLENO "blue")
             )
             MITADX
             MITADY
             ESCENA
)

; Apartado f
(define (bandera-horizontal c1 c2 c3)
  (place-image (above (rectangle ANCHO ALTO-FRANJA RELLENO c1)
                      (rectangle ANCHO ALTO-FRANJA RELLENO c2)
                      (rectangle ANCHO ALTO-FRANJA RELLENO c3)
               )
               MITADX
               MITADY
               ESCENA
  )
)

; Apartado g
(define (bandera c1 c2 c3 sentido)
  (if (string=? sentido "vertical")
      (bandera-vertical c1 c2 c3)
      (bandera-horizontal c1 c2 c3)
  )
)

; Apartado h
(bandera "blue" "white" "red" "vertical")

; Apartado i
(overlay/align "left"
               "middle"
               (rotate -90 (triangle ALTO RELLENO "green"))
               (bandera "red" "white" "black" "horizontal")
)

(overlay/align "middle"
               "middle"
               (circle (/ ALTO-FRANJA 2) RELLENO "yellow")
               (bandera "blue" "white" "blue" "horizontal")
)

(overlay/align "middle"
               "middle"
               (star (/ ALTO-FRANJA 2) RELLENO "yellow")
               (bandera "green" "red" "yellow" "vertical")
)

; Apartado j
(overlay/align "middle"
               "middle"
               (circle (/ ALTO-FRANJA 2) RELLENO "blue")
               (overlay/align "middle"
                              "middle"
                              (beside (rotate 90 (triangle MITADX RELLENO "yellow"))
                                      (rotate -90 (triangle MITADX RELLENO "yellow"))
                              )
                              (bandera "green" "green" "green" "horizontal")
               )
)

; Apartado k
;(define ANCHO 180)