#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <dirent.h>

#define MAX_CLIENTES 100
#define MAX_PRODUTOS 100
#define MAX_PEDIDOS 10
#define MAX_FORNECEDORES 50

int user_type = -1;

typedef struct {
    char nome[50];
    char endereco[100];
    char telefone[15];
    char cpf[15];
    char intolerancia[50];
    int membro;
    int id;
    float taxa;
} Cliente;

typedef struct {
    char nome[50];
    float preco;
    int quantidade;
    char descricao[100];
    char tipo[20];
} Produto;

typedef struct {
    char nome[50];
    char cnpj[20];
    char telefone[15];
    char endereco[100];
} Fornecedor;

typedef struct {
    char nomeCliente[50];
    char nomeProduto[50];
    int quantidade;
    float precoTotal;
    char dataHora[50];
    float precoBruto;
    float desconto;
} Pedido;

Cliente clientes[MAX_CLIENTES];
Produto produtos[MAX_PRODUTOS];
Fornecedor fornecedores[MAX_FORNECEDORES];
Pedido pedidos[MAX_CLIENTES][MAX_PEDIDOS];
int numClientes = 0;
int numProdutos = 0;
int numFornecedores = 0;
int contadorVegano = 0;
int contadorLactose = 0;
int contadorGluten = 0;
int numPedidos[MAX_CLIENTES] = {0};

void mostrarDesignInicial() {
    printf("* ##   ##    ###     #####   ##   ##  ######       ##   ##   ######  #####      ###    *\n");
    printf("* ###  ##   ## ##      ##    ##   ##  ###  ##      ##   ##     ##    ##  ##    ## ##   *\n");
    printf("* #### ##  ##   ##     ##    ##   ##  ##   ##      ##   ##     ##    ##   ##  ##   ##  *\n");
    printf("* #######  ##   ##     ##    ##   ##  ##  ##       ### ###     ##    ##   ##  ##   ##  *\n");
    printf("* ## ####  #######     ##    ##   ##  #####         #####      ##    ##   ##  #######  *\n");
    printf("* ##  ###  ##   ##     ##    ##   ##  ## ###         ###       ##    ##  ##   ##   ##  *\n");
    printf("* ##   ##  ##   ##     ##     #####   ##  ###         #      ######  #####    ##   ##  *\n");
}

