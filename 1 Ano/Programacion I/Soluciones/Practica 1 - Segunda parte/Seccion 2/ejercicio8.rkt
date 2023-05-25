;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname ejercicio8) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define (clasificar-imagen imagen)
  (if (= (image-height imagen) (image-width imagen))
      "Cuadrada"
      (if (> (image-height imagen) (image-width imagen))
          "Angosta"
          "Ancha"
      )
  )
)

(define (sgn-bool b)
  (if b 1 0)
)

(define (sgn-image i)
  (cond [(string=? (clasificar-imagen i) "Ancha") 1]
        [(string=? (clasificar-imagen i) "Cuadrada") 0]
        [else -1]
  )
)

(define (sgn-polimorfico x)
  (cond [(number? x) (sgn x)]
        [(string? x) (sgn (string->number x))]
        [(boolean? x) (sgn-bool x)]
        [(image? x) (sgn-image x)]
        [else "Clase no soportada para la funcion."]
  )
)