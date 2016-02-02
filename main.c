#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define CORVETTE_ID 1
#define CORVETTE_WIDTH 1
#define CORVETTE_NB 1

#define DESTROYER_ID 2
#define DESTROYER_WIDTH 3
#define DESTROYER_NB 2

#define CROISEUR_ID 3
#define CROISEUR_WIDTH 4
#define CROISEUR_NB 2

#define PORTE_AVION_ID 4
#define PORTE_AVION_WIDTH 6
#define PORTE_AVION_NB 1

#define lignesmax 200
#define colonnesmax 200

int doRand(int startVal, int endVal){
    /*srand(time(0));
    return (rand() % (endVal - startVal) + startVal);*/
    int n = rand() % (endVal - startVal) + startVal;
    return (n);
}

int mathInputInt(){
    int userChoise = 1;
    char userNumber[20];

    while(userChoise){
        scanf ("%s", userNumber);

            userChoise = atoi(userNumber);
            if(userChoise != 0){
                return userChoise;
            }else if(*userNumber=='0'){
                return 0;
            }else{
                userChoise = 1;
                printf ("Please use just numbers  ");
            }
    }
    return 0;
}

int testPlayerAlive(int linesNumber, int columnsNumber, int totalPlayers, int map[lignesmax][colonnesmax][10], int playerNumber)
{
    int i, j;
    int flag = 1;
    for(i=0;i<linesNumber;i++){
        for(j=0;j<columnsNumber;j++){
            if(map[i][j][playerNumber] == CORVETTE_ID || map[i][j][playerNumber] == CROISEUR_ID
               || map[i][j][playerNumber] == DESTROYER_ID || map[i][j][playerNumber] == PORTE_AVION_ID){
                flag = 0;
               }
        }
    }
    if(flag == 0){
        return 1; //player alive
    }else{
        return 0; //player dead
    }
}

int numberPlayerLeft(int linesNumber, int columnsNumber, int totalPlayers, int map[lignesmax][colonnesmax][10])
{
    int i;
    int nb = 0;
    for(i=1;i<=totalPlayers;i++){
        if(testPlayerAlive(linesNumber,columnsNumber,totalPlayers,map,i) == 1){
            nb = nb +1;
        }
    }
    return nb;
}

void printMap(int linesNumber, int columnsNumber, int totalPlayers, int map[lignesmax][colonnesmax][10], int playerNumber)
{
    //printf("Legend of the map : 1/2/3/4 : ship of given type -- 0 : nothing -- X : where you already shot -- H : another player's ship you hit -- S : one of your sunken ships\n");
    int i = 0, j = 0;
    for(i=0;i<linesNumber+2;i++){
        if(i == 0 || i == linesNumber + 1){
            for(j=0;j<columnsNumber+2;j++){
                printf("#");
            }
            //printf("\n");
        }else{
            for(j=0;j<columnsNumber+2;j++){
                if(j == 0 || j == columnsNumber + 1){
                    printf("#");
                }else if(map[j-1][i-1][playerNumber] == -1){
                    printf("X");
                }else if(map[j-1][i-1][playerNumber] == -2){
                    printf("H");
                }else if(map[j-1][i-1][playerNumber] == -3){
                    printf("S");
                }else{
                    printf("%d", map[j-1][i-1][playerNumber]);
                }
            }
        //printf("\n");
        }
        if(i==0){
            printf("     Legend of the map :");
        }else if(i==2){
            printf("     1/2/3/4 : ship of given type");
        }else if(i==3){
            printf("     0 : nothing");
        }else if(i==4){
            printf("     X : where you already shot");
        }else if(i==5){
            printf("     H : another player's ship you hit");
        }else if(i==6){
            printf("     S : one of your sunken ships");
        }
        printf("\n");


    }
}

void checkShotAi(int absShot, int ordShot, int linesNumber, int columnsNumber,int totalHumans, int totalAi, int map[lignesmax][colonnesmax][10], int playerNumber, char playerNames[10][15])
{
    int i = 0;
    int flagShot = 1;
    for(i=1;i<=totalAi+totalHumans;i++){
        if(i!=playerNumber){
            if(map[absShot][ordShot][i] != 0 && map[absShot][ordShot][i] != -1 && map[absShot][ordShot][i] != -2 && map[absShot][ordShot][i] != -3){
                map[absShot][ordShot][playerNumber] = -2;
                if(i<=totalHumans){
                    printf("hit the ship type number %d of %s. Congratulations to him!\n",map[absShot][ordShot][i],playerNames[i]);
                }else{
                    printf("hit the ship type number %d of bot number %d. Congratulations to him!\n",map[absShot][ordShot][i],i-totalHumans);
                }
                //printf("hit the ship type number %d of player %d. Congratulations to him!\n",map[absShot][ordShot][i],i);
                map[absShot][ordShot][i] = -3;
                flagShot = 0;
            }else{
                map[absShot][ordShot][playerNumber] = -1;
            }
        }
    }
    if(flagShot == 1){
        printf("hit nothing.\n");
    }
}

