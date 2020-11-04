/*
Programa desenvolvido por Roberto de Souza Gomes e Daniel Pereira Juliao   
sob orientacao do Pf. Luiz Fernando, e pesquisas.                             
*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/*
Declaracao das constantes que serao usadas no parametro da matriz linha* coluna,
e no sorteio definindo o valor minimo e valor maximo de cadeiras a serem sorteados.
*/
#define linha 11
#define coluna 11
#define valor_minimo 29
#define valor_maximo 121
/*
declaracao das funcoes que foram usadas para complementar o programa.
*/
void OpcaoMenu(int opcao);
void ConfirmacaoCompra(int resp);
void Cadastro();
void SalvarArquivo(int resp);
void PreencherMatriz();
void Painel();
void ChamaSorteio();
int ValidaSorteio(int num, int *ant, int cont);
void Edita(int sort, int cont);
/* a partir destas duas variaveis e criada um contador para que quando acabar os ingressos
	o sistema nao permitir a entrada de usuarios.
*/
int partida = 0;
int final = 92;
int resp;
int matriz[linha * coluna];
FILE *ponteiroArquivo; //ponteiro usado para abrir o arquivo
/*
estrutura de dados que sera usado para
para complementar o arquivo do cadastro dos participantes do teatro
*/
struct cadastro
{
    char nome[50];
    char cpf[15];
    char email[30];
    int cadeira;
};
struct cadastro aux;
/*
funcao main onde  todoas as funcoes sao chamadas, e
tratamento de erros que o usuario digita no programa
*/
int main()
{
    int opcao = 0;

    PreencherMatriz(); //Chamando a funcao que monta todo corpo do teatro, ja definindo lugares reservados, preferenciais e livres.

    do
    {
        //a partir daqui e mostrado para o usuario as opcoes do programa principal
        system("cls");
        printf("\t\t\t|MENU|\n");
        printf("_____________________________________________________\n");
        printf("| 1- RESERVAR CADEIRA     (Ainda restam (%d) lugares)|\n", final - partida);
        printf("| 2- MOSTRAR PAINEL DE LUGARES\t\t\t     |\n");
        printf("| 3- SORTEIO \t\t\t\t\t     |\n");
        printf("| 4- SAIR\t\t\t\t\t     |\n");
        printf("                 DIGITE UMA OPCAO:");
        scanf("%d", &opcao);

        OpcaoMenu(opcao);

    } while (1 == 1);

    system("pause");
    return (0);
}

