#include <stdio.h>
#include <stdbool.h>

#define player_x 'C'
#define player_y 'P'
#define empty ' '
#define size 9

char initial_state[size] = {empty, empty, empty, empty, empty, empty, empty, empty, empty};

void printstate(char state[size]){
    printf("|---+---+---|\n");
    printf("| %c | %c | %c |\n", state[0], state[1], state[2]);
    printf("|---+---+---|\n");
    printf("| %c | %c | %c |\n", state[3], state[4], state[5]);
    printf("|---+---+---|\n");
    printf("| %c | %c | %c |\n", state[6], state[7], state[8]);
    printf("|---+---+---|\n");
}

bool winner(char state[size], char player){
    for(int i=0; i<size; i+=3){
        if(state[i] == player && state[i+1] == player && state[i+2] == player)
            return true;
    }
    for(int i=0; i<3; i++){
        if(state[i] == player && state[i+3] == player && state[i+6] == player)
            return true;
    }
    if(state[0] == player && state[4] == player && state[8] == player)
        return true;
    if(state[2] == player && state[4] == player && state[6] == player)
        return true;
    return false;
}

bool terminal(char state[size]){
    if(winner(state, player_x) || winner(state, player_y))
        return true;
    for(int i=0; i<size; i++){
        if(state[i] == empty)
            return false;
    }
    return true;
}

int utility(char state[size]){
    if(winner(state, player_x))
        return 1;
    if(winner(state, player_y))
        return -1;
    return 0;
}

int minvalue(char state[size]);

int maxvalue(char state[size]){
    if(terminal(state))
        return utility(state);
    int v = -100;
    for(int i=0; i<size; i++){
        if(state[i] == empty){
            char result[size];
            for(int j=0; j<size; j++){
                if(i != j)
                    result[j] = state[j];
                else
                    result[j] = player_x;
            }
            int minVal = minvalue(result);
            if(minVal > v)
                v = minVal;
        }
    }
    return v;
}

int minvalue(char state[size]){
    if(terminal(state))
        return utility(state);
    int v = 100;
    for(int i=0; i<size; i++){
        if(state[i] == empty){
            char result[size];
            for(int j=0; j<size; j++){
                if(i != j)
                    result[j] = state[j];
                else
                    result[j] = player_y;
            }
            int maxVal = maxvalue(result);
            if(maxVal < v)
                v = maxVal;
        }
    }
    return v;
}

int main(void){
    printf("Welcome! This is a TicTacToe game, where your symbol is P, and the computer symbols is C\n");
    int playerChoice;
    printf("Do you want to go first or second?\n");
    printf("Enter 1 for first or 2 for second: ");
    scanf("%d", &playerChoice);
    
    bool playerFirst = (playerChoice == 1);
    
    while(!terminal(initial_state)){
        system("clear");
        printstate(initial_state);
        if (playerFirst) {
            int opt;
            printf("Choose your option (0-8): ");
            scanf("%d", &opt);
            if(initial_state[opt] != empty){
                printf("Invalid move. Try again.\n");
                continue;
            }
            initial_state[opt] = player_y;
        }
        else {
            int bestMove = -1;
            int bestValue = -100;
            for(int i=0; i<size; i++){
                if(initial_state[i] == empty){
                    char result[size];
                    for(int j=0; j<size; j++){
                        if(i != j)
                            result[j] = initial_state[j];
                        else
                            result[j] = player_x;
                    }
                    int minVal = minvalue(result);
                    if(minVal > bestValue){
                        bestValue = minVal;
                        bestMove = i;
                    }
                }
            }

            if(bestMove != -1)
                initial_state[bestMove] = player_x;
        }
        
        playerFirst = !playerFirst;
    }

    printstate(initial_state);

    if(winner(initial_state, player_x))
        printf("You lost!\n");
    else if(winner(initial_state, player_y))
        printf("You won!\n");
    else
        printf("It's a draw!\n");
    return 0;
}
