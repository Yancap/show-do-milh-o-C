#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <pthread.h>

//Declaracao das variaveis globais, que podem ser acessadas e modificadas pelas funcoes sem precisar de parametros e retornos

pthread_t tarefas[1];  //Vetor de tipo 'pthread_t' proprio para armazenar os IDs das threads a serem criadas
int parametro = 1; //Variavel a ser usada como parametro na funcao 'pthread_create()'
int iniciaC = 0;  //Variavel de controle, indica o inicio ou fim da execucao do cronometro (off = 0, on = 1)
int tempoC = 0;  //Variavel de controle, indica que 

char vetorRespostaUsuario[20]; //Armazena a resposta do jogador atual

//Matriz que armazena as perguntas em ordem
	char  matrizPergunta[30][70] = {"Em qual esporte é realizada a jogada chamada “strike”?", //1
								   "Qual cantor fez muito sucesso com a música “Rodo do cotidiano”?", //2
								   "Qual a capital da Alemanha?", //3
								   "Qual revolução teve seu início após a Queda da Bastilha?", //4
								   "Qual fruto é conhecido no Norte e Nordeste como 'jerimum'?", //5
								   "Qual é o nome da lei que protege a mulher da violência doméstica?", //6
								   "Qual bicho transmite Doença de Chagas?", //7
								   "Qual é o nome dado ao estado da água em forma de gelo?", //8
								   "Quantas folhas de papel formam uma resma?", //9
								   "Qual dessas novelas não teve Fernanda Montenegro em seu elenco?", //10
								   "Quem é a namorada do Mickey?", //11
								   "Qual é o personagem do folclore brasileiro que tem uma perna só?", //12
								   "O adjetivo 'venoso' está relacionado a:", //13
								   "Quem é o patrono do exército brasileiro?", //14
								   "Quando é comemorado o dia da independência do Brasil?", //15
								   "A compensação por perda é chamada de…", //16
								   "O estádio do Maracanã fica localizado:", //17
								   "O que é a Via Láctea?", //18
								   "Quem fundou a Microsoft?", //19
								   "Qual é o nome do cachorro medroso do Salsicha, dos desenhos animados?", //20
								   "Onde fica o centro da indústria cinematográfica nos EUA?", //21
								   "Qual era o código da identidade secreta de James Bond?", //22
								   "Qual destes é considerado o mês das noivas?", //23
								   "A que letra do nosso alfabeto corresponde a letra grega tau?", //24
								   "Qual é o nome do Patriarca da Independência do Brasil?", //25
								   "Qual personagem bíblico dividiu as águas do Mar Vermelho?", //26
								   "Quantas folhas tem um trevo da sorte?", //27
								   "Quem é o segundo maior cestinha da NBA?", //28
								   "O churrasco é considerado uma comida típica de qual estado?", //29
								   "Qual é a sigla da Organização das Nações Unidas?", //30
								   };
								   
//Matriz que armazena as perguntas em ordem										 
	char matrizResposta[4][35][35]{{"a) Futebol",  "a) O Rappa",  "a) Viena",   "a) Revolução Industria","a) Caju","a) Lei Maria Dolores","a) Abelha","a) Líquido","a) 300 folhas","a) Passione","a) Margarida","a) Cuca","a) Vela","a) Marechal Deodoro","a) 21 de Abril","a) Déficit","a) Em São Paulo","a) Marca de leite","a) Sultão de Brunei","a) Floquinho","a) Nova York","a) 007","a) Julho","a) T","a) Tiradentes","a) Moisés","a) 3","a) Stephen Curry","a) Rio de Janeiro","a) ONU"}, //Alternativa A
  							      {"b) Basquete", "b) Renato Russo",  "b) Bruxelas","b) Revolução Francesa","b) Chuchu","b) Lei Antonieta","b) Barata","b) Sólido", "b) 500 folhas","b) Doce de mãe","b) Minnie","b) Saci-Pererê","b) Vento","b) Barão de Mauá","b) 12 de Outubro","b) Indenização","b) No Rio de Janeiro","b) Civilização Antiga","b) Akio Morita","b) Coragem","b) Las Vegas","b) 707","b) Agosto","b) H","b) Dom Pedro II","b) Jonas","b) 4","b) Lebron James","b) Paraná", "b) OTAN"}, //Alternativa B
 								  {"c) Beisebol", "c) Roberto carlos","c) França",  "c) Revolução Socialista Russa","c) Abóbora","c) Lei Maria da Penha","c) Pulga","c) Gasoso","c) 250 folhas","c) O outro lado do paraíso","c) A pequena sereia","c) Negrinho do Pastoreio","c) Vênia","c) Duque de Caxias","c) 7 de Setembro","c) Indexação","c) Em Porto Alegre","c) Carro","c) Bill Gates","c) Lassie","c) New Orleans","c) 907","c) Setembro","c) J","c) José Bonifácio","c) Josué","c) 5","c) Michael Jordan","c) Santa Catarina","c) CIA"}, //Alternativa C
  								  {"d) Boliche",  "d) Gilberto Gil",  "d) Berlim",  "d) Revolução Gloriosa Inglesa","d) Côco","d) Lei Maria do Carmo","d) Barbeiro","d) Vaporoso","d) 420 folhas","d) Avenida Brasil","d) Olivia Palito","d) Boitatá","d) Veia","d) Marquês Pombal","d) 25 de Dezembro","d) Indébito","d) Em Belo Horizonte","d) Galáxia","d) Jair Bolsonaro","d) Scooby-Doo","d) Hollywood","d) 077","d) Maio","d) F","d) Vasco da Gama","d) Isaías ","d) 2","d) Kevin Durant","d) Rio Grande do Sul","d) FMI"}, //Alternativa D
   };

