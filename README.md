# Sistema de Gerenciamento de Clube de Compras
Projeto acadêmico desenvolvido em linguagem C como trabalho final da matéria de Algoritmos e Estruturas de Dados, utilizando arquivos binários para armazenar os dados do sistema. O objetivo é simular o gerenciamento de um clube de compras fictício, permitindo o cadastro de sócios, fornecedores, produtos, marcas e categorias, a assinatura ou renovação do clube de compras, a realização de pedidos e a listagem de relatórios.

## TECNOLOGIAS UTILIZADAS
- Linguagem C
- Arquivos binários (.bin)
- Dev-C++

## FUNCIONALIDADES
### Sócios
- Cadastro de Sócios - Pessoa Física ou Pessoa Jurídica
- Busca por ID
- Alteração de cadastro
- Exclusão de cadastro
- Assinatura do Clube
- Renovação da assinatura

### Fornecedores
- Cadastro de Fornecedores
- Busca por ID
- Alteração de cadastro
- Exclusão de cadastro

### Produtos
- Cadastro de produtos
- Busca por ID
- Alteração de cadastro
- Exclusão de cadastro
- Controle de estoque

### Categorias
- Cadastro de categorias
- Busca por ID
- Alteração de categorias
- Exclusão de categorias

### Marcas
- Cadastro de marcas
- Busca por ID
- Alteração de marcas
- Exclusão de marcas

### Pedidos
- Realização de pedidos
- Verificação de assinatura ativa
- Carrinho de compras com múltiplos produtos
- Atualização automática do estoque
- Cálculo do valor total
- Desconto exclusivo para sócios
- Escolha entre entrega em domicílio ou retirada presencial
- Geração automática do código do pedido

### Relatórios
- Relatórios de Sócios - todos os Sócios cadastrados, sócios com ou sem assinatura do clube, IDs cadastrados, filtrar por tipo de sócio (Pessoa Física ou Jurídica)
- Relatórios de Fornecedores - todos os fornecedores cadastrados, IDs cadastrados e contatos de fornecedores
- Relatórios de Produtos - todos os produtos cadastrados, IDs cadastrados, produtos com baixo estoque ou sem estoque, tabela de preços, filtrar por categoria ou marca
- Relatórios de Categorias - todas as categorias cadastradas, IDs cadastrados, ordenar categorias por ordem alfabética
- Relatório de Marcas - todas as marcas cadastradas, IDs cadastrados, ordenar marcas por ordem alfabética
- Relatórios de Pedidos - todos os pedidos realizados, filtrar por tipo de entrega (A Domicílio ou Retirada Presencial)

## REGRAS DE NEGÓCIO
- Cada registro (seja sócio, produto, marca etc.) deve possuir um ID único. Não é possível cadastrar nenhum registro com ID duplicado.
- Apenas sócios com assinatura ativa podem realizar pedidos.
- O estoque é atualizado automaticamente após cada compra.
- O sistema registra todas as compras realizadas em um arquivo de pedidos.
- Os sócios assinantes recebem desconto nos produtos.

## CONCEITOS UTILIZADOS
- Structs
- Vetores
- Funções
- Manipulação de arquivos binários
- CRUD (Create, Read, Update e Delete)
- Busca sequencial
- Laços de repetição
- Estruturas condicionais
- Modularização do código

## OBJETIVO DO PROJETO
Aplicar os conceitos estudados na disciplina de Algoritmos e Estruturas de Dados, principalmente manipulação de arquivos binários, estruturas de dados e desenvolvimento de um sistema completo baseado em menu.

## PRINTS DO SISTEMA

<img width="478" height="249" alt="Menu Principal" src="https://github.com/user-attachments/assets/71840a03-ba72-4451-a28b-aab5224a2d07" />
Menu Principal

<img width="529" height="266" alt="Gerenciar" src="https://github.com/user-attachments/assets/97a0494b-6ef9-442a-8afa-932bd44ef5b4" />
Menu de gerenciamento dos principais registros

<img width="534" height="229" alt="CRUD" src="https://github.com/user-attachments/assets/17aea63b-d47c-44ee-83bc-652ff950685e" />
Exemplo de CRUD

<img width="504" height="255" alt="Relatorios" src="https://github.com/user-attachments/assets/763f0fd2-cacc-47d6-b450-a5ea7b3399f4" />
Menu de Relatórios do sistema

<img width="692" height="537" alt="Relatorio Pedido 2" src="https://github.com/user-attachments/assets/86399bc6-8b57-4761-9cf3-7f63986fac36" />
Relatório de Pedido realizado por usuário assinante do Clube
