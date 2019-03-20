/***************************************************************************************************
 *
 * Author: Chip Brommer
 * Date: March 8, 2019
 * Contact: Fredrick.Brommer@usm.edu
 * Class: CSC 413 - Algorithms
 * Professor: Dr. Zhou
 *
 * Description: Create a program to implement a Binary Search Tree. You must implement all the
                following functions/ algorithms (in-order tree traversal, search for a particular
                key in a binary search tree, find the minimum and maximum, find the successor of
                a given node x [must test both the situations], insert a new key, delete a key
                [must test all the situations]) for binary search trees.  It is NOT allowed to use
                the binary tree data structure or algorithm built in your programming language, so
                you must implement your own algorithms.
 
 ***************************************************************************************************/

#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <algorithm>

#include "binarySearchFunctions.h"

using namespace std;

void welcomeMessage(fstream&);
void mainMenu(fstream&);
void mainMenuSwitch(int, fstream&);
void createMenu(fstream&);
void createMenuSwitch(fstream&, int);
void premadeMenu(fstream&);
void premadeSwitch(fstream&, int);
void randomGenerationMenu(fstream&);
void optionsMenu(fstream&, node&);
void optionsMenuSwitch(fstream&, node&, int);
void searchTree(fstream&, node&);
void searchAgain(fstream&, node&);
void insertValue(fstream&, node&);
void insertAgain(fstream&, node&);
void deleteValue(fstream&, node&);
void deleteAgain(fstream&, node&);
void successorFinder(fstream&, node&);
void predecessorFinder(fstream&, node&);
void useAgain(fstream&, node&);
bool integerVerify(int);
int integerSizeRestrictor(int);
int randomNumberGenerator();
void programEnd();

//Main menu
int main()
{
    //Time based random number generator for the program.
    //This is in main so it only gets called once and starts upon program run.
    srand((unsigned int) time(NULL));
    
    //Creating new txt file for console output
    fstream mytxtfile;
    mytxtfile.open("Project2 - Output.txt", fstream::out);
    
    //Calling the main welcome message
    welcomeMessage(mytxtfile);
    
    //Calling the main menu
    mainMenu(mytxtfile);
    
    //Calling the closing procedure for the program.
    programEnd();
    
    return 0;
}

//-------------------------------------------------------------------------------------------------
//welcomeMessage - This function holds the welcome message for the program and prints it to the
//                 console for the user.
//-------------------------------------------------------------------------------------------------
void welcomeMessage(fstream& mytxtfile)
{
    cout << "\t\t\t\t\tChips BST Project\n"
    << "\t\t------------------------------------------\n\n";
    mytxtfile << "\t\t\t\t\tChips BST Project\n"
    << "\t\t------------------------------------------\n\n";
}

//-------------------------------------------------------------------------------------------------
//mainMenu - This is the main menu for the project. Gives the user the option to input a tree,
//           select a pre-made tree, or create a tree from random generated numbers
//-------------------------------------------------------------------------------------------------
void mainMenu(fstream& mytxtfile)
{
    //Holds the users selection
    int userSelection = 0;
    
    //Displaying menu options
    cout << "Main Menu:" << endl;
    cout << "_______________________" << endl;
    cout << "  1: Create a tree from user input" << endl;
    cout << "  2: Use a pre-made tree" << endl;
    cout << "  3: Randomly generate a tree" << endl;
    cout << "  4: Exit" << endl;
    
    //Displaying menu options to the txt file
    mytxtfile << "Main Menu:" << endl;
    mytxtfile << "_______________________" << endl;
    mytxtfile << "  1: Create a tree from user input" << endl;
    mytxtfile << "  2: Use a pre-made tree" << endl;
    mytxtfile << "  3: Randomly generate a tree" << endl;
    mytxtfile << "  4: Exit" << endl;
    
    //Recieving the user selection
    cout << "\n\tYour Selection: ";
    cin >> userSelection;
    
    //Verifies input is an integer. IF NOT, requests new input
    while(!integerVerify(userSelection))
    {
        cout << "Please Enter a Selection: ";
        cin >> userSelection;
    }
    
    //Spacer Line
    cout << endl;
    
    //Displaying the user selection to the txt file
    mytxtfile << "\n\tYour Selection: " << userSelection << endl << endl;
    
    //Calling the main menu switch
    mainMenuSwitch(userSelection, mytxtfile);
}

