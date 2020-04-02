#include <iostream>
#include <chrono>
#include <thread>
using namespace std;



/**Funtion to write strings across several lines
 *
 * @param text_width - Number of chars per line
 * @param text       - Text to write
 * @param padding    - Spaces before the line
 * */
std::string stringWriter(size_t text_width, std::string text, size_t padding = 0) {
    size_t charNbr;
    std::string output_str;

    while (!text.empty()) {
        output_str += string(padding, ' ');
        if (text.size() <= text_width) {
            output_str += (text + '\n');
            text.erase(0, text.size());
            continue;
        }

        charNbr = text_width - 1;
        if (text.at(charNbr) == '.' || text.at(charNbr) == ',' || text.at(charNbr) == '!' || text.at(charNbr) == '?' ||
            text.at(charNbr) == ';' || text.at(charNbr) == ' ') {
            output_str += (text.substr(0, charNbr + 1) + '\n');
            text.erase(0, charNbr + 1);
            continue;
        }


        if (isalnum(charNbr)) {
            if (text.at(charNbr + 1) == ' ') {
                output_str += (text.substr(0, charNbr + 1) + '\n');
                text.erase(0, charNbr + 1);
                text.erase(0, 1);
                continue;
            } else if (text.at(charNbr + 1) == '.' || text.at(charNbr + 1) == ',' || text.at(charNbr + 1) == '!' ||
                       text.at(charNbr + 1) == '?' || text.at(charNbr + 1) == ';') {
                while (isalnum(text.at(charNbr)) && isalnum(text.at(charNbr - 1))) {
                    charNbr--;
                }
                output_str += (text.substr(0, charNbr) + '\n');
                text.erase(0, charNbr);
                continue;
            } else {
                while (isalnum(text.at(charNbr)) && isalnum(text.at(charNbr - 1))) {
                    charNbr--;
                }
                output_str += (text.substr(0, charNbr) + '\n');
                text.erase(0, charNbr);
                continue;
            }
        }
    }
    return output_str;
}



/**Funtion to write numbers in the form '000...a' where a is the number you want to write
 *
 * @param width  - Number of houses to occupy
 * @param number - Number to write
 * */
std::string zeroAdder(size_t width, int number) {
    std::string output_str;
    output_str = std::to_string(number);
    if (output_str.size() < width) {
        size_t nrOf0 = width - output_str.size();
        for (nrOf0; nrOf0 > 0; nrOf0--) {
            output_str = '0' + output_str;
        }
    }
    return output_str;
}

const size_t ignores = 10000;

//game function declaration
void game();


std::chrono::milliseconds timespan(250); // Tme for the sleep functions


#ifdef _WIN32
#define UNICODE
#include <windows.h>
#include <wincon.h>

// Fix compilatin on MinGW
#ifndef DISABLE_NEWLINE_AUTO_RETURN
#define DISABLE_NEWLINE_AUTO_RETURN 0x0008
#endif

#ifndef ENABLE_VIRTUAL_TERMINAL_INPUT
#define ENABLE_VIRTUAL_TERMINAL_INPUT 0x0200
#endif

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

bool SetupConsole() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    // Set output mode to handle virtual terminal sequences
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hIn == INVALID_HANDLE_VALUE || hOut == INVALID_HANDLE_VALUE) {
        return false;
    }
    DWORD dwOriginalInMode = 0;
    DWORD dwOriginalOutMode = 0;
    if (!GetConsoleMode(hIn, &dwOriginalInMode)) {
        return false;
    }
    if (!GetConsoleMode(hOut, &dwOriginalOutMode)) {
        return false;
    }
    DWORD dwInMode = dwOriginalInMode | ENABLE_VIRTUAL_TERMINAL_INPUT;
    if (!SetConsoleMode(hIn, dwInMode))
    {
        // Failed to set VT input mode, can't do anything here.
        return false;
    }
    DWORD dwOutMode = dwOriginalOutMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
    if (!SetConsoleMode(hOut, dwOutMode)) {
        // we failed to set both modes, try to step down mode gracefully.
        dwOutMode = dwOriginalOutMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        if (!SetConsoleMode(hOut, dwOutMode))
        {
            // Failed to set any VT mode, can't do anything here.
            return false;
        }
    }
    return true;
}
#endif //_WIN32

