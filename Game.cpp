/*****************************************
** File:    Game.cpp
** This file contains the Header files for the project.
** consists of functions that mainly searches for ingredients and
** combine them
***********************************************/
#include "Game.h"

// Name - Game() Default Constructor
// Desc - Does nothing explicitly
// Preconditions - None
// Postconditions - None
Game::Game(){}

// Name - LoadIngredients
// Desc - Loads each ingredient into m_ingredients from file.
//        Ingredient names can have spaces (check proj doc for delimiter help)
// Preconditions - Requires file with valid ingredient data
// Postconditions - m_ingredient is populated with ingredient structs
void Game::LoadIngredients(){
	ifstream file(DATA);
	int counter = 0;
	if (!file.is_open()){
		cout << "File is not opened" << endl;
	} else{
		while (PROJ2_SIZE != counter){
		  m_ingredients[counter] = Ingredient();
			getline(file, m_ingredients[counter].m_name, ',');
			getline(file, m_ingredients[counter].m_type, ',');
			getline(file, m_ingredients[counter].m_ingredient1, ',');
			getline(file, m_ingredients[counter].m_ingredient2);
			m_ingredients[counter].m_quantity = 0;
			counter++;
		}
	}
}

// Name - StartGame()
// Desc - Calls GameTitle then loads the file by calling LoadIngredients
//        Manages the game itself continually calling the main menu until the main menu
//        returns 5 (quit)
// Preconditions - Player is placed in game
// Postconditions - Continually checks to see if player has entered 5
void Game::StartGame(){
	const int FIFTH_CHOICE = 5, FIRST_CHOICE = 1, SECOND_CHOICE = 2, THIRD_CHOICE = 3, FOURTH_CHOICE = 4;
	GameTitle();
	cout << "What is the name of your shop? " << endl;
	string name;
	getline(cin, name);
	m_myShop.SetName(name);
	// loads the ingredients into the m_ingredients array
	LoadIngredients();
	// add the ingredient loaded into the shop array
	for(int i = 0; i < PROJ2_SIZE; i++){
		m_myShop.AddIngredient(m_ingredients[i]);
	}
	int choice = MainMenu();
	// breaks out of the loop if user inputs 5, or they reach rank S
	while((choice != FIFTH_CHOICE) and m_myShop.GetRank() != 'S'){
		switch (choice) {
			case FIRST_CHOICE:
				DisplayIngredients();
				break;
			case SECOND_CHOICE:
				SearchIngredients();
				break;
			case THIRD_CHOICE:
				CombineIngredients();
				break;
			case FOURTH_CHOICE:
				m_myShop.ShopScore();
				break;
			default:;
		}
		if (m_myShop.GetRank() != 'S'){
			choice = MainMenu();
		} else if (m_myShop.GetRank() == 'S'){
			cout << "You found all ingredient in shop.\n";
		}
		
	}
	cout << "Thanks for playing UMBC Potion Craft\n";
}

// Name: DisplayMyIngredients()
// Desc - Displays the Shop's ingredients (Uses GetIngredient)
// Preconditions - Player's Shop has ingredients
// Postconditions - Displays a numbered list of ingredients
void Game::DisplayIngredients(){
	for(int i = 0; i < PROJ2_SIZE; i++){
		cout << i + 1 << "." << '\t' << m_myShop.GetIngredient(i).m_name << " " << m_myShop.GetIngredient(i).m_quantity;
		cout << endl;
	}
	cout << endl;
}

// Name: MainMenu()
// Desc - Displays and manages menu. Also checks win condition (Shop reaches S rank).
// Preconditions - Player has a Shop
// Postconditions - Returns number including exit
int Game::MainMenu(){
	int userInput;
	cout << "What would you like to do in " << m_myShop.GetName() << "'s shop?" << endl;
	cout << "1. Display your Shop's Ingredients\n" << "2. Search for Natural Ingredients\n"
		<<"3. Attempt to Merge Ingredients\n" << "4. See scores \n" << "5. Quit \n";
	cin >> userInput;
	return userInput;
}

// Name: SearchIngredients()
// Desc - Attempts to search for natural ingredients (must be type "natural")
// Preconditions - Natural ingredients loaded
// Postconditions - Increases quantity in Shop's possession of ingredients
void Game::SearchIngredients(){
	// need a random number between 0 and 31
	int randomIndex = 0 + (rand() % (PROJ2_SIZE - 1));
	bool keepSearching = true;
	// get ingredient return an ingredient from my shop, takes in an integer
	while (keepSearching){
		//checks if ingredient found is natural
		if(m_myShop.GetIngredient(randomIndex).m_type == "natural"){
			// increments ingredient, increment quantity takes in an ingredient
			m_myShop.IncrementQuantity(m_myShop.GetIngredient(randomIndex));
			keepSearching = false;
		} else{
			randomIndex = 0 + (rand() % (PROJ2_SIZE - 1));
		}
	}
	cout << m_myShop.GetIngredient(randomIndex).m_name << " found" << endl << endl;
}