//---------------------------------------------------------------------------------------
//mainMenuSwitch - This function uses a switch-case for the user entered selection
//                 in the main menu
//---------------------------------------------------------------------------------------
void mainMenuSwitch(int userSelection, fstream& mytxtfile)
{
    //Setting up the switch for the user selection
    switch (userSelection)
    {
        case 1://Enter an array
        {
            createMenu(mytxtfile);
            break;
        }
        case 2://Use a pre-made array
        {
            premadeMenu(mytxtfile);
            break;
        }
        case 3://Randomly Generate an array
        {
            randomGenerationMenu(mytxtfile);
            break;
        }
        case 4://Exit
        {
            //Does not call anything, just breaks out, and by order in the main, exits program
            break;
        }
        default://Invalid selection
        {
            cout << "\t::Invalid Selection::\n";
            mainMenu(mytxtfile);
            break;
        }
    }
}

//-------------------------------------------------------------------------------------------------
//createMenu - This allows the user to create a binary search tree from their desired number of
//              elements and then allows them to input the values for each element.
//-------------------------------------------------------------------------------------------------
void createMenu(fstream& mytxtfile)
{
    int elementChoice = 0;  //Holds the users choice for the number of elements
    
    //DIsplaying options to the user
    cout << "Number of Tree Elements Selection:" << endl;
    cout << "_______________________" << endl;
    cout << "  1: 10" << endl;
    cout << "  2: 11" << endl;
    cout << "  3: 12" << endl;
    cout << "  4: 15" << endl;
    cout << "  5: Exit to Main Menu" << endl;
    
    //DIsplaying options to the user
    mytxtfile << "Number of Tree Elements Selection:" << endl;
    mytxtfile << "_______________________" << endl;
    mytxtfile << "  1: 10" << endl;
    mytxtfile << "  2: 11" << endl;
    mytxtfile << "  3: 12" << endl;
    mytxtfile << "  4: 15" << endl;
    mytxtfile << "  5: Exit to Main Menu" << endl;
    
    cout << "\n\tYour Selection: ";
    cin >> elementChoice;
    
    //Verifies input is an integer. IF NOT, requests new input
    while(!integerVerify(elementChoice))
    {
        cout << "Please Enter a Selection: ";
        cin >> elementChoice;
    }
    
    //Displaying the user selection to the txt file
    mytxtfile << "\n\tYour Selection: " << elementChoice << endl;
    
    //Calling the switch
    createMenuSwitch(mytxtfile, elementChoice);
}

