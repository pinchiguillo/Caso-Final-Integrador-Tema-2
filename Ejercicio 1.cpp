#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <functional>

typedef std::vector<std::string> Tokens;
std::unordered_map<std::string, double> variables;

Tokens tokenize(const std::string& input) {
    Tokens tokens;
    std::stringstream ss(input);
    std::string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

double evaluate(Tokens& tokens, std::unordered_map<std::string, double> localVariables = {}) {
    std::stack<double> stack;

    while (!tokens.empty()) {
        std::string token = tokens.front();
        tokens.erase(tokens.begin());

        if (token == "+") {
            if (stack.size() < 2) {
                throw std::runtime_error("Operandos insuficientes para la suma");
            }
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(a + b);
        } else if (token == "-") {
            if (stack.size() < 2) {
                throw std::runtime_error("Operandos insuficientes para la resta");
            }
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(a - b);
        } else if (token == "*") {
            if (stack.size() < 2) {
                throw std::runtime_error("Operandos insuficientes para la multiplicacion");
            }
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(a * b);
        } else if (token == "/") {
            if (stack.size() < 2) {
                throw std::runtime_error("Operandos insuficientes para la division");
            }
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            if (b == 0) {
                throw std::runtime_error("Division por cero");
            }
            stack.push(a / b);
        } else if (token == "^") {
            if (stack.size() < 2) {
                throw std::runtime_error("Operandos insuficientes para la potenciacion");
            }
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(pow(a, b));
        } else if (token == "sqrt") {
            if (stack.empty()) {
                throw std::runtime_error("Operandos insuficientes para la raiz cuadrada");
            }
            double a = stack.top(); stack.pop();
            if (a < 0) {
                throw std::runtime_error("La raiz cuadrada de un numero negativo no esta definida");
            }
            stack.push(sqrt(a));
        } else if (token == "%") {
            if (stack.size() < 2) {
                throw std::runtime_error("Operandos insuficientes para el modulo");
            }
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            if (b == 0) {
                throw std::runtime_error("Modulo por cero no esta definido");
            }
            stack.push(fmod(a, b));
        } else if (variables.find(token) != variables.end()) {
            // Si el token es una variable conocida, empújala en la pila
            stack.push(variables[token]);
        } else {
            // Si no es un operador, asume que es un número
            try {
                stack.push(std::stod(token));
            } catch (const std::invalid_argument&) {
                throw std::runtime_error("Token desconocido: " + token);
            }
        }
    }

    if (stack.size() != 1) {
        throw std::runtime_error("Expresion invalida");
    }

    return stack.top();
}

int main() {
    try {
        std::string input;
        std::cout << "Ingrese la expresión en notación postfija: ";
        std::getline(std::cin, input);
        Tokens tokens = tokenize(input);
        double result = evaluate(tokens);
        std::cout << "Resultado: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
