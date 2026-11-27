#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void initializeBoard(char board[3][3]);
void displayBoard(char board[3][3]);
int makeMove(char board[3][3], char player);
int checkWinner(char board[3][3], char player);
int checkDraw(char board[3][3]);
void playGame(char board[3][3], int *scoreX, int *scoreO, int *draws);
int readInteger(void);


int main()
{
    char board[3][3];
    int scoreX = 0, scoreO = 0, draws = 0;
    int choice;

    printf("=================================\n");
    printf("       TIC-TAC-TOE GAME\n");
    printf("=================================\n");

    do
    {
        printf("\n1. Start Game\n");
        printf("2. View Scoreboard\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        choice = readInteger();

        switch (choice)
        {
            case 1:
                playGame(board, &scoreX, &scoreO, &draws);
                break;

            case 2:
                printf("\n========== SCOREBOARD ==========\n");
                printf("Player X Wins : %d\n", scoreX);
                printf("Player O Wins : %d\n", scoreO);
                printf("Draws         : %d\n", draws);
                printf("===============================\n");
                break;

            case 3:
                printf("\nThank you for playing!\n");
                break;

            default:
                printf("Invalid choice! Please select 1, 2 or 3.\n");
        }

    } while (choice != 3);

    return 0;
}

void initializeBoard(char board[3][3])
{
    char position = '1';

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = position;
            position++;
        }
    }
}


void displayBoard(char board[3][3])
{
    printf("\n");

    for (int i = 0; i < 3; i++)
    {
        printf(" %c | %c | %c \n",
               board[i][0], board[i][1], board[i][2]);

        if (i < 2)
        {
            printf("---|---|---\n");
        }
    }

    printf("\n");
}


int readInteger(void)
{
    char input[100];
    char *end;
    long number;

    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        return -1;
    }

    number = strtol(input, &end, 10);

   
    if (end == input)
    {
        return -1;
    }

  
    while (*end != '\0' && isspace((unsigned char)*end))
    {
        end++;
    }

    if (*end != '\0')
    {
        return -1;
    }

    return (int)number;
}


int makeMove(char board[3][3], char player)
{
    int position;
    int row, column;

    while (1)
    {
        printf("Player %c, enter position (1-9): ", player);

        position = readInteger();

        if (position < 1 || position > 9)
        {
            printf("Invalid position! Enter a number from 1 to 9.\n");
            continue;
        }

        
        row = (position - 1) / 3;
        column = (position - 1) % 3;

        
        if (board[row][column] == 'X' ||
            board[row][column] == 'O')
        {
            printf("Position already occupied! Try again.\n");
            continue;
        }

        board[row][column] = player;
        return 1;
    }
}

int checkWinner(char board[3][3], char player)
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == player &&
            board[i][1] == player &&
            board[i][2] == player)
        {
            return 1;
        }
    }

    for (int j = 0; j < 3; j++)
    {
        if (board[0][j] == player &&
            board[1][j] == player &&
            board[2][j] == player)
        {
            return 1;
        }
    }

    if (board[0][0] == player &&
        board[1][1] == player &&
        board[2][2] == player)
    {
        return 1;
    }

    if (board[0][2] == player &&
        board[1][1] == player &&
        board[2][0] == player)
    {
        return 1;
    }

    return 0;
}

int checkDraw(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != 'X' &&
                board[i][j] != 'O')
            {
                return 0;
            }
        }
    }

    return 1;
}

void playGame(char board[3][3],
              int *scoreX,
              int *scoreO,
              int *draws)
{
    char player = 'X';
    int result;
    int playAgain;

    do
    {
        initializeBoard(board);

        player = 'X';
        result = 0;

        printf("\nStarting New Game!\n");

        while (result == 0)
        {
            displayBoard(board);

            makeMove(board, player);

            if (checkWinner(board, player))
            {
                displayBoard(board);

                printf("Congratulations! Player %c wins!\n", player);

                if (player == 'X')
                {
                    (*scoreX)++;
                }
                else
                {
                    (*scoreO)++;
                }

                result = 1;
            }

            else if (checkDraw(board))
            {
                displayBoard(board);

                printf("The game is a DRAW!\n");

                (*draws)++;
                result = 1;
            }

         
            else
            {
                if (player == 'X')
                {
                    player = 'O';
                }
                else
                {
                    player = 'X';
                }
            }
        }

        printf("\n========== SCOREBOARD ==========\n");
        printf("Player X Wins : %d\n", *scoreX);
        printf("Player O Wins : %d\n", *scoreO);
        printf("Draws         : %d\n", *draws);
        printf("===============================\n");

        printf("\nPlay again?\n");
        printf("1. Yes\n");
        printf("2. No\n");
        printf("Enter choice: ");

        playAgain = readInteger();

        while (playAgain != 1 && playAgain != 2)
        {
            printf("Invalid choice! Enter 1 or 2: ");
            playAgain = readInteger();
        }

    } while (playAgain == 1);
}