// Função para remover acentos e caracteres especiais
void removerAcentos(char *str) {
    int i = 0, j = 0;
    while (str[i]) {
        if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || str[i] == ' ' || (str[i] >= '0' && str[i] <= '9')) {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

void salvarDadosClienteEmArquivo(Cliente cliente) {
    char filename[100];
    snprintf(filename, sizeof(filename), "%s.txt", cliente.nome);
    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        fprintf(file, "Nome: %s\n", cliente.nome);
        fprintf(file, "Endereco: %s\n", cliente.endereco);
        fprintf(file, "Telefone: %s\n", cliente.telefone);
        fprintf(file, "CPF: %s\n", cliente.cpf);
        fprintf(file, "Intolerancias: %s\n", cliente.intolerancia);
        fprintf(file, "Membro do Clube: %s\n", cliente.membro ? "Sim" : "Nao");
        fclose(file);
    }
}

void cadastrarCliente() {
    if (numClientes >= MAX_CLIENTES) {
        printf("Limite de clientes atingido.\n");
        return;
    }
    printf("\n");
    printf("### CADASTRO-CLIENTE ###\n");
    printf("Digite o nome do cliente: ");
    fgets(clientes[numClientes].nome, sizeof(clientes[numClientes].nome), stdin);
    clientes[numClientes].nome[strcspn(clientes[numClientes].nome, "\n")] = '\0';
    removerAcentos(clientes[numClientes].nome);

    printf("Digite o endereco do cliente: ");
    fgets(clientes[numClientes].endereco, sizeof(clientes[numClientes].endereco), stdin);
    clientes[numClientes].endereco[strcspn(clientes[numClientes].endereco, "\n")] = '\0';

    printf("Digite o telefone do cliente: ");
    fgets(clientes[numClientes].telefone, sizeof(clientes[numClientes].telefone), stdin);
    clientes[numClientes].telefone[strcspn(clientes[numClientes].telefone, "\n")] = '\0';

    printf("Digite as intolerancias alimentares do cliente: ");
    fgets(clientes[numClientes].intolerancia, sizeof(clientes[numClientes].intolerancia), stdin);
    clientes[numClientes].intolerancia[strcspn(clientes[numClientes].intolerancia, "\n")] = '\0';

    printf("\n");
    printf("Deseja se inscrever no clube de membros da loja? (1 - Sim / 0 - Nao): ");
    scanf("%d", &clientes[numClientes].membro);
    getchar();

    if (clientes[numClientes].membro == 1) {
        printf("Beneficios do clube de membros:\n");
        printf("- Desconto de 5%% em todas as compras;\n");
        printf("- Recebimento de promocoes exclusivas;\n");
        printf("- Recebimento de novidades por email;\n");
        printf("\n");
        printf("Ha uma taxa de R$29.99 por mes para participar do clube de membros.\n");
        printf("Voce confirma a inscricao no clube? (1 - Sim / 0 - Nao): ");
        int confirmacao;
        scanf("%d", &confirmacao);
        getchar();
        if (confirmacao == 1) {
            clientes[numClientes].taxa = 29.99;
            printf("Digite o CPF do cliente: ");
            fgets(clientes[numClientes].cpf, sizeof(clientes[numClientes].cpf), stdin);
            clientes[numClientes].cpf[strcspn(clientes[numClientes].cpf, "\n")] = '\0';
        } else {
            clientes[numClientes].membro = 0;
        }
    }

    clientes[numClientes].id = numClientes + 1;
    printf("Cliente cadastrado com sucesso!\n");
    printf("\n");

    salvarDadosClienteEmArquivo(clientes[numClientes]);

    numClientes++;
}

void cadastrarProduto() {
    if (numProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido.\n");
        return;
    }
    printf("\n");
    printf("### CADASTRO-PRODUTO ###\n");
    printf("Digite o nome do produto: ");
    fgets(produtos[numProdutos].nome, sizeof(produtos[numProdutos].nome), stdin);
    produtos[numProdutos].nome[strcspn(produtos[numProdutos].nome, "\n")] = '\0';
    removerAcentos(produtos[numProdutos].nome);

    printf("Digite a descricao do produto: ");
    fgets(produtos[numProdutos].descricao, sizeof(produtos[numProdutos].descricao), stdin);
    produtos[numProdutos].descricao[strcspn(produtos[numProdutos].descricao, "\n")] = '\0';

    printf("Digite o preco do produto: ");
    scanf("%f", &produtos[numProdutos].preco);
    getchar();

    printf("Digite a quantidade a ser reabastecida: ");
    scanf("%d", &produtos[numProdutos].quantidade);
    getchar();

    printf("Escolha em qual lista o produto sera adicionado:\n");
    printf("1. Vegano\n");
    printf("2. Sem Lactose\n");
    printf("3. Sem Gluten\n");
    int escolha;
    scanf("%d", &escolha);
    getchar();

    switch (escolha) {
        case 1:
            strcpy(produtos[numProdutos].tipo, "Vegano");
            contadorVegano += produtos[numProdutos].quantidade;
            break;
        case 2:
            strcpy(produtos[numProdutos].tipo, "Sem Lactose");
            contadorLactose += produtos[numProdutos].quantidade;
            break;
        case 3:
            strcpy(produtos[numProdutos].tipo, "Sem Gluten");
            contadorGluten += produtos[numProdutos].quantidade;
            break;
        default:
            printf("Opcao invalida.\n");
            break;
    }

    printf("Produto reabastecido com sucesso!\n");

    // Salvar dados do produto em um arquivo
    char filename[100];
    snprintf(filename, sizeof(filename), "produto_%s.txt", produtos[numProdutos].nome);
    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        fprintf(file, "Nome: %s\n", produtos[numProdutos].nome);
        fprintf(file, "Descricao: %s\n", produtos[numProdutos].descricao);
        fprintf(file, "Preco: R$%.2f\n", produtos[numProdutos].preco);
        fprintf(file, "Quantidade: %d\n", produtos[numProdutos].quantidade);
        fprintf(file, "Tipo: %s\n", produtos[numProdutos].tipo);
        fclose(file);
    }

    numProdutos++;
}

