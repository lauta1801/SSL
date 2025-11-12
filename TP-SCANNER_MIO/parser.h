#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include <string.h>
#include <stdio.h>
#include "verificadorSemantico.h"
#include "manejadorDeErrores.h"

// Estado del parser (para diagnóstico/debug)
typedef enum {
    PS_OK,           // Parsing exitoso
    PS_ERROR,        // Error de sintaxis
    PS_LEXERROR      // Error léxico
} EstadoParser;

// Función principal del parser
void UnidadDeTraduccion(FILE *archivoFuente);

// Acceso al estado y mensaje de error
EstadoParser ObtenerEstado(void);
const char* ObtenerMensajeError(void);
Token ObtenerTokenError(void);

// Funciones internas del parser
void Declaracion(FILE* archivoFuente);
void TipoBase(FILE* archivoFuente);
void ListaDeclaradores(FILE* archivoFuente);
void Declarador(FILE* archivoFuente);
// void Asignacion(void);
void PuntoYComa(FILE* archivoFuente);

// Opcionales para estructuras y funciones
void DeclaracionFuncion(void);

// Nuevas funciones para obtener descripción
const char* ObtenerNombre(void);       // nombre del identificador
const char* ObtenerTipoBase(void);     // tipo base (int, char, etc.)
const char* ObtenerDescripcion(void);  // descripción acumulada (puntero a..., arreglo de..., etc.)

const char* ObtenerTraduccion(int i);
int ObtenerCantidadTraducciones(void);

#endif // PARSER_H