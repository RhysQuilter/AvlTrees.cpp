#include <iomanip>
#include <iostream>
#include <string>
#include "AVLTree.h"

using namespace std;

//this is initialising the keyboard input for the menu
const int Insert = 1;
const int PrintTree = 2;
const int PrintMenuSelection = 3;
const int Exit = 9;
const int SearchTree = 4;
const int DeleteNode = 5;
const int Clear = 6;

AvlTree<string> avl;


void PrintMenu();
int main();
void InitializeAvlTree();
void DeleteItem();
void TreeSearch();
void PrintAVLTree();
void InsertTree();
void InValidOption();
void ClearTree();

void PrintMenu() {
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n"; //adding new lines to place the menu in the center of the cmd promt
	cout << " \t\t\t\tType " << Insert << " Please insert an item into the AVL Tree." << endl;
	cout << " \t\t\t\tType " << PrintTree << " to print the inserted items into the AVL Tree." << endl;
	cout << " \t\t\t\tType " << PrintMenuSelection << " to Print the Menu to the screen." << endl;
	cout << " \t\t\t\tType " << SearchTree << " To search for an Item withen the AVL Tree." << endl;
	cout << " \t\t\t\tType " << DeleteNode << " To select the Item that you wish to delete" << endl;
	cout << " \t\t\t\tType " << Exit << " To Exit the program." << endl;
	cout << " \t\t\t\tType " << Clear << " To Clear the program." << endl;

} //end of menu
void InValidOption()//start of error handling  
{
	cout << " \n  *** Invalid option entered please enter a valid option to proceed *** \n " << endl;
	PrintMenu();//prints menu to screen if an invalid option is inserted
}

void ClearTree()
{
	avl.Clear();
	cout << " tree has been cleared.." << endl;
}


void InsertTree()//start of tree insert
{
	string item;
	do
	{
		cout << "\nPlease enter the names/items that you would wish to add: OR press '9' to cancel)\n";
		cin >> item;//taking user input from keyboard
		if (item != "9") // if statement to loop the promt to input name untill 9 is selected
		{
			cout << " \n  Names that have been added to tree... \n " << item << endl;
			avl.Insert(item);//inserting name 
			cout << "\n Item has been added\n ";
		}
	} while (item != "9");

}//end of tree insert


void PrintAVLTree()

{
	cout << "PrintAVLTree" << endl;
	cout << "AVL TREE";
	cout << avl.ToString();
}

void TreeSearch()
{
	string  item;
	do
	{
		cout << "\n Enter name that you wish to search OR press '9' to cancel\n";
		cin >> item;//taking user input from keyboard
		if (item != "9")// if statement to loop the promt to input name untill 9 is selected
		{
			cout << " Searching for " << item << " in tree " << endl; //searching to see if item in the avl tree exists..
			cout << avl.ToString();
			avl.Contains(item);
		}
	} while (item != "9");
}


void DeleteItem()
{
	string  item;
	do
	{
		cout << "\n please enter the item you want to delete OR press 9 to cancel \n";
		cin >> item;//taking user input from keyboard
		bool found = avl.Contains(item);//checking to see if item entered is contained in avl tree
		
		
		if ( found)//if statement runs if item is found
		{
			cout << "\n item now being deleted... \n" << item << endl;
			avl.Remove(item);//item gets deleted from tree
		}
		else// if(false)
		{
			cout << item << "\n could not delete item as item not found in the tree...\n " << endl;//if item is not in tree error message displays
		}

	 cout << avl.ToString() << endl;
	} while (item != "9");//keeps looping until 9 is selected.


}






void InitializeAvlTree()
{
	avl.Insert("Tom");
	avl.Insert("Ursula");
	avl.Insert("Mary");
	avl.Insert("Zaki");
	avl.Insert("Tim");
	avl.Insert("Amy");



}




int main()
{
	bool run = true;//while the program is true it will run
	int Selection = -1;

	PrintMenu();

	InitializeAvlTree();
	do
	{
		cout << "Enter Menu Selction (Type " << PrintMenuSelection << " to see menu options)" << endl;
		cin >> Selection;

		switch (Selection) // start of switch statement for the menu selection
		{
		case PrintTree:

			PrintAVLTree();
			break;

		case Insert:

			InsertTree();
			break;

		case PrintMenuSelection:

			PrintMenu();

		case SearchTree:

			TreeSearch();
			break;

		case DeleteNode:

			DeleteItem();
			break;

		case Clear:

			ClearTree();
			break;

		case Exit:
			run = false;
			break;
		default:
			InValidOption();
			break;
		}
	} while (run);
}
