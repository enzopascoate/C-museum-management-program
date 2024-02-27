#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

// Limpa Tela
void limpaTela()
{
    system("cls || clear");
}

// Enter para continuar
void enterParaContinuar()
{
    printf("\tPressione Enter para continuar... ");
    getchar();
}
// Struct Cliente
struct Cliente
{
    char entrada[20];
    char nome[50];
    char sobrenome[50];
    int idade;
    char cidade[50];
    char genero[10];
};

// Cria Pagina

void criarPagina(const char *textoInterior)
{
    limpaTela();
    printf("\n\n\n\n\t++++|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||++++\n");
    printf("\t++++|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||++++\n");
    printf("\t++++===============================================================================================++++\n\n");
    printf("\t\t\t\t\t\t%s\n\n", textoInterior);
    printf("\t++++===============================================================================================++++\n");
    printf("\t++++|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||++++\n");
    printf("\t++++|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||++++\n\n\n\n");
}
// Ler CSV

void lerDadosCSV()
{
    FILE *registro = fopen("dados_clientes.csv", "r");

    char linha[250];

    printf("\n\tDados dos Clientes:\n\n");

    while (fgets(linha, sizeof(linha), registro) != NULL)
    {
        printf("\t%s", linha);
    }

    fclose(registro);
}
// Cadastrar Cliente
void cadastrarCliente(char tipoUsuario)
{
    criarPagina("CADASTRO DE CLIENTE");

    // Coleta os dados do cliente
    struct Cliente cliente;
    printf("\tNome do cliente: ");
    scanf("%s", cliente.nome);
    printf("\tSobrenome do cliente: ");
    scanf("%s", cliente.sobrenome);
    printf("\tAno de Nascimento do cliente: ");
    while (1)
    {
        if (scanf("%d", &cliente.idade) == 1)
        {
            break;
        }
        else
        {
            printf("\tIdade inválida. Digite um número válido: ");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
    getchar();

    char linhaGenero[50];

    int generoExiste = 1;

    while(generoExiste) {
    printf("\tGênero do cliente (Masculino ou Feminino): ");
    scanf(" %49[^\n]", linhaGenero);
    if (strcmp(linhaGenero, "Masculino") == 0 || strcmp(linhaGenero, "Feminino") == 0)
    {
        // Vê se o Gênero é válido
        strcpy(cliente.genero, linhaGenero);
        generoExiste=0;
    }
    else
    {
        printf("\tGênero inválido. Digite 'Masculino' ou 'Feminino'.\n");
    }
    getchar();

    }


    printf("\tCidade de residência do cliente: ");
    fgets(cliente.cidade, sizeof(cliente.cidade), stdin);

    // Define o valor da entrada
    int numeroEntrada = 1;
    char linha[250];

    FILE *registro = fopen("dados_clientes.csv", "r");

    while (fgets(linha, 250, registro) != NULL)
    {
        if (linha[0] == '#')  // Verifica se a linha começa com #
        {
            numeroEntrada++;
        }
    }
    fclose(registro);

    char confirmacao;
    printf("\n\tConfirmar salvamento do cadastro? (S/N): ");

    scanf(" %c", &confirmacao);

    if (confirmacao == 'S' || confirmacao == 's')
    {
        registro = fopen("dados_clientes.csv", "a");

        fprintf(registro, "#%d,%s,%s,%d,%s,%s", numeroEntrada, cliente.nome, cliente.sobrenome, cliente.idade, cliente.genero, cliente.cidade);

        fclose(registro);

        printf("\t-------------------------------------------------------------------------------------------------------");
        printf("\n\n\tDados do Cliente:\n");
        printf("\tNome: %s %s\n", cliente.nome, cliente.sobrenome);
        printf("\tData de Nascimento: %d\n", cliente.idade);
        printf("\tGênero: %s\n", cliente.genero);
        printf("\tCidade de residência: %s\n", cliente.cidade);
        printf("\t-------------------------------------------------------------------------------------------------------\n\n");

        printf("\t+++ Cadastro concluído!.\n\n");
        enterParaContinuar();
        getchar();
        menuPrincipal(tipoUsuario);
    }
    else
    {
        printf("\t--- Cadastro cancelado.\n\n");
        enterParaContinuar();
        getchar();
        menuPrincipal(tipoUsuario);
    }
}

// Excluir Entrada Cliente.
void deletarEntradaPorNumero(int numeroEntrada)
{
    FILE *arquivoOriginal = fopen("dados_clientes.csv", "r");
    if (arquivoOriginal == NULL)
    {
        printf("Erro ao abrir o arquivo de origem.\n");
        return;
    }

    FILE *arquivoTemporario = fopen("temp.csv", "w");
    if (arquivoTemporario == NULL)
    {
        fclose(arquivoOriginal);
        printf("Erro ao abrir o arquivo temporário.\n");
        return;
    }

    char linha[250];
    int numeroLinha = 0;
    int entradaEncontrada = 0;

    while (fgets(linha, sizeof(linha), arquivoOriginal) != NULL)
    {
        if (linha[0] == '#' && sscanf(linha, "#%d,", &numeroLinha) == 1)
        {
            if (numeroLinha == numeroEntrada)
            {
                entradaEncontrada = 1;
            }
            else
            {
                fputs(linha, arquivoTemporario);
            }
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemporario);

    remove("dados_clientes.csv");
    rename("temp.csv", "dados_clientes.csv");

    if (entradaEncontrada)
    {
        reorganizarNumerosEntrada();
    };
};

// Chamar função de Delete

void chamaDeletarEntrada()
{
    int verificarEntradaExiste(int numeroEntrada)
    {
        FILE *arquivoOriginal = fopen("dados_clientes.csv", "r");
        if (arquivoOriginal == NULL)
        {
            printf("Erro ao abrir o arquivo de origem.\n");
            return 0;
        }

        char linha[250];
        int numeroLinha = 0;

        while (fgets(linha, sizeof(linha), arquivoOriginal) != NULL)
        {
            if (linha[0] == '#' && sscanf(linha, "#%d,", &numeroLinha) == 1)
            {
                if (numeroLinha == numeroEntrada)
                {
                    fclose(arquivoOriginal);
                    return 1;
                }
            }
        }

        fclose(arquivoOriginal);
        return 0;
    }


    int numeroEntradaParaExcluir;
    printf("\n\tInforme o número de entrada a ser excluído: ");
    scanf("%d", &numeroEntradaParaExcluir);

    if (!verificarEntradaExiste(numeroEntradaParaExcluir))
    {
        printf("\n\tEntrada não encontrada. Nada foi excluído.\n\n");
        enterParaContinuar();
        getchar();
        return;
    }

    // Solicita Confirmação Delete
    char confirmacao;
    printf("\n\tDeseja confirmar a deleção? (S/N): ");
    scanf(" %c", &confirmacao);

    if (confirmacao == 'S' || confirmacao == 's')
    {
        deletarEntradaPorNumero(numeroEntradaParaExcluir);
        printf("\n\tCadastro excluído com sucesso.\n\n");
    }
    else
    {
        printf("\n\tA deleção foi cancelada.\n\n");
    }

    enterParaContinuar();
    getchar();
    return;
};

// Reorganizar Entradas após Delete

void reorganizarNumerosEntrada()
{
    // Abre o arquivo original
    FILE *arquivoOriginal = fopen("dados_clientes.csv", "r");
    if (arquivoOriginal == NULL)
    {
        fclose(arquivoOriginal);
        printf("Erro ao abrir o arquivo de origem.\n");
        return;
    }

    // Cria um arquivo temporário
    FILE *arquivoTemporario = fopen("temp.csv", "w");
    if (arquivoTemporario == NULL)
    {
        fclose(arquivoOriginal);
        printf("Erro ao criar o arquivo temporário.\n");
        return;
    }

    char linha[250];
    int numeroLinha = 0;
    int novoNumero = 1;

    while (fgets(linha, sizeof(linha), arquivoOriginal) != NULL)
    {
        if (linha[0] == '#' && sscanf(linha, "#%d,", &numeroLinha) == 1)
        {
            // Se a linha começa com # e tem um número de entrada substitui o número de entrada pelo novo número
            fprintf(arquivoTemporario, "#%d,%s", novoNumero, linha + 3); // pula o número antigo
            novoNumero++;
        }
        else
        {
            fputs(linha, arquivoTemporario);
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemporario);

    remove("dados_clientes.csv");
    rename("temp.csv", "dados_clientes.csv");
}



// Menu De Delete
void menuDelete(char tipoUsuario)
{
    int opcao;

    while(1)
    {
        criarPagina("Menu de Deleção de Dados");

        printf("\t0 - Retornar\n");
        printf("\t1 - Deletar Cadastro de Cliente\n");
        printf("\n");
        printf("\tSelecione uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            chamaDeletarEntrada();
            break;
        case 2:
            break;
        case 0:
            menuPrincipal(tipoUsuario);
        default:
            printf("\tOpção inválida. Tente novamente.\n");
        };
    };
};

// Tela Start
void telaStart()
{
    limpaTela();

    printf("\n\n\n\n\n\t++++|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||++++\n");
    printf("\t++++|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||++++\n");
    printf("\t++++|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||++++\n");
    printf("\t++++|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||++++\n");
    printf("\t++++===============================================================================================++++\n\n");
    printf("\t\t\t\t    SEJA BEM-VINDO AO MMS - MUSEUM MANAGEMENT SYSTEM!\n\n");
    printf("\t++++===============================================================================================++++\n");
    printf("\t++++|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||++++\n");
    printf("\t++++|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||++++\n");
    printf("\t++++|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||++++\n");
    printf("\t++++|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||++++\n\n\n\n\n\n\n\n\n");
    enterParaContinuar();
    telaLogin();
}

// Tela do Login
void telaLogin()
{
    char loginInserido[20];
    char senhaInserida[20];
    fflush(stdin);
    criarPagina("TELA DE LOGIN");
    int loginBemSucedido = 0;

    while (!loginBemSucedido)
    {
        printf("\tInsira seu login: ");
        scanf("%s", loginInserido);
        printf("\n\tInsira sua senha: ");
        scanf("%s", senhaInserida);
        if (strcmp(loginInserido, "user") == 0 && strcmp(senhaInserida, "userpassword") == 0)
        {
            loginBemSucedido = 1;
            menuPrincipal();
        }
        else if (strcmp(loginInserido, "admin") == 0 && strcmp(senhaInserida, "adminpassword") == 0)
        {
            loginBemSucedido = 1;
            menuPrincipal('a');
        }
        else
        {
            printf("\tSenha inválida, tente novamente. \n");
            telaLogin();
        }
    }
}

// Tela do Menu Principal
void menuPrincipal(char tipoUsuario)
{
    int opcao;

    while (1)
    {
        criarPagina("MENU PRINCIPAL");
        // Menu Admin
        if (tipoUsuario == 'a')
        {
            printf("\t0 - Logout\n");
            printf("\t1 - Vender Ingresso\n");
            printf("\t2 - Validar Ingresso\n");
            printf("\t3 - Cadastrar Cliente\n");
            printf("\t4 - Acessar Dados\n");
            printf("\t5 - Deletar Dados\n");
        }
        // Menu Usuario
        else
        {
            printf("\t0 - Logout\n");
            printf("\t1 - Vender Ingresso\n");
            printf("\t2 - Validar Ingresso\n");
            printf("\t3 - Cadastrar Cliente\n");
            printf("\t4 - Acessar Dados\n");
        }

        printf("\n");
        printf("\tSelecione uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 0:
            telaLogin();
            break;
        case 1:
            venderIngresso(tipoUsuario);
            break;
        case 2:
            validarIngresso(tipoUsuario);
            break;

        case 3:
            cadastrarCliente(tipoUsuario);
            break;
        case 4:
            menuBuscarDados(tipoUsuario);
            break;
        case 5:
            if (tipoUsuario == 'a')
            {
                menuDelete('a');
            }
            else
            {
                printf("\tOpção inválida. Tente novamente.\n");
            }
            break;
        default:
            printf("\tOpção inválida. Tente novamente.\n");
        }
        enterParaContinuar();
    }
}

// Gera um numero de ingresso aleatorio
long long gerarNumeroAleatorio() {
    long long parte1 = 1000000000LL;
    srand((unsigned int)time(NULL));
    long long parteAleatoria = (long long)rand() * (long long)rand();
    return parte1 + (parteAleatoria % 9000000000LL);
}

// Vender Ingressos
void venderIngresso(char tipoUsuario) {
    criarPagina("VENDA DE INGRESSO");

    int qtdIngressos;
    float valorTotal = 0.0;

    printf("\tQuantos ingressos serão vendidos? ");
    scanf("%d", &qtdIngressos);

    struct Ingresso {
        long long numeroIngresso;
        char tipoIngresso[10];
        char dataVenda[20];
    };

    // Aloca memoria p armazenar os ingressos
    struct Ingresso *ingressos = malloc(qtdIngressos * sizeof(struct Ingresso));

    for (int i = 0; i < qtdIngressos; i++) {
        float valorIngresso = 50.0;

        while (1) {
            printf("\tTipo de ingresso para o ingresso %d (inteiro, meia, isento): ", i + 1);
            scanf("%s", ingressos[i].tipoIngresso);

            if (strcmp(ingressos[i].tipoIngresso, "inteiro") == 0 || strcmp(ingressos[i].tipoIngresso, "meia") == 0 || strcmp(ingressos[i].tipoIngresso, "isento") == 0) {
                break;
            } else {
                printf("\tTipo de ingresso inválido. Por favor, insira 'inteiro', 'meia' ou 'isento'.\n");
            }
        }

        if (strcmp(ingressos[i].tipoIngresso, "meia") == 0) {
            valorIngresso = 25.0;
        } else if (strcmp(ingressos[i].tipoIngresso, "isento") == 0) {
            valorIngresso = 0.0;
        }

        // Gera código de ingresso
        ingressos[i].numeroIngresso = gerarNumeroAleatorio();

        // Pega data e hora atual
        time_t now;
        struct tm *local_time;
        time(&now);
        local_time = localtime(&now);
        strftime(ingressos[i].dataVenda, sizeof(ingressos[i].dataVenda), "%Y-%m-%d %H:%M:%S", local_time);

        valorTotal += valorIngresso;

        printf("\tIngresso %d - Código: %lld, Tipo: %s, Data da Venda: %s\n", i + 1, ingressos[i].numeroIngresso, ingressos[i].tipoIngresso, ingressos[i].dataVenda);
    }

    printf("\n\tValor total da compra: R$%.2f\n\n", valorTotal);

    char confirmacao;
    printf("\tDeseja prosseguir com a venda? (S/N): ");
    scanf(" %c", &confirmacao);

    if (confirmacao == 'S' || confirmacao == 's') {
        // Salva os ingressos apenas se a venda for confirmada
        FILE *arquivoCSV = fopen("ingressos_vendidos.csv", "a");
        if (arquivoCSV == NULL) {
            printf("Erro ao abrir o arquivo de ingressos vendidos.\n");
            return;
        }

        for (int i = 0; i < qtdIngressos; i++) {
            fprintf(arquivoCSV, "%lld - %s - %s\n", ingressos[i].numeroIngresso, ingressos[i].tipoIngresso, ingressos[i].dataVenda);
        }

        fclose(arquivoCSV);

        printf("\n\t+++ Venda realizada com sucesso!\n\n");
        enterParaContinuar();
        getchar();
        menuPrincipal(tipoUsuario);
    } else {
        printf("\n\t--- Compra cancelada.\n\n");
        enterParaContinuar();
        getchar();
        menuPrincipal(tipoUsuario);
    }

    // Libera memoria alocada p ingressos
    free(ingressos);
}

// Validacao de Ingresso
void validarIngresso(char tipoUsuario) {
    criarPagina("VALIDAÇÃO DE INGRESSO");

    long long numeroIngresso;
    int ingressoEncontrado = 0;

    printf("\n\tInsira o número do ingresso: ");
    scanf("%lld", &numeroIngresso);

    FILE *arquivoCSV = fopen("ingressos_vendidos.csv", "r");
    if (arquivoCSV == NULL) {
        printf("\n\nErro ao abrir o arquivo de ingressos vendidos.\n");
        enterParaContinuar();
        menuPrincipal(tipoUsuario);
        return;
    }

    // Cria arquivo temporário p/ armazenar registros
    FILE *tempFile = fopen("temp.csv", "w");
    if (tempFile == NULL) {
        printf("\n\nErro ao criar arquivo temporário.\n");
        fclose(arquivoCSV);
        enterParaContinuar();
        menuPrincipal(tipoUsuario);
        return;
    }

    char linha[100]; // Suponha que cada linha do arquivo tem menos de 100 caracteres

    while (fgets(linha, sizeof(linha), arquivoCSV) != NULL) {
        long long numeroLido;
        char tipoIngresso[10];
        char dataVenda[20];

        if (sscanf(linha, "%lld - %9s - %19s", &numeroLido, tipoIngresso, dataVenda) == 3) {
            // Checa se o numero existe no arquivo
            if (numeroLido == numeroIngresso) {
                ingressoEncontrado = 1;
                printf("\n\n\tAcesso liberado! O ingresso é válido.\n");
            } else {
                // Escreve apenas os ingressos que não foram validados no arquivo temporário
                fprintf(tempFile, "%lld - %s - %s\n", numeroLido, tipoIngresso, dataVenda);
            }
        }
    }

    fclose(arquivoCSV);
    fclose(tempFile);

    // Remove o arquivo original e renomeia o arquivo temporário apenas se um ingresso for encontrado
    if (ingressoEncontrado) {
        if (remove("ingressos_vendidos.csv") != 0) {
            printf("\n\nErro ao remover o arquivo original.\n");
        }
        if (rename("temp.csv", "ingressos_vendidos.csv") != 0) {
            printf("\n\n\tErro ao renomear o arquivo temporário.\n");
        }
    } else {
        printf("\n\n\tAcesso negado! O ingresso inserido não é válido.\n\n");
        // Remove o arquivo temporário se nenhum ingresso for encontrado
        if (remove("temp.csv") != 0) {
            printf("\n\n\tErro ao remover o arquivo temporário.\n");
        }
    }

    enterParaContinuar();
    getchar();
    menuPrincipal(tipoUsuario);
}

// Menu Principal de Busca de Dados
void menuBuscarDados(char tipoUsuario)
{
    int opcao;

    while (1)
    {
        criarPagina("BUSCA DE DADOS");

        printf("\t1 - Dados de Clientes\n");
        printf("\t0 - Voltar ao Menu Principal\n\n");
        printf("\tSelecione uma opção:");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            buscarDadosClientes();
            break;
        case 2:
            break;
        case 0:
            menuPrincipal(tipoUsuario);
        default:
            printf("\tOpção inválida. Tente novamente.\n");
        }
    }
}

// Menu de Dados de Clientes

void buscarDadosClientes()
{
    int stay=1;
    int numFiltros = 0;

    while (stay)
    {
        criarPagina("BUSCA POR DADOS DE CLIENTES");

        printf("\t1 - Busca Filtrada\n");
        printf("\t2 - Exibir Registro Geral\n");
        printf("\t0 - Retroceder\n\n");
        printf("\tSelecione uma opção:");

        int opcaoBusca;
        scanf("%d", &opcaoBusca);

        switch (opcaoBusca)
        {
        case 0:
            stay=0;
            break;
        case 1:
            buscaClientesFiltrada();
            break;
        case 2:
            registroGeralClientes();
            break;
        default:
            printf("\tOpção inválida. Tente novamente.\n");
        }
    }
}

// Registro Geral Clientes

void registroGeralClientes()
{
    limpaTela();
    lerDadosCSV();
    enterParaContinuar();
    getchar();
}

// Filtra Clientes
void filtrarEntradas(int filtro)
{
    limpaTela();
    FILE *registro = fopen("dados_clientes.csv", "r");
    char linha[250];

    if (registro == NULL)
    {
        fclose(registro);
        printf("Erro ao abrir o arquivo de registro.\n");
        return;
    }

    printf("\n\tResultados do filtro:\n\n");

    int numeroEntrada;
    char nome[50];
    char sobrenome[50];
    int anoNascimento;
    char genero[50];
    char cidade[50];

    switch (filtro)
    {
    case 1: // Filtra por Entrada
        printf("\n\tDigite o número de entrada a ser filtrado: ");
        scanf("%d", &numeroEntrada);

        while (fgets(linha, sizeof(linha), registro) != NULL)
        {
            int entrada;
            if (sscanf(linha, "#%d,", &entrada) == 1 && entrada == numeroEntrada)
            {
                printf("\n\t%s", linha);
            }
        }
        enterParaContinuar();
        getchar();
        fclose(registro);
        break;

    case 2: // Filtra por Nome
        printf("\n\tDigite o nome a ser filtrado: ");
        scanf(" %49[^\n]", nome);

        while (fgets(linha, sizeof(linha), registro) != NULL)
        {
            char nomeLido[50];
            if (sscanf(linha, "#%*d,%49[^,],", nomeLido) == 1 && strstr(nomeLido, nome) != NULL)
            {
                printf("\n\t%s", linha);
            }
        }
        enterParaContinuar();
        getchar();
        fclose(registro);
        break;

    case 3: // Filtra por Sobrenome
        printf("\n\tDigite o sobrenome a ser filtrado: ");
        scanf(" %49[^\n]", sobrenome);

        while (fgets(linha, sizeof(linha), registro) != NULL)
        {
            char sobrenomeLido[50];
            if (sscanf(linha, "#%*d,%*[^,],%49[^,],", sobrenomeLido) == 1 && strstr(sobrenomeLido, sobrenome) != NULL)
            {
                printf("\n\t%s", linha);
            }
        }
        enterParaContinuar();
        getchar();
        fclose(registro);
        break;

    case 4: // Filtra por Ano de Nascimento
        printf("\n\tDigite o ano de nascimento a ser filtrado: ");
        scanf("%d", &anoNascimento);

        while (fgets(linha, sizeof(linha), registro) != NULL)
        {
            int anoLido;
            if (sscanf(linha, "#%*d,%*[^,],%*[^,],%d,", &anoLido) == 1 && anoLido == anoNascimento)
            {
                printf("\n\t%s", linha);
            }
        }
        enterParaContinuar();
        getchar();
        fclose(registro);
        break;

    case 5: // Filtra por Gênero
        printf("\n\tDigite o gênero a ser filtrado: ");
        scanf(" %49[^\n]", genero);

        while (fgets(linha, sizeof(linha), registro) != NULL)
        {
            char generoLido[50];
            if (sscanf(linha, "#%*d,%*[^,],%*[^,],%*d,%49[^,],", generoLido) == 1 && strcmp(generoLido, genero) == 0)
            {
                printf("\n\t%s", linha);
            }
        }
        enterParaContinuar();
        getchar();
        fclose(registro);
        break;

    case 6: // Filtra por Cidade
        printf("\n\tDigite a cidade a ser filtrada: ");
        scanf(" %49[^\n]", cidade);

        while (fgets(linha, sizeof(linha), registro) != NULL)
        {
            char cidadeLida[50];
            if (sscanf(linha, "#%*d,%*[^,],%*[^,],%*d,%*[^,],%49[^,],", cidadeLida) == 1 && strstr(cidadeLida, cidade) != NULL)
            {
                printf("\n\t%s", linha);
            }
        }
        enterParaContinuar();
        getchar();
        fclose(registro);
        break;

    default:
        printf("Critério de filtro inválido.\n");
    }
}

// Busca por Clientes com Filtros

void buscaClientesFiltrada()
{
    int stay = 1;
    while (stay)
    {
        criarPagina("BUSCA POR CLIENTES FILTRADA");
        printf("\tSelecione um filtro para a busca (0 para cancelar): \n\n");
        printf("\t1 - Entrada\n");
        printf("\t2 - Nome\n");
        printf("\t3 - Sobrenome\n");
        printf("\t4 - Ano de Nascimento\n");
        printf("\t5 - Gênero\n");
        printf("\t6 - Cidade de Residência\n");
        printf("\n\tSelecione uma opção: ");

        int opcaoFiltro;
        scanf("%d", &opcaoFiltro);

        switch (opcaoFiltro)
        {
        case 0:
            stay=0;
            break;
        default:
            filtrarEntradas(opcaoFiltro);
        }
    }

    enterParaContinuar();
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    telaStart();
    return 0;
}