void cadastrarFornecedor() {
    if (numFornecedores >= MAX_FORNECEDORES) {
        printf("Limite de fornecedores atingido.\n");
        return;
    }

    printf("Digite o nome do fornecedor: ");
    fgets(fornecedores[numFornecedores].nome, sizeof(fornecedores[numFornecedores].nome), stdin);
    fornecedores[numFornecedores].nome[strcspn(fornecedores[numFornecedores].nome, "\n")] = '\0';

    printf("Digite o CNPJ do fornecedor: ");
    fgets(fornecedores[numFornecedores].cnpj, sizeof(fornecedores[numFornecedores].cnpj), stdin);
    fornecedores[numFornecedores].cnpj[strcspn(fornecedores[numFornecedores].cnpj, "\n")] = '\0';

    printf("Digite o telefone do fornecedor: ");
    fgets(fornecedores[numFornecedores].telefone, sizeof(fornecedores[numFornecedores].telefone), stdin);
    fornecedores[numFornecedores].telefone[strcspn(fornecedores[numFornecedores].telefone, "\n")] = '\0';

    printf("Digite o endereco do fornecedor: ");
    fgets(fornecedores[numFornecedores].endereco, sizeof(fornecedores[numFornecedores].endereco), stdin);
    fornecedores[numFornecedores].endereco[strcspn(fornecedores[numFornecedores].endereco, "\n")] = '\0';

    printf("Fornecedor cadastrado com sucesso!\n");

    numFornecedores++;
}

void processarCompra() {
    printf("\n");
    printf("### PROCESSAR-VENDA ###\n");
    printf("Digite o nome do cliente: ");
    char nomeCliente[50];
    fgets(nomeCliente, sizeof(nomeCliente), stdin);
    nomeCliente[strcspn(nomeCliente, "\n")] = '\0';
    removerAcentos(nomeCliente);

    int clienteEncontrado = 0;
    int idCliente;
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].nome, nomeCliente) == 0) {
            clienteEncontrado = 1;
            idCliente = i;
            break;
        }
    }

    if (!clienteEncontrado) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    printf("Digite o nome do produto: ");
    char nomeProduto[50];
    fgets(nomeProduto, sizeof(nomeProduto), stdin);
    nomeProduto[strcspn(nomeProduto, "\n")] = '\0';
    removerAcentos(nomeProduto);

    int produtoEncontrado = 0;
    int idProduto;
    for (int i = 0; i < numProdutos; i++) {
        if (strcmp(produtos[i].nome, nomeProduto) == 0) {
            produtoEncontrado = 1;
            idProduto = i;
            break;
        }
    }

    if (!produtoEncontrado) {
        printf("Produto nao encontrado.\n");
        return;
    }

    printf("Digite a quantidade a ser comprada: ");
    int quantidade;
    scanf("%d", &quantidade);
    getchar();

    if (quantidade > produtos[idProduto].quantidade) {
        printf("Quantidade indisponivel.\n");
        return;
    }

    produtos[idProduto].quantidade -= quantidade;

    float precoTotal = quantidade * produtos[idProduto].preco;
    float desconto = 0;

    if (clientes[idCliente].membro) {
        desconto = precoTotal * 0.05;
        precoTotal -= desconto;
    }

    pedidos[idCliente][numPedidos[idCliente]].precoBruto = quantidade * produtos[idProduto].preco;
    pedidos[idCliente][numPedidos[idCliente]].desconto = desconto;
    pedidos[idCliente][numPedidos[idCliente]].precoTotal = precoTotal;
    strcpy(pedidos[idCliente][numPedidos[idCliente]].nomeCliente, nomeCliente);
    strcpy(pedidos[idCliente][numPedidos[idCliente]].nomeProduto, nomeProduto);
    pedidos[idCliente][numPedidos[idCliente]].quantidade = quantidade;

    time_t agora = time(NULL);
    struct tm *t = localtime(&agora);
    strftime(pedidos[idCliente][numPedidos[idCliente]].dataHora, sizeof(pedidos[idCliente][numPedidos[idCliente]].dataHora), "%Y-%m-%d %H:%M:%S", t);

    printf("\n");
    printf("Compra realizada com sucesso!\n");
    printf("\n=========================================\n");
    printf("||                                     ||\n");
    printf("||         COMPROVANTE DA COMPRA        ||\n");
    printf("||                                     ||\n");
    printf("=========================================\n");
    printf("Cliente: %s\n", pedidos[idCliente][numPedidos[idCliente]].nomeCliente);
    printf("Produto: %s\n", pedidos[idCliente][numPedidos[idCliente]].nomeProduto);
    printf("Quantidade: %d\n", pedidos[idCliente][numPedidos[idCliente]].quantidade);
    printf("Preco Bruto: R$%.2f\n", pedidos[idCliente][numPedidos[idCliente]].precoBruto);
    printf("Desconto: R$%.2f\n", pedidos[idCliente][numPedidos[idCliente]].desconto);
    printf("Preco Total: R$%.2f\n", pedidos[idCliente][numPedidos[idCliente]].precoTotal);
    printf("Data e Hora: %s\n", pedidos[idCliente][numPedidos[idCliente]].dataHora);
    printf("\n");

    numPedidos[idCliente]++;
}

