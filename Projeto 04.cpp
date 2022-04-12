#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>
#include <limits.h>
#include <ctype.h>

#define VETOR_TAM 200000

typedef int vetor[VETOR_TAM];

void build_max_heap(vetor vet, int tam);
void max_heapify(vetor vet, int tam, int i);
void heap_sort(vetor vet, int tam);

long long get_ms();

int ler_vet(char *arq, vetor vet, int *tam);
void imprimir_amostras_vet(vetor vet, int tam);

void menu();

int main( int argc, char** argv ) {
	vetor vet;
	
	int tam, num;
	long long ms1, ms2;

	char op = '1';
	char continuar = 's';
	char leu;

	char path[ 256 ];
	
	if ( argc == 2 ) {
		leu = ler_vet( argv[1], vet, &tam );
		if ( leu ) {
			printf( "\nAs Amostras foram carregadas com sucesso!" );
			build_max_heap( vet, tam );
			printf( "\nO Vetor foi ordenado com sucesso!" );
		} else {
			printf( "\nHouve uma Falha na leitura do arquivo: %s", path );
		}	
		printf( "\n" );
	}
			
	do {
		menu();
		printf( "\nInforme sua escolha: " );

		fflush(stdin);
		fflush(stdout);
		op = getchar();

		switch ( op ) {			
			case '1':
				do {
					printf( "Informe um elemento que deseja inserir: " );
					scanf( "%d", &num );
				
					vet[ tam++ ] = num;
										
					printf( "Deseja inserir um outro elemento? (S/N): " );
					fflush(stdin);
					fflush(stdout);
					continuar = getchar();
				} while( tolower( continuar ) == 's' ); 
				
				build_max_heap( vet, tam );
				break;
			case '2':
				imprimir_amostras_vet( vet, tam );
				break;
			case '3':				
				ms1 = get_ms();
				heap_sort(vet, tam);
				ms2 = get_ms();
				printf( "\nO Vetor foi ordenado em: %lldms", (ms2 - ms1) );				
				break;
			case '0':
				printf( "\nPrecione a Tecla Enter para sair da Aplicacao...\n" );
				break;
			default:
				printf( "\nEsta opcao e invalida, tente novamente!" );
		}

		if ( op != '0' ) {
			if ( op != '0' )
				printf( "\nPrecione a Tecla Enter para continuar..." );
			fflush(stdin);
			fflush(stdout);
			getc(stdin);
		}

	} while ( op != '0' );

	return 0;
}

void menu() {
	printf("\n|************ MENU **************|");
	printf("\n|                                 ");
	printf("\n|  (1) Inserir elementos no Vetor ");
	printf("\n|  (2) Listar elementos do Vetor  ");
	printf("\n|  (3) Utilizar Ordenacao por Heapsort");
	printf("\n|  (0) Sair da Aplicacao          ");
	printf("\n|                                 ");
	printf("\n|********************************|\n");
}

int ler_vet( char *arqnome, vetor vet, int *tam ) {
	int i;
	FILE *arq;
	char linha[10];

	arq = fopen( arqnome, "r" );
	if ( arq == NULL )
		return 0;

	fgets( linha, sizeof( linha ), arq );
	*tam = atoi( linha );

	for ( i = 0; i < *tam; i++) {
		fgets( linha, sizeof(linha), arq );
		vet[ i ] = atoi( linha );
	}

	fclose( arq );

	return 1;
}

void imprimir_amostras_vet( vetor vet, int tam ) {
	int i;

	printf( "\nSegue o Vetor Armazenado = " );
	for ( i = 0; i < tam; i++ )
		printf( "%d ", vet[i] );	
	printf("\n");
}

void max_heapify( vetor vet, int tam, int i ) {
	int esqI, dirI;
	int maiorI;
	int aux;
	
	
	esqI = 2*(i+1)-1;
	dirI = 2*(i+1);
	if ( esqI < tam ) {
		if ( vet[ esqI ] > vet[ i ] ) {
			maiorI = esqI;
		} else {
			maiorI = i;
		}
	} else {
		maiorI = i;
	}
	
	if ( dirI < tam )
		if ( vet[ dirI ] > vet[ maiorI ] )
			maiorI = dirI;
	
	if ( maiorI != i ) {
		aux = vet[ i ];
		vet[ i ] = vet[ maiorI ];
		vet[ maiorI ] = aux;
		max_heapify( vet, tam, maiorI );		
	}
}

void build_max_heap( vetor vet, int tam ) {	
	int c;
	int i;	
	int log, profundidade;
	
	log = (int)log2( tam );
	profundidade = ( log == log2( tam ) ? log-1 : log );
	c = 0;
	for( i = 0; i <= profundidade; i++ )
		c += pow( 2, i );

	for( i = (c-1)/2; i >= 0; i-- )
		max_heapify( vet, tam, i );	
}

void heap_sort( vetor vet, int tam ) {
	int i, aux, len;
	for( len = tam; len > 1; len-- ) {
		aux = vet[ 0 ];
		vet[ 0 ] = vet[ len-1 ];
		vet[ len-1 ] = aux;
		max_heapify( vet, len-1, 0 );
	}
}

long long get_ms() {
	struct timeval t;
	gettimeofday(&t, NULL);
	return (((long long)(t.tv_sec) * 1000)) + (t.tv_usec / 1000);
}
