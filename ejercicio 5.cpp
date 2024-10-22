int main() {
    //mensaje de bienvinida y explicacion de como usar el programa
    std::cout << "-Bienvenido al interprete tinylisp! introduce operaciones! \n-Este programa usa notacion polaca inversa" << std::endl;
    std::cout << "-Recuerda introducir operandos suficientes y escribe 'Salir' para terminar" << std::endl;
    std::string input;
    while (true) {
        std::cout << ">> ";
        std::getline(std::cin, input);
        if (input == "Salir") break;
        try {
            Tokens tokens = tokenize(input);
            std::cout << evaluate(tokens) << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}
