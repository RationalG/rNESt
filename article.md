Emulateur NES : Comment émuler le CPU de la NES
===================

**Author : *Simon Lopez***
**Source code : **  http://github.com/RationalG/rNESt

En informatique, un émulateur est un programme visant à imiter le comportement d'un système informatique. Tout ce qui possède un micro-processeur peut être émulé. Dans le domaine des consoles, écrire un émulateur consistera donc à reproduire le comportement des composants d'un système selon une architecture bien précise, qui peut radicalement varier d'un système à un autre.

L'écriture d'un tel programme peut s'averer difficile. Le nombre de facteurs sur lesquelles cette difficulté dépend serait trop longue à lister ici, mais dans les grandes lignes, une architecture simple sur laquelle il est aisé de trouver des ressources est souhaitable pour celui qui veut se lançer pour la première fois dans un projet d'émulation.

Heuresement pour nous, la NES remplit ces critères à merveille. Aussi étonnant que cela puisse paraître, il existe aujourd'hui encore une large communauté de developpeurs autour des consoles Nintendo. Ces derniers ne produisent pas seulement de nouveaux émulateurs, mais ils developpent également des jeux, des debuggers, des filtres visuels, des programmes pour modifier le contenu des ROMS, etc...Il est même possible de trouver des documents ou des programmes capables de décrire les composants de la NES au circuit près.

Certains systèmes obscurs en revanche, comme celui de la SEGA Saturn, sont réputés pour être très difficile à émuler. A l'époque, les conditions de developpement imposées par ce genre de console étaient épouvantables, et bien souvent à cause de leur échec commercial, trouver des ressources officielles et confirmées comme étant de qualité se présente déjà immediatement comme une contrainte. Même dans les cas où l'émulateur parvient à fonctionner, les performances peuvent frôler le désastre selon le jeu qui est émulé.

Le but de cet article est d'expliquer de façon courte et simplifiée le fonctionnement interne du CPU de la NES et d'apprendre comment reproduire ce fonctionnement. Néanmoins, certaines notions doivent être acquises avant de pouvoir appréhender un tel sujet :
- les systèmes de numérations binaire et hexadécimal
- les unités (bits, bytes...)
- les opérateurs bit à bit (**SHL**, **SHR**, **XOR**, **OR**, **AND**, **NOT**)
- etc...

Maîtriser l'assembleur n'est pas du tout strictement obligatoire, mais en connaître les bases est important. Car même si on choisit un language de haut-niveau pour ce projet, l'écriture du code s'opère toujours d'un point de vue de bas niveau.
Heuresement, la plupart de ces notions peuvent s'apprendre sur le tas, et cet article expliquera en détail chacune de ces notions au fur et à mesure.

> **Note:**

> -  les exemples incluent plusieurs langages. L'assembleur 6502 est utilisé pour exprimer le point de vue du programmeur lorsqu'il écrit du code destiné à être executé sur le micro-processeur de la NES. Le code en C/C++ est choisi lorsqu'il permet de montrer un exemple concret compréhensible par la majorité des lecteurs. Le reste des exemples est écrit en Nim, car il est plus aisé pour moi en général d'illustrer des parties du code que j'ai écrit pour ce projet. Néanmoins j'en remanierai une grande partie afin de ne pas rendre le tout superflu. Ce projet est toujours en développement, le code source original et entier peut être retrouvé sur mon Github : http://github.com/RationalG/rNESt
> - Si vous voulez en savoir plus sur Nim, rendez vous sur http://nim-lang.org


----------