//---------------------------------------------------------------------------------------
//createMenuSwitch - This function uses a switch-case for the user entered selection
//                   in the number of elements function. The user enters values for the
//                   specified number of elements desired. The elements are then stored
//                   into an array that will be use
//---------------------------------------------------------------------------------------
void createMenuSwitch(fstream& mytxtfile, int elementChoice)
{
    int elementInput = 0;   //Holds the users input for the value to place in the array element
    int length = 0;         //Holds the length of the users choice for the array.
    
    node *root = NULL; //Creating the root node.
    
    //Setting up the switch for the user selection
    switch (elementChoice)
    {
        case 1://Length = 10
        {
            length = 10;
            
            cout << "\nPlease enter a value for each element between -100 to 100.\n";
            mytxtfile << "\nPlease enter a value for each element between -100 to 100.\n";
            cout << endl;   //Spacer line
            
            //For loop for user to fill the array elements.
            for (int i = 0; i < length; i++)
            {
                cout << "\tEnter a number for element " << i+1 << ": ";
                cin >> elementInput;
                
                //Verifies input is an integer. IF NOT, requests new input
                while(!integerVerify(elementInput))
                {
                    cout << "\tPlease Enter a number: ";
                    cin >> elementInput;
                }
                
                elementInput = integerSizeRestrictor(elementInput);
                
                //Checking to make sure the number is within size.
                //And then assigning it into the array
                if (i == 0)
                {
                    root = insertNode(root, elementInput);
                }
                else
                {
                    insertNode(root, elementInput);
                }
                
                //Displaying the user input to the txt file
                mytxtfile << "\tEnter a number for element " << i+1 << ": " << elementInput << endl;
            }
            
            //Calling the switch for how the user wants to solve
            optionsMenu(mytxtfile, *root);
            break;
        }
        case 2://Length = 11
        {
            length = 11;
            
            cout << "\nPlease enter a value for each element between -100 to 100.\n";
            mytxtfile << "\nPlease enter a value for each element between -100 to 100.\n";
            cout << endl;   //Spacer line
            
            //For loop for user to fill the array elements.
            for (int i = 0; i < length; i++)
            {
                cout << "\tEnter a number for element " << i+1 << ": ";
                cin >> elementInput;
                
                //Verifies input is an integer. IF NOT, requests new input
                while(!integerVerify(elementInput))
                {
                    cout << "\tPlease Enter a number: ";
                    cin >> elementInput;
                }
                
                elementInput = integerSizeRestrictor(elementInput);
                
                //Checking to make sure the number is within size.
                //And then assigning it into the array
                if (i == 0)
                {
                    root = insertNode(root, elementInput);
                }
                else
                {
                    insertNode(root, elementInput);
                }
                
                //Displaying the user input to the txt file
                mytxtfile << "\tEnter a number for element " << i+1 << ": " << elementInput << endl;
            }
            
            //Calling the switch for how the user wants to solve
            optionsMenu(mytxtfile, *root);
            break;
        }
        case 3://Length = 12
        {
            length = 12;
            
            cout << "\nPlease enter a value for each element between -100 to 100.\n";
            mytxtfile << "\nPlease enter a value for each element between -100 to 100.\n";
            cout << endl;   //Spacer line
            
            //For loop for user to fill the array elements.
            for (int i = 0; i < length; i++)
            {
                cout << "\tEnter a number for element " << i+1 << ": ";
                cin >> elementInput;
                
                //Verifies input is an integer. IF NOT, requests new input
                while(!integerVerify(elementInput))
                {
                    cout << "\tPlease Enter a number: ";
                    cin >> elementInput;
                }
                
                elementInput = integerSizeRestrictor(elementInput);
                
                //Checking to make sure the number is within size.
                //And then assigning it into the array
                if (i == 0)
                {
                    root = insertNode(root, elementInput);
                }
                else
                {
                    insertNode(root, elementInput);
                }
                
                //Displaying the user input to the txt file
                mytxtfile << "\tEnter a number for element " << i+1 << ": " << elementInput << endl;
            }
            
            //Calling the switch for how the user wants to solve
            optionsMenu(mytxtfile, *root);
            break;
        }
        case 4://Length = 15
        {
            length = 15;
            
            cout << "\nPlease enter a value for each element between -100 to 100.\n";
            mytxtfile << "\nPlease enter a value for each element between -100 to 100.\n";
            cout << endl;   //Spacer line
            
            //For loop for user to fill the array elements.
            for (int i = 0; i < length; i++)
            {
                cout << "\tEnter a number for element " << i+1 << ": ";
                cin >> elementInput;
                
                //Verifies input is an integer. IF NOT, requests new input
                while(!integerVerify(elementInput))
                {
                    cout << "\tPlease Enter a number: ";
                    cin >> elementInput;
                }
                
                elementInput = integerSizeRestrictor(elementInput);
                
                //Checking to make sure the number is within size.
                //And then assigning it into the array
                if (i == 0)
                {
                    root = insertNode(root, elementInput);
                }
                else
                {
                    insertNode(root, elementInput);
                }
                
                //Displaying the user input to the txt file
                mytxtfile << "\tEnter a number for element " << i+1 << ": " << elementInput << endl;
            }
            
            //Calling the switch for how the user wants to solve
            optionsMenu(mytxtfile, *root);
            break;
        }
        case 5://main Menu
        {
            mainMenu(mytxtfile);
            break;
        }
        default://Invalid selection
        {
            cout << "\t::Invalid Selection::\n\n";
            createMenu(mytxtfile);
            break;
        }
    }
}