//Vetores que organiza os valores que o usuario vai ganhar ou perder
int dinheiroGanho[21] = {0, 500, 1000, 2000, 3000, 4000, 5000, 6000, 10000, 20000, 30000, 40000, 50000, 60000, 100000, 200000, 300000, 4000000, 500000, 600000, 1000000}; //Dinheiro que usuario vai ganhar se acertar
int dinheiroPerdido[21] = {0, 350, 400, 450, 500, 1000, 1500, 2000, 2500, 3000, 5000, 10000, 15000, 20000, 25000, 30000, 50000, 100000, 150000, 200000, 250000}; //Dinheiro que o usuario vai ganhar se desistir ou errar


//Funcao de gerar numero aleatorios nao repetidos
int aleatorio(int indice,int limite){	//(indice do vetor, numero maximo a ser gerado)
	int random[limite];
	int j, igual;
	int aux = 0;
    int i = 0;
	 
    srand(time(NULL));/*Funcao que define uma regra(semente) para a gerecao de numeros procedurais
    				  A funcao 'srand' esta recebendo o valor de 'time(NULL)' como parametro usado como semente
    				  A funcao 'time(NULL)' gera um numero diferente a cada inicializacao do programa
    				  (retorna o tempo, contado em segundos, desde 01/01/1970)
    				  */

    do{ //Executa o algoritmo pelo menos uma vez antes de verificar a condicao do 'while'
        
		random[i] = rand() % limite; // sorteia um número
        igual = 0;
        for(j = 0; j < i; j++){ // percorre a parte do vetor já preenchida
            if(random[j] == random[i])
                igual = 1; // número repetido
        }

        if(igual == 0) // significa que o elemento não se repetiu
            i++;
    }while(i < limite); // enquanto não for sorteado 25 números diferentes

	return random[indice];
}

//Função que mostra a tela inicial
int telaCadastro(){
//Tela 1 - capa do programaga e cadastro
    
    system("cls");
	system ("color 97"); // cor de fundo azul claro e letras brancas
    
	printf("\n  		S H O W   D O   M I L H Ã O			\n\n\n");
	printf(" 		 ________________________\n");
    printf("		|                        |\n");
    printf("		| C A D A S T R A - S E  |\n");
    printf("		|________________________|\n\n");
	

}

//Função que mostra a tela do menu
int telaMenu(){


system("color 97");
system("cls");

printf("\n");
printf("           _____________________________________\n");
printf("          |                                     |\n");
printf("          |      S H O W  D O  M I L H Ã O      |\n");
printf("          |_____________________________________|\n");


printf("                                      \n");
printf("                     	 ______ \n");
printf("                    	| MENU |\n");
printf("                    	|______|\n");
printf("                                      \n");

printf("          	 __________________________ \n");
printf("          	|    1 - INICIAR O JOGO    |\n");
printf("          	|__________________________|\n");

printf("          	 __________________________ \n");
printf("          	|    2 - RANKING           |\n");
printf("          	|__________________________|\n");

printf("          	 __________________________ \n");
printf("          	|    3 - CRÉDITOS          |\n");
printf("          	|__________________________|\n");

printf("          	 __________________________ \n");
printf("          	|    4 - FECHAR O JOGO     |\n");
printf("          	|__________________________|\n");

printf("\n>> ");
}

char telaCadastro(char nome[], int i){
	
	system ("cls"); // limpa a tela
	system ("color 97"); // cor de fundo azul claro e letras brancas
    printf("   Digite seu nome: ");
    scanf("%s", &nome);
	printf("\n\n\n\n\n\n\n\n\n\nENTER - Avançar ");
	return nome[10];
}

