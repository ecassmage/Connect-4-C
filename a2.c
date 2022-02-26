/* ===========================================================================
COMP-1410 Assignment 2
==============================================================================
Student name: Evan Morrison

Replace the error with statement citing any sources of outside help:
None

=========================================================================== */
/* Had some Broken print statements so had to redo it */


#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


// make_move(board, column, player) updates the board following a move
//   by the given player in the given column; returns false if the move
//   was illegal because the column was full
// requires: 0 <= column < 7
//           player is either 'X' or 'O'
bool make_move(char board[6][7], int column, char player);

// check_win(board) returns true if the given player has 4 connected
//   pieces on the board
bool check_win(char board[6][7], char player);

// first_capital(str, n) returns the first capital letter in str;
//   returns 0 if str contains no capital letters
// requires: str is a string of length n
//           str contains only lower-case and upper-case letters
//           all lower-case letters appear before upper-case letters
/* feature is just for visual purposes so it doesn't really do anything other then disable printf(); from running */
char first_capital(const char str[], int n, int feature); // feature turns off a printing feature. It doesn't do anything apart from that

//char isChar(char x, char y);
//void timeForDumb();  // Time for good old stupid random generating asserts
// deepest_substring(str, out) updates out to be the deepest substring of
//   str; the first is used if multiple possibilities exist
// requires:
//   str is a string with balanced parenthesis
//   out points to enough memory to store the deepest substring of str
void deepest_substring(const char str[], char out[]);

// My Stuff
void printS(char str[], int n);
char isCharUpper(char x, char y);
int randRange(int x, int y);
void timeForDumb();
void first_capitalAsserts();
void check_winAsserts();
void deepest_substringAssert();
bool assertStrings(const char arr[], const char arrCompare[]);
void makeBoard(char board[6][7]);
void show(char brd[6][7]);
bool placePiece(char board[6][7], int row, int column, char player);
int checkDiagonals(char brd[6][7], char piece, int position[2], int direction[2], int move);
bool checkWinConditions(char brd[6][7], char matchPiece, int *ai, int aiArr[2]);
void newBoard(char referenceBoard[6][7], char copyBoard[6][7]);
int findRow(char brd[6][7], char piece, int column);
int AIBrains(char brd[6][7], char player, char opponent, int opponentCheck);
void leAIMakeAMove(char board[6][7], char player, char opponent, char message[]);
bool leMakeAMove(char board[6][7], char player, char message[]);
void secretRules(int *player1, int *player2, int *infinity);
bool doesGameStillHaveSpace(char brd[6][7]);
void gameMaster();


int main(void) {
    // For the O(logn) I assume you wanted log2(n) so I added a little bit extra print text to show that my algorithm
    // is O(logn) If my program goes under logn, it's not actually better but just that it can catch the answer
    // 1 iteration early sometimes as I catch it sometimes before the two pointers meet fully or 1 iteration early,
    // The algorithm though is still O(logn).
    srand(time(NULL));
    first_capitalAsserts();
    printf("All first_capital Asserts have completed.\n");
    check_winAsserts();  // Asserting check_win
    printf("All check_win Asserts have completed.\n");
    deepest_substringAssert();  // Asserting deepest_substring
    printf("All deepest_substring Asserts have completed.\n");
    printf("All Asserts were Successful");
    gameMaster();
}


void first_capitalAsserts(){
    timeForDumb();  // Asserting first_capital
    assert(first_capital("abcfajfsldfjsdlfsjldfsldfslkdfjABC", 34, 0) == 'A');
    assert(first_capital("abcABC", 6, 0) == 'A');
    assert(first_capital("abdfsdfsssdcHABC", 16, 0) == 'H');
    assert(first_capital("A", 1, 0) == 'A');
    assert(first_capital("FJSFASFDLKASDFJASLDKFASLDFJLASDFA", 33, 0) == 'F');
    assert(first_capital("a", 2, 0) == '0');
    assert(first_capital("afsdfgsdgfsdfges", 16, 0) == '0');
    assert(first_capital("agsfgsfgsdfg", 12, 0) == '0');
    assert(first_capital("sfgsdfgsdfgsdfgsdfgsdfgsdfgsd", 29, 0) == '0');
}


