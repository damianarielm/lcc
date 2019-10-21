from abstractfactory import *
from random import choice

class Espanol(Idioma): # FabricaConcreta1
    def CrearCartaBlanca(self): # CrearProductoA
        return CartaBlancaEspanol()
    def CrearCartaNegra(self): # CrearProductoB
        return CartaNegraEspanol()

class CartaBlancaEspanol(CartaBlanca): # ProductoA1
    def __init__(self):
        self.texto = choice([ \
            "Una maldicion gitana", \
            "Un minuto de silencio", \
            "Mucho pibe, poca mina", \
            "Un policia honesto, sin nada que perder", \
            "Hambruna", \
            "Bacteria come-carne", \
            "Serpientes sexuales voladoras", \
            "Que no te importe un carajo el tercer mundo", \
            "Sexting", \
            "Criaturas cambia-aspecto", \
            "Estrellas porno", \
            "Saquear y violar", \
            "72 virgenes", \
            "Persecusion y tiroteo", \
            "Una paradoja temporal", \
            "Autentica comida mejicana", \
            "Bijouterie de Once", \
            "Consultores", \
            "Deuda impagable", \
            "Complejo de ELektra", \
            "El 10 de Pachano", \
            "Tirar un candelabro sobre tus enemigos y subir colgado de la soga", \
            "Carlos Saul Menem", \
            "Desnudo fontral total", \
            "Inyecciones hormonales", \
            "Poner un huevo", \
            "Desnudarse y mirar Nickelodeon", \
            "Fingir que te importa", \
            "Hacer el ridiculo en publico", \
            "Compartir jeringas", \
            "Mocos", \
            "La inevitable muerte por calor del universo", \
            "El milagro del nacimiento", \
            "El apocalipsis", \
            "Sacar el amigo", \
            "Privilegios de la gente blanca", \
            "Obligaciones de casada", \
            "El Hamburglar (McDonalds)", \
            "Desodorante AXE", \
            "La Sangre de Cristo", \
            "Accidente horrorificos con laser para remocion de pelo", \
            "BATMAN!!!", \
            "Agricultura", \
            "Un mongoloide robusto", \
            "Seleccion natural", \
            "Abortos hechos con perchas", \
            "Comerse todas las galletitas antes de la venta de galleta para el SIDA", \
            "El escote de la diputada Hot", \
            "World of Warcraft", \
            "Proteger a una amiga de un hinchapelotas", \
            "Obesidad", \
            "Un montaje homoerotico de Voleibol", \
            "Mandibula trabada", \
            "Un ritual de apareamiento", \
            "Torsion testicular", \
            "Sushi de Tenedor Libre", \
            "Ricardo Fort", \
            "Queso caliente", \
            "Ataques de Velocirraptors", \
            "Sacarte la remera", \
            "Smegma", \
            "Alcoholismo", \
            "Un hombre de mediana edad andando en rollers", \
            "Super Rayo Cariñosito", \
            "Tener arcadas y vomitar", \
            "Chupetines demasiado grandes", \
            "Odiarse a uno mismo", \
            "Niños con correas", \
            "Juego previo de medio pelo", \
            "La biblia", \
            "Porno extremo aleman", \
            "Estar prendido fuego", \
            "Embarazo adolescente", \
            "Ghandi" , \
            "Dejar un mensaje de voz incomodo", \
            "Uppercuts", \
            "Representantes de Servicio al Consumidor", \
            "Una ereccion que dure mas de 4 horas", \
            "Mis genitales", \
            "Ir de levante a una clinica de abortos", \
            "Ciencia", \
            "Sexo oral no reciprocado", \
            "Aves que no pueden volar", \
            "Una buena linea", \
            "Tortura por ahogamiento simulado", \
            "Un desayuno balanceado", \
            "El Normal 4", \
            "Sacarle un dulce a un niño. De verdad", \
            "Un Sol para los chicos", \
            "Rascarse el culo a escondidas", \
            "Post-it-pasivo-agresivos", \
            "El equipo de gimnasia de China", \
            "Pasarse a la Caja de Ahorro", \
            "Mear un poquito", \
            "Video casero de Claribel Medina llorando mientras come una viandita de Cormillot", \
            "Eyaculaciones nocturnas", \
            "Los judios", \
            "Mis curvas", \
            "Muslos poderosos", \
            "Giñarle el ojo a gente mayor", \
            "Mr Musculo, saliendo de la nada", \
            "Una suave caricia en el interior del muslo", \
            "Tension sexual", \
            "La fruta prohibida", \
            "Skeletor", \
            "Whiskas", \
            "Ser rico", \
            "Dulce venganza", \
            "Menemismas", \
            "Un antilope con cases", \
            "Natalie Portman", \
            "Una tocadita disimulada", \
            "Pilotos Kamikaze", \
            "Sean Connery", \
            "La legislacion homosexual", \
            "El paraguayo trabajador en serio", \
            "Un pajaro en una jaula cubierta", \
            "Monaguillos", \
            "La Caja Vengadora", \
            "Enojarte tanto que se te para", \
            "Muestras gratis", \
            "Mucho ruido y pocas nueces", \
            "Hacer lo correcto", \
            "La Asamblea del año XIII", \
            "Lactacion", \
            "Paz mundial", \
            "RoboCop", \
            "Cabeza de termo", \
            "Justin Bieber", \
            "Oompa-Loompas", \
            "Gemido Tiroles", \
            "Pubertad", \
            "Fantasmas", \
            "Lolas hechas asimetricas", \
            "Las Manos Magicas", \
            "Colarse los dedos", \
            "Mariano Grondona agarrandose el escroto en un gancho de cortina", \
            "Naranju", \
            "Brutalidad policiaca", \
            "El petiso orejudo", \
            "Preadolescentes", \
            "Escalpar", \
            "Tweeting", \
            "Darth Vader", \
            "Una tirada de goma decepcionante", \
            "Exactamente lo que esperarias", \
            "Esperar un eructo y terminar vomitando en el piso", \
            "Celulas madre de embriones", \
            "Escote elegante y pronunciado", \
            "No ponerla nunca", \
            "Una lobotomia hecha con un picahielo", \
            "Tom Cruise", \
            "Herpes bucal", \
            "Cachalote", \
            "Gente sin casa", \
            "Tercera base", \
            "Incesto", \
            "Pac-man traga-leche", \
            "Un mimo teniendo un ataque", \
            "Hulk Hogan"
        ])

