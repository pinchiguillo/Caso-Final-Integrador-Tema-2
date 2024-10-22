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
std::unordered_map<std::string, std::pair<int, std::function<double(const std::vector<double>&)>>> functions;

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