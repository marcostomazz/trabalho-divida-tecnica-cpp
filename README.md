# Trabalho — Dívida Técnica em C++

Trabalho desenvolvido para a disciplina DIM0501 — Boas Práticas de Programação, da UFRN.

## Sistema analisado

Sistema de Controle de Estoque e Vendas executado em linha de comando. O sistema permite cadastrar produtos, registrar vendas, listar produtos e identificar estoque baixo.

## Dívidas técnicas quitadas

- Remoção da senha administrativa fixa no código-fonte.
- Leitura da senha a partir do arquivo externo `config.txt`.
- Validação de quantidade positiva no registro de vendas.

## Arquivos do projeto

- `Estoque.cpp`: código-fonte do sistema.
- `config.txt`: arquivo de configuração com a senha administrativa.

## Como compilar

```bash
g++ Estoque.cpp -o estoque
