#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <fstream>

using namespace std;

#ifndef TAREA_EXTRA_TOKEN_H
#define TAREA_EXTRA_TOKEN_H

class Token {
public:
    enum Type { ID ,PRINT , NUM, PLUS, MINUS,MULT, SEMICOLON,LPAREN=0, RPAREN, ASING, ERR, END };
    static const char* token_names[12];
    Type type;  //almacena el tipo de token específico que ha sido identificado durante el análisis léxico
    string lexema; //si el token es de tipo ID y el lexema es variable1,
    Token(Type); //onstructor que inicializa un token solo con el tipo. uttil para signos d eoperacion
    Token(Type, char c);//para tokens de un solo carácter como +, -, *
    Token(Type, const string source);//para palabras
};

const char* Token::token_names[12] = {"ID","PRINT","NUM", "PLUS", "MINUS", "MULT","SEMICOLON","LPAREN" , "RPAREN",  "ASING" , "ERR", "END"};

Token::Token(Type type):type(type) { lexema = ""; }

Token::Token(Type type, char c):type(type) { lexema = c; }

Token::Token(Type type, const string source):type(type) {
    lexema = source;
}
#endif //TAREA_EXTRA_TOKEN_H