//Função que mostra as regras do jogo
char telaRegras(char nome[], int i){
	
	system ("cls"); // limpa a tela
	system ("color C7"); // cor de fundo vermelho claro e letras brancas
	printf("Seja bem-vindo(a), %s!\n", nome);
    printf(" ________________________________________________________________________________________\n");
    printf("|REGRAS:                                                                                 |\n");
    printf("|Universitários - Três estudantes de diversas faculdades dão suas respostas à pergunta   |\n");
    printf("|e cabe ao participante confiar ou não.                                                  |\n");
    printf("|                                                                                        |\n");
    printf("|Cartas - Quatro cartas de baralho são viradas e o participante escolhe uma. Se tirar o  |\n");
    printf("|Rei, nenhuma alternativa errada é eliminada. Ás elimina uma alternativa, 2 elimina duas |\n");
    printf("|alternativas e 3 elimina todas as três alternativas erradas, restando apenas a correta. |\n");
    printf("|                                                                                        |\n");
    printf("|Pulos - O participante pode passar a pergunta caso não saiba a resposta. Este recurso   |\n"); 
    printf("|pode ser utilizado até três vezes.                                                      |\n");
    printf("|                                                                                        |\n");
    printf("|Tempo - Voce so tem 30 segundos para responder cada pergunta. Quando o tempo acaba voce |\n");
    printf("|ainda devera responder, porém irá perder independentemente da resposta.                 |\n");
    printf("|________________________________________________________________________________________|\n");
	printf("\n\nENTER - Avançar \n\n\n");
	getch();
}

//Função que mostra as Perguntas, Respostas e quanto vai ganhar
int telaPergunta(char pergunta[], char alternativaA[], char alternativaB[], char alternativaC[], char alternativaD[], int i){
	//getch();
	system("cls");
   system("color 97");
   printf("|---------------------------------------- RODADA %d ----------------------------------------\n", i);
   printf(" __________________________________________________________________________________________\n");
   printf("|%d %s                                 |\n", i, pergunta);
   printf("|__________________________________________________________________________________________\n\n");
   
   printf(" __________________________________________________________________________________________\n");
   printf("|%s                                                                                \n", alternativaA);
   printf("|__________________________________________________________________________________________\n");
   
   printf(" __________________________________________________________________________________________\n");
   printf("|%s                                                                               \n", alternativaB);
   printf("|__________________________________________________________________________________________\n");

   printf(" __________________________________________________________________________________________\n");
   printf("|%s                                                                               \n", alternativaC);
   printf("|__________________________________________________________________________________________\n");
    
   printf(" __________________________________________________________________________________________\n");
   printf("|%s                                                                                \n", alternativaD);
   printf("|__________________________________________________________________________________________\n\n");
   
   
   
  //Mostra as Ajudas
		printf("                                     A J U D A                                             \n");
  	    printf("          ________             ________________            ________           ________    \n");
  	    printf("         |1-Cartas|           |2-Universitários|          |3- Pular|         |4- Parar|   \n");
  	    printf("         |________|           |________________|          |________|         |________|    \n\n");
  	


}

//Tela que mostra o valor a ser recebido e perdido
int telaQuantoGanhar(int perdido,int parar, int ganho){
	printf("               __________            __________             __________                      \n");
    printf("              /         /           /         /            /         /                      \n");
    printf("                %d                    %d                     %d                         \n", perdido, parar, ganho);
    printf("            /_________/           /_________/            /_________/                       \n");
    printf("              ERRAR                4 - PARAR               ACERTAR                         \n");
}

//Função que mostra o ranking
int telaRanking(char nome,int dinheiro){
	int i = 0, index = 0;
	getch();
    system("cls");
    system("color 97");
    printf("                            ________________________                                        \n");
    printf("                           |                        |                                       \n");
    printf("                           |      R A N K I N G     |                                       \n");
    printf("                           |________________________|                                       \n\n");
    while(i < index){
	
    printf("  %s ---------------------------------------------------------------------- R$ %f\n",nome,dinheiro);
    i++;
	}
}
int aux = 0, aux1;


//Funcao Universitarios
int universitario(char gabarito,int contRodada, int controlQuestao[]){ //o parametro "gabarito" vai receber o valor correspondente ao vetor gabarito
    char auxChar[5] = {"abcd"};
    int auxInt = aleatorio(0,3);
    char resp;
    system("cls");
    system("color 97");
    printf("Universitario 1 >> %c\n", gabarito); //Resposta Correta
    printf("Universitario 2 >> %c\n", gabarito); //Resposta Correta
    printf("Universitario 3 >> %c\n", auxChar[auxInt]); //Resposta Correta ou não
    printf("\n\nAperte Enter para continuar >>");
    getch();
	
   //Mostra a pergunta
   system("cls");
   system("color 97");
   printf("|---------------------------------------- RODADA %d ----------------------------------------\n", contRodada);
   printf(" __________________________________________________________________________________________\n");
   printf("|%d %s                                 |\n",  contRodada+1, matrizPergunta[controlQuestao[contRodada]]);
   printf("|__________________________________________________________________________________________\n\n");
   
   
    for(int i = 0; i < 4; i++){
    	
        if(matrizResposta[i][contRodada][0] != gabarito && aux > 0){ //Se o indice da alternativa for diferente ao da resposta certa E o auxiliar for maior que zero ele vai ser removido      												
        	//Mostra as alternativas removida
        	 printf(" __________________________________________________________________________________________\n");
  			 printf("|                                                                               \n");
  			 printf("|__________________________________________________________________________________________\n\n");
        	
           
            aux--;
        } else {
        	//Mostra as alternativas não removidas
        	 printf(" __________________________________________________________________________________________\n");
  			 printf("|%s                                                                                \n",  matrizResposta[i][controlQuestao[contRodada]]);
  			 printf("|__________________________________________________________________________________________\n\n");
        
        }
       
    }
     //Mostra as Ajudas
		printf("                                     A J U D A                                             \n");
  	    printf("          ________             ________________            ________           ________    \n");
  	    printf("         |1-Cartas|           |2-Universitários|          |3- Pular|         |4- Parar|   \n");
  	    printf("         |________|           |________________|          |________|         |________|    \n\n");
    
}