/**Clears the console*/
void clearConsole(){
    cout << "\x1B[2J\x1B[H";
}

/*/////////////////////////////////////////////////////////////////////////////*/



/**Capture function (Not the tests)
 *
 * @param p1     - Player 1 Board
 * @param player1Name - Player 1 Name (Received as a const string reference, since we dont need to change it, saving mem)
 * @param score1     - Player 1 Score (Received as a pointer to the value declared in the game function)
 * @param p2    - Player 2 Board
 * @param player2Name - Player 2 Name (Received as a const string reference, since we dont need to change it, saving mem)
 * @param score2      - Player 2 Score (Received as a pointer to the value declared in the game function)
 * */
void drawTable(int p1[], const string &player1Name, int score1, int p2[], const string &player2Name,  int score2) {
    string scoreP1 = player1Name + string(" points:");
    string scoreP2 = player2Name + string(" points:");
    cout << string(2, '\n');
    cout << string(2, ' ');
    cout << scoreP2 << endl;
    cout << string(2, ' ') << string(scoreP2.size() - 2, ' ') << zeroAdder(2, score2) << endl;
    cout << string(2, ' ') << string(scoreP2.size() + 5, ' ') << "   " <<  "6" << "      " << "5" << "      " << "4" << "      " << "3" << "      "
    << "2" << "      " << "1" << "  \n";
    cout << string(2, ' ') << string(scoreP2.size() + 5, ' ') << string("┌─────────────────────────────────────────┐\n");
    cout << string(2, ' ') << string(scoreP2.size() + 5, ' ') << "│  " << zeroAdder(2, p2[5]) << "  │  " <<
         zeroAdder(2, p2[4]) << "  │  " << zeroAdder(2, p2[3]) << "  │  " <<
         zeroAdder(2, p2[2]) << "  │  " << zeroAdder(2, p2[1]) << "  │  " <<
         zeroAdder(2, p2[0]) << "  │\n";
    cout << string(2, ' ') << string(scoreP2.size() + 5, ' ') << string("└─────────────────────────────────────────┘\n");
    cout << string("\n");
    cout << string(2, ' ') << string(scoreP2.size() + 5, ' ') << string("┌─────────────────────────────────────────┐\n");
    cout << string(2, ' ') << string(scoreP2.size() + 5, ' ') << "│  " << zeroAdder(2, p1[0]) << "  │  " <<
         zeroAdder(2, p1[1]) << "  │  " << zeroAdder(2, p1[2]) << "  │  " <<
         zeroAdder(2, p1[3]) << "  │  " << zeroAdder(2, p1[4]) << "  │  " <<
         zeroAdder(2, p1[5]) << "  │\n";
    cout << string(2, ' ') << string(scoreP2.size() + 5, ' ') << string("└─────────────────────────────────────────┘\n");
    cout << string(2, ' ') << string(scoreP2.size() + 5, ' ') << "    " <<  "1" << "      " << "2" << "      " << "3" << "      " << "4" << "      "
         << "5" << "      " << "6" << "  \n";
    cout << string(2, ' ') << string(scoreP2.size() + 5 + 43 + 5, ' ') << scoreP1 << endl;
    cout << string(2, ' ') << string(scoreP2.size() + 5 + 43 + 5 + scoreP1.size() - 2, ' ') << zeroAdder(2, score1) << endl;
    cout << string(2, '\n');
}



/**Check if the game as come to an end
 * @param score1 - player1 score
 * @param score2 - player2 score*/
bool gameEnd(int score1,  int score2) {
    if (score1 == 24 && score2 == 24){
        return true;
    }
    else if (score1 > 24 || score2 > 24){
       return true;
    }
    else
        return false;
}



/**Function to introduce the changes made in the board
 * @param player1Name - player1 name
 * @param player2Name - player2 name*/
int firstPlayer(const string &player1Name, const string &player2Name) {
    srand(time(NULL));
    int first = rand() % 2;
    if (first) {
        cout << string(5, ' ') << player2Name << " goes first." << endl;
        return first;
    } else {
        cout << string(2, ' ') << player1Name << " goes first." << endl;
        return first;
    }
}



/**Function to introduce the changes made in the board
 * @param playerToEat  - Board of the opponent
 * @param lastHouse - House chosen by the player in turn*/
