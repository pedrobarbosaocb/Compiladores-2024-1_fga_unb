# Instruções para Rodar o Analisador

## Preparativos

1. **Prepare o arquivo de entrada**:
   - Insira a string ou código que deseja testar no arquivo `input.lan`. Este arquivo deve estar no mesmo diretório onde você irá executar os comandos.

## Compilação

1. **Compile o projeto**:
   - No terminal, execute o comando abaixo para compilar o código-fonte e gerar o executável:

     ```bash
     make
     ```

   - Este comando utiliza o `Makefile` para compilar todos os arquivos necessários e criar o executável `testParser`.

## Execução

1. **Execute o analisador**:
   - Após a compilação bem-sucedida, execute o analisador usando o seguinte comando:

     ```bash
     ./testParser < input.lan
     ```

   - Este comando direciona o conteúdo do arquivo `input.lan` como entrada para o programa `testParser`.

## Exemplo

1. **Exemplo de uso**:
   - Suponha que você tenha o seguinte conteúdo no `input.lan`:

     ```
     start
     var x = 10;
     print x;
     
     ```

   - Após executar `./testParser < input.lan`, você verá a saída processada pelo analisador, mostrando os tokens identificados e suas características.
