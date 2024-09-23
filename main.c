#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EQUIPES 16
#define MAX_JOGOS 32
#define MAX_JOGADORES 1 // mudei a variavel pra ficar mais facil testar - taina
#define ARQUIVO_EQUIPES "equipes.dat"
#define ARQUIVO_JOGOS "jogos.dat"

// struct para armazenar dados de um jogador
typedef struct {
    char nome[50];
    int numero;
    int idade;
    int gols;
} Jogador;

//struct para armazenar dados de uma equipe
typedef struct {
    char nome[50];
    char treinador[50];
    Jogador jogadores[MAX_JOGADORES];
    int gols;
} Equipe;

//struct para armazenar dados de um jogo
typedef struct {
    char equipe1[50];
    char equipe2[50];
    int gols1;
    int gols2;
} Jogo;

// inicializar as variaveis globais
Equipe equipes[MAX_EQUIPES]; // vetor para armazenar as equipes
Jogo jogos[MAX_JOGOS]; // vetor para armazenar os jogos
int num_equipes = 0; // numero de equipes cadastradas
int num_jogos = 0; // numero de jogos cadastrados

// funcoes para carregar e salvar dados
// Adicionei 2 funcoes a mais em relaÃ§Ã£o aos jogos - Taina
void carregarDadosJogos();
void salvarDadosJogos();
void carregarDadosEquipes();
void salvarDadosEquipes();

void exibirEstatisticas(); //funÃ§Ã£o para exibir estatÃ­sticas

void cadastrarEquipe(); // funcao para cadastrar uma nova equipe

void visualizarEquipes(); //funcao para visualizar as equipes cadastradas

void alterarEquipe(); //funcao para alterar os dados de uma equipe

void excluirEquipe(); //funcao para excluir uma equipe

void cadastrarJogo(); //funcao para cadastrar um novo jogo

void visualizarJogos(); //funcao para visualizar os jogos cadastrados

void alterarJogo(); //funcao para alterar os dados de um jogo

void excluirJogo(); //funcao para excluir um jogo

void sortearJogos(); //funcao para visualizar o sorteio dos jogos de acordo com as equipes que estao cadastradas no sistema.

void chavamentoConfrontos(); //funcao para acompanhar as classificacoes da equipe cadastrada e das outras a cada jogo que passa.

void desempate(); // funcao para desempatar duas equipes que estejam em uma mesma condicao

void classificados(); // funcao para visualizar em forma de tabela a posiÃ§Ã£o final das equipes apÃ³s o encerramento do torneio.

void listarDados(); // funcao que permite que o usuario visualize os dados das equipes participantes do torneio, dos jogos e da classificacao de cada fase.

void pesquisar(); // funcao para pesquisar os dados de uma equipe, jogador, jogos ou resultados

/*
nota: pensei em organizar todas as funcoes na main, mas acredito que iria ficar muita informacao dentro dela, entao decidi criar 4 funcoes de menu para organizar melhor o codigo.
*/

void menuEquipes();
void menuJogos();
void menuEstatiscas();
void menuPrincipal();

void limparTela(); // funcao pra deixar o terminal limpo

int main() {
    carregarDadosEquipes();
    carregarDadosJogos();
    menuPrincipal();
    salvarDadosEquipes();
    salvarDadosJogos();
    return 0;
}

void cadastrarEquipe() { //primeiro requisito

// do while - tratamento 
        if(num_equipes >= MAX_EQUIPES){
            printf("MAXIMO DE EQUIPES ATINGIDO.");
            return;
        }
        Equipe novaEquipe;
        limparTela();
        printf("Digite o nome da sua equipe: \n");
        scanf(" %[^\n]", novaEquipe.nome);
        printf("Digite o nome do treinador da sua equipe: \n");
        scanf(" %[^\n]", novaEquipe.treinador);

        for(int i = 0; i<MAX_JOGADORES; i++){
            limparTela();
            printf("Digite o nome do jogador %d: ",i+1);
            scanf(" %[^\n]", novaEquipe.jogadores[i].nome);
            printf("Digite a numero do jogador: ");
            scanf(" %d",&novaEquipe.jogadores[i].numero);
            printf("Digite a idade do jogador: ");
            scanf(" %d",&novaEquipe.jogadores[i].idade);
            novaEquipe.jogadores[i].gols = 0;
        }

        novaEquipe.gols = 0;
        equipes[num_equipes] = novaEquipe;
        num_equipes++;

}

