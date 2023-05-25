;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname ejercicio1) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
; Apartado a
(string-append "Hola" "mundo")
;"Holamundo"

; Apartado b
(string-append "Pro" "gra" "ma.")
;"Programa."

; Apartado c
(number->string 1357)
;"1357"

; Apartado d
;(string-append "La respuesta es " (+ 21 21))
;string-append: expects a string, given 42

; Apartado e
(string-append "La respuesta es " (number->string (+ 21 21)))
;"La respuesta es 42"

; Apartado f
(* (string-length "Hola") (string-length "Chau"))
;16