# Template de projeto em C (AED-I)

Este repositorio e um template simples para exercicios em C. O programa atual imprime "Hello, World!".

## Estrutura

```
.
├── README.md
├── src/
│   └── main.c
├── build/           # executaveis compilados (criado apos o build)
└── .devcontainer/
    ├── Dockerfile
    └── devcontainer.json
```

## Compilacao

Use um compilador C (clang ou gcc). No diretorio do projeto:

```bash
mkdir -p build
clang -Wall -pedantic -o build/app src/main.c
```

## Execucao

```bash
./build/app
```

## Saida esperada

```
Hello, World!
```

## Como usar

- Edite [src/main.c](src/main.c) para iniciar seus exercicios.
- Recompile apos cada mudanca.

## Ambiente de desenvolvimento (opcional)

Este projeto inclui configuracao de Dev Container para VS Code em [.devcontainer](.devcontainer). O container usa Alpine Linux e instala `clang` e `valgrind`.

### GitHub Codespaces

Voce pode usar o Codespaces para abrir o projeto no navegador:

1. No GitHub, clique em **Code**.
2. Selecione a aba **Codespaces**.
3. Clique em **Create codespace on main**.

Ao iniciar, o ambiente ja vem configurado pelo dev container.

### Docker

Caso tenha Docker instalado na sua máquina, você pode usar o dev container localmente:

```bash
docker build -t aed-i-c -f .devcontainer/Dockerfile .
docker run --rm -it -v "$PWD":/work -w /work aed-i-c
```

Dentro do container, compile e execute normalmente:

```bash
mkdir -p build
clang -Wall -pedantic -o build/app src/main.c
./build/app
```