void OpcaoMenu(int opcao)
{
    switch (opcao)
    {
    case 1:
        system("cls");
        /*
			Aqui a partir deste if e definido ate quando o sistema vai rodar,
			foram criadas duas variaveis final iniciada com o valor 92, e partida valor 0, que sera encrementada ++,
			a comparacao e feita com a partida enquanto ela for menor do que 92, o sistema
			vai permitir a entrada de usuarios, quando chegar a 92 o usuario nao podera fazer
			o cadastro e consequentemente nao vai escolher o assento.
		*/
        if (partida < final)
        {
            /*
				antes de escolher o assento e chamada a funcao de cadastro,
				logo apos o usuario estiver cadastrado ele podera escolher seu assento.
			*/
            Cadastro();
            getch();
            /*
				tratando o que o usuario digita, por exemplo assentos que nao existem,
				assentos preferenciais,assentos reservados, e assentos ja comprados.
			*/
            while (1)
            {
                Painel();
                printf("\n\nDigite o numero da cadeira desejada: \n");
                scanf("%d", &resp);

                if (resp <= 0 || resp > 121)
                {
                    printf("Esta cadeira nao existe!!!Escolha outra!\n");
                    getch();
                    system("cls");
                }
                else if (matriz[resp - 1] == 222)
                {
                    printf("Esta cadeira ja esta reservada!!!Escolha outra!\n");
                    getch();
                    system("cls");
                }
                else if (matriz[resp - 1] == 333)
                {
                    printf("Esta cadeira e preferencial!!!Escolha outra!\n");
                    getch();
                    system("cls");
                }
                else if (matriz[resp - 1] == 0)
                {
                    printf("Esta cadeira esta ocupada!!! Escolha outra!\n");
                    getch();
                    system("cls");
                }
                else
                {
                    matriz[resp - 1] = 0;
                    /*
                    apos a escolha da cadeira o cadastro e finalizado salvando junto com a cadeira escolhida.
                    */
                    SalvarArquivo(resp);
                    break;
                }
                system("cls");
            }
            ConfirmacaoCompra(resp);
            partida++;
        }
        else
        {
            printf("\t\t\t\tATENCAO!!!\nNao existem mais lugares no teatro\n");
        }
        system("pause");
        break;

    case 2:
        system("cls");
        /*
			aqui e chamado a funcao painel que contem a matriz
		*/
        Painel();
        printf("\n\n");
        system("pause");
        break;

    case 3:
        system("cls");
        /*
			Aqui e chamada a funcoo que ira sortear os participantes!
		*/
        ChamaSorteio();
        system("pause");
        break;

    case 4:
        /*
			selecionando este este caso o programa nao vai retornar nada e vais sair
		*/
        system("pause");
        exit(0);
        break;

    default:
        printf("OPCAO INVALIDA!!!\n");
        system("pause");
        break;
    }
}
void ConfirmacaoCompra(int resp)
{
    /*
	variaveis que serao usadas para mostrar nome e o email do participante
	na confirmacao da compra.
	*/
    char nomes[30];
    char email[30];
    /*
	variaveis que serao usadas no programa para mostrar
	para o usuario da data e hora da realizacao do programa
	*/
    char timeStr[9];
    struct tm *data_hora_atual;
    time_t segundos;
    time(&segundos);
    data_hora_atual = localtime(&segundos);
    /*
				a partir daqui e realizado a reabertura do arquivo
				para que na mensagem de confirmacao seja mostrada personalizada para cada usuario.
			*/
    ponteiroArquivo = fopen("arquivo.txt", "r");
    fgets(nomes, 30, ponteiroArquivo);
    fgets(email, 30, ponteiroArquivo);

    fclose(ponteiroArquivo);
    system("cls");

    _strtime(timeStr);
    printf("\tCOMPROVANTE DE COMPRA\n\n");
    printf("\tParabens Sr. %s pela sua compra no dia %d/%d/%d as %s \n\n", aux.nome, data_hora_atual->tm_mday, data_hora_atual->tm_mon + 1, data_hora_atual->tm_year + 1900, timeStr);
    printf("\tEnviaremos para o seu email %s um ticket avisando o numero do seu assento (%d),e informacoes do horario de entrada e saida da apresentacao!!!", aux.email, resp);
    printf("\n\n\n");
}
/*
Funcao que e responsavel para cadastrar o usuario.
*/
void Cadastro()
{
    /*
	a partir deste codigo o arquivo.txt e criado
	*/
    ponteiroArquivo = (fopen("arquivo.txt", "a"));
    do
    {
        system("cls");
        printf("\t\tSEJA BEM VINDO AO TEATRO DA UNIP!!\n\n");
        printf("\t\tAntes de comprar a cadeira vamos fazer um breve cadastro........\n\npresssione ENTER para continuar......\n\n\n");
        /*
	O usuario Digita as informacoes pedidas
	*/
        getchar();
        printf("\t\tDigite seu nome: ");
        gets(aux.nome);
        fflush(stdin);

        printf("\t\tDigite seu CPF: ");
        gets(aux.cpf);
        fflush(stdin);

        printf("\t\tDigite seu Email: ");
        gets(aux.email);
        fflush(stdin);
    } while (strlen(aux.nome) == 0 || strlen(aux.cpf) == 0 || strlen(aux.email) == 0);
}
//Complementa a funcao de cadastro
void SalvarArquivo(int resp)
{
    aux.cadeira = resp;
    /*
	e com o fprintf organizamos as informacoes digitadas no arquivo.
	*/
    printf("\n");
    fprintf(ponteiroArquivo, "\n------------------------\n");
    fprintf(ponteiroArquivo, "nome: %s\n", aux.nome);
    fprintf(ponteiroArquivo, "CPF: %s\n", aux.cpf);
    fprintf(ponteiroArquivo, "Cadeira: %d\n", aux.cadeira);
    fprintf(ponteiroArquivo, "Email: %s\n", aux.email);

    fclose(ponteiroArquivo);
}
//esta e a funcao responsavel por preencher todos os lugares do teatro com numeros, e iniciando com valores definidos no indice do vetor.
void PreencherMatriz()
{
    int c, l;
    int num = 1;

    for (l = 0; l < linha; l++)
    {
        for (c = 0; c < coluna; c++)
        {
            matriz[l * linha + c] = num;
            num++;
        }
    }

    /*
    do ascento 23 ao 28 sera adicionado no indice do vetor o valor 333 ,para identificar
	o assento preferencial que posteriormente na funcao painel o valor visivel para o usuario sera(P).
	*/
    for (c = 0; c < 6; c++)
    {
        matriz[2 * linha + c] = 333;
    }

    /*
	com a mesma ideia de iniciar primeiro com o valor, que aqui sera 222,
	do primeiro ascento ate o 22°, e o visivel para oo usuario sera(R).
	*/
    for (l = 0; l < 2; l++)
    {
        for (c = 0; c < linha; c++)
        {
            matriz[l * linha + c] = 222;
        }
    }
}

