##Especificacion Lenguaje Natural de scanner:

Un scanner reconoce una secuencia de lexemas (palabras/cadenas/caracteres) y los asocia a una secuencia de tokens.
Para ello, lee el código fuente carácter por carácter y, cuando reconoce un lexema completo, determina su tipo de token.  
Si es una secuencia de dígitos, se la reconoce como un token de tipo número. 
Si es un símbolo entre comillas simples, se lo reconoce como un token de tipo carácter.
Si son una secuencia de caracteres entre comillas dobles, se la reconoce como un token de tipo cadena. 
Si el lexema coincide con alguna palabra reservada (o keyword), como if, else, while, for, return, int, char, float, void, entonces devuelve el token correspondiente a esa keyword. 
Los símbolos como llaves { }, paréntesis ( ), operadores matemáticos o lógicos (+, -, *, /, =, ==, <, >), y delimitadores (, y ;) se reconocen como tokens de su tipo correspondiente. 
Si se encuentra un carácter desconocido que no pertenece a ningún token válido, se devuelve un token de error.
Cuando no quedan más caracteres por procesar, se devuelve un token de fin.
Para cada lexema reconocido, el escáner devuelve un objeto token con el tipo y, en caso de ser necesario, un valor asociado (por ejemplo, el nombre del identificador, el número entero, el carácter o la cadena, etcétera). 

##Especificación Expresiones Regulares de scanner: https://docs.google.com/document/d/1y-_tjjBD1hESLqQM05xO9RgVXsvGFq8Xs_GuUzTRvJM/edit?tab=t.0

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