void visualizarEquipes() {
    if(num_equipes == 0){
        printf("Nenhuma equipe cadastrada.");
        return;
    }
    for(int i = 0; i < num_equipes; i++){
        limparTela();
        puts("");
        printf("Equipe %d:\n", i+1);
        printf("    Nome da Equipe: %s\n", equipes[i].nome);
        printf("    Nome do Treinador: %s\n", equipes[i].treinador);
        printf("    NÃºmero de Gols: %d\n", equipes[i].gols);
        for(int j = 0; j < MAX_JOGADORES; j++){
            printf("\n    Jogador %d:\n", j+1);
            printf("        Nome do jogador: %s \n        Numero da camisa: %d\n        Idade: %d\n        Gols: %d\n", 
            equipes[i].jogadores[j].nome, equipes[i].jogadores[j].numero, equipes[i].jogadores[j].idade, 
            equipes[i].jogadores[j].gols);
        }
        puts("");
    }

}

void alterarEquipe() {
    limparTela();
    if (num_equipes == 0){
        printf("Nao existe equipes cadastradas...\n\n");
        return;
    }
    printf("Qual equipe voce deseja alterar?\n\n");
    for (int i = 0; i < num_equipes; i++){
        printf("    %d. %s\n", i+1, equipes[i].nome);
    }
    int escolha;
    scanf(" %d", &escolha);
    limparTela();
        puts("");
        printf("Informacoes:\n");
        printf("    Nome da Equipe: %s\n", equipes[escolha - 1].nome);
        printf("    Nome do Treinador: %s\n", equipes[escolha - 1].treinador);
        printf("    Numero de Gols: %d\n", equipes[escolha - 1].gols);
        puts("");
        printf("O que voce deseja alterar: \n");
        printf("1. Nome da Equipe\n");
        printf("2. Nome do Treinador\n");
        printf("3. Numero de Gols\n");
        int opcao;
        printf("    Opcao: ");
        scanf(" %d", &opcao);
        do{
            switch (opcao){
            case 1:
                printf("Novo nome do time: ");
                scanf(" %[^\n]", equipes[escolha-1].nome);
                opcao = 0;
                break;

            case 2:
            printf("Novo nome do treinador: ");
                scanf(" %[^\n]", equipes[escolha-1].treinador);
                opcao = 0;
                break;

            case 3:
                printf("Nova quantidade de gols: ");
                scanf(" %d", &equipes[escolha-1].gols);
                opcao = 0;
                break;

            case 0:break;

            default:
                printf("Opcao invalida!\n");
                break;
            } 
        } while (opcao!=0);

}

void excluirEquipe() {
    limparTela();
    if (num_equipes == 0){
        printf("Nao existe equipes cadastradas...\n\n");
        return;
    }
    printf("Qual equipe voce deseja excuir?\n\n");
    for (int i = 0; i < num_equipes; i++){
        printf("    %d. %s\n", i+1, equipes[i].nome);
    }
    int escolha;
    scanf(" %d", &escolha);
    //Adicionei esse while, para caso se o escolha receber um nÃºmero que nÃ£o 
    //cabe dentro do num_equipes. - TainÃ¡
    while(escolha < num_equipes || escolha > num_equipes){
        printf("Escolha invÃ¡lida...\n");
        printf("Tente Novamente...\n");
        scanf(" %d", &escolha);
    }
    escolha--;
    limparTela();
    puts("");
        printf("Equipe %d:\n", escolha);
        printf("    Nome da Equipe: %s\n", equipes[escolha].nome);
        printf("    Nome do Treinador: %s\n", equipes[escolha].treinador);
        printf("    NÃºmero de Gols: %d\n", equipes[escolha].gols);
        puts("");
        printf("VocÃª tem certeza que deseja excluir essa equipe?\n");
        puts("1. Sim");
        puts("0. Nao");
        int opcao;
        scanf(" %d", &opcao);
        switch (opcao)
        {
        case 1:
            for (int i = escolha; i < num_equipes - 1; i++) {
                equipes[i] = equipes[i + 1];
            }
            num_equipes--;
            puts("Equipe exluida!");
            break;

        case 0:
            break;

        default:
            puts("Opcao invalida!");
            break;
        }

}

