# Syntax Highlighter
## Equipo 2: Implementación de métodos computacionales

## Integrantes
* Eduardo Jair Hernández Gómez A01412492
* Axel Gael Uzeta Gómez A00829417
* José Andrés Lozano Alanís A01284569

## Gramática del analizador

> S -> B C A D  | B C A D E

> B -> Variable

> C -> Asignación (=)

> D -> Puntuación (;)

> E -> Comentario (//)

> F -> Entero

> G -> Real

> H -> + | - | / | * | ^ 

> I -> Parentésis que abre

> J -> Parentésis que cierra

> A -> F | F H A

> A -> G | G H A

> A -> B | B H A

> A -> I A J | I A J H A


## Pasos para ejecutar el código
El proceso para ejecutar el codigo de manera correcta es primeramente 
tener todos los archivos necesarios para el correcto funcionamiento, los cuales son nuestro main "DFA.cpp"
y nuestra estructura DFA.h para nuestros casos de prueba utilizaremos "test.txt" en caso de que se queiran probar
mas casos de prueba se deberan anadir a este txt y correr el codigo, otros documentos necesarios son
nuestro styles.css, index.html, que abriran la pagina donde ya se veran resaltados en distintos colores nuestras pruebas
marcando de color rojo las incorrectas y de disitinto colores segun el tipo de dato las correctas,
para nuestras pruebas unitarias es necesario "unittesting.cpp" y "catch.hpp" para nuestras pruebas unitarias
definimos nuestras funciones a probar les pasamos distintos parametros correspondientes a los datos que utilizamos,
pedimos que nos devuelvan true en caso de que sea correcto y false por el contrario.
