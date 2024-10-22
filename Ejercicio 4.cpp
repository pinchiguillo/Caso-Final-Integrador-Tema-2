else if (token == "defun") {
    if (tokens.size() < 3) {
        throw std::runtime_error("Sintaxis incorrecta para la definicion de funcion");
    }
    std::string funcName = tokens.front(); tokens.erase(tokens.begin());
    int paramCount;
    try {
        paramCount = std::stoi(tokens.front()); tokens.erase(tokens.begin());
    } catch (const std::invalid_argument&) {
        throw std::runtime_error("El numero de parametros debe ser un entero");
    }
    Tokens paramNames(tokens.begin(), tokens.begin() + paramCount); // Get parameter names
    tokens.erase(tokens.begin(), tokens.begin() + paramCount);
    Tokens bodyTokens(tokens);
    functions[funcName] = {paramCount, [paramNames, bodyTokens](const std::vector<double>& args) -> double {
        if (args.size() != paramNames.size()) {
            throw std::runtime_error("Numero incorrecto de argumentos para la funcion");
        }
        std::unordered_map<std::string, double> localVariables;
        for (size_t i = 0; i < paramNames.size(); ++i) {
            localVariables[paramNames[i]] = args[i];
        }
        Tokens evalTokens = bodyTokens;
        return evaluate(evalTokens, localVariables);
    }};
    std::cout << "Funcion " << funcName << " definida con exito." << std::endl;
    return 0;}