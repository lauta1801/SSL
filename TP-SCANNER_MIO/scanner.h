#ifndef SCANNER_H
#define SCANNER_H

#include <stdbool.h>
#include <stdio.h>

typedef enum {
    tokenIdentificador,   // Identificadores
    tokenNumero,          // Números
    tokenCaracter,        // Constante de carácter (si lo usás)
    tokenString,          // Constante de cadena
    tokenOperador,        // Operadores (+ - * / =)
    tokenDelimitador,     // Delimitadores (; , ( ) [ ] { })
    tokenFin,             // Fin de entrada
    LexError              // Error léxico / token inválido
} TipoDeToken;

typedef union {
    int numero;
    char identificador[64];
    char simbolo;
    char texto[128];
} ValorDelToken;

typedef struct {
    TipoDeToken tipo;
    ValorDelToken valor;
} Token;

// Función principal del scanner
bool GetNextToken(Token *t /* out */, FILE *archivoFuente);

#endif // SCANNER_H