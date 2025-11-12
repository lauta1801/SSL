#include "parser.h"

/*
Estas son las Variables Globales estaticas
*/
// variables del estado y error
static Token tokenActual;
static Token tokenError;
static EstadoParser estado = PS_OK;
static char mensajeError[256];

// variables para construir la traduccion
static char name[64];        // nombre del identificador
static char datatype[64];    // tipo base (int, char, etc.)
static char out[256];        // descripción acumulada

#define MAX_DECLARACIONES 100 // todas las max_declaraciones por 100
static char traducciones[MAX_DECLARACIONES][256]; // declara un arreglo de caracteres 
static int cantidadTraducciones = 0;

// Su trabajo es consumir el token actual y pedirle al scanner (el analizador léxico) que le dé el siguiente.
static void Avanzar(FILE *archivoFuente) {
    if (!GetNextToken(&tokenActual, archivoFuente)) {
        estado = PS_LEXERROR;
        tokenError = tokenActual;
        snprintf(mensajeError, sizeof(mensajeError),
                 "Caracter invalido en token '%c'", tokenActual.valor.simbolo);
        emitirErrorLexico(mensajeError);
    }
}

// Su trabajo es verificar que el token actual es exactamente 
// el que se esperaba y, si lo es, consumirlo y avanzar al siguiente.
static void Match(TipoDeToken esperado, char simboloOpcional, FILE *archivoFuente) {
    
    if (tokenActual.tipo == esperado &&
        (simboloOpcional == '\0' || tokenActual.valor.simbolo == simboloOpcional)) {
        Avanzar(archivoFuente);
    } else {
        estado = PS_ERROR;
        tokenError = tokenActual;
        snprintf(mensajeError, sizeof(mensajeError),
                 "Se esperaba token tipo %d con simbolo '%c', pero se encontro tipo %d con simbolo '%c'",
                 esperado, simboloOpcional, tokenActual.tipo, tokenActual.valor.simbolo);
        emitirErrorSintactico(mensajeError);
    }
}

// Punto de entrada
void UnidadDeTraduccion(FILE *archivoFuente) {
    estado = PS_OK;
    mensajeError[0] = '\0';
    cantidadTraducciones = 0;
    Avanzar(archivoFuente);

    while (estado == PS_OK) {
        if (tokenActual.tipo == tokenFin) {
            break;
        }
        // Lo que se reempleza por lo comentado
        if (tokenActual.tipo == tokenIdentificador) {
            Declaracion(archivoFuente);
        } else {
            estado = PS_ERROR;
            tokenError = tokenActual;
            emitirErrorSintactico("Se esperaba una declaracion");
            break;
        }
    }
}

void Declaracion(FILE* archivoFuente) {
    TipoBase(archivoFuente);
    if (estado != PS_OK) return;

    // 1. Guardamos cuántas traducciones había ANTES de esta línea
    int indiceInicio = cantidadTraducciones;

    ListaDeclaradores(archivoFuente);
    if (estado != PS_OK) return;

    PuntoYComa(archivoFuente);
    if (estado != PS_OK) return; // Importante: Salir si el ';' falla

    // 2. Si todo OK (incluido el ';'), imprimimos las traducciones
    //    que se acaban de agregar (desde indiceInicio hasta el final)
    for (int i = indiceInicio; i < cantidadTraducciones; i++) {
        printf("%s\n", traducciones[i]); // Imprime la traducción
    }
}

// <tipo> ::= identificador
void TipoBase(FILE *archivoFuente) {
    if (tokenActual.tipo == tokenIdentificador) {
        validarTipo(tokenActual.valor.identificador);
        strcpy(datatype, tokenActual.valor.identificador);
        Avanzar(archivoFuente);
    } else {
        estado = PS_ERROR;
        tokenError = tokenActual;
        emitirErrorSintactico("Se esperaba un tipo base");
    }
}

// <lista-declaradores> ::= <declarador> { , <declarador> }
void ListaDeclaradores(FILE *archivoFuente) {
    Declarador(archivoFuente);
    if (estado != PS_OK) return;

    while (estado == PS_OK &&
           tokenActual.tipo == tokenDelimitador &&
           tokenActual.valor.simbolo == ',') {
        Match(tokenDelimitador, ',', archivoFuente);
        if (estado != PS_OK) return;

        Declarador(archivoFuente);
        if (estado != PS_OK) return;
    }
}

// Declarador dividido en dcl y dirdcl
void Declarador(FILE *archivoFuente) {
    name[0] = '\0';
    out[0] = '\0';
    dcl(archivoFuente);

    if (estado != PS_OK) return;

    if (strlen(name) > 0 && strlen(datatype) > 0 && cantidadTraducciones < MAX_DECLARACIONES) {
        char resultado[256];
        char descripcionFinal[256];

        // Si out está vacío, simplemente usamos el tipo base
        if (strlen(out) == 0) {
            strcpy(descripcionFinal, datatype);
        } else {
            snprintf(descripcionFinal, sizeof(descripcionFinal), "%s%s", out, datatype);
        }

        snprintf(resultado, sizeof(resultado), "%s: %s", name, descripcionFinal);
        strcpy(traducciones[cantidadTraducciones++], resultado);
    }
}




// Verifica punto y coma
void PuntoYComa(FILE *archivoFuente) {
    if (tokenActual.tipo == tokenDelimitador && tokenActual.valor.simbolo == ';') {
        Match(tokenDelimitador, ';',archivoFuente);
    } else {
        estado = PS_ERROR;
        tokenError = tokenActual;
        emitirErrorSintactico("Se esperaba ';' al final de la declaracion");
    }
}

// Estado y mensaje
EstadoParser ObtenerEstado(void) {
    return estado;
}

const char* ObtenerMensajeError(void) {
    return mensajeError;
}

Token ObtenerTokenError(void) {
    return tokenError;
}

const char* ObtenerNombre(void) {
    return name;
}

const char* ObtenerTipoBase(void) {
    return datatype;
}

const char* ObtenerDescripcion(void) {
    return out;
}

const char* ObtenerTraduccion(int i) {
    if (i >= 0 && i < cantidadTraducciones) {
        return traducciones[i];
    }
    return NULL;
}

int ObtenerCantidadTraducciones(void) {
    return cantidadTraducciones;
}
