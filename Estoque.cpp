// Sistema de Controle de Estoque e Vendas
// versao 1.1 - refatoracao de itens prioritarios de divida tecnica

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

using namespace std;

const string ARQUIVO_CONFIGS = "config.txt";

struct Produto {
    string nome;
    double preco;
    int qtd;
};

vector<Produto> produtos;

string carregar_senha_admin() {
    ifstream arquivo(ARQUIVO_CONFIGS);
    string senha;

    if (!arquivo.is_open()) {
        throw runtime_error("Nao foi possivel abrir o arquivo de configuracao.");
    }

    if (!getline(arquivo, senha) || senha.empty()) {
        throw runtime_error("Senha administrativa nao encontrada no arquivo.");
    }

    if (!senha.empty() && senha.back() == '\r') {
        senha.pop_back();
    }

    return senha;
}

// funcao que adiciona produto
void add(string n, double p, int q) {
    static vector<string> hist;   // historico
    Produto prod;
    prod.nome = n;
    prod.preco = p;
    prod.qtd = q;
    produtos.push_back(prod);
    hist.push_back(n);
    cout << "Produto adicionado!" << endl;
}

double vender(string nome, int quantidade) {
    if (quantidade <= 0) {
        cout << "Erro: a quantidade deve ser maior que zero." << endl;
        return 0.0;
    }

    for (int i = 0; i < produtos.size(); i++) {
        if (produtos[i].nome == nome) {
            if (produtos[i].qtd >= quantidade) {
                produtos[i].qtd = produtos[i].qtd - quantidade;
                double total = produtos[i].preco * quantidade;

                // desconto pra compras grandes
                if (total > 100) {
                    total = total - total * 0.1;
                }

                cout << "Venda realizada. Total: " << total << endl;
                return total;
            } else {
                cout << "Estoque insuficiente" << endl;
                return 0;
            }
        }
    }

    cout << "Produto nao encontrado" << endl;
    return 0;
}

// calcula o total de uma compra (usado no relatorio)
double calcular_total(double preco, int quantidade) {
    double t = preco * quantidade;

    if (t > 200) {
        t = t - t * 0.15;
    }

    return t;
}

void listar() {
    cout << "=== PRODUTOS ===" << endl;

    for (int i = 0; i < produtos.size(); i++) {
        cout << produtos[i].nome << " - R$" << produtos[i].preco
             << " - qtd: " << produtos[i].qtd << endl;
    }
}

void relatorio_estoque_baixo() {
    cout << "=== ESTOQUE BAIXO ===" << endl;

    for (int i = 0; i < produtos.size(); i++) {
        if (produtos[i].qtd < 5) {
            cout << produtos[i].nome << " esta com estoque baixo ("
                 << produtos[i].qtd << ")" << endl;
        }
    }
}

void relatorio_vendas() {
    // TODO: implementar de verdade
}

int main() {
    while (true) {
        cout << "\n1-Cadastrar  2-Vender  3-Listar  4-Estoque baixo  5-Admin  0-Sair" << endl;
        cout << "Opcao: ";

        string op;
        cin >> op;

        if (op == "1") {
            string n;
            double p;
            int q;

            cout << "Nome: ";
            cin >> n;

            cout << "Preco: ";
            cin >> p;

            cout << "Qtd: ";
            cin >> q;

            add(n, p, q);

        } else if (op == "2") {
            string n;
            int q;

            cout << "Nome do produto: ";
            cin >> n;

            cout << "Quantidade: ";
            cin >> q;

            vender(n, q);

        } else if (op == "3") {
            listar();

        } else if (op == "4") {
            relatorio_estoque_baixo();

        } else if (op == "5") {
            string s;

            cout << "Senha: ";
            cin >> s;

            try {
                string senha_correta = carregar_senha_admin();

                if (s == senha_correta) {
                    cout << "Acesso liberado" << endl;
                } else {
                    cout << "Senha errada" << endl;
                }
            } catch (const exception& erro) {
                cerr << "Erro de configuracao: " << erro.what() << endl;
            }

        } else if (op == "0") {
            break;

        } else {
            cout << "Opcao invalida" << endl;
        }
    }

    return 0;
}