int checkShotHuman(int absShot, int ordShot, int linesNumber, int columnsNumber,int totalHumans, int totalAi, int map[lignesmax][colonnesmax][10], int playerNumber, char playerNames[10][15])
{
    int i = 0;
    int flagShot = 1;
    for(i=1;i<=totalHumans+totalAi;i++){
        if(i!=playerNumber){
            if(map[absShot][ordShot][i] != 0 && map[absShot][ordShot][i] != -1 && map[absShot][ordShot][i] != -2 && map[absShot][ordShot][i] != -3){
                map[absShot][ordShot][playerNumber] = -2;
                if(i<=totalHumans){
                    printf("You hit the boat type number %d of %s. Congratulations!\n",map[absShot][ordShot][i],playerNames[i-1]);
                }else{
                    printf("You hit the boat type number %d of bot number %d. Congratulations!\n",map[absShot][ordShot][i],i-totalHumans);
                }
                map[absShot][ordShot][i] = -3;
                flagShot = 0;
            }else{
                map[absShot][ordShot][playerNumber] = -1;
            }
        }
    }
    if(flagShot == 1){
        printf("\nYou hit nothing.\n");
    }
    return 0;
}

int testShot(int absShot, int ordShot, int playerNumber, int map[lignesmax][colonnesmax][10])
{
    if(map[absShot][ordShot][playerNumber] == 0 ){ //nothing there
        return 0;
    }else if(map[absShot][ordShot][playerNumber] == -1 || map[absShot][ordShot][playerNumber] == -2){ //already shot there
        return -1;
    }else if(map[absShot][ordShot][playerNumber] == CORVETTE_ID || map[absShot][ordShot][playerNumber] == CROISEUR_ID
             || map[absShot][ordShot][playerNumber] == DESTROYER_ID || map[absShot][ordShot][playerNumber] == PORTE_AVION_ID || map[absShot][ordShot][playerNumber] == -3){ //one of your boats here
        return 1;
    }
}

/*int doShot(int absShot, int ordShot, int playerNumber, int map[lignesmax][colonnesmax][10])
{
    if(testShot(absShot, ordShot, playerNumber, map) == 0){
        map[absShot][ordShot][playerNumber] == -1;
        return 0;
    } else if(testShot(absShot, ordShot, playerNumber, map) == 1){
        return 1;
    }else if(testShot(absShot, ordShot, playerNumber, map) == -1){
        return -1;
    }
}*/

int aiTurn(int linesNumber, int columnsNumber, int totalHumans, int totalAi, int map[lignesmax][colonnesmax][10], int playerNumber, char playerNames[10][15])
{
    int ordShot, absShot;
    int flag = 1;

    while(flag){
        absShot = doRand(0,columnsNumber);
        ordShot = doRand(0,linesNumber);
        if(testShot(absShot,ordShot,playerNumber,map) == 0){
            flag = 0;
        }
    }
    flag = 1;
    printf("Bot number %d shot at [%d,%d] and ",playerNumber-totalHumans,absShot,ordShot);
    checkShotAi(absShot,ordShot,linesNumber,columnsNumber,totalHumans,totalAi,map,playerNumber,playerNames);
    return 0;
}

int humanTurn(int linesNumber, int columnsNumber, int totalHumans, int totalAi, int map[lignesmax][colonnesmax][10], int playerNumber, char playerNames[10][15])
{
    int ordShot, absShot;
    int flag = 1;
    while(flag){
        printf("\n\n >> %s's turn.<<\n", playerNames[playerNumber-1]);
        printMap(linesNumber,columnsNumber,totalAi+totalHumans,map,playerNumber);
        printf("\n\n");
        printf("Where do you want to shoot ?\n");
        printf("X axis: ");
        scanf("%d",&absShot);
        printf("Y axis: ");
        scanf("%d",&ordShot);
        if(testShot(absShot,ordShot,playerNumber,map) == 0){
            flag = 0;
        }else if(testShot(absShot,ordShot,playerNumber,map) == 1){
            printf("One of your ships is there. Start again.");
        }else if(testShot(absShot,ordShot,playerNumber,map) == -1){
            printf("You already shot here once. Start again.");
        }
    }
    flag = 1;
    checkShotHuman(absShot,ordShot,linesNumber,columnsNumber,totalHumans,totalAi,map,playerNumber,playerNames);
    return 0;
}