//esta e a funcao que mostra as linhas e as colunas do teatro matriz a tribui (R),(P),(C) para os indices 222,333,0
void Painel()
{
    int c, l;
    printf("\n\t\t\t\t\t\tPAINEL DE OCUPACOES   \n\n");
    printf("          ");

    /*
	Com esse for todos indices do painel e varrido
	ao encontrar os valore 222,333 e 0, com o if ele adiciona 
	os valores que sera visivel para o usuario (R), (P) e (C).
	*/
    for (c = 0; c < coluna; c++)
        printf("\t%d", c + 1);

    for (l = 0; l < linha; l++)
    {
        printf("\n\n\t%d", l + 1);
        for (c = 0; c < coluna; c++)
            if (matriz[l * linha + c] == 222)
            {
                printf("\t(R)");
            }
            else if ((matriz[l * linha + c] == 0))
            {
                printf("\t(C)");
            }
            else if (matriz[l * linha + c] == 333)
            {
                printf("\t(P)");
            }
            else
                printf("\t(%d)", matriz[l * linha + c]);
    }
    printf("\n\n\t(29-121) - LUGAR LIVRE    (P) - Assento preferencial   (C) - CADEIRA JA COMPRADA   (R) CADEIRA RESERVADA\n");
}
/*
A partir daqui e criado as funcoes que vao fazer o sorteio
dos participantes, esse conjunto de funcoes e responsavel por
gerar os assentos aleatorios, e tambem revalidar assentos que poderiam
ser sorteados mais de uma vez.

*/
void ChamaSorteio()
{
    int i;
    int sorteados[4];

    srand(time(NULL));

    printf("\t\t\t\t\t--------|SORTEIO|--------\n\n");

    for (i = 0; i < 4; i++)
    {
        sorteados[i] = valor_minimo + rand() % (valor_maximo - valor_minimo);
        if (i == 0)
        {
            Edita(sorteados[i], i);
        }
        else
        {
            sorteados[i] = ValidaSorteio(sorteados[i], sorteados, i);
            Edita(sorteados[i], i);
        }
    }
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------- ");
    getch();
    printf("Parabens a todos os premiados!!");
    printf("\n\n");
    getch();
}

int ValidaSorteio(int num, int *ant, int cont)
{
    int aux;

    for (aux = 0; aux < cont; aux++)
    {
        while (num == *(ant + aux))
        {
            num = valor_minimo + rand() % (valor_maximo - valor_minimo);
        }
    }
    return num;
}
void Edita(int sort, int cont)
{

    printf("\t\t\t\t%d-premiado usuario da caderia : %.2d\n", cont + 1, sort);
}
