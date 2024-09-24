#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
    int vitorias; // implementei isso
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
// Adicionei 2 funcoes a mais em relacao aos jogos - Taina
void carregarDadosJogos();
void salvarDadosJogos();
void carregarDadosEquipes();
void salvarDadosEquipes();

void exibirEstatisticas(); //funcao para exibir estatisticas CHECK

void cadastrarEquipe(); // funcao para cadastrar uma nova equipe CHECK

void visualizarEquipes(); //funcao para visualizar as equipes cadastradas CHECK

void alterarEquipe(); //funcao para alterar os dados de uma equipe CHECK

void excluirEquipe(); //funcao para excluir uma equipe CHECK

void cadastrarJogo(); //funcao para cadastrar um novo jogo CHECK

void visualizarJogos(); //funcao para visualizar os jogos cadastrados CHECK

void alterarJogo(); //funcao para alterar os dados de um jogo CHECK

void excluirJogo(); //funcao para excluir um jogo CHECK

void sortearJogos(); //funcao para visualizar o sorteio dos jogos de acordo com as equipes que estao cadastradas no sistema. CHECK

void chavamentoConfrontos(); //funcao para acompanhar as classificacoes da equipe cadastrada e das outras a cada jogo que passa. CHECK

int desempate(int equipe1, int equipe2); // funcao para desempatar duas equipes que estejam em uma mesma condicao CHECK

void classificados(); // funcao para visualizar em forma de tabela a posiÃ§Ã£o final das equipes apÃ³s o encerramento do torneio. CHECK

void listarDados(); // funcao que permite que o usuario visualize os dados das equipes participantes do torneio, dos jogos e da classificacao de cada fase. CHECK

void pesquisar(); // funcao para pesquisar os dados de uma equipe, jogador, jogos ou resultados CHECK

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

void cadastrarEquipe() {  
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

    for(int i = 0; i < MAX_JOGADORES; i++){
        limparTela();
        printf("Digite o nome do jogador %d: ", i + 1);
        scanf(" %[^\n]", novaEquipe.jogadores[i].nome);
        printf("Digite o numero do jogador: ");
        scanf(" %d", &novaEquipe.jogadores[i].numero);
        printf("Digite a idade do jogador: ");
        scanf(" %d", &novaEquipe.jogadores[i].idade);
        novaEquipe.jogadores[i].gols = 0;
    }

    novaEquipe.gols = 0;
    novaEquipe.vitorias = 0; // Inicializa o número de vitórias
    equipes[num_equipes] = novaEquipe;
    num_equipes++;
}

void visualizarEquipes() {
    if(num_equipes == 0){
        printf("Nenhuma equipe cadastrada.");
        return;
    }
    for(int i = 0; i < num_equipes; i++){
        // limparTela(); com essa função n dá pra ver todas as equipes no terminal, por isso comentei
        puts("");
        printf("Equipe %d:\n", i + 1);
        printf("    Nome da Equipe: %s\n", equipes[i].nome);
        printf("    Nome do Treinador: %s\n", equipes[i].treinador);
        printf("    Numero de Gols: %d\n", equipes[i].gols);
        printf("    Numero de Vitorias: %d\n", equipes[i].vitorias); // Exibe o número de vitórias
        for(int j = 0; j < MAX_JOGADORES; j++){
            printf("\n    Jogador %d:\n", j + 1);
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
        printf("    %d. %s\n", i + 1, equipes[i].nome);
    }
    int escolha;
    scanf(" %d", &escolha);
    limparTela();
    puts("");
    printf("Informacoes:\n");
    printf("    Nome da Equipe: %s\n", equipes[escolha - 1].nome);
    printf("    Nome do Treinador: %s\n", equipes[escolha - 1].treinador);
    printf("    Numero de Gols: %d\n", equipes[escolha - 1].gols);
    printf("    Numero de Vitorias: %d\n", equipes[escolha - 1].vitorias); // Mostrando número de vitórias
    puts("");
    
    printf("O que voce deseja alterar: \n");
    printf("1. Nome da Equipe\n");
    printf("2. Nome do Treinador\n");
    printf("3. Numero de Gols\n");
    printf("4. Numero de Vitorias\n"); // Nova opção para alterar vitórias
    int opcao;
    printf("    Opcao: ");
    scanf(" %d", &opcao);
    
    do {
        switch (opcao) {
            case 1:
                printf("Novo nome do time: ");
                scanf(" %[^\n]", equipes[escolha - 1].nome);
                opcao = 0;
                break;

            case 2:
                printf("Novo nome do treinador: ");
                scanf(" %[^\n]", equipes[escolha - 1].treinador);
                opcao = 0;
                break;

            case 3:
                printf("Nova quantidade de gols: ");
                scanf(" %d", &equipes[escolha - 1].gols);
                opcao = 0;
                break;

            case 4:
                printf("Novo numero de vitorias: ");
                scanf(" %d", &equipes[escolha - 1].vitorias); // Atualizando vitórias
                opcao = 0;
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        } 
    } while (opcao != 0);
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
        printf("Escolha invalida...\n");
        printf("Tente Novamente...\n");
        scanf(" %d", &escolha);
    }
    escolha--;
    limparTela();
    puts("");
        printf("Equipe %d:\n", escolha);
        printf("    Nome da Equipe: %s\n", equipes[escolha].nome);
        printf("    Nome do Treinador: %s\n", equipes[escolha].treinador);
        printf("    Numero de Gols: %d\n", equipes[escolha].gols);
        puts("");
        printf("Voce tem certeza que deseja excluir essa equipe?\n");
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
    if(num_jogos >= MAX_JOGOS) {
        printf("MAXIMO DE JOGOS ATINGIDO.");
        return;
    }

    Jogo novoJogo;
    novoJogo.gols1 = 0;
    novoJogo.gols2 = 0;
    limparTela();

    if(num_equipes < 2) {
        printf("Nao ha equipes o suficiente para cadastrar um jogo.\n");
        return;
    } else {
        for(int i = 0; i < num_equipes; i++) {
            printf("Equipe %d:\n", i + 1);
            printf("    Nome da Equipe: %s\n", equipes[i].nome);
            printf("    Numero de Gols: %d\n", equipes[i].gols);
        }

        int opcao, opcao2;
        printf("Digite o numero identificador da equipe que jogou em casa: ");
        scanf("%d", &opcao);
        while(opcao < 1 || opcao > num_equipes) {
            printf("Digite novamente o numero identificador da equipe que jogou em casa: ");
            scanf("%d", &opcao);
        }

        strcpy(novoJogo.equipe1, equipes[opcao - 1].nome);
        printf("Digite o numero identificador da equipe que jogou FORA de casa: ");
        scanf("%d", &opcao2);
        while(opcao2 < 1 || opcao2 > num_equipes || opcao2 == opcao) {
            printf("Digite novamente o numero identificador da equipe que jogou FORA de casa: ");
            scanf("%d", &opcao2);
        }

        strcpy(novoJogo.equipe2, equipes[opcao2 - 1].nome);

        // Verifica se o jogo já foi cadastrado
        if(num_jogos > 0) {
            for (int i = 0; i < num_jogos; i++) {
                if ((strcmp(novoJogo.equipe1, jogos[i].equipe1) == 0 && strcmp(novoJogo.equipe2, jogos[i].equipe2) == 0) || 
                    (strcmp(novoJogo.equipe2, jogos[i].equipe1) == 0 && strcmp(novoJogo.equipe1, jogos[i].equipe2) == 0)) {
                    printf("Jogo previamente cadastrado.\n");
                    return;
                }
            }

            // Verifica se as equipes estão ativas no torneio
            for(int i = 0; i < num_jogos; i++) {
                if((strcmp(novoJogo.equipe1, jogos[i].equipe1) == 0 && jogos[i].gols1 < jogos[i].gols2) || 
                   (strcmp(novoJogo.equipe1, jogos[i].equipe2) == 0 && jogos[i].gols2 < jogos[i].gols1)) {
                    printf("Equipe %s perdeu, logo nao esta participando do torneio.\n", novoJogo.equipe1);
                    return;
                } else if((strcmp(novoJogo.equipe2, jogos[i].equipe2) == 0 && jogos[i].gols2 < jogos[i].gols1) || 
                          (strcmp(novoJogo.equipe2, jogos[i].equipe1) == 0 && jogos[i].gols1 < jogos[i].gols2)) {
                    printf("Equipe %s perdeu, logo nao esta participando do torneio.\n", novoJogo.equipe2);
                    return;
                }
            }
        }

        printf("Equipe 1: %s\n", equipes[opcao - 1].nome);
        printf("Equipe 2: %s\n", equipes[opcao2 - 1].nome);
        printf("Digite a quantidade de gols da primeira equipe: \n");
        scanf(" %d", &novoJogo.gols1);
        printf("Digite a quantidade de gols da segunda equipe: \n");
        scanf(" %d", &novoJogo.gols2);

        // Verifica empate
        while(novoJogo.gols1 == novoJogo.gols2) {
            printf("Empate nao existe durante um campeonato mata-mata.\nInsira a quantidade de gols novamente \n");
            printf("Digite a quantidade de gols da primeira equipe: \n");
            scanf(" %d", &novoJogo.gols1);
            printf("Digite a quantidade de gols da segunda equipe: \n");
            scanf(" %d", &novoJogo.gols2);
        }

        // Atualiza a quantidade de gols e vitorias
        equipes[opcao - 1].gols += novoJogo.gols1;
        equipes[opcao2 - 1].gols += novoJogo.gols2;

        // Incrementa vitórias
        if(novoJogo.gols1 > novoJogo.gols2) {
            equipes[opcao - 1].vitorias++; // A equipe da casa venceu
        } else {
            equipes[opcao2 - 1].vitorias++; // A equipe fora venceu
        }

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
        //limparTela(); com essa função n dá pra ver todas as equipes no terminal, por isso comentei
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
    if (num_jogos == 0) {
        printf("Nao existe jogos cadastrados...\n\n");
        return;
    }
    
    printf("Qual jogo voce deseja alterar?\n\n");
    for (int i = 0; i < num_jogos; i++) {
        printf("    %d. %s X %s\n", i + 1, jogos[i].equipe1, jogos[i].equipe2);
    }
    
    int escolha;
    scanf(" %d", &escolha);
    
    if (escolha < 1 || escolha > num_jogos) {
        printf("Opcao invalida.\n");
        return;
    }

    // Salvar o estado anterior para decrementar depois
    int gols1_ant = jogos[escolha - 1].gols1;
    int gols2_ant = jogos[escolha - 1].gols2;

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
    
    do {
        switch (opcao) {
            case 1:
                printf("Novo nome da Equipe 1: ");
                scanf(" %[^\n]", jogos[escolha - 1].equipe1);
                opcao = 0;
                break;

            case 2:
                printf("Nova quantidade de gols: ");
                scanf(" %d", &jogos[escolha - 1].gols1);
                opcao = 0;
                break;

            case 3:
                printf("Novo nome da Equipe 2: ");
                scanf(" %[^\n]", jogos[escolha - 1].equipe2);
                opcao = 0;
                break;

            case 4:
                printf("Nova quantidade de gols: ");
                scanf(" %d", &jogos[escolha - 1].gols2);
                opcao = 0;
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        } 
    } while (opcao != 0);

    // Atualiza a contagem de vitórias das equipes
    int gols1_novos = jogos[escolha - 1].gols1;
    int gols2_novos = jogos[escolha - 1].gols2;

    // Decrementa as vitórias da situação anterior
    if (gols1_ant > gols2_ant) {
        equipes[escolha - 1].vitorias--; // A equipe 1 estava ganhando
    } else if (gols2_ant > gols1_ant) {
        equipes[escolha].vitorias--; // A equipe 2 estava ganhando
    }

    // Incrementa as vitórias da nova situação
    if (gols1_novos > gols2_novos) {
        equipes[escolha - 1].vitorias++; // A equipe 1 está ganhando agora
    } else if (gols2_novos > gols1_novos) {
        equipes[escolha].vitorias++; // A equipe 2 está ganhando agora
    }
}

void excluirJogo() {
    limparTela();
    if (num_jogos == 0) {
        printf("Nao existe jogos cadastrados...\n\n");
        return;
    }

    printf("Qual jogo voce deseja excluir?\n\n");
    for (int i = 0; i < num_jogos; i++) {
        printf("    %d. %s X %s\n", i + 1, jogos[i].equipe1, jogos[i].equipe2);
    }
    
    int escolha;
    scanf(" %d", &escolha);

    // Verifica se a escolha está dentro do intervalo válido
    while (escolha < 1 || escolha > num_jogos) {
        printf("Escolha invalida...\n");
        printf("Tente Novamente...\n");
        scanf(" %d", &escolha);
    }
    
    escolha--; // Ajusta para índice de array
    limparTela();
    puts("");
    printf("Jogo %d:\n", escolha + 1);
    printf("    Nome da Equipe 1: %s\n", jogos[escolha].equipe1);
    printf("    Numero de Gols: %d\n", jogos[escolha].gols1);
    printf("    Nome da Equipe 2: %s\n", jogos[escolha].equipe2);
    printf("    Numero de Gols: %d\n", jogos[escolha].gols2);
    puts("");
    
    printf("Voce tem certeza que deseja excluir esse jogo?\n");
    puts("1. Sim");
    puts("0. Nao");
    
    int opcao;
    scanf(" %d", &opcao);
    switch (opcao) {
        case 1:
            // Decrementa as vitórias da equipe vencedora
            if (jogos[escolha].gols1 > jogos[escolha].gols2) {
                // A equipe 1 ganhou
                for (int i = 0; i < num_equipes; i++) {
                    if (strcmp(equipes[i].nome, jogos[escolha].equipe1) == 0) {
                        equipes[i].vitorias--;
                        break;
                    }
                }
            } else if (jogos[escolha].gols2 > jogos[escolha].gols1) {
                // A equipe 2 ganhou
                for (int i = 0; i < num_equipes; i++) {
                    if (strcmp(equipes[i].nome, jogos[escolha].equipe2) == 0) {
                        equipes[i].vitorias--;
                        break;
                    }
                }
            }

            // Remove o jogo
            for (int i = escolha; i < num_jogos - 1; i++) {
                jogos[i] = jogos[i + 1];
            }
            num_jogos--;
            puts("Jogo excluido!");
            break;

        case 0:
            break;

        default:
            puts("Opcao invalida!");
            break;
    }
}

void sortearJogos(){
    limparTela();

    // Verifica se o número de equipes é suficiente
    if (num_equipes < 2) {
        printf("O numero de equipes deve ser pelo menos 2 para o sorteio.\n");
        return;
    }

    // Inicializa um vetor para armazenar os índices das equipes sorteadas
    bool sorteadas[MAX_EQUIPES] = {false};
    num_jogos = 0; // Reseta o número de jogos para o sorteio

    printf("Sorteando jogos:\n");

    // Sorteio de jogos em pares
    for (int i = 0; i < num_equipes; i += 2) {
        if (i + 1 >= num_equipes) {
            printf("Numero de equipes impar. O ultimo time (%s) avança diretamente.\n", equipes[i].nome);
            break; // Se o número de equipes é ímpar, não forma um jogo
        }

        // Sorteia dois índices diferentes para formar um jogo
        int equipe1, equipe2;

        do {
            equipe1 = rand() % num_equipes;
        } while (sorteadas[equipe1]); // Garante que a equipe1 ainda não foi sorteada
        sorteadas[equipe1] = true; // Marca a equipe como sorteada

        do {
            equipe2 = rand() % num_equipes;
        } while (sorteadas[equipe2] || equipe1 == equipe2); // Garante que a equipe2 é diferente e não foi sorteada
        sorteadas[equipe2] = true; // Marca a equipe como sorteada

        // Cria um novo jogo e adiciona ao vetor de jogos
        Jogo novoJogo;
        strcpy(novoJogo.equipe1, equipes[equipe1].nome);
        strcpy(novoJogo.equipe2, equipes[equipe2].nome);
        novoJogo.gols1 = 0; // Inicializa os gols
        novoJogo.gols2 = 0; // Inicializa os gols

        jogos[num_jogos++] = novoJogo; // Adiciona o novo jogo ao vetor de jogos
        printf("Jogo %d: %s X %s\n", num_jogos, novoJogo.equipe1, novoJogo.equipe2);
    }

    // Se ainda houver equipes não sorteadas, elas avançam automaticamente
    for (int i = 0; i < num_equipes; i++) {
        if (!sorteadas[i]) {
            printf("A equipe %s avança diretamente para a proxima fase.\n", equipes[i].nome);
        }
    }

}

int desempate(int equipe1, int equipe2) {
    int golsEquipe1, golsEquipe2;
    
    printf("Empate! Realizando desempate entre %s e %s.\n", equipes[equipe1].nome, equipes[equipe2].nome);
    printf("Informe o placar da prorrogacao do jogo %s X %s (gols %s - gols %s): ", equipes[equipe1].nome, equipes[equipe2].nome, equipes[equipe1].nome, equipes[equipe2].nome);
    scanf("%d %d", &golsEquipe1, &golsEquipe2);

    if (golsEquipe1 > golsEquipe2) {
        printf("A equipe %s vence a prorrogacao!\n", equipes[equipe1].nome);
        return equipe1; // Equipe 1 vence
    } else {
        printf("A equipe %s vence a prorrogacao!\n", equipes[equipe2].nome);
        return equipe2; // Equipe 2 vence
    }
}

void chavamentoConfrontos() {
    limparTela();

    if (num_equipes < 8) { // Verifica se existem pelo menos 8 equipes
        printf("Precisa de pelo menos 8 equipes para realizar o chaveamento completo.\n");
        return;
    }

    printf("Chaveamento Completo:\n");

    // Oitavas de Final
    printf("Oitavas de Final:\n");
    for (int i = 0; i < num_equipes; i += 2) {
        printf("Jogo %d: %s X %s\n", (i / 2) + 1, equipes[i].nome, equipes[i + 1].nome);
    }

    printf("\nResultados das Oitavas de Final:\n");
    int vencedoresOitavas[8]; // Array para armazenar os vencedores
    for (int i = 0; i < num_equipes; i += 2) {
        int golsEquipe1, golsEquipe2;
        printf("Informe o placar do jogo %s X %s (gols %s - gols %s): ", equipes[i].nome, equipes[i + 1].nome, equipes[i].nome, equipes[i + 1].nome);
        scanf("%d %d", &golsEquipe1, &golsEquipe2);
        
        if (golsEquipe1 > golsEquipe2) {
            vencedoresOitavas[i / 2] = i; // Equipe 1 vence
            equipes[i].vitorias++; // Atualiza vitórias da equipe 1
        } else if (golsEquipe2 > golsEquipe1) {
            vencedoresOitavas[i / 2] = i + 1; // Equipe 2 vence
            equipes[i + 1].vitorias++; // Atualiza vitórias da equipe 2
        } else {
            // Empate, chama a função de desempate
            vencedoresOitavas[i / 2] = desempate(i, i + 1); // Chama a função de desempate
            equipes[vencedoresOitavas[i / 2]].vitorias++; // Atualiza vitórias da equipe vencedora
        }
    }

    // Quartas de Final
    printf("\nQuartas de Final:\n");
    for (int i = 0; i < 8; i += 2) {
        printf("Jogo %d: %s X %s\n", (i / 2) + 1, equipes[vencedoresOitavas[i]].nome, equipes[vencedoresOitavas[i + 1]].nome);
    }

    printf("\nResultados das Quartas de Final:\n");
    int vencedoresQuartas[4];
    for (int i = 0; i < 8; i += 2) {
        int golsEquipe1, golsEquipe2;
        printf("Informe o placar do jogo %s X %s (gols %s - gols %s): ", equipes[vencedoresOitavas[i]].nome, equipes[vencedoresOitavas[i + 1]].nome, equipes[vencedoresOitavas[i]].nome, equipes[vencedoresOitavas[i + 1]].nome);
        scanf("%d %d", &golsEquipe1, &golsEquipe2);
        
        if (golsEquipe1 > golsEquipe2) {
            vencedoresQuartas[i / 2] = vencedoresOitavas[i]; // Equipe 1 vence
            equipes[vencedoresOitavas[i]].vitorias++; // Atualiza vitórias da equipe 1
        } else if (golsEquipe2 > golsEquipe1) {
            vencedoresQuartas[i / 2] = vencedoresOitavas[i + 1]; // Equipe 2 vence
            equipes[vencedoresOitavas[i + 1]].vitorias++; // Atualiza vitórias da equipe 2
        } else {
            // Empate, chama a função de desempate
            vencedoresQuartas[i / 2] = desempate(vencedoresOitavas[i], vencedoresOitavas[i + 1]); // Chama a função de desempate
            equipes[vencedoresQuartas[i / 2]].vitorias++; // Atualiza vitórias da equipe vencedora
        }
    }

    // Semifinais
    printf("\nSemifinais:\n");
    for (int i = 0; i < 4; i += 2) {
        printf("Jogo %d: %s X %s\n", (i / 2) + 1, equipes[vencedoresQuartas[i]].nome, equipes[vencedoresQuartas[i + 1]].nome);
    }

    printf("\nResultados das Semifinais:\n");
    int vencedoresSemifinais[2];
    for (int i = 0; i < 4; i += 2) {
        int golsEquipe1, golsEquipe2;
        printf("Informe o placar do jogo %s X %s (gols %s - gols %s): ", equipes[vencedoresQuartas[i]].nome, equipes[vencedoresQuartas[i + 1]].nome, equipes[vencedoresQuartas[i]].nome, equipes[vencedoresQuartas[i + 1]].nome);
        scanf("%d %d", &golsEquipe1, &golsEquipe2);
        
        if (golsEquipe1 > golsEquipe2) {
            vencedoresSemifinais[i / 2] = vencedoresQuartas[i]; // Equipe 1 vence
            equipes[vencedoresQuartas[i]].vitorias++; // Atualiza vitórias da equipe 1
        } else if (golsEquipe2 > golsEquipe1) {
            vencedoresSemifinais[i / 2] = vencedoresQuartas[i + 1]; // Equipe 2 vence
            equipes[vencedoresQuartas[i + 1]].vitorias++; // Atualiza vitórias da equipe 2
        } else {
            // Empate, chama a função de desempate
            vencedoresSemifinais[i / 2] = desempate(vencedoresQuartas[i], vencedoresQuartas[i + 1]); // Chama a função de desempate
            equipes[vencedoresSemifinais[i / 2]].vitorias++; // Atualiza vitórias da equipe vencedora
        }
    }

    // Final
    printf("\nFinal:\n");
    printf("Jogo: %s X %s\n", equipes[vencedoresSemifinais[0]].nome, equipes[vencedoresSemifinais[1]].nome);

    printf("\nResultados da Final:\n");
    int golsEquipe1, golsEquipe2;
    printf("Informe o placar do jogo %s X %s (gols %s - gols %s): ", equipes[vencedoresSemifinais[0]].nome, equipes[vencedoresSemifinais[1]].nome, equipes[vencedoresSemifinais[0]].nome, equipes[vencedoresSemifinais[1]].nome);
    scanf("%d %d", &golsEquipe1, &golsEquipe2);

    if (golsEquipe1 > golsEquipe2) {
        printf("A equipe %s e a campeã!\n", equipes[vencedoresSemifinais[0]].nome);
        equipes[vencedoresSemifinais[0]].vitorias++; // Atualiza vitórias da equipe campeã
    } else if (golsEquipe2 > golsEquipe1) {
        printf("A equipe %s e a campeã!\n", equipes[vencedoresSemifinais[1]].nome);
        equipes[vencedoresSemifinais[1]].vitorias++; // Atualiza vitórias da equipe campeã
    } else {
        // Empate na final, chama a função de desempate
        int campeaoFinal = desempate(vencedoresSemifinais[0], vencedoresSemifinais[1]);
        printf("A equipe %s e a campeã!\n", equipes[campeaoFinal].nome);
        equipes[campeaoFinal].vitorias++; // Atualiza vitórias da equipe campeã
    }
}

void classificados() {
    Equipe temp;
    for (int i = 0; i < num_equipes - 1; i++) {
        for (int j = i + 1; j < num_equipes; j++) {

            if (equipes[i].gols < equipes[j].gols || 
                (equipes[i].gols == equipes[j].gols && equipes[i].vitorias < equipes[j].vitorias)) {
                // Troca as equipes
                temp = equipes[i];
                equipes[i] = equipes[j];
                equipes[j] = temp;
            }
        }
    }

    // Exibe a tabela de classificação
    printf("\nClassificacao Final do Torneio:\n");
    printf("----------------------------------------------------\n");
    printf("| Posicao |      Equipe      | Gols | Vitorias |\n");
    printf("----------------------------------------------------\n");
    
    for (int i = 0; i < num_equipes; i++) {
        printf("|   %2d    | %-16s | %4d |    %2d   |\n", 
               i + 1, equipes[i].nome, equipes[i].gols, equipes[i].vitorias);
    }
    printf("----------------------------------------------------\n");
}

void listarDados() {
    limparTela();
    printf("Escolha uma das opcoes abaixo para visualizar os dados:\n");
    printf("1. Dados das Equipes\n");
    printf("2. Dados dos Jogos\n");
    printf("3. Classificacao Final\n");
    printf("0. Sair\n");

    int opcao;
    do {
        printf("Digite sua opcao: ");
        scanf(" %d", &opcao);
        limparTela();

        switch (opcao) {
            case 1:
                printf("Dados das Equipes:\n");
                printf("----------------------------------------------------\n");
                printf("|     Equipe      | Treinador        | Gols | Vitorias |\n");
                printf("----------------------------------------------------\n");
                for (int i = 0; i < num_equipes; i++) {
                    printf("| %-16s | %-16s | %4d |    %2d   |\n", 
                           equipes[i].nome, equipes[i].treinador, equipes[i].gols, equipes[i].vitorias);
                }
                printf("----------------------------------------------------\n");
                break;

            case 2:
                printf("Dados dos Jogos:\n");
                printf("----------------------------------------------------\n");
                for (int i = 0; i < num_jogos; i++) {
                    printf("Jogo %d: %s %d X %d %s\n", 
                           i + 1, jogos[i].equipe1, jogos[i].gols1, jogos[i].gols2, jogos[i].equipe2);
                }
                printf("----------------------------------------------------\n");
                break;

            case 3:
                classificados(); // Chama a função que exibe a classificação
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }

        if (opcao != 0) {
            printf("Digite 0 para sair ou qualquer outro número para continuar: ");
            int sair;
            scanf(" %d", &sair);
            if (sair == 0) {
                opcao = 0; // Atualiza opcao para sair do loop
            } else {
                limparTela();
            }
        }

    } while (opcao != 0);
}

void pesquisar(){
       limparTela();
    printf("Escolha uma das opcoes abaixo para pesquisar:\n");
    printf("1. Pesquisar por Equipe\n");
    printf("2. Pesquisar por Jogador\n");
    printf("3. Pesquisar por Jogo\n");
    printf("0. Sair\n");

    int opcao;
    do {
        printf("Digite sua opcao: ");
        scanf(" %d", &opcao);
        limparTela();

        switch (opcao) {
            case 1: {
                char nomeEquipe[50];
                printf("Digite o nome da equipe: ");
                scanf(" %49[^\n]", nomeEquipe); // Lê até 49 caracteres ou até uma nova linha
                int encontrado = 0;

                for (int i = 0; i < num_equipes; i++) {
                    if (strcmp(equipes[i].nome, nomeEquipe) == 0) {
                        printf("Dados da Equipe:\n");
                        printf("Nome: %s\n", equipes[i].nome);
                        printf("Treinador: %s\n", equipes[i].treinador);
                        printf("Gols: %d\n", equipes[i].gols);
                        printf("Vitorias: %d\n", equipes[i].vitorias);
                        encontrado = 1;
                        break;
                    }
                }

                if (!encontrado) {
                    printf("Equipe nao encontrada!\n");
                }
                break;
            }

            case 2: {
                char nomeJogador[50];
                printf("Digite o nome do jogador: ");
                scanf(" %49[^\n]", nomeJogador); // Lê até 49 caracteres ou até uma nova linha
                int encontrado = 0;

                for (int i = 0; i < num_equipes; i++) {
                    for (int j = 0; j < MAX_JOGADORES; j++) {
                        if (strcmp(equipes[i].jogadores[j].nome, nomeJogador) == 0) {
                            printf("Dados do Jogador:\n");
                            printf("Nome: %s\n", equipes[i].jogadores[j].nome);
                            printf("Número: %d\n", equipes[i].jogadores[j].numero);
                            encontrado = 1;
                            break;
                        }
                    }
                    if (encontrado) break;
                }

                if (!encontrado) {
                    printf("Jogador nao encontrado!\n");
                }
                break;
            }

            case 3: {
                char equipe1[50], equipe2[50];
                printf("Digite o nome da primeira equipe: ");
                scanf(" %49[^\n]", equipe1);
                printf("Digite o nome da segunda equipe: ");
                scanf(" %49[^\n]", equipe2);
                int encontrado = 0;

                for (int i = 0; i < num_jogos; i++) {
                    if ((strcmp(jogos[i].equipe1, equipe1) == 0 && strcmp(jogos[i].equipe2, equipe2) == 0) || 
                        (strcmp(jogos[i].equipe1, equipe2) == 0 && strcmp(jogos[i].equipe2, equipe1) == 0)) {
                        printf("Resultado do Jogo:\n");
                        printf("%s %d X %d %s\n", jogos[i].equipe1, jogos[i].gols1, jogos[i].gols2, jogos[i].equipe2);
                        encontrado = 1;
                        break;
                    }
                }

                if (!encontrado) {
                    printf("Jogo nao encontrado!\n");
                }
                break;
            }

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }

        if (opcao != 0) {
            printf("Digite 0 para sair ou qualquer outro numero para continuar: ");
            int sair;
            scanf(" %d", &sair);
            if (sair == 0) {
                opcao = 0; // Atualiza opcao para sair do loop
            } else {
                limparTela(); // Limpa a tela se o usuário não quiser sair
            }
        }

    } while (opcao != 0);
}

void exibirEstatisticas() {
    limparTela();
    
    printf("Estatisticas das Equipes:\n");
    printf("----------------------------------------------------\n");
    printf("|      Equipe      | Gols Marcados | Vitórias | Media de Gols |\n");
    printf("----------------------------------------------------\n");

    for (int i = 0; i < num_equipes; i++) {
        float mediaGols = (num_jogos > 0) ? (float)equipes[i].gols / num_jogos : 0.0; // Calcula a média de gols
        printf("| %-16s | %14d | %8d | %14.2f |\n", 
               equipes[i].nome, equipes[i].gols, equipes[i].vitorias, mediaGols);
    }

    printf("----------------------------------------------------\n");
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
            case 5: carregarDadosEquipes(); break;
            case 6: salvarDadosEquipes(); break;
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
            case 5: carregarDadosJogos(); break;
            case 6: salvarDadosJogos(); break;
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
        printf("3. Determinar Classificados\n");
        printf("4. Listar Dados Gerais\n");
        printf("5. Pesquisar Dados\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao){
            case 1: sortearJogos(); break;
            case 2: chavamentoConfrontos(); break;
            case 3: classificados(); break;
            case 4: listarDados(); break;
            case 5: pesquisar(); break;
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