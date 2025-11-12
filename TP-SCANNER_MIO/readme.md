## Especificacion Lenguaje Natural:

El traductor de declaraciones (dcl) tiene como objetivo analizar una declaración del lenguaje C y expresar su significado en lenguaje natural. Para lograr esto, se divide el proceso en tres etapas principales: el análisis léxico, el análisis sintáctico y el análisis semántico. Cada una de estas etapas cumple una función específica dentro del proceso de traducción.

En primer lugar, el análisis léxico se encarga de leer el texto del programa y dividirlo en componentes básicos llamados tokens. Estos tokens son las unidades mínimas que conforman el lenguaje, como los tipos de datos, los nombres de variables, los números o los símbolos. El analizador léxico ignora los espacios, tabulaciones y saltos de línea porque no tienen un significado en la estructura del lenguaje, al igual que los comentarios, que se descartan por completo. Las palabras reservadas que reconoce este analizador son “int”, “char” y “void”, que representan los tipos de datos básicos del lenguaje C. Los identificadores son los nombres de variables o funciones definidos por el usuario, y deben comenzar con una letra o un guion bajo, pudiendo contener letras o números a continuación. Si un identificador coincide con una palabra reservada, se interpreta como palabra clave. Los números representan valores enteros positivos y suelen utilizarse en la definición de arreglos. También se reconocen símbolos que estructuran la declaración, como el asterisco (*) para indicar punteros, los paréntesis para agrupar o definir funciones, los corchetes para definir arreglos, la coma para separar elementos y el punto y coma para indicar el final de la declaración. Finalmente, cualquier carácter desconocido o fuera del lenguaje genera un error léxico e informa su posición.

En segundo lugar, el análisis sintáctico define la estructura que deben tener los tokens para formar una declaración válida en C. Es decir, establece cómo deben combinarse los tipos, identificadores y símbolos para crear una estructura correcta. Una declaración se compone de un tipo base, seguido de un declarador y finalizada con un punto y coma. El tipo base indica la naturaleza del dato, como “int”, “char” o “void”. El declarador describe la forma del identificador y puede representar un nombre simple, un puntero, un arreglo o una función. Por ejemplo, “int *p;” representa un puntero a un entero, mientras que “int (*p)[10];” representa un puntero a un arreglo de 10 enteros. De esta manera, la gramática describe las combinaciones posibles entre los elementos del lenguaje para que el analizador pueda determinar si una declaración es válida o no.

Finalmente, el análisis semántico es la etapa que interpreta el significado de la declaración y la traduce a lenguaje natural. Cada regla sintáctica tiene asociada una acción semántica que genera una descripción textual. Por ejemplo, si la declaración es “int *p;”, el tipo base es “int” y el declarador “*p” indica que es un puntero, por lo tanto la traducción final es “p es un puntero a entero”. Si la declaración es “int (*p)[10];”, se interpreta que “p” es un puntero a un arreglo de 10 enteros. Si la declaración es “char **argv;”, se traduce como “argv es un puntero a puntero a carácter”, y si la declaración es “void f();”, se interpreta como “f es una función que devuelve void”. Las reglas semánticas indican que los tipos base se traducen directamente (por ejemplo “int” como “entero”), los punteros se expresan con la frase “puntero a”, los arreglos con “arreglo de”, y las funciones con “función que devuelve”. Los paréntesis se usan para modificar la precedencia y establecer el orden correcto de interpretación, permitiendo diferenciar entre expresiones similares como “int *p[10];” (“p es un arreglo de 10 punteros a enteros”) y “int (*p)[10];” (“p es un puntero a un arreglo de 10 enteros”).

En conclusión, el traductor dcl toma una declaración del lenguaje C y la convierte en una frase clara y entendible en lenguaje natural. El análisis léxico se ocupa de identificar los componentes del texto, el análisis sintáctico verifica su estructura, y el análisis semántico interpreta su significado. De esta forma, se logra describir correctamente cualquier declaración simple del lenguaje C, como punteros, arreglos o funciones, de manera comprensible para una persona sin conocimientos técnicos del código.


## Especificación Léxica

### 1. Prioridad de reconocimiento
1. Espacios y comentarios (ignorar)  
2. Palabras clave  
3. Identificadores  
4. Números  
5. Símbolos  
6. Errores léxicos  



### 2. Espacios en Blanco y Comentarios
**Whitespace:** `([ \t\r\n])+`  
**Acción:** Ignorar  

**Comentario bloque:** `/\*.*?\*/`  
**Acción:** Ignorar  

**Comentario línea:** `//[^\r\n]*`  
**Acción:** Ignorar  



### 3. Palabras Clave (Keywords)
**Categoría:** Tipo  
**Token:** `Int`, `Char`, `Void`
**Regex:** `(int|char|void)`  



### 4. Identificadores
**Token:** `Ident`  
**Regex:** `[A-Za-z_][A-Za-z0-9_]*`  
**Descripción:** Nombres de variables, funciones o tipos definidos por el usuario.  
Si coincide con una palabra clave, se emite como *keyword*.  



### 5. Números
**Token:** `IntLiteral`  
**Regex:** `(0|[1-9][0-9]*)`  
**Descripción:** Enteros positivos decimales simples.  



### 6. Símbolos y Punctuators
**Símbolos reconocidos:**  
`*` → `Asterisk`  
`(` → `LParen`  
`)` → `RParen`  
`[` → `LBrack`  
`]` → `RBrack`  
`,` → `Comma`  
`;` → `Semicolon` *(opcional)*  



### 7. Errores Léxicos
Cualquier carácter no reconocido genera el token:  

## Especificación Sintáctica
```ebnf

unidad_traduccion → declaration

declaration → tipo declarator ;

tipo → int
    | char
    | void

declarator → Ident
            | * declarator
            | ( declarator )
            | declarator [ IntLiteral ]
            | declarator ( )
```

## Especificación Semántica
```ebnf
Las reglas semánticas principales son las siguientes:

1. Regla de declaración:
   declaration → tipo declarator ;
   Acción semántica:
   LN(declaration) = LN(declarator) + " es " + descripción(LN(tipo))

2. Regla de tipo base:
   tipo → int | char | void
   Acción semántica:
   LN(tipo) = "entero" | "carácter" | "void"

3. Declarador simple:
   declarator → Ident
   Acción semántica:
   LN(declarator) = nombre(Ident)

4. Declarador puntero:
   declarator → * declarator
   Acción semántica:
   LN(declarator) = LN(declarator₂) + " puntero a"

5. Declarador arreglo (array):
   declarator → declarator [ IntLiteral ]
   Acción semántica:
   LN(declarator) = LN(declarator₁) + " arreglo de " + valor(IntLiteral)

6. Declarador función:
   declarator → declarator ( )
   Acción semántica:
   LN(declarator) = LN(declarator₁) + " función que devuelve"

7. Agrupaciones con paréntesis:
   declarator → ( declarator )
   Acción semántica:
   LN(declarator) = LN(contenido de declarator)

```

