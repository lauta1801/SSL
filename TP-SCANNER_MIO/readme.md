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

### 1. Convenciones Generales
- **Alfabeto:** ASCII / UTF-8  
- **Case-sensitive:** `const` ≠ `Const`  
- **Regla de máxima captura (max-munch):** el scanner toma el lexema más largo.  
- **Prioridad de reconocimiento:**  
  1. Espacios y comentarios (ignorar)  
  2. Palabras clave  
  3. Identificadores  
  4. Números  
  5. Símbolos  
  6. Errores léxicos  



### 2. Espacios en Blanco y Comentarios
| Tipo | Regex | Acción |
|------|--------|---------|
| **Whitespace** | `([ \t\r\n])+` | Ignorar |
| **Comentario bloque** | `/\*.*?\*/` | Ignorar |
| **Comentario línea** | `//[^\r\n]*` | Ignorar |


### 3. Palabras Clave (Keywords)
| Categoría | Token | Regex |
|------------|--------|--------|
| **Tipo** | `Void`, `Char`, `Int`, `Float`, `Double`, etc. | `void|char|short|int|long|signed|unsigned|float|double` |
| **Calificador** | `Const`, `Volatile` | `const|volatile` |
| *(Opcional)* | `Struct`, `Union`, `Enum` | `struct|union|enum` |



### 4. Identificadores
| Token | Regex | Descripción |
|--------|--------|-------------|
| `Ident` | `[A-Za-z_][A-Za-z0-9_]*` | Nombres de variables, funciones o tipos definidos por el usuario. Si coincide con palabra clave, se emite como keyword. |


### 5. Números
| Token | Regex | Descripción |
|--------|--------|-------------|
| `IntLiteral` | `(0|[1-9][0-9]*)` | Enteros positivos decimales simples. |


### 6. Símbolos y Punctuators
| Símbolo | Token |
|----------|--------|
| `*` | `Asterisk` |
| `(` | `LParen` |
| `)` | `RParen` |
| `[` | `LBrack` |
| `]` | `RBrack` |
| `,` | `Comma` |
| `;` | `Semicolon` *(opcional)* |


### 7. Errores Léxicos
Cualquier carácter no reconocido genera el token:

