#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//Declaração de tipos
typedef struct dependente{
    char nome[20];
    int idade;
}dependente;

typedef struct associado{
    int id;
    char nome[20];
    int idade;
    int qtdDep;
    int qtdaulas;
    int Mensalidade;
    dependente dep[3];
    bool natacao;
    bool fotsal;
    bool tenis;
}associado;

//Declaração de funções
//cadastro
associado cadastraAssociado();
dependente cadastraDependente();

//pesquisa
int pesquisaID(associado associados[], int ID, int qtd);
int pesquisaNome(associado associados[], int qtd);

//listas
void listaAssociados (associado associados[], int qtd);
void listaModalidade(associado associados[], int qtd);

//calculadores
int calculamensalidadeAssociado(associado Associado);

//Relatório Geral
int Totdep(associado associados[], int qtd);
int TotNat(associado associados[], int qtd);
int TotFut(associado associados[], int qtd);
int TotTenis(associado associados[], int qtd);
int MnAulas(associado associados[], int qtd);
int TotMen(associado associados[], int qtd);
float MedMens(associado associados[], int qtd);
int MMen(associado associados[], int qtd);

//utilidades
void menu();
void ERROsn(char opc);
void continuar();
void logoCaddependente();
void logolistaAssociados();
void logolistarmodalidade();
void pontinhosdoiscinco();
void logoPesquisa();
void logoRelatorio();
void barrinha();
void logoMenu();