//-------------------------------------------------------------------------------------------------
//premadeMenu - This is the a menu for the user to pick from some pre made values to use a binary
//              search on.
//-------------------------------------------------------------------------------------------------
void premadeMenu(fstream & mytxtfile)
{
    int premadeSelection = 0;
    
    //Displaying options to the user
    cout << "Premade Selections:" << endl;
    cout << "_______________________" << endl;
    cout << "  1: 15 6 18 3 7 17 20 2 4 13 9 " << endl;
    cout << "  2: 11 10 9 8 7 6 5 4 3 2 1 " << endl;
    cout << "  3: 11 7 4 9 2 8 1 7 6 15 12 3 13 14 5" << endl;
    cout << "  4: Exit to Main Menu" << endl;
    
    //Displaying options to the txt file
    
    mytxtfile << "Premade Selections:" << endl;
    mytxtfile << "_______________________" << endl;
    mytxtfile << "  1: 15 6 18 3 7 17 20 2 4 13 9 " << endl;
    mytxtfile << "  2: 11 10 9 8 7 6 5 4 3 2 1 " << endl;
    mytxtfile << "  3: 11 7 4 9 2 8 1 7 6 15 12 3 13 14 5" << endl;
    mytxtfile << "  4: Exit to Main Menu" << endl;
    
    cout << "\n\tYour Selection: ";
    cin >> premadeSelection;
    
    //Verifies input is an integer. IF NOT, requests new input
    while(!integerVerify(premadeSelection))
    {
        cout << "Please Enter a Selection: ";
        cin >> premadeSelection;
    }
    
    //Displaying the user selection to the txt file
    mytxtfile << "\n\tYour Selection: " << premadeSelection << endl << endl;
    
    premadeSwitch(mytxtfile, premadeSelection);
}

//-------------------------------------------------------------------------------------------------
//premadeSwitch - Called by the premade options menu, sets the users array and then calls the sortmenu
//-------------------------------------------------------------------------------------------------
void premadeSwitch(fstream & mytxtfile, int premadeSelection)
{
    node *root = NULL; //Creating the root node.
    
    //Setting up the switch for the user selection
    switch (premadeSelection)
    {
        case 1://15 6 18 3 7 17 20 2 4 13 9
        {
            //Inserting the values into the tree
            root = insertNode(root, 15);
            insertNode(root, 6);
            insertNode(root, 18);
            insertNode(root, 3);
            insertNode(root, 7);
            insertNode(root, 17);
            insertNode(root, 20);
            insertNode(root, 2);
            insertNode(root, 4);
            insertNode(root, 13);
            insertNode(root, 9);
            
            //Calling the binary search function
            optionsMenu(mytxtfile, *root);
            break;
        }
        case 2://11 10 9 8 7 6 5 4 3 2 1
        {
            //Inserting the values into the tree
            root = insertNode(root, 11);
            insertNode(root, 10);
            insertNode(root, 9);
            insertNode(root, 8);
            insertNode(root, 7);
            insertNode(root, 6);
            insertNode(root, 5);
            insertNode(root, 4);
            insertNode(root, 3);
            insertNode(root, 2);
            insertNode(root, 1);
            
            //Calling the binary search function
            optionsMenu(mytxtfile, *root);
            break;
        }
        case 3://11 7 4 9 2 8 1 7 6 15 12 3 13 14 5
        {
            //Inserting the values into the tree
            root = insertNode(root, 11);
            insertNode(root, 7);
            insertNode(root, 4);
            insertNode(root, 9);
            insertNode(root, 2);
            insertNode(root, 8);
            insertNode(root, 1);
            insertNode(root, 7);
            insertNode(root, 6);
            insertNode(root, 15);
            insertNode(root, 12);
            insertNode(root, 3);
            insertNode(root, 13);
            insertNode(root, 14);
            insertNode(root, 5);
            
            //Calling the binary search function
            optionsMenu(mytxtfile, *root);
            break;
        }
        case 4://Back to main
        {
            mainMenu(mytxtfile);
            break;
        }
        default://Invalid selection
        {
            cout << "\t::Invalid Selection::\n";
            premadeMenu(mytxtfile);
            break;
        }
    }
}

//-------------------------------------------------------------------------------------------------
//generationMenu - This is the menu option for the user to have an array filled with randomly
//                  generated numbers which then gets sent to the options menu
//-------------------------------------------------------------------------------------------------
void randomGenerationMenu(fstream & mytxtfile)
{
    node *root = NULL; //Creating the root node.
    int value = 0;
    
    cout << "Randomly generating and inserting 11 elements...\n";
    mytxtfile << "Randomly generating and inserting 11 elements...\n";
    
    //For loop to fill the array while calling the random number generator
    for(int x = 0; x < 11; x++)
    {
        //Setting value to the number from the random number generator
        value = randomNumberGenerator();
        
        if (x == 0)
        {
            root = insertNode(root, value);
        }
        else
        {
            insertNode(root, value);
        }
        
        cout << "Inserting value: " << value << endl;
    }
    
    //Calling the binary search
    optionsMenu(mytxtfile, *root);
}