void check_winAsserts(){
    /* If you need anymore assertions just continue running the ai, it will infinitely create games and play them just
     * look at the victor to see who won.
     * I would hide these away in a json file or a txt file and then pull them in out of site to clean up the program
     * but I am not allowed more then a .txt and a .c so this isn't feasible
     */
    char test1[6][7] = {
            ".......",
            ".......",
            "...X..",
            "..XO..O",
            ".XOO..O",
            "XOOO..O"
    };
    char test2[6][7] = {
            ".......",
            ".......",
            "X......",
            "X.....O",
            "X.....O",
            "X.....O"
    };
    char test3[6][7] = {
            {"......."},
            {"......O"},
            {".X....O"},
            {"OX....X"},
            {"XO...XO"},
            {"XOOOOXX"}
    };
    char test4[6][7] = {
            {"...X..."},
            {"X.XXX.."},
            {"OXOOO.."},
            {"XOOXX.."},
            {"XOXOOO."},
            {"XOXXOO."}
    };
    char test5[6][7] = {
            ".......",
            ".......",
            ".XX....",
            "XOXX..O",
            "XOOXX.O",
            "OOXOOXO"
    };
    char test6[6][7] = {
            ".......",
            ".......",
            ".......",
            ".......",
            "OOOO...",
            "XXXOX.."
    };
    char test7[6][7] = {
            ".......",
            ".......",
            ".......",
            ".......",
            "OOO....",
            "XXXX..."
    };
    char test8[6][7] = {
            ".......",
            "......X",
            "OXO...X",
            "XOXX..O",
            "XOOXX.O",
            "OOXOOXO"
    };
    char test9[6][7] = {
            "OXOXOOO",
            "XOXOOXX",
            "OXOXXOX",
            "OXOXOXO",
            "OXOOOXO",
            "XOXXOXO"
    };
    char test10[6][7] = {
            "XOXOXOX",
            "XOXOXOX",
            "XOXOXOX",
            "OXOXOXO",
            "OXOXOXO",
            "OXOXOXO"
    };

    assert(check_win(test1, 'X') == 1);  // X Wins
    assert(check_win(test1, 'O') == 0);  // O Loses
    printf("The Assert Agrees that X wins and O Loses\n");
    show(test1);

    assert(check_win(test2, 'X') == 1);  // X Wins
    assert(check_win(test2, 'O') == 0);  // O Loses
    printf("The Assert Agrees that X wins and O Loses\n");
    show(test2);

    assert(check_win(test3, 'O') == 1);  // O Wins
    assert(check_win(test3, 'X') == 0);  // X Loses
    printf("The Assert Agrees that O wins and X Loses\n");
    show(test3);

    assert(check_win(test4, 'X') == 1);  // X Wins
    assert(check_win(test4, 'O') == 0);  // O Loses
    printf("The Assert Agrees that X wins and O Loses\n");
    show(test4);

    assert(check_win(test5, 'X') == 1);  // X Wins
    assert(check_win(test5, 'O') == 0);  // O Loses
    printf("The Assert Agrees that X wins and O Loses\n");
    show(test5);

    assert(check_win(test6, 'O') == 1);  // O Wins
    assert(check_win(test6, 'X') == 0);  // X Loses
    printf("The Assert Agrees that O wins and X Loses\n");
    show(test6);

    assert(check_win(test7, 'X') == 1);  // X Wins
    assert(check_win(test7, 'O') == 0);  // O Loses
    printf("The Assert Agrees that X wins and O Loses\n");
    show(test7);

    assert(check_win(test8, 'O') == 1);  // O Wins
    assert(check_win(test8, 'X') == 0);  // X Loses
    printf("The Assert Agrees that O wins and X Loses\n");
    show(test8);

    assert(check_win(test9, 'O') == 0);  // O Loses
    assert(check_win(test9, 'X') == 0);  // X Loses
    printf("The Assert Agrees that O loses and X Loses\n");
    show(test9);

    assert(check_win(test10, 'O') == 0);  // O Loses
    assert(check_win(test10, 'X') == 0);  // X Loses
    printf("The Assert Agrees that O loses and X Loses\n");
    show(test10);
}