int main(){
    int opc, qtd, i, n, somaqtd, identificador, qtdEstatica;
    associado associados[50];
    associado teste;
    qtd = 0;
    do{
        menu();
        scanf("%d", &opc);
        switch (opc)
        {
        case 1:
            system("clear||cls");
            printf("----------Cadastro De Associado----------\n");

            printf("Quantos associados deseja cadastrar?\n");
            scanf("%d", &somaqtd);

            qtdEstatica = qtd; //como será adicionado 1 à qtd toda vez que for cadastrado um usuário, eu salvei a qtd antes dela entrar no for.

            for (i = qtdEstatica; i < somaqtd+qtdEstatica; i++){ // o for deve iniciar no último item cadastrado, para n sobreescrever.

                teste = cadastraAssociado();

                identificador = pesquisaID(associados, teste.id, qtd);

                if (identificador == -1){
                    if (teste.id != 0){

                        associados[i] = teste;
                        qtd++;

                    }
                    else{
                        /*id == 0 significa cancelamento do cadastro, neste caso a variável associados[i] deverá ser sobrescrita.*/
                        i--;
                        somaqtd--;
                        break;
                    }
                }
                else{
                    pontinhosdoiscinco();

                    printf("\nFalha ao cadastrar: O ID informado já existe...\n");
                    i--;

                    if (i != (somaqtd + qtdEstatica)){
                        continuar();
                    }
                }
            }
            break;

        case 2:
            logoCaddependente();
            printf("Insira o ID do associado: ");            
            scanf("%d", &opc);

            i = pesquisaID(associados, opc, qtd);

            if (i == -1)
                printf("ID não encontrado\n");
            else{
                logoCaddependente();
                printf("Quantos dependentes deseja cadastrar?\n");
                scanf("%d", &opc);

                do{
                    if (opc > 3){
                        printf("ERRO: Número máximo de dependentes igual a 3\nDigite novamente: ");
                        scanf("%d", &opc);
                    }
                    if (opc < 0){
                        printf("ERRO: O número de dependentes deve ser positivo\nDigite novamente: ");
                        scanf("%d", &opc);
                    }
                }while(opc > 3 || opc <0);

                associados[i].qtdDep = opc;

                for (n = 0; n < opc; n++){
                    logoCaddependente();
                    associados[i].dep[n] = cadastraDependente();
                }    

                logoCaddependente();
                for (n = 0; n < opc; n++){

                    printf("NOME DO DEPENDENTE: %s // IDADE DO DEPENDENTE: %d\n", associados[i].dep[n].nome, associados[i].dep[n].idade);
                }

            //Soma de mensalidade com basse nos dependentes
            associados[i].Mensalidade = associados[i].Mensalidade + (50*associados[i].qtdDep);

            }
            
            opc = 0; //Caso a opção escolhida pelo usuário seja 7, isso sairia do programa...
            break;

        case 3:
            logolistaAssociados();
            listaAssociados(associados, qtd);
            break;
        case 4:
            logolistarmodalidade();
            printf("Qual a modalidade?\n");
            printf("------------------\n");
            printf("|Digite:         |\n");
            printf("|N para natação  |\n");
            printf("|F para Futsal   |\n");
            printf("|T para Tênis    |\n");
            printf("------------------\n");
            listaModalidade(associados, qtd);
            break;

        case 5:
            logoPesquisa();
            printf("Digite o nome do associado que deseja pesquisar (da mesma forma que inserida em cadastro).\n");
            printf("NOME: ");

            identificador = pesquisaNome(associados, qtd);


            if (identificador == -1){
                pontinhosdoiscinco();
                printf("ERRO: Associado não encontrado! \n(Verifique se a entrada é igual a presente na lista de associados)\n");
            }
            else{
                logoPesquisa();
                i = identificador; // é mais fácil de escrever...
                printf("Associado nº %d \nNOME: %s // IDADE: %d  \nNÚMERO DE DEPENDENTES: %d // QUANTIDADE DE AULAS: %d \nMENSALIDADE: %d\n", associados[i].id, associados[i].nome, associados[i].idade, associados[i].qtdDep, associados[i].qtdaulas, associados[i].Mensalidade);
            }
            break;
        
        case 6:
            logoRelatorio();
            printf("CADASTROS:\n");
            printf("\n_TOTAL DE ASSOCIADOS >>> %d\n", qtd);
            printf("_TOTAL DE DEPENDENTES >>> %d\n", Totdep(associados, qtd));
            barrinha();

            printf("AULAS:\n");
            printf("\n_TOTAL ALUNOS DE NATAÇÃO >>> %d\n", TotNat(associados, qtd));
            printf("_TOTAL ALUNOS DE FUTSAL >>> %d\n", TotFut(associados, qtd));
            printf("_TOTAL ALUNOS DE TÊNIS >>> %d\n", TotTenis(associados, qtd));
            printf("ASSOCIADO(S) COM MAIOR NÚMERO DE AULA: ");
            for(i = 0; i < qtd; i++){
                if (associados[i].qtdaulas >= MnAulas(associados, qtd)){
                    printf("%s //\n", associados[i].nome);
                }
            }
            barrinha();

            printf("Mensalidade:\n");
            printf("\n_TOTAL MENSALIDADE >>> %d\n", TotMen(associados, qtd));
            printf("MÉDIA MENSALIDADE >>> %.2f\n", MedMens(associados, qtd));
            printf("VALOR MAIS ALTO DE MENSALIDADE >>> %d\n", MMen(associados, qtd));
            barrinha();

            break;
        case 7:
            logoMenu();
            printf("Obrigado! Até logo!\n");
            break;
        default:
            pontinhosdoiscinco();
            printf("Valor inserido inválido (digite um número de 1-7)\n");
            break;
        }
        continuar();
    }while(opc != 7);
}


