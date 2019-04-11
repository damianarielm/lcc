go :- hypothesize(Artista),
  write('Creo que el artista es: '),
  write(Artista),
  nl,
  undo.

hypothesize(palmeras)    :- palmeras, !.
hypothesize(leomatioli)  :- leomatioli, !.
hypothesize(damasgratis) :- damasgratis, !.
hypothesize(malafama)    :- malafama, !.
hypothesize(carabajal)   :- carabajal, !.
hypothesize(manseros)    :- manseros, !.

hypothesize(madonna)        :- madonna, !.
hypothesize(michaeljackson) :- michaeljackson, !.
hypothesize(queen)          :- queen, !.
hypothesize(deeppurple)     :- deeppurple, !.
hypothesize(bach)           :- bach, !.
hypothesize(vivaldi)        :- vivaldi, !.
hypothesize(mozart)         :- mozart, !.
hypothesize(beethoven)      :- beethoven.


cheetah :- mammal,
  carnivore,
  verify(has_tawny_color),
  verify(has_dark_spots).
tiger :- mammal,
  carnivore,
  verify(has_tawny_color),
  verify(has_black_stripes).
giraffe :- ungulate,
  verify(has_long_neck),
  verify(has_long_legs).
zebra :- ungulate,
  verify(has_black_stripes).
ostrich :- bird,
  verify(does_not_fly),
  verify(has_long_neck).
penguin :- bird,
  verify(does_not_fly),
  verify(swims),
  verify(is_black_and_white).
albatross :- bird,
  verify(appears_in_story_Ancient_Mariner),
  verify(flys_well).

mammal    :- verify(has_hair), !.
mammal    :- verify(gives_milk).
bird      :- verify(has_feathers), !.
bird      :- verify(flys),
  verify(lays_eggs).
carnivore :- verify(eats_meat), !.

carnivore :- verify(has_pointed_teeth),              
  verify(has_claws),             
  verify(has_forward_eyes).
ungulate :- mammal,             
  verify(has_hooves), !.
ungulate :- mammal,             
  verify(chews_cud).

ask(Question) :-
  write('El artista tiene el siguiente atributo?: '),
  write(Question),
  write('? '),
  read(Response),
  nl,
  ( (Response == yes ; Response == y)
    ->
      assert(yes(Question)) ;
      assert(no(Question)), fail).

:- dynamic yes/1,no/1.

verify(S) :-   
  (yes(S)     
    ->    
      true ;    
      (no(S)     
        ->     
	  fail ;     ask(S))).

undo :- retract(yes(_)),fail.
undo :- retract(no(_)),fail.
undo.


nacional :- verify(argentina).

cumbia :- nacional,
          verify(moderno).

folklore :- nacional,
            verify(antiguo).

chamame :- folklore,
           verify(guitarrac),
           verify(acordeon).

chacarera :- folklore,
             verify(bombo),
	     verify(guitarrac),
	     verify(violin).

villera :- cumbia,
           verify(keytar),
	   verify(guiro),
	   verify(bajo).

santafesina :- cumbia,
               verify(acordeon),
	       verify(guiro),
	       verify(bajo).

palmeras :- santafesina,
            verify(seis).

leomatioli :- santafesina,
              verify(uno).

damasgratis :- villera,
               verify(nueve).

malafama :- villera,
            verify(ocho).

carabajal :- chacarera,
             verify(cuatro).

manseros :- chacarera,
            verify(tres).


internacional :- verify(noargentina).

academica :- internacional,
             verify(antigua).

barroco :- acadeimca,
           verify(bajocontinuo).

clasico :- academica,
           verify(homofonico).

popular :- internacional,
           verify(moderna).

rock :- popular,
        verify(guitarrae),
	verify(bateria),
	verify(bajo).

pop :- popular,
       verify(teclado).

madonna :- pop,
           verify(mujer).

michaeljackson :- pop,
                  verify(violador).

queen :- rock,
         verify(cuatro).

deeppurple :- rock,
              verify(cinco).

bach :- barroco,
        verify(castano).

vivaldi :- barroco,
           verify(pelirrojo).

mozart :- clasico,
          verify(mason).

beethoven :- clasico,
             verify(sordo).