void deepest_substringAssert() {
    char out[100000];
    deepest_substring("a+((b+c)+d)", out);
    assert(assertStrings(out, "b+c") == 1);
    assert(strcmp(out, "b+c") == 0);
    printf("\n");
    memset(out, 0, 100000); // need these to wipe the out function then the length catch won't work properly
    deepest_substring("(a+((b+c+h)+d)-h*i)", out);
    assert(assertStrings(out, "b+c+h") == 1);
    assert(strcmp(out, "b+c+h") == 0);
    printf("\n");
    memset(out, 0, 100000); // need these to wipe the out function then the length catch won't work properly
    deepest_substring("a+((b-h+c/l)+d)", out);
    assert(assertStrings(out, "b-h+c/l") == 1);
    assert(strcmp(out, "b-h+c/l") == 0);
    printf("\n");
    memset(out, 0, 100000); // need these to wipe the out function then the length catch won't work properly
    deepest_substring("a+b+c+d", out);
    assert(assertStrings(out, "a+b+c+d") == 1);
    assert(strcmp(out, "a+b+c+d") == 0);
    printf("\n");
    memset(out, 0, 100000); // need these to wipe the out function then the length catch won't work properly
    deepest_substring("a+b+c+d", out);
    assert(assertStrings(out, "a+b+c+d") == 1);
    assert(strcmp(out, "a+b+c+d") == 0);
    printf("\n");
    memset(out, 0, 100000); // need these to wipe the out function then the length catch won't work properly
    deepest_substring("((((((((a+b-c*d/e**f+f+f))))))))", out);  // ** means power of in python
    assert(assertStrings(out, "a+b-c*d/e**f+f+f") == 1);  // ** means power of in python
    assert(strcmp(out, "a+b-c*d/e**f+f+f") == 0);  // ** means power of in python
    printf("\n");
    memset(out, 0, 100000); // need these to wipe the out function then the length catch won't work properly
    deepest_substring("((((((((a+b-c*d/e**f+f+f)))))))) * (((((((((5 + 4)))))))))", out);  // ** means power of in python
    assert(assertStrings(out, "5 + 4") == 1);  // 5 + 4 are nested inside 9 brackets not 8 like the first equation
    assert(strcmp(out, "5 + 4") == 0);
    printf("\n");
    memset(out, 0, 100000); // need these to wipe the out function then the length catch won't work properly
    deepest_substring("((((((((a+b-c*d/e**f+f+f)))))))) * ((((((((5 + 4))))))))", out);  // ** means power of in python
    assert(assertStrings(out, "a+b-c*d/e**f+f+f") == 1);  // ** means power of in python
    assert(strcmp(out, "a+b-c*d/e**f+f+f") == 0);  // ** means power of in python
    printf("\n");
    memset(out, 0, 100000); // need these to wipe the out function then the length catch won't work properly


}

# define repetitions 100  // This is how many assertions will be run here
# define maxLengthStrings 1000  // This is the maximum length of the string that can be written
# define stopPrinting 5  // Change this if you want more or less asserts to be printed
void timeForDumb(){
    for (int reps = 0; reps < repetitions; reps++) {
        if (reps <= stopPrinting && reps > 0) printf("Going onto next Assert\n\n");
        char string[maxLengthStrings];
        char letter;
        char firstLetter;

        int length = randRange(5, maxLengthStrings - 1);
        int split = randRange(1, length - 1);

        for (int i = 0; i < length; i++) {
            if (i < split) {
                letter = (char) randRange(97, 122);
            } else {
                letter = (char) randRange(65, 90);
                if (i == split)
                    firstLetter = letter;
            }
            string[i] = letter;
        }
        if (reps <= 5){
            printf("%c == %c\n", first_capital(string, length, 1), firstLetter);
            printS(string, length);
            printf("Going into Assert\n");
            assert(first_capital(string, length, 1) == firstLetter);
            printf("Assert was Successful ");
        }
        else{
            assert(first_capital(string, length, 0) == firstLetter);
        }
        if (reps == stopPrinting){
            printf("This was the final Assert\n");
            printf("\nI have demonstrated 6 asserts so far so I am going to hide the rest from appearing\n"
                   "to prevent too much clutter in the console.\n\n");
        }
    }
    printf("All Done\n");
}


bool make_move(char board[6][7], int column, char player){
    if (board[0][column] == '.' && 0 <= column && column < 7){
        placePiece(board, 0, column, player);
        return true;
    } return false;
}