void capturesTest(int playerToEat[], size_t lastHouse) {
    while (playerToEat[lastHouse] >= 2 && playerToEat[lastHouse] <= 3 && lastHouse >= 0) {
        playerToEat[lastHouse] = 0;
        lastHouse--;
    }
}



/**Capture function (Not the tests)
 *
 * @param player1     - Player 1 Board
 * @param player1Name - Player 1 Name (Received as a const string reference, since we dont need to change it, saving mem)
 * @param score1      - Player 1 Score (Received as a pointer to the value declared in the game function)
 * @param player2     - Player 2 Board
 * @param player2Name - Player 2 Name (Received as a const string reference, since we dont need to change it, saving mem)
 * @param score2      - Player 2 Score (Received as a pointer to the value declared in the game function)
 * @param playerToEat - Board of the player playing this turn
 * @param lastHouse   - House chosen by the player
 * @param turnName    - Name of the player playing this turn (Received as a const string reference, since we dont need to change it, saving mem)
 * @param turnPoints  - Score of the player playing this turn (Received as a pointer to the value declared in the game function)
 * */
void captures(int player1[], const string &player1Name, int *score1, int player2[], const string &player2Name, int *score2,
             int playerToEat[], size_t lastHouse, const string &turnName, int *turnPoints) {
    int points = 0;
    while (playerToEat[lastHouse] >= 2 && playerToEat[lastHouse] <= 3 && lastHouse >= 0) {
        points += playerToEat[lastHouse];
        *turnPoints += playerToEat[lastHouse];
        playerToEat[lastHouse] = 0;
        lastHouse--;
        clearConsole();
        drawTable(player1, player1Name, *score1, player2, player2Name, *score2);
        std::this_thread::sleep_for(timespan);
    }
    cout << string(2, ' ') << turnName << " ate " << points << " seeds!"<< endl;
}



/**Function to test the possible moves
 * @param turn  - Board of the player in turn
 * @param nTurn - Board of the opponent
 * @param house - House chosen by the player in turn*/
int testSowerAndCap(int turn[], int nTurn[], size_t house) {
    bool capture = false;
    if (!turn[house]) {                                               // Check if its a empty house
        return -1;
    } else {
        int temp = turn[house];                                       // Sow
        turn[house] = 0;
        for (size_t i = house + 1; i <= 5 && temp > 0; i++) {
            turn[i] += 1;
            temp--;
        }
        while (temp) {
            for (size_t i = 0; i <= 5 && temp > 0; i++) {
                nTurn[i] += 1;
                temp--;
                if (temp < 1) {
                    if (nTurn[i] >= 2 && nTurn[i] <= 3) {
                        capture = true;                               // Check for captures
                        capturesTest(nTurn, i);                       // Apply changes made by the captures
                    }
                }
            }
            for (size_t i = 0; i <= 5 && temp > 0; i++) {
                if (i != house) {
                    turn[i] += 1;
                    temp--;
                }
            }
        }
        if (capture){
            int checkSeeds = 0;
            for (size_t i = 0; i < 6; i++){
                checkSeeds += nTurn[i];
            }
            if (checkSeeds) {
                return 1;
            }
            else {
                return -2;                                            // Prevent 'Grand slam'
            }
        }
        int checkSeedsNTurn = 0;                                      // Force the players to share seeds with the opponent if possible
        bool nextRound = false;
        for (size_t i = 0; i < 6; i++){
            checkSeedsNTurn += nTurn[i];
        }
        if (checkSeedsNTurn){
            return 0;
        }
        else{
            for (size_t i = 0; i < 6; i++){
                if (turn[i] > 6-i)
                    nextRound = true;
            }
            if(!nextRound) {
                return 2;
            }
            else{
                return -3;
            }
        }

    }

}



/**Takes care of sow when there are no captures (Not the tests)
 *
 * @param player1     - Player 1 Board
 * @param player1Name - Player 1 Name (Received as a const string reference, since we dont need to change it, saving mem)
 * @param score1      - Player 1 Score (Received as a pointer to the value declared in the game function)
 * @param player2     - Player 2 Board
 * @param player2Name - Player 2 Name (Received as a const string reference, since we dont need to change it, saving mem)
 * @param score2      - Player 2 Score (Received as a pointer to the value declared in the game function)
 * @param turn        - Board of the player playing this turn
 * @param nTurn       - Board of the player waiting this turn
 * @param house       - House chosen by the player
 * @param turnName    - Name of the player playing this turn (Received as a const string reference, since we dont need to change it, saving mem)
 * */