//-------------------------------------------------------------------------------------------------
//optionsMenu - This is the menu that has all the options for what a user can search the numbers
//              for.
//-------------------------------------------------------------------------------------------------
void optionsMenu(fstream & mytxtfile, node& root)
{
    int sortSelection = 0;
    
    //Displaying options to the user
    cout << "\nOptions Menu:" << endl;
    cout << "_______________________" << endl;
    cout << "  1: In Order Tree Traversal" << endl;
    cout << "  2: Find The Minimum" << endl;
    cout << "  3: Find The Maximum" << endl;
    cout << "  4: Search for Particular Key" << endl;
    cout << "  5: Find successor of a node" << endl;
    cout << "  6: Find predecessor of a node" << endl;
    cout << "  7: Insert a New Key" << endl;
    cout << "  8: Delete a Key" << endl;
    cout << "  9: Exit to Main Menu" << endl << endl;
    
    //Displaying options to the user
    mytxtfile << "\nOptions Menu:" << endl;
    mytxtfile << "_______________________" << endl;
    mytxtfile << "  1: In Order Tree Traversal" << endl;
    mytxtfile << "  2: Find The Minimum" << endl;
    mytxtfile << "  3: Find The Maximum" << endl;
    mytxtfile << "  4: Search for Particular Key" << endl;
    mytxtfile << "  5: Find successor of a node" << endl;
    mytxtfile << "  6: Find predecessor of a node" << endl;
    mytxtfile << "  7: Insert a New Key" << endl;
    mytxtfile << "  8: Delete a Key" << endl;
    mytxtfile << "  9: Exit to Main Menu" << endl << endl;
    
    cout << "   Your Selection: ";
    cin >> sortSelection;
    
    //Verifies input is an integer. IF NOT, requests new input
    while(!integerVerify(sortSelection))
    {
        cout << "Please Enter a selection: ";
        cin >> sortSelection;
    }
    
    //Spacer Line
    cout << endl;
    
    //Displaying the user selection to the txt file
    mytxtfile << "\n\tYour Selection: " << sortSelection << endl << endl;
    
    optionsMenuSwitch(mytxtfile, root, sortSelection);
}

//---------------------------------------------------------------------------------------
//sortMenuSwitch - This function uses a switch-case for the user entered selection
//                 in the msort menu, distributes the user to the preferred sort algorithm
//---------------------------------------------------------------------------------------
void optionsMenuSwitch(fstream& mytxtfile, node& root, int sortSelection)
{
    //Setting up the switch for the user selection
    switch (sortSelection)
    {
        case 1://In Order Tree Traversal
        {
            treeTraversal(&root);
            useAgain(mytxtfile, root);  //Option to use same tree
            break;
        }
        case 2://Find the Minimum
        {
            int min = minimumValue(&root);
            cout << "The lowest value in the tree is " << min << "." << endl;
            mytxtfile << "The lowest value in the tree is " << min << "." << endl;
            useAgain(mytxtfile, root);  //Option to use same tree
            break;
        }
        case 3://Find The Maximum
        {
            int max = maximumValue(&root);
            cout << "The highest value in the tree is " << max << "." << endl;
            mytxtfile << "The highest value in the tree is " << max << "." << endl;
            useAgain(mytxtfile, root);  //Option to use same tree
            break;
        }
        case 4://Search for Particular Key
        {
            searchTree(mytxtfile, root);
            break;
        }
        case 5://Find successor of a key
        {
            successorFinder(mytxtfile, root);
            break;
        }
        case 6://Find predecessor of a key
        {
            predecessorFinder(mytxtfile, root);
            break;
        }
        case 7://Insert a New Key
        {
            insertValue(mytxtfile, root);
            break;
        }
        case 8://Delete a key
        {
            deleteValue(mytxtfile, root);
            break;
        }
        case 9://Back to main menu
        {
            mainMenu(mytxtfile);
            break;
        }
        default://Invalid selection
        {
            cout << "\t::Invalid Selection::\n";
            optionsMenu(mytxtfile, root);
            break;
        }
    }
}

