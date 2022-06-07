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
#include <filesystem>
#include <ctime>
#include <sys/time.h>
#include <thread>
#include "DFA.h"

using namespace std;

vector<DFA> dfa;

bool B(vector<DFA> dfa, int index)
{
    if (dfa[index].tipo == "Variable")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool C(vector<DFA> dfa, int index)
{
    if (dfa[index].tipo == "Asignación")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool D(vector<DFA> dfa, int index)
{
    if (dfa[index].tipo == "Punto y coma")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool E(vector<DFA> dfa, int index)
{
    if (dfa[index].tipo == "Comentario")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool F(vector<DFA> dfa, int index)
{
    if (dfa[index].tipo == "Entero")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool G(vector<DFA> dfa, int index)
{
    if (dfa[index].tipo == "Real")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool H(vector<DFA> dfa, int index)
{
    if (dfa[index].tipo == "Suma" | dfa[index].tipo == "Multiplicación" | dfa[index].tipo == "Resta" | dfa[index].tipo == "División" | dfa[index].tipo == "Potencia")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool I(vector<DFA> dfa, int index)
{
    if (dfa[index].tipo == "Parentesis que abre")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool J(vector<DFA> dfa, int index)
{
    if (dfa[index].tipo == "Parentesis que cierra")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool A(vector<DFA> dfa, int index)
{
    bool validation = false;
    // A -> F | F H A
    if (F(dfa, index) == true)
    { // Enteros
        validation = true;
        index++;
        if (H(dfa, index) == true)
        { // Operadores
            validation = true;
            index++;
            return A(dfa, index);
        }
        return validation;
        // A -> G | G H A
    }
    else if (G(dfa, index) == true)
    { // Real
        validation = true;
        index++;
        if (H(dfa, index) == true)
        { // Operadores
            validation = true;
            index++;
            return A(dfa, index);
        }
        return validation;
        // A -> B | B H A
    }
    else if (B(dfa, index) == true)
    { // Variable
        validation = true;
        index++;
        if (H(dfa, index) == true)
        { // Operadores
            validation = true;
            index++;
            return A(dfa, index);
        }
        return validation;
        // A -> I A J | I A J H A
    }
    else if (I(dfa, index) == true)
    { // paréntesis que abre
        validation = true;
        index++;
        validation = A(dfa, index);
        if (validation == false)
        {
            return validation;
        }
        index++;
        for (int i = index; i < dfa.size(); i++)
        {
            if (J(dfa, i) == true)
            {
                index = i;
                break;
            }
        }
        validation = J(dfa, index); // paréntesis que cierra
        if (validation == false)
        {
            return validation;
        }
        index++;
        if (H(dfa, index) == true)
        { // Operadores
            validation = true;
            index++;
            return A(dfa, index);
        }
        return validation;
    }
    return validation;
}

bool S(vector<DFA> dfa, int index, int end)
{
    bool validation = true;
    validation = B(dfa, index); // Variable
    if (validation == false)
    {
        return false;
    }
    index++;
    validation = C(dfa, index); // Asignación
    if (validation == false)
    {
        return false;
    }
    index++;
    validation = A(dfa, index); // F | F H A // G | G H A  // B | B H A  // I A J | I A J H A
    if (validation == false)
    {
        return false;
    }
    if (E(dfa, end) == true)
    { // Comentario
        if (D(dfa, end - 1) == true)
        { // Punto y coma
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (D(dfa, end) == true)
    { // Punto y coma
        return true;
    }
    else
    {
        return false;
    }
}



void syntaxHighligther(string archive, string number){
    string archivo = archive;
    ifstream fileIn(archivo);
    string line;
    string token = "", tipo = "";
    int count = 0, countLine = 0;

    // Recorremos las lineas del archivo test.txt
    while (getline(fileIn, line))
    {
        // Guardamos los datos del archivo en su respectiva variable de acuerdo al orden
        countLine++;
        int len = line.length();
        char char_array[len + 1];

        strcpy(char_array, line.c_str());
        for (int i = 0; i < len; i++)
        {
            if (char_array[i] == ' ')
            {
                DFA _dfa(token, tipo);
                dfa.push_back(_dfa);
                token = "";
                tipo = "";
            }
            else if (char_array[i] == '/' && char_array[i - 1] == '/')
            {
                token = "/";
                tipo = "Comentario";
                count = i;
                for (int j = count; j < len; j++)
                {
                    token += char_array[j];
                    if (j == len - 1)
                    {
                        DFA _dfa(token, tipo);
                        dfa.push_back(_dfa);
                        token = "";
                        tipo = "";
                        i = j;
                    }
                }
            }
            else if (char_array[i] == '+')
            {
                token = "+";
                tipo = "Suma";
            }
            else if (char_array[i] == '*')
            {
                token = "*";
                tipo = "Multiplicación";
            }
            else if (char_array[i] == '-' && char_array[i + 1] == ' ')
            {
                token = "-";
                tipo = "Resta";
            }
            else if (char_array[i] == '/' && char_array[i + 1] == ' ')
            {
                token = "/";
                tipo = "División";
            }
            else if (char_array[i] == '=')
            {
                token = "=";
                tipo = "Asignación";
            }
            else if (char_array[i] == '^')
            {
                token = "^";
                tipo = "Potencia";
            }
            else if (char_array[i] == ';')
            {
                token = ";";
                tipo = "Punto y coma";
                if (i == len - 1)
                {
                    DFA _dfa(token, tipo);
                    dfa.push_back(_dfa);
                    token = "";
                    tipo = "";
                    i = len;
                }
            }
            else if (char_array[i] == '-' && (char_array[i + 1] == '0' || char_array[i + 1] == '1' || char_array[i + 1] == '2' || char_array[i + 1] == '3' || char_array[i + 1] == '4' || char_array[i + 1] == '5' || char_array[i + 1] == '6' || char_array[i + 1] == '7' || char_array[i + 1] == '8' || char_array[i + 1] == '9'))
            {
                count = i;
                tipo = "Entero";
                for (int j = count; j < len; j++)
                {
                    if (char_array[j] == ' ')
                    {
                        i = j - 1;
                        break;
                    }
                    if (char_array[j] == '.')
                    {
                        tipo = "Real";
                    }
                    token += char_array[j];
                    if (j == len - 1)
                    {
                        DFA _dfa(token, tipo);
                        dfa.push_back(_dfa);
                        token = "";
                        tipo = "";
                        i = j;
                    }
                }
            }
            else if (char_array[i] == '0' || char_array[i] == '1' || char_array[i] == '2' || char_array[i] == '3' || char_array[i] == '4' || char_array[i] == '5' || char_array[i] == '6' || char_array[i] == '7' || char_array[i] == '8' || char_array[i] == '9')
            {
                tipo = "Entero";
                count = i;
                for (int j = count; j < len; j++)
                {
                    if (char_array[j] == ' ')
                    {
                        i = j - 1;
                        break;
                    }
                    token += char_array[j];
                    if (char_array[j] == '.')
                    {
                        tipo = "Real";
                    }
                    if (j == len - 1)
                    {
                        DFA _dfa(token, tipo);
                        dfa.push_back(_dfa);
                        token = "";
                        tipo = "";
                        i = j;
                    }
                }
            }
            else if (char_array[i] == 'a' || char_array[i] == 'b' || char_array[i] == 'c' || char_array[i] == 'd' || char_array[i] == 'e' || char_array[i] == 'f' || char_array[i] == 'g' || char_array[i] == 'h' || char_array[i] == 'i' || char_array[i] == 'j' || char_array[i] == 'k' || char_array[i] == 'l' || char_array[i] == 'm' || char_array[i] == 'n' || char_array[i] == 'o' || char_array[i] == 'p' || char_array[i] == 'q' || char_array[i] == 'r' || char_array[i] == 's' || char_array[i] == 't' || char_array[i] == 'u' || char_array[i] == 'v' || char_array[i] == 'w' || char_array[i] == 'x' || char_array[i] == 'y' || char_array[i] == 'z' || char_array[i + 1] == '_')
            {
                count = i;
                for (int j = count; j < len; j++)
                {
                    if (char_array[j] == ' ')
                    {
                        i = j - 1;
                        break;
                    }
                    token += char_array[j];
                    if (j == len - 1)
                    {
                        DFA _dfa(token, tipo);
                        dfa.push_back(_dfa);
                        token = "";
                        tipo = "";
                        i = j;
                    }
                }
                tipo = "Variable";
            }
            else if (char_array[i] == '(')
            {
                token = "(";
                tipo = "Parentesis que abre";
            }
            else if (char_array[i] == ')')
            {
                token = ")";
                tipo = "Parentesis que cierra";
            }
        }
    }

    // Actividad Integradora 1
    // Utilizamos la salida del analizador lexico (dfa) para generar la entrada para el analizador sintactico
    bool validacion[countLine];
    int matrizGuardado[countLine][2]; // matriz de cantidad de lineas a revisar por el indice inicial y final de la linea

    // Guardar el inicio y fin de cada línea del test
    int aux = 0, bandera = 0;
    for (int i = 0; i < dfa.size(); i++)
    {
        if (bandera == 0)
        {
            matrizGuardado[aux][0] = i;
            bandera = 1;
        }
        if (dfa[i].tipo == "Comentario")
        {
            matrizGuardado[aux][1] = i;
            aux++;
            bandera = 0;
        }
        else if (dfa[i].tipo == "Punto y coma" && dfa[i + 1].tipo != "Comentario")
        {
            matrizGuardado[aux][1] = i;
            aux++;
            bandera = 0;
        }
    }

    for (int i = 0; i < countLine; i++)
    {
        validacion[i] = S(dfa, matrizGuardado[i][0], matrizGuardado[i][1]);
    }

    for (int i = 0; i < countLine; i++)
    {
        cout << i + 1 << ". " << validacion[i] << endl;
    }

    ofstream file;
    file.open("results/archive"+number+".html");
    file<< "<!DOCTYPE html>\n";
    file<< "<html lang=\"es\">\n<head>";
    file<< "<meta charset=\"UTF-8\">\n";
    file<< "<title>Document</title>\n";
    file<< "<link rel=\"stylesheet\" href=\"styles.css\">\n";
    file<< "</head>\n";
    file<< "<body>\n";

    for (int i = 0; i < countLine; i++)
    {
        if (validacion[i] == false)
        {
            file << "<span class=\"wrong\">";
            for (int j = matrizGuardado[i][0]; j <= matrizGuardado[i][1]; j++)
            {
                file << dfa[j].token << " ";
            }
            file << "</span>";
            file << "<br>";
        }
        else
        {
            for (int j = matrizGuardado[i][0]; j <= matrizGuardado[i][1]; j++)
            {
                if (dfa[j].tipo == "Variable"){
                    file << "<span class=\"variable\">";
                    file << dfa[j].token << " ";
                    file << "</span>";
                }else if (dfa[j].tipo == "Asignación"){
                    file << "<span class=\"asignacion\">";
                    file << dfa[j].token << " ";
                    file << "</span>";
                }else if (dfa[j].tipo == "Punto y coma"){
                    file << "<span class=\"puntuacion\">";
                    file << dfa[j].token << " ";
                    file << "</span>";
                }else if (dfa[j].tipo == "Comentario"){
                    file << "<span class=\"comentario\">";
                    file << dfa[j].token << " ";
                    file << "</span>";
                }else if (dfa[j].tipo == "Entero"){
                    file << "<span class=\"entero\">";
                    file << dfa[j].token << " ";
                    file << "</span>";
                }else if (dfa[j].tipo == "Real"){
                    file << "<span class=\"real\">";
                    file << dfa[j].token << " ";
                    file << "</span>";
                }else if (dfa[j].tipo == "Suma" | dfa[j].tipo == "Multiplicación" | dfa[j].tipo == "Resta" | dfa[j].tipo == "División" | dfa[j].tipo == "Potencia"){
                    file << "<span class=\"operador\">";
                    file << dfa[j].token << " ";
                    file << "</span>";
                }else if (dfa[j].tipo == "Parentesis que abre" | dfa[j].tipo == "Parentesis que cierra"){
                    file << "<span class=\"parentesis\">";
                    file << dfa[j].token << " ";
                    file << "</span>";
                }
            }
            file << "<br>";
        }
    }

    file << "\n</body>\n";
    file << "</html>\n";

    file.close();

    // S -> B C A D  | B C A D E
    // B -> Variable
    // C -> Asignación (=)
    // D -> Puntuación (;)
    // E -> Comentario (//)
    // F -> Entero
    // G -> Real
    // H -> + | - | / | * | ^
    // I -> Parentésis que abre
    // J -> Parentésis que cierra
    // A -> F | F H A
    // A -> G | G H A
    // A -> B | B H A
    // A -> I A J | I A J H A
}

namespace fs = std::filesystem;

void startTime(struct timeval &begin)
{
  gettimeofday(&begin, 0);
}

void getTime(struct timeval begin, struct timeval end)
{
  long seconds, microseconds;
  double elapsed;
  gettimeofday(&end, 0);
  seconds = end.tv_sec - begin.tv_sec;
  microseconds = end.tv_usec - begin.tv_usec;
  elapsed = seconds + microseconds * 1e-6;
  printf("Tiempo de ejecucion: %.8f seconds.\n", elapsed);
}

int main()
{
    string path = "tests";
    int number = 1;

    // Tiempo inicial
    struct timeval begin, end;
    gettimeofday(&begin, 0);

    // Secuencial
    for (const auto & entry : fs::directory_iterator(path)){
        if (!entry.is_directory())
        {
            syntaxHighligther(entry.path(), to_string(number));
            number++;
        } 
    }

    // Tiempo final
    gettimeofday(&end, 0);
    getTime(begin, end);



    // Tiempo inicial
    struct timeval begin2, end2;
    gettimeofday(&begin2, 0);
    number = 0;
    // Paralelo
    for (const auto & entry : fs::directory_iterator(path)){
        if (!entry.is_directory())
        {
            thread t1(syntaxHighligther,entry.path(), to_string(number));
            t1.join();
            number++;
        } 
    }

    // Tiempo final
    gettimeofday(&end2, 0);
    getTime(begin2, end2);

    return 0;
}