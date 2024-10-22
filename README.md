https://github.com/pinchiguillo/Caso-Final-Integrador-Tema-2

# Caso final integrador

## Enunciado del ejercicio

### Código original

```
// tiny_lisp.cpp
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

typedef std::vector<std::string> Tokens;

Tokens tokenize(const std::string& input) {
    Tokens tokens;
    std::string token;
    std::istringstream stream(input);

    while (stream >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

int evaluate(Tokens& tokens) {
    std::stack<int> stack;

    while (!tokens.empty()) {
        std::string token = tokens.back();
        tokens.pop_back();

        if (token == "+") {
            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            stack.push(a + b);
        } else if (token == "*") {
            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            stack.push(a * b);
        } else {
            stack.push(std::stoi(token));
        }
    }

    return stack.top();
}

int main() {
    std::string input;
    std::getline(std::cin, input);
    Tokens tokens = tokenize(input);
    std::cout << evaluate(tokens) << std::endl;
    return 0;
}
```

### Rúbrica

    Soporte de operaciones adicionales (0-14 puntos)
        0: No se agregan operaciones adicionales
        7: Se agregan algunas operaciones adicionales, como - y /
        14: Se agregan muchas operaciones adicionales, cubriendo la mayoría de las operaciones matemáticas estándar

    Soporte para diferentes números de argumentos (0-14 puntos)
        0: No se da soporte a operaciones con diferentes números de argumentos
        7: Se da soporte a algunas operaciones con diferentes números de argumentos
        14: Se da soporte a muchas operaciones con diferentes números de argumentos, incluyendo min y max

    Soporte para variables (0-14 puntos)
        0: No se da soporte a variables
        7: Se da soporte básico a variables (pueden ser definidas y usadas, pero no modificadas)
        14: Se da soporte completo a variables (pueden ser definidas, usadas y modificadas)

    Soporte para funciones (0-14 puntos)
        0: No se da soporte a funciones
        7: Se da soporte básico a funciones (pueden ser definidas y usadas, pero no pueden tener parámetros)
        14: Se da soporte completo a funciones (pueden ser definidas, usadas y pueden tener parámetros)

    Interfaz de usuario (0-14 puntos)
        0: La interfaz de usuario es mínima (solo puede procesar una expresión a la vez)
        7: La interfaz de usuario es moderadamente usable (puede procesar múltiples expresiones, pero no da feedback al usuario)
        14: La interfaz de usuario es altamente usable (puede procesar múltiples expresiones, da feedback al usuario, muestra un prompt, etc.)

    Calidad del código (0-14 puntos)
        0: El código es difícil de leer y entender, no sigue las buenas prácticas de codificación
        7: El código es moderadamente legible y sigue algunas buenas prácticas de codificación
        14: El código es muy legible, bien estructurado y sigue las buenas prácticas de codificación

    Manejo de errores (0-14 puntos)
        0: El programa no maneja errores o falla silenciosamente en casos de error
        7: El programa maneja algunos errores y falla de manera segura
        14: El programa maneja una amplia gama de posibles errores y proporciona mensajes de error útiles al usuario

## Guia de Uso del Comando "defun"

El comando `defun` se utiliza para definir funciones personalizadas que luego pueden ser invocadas dentro del intérprete. A continuación, se presenta una guía sobre cómo usar `defun`, junto con ejemplos ilustrativos.

### Sintaxis de `defun`

```
defun <nombre_de_funcion> <cantidad_de_parametros> <lista_de_parametros> <cuerpo_de_la_funcion>
```

- **<nombre_de_funcion>**: El nombre de la función que desea definir. Puede ser cualquier identificador alfanumérico.
- **<cantidad_de_parametros>**: Número de parámetros que la función acepta. Debe ser un número entero.
- **<lista_de_parametros>**: Nombres de los parámetros. Cada nombre debe ser único.
- **<cuerpo_de_la_funcion>**: Expresión que define la lógica de la función.

### Ejemplos

#### Ejemplo 1: Definir una Función de Suma

Definir una función llamada `suma` que tome dos parámetros y devuelva su suma:

```
>> defun suma 2 a b a b +
```

Para usar la función `suma`:

```
>> 5 3 suma
```

**Salida esperada**:
```
8
```

#### Ejemplo 2: Definir una Función de Multiplicación

Definir una función llamada `multiplicar` que tome dos parámetros y los multiplique:

```
>> defun multiplicar 2 x y x y *
```

Para usar la función `multiplicar`:

```
>> 4 6 multiplicar
```

**Salida esperada**:
```
24
```

#### Ejemplo 3: Definir una Función para la Raíz Cuadrada

Definir una función llamada `raiz` que tome un parámetro y devuelva su raíz cuadrada:

```
>> defun raiz 1 x x sqrt
```

Para usar la función `raiz`:

```
>> 16 raiz
```

**Salida esperada**:
```
4
```

#### Ejemplo 4: Definir una Función Compleja (Potencia)

Definir una función llamada `potencia` que eleve un número a otro:

```
>> defun potencia 2 base exponente base exponente ^
```

Para usar la función `potencia`:

```
>> 2 3 potencia
```

**Salida esperada**:
```
8
```

#### Ejemplo 5: Definir una Función para el Valor Absoluto

Definir una función llamada `valorAbsoluto` que tome un número y devuelva su valor absoluto:

```
>> defun valorAbsoluto 1 x x abs
```

Para usar la función `valorAbsoluto`:

```
>> -7 valorAbsoluto
```

**Salida esperada**:
```
7
```

### Notas Adicionales
- Las funciones pueden tomar cualquier operación soportada por el intérprete, como `+`, `-`, `*`, `/`, `sqrt`, `sin`, `cos`, etc.
- Los parámetros definidos en una función se pueden usar en cualquier orden en el cuerpo de la función.
- Una vez definida, la función se puede invocar en cualquier momento ingresando su nombre seguido de los argumentos necesarios.