int beginGame(int linesNumber, int columnsNumber, int totalHumans, int totalAi, int map[lignesmax][colonnesmax][10], int humanLeftTable[10], int aiLeftTable[10], char playerNames[10][15])
{
    int i = 0, j = 0;
    int nb = 0;
    /*for(i=1;i<=totalHumans;i++){ //calculus of alive human players
        if(humanLeftTable[i-1] == 1){
            humansLeft++;
        }
    }
    for(i=1;i<=totalHumans;i++){  // calculus of alive bot players
        if(humanLeftTable[i-1] == 1){
            aisLeft++;
        }
    }*/
    nb = numberPlayerLeft(linesNumber,columnsNumber,totalAi+totalHumans,map);
    //printf("%d joueurs vivants", nb);
    while(nb>=2){
        for(i=1;i<=totalHumans;i++){
            if(testPlayerAlive(linesNumber,columnsNumber,totalHumans+totalAi,map,i) == 0 && humanLeftTable[i-1] == 1){
                printf("--- Player %s is now dead! RIP ---",playerNames[i-1]);
                humanLeftTable[i-1] = 0;
            }
            if(humanLeftTable[i-1] == 1){
                humanTurn(linesNumber,columnsNumber,totalHumans,totalAi,map,i,playerNames);
            }
        }
        for(i=1;i<=totalAi;i++){
            if(testPlayerAlive(linesNumber,columnsNumber,totalAi+totalHumans,map,i+totalHumans) == 0 && aiLeftTable[i-1] == 1){
                printf("--- Bot number %d is now dead! RIP ---\n", i);
                aiLeftTable[i-1] = 0;
            }
            if(aiLeftTable[i-1] == 1){
                aiTurn(linesNumber,columnsNumber,totalHumans,totalAi,map,i+totalHumans,playerNames);
            }
        }
        nb = numberPlayerLeft(linesNumber,columnsNumber,totalAi+totalHumans,map);
    }
    if(nb == 1){
        for(j==1;j<=totalAi+totalHumans;j++){
            //int a = testPlayerAlive(linesNumber,columnsNumber,totalAi+totalHumans,map,j);
            //printf("lala %d", a);
            if(testPlayerAlive(linesNumber,columnsNumber,totalAi+totalHumans,map,j)){
                //printf("lala");
                if(j < totalHumans){
                    printf("\n>>> Congratulations to %s for winning! <<<\n",j,playerNames[j-1]);
                }else{
                    printf("\n>>> Congratulations to bot number %d for winning <<<\n",j-totalHumans);
                }

            }
        }
    }
    return 0;
}

void setShip(int x, int y, int dir, int width, int id, int linesNumber, int columnsNumber, int totalPlayers, int playerNumber, int map[lignesmax][colonnesmax][10])
{
    int i = 0;

    //printf("setNavire joueur=%d x=%d y=%d size=%d id=%d dir=%d \n",playerNumber,x,y,width,id,dir);

    if(dir == 0){
        for(i= 0;i<width;i++){
            map[x][y+i][playerNumber] = id;
        }
    }else if(dir == 1){
        for(i=0;i<width;i++){
            map[x+i][y][playerNumber] = id;
        }
    }else if(dir == 2){
        for(i=0;i<width;i++){
            map[x][y-i][playerNumber] = id;
        }
    }else if(dir == 3){
        for(i=0;i<width;i++){
            map[x-i][y][playerNumber] = id;
        }
    }
}

