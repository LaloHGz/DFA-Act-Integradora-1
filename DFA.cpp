/*
Equipo 2 Métodos computacionales
Eduardo Jair Hernández Gómez A01412492
Axel Gael Uzeta Gómez A00829417
José Andrés Lozano Alanís A01284569
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include "DFA.h"
using namespace std;

int main()
{
    vector<DFA> dfa;
    ifstream fileIn("test.txt");
    string line;
    string word;
    string token = "", tipo = "";
    int count = 0;
    // Recorremos las lineas del archivo test.txt
    while (getline(fileIn,line)) { 
        // Guardamos los datos del archivo en su respectiva variable de acuerdo al orden

        int len = line.length();

        char char_array[len + 1];
    
        strcpy(char_array, line.c_str());
        for (int i = 0; i < len; i++) {
            if(char_array[i] == ' '){
                DFA _dfa(token, tipo);
                dfa.push_back(_dfa);
                token = "";
                tipo = "";
            }else if (char_array[i] == '/' && char_array[i-1] == '/'){
                token = "/";
                tipo = "Comentario";
                count = i;
                for (int j = count; j < len; j++){
                    token += char_array[j];
                    if (j == len-1){
                        DFA _dfa(token, tipo);
                        dfa.push_back(_dfa);
                        token = "";
                        tipo = "";
                        i = j;
                    }
                }
            }else if (char_array[i] == '+'){
                token = "+";
                tipo = "Suma";
            }else if (char_array[i] == '*'){
                token = "*";
                tipo = "Multiplicación";
            }else if (char_array[i] == '-' && char_array[i+1] == ' ') {
                token = "-";
                tipo = "Resta";
            }else if (char_array[i] == '/' && char_array[i+1] == ' '){
                token = "/";
                tipo = "División";
            }else if (char_array[i] == '='){
                token = "=";
                tipo = "Asignación";
            }else if (char_array[i] == '^'){
                token = "^";
                tipo = "Potencia";
            }else if (char_array[i] == ';'){
                token = ";";
                tipo = "Punto y coma";
                if (i == len-1){
                    DFA _dfa(token, tipo);
                    dfa.push_back(_dfa);
                    token = "";
                    tipo = "";
                    i = len;
                }
            }else if (char_array[i] == '-' && (char_array[i+1] == '0' || char_array[i+1] == '1' || char_array[i+1] == '2'|| char_array[i+1] == '3'|| char_array[i+1] == '4'|| char_array[i+1] == '5'|| char_array[i+1] == '6'|| char_array[i+1] == '7'|| char_array[i+1] == '8'|| char_array[i+1] == '9')){
                count = i;
                tipo = "Entero";
                for (int j = count; j < len; j++){
                    if (char_array[j] == ' '){
                        i = j-1;
                        break;
                    }
                    if (char_array[j] == '.'){
                        tipo = "Real";
                    }   
                    token += char_array[j];
                    if (j == len-1){
                        DFA _dfa(token, tipo);
                        dfa.push_back(_dfa);
                        token = "";
                        tipo = "";
                        i = j;
                    }
                } 
            }else if (char_array[i] == '0' || char_array[i] == '1' || char_array[i] == '2'|| char_array[i] == '3'|| char_array[i] == '4'|| char_array[i] == '5'|| char_array[i] == '6'|| char_array[i] == '7'|| char_array[i] == '8'|| char_array[i] == '9'){
                tipo = "Entero";
                count = i;
                for (int j = count; j < len; j++){
                    if (char_array[j] == ' '){
                        i = j-1;
                        break;
                    }
                    token += char_array[j];
                    if (char_array[j] == '.'){
                        tipo = "Real";
                    }   
                    if (j == len-1){
                        DFA _dfa(token, tipo);
                        dfa.push_back(_dfa);
                        token = "";
                        tipo = "";
                        i = j;
                    }
                } 
            }else if (char_array[i] == 'a'|| char_array[i] == 'b'|| char_array[i] == 'c'|| char_array[i] == 'd'|| char_array[i] == 'e'|| char_array[i] == 'f'|| char_array[i] == 'g'|| char_array[i] == 'h'|| char_array[i] == 'i'|| char_array[i] == 'j'|| char_array[i] == 'k'|| char_array[i] == 'l'|| char_array[i] == 'm'|| char_array[i] == 'n'|| char_array[i] == 'o'|| char_array[i] == 'p'|| char_array[i] == 'q'|| char_array[i] == 'r'|| char_array[i] == 's'|| char_array[i] == 't'|| char_array[i] == 'u'|| char_array[i] == 'v'|| char_array[i] == 'w'|| char_array[i] == 'x'|| char_array[i] == 'y'|| char_array[i] == 'z' || char_array[i+1] == '_'){
                count = i;
                for (int j = count; j < len; j++){
                    if (char_array[j] == ' '){
                        i = j-1;
                        break;
                    }
                    token += char_array[j];
                    if (j == len-1){
                        DFA _dfa(token, tipo);
                        dfa.push_back(_dfa);
                        token = "";
                        tipo = "";
                        i = j;
                    }
                }
                tipo = "Variable";
            }else if (char_array[i] == '('){
                token = "(";
                tipo = "Paréntesis que abre";
            }else if (char_array[i] == ')'){
                token = ")";
                tipo = "Paréntesis que cierra";
            }
        }

    }

    //Imprimimos el vector
    for (int i = 0; i < dfa.size(); i++) {
        cout<<dfa[i].print()<<endl;
    }


    // Actividad Integradora 1
    // Utilizamos la salida del analizador lexico (dfa) para generar la entrada para el analizador sintactico

    // S -> B C A D  | B C A D E
    // B -> Variable
    // C -> Asignación (=)
    // D -> Puntuación (;)
    // E -> Comentario (//)
    // F -> Entero
    // G -> Real
    // H -> + | - | / | * | ^ 
    // A -> F | F H A
    // A -> G | G H A
    // A -> B | B H A
    // A -> (A) | (A) H A

    
    return 0;
}