// Name: CombineIngredients()
// Desc - Attempts to combine known ingredients. If combined, quantity of ingredient decreased
// Preconditions - Shop is populated with ingredients
// Postconditions - Increments quantity of item "made", decreases quantity of source items
void Game::CombineIngredients(){
	int choice1 = 0, choice2 = 0, recipeFound = 0;
	string recipeName;
	// updates choice1 and choice2 with input made
	RequestIngredient(choice1);
	RequestIngredient(choice2);
	
	// decrease 1 for indexing, for example if user input 1, then that means ingredient @ index 0
	choice1 -= 1;
	choice2 -= 1;
	
	// assign ingredient1 and ingredient2 to the name of that ingredient @ that index
	string ingredient1 = m_myShop.GetIngredient(choice1).m_name, ingredient2 = m_myShop.GetIngredient(choice2).m_name;
	
	// assign quantity of each ingredient to its corresponding ingredient
	int quantity1 = m_myShop.GetIngredient(choice1).m_quantity, quantity2 = m_myShop.GetIngredient(choice2).m_quantity;
	
	// checks if there's at least 1 quantity of each ingredient passed in, returns true if there is
	if (m_myShop.CheckQuantity(m_myShop.GetIngredient(choice1), m_myShop.GetIngredient(choice2))) {
		recipeFound = SearchRecipes(ingredient1, ingredient2);
		if (recipeFound != -1){
		  recipeName = m_myShop.GetIngredient(recipeFound).m_name;
		}
		
		// only check for quantities if a matching recipe is found
		if (recipeFound != -1){
			// checks if they are the same and there's at least 2 quantity  of the ingredient
			if (ingredient1 == ingredient2) {
				m_myShop.IncrementQuantity(m_myShop.GetIngredient(recipeFound));
				m_myShop.DecrementQuantity(m_myShop.GetIngredient(choice1));
				m_myShop.DecrementQuantity(m_myShop.GetIngredient(choice1));
				// display ingredients made
				cout << ingredient1 << " combined with " << ingredient2 << " to make " << recipeName << endl;
				cout << "You have made " << recipeName << " for your shop\n";
				// checks if they aren't the same but there is at least one of each
			} else if (ingredient1 != ingredient2) {
				m_myShop.IncrementQuantity(m_myShop.GetIngredient(recipeFound));
				m_myShop.DecrementQuantity(m_myShop.GetIngredient(choice1));
				m_myShop.DecrementQuantity(m_myShop.GetIngredient(choice2));
				// display ingredients made
				cout << ingredient1 << " combined with " << ingredient2 << " to make " << recipeName << endl;
				cout << "You have made " << recipeName << " for your shop\n";
			} else{
			  cout << "Error";
			}
		}
		else{
		  cout << "That Recipe does not exist" << endl;
		}
	} // checks if they aren't the same and none of each ingredient is available
	else if ((ingredient1 != ingredient2 and ((quantity1 == 0) and (quantity2 == 0)))) {
		cout << "You do not have enough " << ingredient1 << " or " << ingredient2 << " to attempt that merge\n";
		// checks if they aren't the same but the first ingredient isn't available
	} else if ((ingredient1 != ingredient2) and (quantity1 == 0)){
		cout << "You do not have enough " << ingredient1 << " to attempt that merge\n";
		// checks if they aren't the same but the second ingredient isn't available
	} else if ((ingredient1 != ingredient2) and (quantity2 == 0)) {
		cout << "You do not have enough " << ingredient2 << " to attempt that merge\n";
		// checks if they are the same but at least two isn't available
	} else if ((ingredient1 == ingredient2) and (quantity1 < 2)){
		cout << "You do not have enough " << ingredient1  << " to attempt that merge\n";
	} else{
		cout << "That ingredient doesnt exist";
	}
	cout << endl;
}

// Name: RequestIngredient()
// Desc - Requests ingredient to use to merge
// Preconditions - Shop has ingredients to try and merge
// Postconditions - Returns integer of item selected by user
void Game::RequestIngredient(int &choice){
	cout << "Which ingredients would you like to merge: \n" << "To list known ingredients enter -1: \n";
	cin >> choice;
	if (choice == -1){
		DisplayIngredients();
	}
	// checks if choice is between 0 and 32
	while (((choice <= 0) || (choice > PROJ2_SIZE))){
		if (choice == -1){
			cout << "Which ingredients would you like to merge: \n" << "To list known ingredients enter -1: \n";
			cin >> choice;
		} else{
			cout << "Try again, enter an ingredient in the range of 0 and " << PROJ2_SIZE << endl;
			cin >> choice;
		}
	}
}

// Name: SearchRecipes()
// Desc - Searches recipes for two strings (name of item)
// Preconditions - m_ingredients is populated
// Postconditions - Returns int index of matching recipe
int Game::SearchRecipes(string name1, string name2){
	bool found = false;
	//loop through array and find index of recipe that matches the ingredient provided
	for (int i = 0; i < PROJ2_SIZE; i++){
		if ((m_myShop.GetIngredient(i).m_ingredient1 == name1 and m_myShop.GetIngredient(i).m_ingredient2 == name2)||
			(m_myShop.GetIngredient(i).m_ingredient1 == name2 and m_myShop.GetIngredient(i).m_ingredient2 == name1)){
			return i;
		} else {found = true;}
	}
	if (found){
		cout << "Nothing happened when you tried to combine " << name1 << " and " << name2 << endl;
	}
	return -1;
}