bool check_win(char board[6][7], char player){
    /* Why you ask does this function just call another function, well that is very simply. Because I don't want to
     * write a new function when this one works perfectly fine. Also I need *ai and aiArr[2] for my ai and adding those
     * to the definition thingy at the top might be a not good thing for me to do so I won't
     */
    int ai, aiArr[2];
    return checkWinConditions(board, player, &ai, aiArr);
}


char first_capital(const char str[], int n, int feature){
    /* middle = e
     * [*, b, c, d, e, F, G, H, *]
     * middle = g
     * [a, b, c, d, *, F, G, H, *]
     * middle = F
     * [a, b, c, d, *, F, *, H, I]
     * e, F, G
     */
    int pointy1 = 0;
    int pointy2 = n;
    int middle = floor((pointy1 + pointy2) / 2);
    for (int i = 0; i < n; i++){  // I dunno didn't want to do math so I use number bigger then needed.
        if (65 <= str[middle] && str[middle] <= 90){
            pointy2 = middle;
        }
        else {
            pointy1 = middle;
        }
        middle = floor((pointy1 + pointy2) / 2);
        if (pointy2 - pointy1 <= 2) {
            char letterReturn;
            if (pointy2 - pointy1 == 1) {
                letterReturn = isCharUpper(str[pointy1], str[pointy2]);
            }
            else if ((pointy2 - pointy1 == 2)) {
                letterReturn = isCharUpper(isCharUpper(str[pointy1], str[middle]), str[pointy2]);
            }
            else {
                letterReturn = str[pointy1];
            }
            if (feature == 1) {
                printf("Big-O == %d\n"
                       "Log2 == %lf\n", i + 1,
                       log2(n));  // i+1 is for loop plus first iteration because can't forget it
            }
            if (65 <= letterReturn  && letterReturn <= 90) return letterReturn;
            else return '0';
        }
    }
    return 'f';  // f is for failure. It also will always trip the assert if this program fails so its also insurance.

//    // A-Z == 65-90
//    // a-z == 97-122

}


void deepest_substring(const char str[], char out[]){
    int biggestParentheses = 0;
    int parentheses = 0;
    for (int i = 0; str[i] != '\0'; i++){
        printf("%c", str[i]);
        if (str[i] == '(') parentheses++;
        if (parentheses > biggestParentheses) biggestParentheses = parentheses;
        if (str[i] == ')') parentheses--;
    }
    printf("\n");
    int pointy = 0;
    int bigBoyParentheses = 0;
    parentheses = 0;
    for (int i = 0; str[i] != '\0'; i++){
        if (str[i] == '(') parentheses++;  // Increases bracket count
        else if (bigBoyParentheses == 1 && str[i] == ')') break;  // breaks once innermost bracket has been copied
        if (parentheses == biggestParentheses) bigBoyParentheses = 1;  // Starts the copying process.
        if (bigBoyParentheses == 1 && str[i] != '(' && str[i] != ')') out[pointy++] = str[i];
    }
    for (int i = 0; out[i] != '\0'; i++){
        printf("%c", out[i]);
    }
    printf("\n");
}


void printS(char str[], int n){
    // A-Z == 65-90
    // a-z == 97-122
    int temp = 0;
    printf("[");
    for (int i = 0; str[i] != '\0' || i < n; i++){
        if (i + 1 == n || str[i + 1] == '\0') printf("%c]\n", str[i]);
        else printf("%c, ", str[i]);
    }

}


char isCharUpper(char x, char y){
    if ((65 <= x && x <= 90) || y < 65 || y > 90)
        return x;
    return y;
}


int randRange(int x, int y){
    return rand() % (y - x) + x;
}


bool assertStrings(const char arr[], const char arrCompare[]){
    int length = 0;
    for (; arr[length] != '\0'; length++){
        if (arr[length] != arrCompare[length]){
            return false;
        }
    }
    if (arrCompare[length] == '\0'){
        return true;
    }
    return false;
}


void makeBoard(char board[6][7]){
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 7; j++){
            board[i][j] = '.';
        }
    }
}


void show(char brd[6][7]){
    printf("  0 1 2 3 4 5 6\n");
    for (int i = 0; i < 6; i++){
        printf("%d ", i);
        for (int j = 0; j < 7; j++){
            printf("%c ", brd[i][j]);
        }
        printf("%d\n", i);
    }
    printf("  0 1 2 3 4 5 6\n\n");
}


