#include <stdio.h>
#include <stdbool.h>

// Função para imprimir o tabuleiro do jogo da velha
void print_board(char board[3][3]) {
    printf("\n  0 1 2\n");
    for (int i = 0; i < 3; ++i) {
        printf("%d ", i);
        for (int j = 0; j < 3; ++j) {
            printf("%c", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("  -----\n");
    }
    printf("\n");
}

// Função para verificar se há um vencedor
bool check_winner(char board[3][3]) {
    // Verifica as linhas
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return true;
    }
    // Verifica as colunas
    for (int j = 0; j < 3; ++j) {
        if (board[0][j] != ' ' && board[0][j] == board[1][j] && board[1][j] == board[2][j])
            return true;
    }
    // Verifica as diagonais
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return true;
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return true;

    return false;
}

// Função principal
int main() {
    char board[3][3]; // O tabuleiro do jogo
    char players[2] = {'X', 'O'}; // Jogadores
    bool game_over = false;
    char play_again;

    while (true) {
        // Inicializa o tabuleiro
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                board[i][j] = ' ';
            }
        }

        int player = 0; // Índice do jogador atual

        while (!game_over) {
            print_board(board);

            // Jogada do jogador
            int row, col;
            printf("Jogador %c, insira a linha e coluna (exemplo: 1 2): ", players[player]);
            scanf("%d %d", &row, &col);

            // Verifica se a jogada é válida
            if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
                printf("Jogada inválida! Tente novamente.\n");
                continue;
            }

            // Realiza a jogada
            board[row][col] = players[player];

            // Verifica se há um vencedor ou empate
            if (check_winner(board)) {
                printf("Parabéns! Jogador %c venceu!\n", players[player]);
                game_over = true;
            } else {
                // Verifica se ocorreu um empate
                bool is_full = true;
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        if (board[i][j] == ' ') {
                            is_full = false;
                            break;
                        }
                    }
                }
                if (is_full) {
                    printf("Empate!\n");
                    game_over = true;
                }
            }

            // Alterna para o próximo jogador
            player = (player + 1) % 2;
        }

        print_board(board);

        // Pergunta se deseja jogar novamente
        printf("Deseja jogar novamente? (S/N): ");
        scanf(" %c", &play_again);

        if (play_again != 'S' && play_again != 's') {
            break;
        } else {
            game_over = false;
        }
    }

    return 0;
}