Le CPU de la NES et son fonctionnement
-------------
![enter image description here](https://scr.sad.supinfo.com/articles/resources/150436/340/1.png)
Pour la petite histoire, Ricoh à travaillé main dans la main avec Nintendo pour manufacturer ce micro-processeur. Il s'agit du Ricoh A203 pour la version NTSC et du Ricoh A207 pour la version PAL. Ils se sont basé sur le MOS 6502, qui fut très connu à l'époque pour être le micro-processeur utilisé par la Commodore 64.

Le fonctionnement du CPU peut s'expliquer de manière simple : lorsque l'utilisateur ajoute une **ROM** en entrée, l'émulateur charge le programme en mémoire, le CPU se place à l'endroit indiqué par le programme pour trouver le point d'entrée, et se met à interprêter les **opcodes** du programme pour savoir quelle instruction executer et poursuit sa route.
Qu'est ce qu'une **ROM** ? Le terme ROM désigne une mémoire morte dans laquelle est stocké le programme destiné à être chargé. Le code est habituellement écrit en assembleur (il est aussi possible d'écrire un jeu NES en C), puis une fois assemblé, le contenu est écrit sur la cartouche. Aujourd'hui, ces ROMs sont représentées sous la forme de simples fichiers dont le format est standardisé. Nous nous inquiéterons que du format .NES dans cet article.

Une fois la ROM parsée, le code est stocké dans un tableau représentant notre **mémoire**. Le CPU dispose d'un bus d'adresse de la taille de 16-bit, la plage d'adressage disponible possède donc une étendue de 65536 octets. La deuxième moitié de cet étendue représente la region reservée au programme NES. Celui-ci etant divisé en pages de 16384 octets, seulement deux pages maximum sont autorisées à être chargées en mémoire. Note : il est possible que la ROM contienne plus de deux pages de programme, nous verrons alors qu'il faudra parfois intervertir une page entre la ROM et la mémoire pendant l'éxécution.

Le bus d'adresse est aussi le composant qui sert d'interface entre le CPU et les autres micro-processeurs de la NES (**PPU*, APU***). Mais en ce qui concerne le code du jeu chargé en mémoire, c'est à partir de là que le CPU devra lire, octet par octet, les opcodes et les données du programme à interprêter.

Qu'est ce qu'un **opcode** ? Le terme complet se designe par "**Operation code**", ou code d'opération : il s'agit d'une représentation symbolique d'une instruction. En assembleur par exemple, le simple fait de vouloir stocker une valeur dans un registre peut s'effectuer par l'instruction LDA. Dans l'example suivant, le code charge la valeur 255 ($FF en hexadécimal) dans le registre A du CPU :

```
LDA #$FF
```

Une fois le code assemblé, la ligne se retrouve sur cette forme :

```
A9 FF
```

Ici, la ligne est composée de deux bytes : le premier byte représente l'opcode et le deuxième représente l'opérande correspondant. A9 n'est rien d'autre que l'opcode correspondant à LDA.
Il faudra par conséquent établir une matrice, permettant au CPU de faire la correspondance entre l'opcode et l'instruction à executer. Le 6502 possède un jeu de 56 instructions qui sera détaillé plus tard. Nous verrons cependant que ces instructions pourront être utilisées via plusieurs **modes d'addressage (expliqués plus tard)**. C'est d'ailleurs le cas de l'instruction LDA, illustrée dans l'exemple précédent.
Après avoir brièvement parlé de ce qui nous attends une fois que nous aurons de quoi commencer l'émulation du CPU, nous allons expliquer comment parser une ROM et la charger dans la mémoire de la NES.

Parsage et chargement d'une ROM
-------------

Comme dit précédemment, un émulateur charge la ROM d'un jeu qui se trouve sous la forme d'un fichier. Nous avions également parlé de format standardisé.
A l'époque, lors des débuts de l'émulation NES, le dump des cartouches vers les fichiers s'effectuaient sans conventions, ce qui rendait très difficile le parsage des ROM, car l'émulateur devait s'adapter selon le jeu donné en entrée. Ce n'est plus le cas aujourd'hui, une ROM doit être formatée selon un champ de règles précis pour pouvoir être émulée.
Le format standard se divise en deux versions : le format iNES et le format NES 2.0, plus récent et plus avancé. Nous nous interesseront au premier format dans cet article pour l'exemple de ROM que nous allons illustrer.
De ce fait : comment est formatée une ROM ? Quelle données doit-être prises en compte avant de pouvoir charger le programme à l'intérieur ?
Avant de pouvoir charger quoi que ce soit en mémoire, il nous faut des informations sur la ROM en question. Ces informations sont placées à l'interieur de la ROM, au tout début du fichier. Elles représentent l'en-tête de la ROM.L'en-tête mesure toujours 16 bytes.
Petit rappel sur les unités : un byte représente 8 bits (2 caractères). Dans l'exemple suivant, la ligne est découpé en part de 2 bytes: il y a donc 16 bytes, soit 32 caractères représenté sur l'image.
Regardons par exemple l'en-tete d'une ROM de Mario Bros (n'oubliez pas que les données sont représentées sous la forme héxadécimale !) :

![](https://scr.sad.supinfo.com/articles/resources/150436/340/2.png)

- Le **quatres premiers** bytes (4e45 sur l'image) valident le format iNES. Ils doivent obligatoirement représenter la chaine suivante : "NES->" . "4e" représente "N", "45" représente "E", "53" représente "S" et "1a" représente "->".Sans cette représentation exacte, une ROM ne peut être conforme aux conventions iNES et doit être rejetée par l'emulateur.
- Le **cinquième** byte (02 sur l'image) représente le nombre de pages qui contiennent le programme (PRG-ROM). Ces pages sont situées **juste après l'en-tête de la ROM**. Comme dit dans le chapitre précédent, une page mesure 16384 octets, et la region de la mémoire reservée au programme NES ne peut en contenir que 32768. Heuresement pour nous, Mario Bros contient 2 pages de programme, nous pourrons alors charger l'intégralité du programme en mémoire.
- Le **sixième** byte (01 sur l'image) correspond au nombre de pages CHR (CHR-ROM). Il s'agit de la banque de tiles, qui représenteront les graphismes à l'écran. Celle-ci sera chargé au sein du PPU, qui est le processeur graphique de la NES.
- Le **septième** byte (01 sur l'image) est un peu particulier : il doit être découpé en deux paires de 4 bits. La première paire correspond au numéro du **mapper**. La seconde paire correspond à un type de **mirroring** (horizontal ou vertical).


----------


6502 : registres
-------------------

Avant de partir plus en détail sur les instructions du 6502, il convient de parler des acteurs principaux du CPU : les registres.
Le 6502 permet de travailler avec les registres suivants :

>- **L'Accumulateur** (dit registre 'A') : celui-ci est utilisé pour les opérations arithmétiques et logiques. Cependant il n'existe aucune instruction permettant d'effectuer une incrémentation ou une décrémentation sur la valeur contenue dans le registre. Il s'agit d'un registre 8-bit.
>- **Le registre d'index X** (dit registre 'X') : comme tout les registres d'index, il est utilisé comme compteur pour gérer les boucles et est également designé pour contenir les offsets lors des calculs d'adresse mémoire. Ce registre a une particularité : il peut être utilisé pour conserver la valeur du stack pointer ou changer la valeur de ce dernier. Le 6502 possède deux instructions qui permettent aux programmeurs d'incrementer ou de décrementer la valeur affectée a ce registre. Il s'agit également d'un registre 8-bit.
>- **Le registre d'index Y** (dit registre 'Y') : Similaire au registre X, mise à part qu'il ne possède aucune particularité.
>- Le **pointeur d'instruction** ou **Program Counter** en anglais (dit registre "PC") : il s'agit d'un registre 16-bit contenant l'adresse de la prochaine instruction à être executée. Sa valeur change à chaque instruction executée. Ce changement dépend non seulement de l'instruction executée en cours, mais aussi du mode d'adressage employé.
>- Le **pointeur de pile** ou **Stack Pointer** en anglais (dit registre "SP") : il s'agit d'un registre 8-bit contenant les 8 bits de poids faible de l'adresse pointant vers la prochaine region libre au dessus de la pile. La pile est située dans une région de la mémoire, précisément à l'étendue 0100->01FF . L'utilisateur peut y empiler et y dépiler des valeurs. Elle est également utilisée pour gerer les adresses de retour.
>- Le **registre de status** ou **Status Register** en anglais (dit registre "PS") : il s'agit encore d'un registre 8-bit, mais son utilisation est particulière. Chacun des bits correspond à un drapeau gardant trace du résultat de l'opération effectué par la dernière instruction executée. Beaucoup d'instructions testent ce registre pour vérifier des conditions avant d'éxecuter une opération.

Les bits du **registre de status** sont ordonnées de la manière suivante :

>- Bit 0 : Carry Flag : utilisé majoritairement lors des opérations
   arithmétiques
>- Bit 1 : Zero Flag : activé lorsque la dernière opération effectuée affecte zéro à un registre
>- Bit 2 : Interrupt Flag : utilisé pour empêcher le processeur de sauter vers le vecteur IRQ, situé à l'adresse $FFFE
>- Bit 3 : Decimal Flag : le processeur de la NES ne supporte pas l'utilisation du mode décimal, mais il existe 2 instructions capables de manipuler ce bit.
>- Bit 4 : Break Flag : activé seulement lors de l'appel à l'instruction BRK, qui permet au processeur de sauter vers le vecteur IRQ.
>- Bit 5 : Inutilisé et toujours mis à 1.
>- Bit 6 : Overflow flag : Si une addition ou une soustraction produit un resultat trop gros pour être contenu dans un byte, alors ce bit sera mis à 1. Sinon il sera mis à 0.
>- Bit 7 : Sign Flag (ou Negative Flag) : Si une addition ou une soustraction produit une valeur négative, alors ce bit sera mis à 1. Sinon, il sera mis à 0.

Les détails concernant l'utilisation de ces registres sera approfondie au fur et à mesure que nous parlerons des instructions.

----------

6502 : Modes d'adressage
-------------

Le 6502 offrait aux programmeurs plusieurs moyens pour spécifier une adresse mémoire. Il existe 13 modes d'adressage. C'est la raison pour laquelle il existe, pour la majorité des cas, plusieurs opcodes pour une seule instruction. Néanmoins il n'est pas possible d'utiliser n'importe quel mode avec n'importe quelle instruction. Par exemple, l'instruction SEI, qui permet d'activer l'Interrupt Flag du registre de status, n'aurait aucun intêret à pouvoir supporter plusieurs modes d'adressage. En revanche, d'autres instructions bénéficient de l'avantage de pouvoir être appelées en laissant au programmeur la liberté de spécifier une valeur 8-bit ou une adresse mémoire dont la location contient une valeur.
Nous allons passer en revue chaque mode d'adressage et expliquer comment les utiliser :
Mode Accumulator : Permet d'indiquer à l'instruction appelée d'affecter directement le registre A (L'accumulateur). Exemple :

    ASL A    ;Décale tout les bits de A vers la gauche
    ASL $10  ;Décale tout les bits de la valeur située à la location $0010 de la mémoire.  

L'exemple ici illustre deux modes différents dans le but de clarifier comment une instruction peut être utilisée de plusieurs manières. La première ligne représente l'utilisation d'ASL en mode Accumulator tandis que la deuxième emploie le mode Immediate (expliqué juste en-dessous)
Mode Immediate : Permet de spécifier une valeur constante de 8-bit comme opérande. Exemple :

    LDA #10     ;Charge 10 dans le registre A
    EOR #32     ;Performe un OU exclusif (A = A xor 32)

EOR performe un OU exclusif sur l'accumulateur avec la valeur spécifiée. Dans cet exemple, A se retrouve avec la valeur `$2A` ( 42 )
Mode Zero Page : Permet de spécifier une adresse à l'aide d'une valeur 8-bit comme opérande. La valeur maximale d'une valeur 8-bit étant `$FF`, cela signifie entre autres que seule la region `$0000 - $00FF` de la mémoire sera adressable. Exemple :

    `LDX $FD`     ;Charge la valeur localisée à l'adresse $00FD de la mémoire dans le registre X

Il est utile de noter que Zero Page désigne la region qui se trouve juste avant la pile, située à l'étendue `$0100 -> $01FF`
Mode Zero Page, X : Similaire au mode Zero Page, à une exception près : la valeur contenue dans le registre X sera additionnée à la valeur de l'opérande spécifié. Exemple :

    LDX #$0D    ;Charge 13 dans le registre X
    LDY $F0, X  ;Charge la valeur localisée à l'adresse $00FD de la mémoire dans le registre Y

Ici, on affecte `#$0D` (13) au registre X. On souhaite récuperer la valeur située à `$00FD` pour l'affecter au registre Y. On spécifie alors `$F0`, puisque l'addition avec la valeur de X donnera l'adresse `$00FD`.
Mode Zero Page, Y : Similaire au mode Zero Page, X. Sauf que ce sera la valeur du registre Y qui sera additionnée à l'adresse spécifiée.
Mode Absolute : Permet de spécifier une adresse 16-bit comme opérande. Exemple :

    JMP $8000    ;Le processeur saute vers le début du programme NES, chargé à l'adresse $8000

Mode Absolute, X : Similaire au mode Absolute, mais tout comme le mode Zero Page, X, le processeur performe l'addition du registre X avec l'adresse spécifiée.
Mode Absolute, Y : Similaire au mode Absolute, X. Sauf que ce sera la valeur du registre Y qui sera additionnée à l'adresse spécifiée.
Mode Indirect : Permet de spécifier une adresse 16-bit comme opérande qui pointe vers une location contenant les 8 bits de poids faible d'une autre adresse. Exemple :

    JMP ($FFFC)    ;Le processeur saute vers le vecteur RESET.

A noter : seul JMP utilise ce mode. On peut considérer ce mode comme étant un double-jump, puisque le processeur sautera finalement vers l'adresse trouvée lors du jump initial.
Mode Indirect, X : Il s'opère de la même façon que le mode Indirect, mais présente les mêmes similitudes que le mode Zero Page. Il permet de specifier une valeur 8 bit et donc, par conséquent, d'adresser la region `$0000 -> $00FF` uniquement. Encore une fois, la valeur du registre X sera ajoutée à l'adresse spécifiée :


    LDX #01         ;Charge 1 dans X
    LDA ($FD, X)    ;Charge les 8 bits de poids faible de l'adresse           localisée à $00FE dans A


1 sera additionné à `$FD`, ce qui produira `$00FE` pour adresse.
Mode Indirect, Y : Similaire au mode Indirect, X. Sauf que ce sera la valeur du registre Y qui sera additionnée à l'adresse spécifiée.
Mode Implicit : Aucun opérande n'a besoin d'être spécifiée puisque l'instruction appelée évoque implicitement le ou les registres qui seront impliqués dans l'opération. Exemple :


    TXA    ;Charge la valeur du registre X dans le registre A

----------


6502 : Instructions
--------------------

Afin de simplifier les explications, nous allons employer les initiales des registres. (voir chapitre sur les registres : A, X, Y, PC, PS, SP). La ROM prise en exemple reste celle de Mario Bros
Avant de pouvoir recoder les instructions, il faut savoir ce qu'elles font, avec quels modes d'adressage peut-on les employer, et aussi prendre connaissance de leur opcode. Pour cela, il est quasi-obligatoire d'avoir une ou plusieurs références sur le 6502 :
>- *6502 Assembly Language Programming*, écrit par Lance A. Leventhal. Il s'agit de la référence absolue pour programmer sur le 6502. Ce livre permet de revisiter les concepts basiques d'un programme en assembleur mais il décrit surtout en intégralité le jeu d'instructions du 6502 ainsi que les modes d'adressage. Le livre est sorti en 1986, et reste indétrônable en tant que ressource de qualité.
>- http://nesdev.com : si le livre ne vous convient pas alors ce site devient la référence principale par défaut : l'ensemble de son contenu est entièrement écrit par la communauté regroupant les developpeurs sur NES/SNES. On y trouve un listing de documents, un forum actif ainsi qu'un wiki (très mal documenté selon mon opinion, mais il a le mérite de contenir des informations très spécifique relatif à la programmation des jeux NES)
>- http://6502.org : il s'agit ici d'un site spécialisé sur le 6502. Le lien pointe directement vers la page dediée aux opcodes.
>- Rendez visite à la version cache des pages sur les registres, opcodes et modes d'adressage d'obelisk.demon.co.uk. Ce site avait le mérite d'expliquer tout les détails importants relatif au 6502 et de mettre en forme son contenu de façon claire, sans avoir à noyer le lecteur sous un flot d informations inutiles. Il a malheureusement disparu il y a très peu de temps.
>- Et enfin, n'hésitez pas à faire vos propres recherches sur le 6502, les resources sont très nombreuses sur ce micro-processeur qui a fait succès dans le temps.

A ce stade, le problème qui se pose rapidement à nous est de pouvoir mettre en place une structure nous permettant de déclencher un appel vers une instruction dès lors que l'on reçoit un opcode en lecture. La méthode conseillée n'est pas des plus élégantes, mais un simple switch dans lequel tout les opcodes sont passés en revue est ce que font la plupart des émulateurs. Dans mon code j'ai opté pour une solution plus simple : creer une table de clés/valeurs, qui permet de déclencher l'appel a une instruction selon la clé spécifiée en index du tableau.

Dans tout les cas, cela prend beaucoup de temps. Si on veut faire les choses proprement, la combination de toutes les instructions et de tout les modes d'adressages peut être contenu dans un tableau comme celui là :

![enter image description here](https://scr.sad.supinfo.com/articles/resources/150436/340/3.png)

Le commentaire dans le code est assez explicite : on peut reconnaître l'instruction à appeler en spécifiant l'opcode récupéré en tant qu'index du tableau. Pour déclencher l'appel, on peut utiliser un tableau de ce genre :

![enter image description here](https://scr.sad.supinfo.com/articles/resources/150436/340/4.png)

L'index à spécifier pour une table de ce genre est simplement une clé correspondant à une valeur. Un exemple tout bête en Nim d'une utilisation de ces deux tables pour déclencher une fonction :

    var opcode = readMemory(nesCpu.pc)
    var operation = instructionsTable[opcode]
    procsDispatcher[operation]()


Une des contraintes en Nim pour l'emploi de ce type de structure est qu'il est impossible de mélanger les fonctions ne prenant aucun paramètre avec celles qui nécéssitent d'en spécifier. Or, seuls les instructions utilisant le mode Implicit n'utilisent pas d'opérande à spécifier. Un choix s'impose ici : soit on déclare les fonctions de façon à ce qu'elles prennent tous un paramètre, soit on utilise une variable globale pour stocker l'opérande récupéré selon le mode d'adressage employé. Il faudra dans tout les cas creer un tableau et une table exactement similaire à celles des instructions et acceder à celles ci en utilisant toujours l'opcode récupéré comme index. Il nous reste à savoir comment utiliser ces tableaux pour gérer les opérandes.
La meilleure façon de gerer opérandes est de creer une fonction pour chaque mode d'adressage. Nous pourrons y gerer la récuperation des opérandes et l'incrémentation du registre PC à chaque fois qu'une instruction est executée, afin que le CPU puisse enchaîner avec l'instruction suivante. Puisqu'un opcode utilisant le mode Implicit ne possède pas d'opérande à specifier, alors l'opcode suivant se situe juste dans la location d'après en mémoire. Par contre, un opcode utilisant le mode Absolute demande à ce qu'une adresse 16-bit soit spécifiée comme opérande, soit l'équivalent de 2 bytes. Puisque les deux cases suivant l'opcode contiennent l'adresse spécifiée en opérande, il faut faudra alors additionner 3 au registre PC pour que l'adresse contenue dans ce dernier pointe sur l'opcode suivant.
La recupération des opcodes sera expliqué un peu plus bas. Nous allons reconstituer quelques instructions.
Lorsque le programme est chargée en mémoire, le moyen sur de faire débuter le programme est d'enclencher le CPU sur le vecteur RESET. Ce vecteur contient l'adresse de la location où le programme est censé démarrer.
Il existe trois vecteurs : NMI, IRQ et RESET. Ils sont situés à la fin de la ROM. Pour cet article, les deux premiers vecteurs ne nous intéressent pas. Le vecteur RESET nous sert comme point de départ pour le CPU.
Il faut donc affecter au PC l'adresse contenu dans le vecteur RESET. N'oubliez pas que la NES ne peut acceder à la mémoire que par unité de 8-bit, cette adresse est donc étendue sur 2 bytes. Jetons un coup d'oeil à la version désassemblé de la ROM de Mario Bros :

![enter image description here](https://scr.sad.supinfo.com/articles/resources/150436/340/5.png)

Comment peut-on lire cette section du programme ? Il suffit simplement de lire les commentaires du désassembleur : le vecteur reset est situé à l'adresse `$FFFC` de la mémoire. Les 8 bits de poids faibles de l'adresse, contenu à `$FFFC`, représente 00. Les 8 bits de poids fort de l'adresse, contenu à `$FFFD`, représentent C0. Pour reconstituer l'adresse, il faudra alors recuperer les valeurs contenues à `$FFFC` et `$FFFD`, et les remettre dans l'ordre pour former `$C000`, l'adresse qui doit être affecté au PC lors de son initialisation.
Voici comment cela peut être réalisé en Nim :

    # fichier cpu.nim
    
    type
        CPUObj* = object of RootObj
            a, x, y, s, pc, ps: int
    
    proc interruptReset(): void =
        nesCpu.pc = getMemoryShortAt(0xFFFC)
    
    proc initCPU() : void =
        #on initialise le stack pointer
        nesCpu.s = 0x1FD 
        interruptReset()
    
    
    # fichier mem.nim
    
    type
        CPUMemoryObj* = object of RootObj
            bank: seq[int]
    
    #retourne les 16 bits partant de l'adresse spécifiée en paramètre
    proc getMemoryShortAt(address: int): int =
        var lowByte = cpuMemory.bank[address]
        var highByte = cpuMemory.bank[address + 1] shl 8
        return highByte or lowByte

Dans cette exemple, on part du principe que la mémoire a déjà été initialisée avec le programme chargé à l'adresse $8000.
'shl' est un opérateur bit à bit qui effectue ici un décalage vers la gauche sur les 8 bits contenu à l'adresse $FFFD.
'or' est également un opérateur bit à bit qui performe ici un OU logique sur chacun des opérandes. La fonction finit par nous renvoyer $C000.
Lorsque le PC est initialisé à cette adresse, il faut débuter l'interprétation des opcodes. Voyons voir ce qui se trouve à l'adresse $C000 de la mémoire :

![enter image description here](https://scr.sad.supinfo.com/articles/resources/150436/340/6.png)

Encore une fois, il s'agit de la version désassemblée de la ROM. Nous ne sommes pas censés savoir que l'opcode se trouvant à $C000 sera D8. Justement nous allons verifier cela par nous même en récupérant nous même l'opcode :

    # fichier cpu.nim
    
    proc update*(): void = 
        #nesCpu.pc a été initialisé a 0xC000
        var opcode = readMemory(nesCpu.pc)
        var operation = instructionsTable[opcode]
    
        echo opcode #écrit D8
        echo operation #écrit CLD
    
    
    #fichier mem.nim
    
    proc readMemory(address: int): int =
        return cpuMemory.bank[address]

Rien de sorcier jusqu'a présent. Il nous faut maintenant reconstituer l'instruction CLD et déclencher son appel. CLD veut dire Clear Decimal, elle sert à situer le bit correspondant au Decimal Flag du registre PS à 0. La majorité des jeux NES débutent par cette instruction, car de toute manière, le Ricoh A203/A207 ne supportait pas le mode décimal.
Le registre PS peut être de plusieurs façons, certains choisissent de déclarer un booléen pour chaque drapeau. Pour ma part j'ai décidé de le gerer simplement comme un int sur lequel on viendrait appliquer des opérations bit à bit. Le Decimal Flag correspond au bit N°3 du registre PS. CLD peut être constituée alors de la manière suivante :

    #fichier cpu.nim
    
    proc opCld(): void =
        nesCpu.ps = nesCpu.ps and not (1 shl 3)

Si vous regardez les références, seul le mode d'adressage Implicit est supporté par l'instruction CLD. Puisqu'aucun opérande n'est à specifier dans ce mode, le prochain opcode se trouve juste dans la location suivante, à $C001. Il convient donc d'additionner 1 au registre PC chaque fois qu'il rencontrera un opcode utilisant l'**Implicit mode**.

    # fichier cpu.nim
    
    var operand : int
    
    proc implicit(): int {.discardable.} =
        nesCpu.pc += 1
        return 0
    
    proc update*(): void = 
        #on recupere l'opcode depuis la mémoire
        var opcode = readMemory(nesCpu.pc)
        #on fait correspondre l'opcode avec l'instruction à executer
        var operation = instructionsTable[opcode]   
        #on fait correspondre l'opcode avec le mode d'adressage utilisé
        var mode = addressingModes[opcode]
    
        #selon le mode d'adressage utilisé, on récupere l'opérande si il y en a un
        operand = addressingModesDispatcher[mode]()
        #on déclenche l'appel à l'instruction
        procsDispatcher[operation]()

Regardons maintenant l'opcode suivant : 78, qui correspond à l'instruction **SEI**. Cette instruction veut dire **Set Interrupt**, elle sert a situer le bit correspondant à l'Interrupt Flag du registre PS à 1. L'Interrupt Flag correspond au bit N°2 du registre PS :

    #fichier cpu.nim
    
    proc opSei(): void =
        nesCpu.ps = nesCpu.ps or (1 shl 2)

Comme CLD, l'instruction SEI ne supporte que l'Implicit Mode. Nous ajoutons alors 1 à PC et poursuivons notre route.
AD correspond à LDA en mode Absolute, c'est à dire que l'opérande spécifiée est une adresse 16-bit. Nous allons devoir récuperer les 2 bytes suivant l'opcode pour reconstituer l'adresse et l'envoyer en paramètre à la fonction.
LDA en mode Absolute charge la valeur recupérée depuis l'adresse spécifiée pour la charger dans le registre A. Si 0 est chargé dans A, nous mettons le bit correspondant au Zero Flag du registre PS à 1, sinon à 0. Si c'est une valeur négative, nous effectuons la même opération sur le bit correspondant au Negative Flag.

    proc absolute(): int {.discardable.} =
        # on fait appel à la même méthode que l'on a utilisé pour recupérer l'adresse du vecteur RESET
        nesCpu.pc += 3
        return getMemoryShortAt(nesCpu.pc +1)
    
    
    proc opLda(): void =
         nesCpu.a = readMemory(operand)
         
         # test si zéro
         if nesCpu.a == 0 :
             nesCpu.ps = nesCpu.ps or (1 shl 1)
         else :
             nesCpu.ps = nesCpu.ps and not (1 shl 1)
    
         # test si négatif (voir nombres signés)
         if (nesCpu.a and 0x80) == 0x80 :
             nesCpu.ps = nesCpu.ps or (1 shl 7)
         else :
             nesCpu.ps = nesCpu.ps and not (1 shl 7)

Et ainsi de suite. Beaucoup d'autres paramètres sont à prendre en compte lors du contexte d'une execution d'instruction, mais le but de l'article était de donner une idée de comment les reproduire et de faire tourner un CPU jusqu'a ce qu'il puisse tourner de lui-même lorsqu'un programme est inséré en mémoire.


----------


Conclusion
--------------------

Le sujet de l'émulation est difficile à aborder dans un petit document. Il y a énormement de choses qui ont été volontairement omises dans cet article concernant le CPU et même concernant la NES en-elle même. Un vrai article complet aurait été capable d'expliquer en détail l'architecture de la NES, de parler des cycles d'executions, du PPU, de l'APU mais même une petite machine de cette époque est capable de renfermer une quantité infinie de détails à prendre en compte lorsque l'on veut l'émuler.
Le CPU et la mémoire sont les parties les plus accessibles d'un émulateur, et même avec un CPU fonctionnel à 100%, on est loin de ce qu'on appelerait un émulateur fonctionnel a 100%, car le PPU et l'APU nécéssite d'aborder des notions un peu plus complexes et qui prennent beaucoup plus de temps à mettre en place.
J'espère que cet article vous donnera la motivation de partir sur un tel projet. L'émulation est un sujet large et passionnant, et c'est bien pour cela que l'on trouve encore des developpeurs qui s'interessent à des consoles aussi anciennes que la NES.