void cadastrarJogo() {
    if(num_jogos >= MAX_JOGOS){
            printf("MAXIMO DE JOGOS ATINGIDO.");
            return;
        }
        Jogo novoJogo;
        novoJogo.gols1 = 0;
        novoJogo.gols2 = 0;
        limparTela();
        if(num_equipes < 2){
            printf("Não há equipes o suficiente para cadastrar um jogo.\n");
            return;
        }else{
         for(int i = 0; i < num_equipes; i++){
            printf("Equipe %d:\n", i+1);
            printf("    Nome da Equipe: %s\n", equipes[i].nome);
            printf("    NÃºmero de Gols: %d\n", equipes[i].gols);
        }
        int opcao, opcao2;
             printf("Digite o número identificador da equipe que jogou em casa:");
             scanf("%d", &opcao);
        while(opcao < 0 && opcao > num_equipes){
        printf("Digite novamente o número identificador da equipe que jogou em casa:");
        scanf("%d", &opcao);
        }
        strcpy(novoJogo.equipe1, equipes[opcao-1].nome);
        printf("Digite o número identificador da equipe que fora de casa:");
        scanf("%d", &opcao2);
        while(opcao2 < 0 && opcao2 > num_equipes && opcao2 == opcao){
        printf("Digite novamente o número identificador da equipe que jogou FORA de casa:");
        scanf("%d", &opcao2);
        }
        strcpy(novoJogo.equipe2, equipes[opcao2-1].nome);
        //adicionar - condicional do documento - Tem como pré-condição que o novo jogo 
        //a ser cadastrado ainda não exista no sistema. 
        //Se existir, é entendido como informação duplicada.
        printf("Equipe 1: %s\n", equipes[opcao2-1].nome);
        printf("Equipe 2: %s\n", equipes[opcao-1].nome);
        printf("Digite a quantidade de gols da primeira equipe: \n");
        scanf(" %d", &novoJogo.gols1);
        printf("Digite a quantidade de gols da segunda equipe: \n");
        scanf(" %d", &novoJogo.gols2);
        while(novoJogo.gols1 == novoJogo.gols2){
            printf("Empate não existe durante um campeonato mata-mata.\nInsira a quantidade de gols novamente \n");
            printf("Digite a quantidade de gols da primeira equipe: \n");
            scanf(" %d", &novoJogo.gols1);
            printf("Digite a quantidade de gols da segunda equipe: \n");
            scanf(" %d", &novoJogo.gols2);
        }
        equipes[opcao-1].gols += novoJogo.gols1;
        equipes[opcao2-1].gols += novoJogo.gols2;
        jogos[num_jogos] = novoJogo;
        num_jogos++;
        }
}

void visualizarJogos() {
    if(num_jogos == 0){
        printf("Nenhuma jogo cadastrado.");
        return;
    }
    for(int i = 0; i < num_jogos; i++){
        limparTela();
        puts("");
        printf("Jogo %d:\n", i+1);
        printf("    Nome da Equipe 1: %s\n", jogos[i].equipe1);
        printf("    Numero de Gols: %d\n", jogos[i].gols1);
        printf("    Nome da Equipe 2: %s\n", jogos[i].equipe2);
        printf("    Numero de Gols: %d\n", jogos[i].gols2);
        if(jogos[i].gols1 > jogos[i].gols2){
            printf("Equipe Vitoriosa: %s\n", jogos[i].equipe1);
        }else if(jogos[i].gols1 < jogos[i].gols2){
            printf("Equipe Vitoriosa: %s\n", jogos[i].equipe2);
        }else{
        // FUNCAO DE DESEMPATE    
            printf("Empate");
        }
        puts("");
}
}