void sower(int player1[], const string &player1Name, int score1, int player2[], const string &player2Name, int score2, int turn[],
           int nTurn[], size_t house, const string &turnName) {
    int temp = turn[house];                                                         // Temp variable to store seed to sow
    turn[house] = 0;                                                                // Remove seeds from the chosen house
    clearConsole();
    drawTable(player1, player1Name, score1, player2, player2Name, score2);
    std::this_thread::sleep_for(timespan);
    for (size_t i = house + 1; i <= 5 && temp > 0; i++) {                           // Sow seeds in the field of the turn player
        turn[i] += 1;
        temp--;
        clearConsole();
        drawTable(player1, player1Name, score1, player2, player2Name, score2);
        cout << "  " << turnName << " chose house " << house + 1 << "." << endl;
        std::this_thread::sleep_for(timespan);
    }
    while (temp) {                                                                 // While there's seeds distribute the for each players board
            for (size_t i = 0; i <= 5 && temp > 0; i++) {                          // Opponent's board
                nTurn[i] += 1;
                temp--;
                clearConsole();
                drawTable(player1, player1Name, score1, player2, player2Name, score2);
                cout << "  " << turnName << " chose house " << house + 1 << "." << endl;
                std::this_thread::sleep_for(timespan);
            }
            for (size_t i = 0; i <= 5 && temp > 0; i++) {                          // Player board
                clearConsole();
                if (!(i == house)){                                                // Can't sow in the house from which the seeds were removed
                    turn[i] += 1;
                    temp--;
                }
                drawTable(player1, player1Name, score1, player2, player2Name, score2);
                cout << "  " << turnName << " chose house " << house + 1 << "." << endl;
                std::this_thread::sleep_for(timespan);
            }
        }
}



/**Takes care of sow and invokes the capture function (Not the tests)
 *
 * @param player1     - Player 1 Board
 * @param player1Name - Player 1 Name (Received as a const string reference, since we dont need to change it, saving mem)
 * @param score1      - Player 1 Score (Received as a pointer to the value declared in the game function)
 * @param player2     - Player 2 Board
 * @param player2Name - Player 2 Name (Received as a const string reference, since we dont need to change it, saving mem)
 * @param score2      - Player 2 Score (Received as a pointer to the value declared in the game function)
 * @param turn        - Board of the player playing this turn
 * @param nTurn       - Board of the player waiting this turn
 * @param house       - House chosen by the player
 * @param turnName    - Name of the player playing this turn (Received as a const string reference, since we dont need to change it, saving mem)
 * @param turnPoints  - Score of the player playing this turn (Received as a pointer to the value declared in the game function)
 * */
void sowerAndCap(int player1[], const string &player1Name, int *score1, int player2[], const string &player2Name, int *score2, int turn[],
           int nTurn[], size_t house, const string &turnName, int *turnPoints) {
    // To check how the sow function works see the sower function. Comments only regarding the capture function
    int temp = turn[house];
    turn[house] = 0;
    clearConsole();
    drawTable(player1, player1Name, *score1, player2, player2Name, *score2);
    std::this_thread::sleep_for(timespan);
    for (size_t i = house + 1; i <= 5 && temp > 0; i++) {
        turn[i] += 1;
        temp--;
        clearConsole();
        drawTable(player1, player1Name, *score1, player2, player2Name, *score2);
        cout << string(2, ' ') << turnName << " chose house " << house + 1 << "." << endl;
        std::this_thread::sleep_for(timespan);
    }
    while (temp) {
        for (size_t i = 0; i <= 5 && temp > 0; i++) {
            nTurn[i] += 1;
            temp--;
            clearConsole();
            drawTable(player1, player1Name, *score1, player2, player2Name, *score2);
            cout << string(2, ' ') << turnName << " chose house " << house + 1 << "." << endl;
            std::this_thread::sleep_for(timespan);
            if(temp < 1)                                                   // In the last seed call the captures function
                captures(player1, player1Name, score1, player2, player2Name, score2, nTurn, i, turnName, turnPoints);
        }
        for (size_t i = 0; i <= 5 && temp > 0; i++) {
            clearConsole();
            if (i != house){                                                // Can't sow in the house from which the seeds were removed
                turn[i] += 1;
                temp--;
            }
            drawTable(player1, player1Name, *score1, player2, player2Name, *score2);
            cout << "  " << turnName << " chose house " << house + 1 << "." << endl;
            std::this_thread::sleep_for(timespan);
        }
    }
}