//Funcao Cartas									
int cartas(char gabarito, int contRodada, int controlQuestao[]){
    int aux = 0;
    aux = aleatorio(1,4); //Gera um valor aleatorio de quantas alternativas vai ser removidas
    
    system("cls");
    system("color 97");
    if(aux == 0){
		aux++;
	}
	aux1 = aux;
    printf("%d Alternativas Removidas", aux);
    getch();
	
   //Mostra a pergunta
   system("cls");
   system("color 97");
   printf("|---------------------------------------- RODADA %d ----------------------------------------\n", contRodada);
   printf(" __________________________________________________________________________________________\n");
   printf("|%d %s                                 |\n",  contRodada+1, matrizPergunta[controlQuestao[contRodada]]);
   printf("|__________________________________________________________________________________________\n\n");
   
   
    for(int i = 0; i < 4; i++){
    	
        if(matrizResposta[i][contRodada][0] != gabarito && aux > 0){ //Se o indice da alternativa for diferente ao da resposta certa E o auxiliar for maior que zero ele vai ser removido      												
        	//Mostra as alternativas removida
        	 printf(" __________________________________________________________________________________________\n");
  			 printf("|                                                                               \n");
  			 printf("|__________________________________________________________________________________________\n\n");
        	
           
            aux--;
        } else {
        	//Mostra as alternativas não removidas
        	 printf(" __________________________________________________________________________________________\n");
  			 printf("|%s                                                                                \n",  matrizResposta[i][controlQuestao[contRodada]]);
  			 printf("|__________________________________________________________________________________________\n\n");
        
        }
        
    }
     //Mostra as Ajudas
		printf("                                     A J U D A                                             \n");
  	    printf("          ________             ________________            ________           ________    \n");
  	    printf("         |1-Cartas|           |2-Universitários|          |3- Pular|         |4- Parar|   \n");
  	    printf("         |________|           |________________|          |________|         |________|    \n\n");
  	    
	return aux1;
}

//Funcao que conta o tempo passado por parametro em segundos
int cronometro(int tempo){
  //Variaves
  int seg = tempo; //Variavel segundos comeca com tempo maximo
  int min = 0;
  int num;
  
//enquanto o valor de segundos forem maior do que o 0 ele ficara dentro do while, decrescendo em 1, a cada 1 segundo
	while(seg >= 0) {	
  		
		if(seg == 30 || seg == 20 || seg == 10){
  		    printf ("\n\t\t\t\tVocê tem %dm:%ds\n", min, seg); //imprime de maneira atualizada o tempo faltante, a cada 10 segundos
  		}
  	
		Sleep (1000); //aqui o tempo ira parar o programa ate quando chegar a 1000 milesegundos e dara prosseguimento
		
		seg--; //indice segundos que recebera sempre menos 1, a cada 1000 repeticao
		
		//Se o jogador responder, saira da repeticao, parando de contar o tempo
		if(iniciaC == 0){
			break;
		}
		
	}

//Quando o tempo acaba, se o jogador nao tiver respondido, sera mostrado a mensagem "TEMPO ESGOTADO" 
  if(iniciaC != 0){
	printf("\nTEMPO ESGOTADO\n");
	tempoC = -1;  //Modifica a variavel de controle para -1, indicando o tempo esgotado
  }
  
}

//Funcao que sera associada ao primeiro thread (alem do thread principal)
void * tarefa_f1( void * p_param){
	
	int y = *((int *) p_param );  //Converte o valor de 'void * p_param' para int
	y = 1;
	
//Essa funcao ira ficar verificando, em segundo plano, se fora indicado para iniciar o cronometro
	while(y == 1){
		if(iniciaC == 1){
			
			cronometro(30);	//Aqui a funcao cronometro recebe o parametro 30, que corresponde aos segundos a serem contados
				
		}
		
		iniciaC = 0;  //Aqui reniciamos a variavel responsavel por permitir o inicio do cronometro
		Sleep(2000);  //Espera de 2 segundos para que o while nao verifique varias vezes por segundo desnecessariamente
	}
	
	pthread_exit(0);  //Finaliza o thread no final da funcao
}

