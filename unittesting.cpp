#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include "DFA.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

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

TEST_CASE ("Unitesting B -> variable"){
    vector<DFA> dfatest;
    DFA _dfatest("a", "Variable");
    dfatest.push_back(_dfatest);
    REQUIRE(B(dfatest,0) == true);
}

TEST_CASE ("Unitesting2 B -> Variable"){
    vector<DFA> dfatest;
    DFA _dfatest("1485", "Entero");
    dfatest.push_back(_dfatest);
    REQUIRE(B(dfatest,0) == false);
} 

TEST_CASE ("Unitesting C -> Asignación"){
    vector<DFA> dfatest;
    DFA _dfatest("=", "Asignación");
    dfatest.push_back(_dfatest);
    REQUIRE(C(dfatest,0) == true);
}

TEST_CASE ("Unitesting D -> Punto y coma"){
    vector<DFA> dfatest;
    DFA _dfatest(";", "Punto y coma");
    dfatest.push_back(_dfatest);
    REQUIRE(D(dfatest,0) == true);
}