/*****************************************
** File:    Shop.cpp
** This file contains the Header files for the project.
** consists of functions that help set up the shop, also prints out the rank
**
**
***********************************************/
#include "Shop.h"

// Name: Shop() - Default Constructor
// Desc: Used to build a new Player Shop
// Preconditions - Requires default values (Name = Test, numIngredients = 0, Rank = F
// Postconditions - Creates a new Player Shop
Shop::Shop(){
	m_shopName = "Test";
	m_numIngredients = 0;
	m_shopRank = 'F';
}

// Name: Shop(name) - Overloaded constructor
// Desc - Used to build a new Player Shop (m_numIngredients = 0, m_shopRank = F)
// Preconditions - Requires name
// Postconditions - Creates a new Player Shop
Shop::Shop(string name){
	GetName();
	m_numIngredients = 0;
	m_shopRank = 'F';
}

// Name: GetName()
// Desc - Getter for the Player Shop's name1
// Preconditions - Player Shop exists
// Postconditions - Returns the name of the Player Shop
string Shop::GetName(){
	return m_shopName;
}

// Name: SetName(string)
// Desc - Allows the user to change the name of the Player Shop
// Preconditions - Player Shop exists
// Postconditions - Sets name of Player Shop
void Shop::SetName(string name){
	m_shopName = name;
}

// Name: CheckIngredient(Ingredient)
// Desc - Checks to see if the Shop has an ingredient
// Preconditions - Shop already has ingredients
// Postconditions - Returns index of ingredient if the Shop has it else -1

int Shop::CheckIngredient(Ingredient ingredient){
	// check if ingredient passed in to the function is in shop ingredients
	for (int i = 0; i < PROJ2_SIZE; i++){
		if((m_myIngredients[i].m_name == ingredient.m_name) and m_myIngredients[i].m_quantity > 0){
			return i;
		}
	}
	return -1;
}

// Name: AddIngredient(string)
// Desc - Inserts an ingredient into the Shop's list of ingredients.
//        Increments m_numIngredients
// Preconditions - Shop exists
// Postconditions - Add an ingredient to the Shop's m_myIngredients with a quantity of 0

void Shop::AddIngredient(Ingredient ingredient){
	// if store doesn't have the ingredient, add ingredient to the shop ingredient
	m_myIngredients[m_numIngredients] = ingredient;
	m_numIngredients += 1;
}

// Name: IncrementQuantity(Ingredient)
// Desc - Increases the quantity for an ingredient the Shop knows
// Preconditions - Shop exists
// Postconditions - Increases quantity of ingredient for the Shop
void Shop::IncrementQuantity(Ingredient ingredient){
	// increment ingredient when called
	for (int i = 0; i < PROJ2_SIZE; i++) {
		if (m_myIngredients[i].m_name == ingredient.m_name) {
			m_myIngredients[i].m_quantity += 1;
		}
	}

}

// Name: DecrementQuantity(Ingredient)
// Desc - Reduces quantity from the Shop's inventory with true, if no quantity false
// Preconditions - A Shop exists
// Postconditions - Reduces quantity of ingredient for the Shop
bool Shop::DecrementQuantity(Ingredient ingredient) {
	// reduce quantity of ingredient passed in when called
	for (int i = 0; i < PROJ2_SIZE; i++) {
		if ((m_myIngredients[i].m_name == ingredient.m_name) and (m_myIngredients[i].m_quantity > 0)) {
			m_myIngredients[i].m_quantity -= 1;
			return true;
		}
	}
	return false;
}

// Name: CheckQuantity(Ingredient)
// Desc - Checks to see if quantity of two merge ingredients are available
// Preconditions - Shop exists with ingredients
// Postconditions - Returns true if both are available (including two of same ingredient)
bool Shop::CheckQuantity(Ingredient ingredient1, Ingredient ingredient2){
	const int QUANTITY_TWO = 2;
	// check ingredient return index of ingredient if its available else returns -1
	int ind1 = CheckIngredient(ingredient1);
	int ind2 = CheckIngredient(ingredient2);
	// checks if at least one isn't available
	if (ind1 == -1 || ind2 == -1) { return false;}
	// checks if they are the same then we need @ least 2 of the ingredient, OR
	// if they are not the same then we need @ least 1 of each
	else if (((ind1 == ind2) and (m_myIngredients[ind1].m_quantity >= QUANTITY_TWO)) ||
			((ind1 != ind2) and (m_myIngredients[ind1].m_quantity >= 1) and (m_myIngredients[ind2].m_quantity >= 1))) {
		return true;
	}
	return false;
}

// Name: GetIngredient(int)
// Desc - Checks to see if the Shop has any ingredients
// Preconditions - The Shop already has ingredients
// Postconditions - Returns ingredient at specific index
Ingredient Shop::GetIngredient(int i){
  return m_myIngredients[i];
}

// Name: CalcRank()
// Desc - Divides the total available ingredients, by the IngredientCount()
// Updates the rank based on percentages
//      0-29 = F, 30-49 = D, 50-69 = C, 70-89 = B, 90-99 = A, 100 = S
// Preconditions - Shop exists and has a rank
// Postconditions - m_shopRank will be updated
void Shop::CalcRank(){
	const int PERCENT = 100;
	double rank = (double(IngredientCount()) / PROJ2_SIZE) * PERCENT;
	if (rank < RANK_D){ m_shopRank = 'F';}
	else if (rank < RANK_C){m_shopRank = 'D';}
	else if (rank < RANK_B) {m_shopRank = 'C';}
	else if (rank < RANK_A) {m_shopRank = 'B';}
	else if (rank < RANK_S) {m_shopRank = 'A';}
	else if (rank == RANK_S) {m_shopRank = 'S';}
}

// Name: GetRank()
// Desc - Returns the current shop's rank
// Preconditions - The shop exists
// Postconditions - Returns the character indicating the rank of the shop
char Shop::GetRank(){
	// calls calc rank and find out the current rank when the user calls the GetRank function
	CalcRank();
	return m_shopRank;
}

// Name: IngredientCount()
// Desc - Loops through m_myIngredients to see how many ingredients have a quantity > 0
// Preconditions - The shop exists, m_myIngredients populated
// Postconditions - Returns the count of ingredients with a quantity > 0
int Shop::IngredientCount(){
	// counts the number of ingredient found whenever the function is called
	int count = 0;
	for (int i = 0; i < PROJ2_SIZE; i++){
		if (m_myIngredients[i].m_quantity > 0){
			count ++;
		}
	}
	return count;
}

// Name: ShopScore()
// Desc - Displays information about the shop: name, ingredients found, total available,
//        percentage found, and rank
// Preconditions - The shop exists, m_myIngredients populated
// Postconditions - Displays name, ingredient count, total ingredients, percentage, and rank
void Shop::ShopScore(){
	const int PERCENT = 100, PRECISION_TWO = 2;
	cout << "*** The Potion Shop ***" << endl;
	cout << "Owned by: " << GetName() << endl;
	cout << "There are " << PROJ2_SIZE << " available products." << endl;
	double numAvailable = IngredientCount();
	cout << "This shop has " << numAvailable << " products in stock." << endl;
	cout.precision(PRECISION_TWO);
	cout << "which is " << fixed << ((numAvailable / PROJ2_SIZE) * PERCENT) << "%" << endl;
	cout << "Shop Rank: " << GetRank() << endl << endl;
}
