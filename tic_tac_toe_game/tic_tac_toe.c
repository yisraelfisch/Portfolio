/*************************************** 
file name: tic_tac_toe.c
Author: yisrael fisch
discription: this a simple tic tac toe
for two players every player insert his 
moves through the keyboard
******************************************/

#include <stdio.h>

int main()
{
    char board[3][3];
    int play = 1;
    int result = 0;
    int cell = 0;
    int turns_count = 0;
    int row = 0;
    int col = 0;
    int clean_stdin = 0;
    
    puts("Insructions:\nThis is a simple tic tac toe play.\nplayer 1 is X player 2 is O.\n");
    puts("enter a cell number to make your move\npress -1 to exit.\n");
    
    while(play == 1)
    {

        /* set game and board */
        result = 0;
        cell = 0;
        turns_count = 0;
        row = 0;
        col = 0;
        clean_stdin = 0;

        char playerSign = ' ';
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                board[i][j] = ' ';
            }
        }

        /* print board to screen */
        printf("\n\n\t  ");
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                printf("%c", board[i][j]);
                if (j < 2)
                {
                    printf("  |  ");
                }
            }
            if (i < 2)
            printf("\n\t----------------\n\t  ");
        }
        printf("\n\n\n");

        /* game in play */
        while (turns_count < 9)
        {
            /* check which player have the current turn */
            if (turns_count % 2 == 0)
            {
                // player 1
                printf("\nPlayer 1 [ X ] your turn. enter cell : ");
                playerSign = 'X';
            }
            else
            {
                // player 2
                printf("\nPlayer 2 [ O ] your turn. enter cell: ");
                playerSign = 'O';
            }
            char buffer;
            scanf("%d", &cell);
            
            /* inserting cell and check for correctness */
            if (cell > 0 && cell < 10)
            {
                row = (cell - 1) / 3;
                col = (cell - 1) % 3;

                if (board[row][col] != ' ')
                {
                    printf("\nInvalid: Cell is already taken!\n");
                    cell = 0;
                    continue;
                }
                else
                {
                    board[row][col] = playerSign;
                }

                /* print board to screen */
                printf("\n\n\t  ");
                for(int i = 0; i < 3; i++)
                {
                    for(int j = 0; j < 3; j++)
                    {
                        printf("%c", board[i][j]);
                        if (j < 2)
                        {
                            printf("  |  ");
                        }
                    }
                    if (i < 2)
                    printf("\n\t----------------\n\t  ");
                }
                printf("\n\n\n");

            /* check for winner */
            if((turns_count > 3)&&
                (board[0][0] == playerSign && board[0][1] == playerSign && board[0][2] == playerSign ||
                board[1][0] == playerSign && board[1][1] == playerSign && board[1][2] == playerSign ||
                board[2][0] == playerSign && board[2][1] == playerSign && board[2][2] == playerSign ||
                board[0][0] == playerSign && board[1][0] == playerSign && board[2][0] == playerSign ||
                board[0][1] == playerSign && board[1][1] == playerSign && board[2][1] == playerSign ||
                board[0][2] == playerSign && board[1][2] == playerSign && board[2][2] == playerSign ||
                board[0][0] == playerSign && board[1][1] == playerSign && board[2][2] == playerSign ||
                board[0][2] == playerSign && board[1][1] == playerSign && board[2][0] == playerSign))
            {
                    printf("\t *** Player %d Won!! ***\n", playerSign == 'X' ? 1 : 2);
                    
                    break;
            }

                turns_count++;
                cell = 0;

            }
            /* exit request */
            else if (cell == -1)
            {
                printf("\n\tGame Terminated\n");
                return 0;
            }
            /* wrong typing */
            else
            {
                printf("\nPlease Enter a valid cell value\n");
                while((clean_stdin = getchar()) != '\n' && clean_stdin != EOF);
                cell = 0;
                continue;
            }
        }
        /* check if no turns left to play */
        if(turns_count == 9)
        {
            puts("It's a tie!\nyou'r both smart players!\n");
        }
        play = 0;
        puts("Press 1 if you want play again want or any number if you want to exit\n");
        scanf("%d", &play);
    }
    puts("Bye bye, thanks for playing with  my app!\n");
    return 0;
}