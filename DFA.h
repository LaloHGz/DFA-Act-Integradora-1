#pragma once
#include<iostream>

using namespace std;

struct DFA {
    string token;
    string tipo;
    DFA();
    DFA(string token, string tipo);
    string print();
};

DFA::DFA(){
    this -> token = "";
    this -> tipo = "";
    
}

DFA::DFA(string token, string tipo){
    this -> token = token;
    this -> tipo = tipo;

}

string DFA::print(){
    return this ->token + " "+ this-> tipo;
}