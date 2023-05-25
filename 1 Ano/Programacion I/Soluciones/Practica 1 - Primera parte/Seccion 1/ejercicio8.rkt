;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname ejercicio8) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define (pitagorica? a b c)  
  (string-append "Los numeros "
                 (number->string a)
                 ", "
                 (number->string b)
                 " y "
                 (number->string c)
                 (if (= (+ (sqr a) (sqr b)) (sqr c))
                     " "
                     " no "
                 )
                 "forman una terna pitagorica."
  )
)