//Funcao que verifica se o usuario digitou uma das alternativas validas, se nao for, faz o processo pergunta novamente
char verificar(int indexRodada, int contRodada, int *controlQuestao){
		//Verifica se a resposta e valida
		while(vetorRespostaUsuario[contRodada] != 'a' && vetorRespostaUsuario[contRodada] != 'b' && vetorRespostaUsuario[contRodada] != 'c' && vetorRespostaUsuario[contRodada] != 'd' && vetorRespostaUsuario[contRodada] != '1' && vetorRespostaUsuario[contRodada] != '2' && vetorRespostaUsuario[contRodada] != '3' && vetorRespostaUsuario[contRodada] != '4'){
						
		//Enquanto o jogador nao digitar uma alternativa valida, reimprimirá a tela da questao atual para que ele digite uma alternativa valida
		telaPergunta(matrizPergunta[controlQuestao[contRodada]], matrizResposta[0][controlQuestao[contRodada]], matrizResposta[1][controlQuestao[contRodada]], matrizResposta[2][controlQuestao[contRodada]], matrizResposta[3][controlQuestao[contRodada]], indexRodada+1);
		telaQuantoGanhar(dinheiroPerdido[indexRodada], dinheiroGanho[indexRodada], dinheiroGanho[indexRodada + 1]);
				    					    			    	
		//Pede pro jogador digitar outra resposta
		iniciaC = 1; //Indica para a thread do cronometro iniciar a contagem
				    	
		printf("\n\nDigite uma resposta valida!!!");
		printf("\n>> ");
		scanf("%s", &vetorRespostaUsuario[contRodada]);
												
		iniciaC = 0; //Indica para a thread do cronometro parar a contagem, pois o jogador ja respondeu
						
		}
}