//---------------------------------------------------------------------------------------
//insertValue - This function is called by the options menu when the user wants to insert
//              a new value into the tree. Ensures the entry is a numerical value between
//              -100 to 100.
//---------------------------------------------------------------------------------------
void insertValue(fstream& mytxtfile, node& root)
{
    int valueInput = 0; //Holds the number to be inserted.
    
    //Displaying the current tree
    cout << "Numbers in current tree: " << endl;
    mytxtfile << "Numbers in current tree: " << endl;
    standardPrint(&root, mytxtfile);
    
    cout << "\n\tEnter a number to be inserted: ";
    cin >> valueInput;
    
    //Verifies input is an integer. IF NOT, requests new input
    while(!integerVerify(valueInput))
    {
        cout << "\n\tEnter a number to be inserted: ";
        cin >> valueInput;
    }
    
    //This line verifies the value is within our paramaters.
    valueInput = integerSizeRestrictor(valueInput);
    
    //Checking to make sure the number is within size.
    //And then assigning it into the array
    insertNode(&root, valueInput);
    
    //Displaying the user input to the txt file
    mytxtfile << "\nValue to be inserted into tree" << ": " << valueInput << endl;
    
    //Displaing the updated tree
    cout << "\nNumbers in tree now: " << endl;
    mytxtfile << "\nNumbers in tree now: " << endl;
    standardPrint(&root, mytxtfile);
    cout << endl;
    mytxtfile << endl;
    
    insertAgain(mytxtfile, root);
}

//---------------------------------------------------------------------------------------
//insertAgain - Asks the user if they would like to delete another value from the tree.
//           If they want to, send user back to deleteValue function, else returns to
//           optionsMenu.
//---------------------------------------------------------------------------------------
void insertAgain(fstream& mytxtfile, node& root)
{
    char userSelection;
    
    cout << "Would you like to insert another value?\n";
    cout << "Enter Y for Yes, Else returns to options menu.\n";
    mytxtfile << "Would you like to insert another value?\n";
    mytxtfile << "Enter Y for Yes, Else returns to options menu.\n";
    cout << "\tUser Input: ";
    cin >> userSelection;
    
    //converts to char input to an upper character and compares it,
    //if the input was a 'Y' then sends back to the insertValue function
    if(toupper(userSelection) == 'Y')
    {
        cout << endl;
        mytxtfile << "\tUser Input: " << userSelection << endl << endl;
        insertValue(mytxtfile, root);
    }
    else //input was not a 'Y' , defaults back to main menu
    {
        cout << endl;
        mytxtfile << "\tUser Input: " << userSelection << endl << endl;
        useAgain(mytxtfile, root);
    }
}

//---------------------------------------------------------------------------------------
//deleteValue - This function is called by the options menu when the user wants to delete
//              a value in the tree
//---------------------------------------------------------------------------------------
void deleteValue(fstream& mytxtfile, node& root)
{
    int valueInput = 0;
    
    cout << "Numbers in current tree: " << endl;
    mytxtfile << "Numbers in current tree: " << endl;
    standardPrint(&root, mytxtfile);
    
    cout << "\n\tEnter number to be deleted: ";
    cin >> valueInput;
    
    //Verifies input is an integer. IF NOT, requests new input
    while(!integerVerify(valueInput))
    {
        cout << "\n\tEnter a Number to be deleted: ";
        cin >> valueInput;
    }
    
    //This line verifies the value is within our paramaters.
    valueInput = integerSizeRestrictor(valueInput);
    
    //Checking to make sure the number is within size.
    //And then assigning it into the array
    deleteNode(&root, valueInput);
    
    //Displaying the user input to the txt file
    mytxtfile << "\nValue to be deleted from tree" << ": " << valueInput << endl;
    
    cout << "\nNumbers in tree now: " << endl;
    mytxtfile << "\nNumbers in tree now: " << endl;
    standardPrint(&root, mytxtfile);
    cout << endl << endl;
    mytxtfile << endl << endl;
    
    deleteAgain(mytxtfile, root);
}

//---------------------------------------------------------------------------------------
//deleteAgain - Asks the user if they would like to delete another value from the tree.
//           If they want to, send user back to deleteValue function, else returns to
//           optionsMenu.
//---------------------------------------------------------------------------------------
void deleteAgain(fstream& mytxtfile, node& root)
{
    char userSelection;
    
    cout << "Would you like to delete another value?\n";
    cout << "Enter Y for Yes, Else returns to options menu.\n";
    mytxtfile << "Would you like to delete another value?\n";
    mytxtfile << "Enter Y for Yes, Else returns to options menu.\n";
    cout << "\tUser Input: ";
    cin >> userSelection;
    
    //converts to char input to an upper character and compares it,
    //if the input was a 'Y' then sends back to the sorting menu
    if(toupper(userSelection) == 'Y')
    {
        cout << endl;
        mytxtfile << "\tUser Input: " << userSelection << endl << endl;
        deleteValue(mytxtfile, root);
    }
    else //input was not a 'Y' , defaults to useAgain function
    {
        cout << endl;
        mytxtfile << "\tUser Input: " << userSelection << endl << endl;
        useAgain(mytxtfile, root);
    }
}