void listarProdutos() {
    printf("Produtos Disponiveis:\n");
    for (int i = 0; i < numProdutos; i++) {
        printf("Nome: %s\n", produtos[i].nome);
        printf("Descricao: %s\n", produtos[i].descricao);
        printf("Preco: R$%.2f\n", produtos[i].preco);
        printf("Quantidade: %d\n", produtos[i].quantidade);
        printf("Tipo: %s\n", produtos[i].tipo);
        printf("------------------------------\n");
    }
}

void listarFornecedores() {
    printf("Fornecedores Cadastrados:\n");
    for (int i = 0; i < numFornecedores; i++) {
        printf("Nome: %s\n", fornecedores[i].nome);
        printf("CNPJ: %s\n", fornecedores[i].cnpj);
        printf("Telefone: %s\n", fornecedores[i].telefone);
        printf("Endereco: %s\n", fornecedores[i].endereco);
        printf("------------------------------\n");
    }
}

void listarPedidosCliente() {
    printf("Digite o nome do cliente: ");
    char nomeCliente[50];
    fgets(nomeCliente, sizeof(nomeCliente), stdin);
    nomeCliente[strcspn(nomeCliente, "\n")] = '\0';
    removerAcentos(nomeCliente);

    int clienteEncontrado = 0;
    int idCliente;
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].nome, nomeCliente) == 0) {
            clienteEncontrado = 1;
            idCliente = i;
            break;
        }
    }

    if (!clienteEncontrado) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    printf("Pedidos do Cliente %s:\n", nomeCliente);
    for (int i = 0; i < numPedidos[idCliente]; i++) {
        printf("Produto: %s\n", pedidos[idCliente][i].nomeProduto);
        printf("Quantidade: %d\n", pedidos[idCliente][i].quantidade);
        printf("Preco Total: R$%.2f\n", pedidos[idCliente][i].precoTotal);
        printf("Data e Hora: %s\n", pedidos[idCliente][i].dataHora);
        printf("------------------------------\n");
    }
}

void consultarCliente() {
    printf("Digite o nome do cliente: ");
    char nomeCliente[50];
    fgets(nomeCliente, sizeof(nomeCliente), stdin);
    nomeCliente[strcspn(nomeCliente, "\n")] = '\0';
    removerAcentos(nomeCliente);

    char filename[100];
    snprintf(filename, sizeof(filename), "%s.txt", nomeCliente);
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        char linha[200];
        while (fgets(linha, sizeof(linha), file) != NULL) {
            printf("%s", linha);
        }
        fclose(file);
    } else {
        printf("Cliente nao encontrado.\n");
    }
}

