/*****************************************
** File:    Game.h
** This file contains the ingredients and shop.h file and uses it to create a game
***********************************************/

#ifndef GAME_H //Header Guard
#define GAME_H //Header Guard
#include <fstream>
#include <iostream>
#include <string>
#include "Ingredient.h"
#include "Shop.h"

using namespace std;

//Constants (Do not edit)
const string DATA = "potion.txt"; //File constant

//No additional variables or functions allowed
class Game{
	public:
	// Name - Game() Default Constructor
	// Desc - Does nothing explicitly
	// Preconditions - None
	// Postconditions - None
	Game(); //Default Constructor
	// Name - LoadIngredients
	// Desc - Loads each ingredient into m_ingredients from file.
	//        Ingredient names can have spaces (check proj doc for delimiter help)
	// Preconditions - Requires file with valid ingredient data
	// Postconditions - m_ingredient is populated with ingredient structs
	void LoadIngredients();
	// Name - StartGame()
	// Desc - Calls GameTitle then loads the file by calling LoadIngredients
	//        Manages the game itself continually calling the main menu until the main menu
	//        returns 5 (quit)
	// Preconditions - Player is placed in game
	// Postconditions - Continually checks to see if player has entered 5
	void StartGame();
	// Name: DisplayMyIngredients()
	// Desc - Displays the Shop's ingredients (Uses GetIngredient)
	// Preconditions - Player's Shop has ingredients
	// Postconditions - Displays a numbered list of ingredients
	void DisplayIngredients();
	// Name: MainMenu()
	// Desc - Displays and manages menu. Also checks win condition (Shop reaches S rank).
	// Preconditions - Player has a Shop
	// Postconditions - Returns number including exit
	int MainMenu();
	// Name: SearchIngredients()
	// Desc - Attempts to search for natural ingredients (must be type "natural")
	// Preconditions - Natural ingredients loaded
	// Postconditions - Increases quantity in Shop's possession of ingredients
	void SearchIngredients();
	// Name: CombineIngredients()
	// Desc - Attempts to combine known ingredients. If combined, quantity of ingredient decreased
	// Preconditions - Shop is populated with ingredients
	// Postconditions - Increments quantity of item "made", decreases quantity of source items
	void CombineIngredients();
	// Name: RequestIngredient()
	// Desc - Requests ingredient to use to merge
	// Preconditions - Shop has ingredients to try and merge
	// Postconditions - Returns integer of item selected by user
	void RequestIngredient(int &choice);
	// Name: SearchRecipes()
	// Desc - Searches recipes for two strings (name of item)
	// Preconditions - m_ingredients is populated
	// Postconditions - Returns int index of matching recipe
	int SearchRecipes(string, string);
	// Name: GameTitle()
	// Desc - Title for Game (Do not edit)
	// Do NOT copy to Game.cpp (use this version)
	// Preconditions - None
	// Postconditions - None
	void GameTitle(){
		cout << "PPPP  OO  TTTTT III  OO  N   N CCCC RRR   AA  FFFF TTTTT" << endl;
		cout << "P  P O  O   T    I  O  O NN  N C    R  R A  A F      T  " << endl;
		cout << "PPPP O  O   T    I  O  O N N N C    RRR  AAAA FFFF   T  " << endl;
		cout << "P    O  O   T    I  O  O N  NN C    R R  A  A F      T  " << endl;
		cout << "P     OO    T   III  OO  N   N CCCC R  R A  A F      T  " << endl;
	}
	private:
	Shop m_myShop; //Player's Shop for the game
	// need to load the ingredients into that array
	Ingredient m_ingredients[PROJ2_SIZE]; //All ingredients in the game (loaded from file)
};

#endif //Exit Header Guard