//---------------------------------------------------------------------------------------
//searchTree - This function will search the tree to find the specified key. If the number
//             exists, displays FOUND.
//---------------------------------------------------------------------------------------
void searchTree(fstream& mytxtfile, node& root)
{
    int inputNumber; //Variable to hold our user input.
    
    //recieving input from user on which number to search for. 
    cout << "Specify a number to search for: ";
    cin >> inputNumber;
    
    if(findNode(&root, inputNumber) == true) //Number is found.
    {
        cout << "\t-FOUND-" << endl;
    }
    else //Not Found
    {
        cout << "\t-NOT FOUND-" << endl;
    }
    
    //Asking the user if they would like to search another number.
    searchAgain(mytxtfile, root);
}

//---------------------------------------------------------------------------------------
//useAgain - Asks the use the same tree with a different option. If yes, send back to
//           options menu.
//---------------------------------------------------------------------------------------
void searchAgain(fstream& mytxtfile, node& root)
{
    char userSelection;     //Holds the user selection
    
    cout << "\nWould you like to search another number?\n";
    cout << "Enter Y for Yes, Else returns to options menu.\n";
    mytxtfile << "Would you like to search another number?\n";
    mytxtfile << "Enter Y for Yes, Else returns to options menu.\n";
    cout << "\tUser Input: ";
    cin >> userSelection;
    
    //converts to char input to an upper character and compares it,
    //if the input was a 'Y' then sends back to the sorting menu
    if(toupper(userSelection) == 'Y')
    {
        cout << endl;
        mytxtfile << "\tUser Input: " << userSelection << endl << endl;
        searchTree(mytxtfile, root);
    }
    else //input was not a 'Y' , defaults back to option menu
    {
        cout << endl;
        mytxtfile << "\tUser Input: " << userSelection << endl << endl;
        optionsMenu(mytxtfile, root);
    }
}

//---------------------------------------------------------------------------------------
//successorFinder - gets an input from the user, verifies it is in the tree. If it is in
//                  it calls the binary search function to find its successor.
//---------------------------------------------------------------------------------------
void successorFinder(fstream& mytxtfile, node& root)
{
    int userInput;
    
    cout << "Enter a number to find the successor of: ";
    mytxtfile << "Enter a number to find the successor of: ";
    cin >> userInput;
    cout << endl;
    
    //Verifies input is an integer. IF NOT, requests new input
    while(!integerVerify(userInput))
    {
        cout << "Enter a number: ";
        cin >> userInput;
    }
    
    //Spacer Line
    cout << endl;
    
    //Displaying the user selection to the txt file
    mytxtfile << "\n\tNumber entered: " << userInput << endl << endl;
    
    //Checking if the input number is in the tree, if not sends user back to options menu
    if(findNode(&root, userInput) == false)
    {
        cout << "Number specified is not in the tree.\n";
        mytxtfile << "Number specified is not in the tree.\n";
        optionsMenu(mytxtfile, root);
    }
    else
    {
        //Creating a node called temp that we will use to search for
        //It is created off the nodeSearch function that finds the node with the value speicified.
        node * temp = nodeSearch(&root, userInput);
        
        //Creating a node to store the successor.
        node * successor = findSuccessor(&root, temp);
        
        if(successor !=  NULL)
        {
            printf("\tSuccessor of %d is %d ", temp->key, successor->key);
            cout << endl;
            mytxtfile << "\tSuccessor of " <<  temp->key << " is " << successor->key << endl;
        }
        else
        {
            printf("\n\tSuccessor of %d doesn't exit", temp->key);
            cout << endl;
            mytxtfile << "\tSuccessor of " <<  temp->key << " doesn't exist.\n";
        }
    }
    
     useAgain(mytxtfile, root);
}