bool placePiece(char board[6][7], int row, int column, char player){
    if (board[row][column] != '.') return true;
    else {
        int flipADeeDoo = placePiece(board, row + 1, column, player);
        if (flipADeeDoo == 1) {
            board[row][column] = player;
            return false;
        }
        else return false;
    }
}


int checkDiagonals(char brd[6][7], char piece, int position[2], int direction[2], int move){
    int coords[2] = {position[0] + direction[0], position[1] + direction[1]};
    if (brd[coords[0]][coords[1]] == piece && move < 3 && (0 <= coords[0] && coords[0] < 6 && 0 <= coords[1] && coords[1] < 7)){
        return 1 + checkDiagonals(brd, piece, coords, direction, move+1);
    }
    else{
        return 0;
    }
}


bool checkWinConditions(char brd[6][7], char matchPiece, int *ai, int aiArr[2]){
    /* This will not handle a double win, only finding the first winning move it can find as it should since connect 4
     * isn't a game that is supposed to tie win like that after all, once a winning move is made the game is supposed
     * to come to an end so staying past that is pointless.
     *
     */
    /*
     * [0 0 0 0 0 0 0 0 0]
     * [0 1 0 0 1 0 0 1 0]
     * [0 0 1 0 1 0 1 0 0]
     * [0 0 0 1 1 1 0 0 0]
     * [0 1 1 1 1 1 1 1 0]
     * [0 0 0 1 1 1 0 0 0]
     * [0 0 1 0 1 0 1 0 0]
     * [0 1 0 0 1 0 0 1 0]
     * [0 0 0 0 0 0 0 0 0]
     * First the 8 directions instance point is (4, 4)
     *
     * then go in each direction for 3 moves and count how many match (4, 4) then once done we'll have
     * [0 0 0 0 0 0 0 0 0]
     * [0 0 0 0 0 0 0 0 0]
     * [0 0 0 0 0 0 0 0 0]
     * [0 0 0 3 3 3 0 0 0]
     * [0 0 0 3 1 3 0 0 0]
     * [0 0 0 3 3 3 0 0 0]
     * [0 0 0 0 0 0 0 0 0]
     * [0 0 0 0 0 0 0 0 0]
     * [0 0 0 0 0 0 0 0 0]
     * The process will break for each route after either 3 matches or a piece not matching
     * We will then count up opposites plus the center and if something is greater or equal to 4 true for victory
     */
    int directions[8][2] = {{-1, -1}, {1, 1}, {-1, 0}, {1, 0}, {-1, 1}, {1, -1}, {0, -1}, {0, 1}};

    for (int i = 0; i < 6; i++){

        for (int j = 0; j < 7; j++){

            int countInEachDirection[8] = {0};

            if (brd[i][j] == matchPiece) {

                int startFromCoord[2] = {i, j};

                for (int pickle = 0; pickle < 8; pickle++) {

                    // int goToCoord[2] = {directions[pickle][0] - i, directions[pickle][1] - j};
                    countInEachDirection[pickle] = checkDiagonals(brd, brd[i][j], startFromCoord, directions[pickle], 0);

                }

                for (int pair = 0; pair < 8; pair += 2){

                    // ▼ This basically checks if the opposites plus the center equal 4 ▼
                    if (1 + countInEachDirection[pair] + countInEachDirection[pair + 1] >= 4) {
                        if (*ai == 1) {
                            *ai = 4;
                        }
                        return true;

                    }
                }
            }
        }
    }
    if (*ai == 0) {
        return false;

    }
    else {
        int countInEachDirection[8] = {0};

        for (int pickle = 0; pickle < 8; pickle++) {

            countInEachDirection[pickle] = checkDiagonals(brd, matchPiece, aiArr, directions[pickle], 0);

        }

        int bestLine = 0;

        for (int pair = 0; pair < 8; pair += 2) {

            // ▼ This basically checks if the opposites plus the center equal 4 ▼
            if (1 + countInEachDirection[pair] + countInEachDirection[pair + 1] > bestLine) {

                bestLine = 1 + countInEachDirection[pair] + countInEachDirection[pair + 1];

            }

        }
        *ai = bestLine;
        return false;
    }
}


