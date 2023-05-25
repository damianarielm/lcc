;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname ejercicio1) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define (sgn2 x) (cond [(< x 0) -1]
                       [(= x 0) 0]
                       [(> x 0) 1])
)

;(sgn2 (- 2 3))
;===<Definicion de ->
;(sgn2 -1)
;===<Definicion de sgn2>
;(cond [(< -1 0) -1]
;      [(= -1 0) 0]
;      [(> -1 0) 1])
;===<Definicion de "<">
;(cond [#true -1]
;      [(= -1 0) 0]
;      [(> -1 0) 1])
;===<Definicion de cond>
;-1

;(sgn2 6)
;===<Definicion de sgn2>
;(cond [(< 6 0) -1]
;      [(= 6 0) 0]
;      [(> 6 0) 1])
;===<Definicion de "<">
;(cond [#false -1]
;      [(= 6 0) 0]
;      [(> 6 0) 1])
;===<Definicion de cond>
;(cond [(= 6 0) 0]
;      [(> 6 0) 1])
;===<Definicion de =>
;(cond [#false 0]
;      [(> 6 0) 1])
;===<Definicion de cond>
;(cond [(> 6 0) 1])
;===<Definicion de ">">
;(cond [#true 1])
;===<Definicion de cond>
;1