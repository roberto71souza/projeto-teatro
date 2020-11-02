/*
Programa desenvolvido por Roberto de Souza Gomes e Daniel Pereira Julião   
sob orientaçao do Pfs. Luiz Fernando, e pesquisas.                             
*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
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
int valida(int num, int *ant, int cont);//esta funcao e a responsavel por validar e revalidar as cadeiras sorteados
void edita (int sort,int cont);
void chamaSorteio();//funcao que chama o sorteio
void CadeiraNum();//declara a funcao que preenche os lugares com numeros
void painel();//declara a funcao que mostra a matriz
void compra();//declara a funcao que faz a compra dos lugares
void cad();//Funcao responsavel por cadastrar o usuario
int resp;
int matriz[linha*coluna];
FILE *ponteiroArquivo;  //ponteiro usado para abrir o arquivo 
/*
estrutura de dados que sera usado para
para complementar o arquivo do cadastro dos participantes do teatro
*/
struct cadastro{
    char nome [50];
    char cpf [15];
    char email [30];
    };
     struct cadastro aux;
/*
funcao main onde  todoas as funcoes sao chamadas, e
tratamento de erros que o usuario digita no programa
*/
int main(){
	int opcao=0;
	
	/* a partir destas duas variaveis e criada um contador para que quando acabar os ingressos
	o sistema nao permitir a entrada de usuarios.
	*/
	int partida=0;
	int final=92;
	
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

    cadeiraNum(matriz);//aqui complementa a funcao cadeiraNum(matriz); Mostrando o estado de compra atualizado!.

    do{
		//a partir daqui e mostrado para o usuario as opcoes do programa principal
         system("cls"); 
         printf("\n\n\t\t\t\t\t\t\t\t\t\t\t|MENU|\n\t\t\t\t\t\t\t\t______________________________________________________\n");      
         printf("\t\t\t\t\t\t\t\t| 1- RESERVAR CADEIRA     (Ainda restam (%d) lugares)|\n",final-partida);        
         printf("\t\t\t\t\t\t\t\t| 2- MOSTRAR PAINEL DE LUGARES\t\t\t     |\n"); 
		 printf("\t\t\t\t\t\t\t\t| 3- SORTEIO \t\t\t\t\t     |\n");       
         printf("\t\t\t\t\t\t\t\t| 4- SAIR\t\t\t\t\t     |\n");        
         printf("\t\t\t\t\t\t\t\t                 DIGITE UMA OPCAO:");
		 scanf("%d",&opcao);               
                       
     switch(opcao){
            case 1:
                system("cls");
                /*
				Aqui a partir deste if e definido ate quando o sistema vai rodar,
				foram criadas duas variaveis final iniciada com o valor 92, e partida valor 0, que sera encrementada ++,
				a comparacao e feita com a partida enquanto ela for menor do que 92, o sistema
				vai permitir a entrada de usuarios, quando chegar a 92 o usuario nao podera fazer
				o cadastro e consequentemente nao vai escolher o assento.
				a variavel final ela vai mostrar para usuario logo em frente a opcao Reservar cadeira.
				*/
                if(partida<92){
				/*
				antes de escolher o assento e chamada a funcao de cadastro,
				logo apos o usuario estiver cadastrado ele podera escolher seu assento.
				*/			
                cad();
                getch();
                system("cls");
                painel(matriz);
                /*
				tratando o que o usuario digita, por exemplo assentos que nao existem,
				assentos preferenciais,assentos reservados, e assentos ja comprados.
				*/
                while(1){
                    printf("\n\nDigite o numero da cadeira desejada: \n");
                    scanf("%d",&resp);

                    if ((resp<=0) || (resp>=122)){
                        printf("Esta cadeira nao existe!!!Escolha outra!\n");
                        getch();
                    }else if ((resp>=1) && (resp<=22)){
                        printf("Esta cadeira ja esta reservada!!!Escolha outra!\n");
                        getch();
                    }else if ((resp>=23) && (resp<=28)){
                        printf("Esta cadeira e preferencial!!!Escolha outra!\n");
                        getch();
                    }else if (matriz[resp-1]==0){
                        printf("Esta cadeira esta ocupada!!! Escolha outra!\n");
                        getch();
                    }else {
                        matriz[resp-1] = 0;
                        break;
                   }
                }
                
                /*
				a partir daqui e reaalizado a reabertura do arquivo
				para que na mensagem de confirmacao seja mostrada o nome do comprador e o email do Comprador.
				*/
                ponteiroArquivo=fopen("arquivo.txt","r");
                fgets(nomes,30,ponteiroArquivo);
                fgets(email,30,ponteiroArquivo);

                fclose(ponteiroArquivo);
                system("cls");

                _strtime( timeStr );
                printf("\n\n\t\t\t\t\t\t\t\t\t\tCOMPROVANTE DE COMPRA\n\n");
				printf("\t\t\t\t\t\t\t\t Parabens Sr. %s pela sua compra no dia %d/%d/%d as %s \n\n",aux.nome, data_hora_atual->tm_mday,data_hora_atual->tm_mon+1,data_hora_atual->tm_year+1900,timeStr);
                printf("\t\t\t Enviaremos para o seu email %s um ticket avisando o numero do seu assento (%d),e informacoes do horario de entrada e saida da apresentacao!!!",aux.email,resp);
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			partida++;
                }else{
                	printf("\t\t\t\tATENCAO!!!\nNao existem mais lugares no teatro\n");
				}
                system("pause");
                break;
                
            case 2:
                system("cls");
                /*
				aqui e chamado a funcao painel que contem a matriz
				*/
                painel( matriz);
                printf("\n\n");
                system("pause");
                break;
                
            case 3:
                system("cls");
                /*
				Aqui e chamada a funcoo que ira sortear os participantes!
				*/
                chamaSorteio();
                system("pause");
                break;

            case 4:
				/*
				selecionando este este caso o programa nao vai retornar nada e vais sair
				*/
                return 0;
                break;

            default:
                printf("OPCAO INVALIDA!!!\n");
                system("pause");
            break;
         }
    }while(1==1);

    system("pause");
    return(0);
}

