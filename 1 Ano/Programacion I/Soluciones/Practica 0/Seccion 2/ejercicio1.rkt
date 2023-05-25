;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname ejercicio1) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
; Apartado a
(- (* 12 5) (* 7 6))

(+ (- (* 3 5) (/ (* 7 4) 14)) (/ 3 1))

(+ (cos 0.8) 1/5 (* (sin 0.5) 3.5))

; Apartado b
;(- (* 12 5) (* 7 6))
;===<Definicion de *>
;(- 60 (* 7 6))
;===<Definicion de *>
;(- 60 42)
;===<Definicion de ->
;18

;(+ (- (* 3 5) (/ (* 7 4) 14)) (/ 3 1))
;===<Definicion de *>
;(+ (- 15 (/ (* 7 4) 14)) (/ 3 1))
;===<Definicion de *>
;(+ (- 15 (/ 28 14)) (/ 3 1))
;===<Definicion de />
;(+ (- 15 2) (/ 3 1))
;===<Definicion de ->
;(+ 13 (/ 3 1))
;===<Definicion de />
;(+ 13 3)
;===<Definicion de +>
;16

;(+ (cos 0.8) 1/5 (* (sin 0.5) 3.5))
;=~=<Definicion de cos>
;(+ 0.6967 1/5 (* (sin 0.5) 3.5))
;=~=<Definicion de +>
;(+ 0.8967 (* (sin 0.5) 3.5))
;=~=<Definicion de sin>
;(+ 0.8967 (* 0.4794 3.5))
;=~=<Definicion de *>
;(+ 0.8967 1.6779)
;=~=<Definicion de +>
;2.5746