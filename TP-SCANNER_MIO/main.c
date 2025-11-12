#include <stdio.h>
#include <string.h>
#include "parser.h"

int main(void) {
    FILE *archivoFuente = fopen("declaradores.txt", "r"); // abre el archivo de codigo fuente
    if (archivoFuente == NULL) {
        printf("Error al abrir el archivo de codigo fuente.\n");
        return 1;
    }
    
    UnidadDeTraduccion(archivoFuente); // funcion principal del parser (Definida parser.h)

    EstadoParser estado = ObtenerEstado(); // obtiene el estado final del parser, si termino bien o si hubo un error 
    Token t = ObtenerTokenError(); // si hubo un error en la linea obtiene el token que causo el problema 

    if (estado == PS_OK) {  // si el estado esta ok muestra el mensaje de no se encontraro errores
        printf("\nParsing finalizado correctamente. No se encontraron errores.\n");
        
    } else if (estado == PS_ERROR) // Sino esta bien muestra el error sintactico 
    {
        printf("\nError sintactico: %s\n", ObtenerMensajeError());
        printf("Token conflictivo: ");
        if (t.tipo == tokenIdentificador) {
            printf("'%s'\n", t.valor.identificador);
        } else if (t.tipo == tokenNumero) {
            printf("'%d'\n", t.valor.numero);
        } else if (t.tipo == tokenOperador || t.tipo == tokenDelimitador || t.tipo == tokenCaracter) {
            printf("'%c'\n", t.valor.simbolo);
        } else if (t.tipo == tokenString) {
            printf("'%s'\n", t.valor.texto);
        } else {
            printf("tipo %d\n", t.tipo);
        }
    } else if (estado == PS_LEXERROR) { // sino muestra que fue un error lexico
        printf("\nError lexico: %s\n", ObtenerMensajeError());
        printf("Token conflictivo: ");
        if (t.tipo == tokenOperador || t.tipo == tokenDelimitador || t.tipo == tokenCaracter) {
            printf("'%c'\n", t.valor.simbolo);
        } else {
            printf("tipo %d\n", t.tipo);
        }
    } else { // sino muestra que fue un error desconocido
        printf("\nError desconocido.\n");
    }

    fclose(archivoFuente); // cierra el archivo de codigo fuente
    return 0;
    }
}