//esta e a funcao responsavel por preencher todos os lugares do teatro com numeros!e iniciando os valores de preferencial e reservados.
void cadeiraNum(){
    int c,l;
    int num = 1;

    for(l=0;l<linha;l++)
        for(c=0;c<coluna;c++){
            matriz[l*linha+c]=num;
            num++;
        }
    /*
	aqui na 3° linha ate a 6° coluna sera iniciado com o valor 333,para identificar
	o assento preferencial que posteriormente na funcao painel o valor visivel para o usuario sera(P).
	*/
    matriz[2*linha+0]=333;
    matriz[2*linha+1]=333;
    matriz[2*linha+2]=333;
    matriz[2*linha+3]=333;
    matriz[2*linha+4]=333;
    matriz[2*linha+5]=333;
    
    /*
	com a mesma ideia de iniciar primeiro com o valor, que aqui sera 222,
	a 1° e a 2° fileira, ate a decima-primeira coluna, e o visivel para oo usuario sera(R).
	*/
    matriz[0*linha+0]=222;
    matriz[0*linha+1]=222;
    matriz[0*linha+2]=222;
    matriz[0*linha+3]=222;
    matriz[0*linha+4]=222;
    matriz[0*linha+5]=222;
    matriz[0*linha+6]=222;
    matriz[0*linha+7]=222;
    matriz[0*linha+8]=222;
    matriz[0*linha+9]=222;
    matriz[0*linha+10]=222;
    /*
	2° fileira ate 11° coluna;
	*/
    matriz[1*linha+0]=222;
    matriz[1*linha+1]=222;
    matriz[1*linha+2]=222;
    matriz[1*linha+3]=222;
    matriz[1*linha+4]=222;
    matriz[1*linha+5]=222;
    matriz[1*linha+6]=222;
    matriz[1*linha+7]=222;
    matriz[1*linha+8]=222;
    matriz[1*linha+9]=222;
    matriz[1*linha+10]=222;
}