int testCase(int x, int y, int dir, int width, int linesNumber, int columnsNumber, int totalPlayers, int playerNumber, int map[lignesmax][colonnesmax][10])
{
    int i = 0;
    int j = 0;
    int flagOk = 1;

    /*for(i = 0; i < totalPlayers; i++){ //test if case occupied by any player's boat
       if(map[x][y][i] !=0){
        flagOk = 0;
       }
    }*/

    if(dir == 0){ //towards bottom
        if(y + width - 1 <  linesNumber){ // boat doesnt go out of the board towards bottom
            for(i=0;i<width;i++){ // For each case towards bottom
                for(j=1;j<=playerNumber+1;j++){ // and for each player
                    if(map[x][y+i][j] != 0){ // case doesnt contain anything
                        flagOk = 0;
                    }
                }

            }
        }else{
        return -1;
        }
    }else if(dir == 1){ //towards right
        if(x + width - 1 <  columnsNumber){ // boat doesnt go out of the board towards right
            for(i=0;i<width;i++){ // For each case towards bottom
                for(j=1;j<=playerNumber;j++){ // and for each player
                    if(map[x+i][y][j] != 0){ // case doesnt contain anything
                        flagOk = 0;
                    }
                }

            }
        }else{
        return -1;
        }
    }else if(dir == 2){ //towards top
        if(y - width - 1 >  linesNumber){ // boat doesnt go out of the board towards top
            for(i=0;i<width;i++){ // For each case towards right
                for(j=1;j<=playerNumber;j++){ // and for each player
                    if(map[x][y-i][j] != 0){ // case doesnt contain anything
                        flagOk = 0;
                    }
                }

            }
        }else{
        flagOk = 0;
        }
    }else if(dir == 3){ //towards left
        if(x - width - 1 >  columnsNumber){ // boat doesnt go out of the board towards bottom
            for(i=0;i<width;i++){ // For each case towards left
                for(j=1;j<=playerNumber;j++){ // and for each player
                    if(map[x-i][y][j] != 0){ // case doesnt contain anything
                        flagOk = 0;
                    }
                }

            }
        }else{
        return -1;
        }
    }else{
        return -1;
    }

    if(flagOk == 0){// if any case occupied towards given direction
        return -1;
    }else{
        return 0;
    }
}

void setPorteAvion(int nbPorteAvion, int linesNumber, int columnsNumber, int totalPlayers, int map[lignesmax][colonnesmax][10], int playerNumber)
{
    int i = 0;
    int x = -1;
    int y = -1;
    int d = -1;
    int flag = 1;
    for(i=0;i<nbPorteAvion;i++){
        while(flag){
            y = doRand(0,linesNumber);
            x = doRand(0,columnsNumber);
            d = doRand(0,4);
            if(testCase(x,y,d,PORTE_AVION_WIDTH,linesNumber,columnsNumber,totalPlayers,playerNumber,map) == 0){
                setShip(x,y,d,PORTE_AVION_WIDTH,PORTE_AVION_ID,linesNumber,columnsNumber,totalPlayers,playerNumber,map);
                flag = 0;
            }
        }
        flag = 1;
    }
}

void setDestroyer(int nbDestroyer, int linesNumber, int columnsNumber, int totalPlayers, int map[lignesmax][colonnesmax][10], int playerNumber)
{
    int i = 0;
    int x = -1;
    int y = -1;
    int d = -1;
    int flag = 1;
    for(i=0;i<nbDestroyer;i++){
        while(flag){
            y = doRand(0,linesNumber);
            x = doRand(0,columnsNumber);
            d = doRand(0,4);
            if(testCase(x,y,d,DESTROYER_WIDTH,linesNumber,columnsNumber,totalPlayers,playerNumber,map) == 0){
                setShip(x,y,d,DESTROYER_WIDTH,DESTROYER_ID,linesNumber,columnsNumber,totalPlayers,playerNumber,map);
                flag = 0;
            }
        }
        flag = 1;
    }
}

void setCroiseur(int nbCroiseur, int linesNumber, int columnsNumber, int totalPlayers, int map[lignesmax][colonnesmax][10], int playerNumber)
{
    int i = 0;
    int x = -1;
    int y = -1;
    int d = -1;
    int flag = 1;
    for(i=0;i<nbCroiseur;i++){
        while(flag){
            y = doRand(0,linesNumber);
            x = doRand(0,columnsNumber);
            d = doRand(0,4);
            if(testCase(x,y,d,CROISEUR_WIDTH,linesNumber,columnsNumber,totalPlayers,playerNumber,map) == 0){
                setShip(x,y,d,CROISEUR_WIDTH,CROISEUR_ID,linesNumber,columnsNumber,totalPlayers,playerNumber,map);
                flag = 0;
            }
        }
        flag = 1;
    }
}


