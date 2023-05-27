;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname ejercicio9) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
; Representamos el valos mensual de una cuota en pesos
; con un numero.

(define DESCUENTO-2-AMIGOS 0.9)
(define DESCUENTO-3-AMIGOS 0.8)

(define DESCUENTO-2-MESES 0.85)
(define DESCUENTO-3-MESES 0.75)

(define LIMITE-DESCUENTO 0.65)

(define VALOR-CUOTA 650)