void alterarJogo() {
    limparTela();
    if (num_jogos == 0){
        printf("Nao existe equipes cadastradas...\n\n");
        return;
    }
    printf("Qual jogo voce deseja alterar?\n\n");
    for (int i = 0; i < num_jogos; i++){
        printf("    %d. %s X %s\n", i+1, jogos[i].equipe1, jogos[i].equipe2);
    }
    int escolha;
    scanf(" %d", &escolha);
    limparTela();
        puts("");
        printf("Informacoes:\n");
        printf("    Nome da Equipe 1: %s\n", jogos[escolha - 1].equipe1);
        printf("    Numero de Gols: %d\n", jogos[escolha - 1].gols1);
        printf("    Nome da Equipe 2: %s\n", jogos[escolha - 1].equipe2);
        printf("    Numero de Gols: %d\n", jogos[escolha - 1].gols2);
        puts("");
        printf("O que voce deseja alterar: \n");
        printf("1. Nome da Equipe 1\n");
        printf("2. Numero de Gols da Equipe 1\n");
        printf("3. Nome da Equipe 2\n");
        printf("4. Numero de Gols da Equipe 2\n");
        int opcao;
        printf("    Opcao: ");
        scanf(" %d", &opcao);
        do{
            switch (opcao){
            case 1:
                printf("Novo nome da Equipe 1: ");
                scanf(" %[^\n]", jogos[escolha-1].equipe1);
                opcao = 0;
                break;

            case 2:
                printf("Nova quantidade de gols: ");
                scanf(" %d", &jogos[escolha-1].gols1);
                opcao = 0;
                break;

            case 3:
                printf("Novo nome da Equipe 1: ");
                scanf(" %[^\n]", jogos[escolha-1].equipe2);
                opcao = 0;
                break;
            case 4:
                printf("Nova quantidade de gols: ");
                scanf(" %d", &jogos[escolha-1].gols2);
                opcao = 0;
            case 0:break;

            default:
                printf("Opcao invalida!\n");
                break;
            } 
        } while (opcao!=0);

}

void excluirJogo() {
    limparTela();
    if (num_jogos == 0){
        printf("Nao existe jogos cadastrados...\n\n");
        return;
    }
    printf("Qual jogo voce deseja excluir?\n\n");
    for (int i = 0; i < num_jogos; i++){
        printf("    %d. %s X %s\n", i+1, jogos[i].equipe1, jogos[i].equipe2);
    }
    int escolha;
    scanf(" %d", &escolha);
    //Adicionei esse while, para caso se o escolha receber um numero que nao 
    //cabe dentro do num_jogos. - Taina!
    while(escolha < num_jogos || escolha > num_jogos){
        printf("Escolha invalida...\n");
        printf("Tente Novamente...\n");
        scanf(" %d", &escolha);
    }
    escolha--;
    limparTela();
    puts("");
        printf("Jogo %d:\n", escolha + 1);
        printf("    Nome da Equipe: %s\n", jogos[escolha].equipe1);
        printf("    Numero de Gols: %d\n", jogos[escolha].gols1);
        printf("    Nome da Equipe: %s\n", jogos[escolha].equipe2);
        printf("    Numero de Gols: %d\n", jogos[escolha].gols2);
        puts("");
        printf("Voce tem certeza que deseja excluir esse jogo?\n");
        puts("1. Sim");
        puts("0. Nao");
        int opcao;
        scanf(" %d", &opcao);
        switch (opcao)
        {
        case 1:
            for (int i = escolha; i < num_jogos - 1; i++) {
                jogos[i] = jogos[i + 1];
            }
            num_jogos--;
            puts("Jogo exluido!");
            break;

        case 0:
            break;

        default:
            puts("Opcao invalida!");
            break;
        }

}


void sortearJogos(){

}

void chavamentoConfrontos(){

}

void desempate(){

}

void determinarClassificados(){

}

void listarDados(){

}

void pesquisar(){

}

void exibirEstatisticas(){

}

void carregarDadosEquipes(){
    FILE *arquivo = fopen(ARQUIVO_EQUIPES, "rb"); // abrie o arquivo
    if (arquivo == NULL) {
        return; // caso o arquivo nao exista, ou nao foi declado certo
    }

    fread(&num_equipes, sizeof(int), 1, arquivo); // carregaa o numero de equipes
    fread(equipes, sizeof(Equipe), num_equipes, arquivo); // carregaa as equipes
    fclose(arquivo); // fechaa o arquivo
}

