;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname ejercicio4) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define (clasificar-imagen imagen)
  (cond [(> (image-width imagen) (* 2 (image-height imagen))) "Muy ancha"]
        [(> (image-height imagen) (* 2 (image-width imagen))) "Muy angosta"]
        [(> (image-height imagen) (image-width imagen)) "Angosta"]
        [(= (image-height imagen) (image-width imagen)) "Cuadrada"]
        [else "Ancha"]
  )
)