/*-----------------------------------------------CADASTROS-------------------------------------------------*/
//ASSOCIADO
associado cadastraAssociado(){
    associado Associado;
    char opc;
    int Identificador;

    system("clear||cls");
    printf("----------Cadastro De Associado----------\n");

    printf("ID do associado: ");
    scanf ("%d", &Associado.id);
    do{
        if (Associado.id == 0){
            printf("ID inválido, insira um ID diferente de 0: ");
            scanf("%d", &Associado.id);
        }
    }while(Associado.id == 0);

    printf("\nNome do associado: ");
    getchar();
    scanf ("%[^\n]s", Associado.nome);

    printf("\nIdade do associado: ");
    scanf("%d", &Associado.idade);
    do{
        if (Associado.idade < 0){
            printf("ERRO: A idade deve ser um valor positivo\nDigite novamente: ");
            scanf("%d", &Associado.idade);
        }
    }while (Associado.idade < 0);

    printf("\nO associado faz aula de Natação? (s/n): ");
    getchar();
    scanf("%c", &opc);
    ERROsn(opc);
    if (opc == 's')
        Associado.natacao = true;
    else{
        Associado.natacao = false;
    }

    printf("\nO associado faz aula de Futsal? (s/n): ");
    getchar();
    scanf("%c", &opc);
    ERROsn(opc);
    if (opc == 's')
        Associado.fotsal = true;
    else{
        Associado.fotsal = false;
    }

    printf("\nO associado faz aula de Tênis? (s/n): ");
    getchar();
    scanf("%c", &opc);
    ERROsn(opc);
    if (opc == 's')
        Associado.tenis = true;
    else{
        Associado.tenis = false;
    }
    
    printf("\n\nConfirmar cadastro (ID: %d; NOME: %s; IDADE: %d ;", Associado.id, Associado.nome, Associado.idade);
    if (Associado.natacao) printf("Natação: sim;");
    else printf("Natação: não; ");
                
    if (Associado.fotsal) printf("Futsal: sim;");
    else printf ("Futsal: não; ");

    if (Associado.tenis) printf("Tênis: sim) s/n: ");
    else printf("Tênis: não) s/n: ");
    getchar();
    scanf("%c", &opc);
    ERROsn(opc);

    if (opc == 'n'){
        Associado.id = 0;
    }

    Associado.qtdaulas=0; // para n pegar lixo
    if(Associado.fotsal)
        Associado.qtdaulas++;
    if(Associado.natacao)
        Associado.qtdaulas++;
    if(Associado.tenis)
        Associado.qtdaulas++;

        
    Associado.Mensalidade = calculamensalidadeAssociado(Associado);

    Associado.qtdDep = 0; // tem que definir 0 para não sair número aleatório...

    return Associado;
}
//CADASTRO DE DEPENDENTE
dependente cadastraDependente(){
    dependente Dep;
    
    printf("Digite o nome do dependente: ");
    getchar();
    scanf("%[^\n]s", Dep.nome);

    printf("Idade do dependente: ");
    scanf("%d", &Dep.idade);
    do{
        if (Dep.idade < 0){
            printf("ERRO: A idade deve ser um valor positivo\nDigite novamente: ");
            scanf("%d", &Dep.idade);
        }
    }while (Dep.idade < 0);
    return Dep;
}
/*-------------------------------------------------PESQUISA----------------------------------------------------*/
//POR ID
int pesquisaID(associado associados[], int ID, int qtd){
    int i;
    bool achei;

    for (i = 0; i < qtd; i++){
        if (associados[i].id == ID){
            achei = true;

            break;
        }
    }

    if (achei == false){
        i = -1;
    }
    return i;
}

//POR NOME
int pesquisaNome(associado associados[], int qtd){
    char Nome[20];
    int i;
    bool achei;

    achei = false;

    getchar();
    scanf("%s", Nome);

    for (i = 0; i < qtd; i++){
        if (strcmp(associados[i].nome, Nome) == 0){
            achei = true;
            break;
        }
    }

    if (achei == false){
        i = -1;
    }

    return i;
}

/*----------------------------------------LISTAS--------------------------------------------*/
//ASSOCIADOS
void listaAssociados (associado associados[], int qtd){
    int i;
    for (i = 0; i < qtd; i++){
        printf("ID: %d // Nome: %s // Idade: %d // Número de Dependentes: %d // ",associados[i].id, associados[i].nome, associados[i].idade, associados[i].qtdDep);
        if (associados[i].natacao) printf("Natação: sim // ");
        else printf("Natação: não // ");
                
        if (associados[i].fotsal) printf("Futsal: sim // ");
        else printf ("Futsal: não // ");

        if (associados[i].tenis) printf("Tênis: sim\n");
        else printf("Tênis: não\n");
        pontinhosdoiscinco();
    }
}
//MODALIDADE
void listaModalidade(associado associados[], int qtd){
    char Modalidade;
    int i;
    bool achei;

    achei = false;
    do{
        getchar();
        scanf("%c", &Modalidade);

    
        if(Modalidade == 'n'|| Modalidade == 'N'){
            for (i = 0; i < qtd; i++){
                if (associados[i].natacao == true){
                    printf("%d - %s\n", associados[i].id, associados[i].nome);
                    achei = true;
                }
            }
        }
        if(Modalidade == 'f'|| Modalidade == 'F')
            for (i = 0; i < qtd; i++){
                if (associados[i].fotsal == true){
                    printf("%d - %s\n", associados[i].id, associados[i].nome);
                    achei = true;
                }
            }
            
        if(Modalidade == 't'|| Modalidade == 'T'){
            for (i = 0; i < qtd; i++){
                if (associados[i].tenis == true){
                    printf("%d - %s\n", associados[i].id, associados[i].nome);
                    achei = true;
                }
            }
        }
        if (achei == false){
            printf("ERRO: Modalidade não encontrada (tente N/F/T)\n");
        }
        pontinhosdoiscinco();
    }while(achei == false);
}
/*----------------------------------------CALCULADORES--------------------------------------------*/
int calculamensalidadeAssociado(associado Associado){
    int Passociado, Pdep, Paula, Ptotal;

    Passociado = 100;
    Paula = Associado.qtdaulas*30;
    
    Ptotal = Paula + Passociado;

    return Ptotal;
}
//int calculamensalidadeDependente();

