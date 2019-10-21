from abstractfactory import *
from random import choice

class Ingles(Idioma): # FabricaConcreta2
    def CrearCartaBlanca(self): # CrearProductoA
        return CartaBlancaIngles()
    def CrearCartaNegra(self): # CrearProductoB
        return CartaNegraIngles()

class CartaBlancaIngles(CartaBlanca): #ProductoA2
    def __init__(self):
        self.texto = choice([ \
            "“Tweeting”",\
            "72 virgins",\
            "8 oz of sweet Mexican black-tar heroin",\
            "A 55-gallon drum of lube",\
            "A bag of magic beans",\
            "A balanced breakfast",\
            "A beached whale",\
            "A big black dick",\
            "A big hoopla about nothing",\
            "A bigger, blacker dick",\
            "A bleached asshole",\
            "A bloody pacifier",\
            "A Bop It",\
            "A brain tumor",\
            "A Burmese tiger pit",\
            "A can of whoop-ass",\
            "A Christmas stocking full of coleslaw",\
            "A clandestine butt scratch",\
            "A cooler full of organs",\
            "A crappy little hand",\
            "A death ray",\
            "A defective condom",\
            "A disappointing birthday party",\
            "A dollop of sour cream",\
            "A drive-by shooting",\
            "A falcon with a cap on its head",\
            "A fetus",\
            "A foul mouth",\
            "A gassy antelope",\
            "A gentle caress of the inner thigh",\
            "A good sniff",\
            "A Gypsy curse",\
            "A homoerotic volleyball montage",\
            "A hot mess",\
            "A Hungry-Man Frozen Christmas Dinner for One",\
            "A lifetime of sadness",\
            "A look-see",\
            "A low standard of living",\
            "A magic hippie love cloud",\
            "A man in yoga pants with a ponytail and feather earrings",\
            "A mating display",\
            "A micropenis",\
            "A middle-aged man on roller skates",\
            "A mime having a stroke",\
            "A monkey smoking a cigar",\
            "A mopey zoo lion",\
            "A murder most foul",\
            "A nuanced critique",\
            "A passionate Latino lover",\
            "A pinata full of scorpions",\
            "A really cool hat",\
            "A rival dojo",\
            "A robust mongoloid",\
            "A sad fat dragon with no friends",\
            "A sad handjob",\
            "A salty surprise",\
            "A sassy black woman",\
            "A sausage festival",\
            "A sea of troubles",\
            "A slightly shittier parallel universe",\
            "A snapping turtle biting the tip of your penis",\
            "A soulful rendition of “Ol' Man River”",\
            "A squadron of moles wearing aviator goggles",\
            "A stray pube",\
            "A Super Soaker full of cat pee",\
            "A sweaty, panting leather daddy",\
            "A sweet spaceship",\
            "A thermonuclear detonation",\
            "A tiny horse",\
            "A toxic family environment",\
            "A visually arresting turtleneck",\
            "A web of lies",\
            "A windmill full of corpses",\
            "A woman scorned",\
            "A zesty breakfast burrito",\
            "Aaron Burr",\
            "Active listening",\
            "Actually taking candy from a baby",\
            "Adderall",\
            "African children",\
            "Agriculture",\
            "AIDS",\
            "Alcoholism",\
            "All of this blood",\
            "All-you-can-eat shrimp for $499",\
            "Altar boys",\
            "American Gladiators",\
            "Amputees",\
            "An army of skeletons",\
            "An asymmetric boob job",\
            "An erection that lasts more than four hours",\
            "An ether-soaked rag",\
            "An honest cop with nothing left to lose",\
            "An icepick lobotomy",\
            "An M Night Shyamalan plot twist",\
            "An Oedipus complex",\
            "An unhinged ferris wheel rolling toward the sea",\
            "Anal beads",\
            "Another goddamn vampire movie",\
            "Another shitty year",\
            "Another shop of morphine",\
            "Apologizing",\
            "Appreciative snapping",\
            "Arnold Schwarzenegger",\
            "Asians who aren't good at math",\
            "Assless chaps",\
            "Attitude",\
            "Auschwitz",\
            "Authentic Mexican cuisine",\
            "Autocannibalism",\
            "AXE body spray",\
            "Balls",\
            "Barack Obama",\
            "Basic human decency",\
            "BATMAN!!!",\
            "Beating your wives",\
            "Beefin' over turf",\
            "Bees?",\
            "Being a bust adult with many important things to do",\
            "Being a dick to children",\
            "Being a dinosaur",\
            "Being a motherfucking sorcerer",\
            "Being awesome at sex",\
            "Being fabulous",\
            "Being marginalized",\
            "Being on fire",\
            "Being rich",\
            "Bill Nye the Science Guy",\
            "Bingeing and purging",\
            "Bitches",\
            "Black people",\
            "Bling",\
            "Booby-trapping the house to foil burglars",\
            "Boogers",\
            "Boris the Soviet Love Hammer",\
            "Bosnian chicken farmers",\
            "Breaking out into song and dance",\
            "Britney Spears at 55",\
            "Bullshit",\
            "Cards Against Humanity",\
            "Carnies",\
            "Catapults",\
            "Catastrophic Urethral Trauma",\
            "Centaurs",\
            "Chainsaws for hands",\
            "Charisma",\
            "Cheating in the Special Olympics",\
            "Child abuse",\
            "Child beauty pageants",\
            "Children on leashes",\
            "Chivalry",\
            "Christopher Walken",\
            "Civilian casualties",\
            "Clams",\
            "Classist Undertones",\
            "Clearing a bloody path through Walmart with a scimitar",\
            "Coat hanger abortions",\
            "Cockfights",\
            "College",\
            "Concealing a boner",\
            "Consultants",\
            "Copping a feel",\
            "Coughing into a vagina",\
            "Count Chocula",\
            "Crippling debt",\
            "Crystal meth",\
            "Cuddling",\
            "Customer service representatives",\
            "Cybernetic enhancements",\
            "Daddy issues",\
            "Daddy's belt",\
            "Dancing with a broom",\
            "Darth Vader",\
            "Date rape",\
            "Dead babies",\
            "Dead parents",\
            "Death by Steven Seagal",\
            "Deflowering the princess",\
            "Dental dams",\
            "Dick Cheney",\
            "Dick fingers",\
            "Dining with cardboard cutouts of the cast of “Friends”",\
            "Doin' it in the butt",\
            "Doing the right thing",\
            "Domino's Oreo Dessert Pizza",\
            "Dorito breath",\
            "Double penetration",\
            "Drinking alone",\
            "Dropping a chandelier on your enemies and riding the rope up",\
            "Dry heaving",\
            "Dwarf tossing",\
            "Dying of dysentery",\
            "Dying",\
            "Eating all of the cookies before the AIDS bake-sale",\
            "Eating an albino",\
            "Eating an entire snowman",\
            "Eating the last known Bison",\
            "Edible underpants",\
            "Elderly Japanese men",\
            "Elf cum",\
            "Embryonic stem cells",\
            "Emotions",\
            "Enormous Scandinavian women",\
            "Erectile dysfunction",\
            "Estrogen",\
            "Ethnic cleansing",\
            "Eugenics",\
            "Euphoria by Calvin Klein",\
            "Exactly what you'd expect",\
            "Exchanging pleasantries",\
            "Existing",\
            "Expecting a burp and vomiting on the floor",\
            "Explosions",\
            "Fabricating statistics",\
            "Famine",\
            "Fancy Feast",\
            "Farting and walking away",\
            "Fear itself",\
            "Feeding Rosie O'Donnell",\
            "Fetal alcohol syndrome",\
            "Fiery poops",\
            "Figgy pudding",\
            "Finding a skeleton",\
            "Finding Waldo",\
            "Finger painting",\
            "Fingering",\
            "Firing a rifle into the air while balls deep in a squealing hog",\
            "Five-Dollar Footlongs",\
            "Flash flooding",\
            "Flesh-eating bacteria",\
            "Flightless birds",\
            "Flying sex snakes",\
            "Foreskin",\
            "Forgetting the Alamo",\
            "Former President George W Bush",\
            "Free samples",\
            "Friction",\
            "Friendly fire",\
            "Friends who eat all the snacks",\
            "Friends with benefits",\
            "Frolicking",\
            "Fuck Mountain",\
            "Fucking up “Silent Night” in front of 300 parents",\
            "Full frontal nudity",\
            "Gandalf",\
            "Geese",\
            "Genetically engineered super-soldiers",\
            "Genghis Khan",\
            "Genital piercings",\
            "George Clooney's musk",\
            "German dungeon porn",\
            "Getting abducted by Peter Pan",\
            "Getting drunk on mouthwash",\
            "Getting hilariously gang-banged by the Blue Man Group",\
            "Getting in her pants, politely",\
            "Getting naked and watching Nickelodeon",\
            "Getting really high",\
            "Getting so angry that you pop a boner",\
            "Ghandi",\
            "Ghosts",\
            "Gift-wrapping a live hamster",\
            "Giving 110%",\
            "Gladitorial combat",\
            "Glenn Beck being harried by a swarm of buzzards",\
            "Glenn Beck catching his scrotum on a curtain hook",\
            "Glenn Beck convulsively vomiting as a brood of crab spiders hatches in his brain and erupts from his tear ducts",\
            "Global warming",\
            "Gloryholes",\
            "Goats eating cans",\
            "Goblins",\
            "God",\
            "GoGurt",\
            "Golden showers",\
            "Good grammar",\
            "Grandma",\
            "Grandpa's ashes",\
            "Graphic violence, adult language and some sexual content",\
            "Grave robbing",\
            "Guys who don't call",\
            "Half-assed foreplay",\
            "Harry Potter erotica",\
            "Heartwarming orphans",\
            "Her Royal Highness, Queen Elizabeth II",\
            "Heteronormativity",\
            "Hillary Clinton's death stare",\
            "Hipsters",\
            "Historical revisionism",\
            "Historically black colleges",\
            "Home video of Oprah sobbing into a Lean Cuisine",\
            "Homeless people",\
            "Hope",\
            "Hormone injections",\
            "Horrifying laser hair removal accidents",\
            "Horse meat",\
            "Hot Cheese",\
            "Hot people",\
            "Hot Pockets",\
            "Hulk Hogan",\
            "Hurricane Katrina",\
            "Immaculate conception",\
            "Inappropriate yodeling",\
            "Incest",\
            "Insatiable bloodlust",\
            "Intelligent design",\
            "Intimacy problems",\
            "Italians",\
            "Jafar",\
            "Jean-Claude Van Damme",\
            "Jeff Goldblum",\
            "Jerking off into a pool of children's tears",\
            "Jew-fros",\
            "Jewish fraternities",\
            "Jibber-jabber",\
            "John Wilkes Booth",\
            "Judge Judy",\
            "Just the tip",\
            "Justin Bieber",\
            "Kamikaze pilots",\
            "Kanye West",\
            "Keanu Reaves",\
            "Keg stands",\
            "Kids with ass cancer",\
            "Kim-Jong-il",\
            "Krampus, the Austrian Christmas Monster",\
            "Lactation",\
            "Lady Gaga",\
            "Lance Armstrong's missing testicle",\
            "Land mines",\
            "Laying an egg",\
            "Leaving an awkward voicemail",\
            "Leprosy",\
            "Leveling up",\
            "Licking things to claim them as your own",\
            "Literally eating shit",\
            "Living in a trashcan",\
            "Lockjaw",\
            "Loki, the trickster god",\
            "Loose lips",\
            "Lumberjack fantasies",\
            "Lunchables",\
            "Mad hacky-sack skills",\
            "Making a friend",\
            "Making a pouty face",\
            "Making the penises kiss",\
            "Making the penises kiss",\
            "Mall Santa",\
            "Man meat",\
            "Masturbation",\
            "Me time",\
            "Me",\
            "MechaHitler",\
            "Media coverage",\
            "Medieval Times Dinner & Tournament",\
            "Men",\
            "Menstruation",\
            "Michael Jackson",\
            "Michelle Obama's arms",\
            "Mild autism",\
            "Mooing",\
            "Moral ambiguity",\
            "Morgan Freeman's voice",\
            "Mouth herpes",\
            "Mr Clean, right behind you",\
            "Muhammad (Praise Be Unto Him)",\
            "Multiple stab wounds",\
            "Mutually-assured destruction",\
            "My collection of high-tech sex toys",\
            "My first kill",\
            "My genitals",\
            "My hot cousin",\
            "My humps",\
            "My inner demons",\
            "My machete",\
            "My relationship status",\
            "My sex life",\
            "My soul",\
            "My vagina",\
            "Natalie Portman",\
            "Natural male enhancement",\
            "Natural selection",\
            "Nazis",\
            "Necrophilia",\
            "Neil Patrick Harris",\
            "New Age music",\
            "Nickelback",\
            "Nicolas Cage",\
            "Nipple blades",\
            "Nocturnal emissions",\
            "Not giving a shit about the Third World",\
            "Not reciprocating oral sex",\
            "Nublile slave boys",\
            "Nunchuck moves",\
            "Obesity",\
            "Object permanence",\
            "Old-people smell",\
            "Ominous background music",\
            "One Ring to rule them all",\
            "One thousand Slim Jims",\
            "Oompa-Loompas",\
            "Opposable thumbs",\
            "Overcompensation",\
            "Overpowering your father",\
            "Oversized lollipops",\
            "Pabst Blue Ribbon",\
            "Pac-Man uncontrollably guzzling cum",\
            "Panda sex",\
            "Panty raids",\
            "Parting the Red Sea",\
            "Party poopers",\
            "Passable transvestites",\
            "Passing a kidney stone",\
            "Passive-aggressive Post-it notes",\
            "Pedophiles",\
            "Peeing a little bit",\
            "Penis envy",\
            "Picking up girls at the abortion clinic",\
            "Pictures of boobs",\
            "Pistol-whipping a hostage",\
            "Pixelated bukkake",\
            "Police brutality",\
            "Pooping back and forth. Forever",\
            "Poor life choices",\
            "Poor people",\
            "Poorly-timed Holocaust jokes",\
            "Porn stars",\
            "Powerful thighs",\
            "Prancing",\
            "Praying the gay away",\
            "Preteens",\
            "Pretending to be happy",\
            "Pretending to care",\
            "Pretty Pretty Princess Dress-Up Board Game",\
            "Pterodactyl eggs",\
            "Puberty",\
            "Public ridicule",\
            "Pulling out,",\
            "Pumping out a baby every nine months",\
            "Puppies!",\
            "Queefing",\
            "Quiche",\
            "Quivering jowls",\
            "Racially-biased SAT questions",\
            "Racism",\
            "Raping and pillaging",\
            "Re-gifting",\
            "Repression,",\
            "Republicans",\
            "Revenge fucking",\
            "Riding off into the sunset",\
            "Ripping into a man's chest and pulling out his still-beating heart",\
            "Rising from the grave",\
            "Road head",\
            "Robert Downey, Jr",\
            "RoboCop",\
            "Ronald Reagan",\
            "Roofies",\
            "Ryan Gosling riding in on a white horse",\
            "Same-sex ice dancing",\
            "Santa Claus",\
            "Santa's heavy sack",\
            "Sarah Palin",\
            "Saxophone solos",\
            "Scalping",\
            "Science",\
            "Scientology,",\
            "Scrotal frostbite",\
            "Scrotum tickling",\
            "Scrubbing under the folds",\
            "Sean Connery",\
            "Sean Penn",\
            "Seduction",\
            "Self-loathing",\
            "Seppuku",\
            "Serfdom",\
            "Several intertwining love stories featuring Hugh Grant",\
            "Sexting",\
            "Sexual humiliation",\
            "Sexual tension",\
            "Sexy pillow fights",\
            "Sexy siamese twins",\
            "Shaft",\
            "Shapeshifters",\
            "Shaquille O'Neal's acting career",\
            "Sharing needles",\
            "Skeletor",\
            "Slow motion",\
            "Smallpox blankets",\
            "Smegma",\
            "Sniffing glue",\
            "Socks",\
            "Soiling oneself",\
            "Some really fucked-up shit",\
            "Soup that is too hot",\
            "Space Jam on VHS",\
            "Space muffins",\
            "Special musical guest, Cher",\
            "Spectacular abs",\
            "Sperm whales",\
            "Spontaneous human combustion",\
            "Spring break!",\
            "Statistically validated stereotypes",\
            "Stephen Hawking talking dirty",\
            "Stifling a giggle at the mention of Hutus and Tutsis",\
            "Stranger danger",\
            "Subduing a grizzly bear and making her your wife",\
            "Sudden Poop Explosion Disease",\
            "Suicidal thoughts",\
            "Sunshine and rainbows",\
            "Surprise sex!",\
            "Survivor's guilt",\
            "Sweet, sweet vengeance",\
            "Swiftly achieving orgasm",\
            "Switching to Geico",\
            "Swooping",\
            "Take-backsies",\
            "Taking a man's eyes and balls out and putting his eyes where his balls go and then his balls in the eye holes",\
            "Taking down Santa with a surface-to-air missiles",\
            "Taking off your shirt",\
            "Tangled Slinkys",\
            "Tasteful sideboob",\
            "Teaching a robot to love",\
            "Team-building exercises",\
            "Teenage pregnancy",\
            "Tentacle porn",\
            "Testicular torsion",\
            "That thing that electrocutes your abs",\
            "The American Dream",\
            "The Big Bang",\
            "The Blood of Christ",\
            "The boners of the elderly",\
            "The Care Bear Stare",\
            "The Chinese gymnastics team",\
            "The chronic",\
            "The clitoris",\
            "The corporations",\
            "The Dance of the Sugar Plum Fairy",\
            "The day the birds attacked",\
            "The Donald Trump Seal of Approval",\
            "The economy",\
            "The Fanta girls",\
            "The folly of man",\
            "The forbidden fruit",\
            "The Force",\
            "The four arms of Vishnu",\
            "The gays",\
            "The glass ceiling",\
            "The Google",\
            "The grey nutrient broth that sustains Mitt Romney",\
            "The Gulags",\
            "The Hamburglar",\
            "The hardworking Mexican",\
            "The harsh light of day",\
            "The heart of a child",\
            "The hiccups",\
            "The Holy Bible",\
            "The homosexual agenda",\
            "The human body",\
            "The Hustle",\
            "The inevitable heat death of the universe",\
            "The invisible hand",\
            "The Jews",\
            "The KKK",\
            "The Kool-Aid Man",\
            "The Little Engine That Could",\
            "The Make-A-Wish foundation",\
            "The mere concept of Applebee's",\
            "The milk man",\
            "The miracle of childbirth",\
            "The mixing of the races",\
            "The new Radiohead album",\
            "The placenta",\
            "The Pope",\
            "The profoundly handicapped",\
            "The Rapture",\
            "The Rev Dr Martin Luther King, Jr",\
            "The shambling corpse of Larry King",\
            "The South",\
            "The Star Wars Holiday Special",\
            "The taint; the grundle; the fleshy fun-bridge",\
            "The Tempur-Pedic Swedish Sleep System",\
            "The terrorists",\
            "The Three-Fifths Compromise",\
            "The tiny calloused hands of the Chinese  children that made this card",\
            "The token minority",\
            "The Trail of Tears",\
            "The true meaning of Christmas",\
            "The Ubermensch",\
            "The underground railroad",\
            "The violation of our most basic human rights",\
            "The Virginia Tech Massacre",\
            "The World of Warcraft",\
            "Third base",\
            "Tiny nipples",\
            "Tom Cruise",\
            "Tongue",\
            "Toni Morrison's vagina",\
            "Too much hair gel",\
            "Tripping balls",\
            "Two midgets shitting into a bucket",\
            "Unfathomable stupidity",\
            "Upgrading homeless people to mobile hotspots",\
            "Uppercuts",\
            "Vehicular manslaughter",\
            "Viagra",\
            "Vigilante justice",\
            "Vigorous jazz hands",\
            "Vikings",\
            "Waiting 'til marriage",\
            "Waking up half-naked in a Denny's parking lot",\
            "Waterboarding",\
            "Weapons-grade plutonium",\
            "Wearing an octopus for a hat",\
            "Wearing underwear inside-out to avoid doing laundry",\
            "Whatever Kwanzaa is supposed to be about",\
            "When you fart and a little bit comes out",\
            "Whining like a little bitch",\
            "Whipping a disobedient slave",\
            "Whipping it out",\
            "White people",\
            "White privilege",\
            "Wifely duties",\
            "William Shatner",\
            "Winking at old people",\
            "Wiping her butt",\
            "Women in yogurt commercials",\
            "Women's suffrage",\
            "Words, words, words",\
            "World peace",\
            "Yeast",\
            "YOU MUST CONSTRUCT ADDITIONAL PYLONS",\
            "Zeus's sexual appetites"\
        ])

class CartaNegraIngles(CartaNegra): # ProductoB2
    def __init__(self):
        self.textos = choice([ \
            ["How did I lose my virginity? ", None], \
            ["Why can't I sleep at night? ", None], \
            ["What's that smell? ", None], \
            ["I got 99 problems but ", None, " ain't one"], \
            ["Maybe she's bon with it. Maybe it's ", None], \
            ["What's the next Happy Meal you? ", None], \
            ["Here is the church. Here is the steeple. Open the doors and there is ", None], \
            ["It's a pity that kids these days are all getting involved with ", None], \
            ["Today on Maury: Help! My son is ", None, "!"], \
            ["Alternative medicine is now embracing the curative powers of ", None], \
            ["And the Academy Award for ", None, " goes to ", None], \
            ["What's that sound? ", None], \
            ["What ended my last relationship? ", None], \
            ["MTV's new reality show features eight washed-up celebrities living with ", None], \
            ["I drink to forget ", None], \
            ["I'm sorry Professor, but I couldn't complete my homework because of ", None] \
        ])
