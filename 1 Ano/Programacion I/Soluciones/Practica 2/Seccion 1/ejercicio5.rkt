;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname ejercicio5) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
; Representamos la posicion dentro de una cadena con un numero.
; La posicion cero representa la primer posicion dentro de una cadena.
; Por ejemplo el caracter 0 de la cadena "Damian" es "D".

; string-insert: String Number -> String
; Dada una cadena y una posicion, inserta un guion en dicha posicion
; de la cadena. La funcion no reemplaza el caracter ubicado en la
; posicion, sino que desplaza el resto del texto a la derecha.
(define (string-insert cadena posicion)
  (string-append (substring cadena 0 posicion)
                 "-"
                 (substring cadena posicion)
  )
)

(check-expect (string-insert "DamianAriel" 0) "-DamianAriel")
(check-expect (string-insert "DamianAriel" 6) "Damian-Ariel")
(check-expect (string-insert "DamianAriel" 11) "DamianAriel-")
  