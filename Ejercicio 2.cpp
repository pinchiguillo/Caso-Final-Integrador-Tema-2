// tiny_lisp.cpp
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <math.h>
#include <unordered_map>

typedef std::vector<std::string> Tokens;
std::unordered_map<std::string, int> variables;

Tokens tokenize(const std::string& input) {
    Tokens tokens;
    std::string token;
    std::istringstream stream(input);

    while (stream >> token) {
        tokens.push_back(token);
    }

    return tokens;
}


bool isInteger(const std::string& str) {
    // Verificamos si la cadena está vacía
    if (str.empty()) {
        return false;
    }
    std::size_t start = 0;

    // Manejo de números negativos
    if (str[0] == '-') {
        if (str.size() == 1) {
            return false;
        }
        start = 1;
    }
    for (std::size_t i = start; i < str.size(); ++i) {
        if (!std::isdigit(str[i])) {
            return false;
        }
    }

    return true;
}



int evaluate(Tokens& tokens) { //[2, 3, +]
    std::stack<int> stack;
    std::stack<std::string> variableStack;

    while (!tokens.empty()) {
        std::string token = tokens.front(); //Seleccionamos el primero del vector
        tokens.erase(tokens.begin());

        if (token == "=") { //FORMATO "j = 2"
            if (variableStack.size() < 1) {
                throw std::invalid_argument("Incorrect format of name for variable assignment");
            }
            if(!isInteger(tokens.front())) {
                throw std::invalid_argument("Incorrect argument value for variable assignment");
            }
            std::string var_name = variableStack.top();
            variableStack.pop();
            int value = std::stoi(tokens.front());
            tokens.erase(tokens.begin());

            variables[var_name] = value;
            std::cout << "Asignada variable: " << var_name << " = " << value << std::endl;
        } else if (variables.find(token) != variables.end()) {
            stack.push(variables[token]);
        } else if (token == "+") {
            if (stack.size() < 2) {
                throw std::invalid_argument("Incorrect number of arguments");
            }
            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            stack.push(a + b);
        } else if (token == "*") {
            if (stack.size() < 2) {
                throw std::invalid_argument("Incorrect number of arguments");
            }
            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            stack.push(a * b);
        } else if (token == "-") {
            if (stack.size() < 2) {
                throw std::invalid_argument("Incorrect number of arguments");
            }
            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            stack.push(b - a); // Se intercambia el orden de los elementos
        } else if (token == "/") {
            if (stack.size() < 2) {
                throw std::invalid_argument("Incorrect number of arguments");
            }
            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            stack.push(b / a);
        }  else if (token == "^") {

            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            stack.push(std::pow(b, a));
        } else if (token == "min") {
            if (stack.size() < 1) {
                throw std::invalid_argument("Incorrect number of arguments");
            }
            int a = stack.top();
            stack.pop();
            if (stack.empty()) {
                stack.push(a);
            }else {
                int b = stack.top();
                stack.pop();
                stack.push(std::min(a, b));
            }
        } else if (token == "max") {
            if (stack.size() < 1) {
                throw std::invalid_argument("Incorrect number of arguments");
            }
            int a = stack.top();
            stack.pop();
            if (stack.empty()) {
                stack.push(a);
            }else {
                int b = stack.top();
                stack.pop();
                stack.push(std::max(a, b));
            }
        } else {
            if(isInteger(token)) {
                stack.push(std::stoi(token));
            }else {
                variableStack.push(token);
            }
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
