/*****************************************
** File:    Shop.h
** This file contains the ingredients and functions required to create a working shop
***********************************************/

#ifndef SHOP_H //Include/Header Guard
#define SHOP_H //Include/Header Guard

#include "Ingredient.h" //Include for the ingredient struct
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
using namespace std;

//Constants (Do not edit)
const int PROJ2_SIZE = 32;
const int RANK_D = 30;
const int RANK_C = 50;
const int RANK_B = 70;
const int RANK_A = 90;
const int RANK_S = 100;

// Class Declaration (Do not edit)
class Shop{
	public:
	// Name: Shop() - Default Constructor
	// Desc: Used to build a new Player Shop
	// Preconditions - Requires default values (Name = Test, numIngredients = 0, Rank = F
	// Postconditions - Creates a new Player Shop
	Shop();
	// Name: Shop(name) - Overloaded constructor
	// Desc - Used to build a new Player Shop (m_numIngredients = 0, m_shopRank = F)
	// Preconditions - Requires name
	// Postconditions - Creates a new Player Shop
	Shop(string name);
	// Name: GetName()
	// Desc - Getter for the Player Shop's name
	// Preconditions - Player Shop exists
	// Postconditions - Returns the name of the Player Shop
	string GetName();
	// Name: SetName(string)
	// Desc - Allows the user to change the name of the Player Shop
	// Preconditions - Player Shop exists
	// Postconditions - Sets name of Player Shop
	void SetName(string name);
	// Name: CheckIngredient(Ingredient)
	// Desc - Checks to see if the Shop has an ingredient
	// Preconditions - Shop already has ingredients
	// Postconditions - Returns index of ingredient if the Shop has it else -1
	int CheckIngredient(Ingredient);
	// Name: AddIngredient(string)
	// Desc - Inserts an ingredient into the Shop's list of ingredients.
	//        Increments m_numIngredients
	// Preconditions - Shop exists
	// Postconditions - Add an ingredient to the Shop's m_myIngredients with a quantity of 0
	void AddIngredient(Ingredient);
	// Name: IncrementQuantity(Ingredient)
	// Desc - Increases the quantity for an ingredient the Shop knows
	// Preconditions - Shop exists
	// Postconditions - Increases quantity of ingredient for the Shop
	void IncrementQuantity(Ingredient);
	// Name: DecrementQuantity(Ingredient)
	// Desc - Reduces quantity from the Shop's inventory with true, if no quantity false
	// Preconditions - A Shop exists
	// Postconditions - Reduces quantity of ingredient for the Shop
	bool DecrementQuantity(Ingredient);
	// Name: CheckQuantity(Ingredient)
	// Desc - Checks to see if quantity of two merge ingredients are available
	// Preconditions - Shop exists with ingredients
	// Postconditions - Returns true if both are available (including two of same ingredient)
	bool CheckQuantity(Ingredient, Ingredient);
	// Name: GetIngredient(int)
	// Desc - Checks to see if the Shop has any ingredients
	// Preconditions - The Shop already has ingredients
	// Postconditions - Returns ingredient at specific index
	Ingredient GetIngredient(int);
	// Name: CalcRank()
	// Desc - Divides the total available ingredients, by the IngredientCount()
	// Updates the rank based on percentages
	//      0-29 = F, 30-49 = D, 50-69 = C, 70-89 = B, 90-99 = A, 100 = S
	// Preconditions - Shop exists and has a rank
	// Postconditions - m_shopRank will be updated
	void CalcRank();
	// Name: GetRank()
	// Desc - Returns the current shop's rank
	// Preconditions - The shop exists
	// Postconditions - Returns the character indicating the rank of the shop
	char GetRank();
	// Name: IngredientCount()
	// Desc - Loops through m_myIngredients to see how many ingredients have a quantity > 0
	// Preconditions - The shop exists, m_myIngredients populated
	// Postconditions - Returns the count of ingredients with a quantity > 0
	int IngredientCount();
	// Name: ShopScore()
	// Desc - Displays information about the shop: name, ingredients found, total available,
	//        percentage found, and rank
	// Preconditions - The shop exists, m_myIngredients populated
	// Postconditions - Displays name, ingredient count, total ingredients, percentage, and rank
	void ShopScore();
	private:
	string m_shopName; //Name of the Shop
	char m_shopRank; // Rank of the Shop, can be (D, C, B, or A) (When 'S', game is over)
	int m_numIngredients; //Current number of items in m_myIngredients known to the Player Shop
	Ingredient m_myIngredients[PROJ2_SIZE] = {}; //List of ingredients known to this Shop
};

#endif //Exit Header Guard