/** Game engine; Includes arrays with players' houses and seeds, scores, handles the turns and the win/draw messages
 * as well as sorting the input/output according to the game context.
 *
 * @param player1Name - Name of the first player
 * @param player2Name - Name of the second player (default = Computer)
 */
void logic(const string &player1Name, const string &player2Name = "Computer") {

    int player1[6] = {4, 4, 4, 4, 4, 4};
    int player2[6] = {4, 4, 4, 4, 4, 4};
    int player1cpy[6];
    int player2cpy[6];
    int score1 = 0;
    int score2 = 0;
    clearConsole();
    drawTable(player1, player1Name,score1, player2, player2Name, score2);
    int turn = firstPlayer(player1Name, player2Name);                       // Randomly chose first player
    while (!gameEnd(score1, score2)) {                                      // While there's no end to the game
        copy(begin(player1), end(player1), begin(player1cpy));   // Board copy to use in the test functions
        copy(begin(player2), end(player2), begin(player2cpy));
        if (turn) {                                                         // Turn oscillator
            if (player2Name == "Computer") {                                // Random bot implementation
                size_t house;
                house = rand() % 6;
                int sowRet;
                sowRet = testSowerAndCap(player2cpy, player1cpy, house);
                if (sowRet == -1) {                                         // House selected has no seeds
                    continue;
                }
                else if (sowRet == -2) {                                    // The capture leaves the opponent with no seeds
                                                                            // (grand slam preventive)
                    continue;
                }
                else if (sowRet == -3){                                     // While the play doesn't share seeds with the opponent,
                                                                            // if he as none, ask for another house
                    continue;
                }
                else if (sowRet == 1) {                                     // There's a capture to be done
                    cout << '\n' << string(2, ' ') << player2Name << "'s turn!" <<endl;
                    cout << '\n' << string(2, ' ') << player2Name<< " chose " << house + 1 << endl;
                    cout << '\n' << string(2, ' ') << "Press any key to continue..." << endl;
                    cin.get();
                    cin.ignore(ignores, '\n');
                    sowerAndCap(player1, player1Name, &score1, player2, player2Name, &score2, player2, player1, house,
                          player2Name, &score2);
                }
                else if (sowRet == 2){                                     // The opponent has no seeds and it is impossible to shar with him
                                                                           // Game ends
                    break;
                }
                else {                                                     // No captures, seeds need to be sown
                    cout << '\n' << string(2, ' ') << player2Name << "'s turn!" <<endl;
                    cout << '\n' << string(2, ' ') << player2Name <<" chose " << house + 1 << endl;
                    cout << string(2, ' ') << "Press enter key to continue..." << endl; cin.get();
                    sower(player1, player1Name, score1, player2, player2Name, score2, player2, player1, house,
                          player2Name);
                }

            }                            // Computer playing
            else {                                                          // Player 2 turn
                size_t house;
                cout << '\n' << string(2, ' ') << player2Name << "'s turn!" << endl;
                cout << '\n' << string(2, ' ') << "Input your house: ";
                if (cin.peek() >= '1' && cin.peek() <= '6') {                   // Handle valid input for the game
                    cin >> house;
                    cin.ignore(ignores, '\n');
                    if (house < 1 || house > 6) {
                        cout << "\n  Input a valid house!" << endl;
                        continue;
                    }
                    int sowRet;
                    sowRet = testSowerAndCap(player2cpy, player1cpy, house - 1);
                    if (sowRet == -1){
                        cout << "\n  You chose a house with no seeds!!! Chose another." << endl;
                        continue;
                    }
                    else if (sowRet == -2) {
                        cout << "\n  Can't eat that!!! Your opponent needs those seeds for next round." << endl;
                        continue;
                    }
                    else if (sowRet == -3){
                        cout << "\n  Chose another house! Your opponent needs seeds!" << endl;
                        continue;
                    }
                    else if (sowRet == 1) {
                        sowerAndCap(player1, player1Name, &score1, player2, player2Name, &score2, player2, player1, house - 1,
                              player2Name, &score2);
                    }
                    else if (sowRet == 2){
                        cout << "\n  No more moves available... We will have to end our game." << endl;
                        break;
                    }
                    else {
                        sower(player1, player1Name, score1, player2, player2Name, score2, player2, player1, house - 1,
                              player2Name);
                    }
                }
                else {                                                      // Handle exit or invalid input
                    cin.clear();
                    if (cin.peek() == 'e' || cin.peek() == 'E') {
                        cin.ignore(ignores, '\n');
                        return;
                    } else {
                        cout << "\n  Input a valid house!" << endl;
                        cin.ignore(ignores, '\n');
                        continue;
                    }
                }
            }
        }
        else {                                                              // Player 1 Turn
            int house;
            cout << '\n' << string(2, ' ') << player1Name << "'s turn!" << endl;
            cout << '\n' << string(2, ' ') << "Input your house: ";
            if (cin.peek() >= '1' && cin.peek() <= '6') {
                cin >> house;
                cin.ignore(ignores, '\n');
                if (house < 1 || house > 6) {
                    cout << "\n  Input a valid house!" << endl;
                    continue;
                }
                int sowRet;
                sowRet = testSowerAndCap(player1cpy, player2cpy, house - 1);
                if (sowRet == -1){
                    cout << "\n  You chose a house with no seeds!!! Chose another." << endl;
                    continue;
                }
                else if (sowRet == -2){
                    cout << "\n  Can't eat that!!! Your opponent needs those seeds for next round." << endl;
                    continue;
                }
                else if (sowRet == -3){
                    cout << "\n  Chose another house! Your opponent needs seeds!" << endl;
                    continue;
                }
                else if (sowRet == 1) {
                    sowerAndCap(player1, player1Name, &score1, player2, player2Name, &score2, player1, player2, house - 1,
                                player1Name, &score1);
                }
                else if (sowRet == 2){
                    cout << "\n  No more moves available... We will have to end our game." << endl;
                    break;
                }
                else {
                    sower(player1, player1Name, score1, player2, player2Name, score2, player1, player2, house - 1,
                          player1Name);
                }
            }
            else {
                cin.clear();
                if (cin.peek() == 'e' || cin.peek() == 'E') {
                cin.ignore(ignores, '\n');
                return;
                }
                else {
                    cout << "\n  Input a valid house!" << endl;
                    cin.ignore(ignores, '\n');
                continue;
                }
             }
        }
        turn = (turn + 1) % 2;
    }
    if (score1 > score2){
        cout << string(2, ' ') << player1Name << " wins!" << endl;
    }
    else if (score2 > score1){
        cout << string(2, ' ') << player2Name << " wins!" << endl;
    }
    else if (score1 == score2){
        cout << string(2, ' ') << "That's a draw! Good game you two." << endl;
    }

}



