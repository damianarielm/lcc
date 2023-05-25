;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname ejercicio2) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
; Apartado a
; El coseno de 0 es positivo.
(> (cos 0) 0)

; Apartado b
; La longitud de la cadena "Hola, mundo" es 14.
(= (string-length "Hola, mundo") 14)

; Apartado c
; pi es un número entre 3 y 4.
(and (> pi 3) (< pi 4))

; Apartado d
; El área de un cuadrado de lado 5 es igual a la raíz cudrada de 625.
(= (sqr 5) (sqrt 625))

; Apartado e
; No es cierto que el tercer caracter de la cadena "Ada Lovelace" es "a".
(not (string=? (string-ith "Ada Lovelace" 2) "a"))