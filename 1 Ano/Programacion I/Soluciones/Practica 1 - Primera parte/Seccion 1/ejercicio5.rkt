;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname ejercicio5) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define PC 60)  ; Precio de cuadernos.
(define DC 0.9) ; Descuento de cuadernos.
(define MC 4)   ; Minimo de cuadernos para el descuento.

(define PL 8)    ; Precio de lapices.
(define DL 0.85) ; Descuento de lapices.
(define ML 4)    ; Minimo de lapices para el descuento.

(define (aplica-oferta-lapices? l) (>= l ML))
(define (importe-lapices-normal l) (* l PL))
(define (importe-lapices-oferta l) (* (importe-lapices-normal l) DL))
(define (importe-lapices l)
  (if (aplica-oferta-lapices? l)
      (importe-lapices-oferta l)
      (importe-lapices-normal l)
  )
)

(define (aplica-oferta-cuadernos? c) (>= c MC))
(define (importe-cuadernos-normal c) (* c PC))
(define (importe-cuadernos-oferta c) (* (importe-cuadernos-normal c) DC))
(define (importe-cuadernos c)
  (if (aplica-oferta-cuadernos? c)
      (importe-cuadernos-oferta c)
      (importe-cuadernos-normal c)
  )
)

(define (monto c l)
  (+ (importe-lapices l)
     (importe-cuadernos c)
  )
)