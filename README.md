# TabelaHashing
Integrantes do grupo:
Marcela Cantalice;
Lucas Paraíso; 
Luiz Camello.

Descrição do projeto

O projeto consiste no desenvolvimento de um sistema de autenticação simples em linguagem C, utilizando uma tabela hash implementada do zero.O sistema simula o cadastro e login de usuários, armazenando apenas o nome de usuário e o hash da senha.A senha original não é salva.
A tabela hash foi implementada com encadeamento separado (fechado) para o tratamento de colisões, utilizando structs, alocação dinâmica (malloc/free) e funções de hash.

Funcionalidades obrigatórias
Cadastrar usuário: recebe username e senha, calcula o hash da senha e armazena na tabela.
Login: busca o usuário e valida comparando o hash da senha digitada.
Remover usuário: exclui o usuário da tabela.
Imprimir tabela: exibe as posições da tabela, mostrando os usuários armazenados e as colisões.

Requisitos técnicos
Implementação com encadeamento separado (fechado) para tratamento de colisões.
Uso das funções obrigatórias:
criaHash
insereHash
buscaHash
removeHash
liberaHash
imprimeHash
Uso de alocação dinâmica (malloc e free).
Funções de hash utilizadas:
valorString: converte o nome em valor numérico.
chaveDivisao: aplica o método da divisão para definir a posição na tabela.
hashSenha: gera o hash da senha para armazenar sem guardar o texto original.

Como compilar e executar
No Windows:
gcc projeto.c -o projeto.exe
projeto.exe

No Linux:
gcc projeto.c -o projeto
./projeto

Estrutura do código

Struct Usuario: armazena o nome, o hash da senha e o ponteiro para o próximo usuário (colisão).

Struct Hash: contém o tamanho da tabela e um vetor de ponteiros para usuários.

Função valorString: transforma o nome em número.

Função chaveDivisao: define o índice da tabela aplicando o operador módulo.

Função hashSenha: gera um hash numérico a partir da senha digitada.

Função imprimeHash: mostra todas as posições ocupadas e colisões.

O tratamento de colisões é feito por meio de listas encadeadas.

Exemplo de execução
1 - Cadastrar usuario
2 - Login
3 - Remover usuario
4 - Imprimir tabela
0 - Sair
> 1
Username: bob zip
Senha: 123
Usuario 'bob zip' cadastrado na posicao 2.
 
 