void salvarDadosEquipes(){
    FILE *arquivo = fopen(ARQUIVO_EQUIPES, "wb"); // abrir o arquivo em modo binÃ¡rio de escrita
    if (arquivo == NULL) {
        printf("Erro ao salvar os dados.\n");
        return;
    }
    fwrite(&num_equipes, sizeof(int), 1, arquivo); // salvar o numero de equipes
    fwrite(equipes, sizeof(Equipe), num_equipes, arquivo); // salvar as equipes
    fclose(arquivo); // fechar o arquivo
    // printf("Dados salvos com sucesso!\n");
}

void carregarDadosJogos(){
    FILE *arquivo = fopen(ARQUIVO_JOGOS, "rb"); // abre o arquivo
    if (arquivo == NULL) {
        return; // caso o arquivo nao exista, ou nao foi declado certo
    }

    fread(&num_jogos, sizeof(int), 1, arquivo); // carregaa o numero de jogos
    fread(jogos, sizeof(Jogo), num_jogos, arquivo); // carrega os jogos
    fclose(arquivo); // fecha o arquivo
}

void salvarDadosJogos(){
    FILE *arquivo = fopen(ARQUIVO_JOGOS, "wb"); // abrir o arquivo em modo binÃ¡rio de escrita
    if (arquivo == NULL) {
        printf("Erro ao salvar os dados.\n");
        return;
    }
    fwrite(&num_jogos, sizeof(int), 1, arquivo); // salvar o nÃºmero de equipes
    fwrite(jogos, sizeof(Jogo), num_jogos, arquivo); // salvar as equipes
    fclose(arquivo); // fechar o arquivo
    // printf("Dados salvos com sucesso!\n");
}

void menuEquipes(){
    int opcao;
    do {
        // limparTela();
        printf("\nGestao de Equipes\n");
        printf("1. Cadastrar Equipe\n");
        printf("2. Visualizar Equipes\n");
        printf("3. Alterar Equipe\n");
        printf("4. Exluir Equipe\n");
        printf("5. Carregar Dados\n");
        printf("6. Salvar Dados \n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao){
            case 1: cadastrarEquipe(); break;
            case 2: visualizarEquipes(); break;
            case 3: alterarEquipe(); break;
            case 4: excluirEquipe(); break;
            case 5: carregarDadosEquipes();
            case 6: salvarDadosEquipes();
            case 0: break;
            default: printf("Opcao invalida!");
        }
    } while (opcao != 0);
}

void menuJogos(){
    int opcao;
    do {
        // limparTela();
        printf("\nGestao de Jogos\n");
        printf("1. Cadastrar Jogo\n");
        printf("2. Visualizar Jogos\n");
        printf("3. Alterar Jogo\n");
        printf("4. Excluir Jogo\n");
        printf("5. Carregar Dados\n");
        printf("6. Salvar Dados \n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao){
            case 1: cadastrarJogo(); break;
            case 2: visualizarJogos(); break;
            case 3: alterarJogo(); break;
            case 4: excluirJogo(); break;
            case 5: carregarDadosJogos();
            case 6: salvarDadosJogos();
            case 0: break;
            default: printf("Opcao invalida!");
        }
    } while (opcao != 0);
}

void menuEstatiscas(){
    int opcao;
    do {
        // limparTela();
        printf("\nEstatisticas e Classificacoes\n");
        printf("1. Sortear Jogos\n");
        printf("2. Chaveamento de Confrontos\n");
        printf("3. Desempate\n");
        printf("4. Determinar Classificados\n");
        printf("5. Listar Dados Gerais\n");
        printf("6. Pesquisar Dados\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao){
            case 1: sortearJogos(); break;
            case 2: chavamentoConfrontos(); break;
            case 3: desempate(); break;
            case 4: determinarClassificados(); break;
            case 5: listarDados(); break;
            case 6: pesquisar(); break;
            case 0: break;
            default: printf("Opcao invalida!");
        }
    } while (opcao != 0);
}

void menuPrincipal(){
    int opcao;
    do {
        limparTela();
        printf("\nSistema de Gestao de Torneios\n");
        printf("1. Gestao de Equipes\n");
        printf("2. Gestao de Jogos\n");
        printf("3. Estatisticas e Classificacoes\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao){
            case 1: menuEquipes(); break;
            case 2: menuJogos(); break;
            case 3: menuEstatiscas(); break;
            case 0: printf("Saindo do Sistema...\n"); break;
            default: printf("Opcao invalida!");
        }
    } while (opcao != 0);
}

void limparTela(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}