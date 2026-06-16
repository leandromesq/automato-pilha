#include <iostream>
#include <stack>
#include <string>

// definição dos estados
enum class State {
    Q0,     // estado inicial/leitura
    Q1,     // estado final (aceitacao)
    ERROR   // estado final (rejeicao)
};

bool ehAbertura(char c) {
    return c == '(' || c == '[' || c == '{';
}

bool formamPar(char topoPilha, char lidoFita) {
    if (topoPilha == '(' && lidoFita == ')') return true;
    if (topoPilha == '[' && lidoFita == ']') return true;
    if (topoPilha == '{' && lidoFita == '}') return true;
    return false;
}

bool processaAutomatoMultiplo(const std::string& palavra) {
    std::stack<char> pilha;
    State estadoAtual = State::Q0;

    // Z0 - marcador de fundo de pilha
    pilha.push('$');

    for (char simbolo : palavra) {
        if (estadoAtual == State::ERROR) break;

        if (estadoAtual == State::Q0) {
            if (ehAbertura(simbolo)) {
                //empilhamento
                pilha.push(simbolo);
            }
            else if (simbolo == ')' || simbolo == ']' || simbolo == '}') {
                //desempilhamento
                if (pilha.top() != '$' && formamPar(pilha.top(), simbolo)) {
                    pilha.pop(); // Consome o par correto
                }
                else {
                    // pilha vazia ou par errado
                    estadoAtual = State::ERROR;
                }
            }
            else {
                // caracteres que nao sao delimitadores sao ignorados.
                continue;
            }
        }
    }

    if (estadoAtual == State::Q0 && pilha.top() == '$' && pilha.size() == 1) {
        // estado final (aceitacao)
        estadoAtual = State::Q1;
    } else {
        // estado final (rejeicao)
        estadoAtual = State::ERROR;
    }

    return estadoAtual == State::Q1;
}

int main() {
    std::string entrada;

    std::cout << "====================================================\n";
    std::cout << " APD - Delimitadores Balanceados\n";
    std::cout << " Caracteres que nao sao delimitadores serao ignorados.\n";
    std::cout << " Digite a sequencia para testar ou 'sair' para parar.\n";
    std::cout << "====================================================\n\n";

    while (true) {
        std::cout << ">> ";
        if (!std::getline(std::cin, entrada)) {
            break;
        }

        // saida do terminal
        if (entrada == "sair") {
            std::cout << "Encerrando...\n";
            break;
        }

        if (processaAutomatoMultiplo(entrada)) {
            std::cout << "   [!] Resultado: ACEITO (Q1) - Delimitadores balanceados.\n\n";
        } else {
            std::cout << "   [X] Resultado: REJEITADO (Erro) - Delimitadores desbalanceados.\n\n";
        }
    }

    return 0;
}