/**Function to assert if the game will be single or multiplayer and get the player names*/
void playerOrComputer() {

    cout << '\n' << string(2, ' ') << "Press '1' to start a game against the computer, press '2' to play a 2 player game: ";
    if (cin.peek() == '1') {
        cin.ignore(ignores, '\n');
        string playerName;
        cout << '\n' << string(2, ' ') << "Input your name: ";
        getline(cin, playerName);
        logic(playerName);
        return;
    } else if (cin.peek() == '2') {
        cin.ignore(ignores, '\n');
        string player1Name, player2Name;
        cout << '\n' << string(2, ' ') << "Input Player1's name: ";
        getline(cin, player1Name);
        cout << '\n' << string(2, ' ') << "Input Player2's name: ";
        getline(cin, player2Name);
        logic(player1Name, player2Name);
        return;
    } else if (cin.peek() == 'e' || cin.peek() == 'E') {
        cin.ignore(ignores, '\n');
        return;
    } else {
        // Handle invalid inputs
        cin.ignore(ignores, '\n');
        cout << "  Error: Invalid input!" << endl;
        cout << string(2, '\n');
        playerOrComputer();
    }
}



/**Dialogue 2 - Present the possibility to go to the game and back to the opening message*/
void rulesDialogue() {

    cout << string(2, '\n') << '  ' << "Press 'g' to start a game, press 'b' to go back: ";
    if (cin.peek() == 'g' || cin.peek() == 'G') {
        cin.ignore(ignores, '\n');
        playerOrComputer();
        return;
    } else if (cin.peek() == 'b' || cin.peek() == 'B') {
        cin.ignore(ignores, '\n');
        game();
    } else if (cin.peek() == 'e' || cin.peek() == 'E') {
        cin.ignore(ignores, '\n');
        return;
    } else {
        // Handle invalid inputs
        cin.ignore(ignores, '\n');
        cout << "  Error: Invalid input!" << endl;
        cout << string(2, '\n');
        rulesDialogue();
    }
}