//esta e a funcao que mostra as linhas e as colunas do teatro matriz a tribui (R),(P),(C) para os indices 222,333,0
void painel(){
    int c,l;
    printf("\n\t\t\t\t\t\tPAINEL DE OCUPACOES   \n\n");
    printf("          ");



	/*
	Com esse for todos indices do painel e varrido
	ao encontrar os valore 222,333 e 0, com o if ele adiciona 
	os valores que sera visivel para o usuario (R), (P) e (C).
	*/
    for(c=0;c<coluna;c++)
        printf("\t%d",c+1);

    for(l=0;l<linha;l++){
        printf("\n\n\t%d",l+1);
        for(c=0;c<coluna;c++)
            if(matriz[l*linha+c]==222){
                printf("\t(R)");
            }else if((matriz[l*linha+c]==0)){
                printf("\t(C)");
            }
            else if(matriz[l*linha+c]==333){
                printf("\t(P)");
            }else
                printf("\t(%d)",matriz[l*linha+c]);

    }
    printf("\n\n\t(29-121) - LUGAR LIVRE    (P) - Assento preferencial   (C) - CADEIRA JA COMPRADA   (R) CADEIRA RESERVADA\n");
}

/*
Funcao que e responsavel para cadastrar o usuario e armazenar suas informacoes.
*/
void cad(){
	/*
	a partir deste codigo o arquivo.txt e criado
	*/ 
    ponteiroArquivo=(fopen("arquivo.txt","a"));
    printf("\t\t\t\t\t\t\t\t\tSEJA BEM VINDO AO TEATRO DA UNIP!!\n\n");
    printf("\t\t\t\t\t\t\tAntes de comprar a cadeira vamos fazer um breve cadastro........\n\npresssione ENTER para continuar......\n\n\n");
    getch();
    /*
	O usuario Digita as informacoes pedidas
	*/ 
    getchar();
    printf("\t\t\t\t\t\t\t\tDigite seu nome: ");
    gets(aux.nome);	
    fflush(stdin);

    printf("\t\t\t\t\t\t\t\tDigite seu CPF: ");  
    gets(aux.cpf);
	fflush(stdin);
	
    printf("\t\t\t\t\t\t\t\tDigite seu Email: ");
    gets(aux.email);
	fflush(stdin);
	
    /*
	e com o fprintf organizamos as informacoes digitadas no arquivo.
	*/ 
    printf("\n");
    
	fprintf(ponteiroArquivo, "\n------------------------\n");
    fprintf(ponteiroArquivo,"nome: %s\n",aux.nome);
    fprintf(ponteiroArquivo,"CPF: %s\n",aux.cpf);
    fprintf(ponteiroArquivo,"Email: %s\n",aux.email);

    fclose(ponteiroArquivo);
}
/*
A partir daqui e criado as funcoes que vao fazer o sorteio
dos participantes, esse conjunto de funcoes e responsavel por
gerar os assentos aleatorios, e tambem revalidar assentos que poderiam
ser sorteados mais de uma vez.

*/
void chamaSorteio(){
	int i;
	int sorteados[4];
	
	srand(time(NULL));
	
	printf("\t\t\t\t\t\t\t\t\t--------|SORTEIO|--------\n\n");
	
	for(i=0;i<4;i++){
		sorteados[i] = valor_minimo+rand()%(valor_maximo-valor_minimo);
		if(i==0){
			edita(sorteados[i],i);
		}
		else {
			sorteados[i] = valida(sorteados[i],sorteados,i);
			edita(sorteados[i],i);
		}
	}
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
		getch();
		printf("\n\t\t\t\t\t\t\t\t     Parabens a todos os premiados!!");
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		getch();
}

int valida(int num, int *ant, int cont){
	int aux;
	
	for(aux=0;aux<cont;aux++){
		while(num==*(ant+aux)){
			num=valor_minimo+rand()%(valor_maximo-valor_minimo);
		}		
	}
	return num;
}
void edita (int sort,int cont){
			
		printf("\t\t\t\t\t\t\t\t%d-premiado usuario da caderia : %.2d\n",cont+1,sort);		
		
}
