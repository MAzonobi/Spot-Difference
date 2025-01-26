/* File: proj1.cpp
Project: Spot the Difference Game
Description: This program prompts the user to spot the difference between two images displayed from 
text files

*/

#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
using namespace std;

const int ROWS = 10;  // number of rows for the grid
const int COLS = 21;  // number of columns for the grid


// Name: loadFile
// PreCondition: A valid filename must be entered by the user
// PostConditon: If the file is valid, it is loaded into the 'art' array. Otherwise return false.
bool loadFile(char art[ROWS][COLS]) {
    string fileName;
    cout << "What is the name of the data file to import?" << endl;
    cin >> fileName;

    // Opens file if possible, returns false if file is not valid
    fstream file(fileName);
    if (!file) {
        cout << "File not found." << endl;
        return false;  
    }
    // Initializes 'art' array 
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            art[i][j] = ' ';
        }
    }
    // Declares variables for file inputs
    int row;
    int col;
    char symbol;

    while (file >> row >> col >> symbol) {
        art[row][col] = symbol;
    }
    file.close();

    cout << "Done" << endl;
    return true;  
}

// Name: displayArt
// PreCondition: The file must successfully be loaded 
// PostCondition: ASCII art is displayed on screen
void displayArt(char art[ROWS][COLS], bool isLoaded) {
    if (!isLoaded) {
        cout << "No file loaded." << endl;
        return;
    }

    // Creates spaces between column numbers 
    cout << "   ";  
    for (int i = 0; i < COLS; ++i) {
        if (i < 10)
            cout << i << "  ";  
        else
            cout << i << " ";   
    }
    cout << endl;


    // Creates spaces between the row numbers 
    for (int i = 0; i < ROWS; ++i) {
        
        if (i < 10)
            cout << " " << i << " ";  
        else
            cout << i << " ";         

        for (int j = 0; j < COLS; ++j) {
            cout << art[i][j] << "  ";  
        }
        cout << endl;
    }
}

// Name: clearArray
// PreCondition: The array is the size of ROWS x COLS
// PostCondition: The array is cleared and elements become spaces
void clearArray(char art[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i)
        for (int j = 0; j < COLS; ++j)
            art[i][j] = ' ';
}

// Name: guessChange
// PreCondition: correctRow and correctCol and integer coordinates of change
// PostCondition: The user is prompted to guess the location of change
void guessChange(int correctRow, int correctCol) {

    int guessedRow, guessedCol;

    // The user prompt continues to loop until the coordinates are correct
    do {
        cout << "What row is the change in?" << endl;
        cin >> guessedRow;
        cout << "What column is the change in?" << endl;
        cin >> guessedCol;
        if (guessedRow == correctRow && guessedCol == correctCol) {
            cout << "You are correct!" << endl;
        } else {
            cout << "That is incorrect!" << endl;
        }
    } while (guessedRow != correctRow || guessedCol != correctCol);
}

// Name: playGame
// PreCondition: Array for ASCII art is displayed 
// PostCondition: The game begins and the user is prompted to guess the change
void playGame(char art[ROWS][COLS], bool isLoaded) {
    if (!isLoaded) {
        cout << "No file loaded." << endl;
        return;
    }

    char copyArt[ROWS][COLS];

    // Creates a copy of the original art array
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            copyArt[i][j] = art[i][j];
        }
    }
    
    int randomRow = rand() % ROWS;
    int randomCol = rand() % COLS;

    char original = copyArt[randomRow][randomCol];
    char changed = (rand() % (126 - 33 + 1)) + 33;

    // Ensures that the changes in the art is randomized
    while (changed == original) {
        changed = (rand() % (126 - 33 + 1)) + 33;
    }

    copyArt[randomRow][randomCol] = changed;

    displayArt(art, isLoaded);         
    displayArt(copyArt, isLoaded);     
    guessChange(randomRow, randomCol);
}

// Name: mainMenu
// PreCondition: The user is ready to make a selection
// PostCondition: Displays the mainmenu options to the user and returns an integer 
int mainMenu() {
    int choice;
    cout << "What would you like to do?" << endl;
    cout << "1. Load ASCII Art from File" << endl;
    cout << "2. Display Art" << endl;
    cout << "3. Play Game" << endl;
    cout << "4. Exit" << endl;
    cin >> choice;
    return choice;
}

// Name: main
// PreCondition: All necessary functions have been defined
// PostCondition: Executes game functionality until the user selects exit
int main() {
    char art[ROWS][COLS];
    // Checks if file was successfully loaded
    bool isLoaded = false;
    srand(time(NULL));  
    int choice;
    cout << "Welcome to the Spot the Difference Game" << endl;
    do {
        choice = mainMenu();
        switch (choice) {
            case 1:
                isLoaded = loadFile(art);
                break;
            case 2:
                if (!isLoaded) {
                    cout << "No file loaded." << endl;
                } else {
                    displayArt(art, isLoaded);
                }
                break;
            case 3:
                if (!isLoaded) {
                    cout << "No file loaded." << endl;
                } else {
                    playGame(art, isLoaded);
                }
                break;
            case 4:
                cout << "Thank you for playing the Spot The Difference Game" << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    // Loop repeats until the user chooses to exit     
    } while (choice != 4);
}