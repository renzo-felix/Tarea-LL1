#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <fstream>
#include "Token.h"
using namespace std;
#ifndef TAREA_EXTRA_SCANNER_H
#define TAREA_EXTRA_SCANNER_H
///
//El escáner es responsable de leer el código fuente (o cadena de entrada) carácter por
// carácter y agrupar estos caracteres en tokens significativos que serán entregados al parser
class Scanner {
public:
    Scanner(const char* in_s);//inicializa el escáner con la cadena de entrada (in_s), que es el código fuente que se va a analiza
    Token* nextToken();//genera tokens uno por uno
    ~Scanner();
private:
    string input;//contiene la cadena completa que se está analizando
    int first, current; //inicio del lexema actual (el conjunto de caracteres que forman un token).
    int state;
    char nextChar();//Lee el siguiente carácter de la cadena de entrada y avanza el índice current.
    void rollBack();// mueve el índice current una posición hacia atrás.
    void startLexema();//señalar el punto de inicio de los caracteres que formarán el siguiente
    string getLexema(); //Este lexema representa el valor del token que ha sido identificado
};

Scanner::Scanner(const char* s):input(s),first(0),current(0) { }
Token* Scanner::nextToken() {
    Token* token;
    char c;
    state = 0;
    startLexema();
    while (1) {
        switch (state) {
            case 0:
                c = nextChar();
                if (c == ' ') {
                    startLexema(); state = 0;  // Ignorar espacios
                } else if (c == '\0') {
                    return new Token(Token::END);  // Fin de archivo
                } else if (c == '(') {
                    state = 1;  // Paréntesis izquierdo
                } else if (c == ')') {
                    state = 2;  // Paréntesis derecho
                } else if (c == '+') {
                    state = 3;  // Operador suma
                } else if (c == '-') {
                    state = 4;  // Operador resta
                } else if (c == '*') {
                    state = 5;  // Operador multiplicación
                } else if (c == '=') {
                    state = 6;  // Asignación
                } else if (isdigit(c)) {
                    state = 7;  // Número
                } else if (isalpha(c)) {
                    state = 8;  // Identificador o palabra clave
                } else if (c == ';') {
                    return new Token(Token::SEMICOLON, c);  // Punto y coma
                } else {
                    return new Token(Token::ERR, c);  // Carácter no válido
                }
                break;

            case 1:
                return new Token(Token::LPAREN);  // Token de paréntesis izquierdo
            case 2:
                return new Token(Token::RPAREN);  // Token de paréntesis derecho
            case 3:
                return new Token(Token::PLUS, c);  // Token de suma
            case 4:
                return new Token(Token::MINUS, c);  // Token de resta
            case 5:
                return new Token(Token::MULT, c);  // Token de multiplicación
            case 6:
                return new Token(Token::ASING, c);  // Token de asignación '='

            case 7:
                c = nextChar();
                if (isdigit(c)) {
                    state = 7;  // Continuar leyendo el número
                } else {
                    rollBack();
                    return new Token(Token::NUM, getLexema());  // Devolver número entero
                }
                break;

            case 8:
                c = nextChar();
                if (isalnum(c)) {  // Identificador o palabra clave
                    state = 8;
                } else {
                    rollBack();
                    // Distinguir si es 'print' o un identificador general
                    if (getLexema() == "print") {
                        return new Token(Token::PRINT);  // Reconocer la palabra clave 'print'
                    } else {
                        return new Token(Token::ID, getLexema());  // Devolver identificador
                    }
                }
                break;
        }
    }
}

Scanner::~Scanner() { }

char Scanner::nextChar() {
    int c = input[current];
    if (c != '\0') current++;
    return c;
}

void Scanner::rollBack() {
    if (input[current] != '\0')
        current--;
}

void Scanner::startLexema() {
    first = current;
    return;
}

string Scanner::getLexema() {
    return input.substr(first,current-first);
}
#endif //TAREA_EXTRA_SCANNER_H
