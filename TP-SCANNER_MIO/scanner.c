#include "scanner.h"
#include <ctype.h>
#include <string.h>

// Estado interno del scanner
static int c = ' ';  // Carácter actual

// Buffer para lexemas
static char lexema[64];
static size_t pos_lexema;

// Función auxiliar para leer el siguiente carácter
static void siguiente_caracter(FILE *archivoFuente) {
    c = getc(archivoFuente);
}


bool GetNextToken(Token *t, FILE *archivoFuente) {
    // Saltear espacios en blanco
    while (isspace(c)) {
        siguiente_caracter(archivoFuente);
    }

    // Inicializar buffer
    pos_lexema = 0;
    lexema[0] = '\0';

    // Fin de entrada
    if (c == EOF) {
        t->tipo = tokenFin;
        return true;
    }

    // Identificadores (letras y dígitos, comenzando con letra)
    if (isalpha(c)) {
        do {
            if (pos_lexema < sizeof(lexema) - 1) {
                lexema[pos_lexema++] = c;
            }
            siguiente_caracter(archivoFuente);
        } while (isalnum(c));

        lexema[pos_lexema] = '\0';
        t->tipo = tokenIdentificador;
        strcpy(t->valor.identificador, lexema);
        return true;
    }

    // Números enteros
    if (isdigit(c)) {
        int valor = 0;
        do {
            valor = valor * 10 + (c - '0');
            siguiente_caracter(archivoFuente);
        } while (isdigit(c));

        t->tipo = tokenNumero;
        t->valor.numero = valor;
        return true;
    }

    // Cadenas entre comillas simples
    if (c == '\'') {
        siguiente_caracter(archivoFuente);
        pos_lexema = 0;

        while (c != '\'' && c != EOF && pos_lexema < sizeof(t->valor.texto) - 1) {
            t->valor.texto[pos_lexema++] = c;
            siguiente_caracter(archivoFuente);
        }

        if (c == '\'') {
            t->valor.texto[pos_lexema] = '\0';
            siguiente_caracter(archivoFuente);
            t->tipo = tokenString;
            return true;
        } else {
            t->tipo = LexError;
            return false;
        }
    }

    // Operadores válidos
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=') {
        t->tipo = tokenOperador;
        t->valor.simbolo = c;
        siguiente_caracter(archivoFuente);
        return true;
    }

    // Delimitadores válidos
    if (c == ';' || c == ',' || c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}') {
        t->tipo = tokenDelimitador;
        t->valor.simbolo = c;
        siguiente_caracter(archivoFuente);
        return true;
    }

    // Carácter inválido
    t->tipo = LexError;
    t->valor.simbolo = c;  // Guardar el carácter conflictivo
    siguiente_caracter(archivoFuente);
    return false;
}