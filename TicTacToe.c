//This is a Tic-Tac-Toe program written in C

//This is to allow the deprecated functions in Visual Studio.
#define _CRT_SECURE_NO_DEPRECATE  

#include<stdio.h>
#include<stdlib.h>

//ANSI color code escape sequences
#define red   "\033[1;91m"
#define cyan  "\033[36m"
#define blue  "\033[1;34m"
#define purple "\033[1;95m"
#define green "\033[1;92m"
#define reset "\033[0m"


void create_board(char s[9]);
int input(int player, char sign);
void assign(int position, char sign, char* ptr, int player);
int checkwin(char s[9]);
void filesave(char s[9], int player, int i);

int main()
{
    int player = 1, i, position, result = 0;
    char sign;
    char s[9] = { '1','2','3','4','5','6','7','8','9' }, * ptr;
    ptr = s;
    printf(cyan "  TIC-TAC TOE\n\n" reset);
    printf(green "  PLAYER 1: " reset "X\t\t\t"                 green "PLAYER 2: " reset "O\n\n");

    //creates the tic-tac-toe board for input visualization
    create_board(s);


    for (i = 0; i < 9; i++)
    {
        player = i % 2 + 1;

        sign = (player % 2) ? 'X' : 'O';

        //Now for inputting player input
        position = input(player, sign);

        //converting position to index
        assign(position, sign, s, player);

        //updated tic-tac-toe board is outputted
        create_board(s);

        result = checkwin(s);
        if (result == 1)
        {
            printf(green "\nPlayer %d" reset " won. Congrats!\n", player);

            //it saves the game to a file named "Game.txt"
            filesave(s, player, i);
            break;
        }
    }
    if (result == 0)
        printf("It's a draw.");

    return 0;

}

void create_board(char s[9])
{

    //this is to create board that updates every time loop runs
    printf("\n");
    printf(blue "\t _____ _____ _____ \n");
    printf("\t| " red " %c " blue " | " red " %c " blue " | " red " %c " blue " |\n", s[0], s[1], s[2]);
    printf("\t _____ _____ _____ \n");
    printf("\t| " red " %c " blue " | " red " %c " blue " | " red " %c " blue " |\n", s[3], s[4], s[5]);
    printf("\t _____ _____ _____ \n");
    printf("\t| " red " %c " blue " | " red " %c " blue " | " red " %c " blue " |\n", s[6], s[7], s[8]);
    printf("\t _____ _____ _____ \n\n\n" reset);
}

int input(int player, char sign)
{
    //this is to input position of X and O from users
    int position;
    printf(green " \n  Player %d," reset " Input your position of " purple " %c " reset ":", player, sign);
    scanf("%d", &position);
    if (position > 9 || position < 1)
    {
        printf("Invalid. Try again.\n\n");
        exit(1);
    }
    else
        return position;
}

void assign(int position, char sign, char* ptr, int player)
{
    //this is to update the game-board in every loop
    int x = position;
    if (ptr[x - 1] == 'X' || ptr[x - 1] == 'O')
    {
        printf("\n  You have already entered in that position! Choose another position.");
        input(player, sign);
    }
    else
        ptr[x - 1] = sign;
}

int checkwin(char s[9])
{
    //this is to check if any one of the two has won yet

    //first diagonal check
    if (s[0] == s[4] && s[0] == s[8] || s[2] == s[4] && s[2] == s[6])
        return 1;
    //Now horizontal check
    else if (s[0] == s[1] && s[0] == s[2] || s[3] == s[4] && s[3] == s[5] || s[6] == s[7] && s[6] == s[8])
        return 1;
    //Now vertical check
    else if (s[0] == s[3] && s[0] == s[6] || s[1] == s[4] && s[1] == s[7] || s[2] == s[5] && s[2] == s[8])
        return 1;
    else
        return 0;
}

void filesave(char s[9], int player, int i)
{
    //this is to save the game result in a file called "Game.txt"
    FILE* fp;
    fp = fopen("Game.txt", "w");
    if (fp == NULL)
    {
        printf("File doesn't exist");
        exit(1);
    }
    printf("\n");
    fprintf(fp, " _____ _____ _____ \n");
    fprintf(fp, "|  %c  |  %c  |  %c  |\n", s[0], s[1], s[2]);
    fprintf(fp, " _____ _____ _____ \n");
    fprintf(fp, "|  %c  |  %c  |  %c  |\n", s[3], s[4], s[5]);
    fprintf(fp, " _____ _____ _____ \n");
    fprintf(fp, "|  %c  |  %c  |  %c  |\n", s[6], s[7], s[8]);
    fprintf(fp, " _____ _____ _____ \n\n\n");
    fprintf(fp, " Congrats Player %d ! You won in %d steps.\n\n", player, i + 1);
    fprintf(fp, " Game created by the collaboration of : Biplav Poudel, Yogesh Bhandari, Sugam Rimal, Sharad Shres and Sandip Tamang.");
    fclose(fp);
}