//---------------------------------------------------------------------------------------
//predecessorFinder - gets an input from the user, verifies it is in the tree. If it is in
//                  it calls the binary search function to find its successor.
//---------------------------------------------------------------------------------------
void predecessorFinder(fstream& mytxtfile, node& root)
{
    int userInput;
    
    cout << "Enter a number to find the predecessor of: ";
    mytxtfile << "Enter a number to find the predecessor of: ";
    cin >> userInput;
    cout << endl;
    
    //Verifies input is an integer. IF NOT, requests new input
    while(!integerVerify(userInput))
    {
        cout << "Enter a number: ";
        cin >> userInput;
    }
    
    //Displaying the user selection to the txt file
    mytxtfile << "\n\tNumber entered: " << userInput << endl << endl;
    
    //Checking if the input number is in the tree, if not sends user back to options menu
    if(findNode(&root, userInput) == false)
    {
        cout << "Number specified is not in the tree.\n";
        mytxtfile << "Number specified is not in the tree.\n";
        optionsMenu(mytxtfile, root);
    }
    else
    {
        //Creating a node called temp that we will use to search for
        //It is created off the nodeSearch function that finds the node with the value speicified.
        node * temp = nodeSearch(&root, userInput);
        
        //Creating a node to store the predecessor
        node * predecessor = findPredecessor(&root, temp);
        
        if(predecessor !=  NULL)
        {
            printf("\tPredecessor of %d is %d ", temp->key, predecessor->key);
            cout << endl;
            mytxtfile << "\tPredecessor of " <<  temp->key << " is " << predecessor->key << endl;
        }
        else
        {
            printf("\tPredecessor of %d doesn't exit", temp->key);
            cout << endl;
            mytxtfile << "\tPredecessor of " <<  temp->key << " doesn't exist.\n";
        }
    }
    
    useAgain(mytxtfile, root);
}


//---------------------------------------------------------------------------------------
//useAgain - Asks the use the same tree with a different option. If yes, send back to
//           options menu.
//---------------------------------------------------------------------------------------
void useAgain(fstream& mytxtfile, node& root)
{
    char userSelection;     //Holds the user selection
    
    cout << "\nWould you like to use the same tree for a different option?\n";
    cout << "Enter Y for Yes, Else returns to main menu.\n";
    mytxtfile << "Would you like to use the same tree for a different option?\n";
    mytxtfile << "Enter Y for Yes, Else returns to main menu.\n";
    cout << "\tUser Input: ";
    cin >> userSelection;
    
    //converts to char input to an upper character and compares it,
    //if the input was a 'Y' then sends back to the sorting menu
    if(toupper(userSelection) == 'Y')
    {
        cout << endl;
        mytxtfile << "\tUser Input: " << userSelection << endl << endl;
        optionsMenu(mytxtfile, root);
    }
    else //input was not a 'Y' , defaults back to main menu
    {
        cout << endl;
        mytxtfile << "\tUser Input: " << userSelection << endl << endl;
        mainMenu(mytxtfile);
    }
}

//---------------------------------------------------------------------------------------
//IntegerVerify - This function verifies
//---------------------------------------------------------------------------------------
bool integerVerify(int userInput)
{
    //This while loop ensures the user enters ONLY an integer. Anything else will
    //be kicked out.
    while(1)
    {
        if(cin.fail())
        {
            cin.clear();
            
            //If the input is not within numberic limits, throw error
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Please only enter a number.\n";
            return false;
        }
        if(!cin.fail())
            break;
    }
    
    return true;
}

//---------------------------------------------------------------------------------------
//integerSizeRestrictor - this function ensures that a number entered is within the bounds
//                        of -1000 - 1000.
//---------------------------------------------------------------------------------------
int integerSizeRestrictor(int numberEntered)
{
    while(numberEntered < -100 || numberEntered > 100)
    {
        cout << "\nThat number is out of bounds.";
        cout << "\nTry Again\n";
        cout << "\n\tNumber: ";
        cin >> numberEntered;
        cout << endl;
    }
    
    return numberEntered;
}

//-------------------------------------------------------------------------------------------------
//randomNumberGenerator - This function holds the random number generator for the array.
//-------------------------------------------------------------------------------------------------
int randomNumberGenerator()
{
    int randomNumber = 0;                       //Holds the random number
    
    randomNumber = rand() % (99 - 1) + 0;       //Generates random number between 0 and 99
    
    return randomNumber;                        //Returns the random number.
}

//-------------------------------------------------------------------------------------------------
//programEnd - Prompts the user to enter any key to close the program, then ends the program.
//-------------------------------------------------------------------------------------------------
void programEnd()
{
    cout << "\nPress any key to end...\n";
    cin.get();
}