class CartaNegraEspanol(CartaNegra): # ProductoB1
    def __init__(self):
        self.textos = choice([ \
            ["La normativa de la Secretaria de Transporte ahora prohibe ", None, " en los aviones"], \
            ["Es una pena que hoy en dia los jovenes se estan metiendo con ", None], \
            ["En 1000 años, cuando el papel moneda sea una memoria distante, ", None, " va a ser nuestra moneda"], \
            ["La Asociacion de Futbol Argentino ha prohibido ", None, " por dar a los jugadores una ventaja injusta"], \
            ["¿Cual es el placer culposo de Batman? ", None], \
            ["Lo nuevo de JK Rowling: Harry Potter y la Camara de ", None], \
            ["¿Que me traje de vuelta de Paraguay? ", None], \
            ["¿", None, "? Hay una app para eso"], \
            [None, ". ¿A que no podes comer solo una?"], \
            ["¿Cual es mi sustituto para no usar drogas? ", None], \
            ["Cuando los EEUU y la URSS corrian la carrera espacial, el gobierno Argentino dedico millones de pesos a la investigacion de ", None], \
            ["En la nueva pelicula original de Disney Channel, Hannah Montana se enfrenta a ", None, " por la primera vez"], \
            ["¿Cual es mi poder secreto? ", None], \
            ["¿Cual es la nueva dieta de moda? ", None], \
            ["¿Que comio Vin Diesel para la cena? ", None], \
            ["Cuando el Faraon se mantuvo en su postura, Moises llamo una Plaga de ", None], \
            ["¿Que hago para mantener estable mi relacion amorosa? ", None], \
            ["¿Que es lo mas crujiente? ", None], \
            ["En la carcel de Devoto se dice que podes cambiar 200 cigarrillos por ", None], \
            ["Despues del terremoto, Sean Penn llevo ", None, " a la gente de Haiti"] , \
            ["Ahora, en vez de carbon, Papa Noel le da ", None , " a los chicos malos"] , \
            ["La vida para los pueblos originarios cambio drasticamente cuando el hombre blanco le mostro ", None], \
            ["En los momentos finales de Michael Jackson, penso en ", None], \
            ["A la gente blanca le gusta, ", None], \
            ["¿Por que me duele todo? ", None], \
            ["Una cena romantica a la luz de las velas estaria incompleta sin ", None], \
            ["¿Que llevaria en un viaje al pasado para convencer a la gente de que son un poderoso hechicero? ", None], \
            ["La excursion del curso fue arruinada completamente por ", None], \
            ["¿Que es el mejor amigo de una chica? ", None], \
            ["Cuando sea Presidente de la Argentina, voy a crear el Ministerio de ", None], \
            ["¿Que me estan escondiendo mi padres? ", None], \
            ["¿Que nunca falla para armar una fiesta?", None], \
            ["¿Que mejora con la edad?", None], \
            [None, ": Rico hasa la ultima gota"], \
            ["Tengo 99 problemas, pero ", None, " no es uno"], \
            [None, ". It's a trap"], \
            ["El nuevo Gran Hermano Famosos va a tener 8 famosos de segunda viviendo con ", None], \
            ["¿Que encontraria la abuela perturbador, pero extrañamente encantador? ", None], \
            ["¿Que es lo mas emo? ", None], \
            ["Durante el sexo, me gusta pensar en ", None], \
            ["¿Que termino mi ultima relacion? ", None], \
            ["¿Que ruido es ese? ", None], \
            [None, ". Asi quiero morir"], \
            ["¿Por que estoy pegajoso? ", None], \
            ["¿Cual es el proximo juguete de La Cajita Feliz? ", None], \
            ["De que hay un monton en el cielo? ", None], \
            ["No se con que armas se luchara la tercera guerra mundial, pero la cuarta se luchara con ", None], \
            ["¿Que siempre lograra llevarte a la cama? ", None], \
            [None, ": Probado en niños, aprobado por madres"], \
            ["¿Por que no me puedo dormir por las noches? ", None], \
            ["¿Que es ese olor? ", None], \
            ["¿Que ayuda a CFK a relajarse? ", None], \
            ["Asi termina el mundo, no con un bang, sino con ", None], \
            ["Llea a la Calle Corrientes este verano, ", None, ": El Musical"], \
            ["Antropologos han descubierto recientemente a una tribu primitiva que adora ", None], \
            ["Pero antes de matarlo, Sr. Bond, debo mostrarle ", None], \
            ["Estudios muestran que las ratas de laboratorio recorren laberintos 50% mas rapido despues de ser expuestas a ", None], \
            ["A continuacion, en ESPN+: El torneo mundial de ", None], \
            ["Cuando sea billonario, eligire una estatua de 15 metros de altura conmemorando ", None], \
            ["Con la intencion de atraer mas publico, el Museo Nacional de Ciencias Naturales abrio una exhibicion interactiva de ", None], \
            ["Yo me pregunto, ¿para que sirve la guerra? ", None], \
            ["¿Que me da gases incontrolables? ", None], \
            ["¿A que huele la gente mayor? ", None], \
            ["La medicina alternativa esta usando ahora las propiedades curativas de ", None], \
            ["¿Que prefiere Francisco de Narvaez? ", None], \
            ["Durante el frecuentemente no tenido en cuenta Periodo Marron de Picasso, el produjo cientos de pinturas de ", None], \
            ["¿Que no queres encontrar en tu comida China? ", None], \
            ["Tomo para olvidar ", None], \
            [None, ". Choca los 5, papa"], \
            ["Lo siento profesor, pero no pude completar mi tarea porque ", None], \
            ["¿Cual es el proximo duo de Superheroe/Ayudante? ", None, None], \
            ["Si, yo mate a ", None, ". ¿Como, preguntas? ", None], \
            ["Y el premio de la academia por ", None, " es para ", None], \
            ["Para mi proximo truco, sacare ", None, " de ", None], \
            ["Paso 1: ", None, ". Paso 2: ", None, ". Paso 3: Ganancia"], \
            ["Cuando estaba volando con LSD, ", None, " se convirtio en ", None], \
            [None, " es un camino de ida a ", None], \
            ["En un mundo destrozado por ", None, ", nuestro unico consuelo es ", None], \
            ["En la nueva pelicula de M. Night Shyamalan, Bruce Willis descrubre que ", None, " era en realidad ", None], \
            ["Nunca entendi ", None, " hasta que me encontre con ", None], \
            ["El rumor dice que el plato preferido de  Fernando De la Rua es ", None, " relleno de ", None], \
            ["E! True Hollywood Story presenta ", None, ": la historia de ", None], \
            ["Hace un haiku ", None], \
            [None, " + ", None, " = ", None]
        ])
