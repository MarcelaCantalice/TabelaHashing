# Sistema de Autenticação com Tabela Hash em C

**Integrantes do grupo:**  
- Marcela Cantalice ; 
- Lucas Paraíso ; 
- Luiz Camello ; 

---

## 📌 Descrição do Projeto

Este projeto consiste no desenvolvimento de um **sistema de autenticação simples em C**, utilizando uma **tabela hash implementada do zero**.

O sistema permite cadastrar e autenticar usuários, armazenando:

- **Nome de usuário**
- **Hash da senha (senha original nunca é salva)**

Para o tratamento de colisões, foi utilizada a técnica de **encadeamento separado**, com uso de **structs**, **alocação dinâmica (malloc/free)** e **funções de hash**. As colisões são tratadas com encadeamento separado: cada posição da tabela é uma lista encadeada, e novos usuários são inseridos sempre no início da lista.

---

## 🧩 Funcionalidades

✔ **Cadastrar usuário**  
Recebe nome e senha, calcula o hash da senha e armazena na tabela hash.

✔ **Login**  
Busca o usuário e valida o acesso comparando o hash da senha digitada.

✔ **Remover usuário**  
Exclui o usuário da tabela, ajustando a lista encadeada em caso de colisão.

✔ **Imprimir tabela**  
Mostra todas as posições da tabela hash, exibindo usuários e as colisões no mesmo índice.

---

## 🛠️ Requisitos Técnicos Atendidos

- Implementação de hash com **encadeamento separado** para tratamento de colisões.  
- Uso das funções obrigatórias:
  - `criaHash`
  - `insereHash`
  - `buscaHash`
  - `removeHash`
  - `liberaHash`
  - `imprimeHash`
- Funções de hash:
  - `valorString` → converte o username para um valor numérico usando multiplicação por 31 com proteção contra overflow.
  - `chaveDivisao` → aplica método da divisão  
  - `hashSenha` → gera hash da senha (não armazena texto original)
- Uso de **alocação dinâmica** (`malloc` e `free`)

---

## 🧱 Estrutura do Código

### **Struct Usuario**
Armazena:
- `username`
- `hashSenha`
- ponteiro `prox` (para tratar colisões em lista encadeada)

### **Struct Hash**
Armazena:
- tamanho da tabela
- vetor de ponteiros para usuários

### Principais Funções

- **valorString**  
  Converte o nome de usuário em valor numérico para o hash.
  
- **chaveDivisao**  
  Calcula o índice da tabela usando o método da divisão.

- **hashSenha**  
  Gera um hash numérico a partir da senha digitada.

- **insereHash / buscaHash / removeHash**  
  CRUD completo da tabela hash.

- **imprimeHash**  
  Mostra a tabela e suas colisões.

- **liberaHash**  
  Libera toda a memória alocada dinamicamente.

---

## ▶️ Como Compilar e Executar

### **Windows (PowerShell ou VS Code)**
```bash
gcc projeto.c -o projeto.exe
.\projeto.exe

```

### **Linux**
```bash
gcc projeto.c -o projeto
./projeto
```

---

## 🖥️ Exemplo de Execução

```text
1 - Cadastrar usuário
2 - Login
3 - Remover usuário
4 - Imprimir tabela
0 - Sair
> 1

Nome de usuário: bob zip
Senha: 123

Usuário 'bob zip' cadastrado na posição 2.
```