void newBoard(char referenceBoard[6][7], char copyBoard[6][7]){
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 7; j++){
            copyBoard[i][j] = referenceBoard[i][j];
        }
    }
}


int findRow(char brd[6][7], char piece, int column){
    for (int i = 0; i < 6; i++){
        if (brd[i][column] == piece)
            return i;
    }
    return 0;
}


int AIBrains(char brd[6][7], char player, char opponent, int opponentCheck){

    char copyBoard[6][7]; // creating my copyBoard for independent manipulation
    char copyBoard2[6][7]; // creating my second copyBoard for independent manipulation
    int moves[7] = {0};
    signed int pointsSystem[4] = {0};

    for (int i = 0; i < 7; i++){

        newBoard(brd, copyBoard);  // using my copyBoard for independent manipulation
        if (brd[0][i] == '.')
            pointsSystem[0] = make_move(copyBoard, i, player);  // Made a move so this better then nothing
        else
            pointsSystem[0] = -1000;  // Can't go making an illegal move now can we
        if (pointsSystem[0] == 1){
            int ai = 1;
            int tempArr[2] = {findRow(copyBoard, player, i), i};

            pointsSystem[1] = 100 * checkWinConditions(copyBoard, player, &ai, tempArr);  // Won the game so lots of points
            if (pointsSystem[1] == 100)
                return i;
            pointsSystem[1] += 5 * ai;  // This got the ai closer to winning so it is good
        }
        int movesOpponent[7] = {0};
        int pointsSystemOpponent[2] = {0};
        if (opponentCheck == 1) {
            for (int j = 0; j < 7; j++) {
                newBoard(copyBoard, copyBoard2);  // using my second copyBoard for independent manipulation

                pointsSystemOpponent[0] = make_move(copyBoard2, j, opponent);  // Opponent moves so bad

                if (pointsSystemOpponent[0] == 1) {
                    int ai = 1;
                    int tempArr[2] = {findRow(copyBoard2, opponent, j), j};
                    pointsSystemOpponent[1] = 50 * checkWinConditions(copyBoard2, opponent, &ai, tempArr);  // Opponent won so Bad
                    pointsSystemOpponent[1] += 3 * ai;  // Opponent made a move getting closer to victory.
                }
                movesOpponent[j] = pointsSystemOpponent[0] + pointsSystemOpponent[1];  // Counts opponent Points
            }
            int worstMove[2] = {0};  // Finds best opponent move to return
            for (int moveMakeable = 0; moveMakeable < 7; moveMakeable++) {
                if (movesOpponent[moveMakeable] > worstMove[0]) {
                    worstMove[0] = movesOpponent[moveMakeable];
                    worstMove[1] = moveMakeable;
                }
            }
            pointsSystem[2] = worstMove[0];
            moves[i] = pointsSystem[0] + pointsSystem[1] - pointsSystem[2];  // Counts Ai move to be stored
        }
        else {
            moves[i] = pointsSystem[0] + pointsSystem[1];
        }
    }
    signed int bestMove[2] = {-10000, -10000};
    for (int moveMakeable = 0; moveMakeable < 7; moveMakeable++){
        if (moves[moveMakeable] > bestMove[0]){
            bestMove[0] = moves[moveMakeable];
            bestMove[1] = moveMakeable;

        }
    }
    int allBestMoves[7] = {0};
    int c = 0;
    for (int i = 0; i < 7; i++){
        if (moves[i] == bestMove[0]){
            allBestMoves[c] = i;
            c++;
        }
    }
    int num = rand() % (c);
    return allBestMoves[num];
}


void leAIMakeAMove(char board[6][7], char player, char opponent, char message[]){
    double clk = clock();
    while (1) {
        printf("%s", message);
        fflush(stdout);  // I wanted to have the message appear first before the wait.
        while ((clock() - clk)/CLOCKS_PER_SEC < 0);
        int column = AIBrains(board, player, opponent, 1);  // Go use a brain AI!!!
        printf("%d\n", column);
        if (make_move(board, column, player) == 1) break;
    }
}


