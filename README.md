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

> A -> F | F H A

> A -> G | G H A

> A -> B | B H A

> A -> (A) | (A) H A


## Pasos para ejecutar el código