void setCorvette(int nbCorvette, int linesNumber, int columnsNumber, int totalPlayers, int map[lignesmax][colonnesmax][10], int playerNumber)
{
    int i = 0, x = -1, y = -1, d = -1;
    int flag = 1;
    for(i=0;i<nbCorvette;i++){
        while(flag){
            y = doRand(0,linesNumber);
            x = doRand(0,columnsNumber);
            d = doRand(0,4);
            if(testCase(x,y,d,CORVETTE_WIDTH,linesNumber,columnsNumber,totalPlayers,playerNumber,map) == 0){
                setShip(x,y,d,CORVETTE_WIDTH,CORVETTE_ID,linesNumber,columnsNumber,totalPlayers,playerNumber,map);
                flag = 0;
            }
        }
        flag = 1;
    }
}

void setShips(int linesNumber, int columnsNumber, int totalPlayers, int map[lignesmax][colonnesmax][10])
{
    int k = 1;
    for(k=1;k<=totalPlayers;k++){ // i = numéro de joueur
        setCorvette(CORVETTE_NB,linesNumber,columnsNumber,totalPlayers,map,k);
        setDestroyer(DESTROYER_NB,linesNumber,columnsNumber,totalPlayers,map,k);
        setCroiseur(CROISEUR_NB,linesNumber,columnsNumber,totalPlayers,map,k);
        setPorteAvion(PORTE_AVION_NB,linesNumber,columnsNumber,totalPlayers,map,k);
    }
}

/*void generateMap(int linesNumber, int columnsNumber, int totalPlayers, int map[lignesmax][colonnesmax][10])
{
    setShips(linesNumber, columnsNumber, totalPlayers, map);

}*/

void purgeMap(int map[200][200][10])
{
    int i = 0;
    int j = 0;
    int k = 0;
    for(i=0;i<200;i++){
        for(j=0;j<200;j++){
            for(k=0;k<10;k++){
            map[i][j][k] = 0;
            }
        }
    }
}

void printBeginningMenu()
{
    int i = 0;
    int totalHumans = 0, totalAi = 0, linesNumber = 0, columnsNumber = 0;
    int inputFirstMenu = 0;
    int map[lignesmax][colonnesmax][10];
    int humanLeftTable[10] = {0};
    int aiLeftTable[10] = {0};
    int flag = 1;
    char playerNames[10][15];

    purgeMap(map);

    system("cls");
    printf("###################################################\n");
    printf("#####                                         #####\n");
    printf("#####        Welcome to BATTLESHIP 1.0        #####\n");
    printf("#####                                         #####\n");
    printf("#####                    Press Enter to start #####\n");
    printf("###################################################\n");
    printf("\n");
    while (inputFirstMenu != '\r' && inputFirstMenu != '\n') { inputFirstMenu = getchar(); }

    while(flag){
        printf("\nChoose the number of non-ai players (0 - 10): ");
        totalHumans = mathInputInt();
        if(totalHumans >=0 && totalHumans <=10){
            flag = 0;
        }
    }
    flag = 1;

    for(i=0;i<totalHumans;i++){ // asks players' names
        printf("Name of player number %d: ", i+1);
        scanf("%s",playerNames[i]);
    }

    while(flag){
        printf("\nChoose the number of ai players (0 - %d): ",10-totalHumans);
        totalAi = mathInputInt();
        if(totalAi >=0 && totalAi <= 10 - totalHumans){
            flag = 0;
        }
    }
    flag = 1;

    while(flag){
        printf("\nChoose the number of lines on the map (1 - 200): ");
        linesNumber = mathInputInt();
        if(linesNumber >= 1 && linesNumber <= 200){
            flag = 0;
        }
    }
    flag = 1;

    while(flag){
        printf("\nChoose the number of columns on the map (1 - 200): ");
        columnsNumber = mathInputInt();
        if(columnsNumber >= 1 && columnsNumber <= 200){
            flag = 0;
        }
    }

    for(i=0;i<totalHumans;i++){
        humanLeftTable[i] = 1;
    }
    for(i=0;i<totalAi;i++){
        aiLeftTable[i] = 1;
    }
    int totalPlayers = totalHumans + totalAi;
    setShips(linesNumber,columnsNumber,totalPlayers,map);
    printf("\n\n");
    /*printMap(linesNumber, columnsNumber, totalPlayers, map, 1);
    printf("\n\n");
    printMap(linesNumber, columnsNumber, totalPlayers, map, 2);
    printMap(linesNumber, columnsNumber, totalPlayers, map, 0);*/
    //flag = 0;

    beginGame(linesNumber,columnsNumber,totalHumans,totalAi,map,humanLeftTable,aiLeftTable,playerNames);
}

int main()
{
    printBeginningMenu();
    return 0;
}
