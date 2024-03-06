# Editor de Texto Baseado em Comandos

Este projeto consiste na implementação de um editor de texto baseado em comandos de texto. O objetivo é permitir que o usuário manipule o texto através de uma série de comandos, tais como inserção, deleção, movimentação do cursor, interação com arquivos de texto, entre outros.

## Funcionamento

O editor de texto opera de forma interativa, onde o usuário insere uma sequência de comandos via entrada padrão. Cada comando modifica o texto atual e/ou a posição do cursor, sendo que apenas a linha atual do cursor é exibida após cada iteração.

### Exemplo de Comandos:

- `Itexto`: Insere a string "texto" na posição atual do texto.
- `F`: Move o cursor um caractere à frente.
- `D`: Apaga o caractere da posição atual.
- `Anome.txt`: Carrega o conteúdo do arquivo de texto "nome.txt".
- `Enome.txt`: (Sobre)escreve o conteúdo do editor no arquivo de texto "nome.txt".

Para uma lista completa de comandos disponíveis, consulte a documentação.

## Utilização

Para utilizar o editor de texto:

1. Clone este repositório para sua máquina local.
2. Compile o código fonte do programa.
3. Execute o programa compilado.
4. Insira os comandos desejados seguindo as especificações fornecidas.
5. Interaja com o editor conforme necessário.
6. Encerre o programa ao finalizar.