void consultarUltimoPedido() {
    printf("\n");
    printf("\n=========================================\n");
    printf("### ULTIMO-PEDIDO ###\n");
    printf("\n=========================================\n");
    printf("Digite o nome do cliente: ");
    char nomeCliente[50];
    fgets(nomeCliente, sizeof(nomeCliente), stdin);
    nomeCliente[strcspn(nomeCliente, "\n")] = '\0';
    removerAcentos(nomeCliente);

    int clienteEncontrado = 0;
    int idCliente;
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].nome, nomeCliente) == 0) {
            clienteEncontrado = 1;
            idCliente = i;
            break;
        }
    }

    if (!clienteEncontrado) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    if (numPedidos[idCliente] == 0) {
        printf("Nenhum pedido encontrado para este cliente.\n");
        return;
    }

    printf("Ultimo Pedido do Cliente %s:\n", nomeCliente);
    printf("Produto: %s\n", pedidos[idCliente][numPedidos[idCliente] - 1].nomeProduto);
    printf("Quantidade: %d\n", pedidos[idCliente][numPedidos[idCliente] - 1].quantidade);
    printf("Preco Total: R$%.2f\n", pedidos[idCliente][numPedidos[idCliente] - 1].precoTotal);
    printf("Data e Hora: %s\n", pedidos[idCliente][numPedidos[idCliente] - 1].dataHora);
}


void mostrarMenuAdministrador() {
    printf("### MENU ADMINISTRADOR ###\n");
    printf("1. Cadastrar Cliente\n");
    printf("2. Cadastrar Produto\n");
    printf("3. Cadastrar Fornecedor\n");
    printf("4. Listar Produtos\n");
    printf("5. Listar Fornecedores\n");
    printf("6. Voltar ao Menu Principal\n");
}

void mostrarMenuCliente() {
    printf("### MENU CLIENTE ###\n");
    printf("1. Processar Compra\n");
    printf("2. Listar Produtos\n");
    printf("3. Consultar Cliente\n");
    printf("4. Consultar Ultimo Pedido\n");
    printf("5. Cadastrar-se\n");
    printf("6. Voltar ao Menu Principal\n");
}

void menuPrincipal() {
    while (1) {
        printf("\n");
        mostrarDesignInicial();
        printf("\n");

        printf("Digite o numero correspondente ao seu tipo de usuario:\n");
        printf("1. Administrador\n");
        printf("2. Cliente\n");
        printf("0. Sair\n");

        scanf("%d", &user_type);
        getchar();

        switch (user_type) {
            case 1:
                while (1) {
                    int opcaoAdmin;
                    mostrarMenuAdministrador();
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opcaoAdmin);
                    getchar();

                    switch (opcaoAdmin) {
                        case 1:
                            cadastrarCliente();
                            break;
                        case 2:
                            cadastrarProduto();
                            break;
                        case 3:
                            cadastrarFornecedor();
                            break;
                        case 4:
                            listarProdutos();
                            break;
                        case 5:
                            listarFornecedores();
                            break;
                        case 6:
                            printf("Voltando ao menu principal...\n");
                            break;
                        default:
                            printf("Opcao invalida.\n");
                            break;
                    }

                    if (opcaoAdmin == 6) {
                        break;
                    }
                }
                break;
            case 2:
                while (1) {
                    int opcaoCliente;
                    mostrarMenuCliente();
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opcaoCliente);
                    getchar();

                    switch (opcaoCliente) {
                        case 1:
                            processarCompra();
                            break;
                        case 2:
                            listarProdutos();
                            break;
                        case 3:
                            consultarCliente();
                            break;
                        case 4:
                            consultarUltimoPedido();
                            break;
                        case 5:
                            cadastrarCliente();
                            break;
                        case 6:
                            printf("Voltando ao menu principal...\n");
                            break;
                        default:
                            printf("Opcao invalida.\n");
                            break;
                    }

                    if (opcaoCliente == 5) {
                        break;
                    }
                }
                break;
            case 0:
                printf("Saindo...\n");
                exit(0);
            default:
                printf("Opcao invalida.\n");
                break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    menuPrincipal();

    return 0;
}
