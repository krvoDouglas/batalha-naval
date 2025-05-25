#include <stdio.h>
#include <stdlib.h>

// Definindo constantes para melhor legibilidade do código
#define TAMANHO_TABULEIRO 10    // Tamanho do tabuleiro (10x10)
#define TAMANHO_NAVIO 3         // Tamanho fixo de cada navio
#define AGUA 0                  // Valor que representa água no tabuleiro
#define NAVIO 3                 // Valor que representa parte do navio no tabuleiro
#define NUM_NAVIOS 4            // Número total de navios no jogo

// Enumeração para as orientações possíveis dos navios
typedef enum {
    HORIZONTAL,     // Navio posicionado horizontalmente
    VERTICAL,       // Navio posicionado verticalmente  
    DIAGONAL_DESC,  // Navio posicionado na diagonal descendente (\)
    DIAGONAL_ASC    // Navio posicionado na diagonal ascendente (/)
} Orientacao;

// Estrutura para representar um navio
typedef struct {
    int linha_inicial;      // Linha inicial do navio
    int coluna_inicial;     // Coluna inicial do navio
    Orientacao orientacao;  // Orientação do navio
} Navio;

// Função para inicializar o tabuleiro com água (valor 0)
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    int i, j;
    
    // Percorre toda a matriz e inicializa com valor AGUA (0)
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para verificar se uma posição está dentro dos limites do tabuleiro
int posicao_valida(int linha, int coluna) {
    return (linha >= 0 && linha < TAMANHO_TABULEIRO && 
            coluna >= 0 && coluna < TAMANHO_TABULEIRO);
}

// Função para verificar se é possível posicionar um navio em uma determinada posição
int pode_posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                         Navio navio) {
    int i;
    int linha = navio.linha_inicial;
    int coluna = navio.coluna_inicial;
    
    // Verifica cada posição que o navio ocupará
    for (i = 0; i < TAMANHO_NAVIO; i++) {
        int linha_atual = linha;
        int coluna_atual = coluna;
        
        // Calcula a posição atual baseada na orientação do navio
        switch (navio.orientacao) {
            case HORIZONTAL:
                coluna_atual = coluna + i;
                break;
            case VERTICAL:
                linha_atual = linha + i;
                break;
            case DIAGONAL_DESC:
                linha_atual = linha + i;
                coluna_atual = coluna + i;
                break;
            case DIAGONAL_ASC:
                linha_atual = linha + i;
                coluna_atual = coluna - i;
                break;
        }
        
        // Verifica se a posição está dentro dos limites do tabuleiro
        if (!posicao_valida(linha_atual, coluna_atual)) {
            return 0; // Posição inválida
        }
        
        // Verifica se a posição já está ocupada por outro navio
        if (tabuleiro[linha_atual][coluna_atual] != AGUA) {
            return 0; // Posição já ocupada
        }
    }
    
    return 1; // Posicionamento válido
}

// Função para posicionar um navio no tabuleiro
void posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                     Navio navio) {
    int i;
    int linha = navio.linha_inicial;
    int coluna = navio.coluna_inicial;
    
    // Posiciona cada parte do navio no tabuleiro
    for (i = 0; i < TAMANHO_NAVIO; i++) {
        int linha_atual = linha;
        int coluna_atual = coluna;
        
        // Calcula a posição atual baseada na orientação do navio
        switch (navio.orientacao) {
            case HORIZONTAL:
                coluna_atual = coluna + i;
                break;
            case VERTICAL:
                linha_atual = linha + i;
                break;
            case DIAGONAL_DESC:
                linha_atual = linha + i;
                coluna_atual = coluna + i;
                break;
            case DIAGONAL_ASC:
                linha_atual = linha + i;
                coluna_atual = coluna - i;
                break;
        }
        
        // Marca a posição como ocupada pelo navio
        tabuleiro[linha_atual][coluna_atual] = NAVIO;
    }
}

// Função para exibir o tabuleiro no console
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    int i, j;
    
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n\n");
    
    // Exibe o cabeçalho com números das colunas
    printf("   ");
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    
    // Exibe cada linha do tabuleiro
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i); // Número da linha
        
        // Exibe cada coluna da linha atual
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == AGUA) {
                printf(" ~ "); // Representa água
            } else {
                printf(" X "); // Representa parte do navio
            }
        }
        printf("\n");
    }
    printf("\nLegenda: ~ = Água, X = Navio\n\n");
}

// Função para obter o nome da orientação (para debug/informação)
const char* obter_nome_orientacao(Orientacao orientacao) {
    switch (orientacao) {
        case HORIZONTAL: return "Horizontal";
        case VERTICAL: return "Vertical";
        case DIAGONAL_DESC: return "Diagonal Descendente";
        case DIAGONAL_ASC: return "Diagonal Ascendente";
        default: return "Desconhecida";
    }
}

int main() {
    // Declaração da matriz que representa o tabuleiro
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Definição dos quatro navios com suas posições e orientações
    Navio navios[NUM_NAVIOS] = {
        {2, 1, HORIZONTAL},      // Navio 1: Horizontal na linha 2, coluna 1
        {5, 3, VERTICAL},        // Navio 2: Vertical na linha 5, coluna 3
        {1, 6, DIAGONAL_DESC},   // Navio 3: Diagonal descendente na linha 1, coluna 6
        {7, 8, DIAGONAL_ASC}     // Navio 4: Diagonal ascendente na linha 7, coluna 8
    };
    
    int i;
    int navios_posicionados = 0;
    
    printf("=== INICIALIZANDO JOGO DE BATALHA NAVAL ===\n");
    
    // Inicializa o tabuleiro com água
    inicializar_tabuleiro(tabuleiro);
    printf("Tabuleiro inicializado com sucesso!\n");
    
    // Tenta posicionar cada navio
    printf("\nPosicionando navios no tabuleiro:\n");
    for (i = 0; i < NUM_NAVIOS; i++) {
        printf("Navio %d (%s) na posição (%d, %d): ", 
               i + 1, 
               obter_nome_orientacao(navios[i].orientacao),
               navios[i].linha_inicial, 
               navios[i].coluna_inicial);
        
        // Verifica se é possível posicionar o navio
        if (pode_posicionar_navio(tabuleiro, navios[i])) {
            posicionar_navio(tabuleiro, navios[i]);
            navios_posicionados++;
            printf("SUCESSO!\n");
        } else {
            printf("ERRO - Posição inválida ou ocupada!\n");
        }
    }
    
    // Exibe informações sobre o posicionamento
    printf("\nResumo do posicionamento:\n");
    printf("- Navios posicionados com sucesso: %d/%d\n", navios_posicionados, NUM_NAVIOS);
    printf("- Tamanho de cada navio: %d posições\n", TAMANHO_NAVIO);
    printf("- Tamanho do tabuleiro: %dx%d\n", TAMANHO_TABULEIRO, TAMANHO_TABULEIRO);
    
    // Exibe o tabuleiro final
    exibir_tabuleiro(tabuleiro);
    
    return 0;
}
