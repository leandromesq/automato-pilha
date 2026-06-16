# Autômato de Pilha - Delimitadores Balanceados

Este projeto implementa, em C++, um **autômato de pilha determinístico (APD)** que verifica se os delimitadores de uma entrada estão balanceados.

O programa considera os delimitadores:

```txt
( ) [ ] { }
```

Caracteres que não são delimitadores são ignorados. Assim, o autômato pode analisar tanto cadeias formadas apenas por delimitadores quanto expressões com outros símbolos, como código ou fórmulas.

## Linguagem reconhecida

Seja:

```txt
A = { '(', ')', '[', ']', '{', '}' }
```

O programa aceita uma cadeia `w` quando a sequência formada apenas pelos símbolos de `A` presentes em `w` está corretamente balanceada.

Em outras palavras:

```txt
L = { w | a projeção de w sobre A possui delimitadores balanceados }
```

Exemplos de cadeias aceitas:

```txt
""
"abc"
"()"
"[]"
"{}"
"{[()]}"
"()[]{}"
"({[]})"
"x = (a + b)"
"if (vetor[0]) { executar(); }"
```

Exemplos de cadeias rejeitadas:

```txt
"("
")"
"(()"
"())"
")(" 
"{[(])}"
"([)]"
"func([x)]"
```

## Como o autômato funciona

O autômato utiliza uma pilha para controlar os delimitadores de abertura ainda não fechados. A pilha é representada por `std::stack<char>` da biblioteca padrão do C++.

- A pilha começa com o marcador de fundo `$`.
- Ao ler um delimitador de abertura, `(`, `[` ou `{`, o autômato empilha o delimitador.
- Ao ler um delimitador de fechamento, `)`, `]` ou `}`, o autômato verifica o topo da pilha.
- Se o topo for a abertura correspondente, o autômato desempilha esse símbolo.
- Se o topo não corresponder ao fechamento lido, a cadeia é rejeitada.
- Caracteres que não são delimitadores são ignorados.
- Ao final da entrada, a cadeia é aceita somente se a pilha tiver apenas o marcador de fundo `$`.

## Diagrama do autômato

diagrama no excalidraw

## Estados

- `Q0`: estado inicial / leitura.
- `Q1`: estado final (aceitação).
- `ERROR`: estado de rejeição.

## Pré-requisitos

Para compilar o projeto, é necessário ter um compilador C++ com suporte a C++17.

Opções comuns:

- Linux/WSL: `g++`
- Windows: MinGW, MSYS2, Dev-C++, Code::Blocks ou outro ambiente com `g++`
- macOS: `clang++` ou `g++`

## Compilação e execução 

### Linux/macOS

Compilar:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o automato_pilha
```

Executar:

```bash
./automato_pilha
```

Se estiver usando `clang++` no macOS, você também pode compilar com:

```bash
clang++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o automato_pilha
```

### Windows com g++ instalado

Compilar:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o automato_pilha.exe
```

Executar no PowerShell:

```powershell
.\automato_pilha.exe
```

Executar no Prompt de Comando:

```cmd
automato_pilha.exe
```

### WSL

Entre na pasta do projeto e execute:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o automato_pilha
./automato_pilha
```

## Cadeias para teste

Ao executar o programa, digite uma cadeia e pressione `Enter`. Para encerrar o simulador, digite `sair`.

| Cadeia de entrada | Saída esperada |
|---|---|
| `{[()]}` | `ACEITO` |
| `()[]{}` | `ACEITO` |
| `if (vetor[0]) { executar(); }` | `ACEITO` |
| `abc + 123` | `ACEITO` |
| cadeia vazia | `ACEITO` |
| `{[(])}` | `REJEITADO` |
| `func([x)]` | `REJEITADO` |
| `([)]` | `REJEITADO` |
| `(()` | `REJEITADO` |
| `)(` | `REJEITADO` |

As saídas completas exibidas pelo programa são:

```txt
[!] Resultado: ACEITO (Q1) - Delimitadores balanceados.
```

ou:

```txt
[X] Resultado: REJEITADO (Erro) - Delimitadores desbalanceados.
```