/**Present the game rules*/
void gameRules() {

    clearConsole();
    cout
            << "#######################################################################################################"
            << endl;
    cout << "### GENERAL\n" << endl;
    cout << stringWriter(100,
                         "The Oware game is an game from the Mancala family of board games with Ashanti origin "
                         "in Ghana.", 2);
    cout << endl;
    cout << string(2, ' ') << "The game requires 48 seeds and board like  this one:" << endl;
    int test1[6] = {4, 3, 3, 6, 4, 2};
    int test2[6] = {6, 4, 4, 2, 6, 4};
    drawTable(test1, "Player 1", 0, test2, "Player 2",0);

    cout << stringWriter(100,
                         "The game starts with 4 seed in each house. The goal of the game is to capture more "
                         "seeds than your opponent and, since there are 48 seeds, capturing 25 is enough. The game can "
                         "end with a draw, since there's a even number of seeds.", 2);

    cout << endl;
    cout << "### Sowing\n" << endl;
    cout << stringWriter(100,
                         "Players take turns moving the seeds. On each turn, the player chooses one of the six "
                         "houses on their side of the table, removing all the seeds in that house and distributing them "
                         "for the next houses, one seed per house, including the opponent's houses, in a "
                         "counterclockwise way. You can't seed either in the score houses or in the house you picked to "
                         "remove the seeds.", 2);
    cout << endl;
    cout << "### Capturing\n" << endl;
    cout << stringWriter(100,
                         "You can capture the seeds in a opponent's house when, the last sowed seed makes a house "
                         "2 or 3 seeds, and doesn't capture all of the opponent's seeds. In a turn you can capture seeds"
                         " from more than one house. The captured seeds are stored in the scoring houses.", 2);
    cout << endl;
    cout
            << "#######################################################################################################"
            << endl;
    cout << string(2, ' ');
    rulesDialogue();
}



/**Dialogue 1 - Present the possibility to go to rules and skip to game*/
void openingDialogue() {

    string openstring;
    openstring = stringWriter(100,
                              "Press 'r' to see the rules of the game, 'g' to skip to the game (You can press 'e' to exit the game at anytime): ", 2);
    openstring.erase(openstring.size() - 1, 1);                                                                 // Delete the '\n' included by the stringWriter function
    cout << openstring;
    if (cin.peek() == 'r' || cin.peek() == 'R') {
        cin.ignore(ignores, '\n');
        gameRules();
        return;
    } else if (cin.peek() == 'g' || cin.peek() == 'G') {
        cin.ignore(ignores, '\n');
        playerOrComputer();
        return;
    } else if (cin.peek() == 'e' || cin.peek() == 'E') {
        cin.ignore(ignores, '\n');
        return;
    } else {
        // Handle invalid inputs in the prompt
        cin.ignore(ignores, '\n');
        cout << "  Error: Invalid input!" << endl;
        cout << string(2, '\n');
        openingDialogue();
    }
}



/**Opening message for the game*/
void openingMessage() {

    clearConsole();
    cout
            << "##################################################################################################################################"
            << endl << endl;
    cout
            << "---------------------------------------------  OWARE - A count and capture game  -------------------------------------------------"
            << endl << endl;
    cout
            << "##################################################################################################################################"
            << endl;
    cout << "Author: José Costa T1_201907216 <up201907216@fe.up.pt> " << endl;
    cout
            << "Game Developed for the 1st year Programming Course of the Master in Informatics and Computing Engineering (EI0012) (April 2020) "
            << string(3, '\n');
}



/**This function displays the opening message for the game and allows to return from the rulesDialogue*/
void game() {
    openingMessage();
    openingDialogue();
}



/**This is the main function, used to setup the Windows console (Program developed in Linux), display the opening message and take care of the game exit*/
int main() {
#ifdef _WIN32
    SetupConsole();
#endif
    game();
    cin.clear();
    cout << "  Press enter key to exit the game..." << endl; cin.get();

    return 0;
}