/*----------------------------------------RELATÓRIO GERAL--------------------------------------------*/
//Dependente
int Totdep(associado associados[], int qtd){
    int i, soma;

    soma = 0;

    for (i = 0; i < qtd; i++){
        soma = soma+ associados[i].qtdDep;
    }
    return soma;
}

int TotNat(associado associados[], int qtd){
    int i, soma;

    soma = 0;

    for(i = 0; i < qtd; i++){
        if (associados[i].natacao)
            soma++;
    }
    
    return soma;
}

int TotFut(associado associados[], int qtd){
    int i, soma;

    soma = 0;

    for(i = 0; i < qtd; i++){
        if (associados[i].fotsal)
            soma++;
    }
    
    return soma;
}

int TotTenis(associado associados[], int qtd){
    int i, soma;

    soma = 0;

    for(i = 0; i < qtd; i++){
        if (associados[i].tenis)
            soma++;
    }
    
    return soma;
}

int MnAulas(associado associados[], int qtd){
    int i, maior;

    maior = -1;

    for (i = 0; i < qtd; i++){
        if (associados[i].qtdaulas > maior)
            maior = associados[i].qtdaulas;
    }

    return maior;
}

int TotMen(associado associados[], int qtd){
    int i, soma;

    soma = 0;

    for (i = 0; i < qtd; i++){
        soma = associados[i].Mensalidade + soma;
    }

    return soma;
}

float MedMens(associado associados[], int qtd){
    float media;
    
    media = (float) TotMen(associados,qtd) / qtd;

    return media;
}

int MMen(associado associados[], int qtd){
    int i, Maior;

    Maior = -1;

    for (i = 0; i < qtd; i++){
        if (associados[i].Mensalidade > Maior)
            Maior = associados[i].Mensalidade;
    }

    return Maior;
}
/*----------------------------------------UTILIDADES--------------------------------------------*/
void menu(){
    system("clear||cls");
    printf("----------Menu----------\n");
    printf("1 - Cadastrar associado\n");
    printf("2 - Cadastrar dependente\n");
    printf("3 - Listar associados\n");
    printf("4 - Listar associados por modalidade\n");
    printf("5 - Pesquisar associados\n");
    printf("6 - Gerar relatório de associados\n");
    printf("7 - Finalizar programa\n");
}

void continuar(){
    char continuar;

    printf("Aperte Enter para continuar\n");
    getchar();
    scanf("%c", &continuar);
}

void ERROsn(char opc){
    do{
        if (opc != 's' && opc != 'n' && opc != 'S' && opc != 'N'){
            printf("\nValor inserido inválido, isira s ou n (para sim ou não): ");
            fflush(stdin);
            scanf("%c", &opc);
        }
    }while (opc != 's' && opc != 'n' && opc != 'S' && opc != 'N');
}

void logoCaddependente(){
    system("clear||cls");
    printf("----------Cadastrar Dependente----------\n");
}

void logolistaAssociados(){
    system("clear||cls");
    printf("----------Lista de Associados----------\n");
}

void logolistarmodalidade(){
    system("clear||cls");
    printf("----------Listar por Modalidade----------\n");
}

void pontinhosdoiscinco(){
    printf("-------------------------\n");
}

void logoPesquisa(){
    system("clear||cls");
    printf("----------Pesquisar Associados----------\n");
}

void logoRelatorio(){
    system("clear||cls");
    printf("----------Relatório Geral----------\n");
}

void barrinha(){
    printf("////////////////////////////////////\n");
}

void logoMenu(){
    system("clear||cls");
    printf("----------MENU----------\n");
}