else if (token == "=") {
    if (tokens.empty()) {
        throw std::runtime_error("Falta el nombre de la variable para la asignacion");
    }
    std::string varName = tokens.front();
    tokens.erase(tokens.begin());
    if (stack.empty()) {
        throw std::runtime_error("Operandos insuficientes para la asignacion");
    } else {
        double value = stack.top(); stack.pop();
        variables[varName] = value;
        std::cout << "El valor ha sido asignado." << std::endl;
    }
}