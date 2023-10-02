# Modbus-TCP

# Dependencias

Pra compilar o projeto, voce precisa de:
 - CMake >= 3.13

Compiladores suportados:

- Clang-cl >= 11 (MSVC)
- AppleClang 14
- GCC >= 10

# Como compilar

Tu pode compilar ou em um Docker container que tem seu Dockerfile no repositorio, ou
nativo no PC.

## Compilando nativo

Como é um projeto que usa CMake, primeiro cria-se um diretorio de build,
gera os arquivos de compilação e então, no linux se executa o make, ninja ou algo assim.
Pra compilar em sistema unix, os commandos abaixo podem ser executados:

```shell
mkdir build
cd build
cmake ..
make
```

Pra compilar em Windows, os commandos abaixo podem ser executados
```shell
mkdir build
cd build
cmake ..
cmake --build .
```

## Compiling in the Docker image

To compile in the Docker image, one must have Docker installed and build the image
locally first. After that, run a container using the image and compile the code as
if you are compiling natively.

# Structure