int main(){
	setlocale(LC_ALL,"portuguese");
	
	pthread_create(&tarefas[0], NULL, tarefa_f1, &parametro);
															//1 parametro: variavel com Id da thread armazenado
															//2 parametro: opcoes da thread(em geral NULL), 
															//3 parametro: ponteiro da funcao que ira ser executada na thread 
															//4 parametro: parametro que a thread ira receber
	
	
	//Vetor que armazena o gabarito em ordem, conforme as Matrizes das Respostas e Perguntas
	char vetorGabarito[40] = {"dadbccdbbdbbdccbbdcddadacabbda"};
	
	//Estrutura que armazena os dados para cada usuario
	struct dadosUsuario{
		char nome[10];
		int dinheiro = 0;
		int rodada = 0;
	};
	
	
	//================== Sessão do Menu e Tela Inicial =================
	int menu = 0, i = 0, jogs = 0, indexRodada;
	dadosUsuario vetorDadosUsuarios[10];
	
	while(menu != 4){
		
		//Renicia as variaveis de controle
		menu = 0;
		i = 0;
	
		//Imprime o menu principal
		telaMenu();
		
		scanf("%d", &menu); //Recebe a opcao escolhida do menu
		fflush(stdin); //Limpa o cache do dispositivo de entrada padrao para evitar bugs
		
		if(menu == 1){
			//Entrada de Dados da Quantidade de jogadores
			telaCadastro();
			printf("\nQuantos jogadores vão participar? (Max: 10): ");
			scanf("%d", &jogs);
			fflush(stdin); //Limpa o cache do dispositivo de entrada padrao para evitar bugs
		
			//Inicio da partida
			while(i < jogs){
			
			//Sessão de Declaração/Reinicialização das variaveis e vetores
										     
				//char vetorRespostaUsuario[20]; //Vetor que armazena as questões do usuario	
				
				int quantUniversitario = 0, quantCartas = 0, quantPular = 0, auxPulo = 0;
				//Indices que auxilia na organização dos vetores e rodadas
				int contRodada = 0, indicePergunta; 
				indexRodada = 0;
				//Vetor que armazena e organiza os indices para serem usados nas Matrizes de perguntas, respostas e gabarito
				int controlQuestao[20];
				
				//Entrada do nome
			    //Aguarda o jogador apertar enter
				system ("cls"); // limpa a tela
				system ("color 97"); // cor de fundo azul claro e letras brancas
	    		printf("   Digite seu nome: ");
	    		scanf("%s", &vetorDadosUsuarios[i].nome);
				
				
				telaRegras(vetorDadosUsuarios[i].nome, i); //Mostra a tela de regras, com o nome do usuario
				
				//Estrutura para armazenas os indices aleatorios no Vetor
				for(int index = 0; index < 20; index++){
				//Funcao que gera e verifica se o numero aleatorio gerado foi repetido e armazena em um vetor de controle no indice correspondente
					controlQuestao[index] = aleatorio(index, 30);
					
				}
				
				//Repeticao que passa em cada pergunta por vez
				while(contRodada < 20 && indexRodada < 20){
				
					
				    //===========================================================
				    //Pega o indice aleatorio do vetor e armazena na variavel
				    indicePergunta = controlQuestao[contRodada];
				    
				    //======== Sessão de Perguntas ==========
				    telaPergunta(matrizPergunta[controlQuestao[contRodada]], matrizResposta[0][controlQuestao[contRodada]], matrizResposta[1][controlQuestao[contRodada]], matrizResposta[2][controlQuestao[contRodada]], matrizResposta[3][controlQuestao[contRodada]], indexRodada+1);
				    telaQuantoGanhar(dinheiroPerdido[indexRodada], dinheiroGanho[indexRodada], dinheiroGanho[indexRodada + 1]);
				
                    
					
					//Indica para a thread do cronometro iniciar a contagem
					iniciaC = 1;
				    
					//Recebe a resposta do usuario
					printf("Digite sua resposta: ");
					scanf("%s", &vetorRespostaUsuario[contRodada]);
					vetorRespostaUsuario[contRodada] = tolower(vetorRespostaUsuario[contRodada]);
					//Indica para a thread do cronometro parar a contagem, pois o jogador ja respondeu
					//iniciaC = 0;
					
					//Verifica se a reposta e valida
					verificar(indexRodada, contRodada, controlQuestao);
					
					//================= Sessão de Ajudas ==================
					
					//O loop vai rodar enquanto as resposta do usuario for correspondente as ajudas
					while(vetorRespostaUsuario[contRodada] == '1' || vetorRespostaUsuario[contRodada] == '2' || vetorRespostaUsuario[contRodada] == '3'){
						
						//Verifica se o usuario digitou a resposta conforme ao indice da ajuda Universitario E verifica se o usuario tem a ajuda disponivel
						if(vetorRespostaUsuario[contRodada] == '2' && quantUniversitario < 1){
							//Funcao Universitario
							universitario(vetorGabarito[controlQuestao[contRodada]], contRodada, controlQuestao);
							telaQuantoGanhar(dinheiroPerdido[indexRodada], dinheiroGanho[indexRodada], dinheiroGanho[indexRodada + 1]);
							
					
							//Indica para a thread do cronometro iniciar a contagem
							//iniciaC = 1;
				    
							//Recebe a resposta do usuario
							printf("Digite sua resposta: ");
							scanf("%s", &vetorRespostaUsuario[contRodada]);
							vetorRespostaUsuario[contRodada] = tolower(vetorRespostaUsuario[contRodada]);
							//Indica para a thread do cronometro parar a contagem, pois o jogador ja respondeu
							//iniciaC = 0;
							
							//Verifica se a reposta e valida
							verificar(indexRodada, contRodada, controlQuestao);
							
							quantUniversitario++;
							
						} else {
							//Se caso ele não possui a ajuda, vai mostrar as perguntas e respotas e o loop vai rodar até ele digitar a resposta ou outra ajuda DISPONIVEL
							while(vetorRespostaUsuario[contRodada] != 'a' && vetorRespostaUsuario[contRodada] != 'b' && vetorRespostaUsuario[contRodada] != 'c' && vetorRespostaUsuario[contRodada] != 'd' && vetorRespostaUsuario[contRodada] != '1'  && vetorRespostaUsuario[contRodada] != '3'  && vetorRespostaUsuario[contRodada] != '4'){
								
								telaPergunta(matrizPergunta[controlQuestao[contRodada]], matrizResposta[0][controlQuestao[contRodada]], matrizResposta[1][controlQuestao[contRodada]], matrizResposta[2][controlQuestao[contRodada]], matrizResposta[3][controlQuestao[contRodada]], indexRodada+1);
				   				telaQuantoGanhar(dinheiroPerdido[indexRodada], dinheiroGanho[indexRodada], dinheiroGanho[indexRodada + 1]);
								//iniciaC = 1;
								printf("\n\nVocê não tem mais ajuda de universitarios!!!");
								printf("\nDigite sua resposta: ");
								scanf("%s", &vetorRespostaUsuario[contRodada]);
								vetorRespostaUsuario[contRodada] = tolower(vetorRespostaUsuario[contRodada]);
								//iniciaC = 0;
							}
						}
							//Verifica se o usuario digitou a resposta conforme ao indice da ajuda Cartas E verifica se o usuario tem a ajuda disponivel
						if(vetorRespostaUsuario[contRodada] == '1' && quantCartas < 1){
							//Funcao Cartas
							aux1 = cartas(vetorGabarito[controlQuestao[contRodada]], contRodada, controlQuestao);
							telaQuantoGanhar(dinheiroPerdido[indexRodada], dinheiroGanho[indexRodada], dinheiroGanho[indexRodada + 1]);
							//Indica para a thread do cronometro iniciar a contagem
							//iniciaC = 1;
						    
							//Recebe a resposta do usuario
							printf("Digite sua resposta: ");
							scanf("%s", &vetorRespostaUsuario[contRodada]);
							vetorRespostaUsuario[contRodada] = tolower(vetorRespostaUsuario[contRodada]);
							//iniciaC = 0;
							if(vetorRespostaUsuario[contRodada] == '2'){
									aux = aux1;
							}
							while(vetorRespostaUsuario[contRodada] != 'a' && vetorRespostaUsuario[contRodada] != 'b' && vetorRespostaUsuario[contRodada] != 'c' && vetorRespostaUsuario[contRodada] != 'd' && vetorRespostaUsuario[contRodada] != '1' && vetorRespostaUsuario[contRodada] != '2' && vetorRespostaUsuario[contRodada] != '3' && vetorRespostaUsuario[contRodada] != '4'){
						
									
											    					    			    	
									//Pede pro jogador digitar outra resposta
									//iniciaC = 1; //Indica para a thread do cronometro iniciar a contagem
											    	
									printf("\n\nDigite uma resposta valida!!!");
									printf("\n>> ");
									scanf("%s", &vetorRespostaUsuario[contRodada]);
									vetorRespostaUsuario[contRodada] = tolower(vetorRespostaUsuario[contRodada]);										
									//iniciaC = 0; //Indica para a thread do cronometro parar a contagem, pois o jogador ja respondeu
													
							}
							
							//Indica para a thread do cronometro parar a contagem, pois o jogador ja respondeu
							
									
							quantCartas++;
						} else {
							//Se caso ele não possui a ajuda, vai mostrar as perguntas e respotas e o loop vai rodar até ele digitar a resposta ou outra ajuda DISPONIVEL
							while(vetorRespostaUsuario[contRodada] != 'a' && vetorRespostaUsuario[contRodada] != 'b' && vetorRespostaUsuario[contRodada] != 'c' && vetorRespostaUsuario[contRodada] != 'd'  && vetorRespostaUsuario[contRodada] != '2'  && vetorRespostaUsuario[contRodada] != '3'  && vetorRespostaUsuario[contRodada] != '4'){
								
								telaPergunta(matrizPergunta[controlQuestao[contRodada]], matrizResposta[0][controlQuestao[contRodada]], matrizResposta[1][controlQuestao[contRodada]], matrizResposta[2][controlQuestao[contRodada]], matrizResposta[3][controlQuestao[contRodada]], indexRodada+1);
				   				telaQuantoGanhar(dinheiroPerdido[indexRodada], dinheiroGanho[indexRodada], dinheiroGanho[indexRodada + 1]);
								
								printf("\n\nVocê não tem mais ajuda das Cartas!!!");
								//iniciaC = 1;
								printf("\nDigite sua resposta: ");
								scanf("%s", &vetorRespostaUsuario[contRodada]);
								vetorRespostaUsuario[contRodada] = tolower(vetorRespostaUsuario[contRodada]);
								//iniciaC = 0;
							}
						}
						
							//Verifica se o usuario digitou a resposta conforme ao indice ao Pulo E verifica se o usuario tem a ajuda disponivel
						if(vetorRespostaUsuario[contRodada] == '3' && quantPular < 3){
							
							auxPulo = 1; //Indica pro sistema que um pulo foi realizado
							system("cls");
							system("color 97");
							printf("Voce Pulou!!!\n\n");
							printf("Aperte Enter para voltar >>");
						 	getch();
							//Gasta 1 pulo do total de pulos 
							quantPular++; 
							indexRodada--;
							break;			
							
						
						} else {
							//Se caso ele não possui a ajuda, vai mostrar as perguntas e respotas e o loop vai rodar até ele digitar a resposta ou outra ajuda DISPONIVEL
							while(vetorRespostaUsuario[contRodada] != 'a' && vetorRespostaUsuario[contRodada] != 'b' && vetorRespostaUsuario[contRodada] != 'c' && vetorRespostaUsuario[contRodada] != 'd' && vetorRespostaUsuario[contRodada] != '1'  && vetorRespostaUsuario[contRodada] != '2'  && vetorRespostaUsuario[contRodada] != '4'){
								
								telaPergunta(matrizPergunta[controlQuestao[contRodada]], matrizResposta[0][controlQuestao[contRodada]], matrizResposta[1][controlQuestao[contRodada]], matrizResposta[2][controlQuestao[contRodada]], matrizResposta[3][controlQuestao[contRodada]], indexRodada+1);
				   				telaQuantoGanhar(dinheiroPerdido[indexRodada], dinheiroGanho[indexRodada], dinheiroGanho[indexRodada + 1]);
								iniciaC = 1;
								printf("\n\nVocê não tem mais a Possibilidade de Pular!!!");
								printf("\nDigite sua resposta: ");
								scanf("%s", &vetorRespostaUsuario[contRodada]);
								vetorRespostaUsuario[contRodada] = tolower(vetorRespostaUsuario[contRodada]);
								iniciaC = 0;
								
							}
							
						}
						
					}
					iniciaC = 0;
					//Se ele escolheu pular, vai mostrar essa parte
					if (auxPulo == 1){
		   				 
		  				 system("cls");
		    		     system("color 97");
		    		     indexRodada++;
		    		     contRodada--;
		   				 printf("Voce tem apenas %d pulos\n\n", 3 - quantPular);
		   				 printf("Aperte Enter para voltar >>");
						 getch();
		    			 auxPulo = 0;
					} else {
						
					//================ Sessão que Verifica as Respostas ===================
					
						if (vetorRespostaUsuario[contRodada] == vetorGabarito[controlQuestao[contRodada]] && tempoC != -1){
							//Sessão Caso o Usuario Acerte
							
							system("cls");
		   					system("color 27");			
		  					printf("                                P A R A B É N S ! ! !                                       \n");
		  					printf("                                    VOCÊ RECEBEU                                            \n");
		  					printf("                                   R$   %d                                               \n", dinheiroGanho[indexRodada+1]);
		  					vetorDadosUsuarios[i].rodada++; //O Usuario Ganha a Rodada
							vetorDadosUsuarios[i].dinheiro =  dinheiroGanho[indexRodada+1]; //O Usuario ganha o dinheiro
							indexRodada++; //Continua a Rodada
							printf("Aperte Enter para continuar >>");
							getch();
						} else if(vetorRespostaUsuario[contRodada] == '4' ){
							//Sessão se Caso o usuario desista
							
							system("cls");
		   					system("color E0");							
		  					printf("                                D E S I S T I U ! ! !                                       \n");
		  					printf("                                VOCÊ RECEBE APENAS                                           \n");
		  					printf("                                   R$   %d                                               \n", dinheiroGanho[indexRodada]);
							vetorDadosUsuarios[i].dinheiro =  dinheiroGanho[indexRodada];
							printf("Aperte Enter para voltar >>");
							getch();
							break; //Finaliza a Rodada
							
						} else if(tempoC == -1) {
							//Sessão se caso o tempo acabe
							
							system("cls");
		   					system("color 07");
		  					printf("                                   O TEMPO ACABOU! ! !                                       \n");
		  					printf("                                   VOCÊ PERDEU                                            \n");
		  					printf("                                   R$   %d                                               \n", dinheiroPerdido[indexRodada]);
		  					vetorDadosUsuarios[i].dinheiro = dinheiroPerdido[indexRodada]; 
		  					printf("Aperte Enter para voltar >>");
							getch();
							break; //Finaliza a Rodada
							
						} else {
							//Sessão se caso o usuario errar
							
							system("cls");
		   					system("color 47");
		  					printf("                                   E R R O U ! ! !                                       \n");
		  					printf("                                   VOCÊ PERDEU                                            \n");
		  					printf("                                   R$   %d                                               \n", dinheiroPerdido[indexRodada]);
		  					vetorDadosUsuarios[i].dinheiro = dinheiroPerdido[indexRodada];
		  					printf("Aperte Enter para voltar >>");
							getch();
							break;
							
						}
						if(vetorDadosUsuarios[i].dinheiro == 1000000){
								system("cls");
								system("color 27");
							    printf("	 __________________________________________________________________________________________\n");
   								printf("	|                                                                                          |\n");
   								printf("	|                          PARABENS VOCE CONQUISTOU O PREMIO MAXIMO                        |\n");
  								printf("	|__________________________________________________________________________________________|\n");
  								
  								printf("\nAperte Enter para voltar para o menu >>");
  								getch();
						}
					
					}
					contRodada++;
					
				}
				
				i++;
			}
		}		
		if(menu == 2){
			// ========= Sessão do Ranking =========
			
			int j = 0;
			
		    system("cls");
		    system("color 97");
		    printf("                            ________________________                                        \n");
		    printf("                           |                        |                                       \n");
		    printf("                           |      R A N K I N G     |                                       \n");
		    printf("                           |________________________|                                       \n\n");
		    
			if(jogs == 0){
				//Caso se nenhum jogador for cadastrado
		    	
		    	printf("                       Nenhum jogador foi cadastrado\n\n\n");
		    	
		    	
			}else {
				//Mostra essa estrutura
		    	printf("_____________________________________________________________________________________________________\n");
			while(j < jogs){
				//Mostra todos os jogadores que estão na partida, suas rodadas ganhas e seu dinheiro
		    	printf("NOME: %s               RODADAS GANHAS: %d                    DINHEIRO: R$ %d\n",vetorDadosUsuarios[j].nome, vetorDadosUsuarios[j].rodada, vetorDadosUsuarios[j].dinheiro);
		    	printf("\n------------------------------------------------------------------------------------------------------\n");
		    	j++;
			}
				printf("______________________________________________________________________________________________________\n");
			}
			printf("Aperte Enter para voltar >>");
			getch();
		}		 
		if (menu == 3){
			// ========= Sessão de Créditos ========
			system("cls");
			system ("color 97");
			printf("Time de Desenvolvimento\n");
			printf(" Yan Gabriel\n Pedro Henrique\n Davi Gabriel\n Daniel Correia\n Tierre Arouche\n Diana Medeiros\n Marcos Vinicius\n Gabriel Almeida\n\n");
			printf("Aperte Enter para voltar >>");
			getch();
		} if (menu == 4){
		
		
			// ========= Fim do Jogo ===============
			system("cls");
			system("color 97");
			printf("Crétidos...");
			printf("Time de Desenvolvimento\n");
			printf(" Yan Gabriel\n Pedro Henrique\n Davi Gabriel\n Daniel Correia\n Tierre Arouche\n Diana Medeiros\n Marcos Vinicius\n Gabriel Almeida\n\n");
			printf("Aperte enter pra sair >>");
			getch();
		}
	}
	
	
	return 0;
}
