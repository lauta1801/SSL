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