bool leMakeAMove(char board[6][7], char player, char message[]){
    double move = 10;  // A number greater then 7
    char notQuiteMove[1000];
    while (1) {
        while (!(0 <= move && move < 7)) {
            printf("%s", message);
            if (scanf("%lf", &move));
            else scanf("%[^\n]s", notQuiteMove);  // I noticed that [^\n] is similar to regex notation in python [^] means exclude these characters
            int a = 0;
            while (getchar() != '\n') {
                if (a == 0)
                    printf("What Ever you gave me had bad values in it. I could stop the game But that is no fun\n");
                a++;
            }
            if (notQuiteMove[0] != '\0' && !(0 <= move && move < 7) || move != floor(move)){

                printf("\n%s is not an accepted value. I could stop the game But that is no fun\n"
                       "The Only Accepted Terms are 0, 1, 2, 3, 4, 5, 6\n\n", notQuiteMove);
                memset(notQuiteMove, 0, 1000);
            }
            else if (!(0 <= move && move < 7) || move != floor(move)) {
                printf("\n%lf is not an accepted value. I could stop the game But that is no fun\n"
                       "The Only Accepted Terms are 0, 1, 2, 3, 4, 5, 6\n\n", move);
                move = 10;
            }
        }
        int moveDecided = (int) move;
        if (make_move(board, moveDecided, player) == 1) break;
        else move = 10;
    }
    return true;
}


void secretRules(int *player1, int *player2, int *infinity){
    // Don't look this is private
    char ans[10] = {};
    printf("\n\n\nDo you want the sneaky Game??? say 'no' if TA as TA not allowed heheheh ☺☺☺☺☺: ");
    scanf("%s", ans);
    if (strcmp(ans, "yes") == 0){
        char play1[10] = {};
        char play2[10] = {};
        char play3[10] = {};
        printf("Do you want the sneaky Player1???: ");
        scanf("%s", play1);
        printf("Do you want the sneaky Player2???: ");
        scanf("%s", play2);
        printf("Do you want the sneaky rule 3???: ");
        scanf("%s", play3);
        if (strcmp(play1, "yes") == 0) *player2 = 1;
        if (strcmp(play2, "yes") == 0) *player1 = 1;
        if (strcmp(play3, "yes") == 0) *infinity = 1;
        if (*player1 == 1 || *player2 == 1) printf("Yay AI!!!!\n");
        else printf("Guess no AI this time.... \n");
    }
    else printf("Guess no AI this time.... \n");
}


bool doesGameStillHaveSpace(char brd[6][7]){
    for (int i = 0; i < 7; i++){
        if (brd[0][i] == '.') return true;
    }
    return false;
}


#define Symbol1 "X"
#define Symbol2 "O"

void gameMaster(){
    int blankArr[2]; // This is a blank array because unlike python I don't know how to send no parameter occasionally
    int blankAI = 0;
    int player1 = 0;
    int player2 = 0;
    int rule3 = 0;
    secretRules(&player1, &player2, &rule3);


    while (1) {
        char gameBoard[6][7];
        makeBoard(gameBoard);
        show(gameBoard);
        while (1) {
            if (player1 == 0) leMakeAMove(gameBoard, Symbol1[0], "Player 1 is up to play. What column shall you pick hmm: ");
            else leAIMakeAMove(gameBoard, Symbol1[0], Symbol2[0], "AI 1 is up to play. What column shall you pick hmm: ");
            show(gameBoard);
            if (checkWinConditions(gameBoard, Symbol1[0], &blankAI, blankArr) == 1) {
                printf("Numero Uno is Player 1\n    Player 1 Wins\n");
                break;
            }
            if (doesGameStillHaveSpace(gameBoard) == 0) break;


            if (player2 == 0) leMakeAMove(gameBoard, Symbol2[0], "Player 2 is up to play. What column shall you pick hmm: ");
            else leAIMakeAMove(gameBoard, Symbol2[0], Symbol1[0], "AI 2 is up to play. What column shall you pick hmm: ");
            show(gameBoard);
            if (checkWinConditions(gameBoard, Symbol2[0], &blankAI, blankArr) == 1) {
                printf("Numero Uno is Player 2\n    Player 2 Wins\n");
                break;
            }
            if (doesGameStillHaveSpace(gameBoard) == 0) break;

        }
        if (doesGameStillHaveSpace(gameBoard) == 0)
            printf("This game was a failure so grotesque that no team even won!!!!\n");
        if (rule3 == 0)
            break;
    }
}
