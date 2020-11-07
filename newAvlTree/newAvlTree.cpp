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

AVLtree<string> avl;


void PrintMenu();
int main();
void InitializeAvlTree();
void DeleteItem();
void TreeSearch();
void PrintAVLTree();
void InsertTree();
void InValidOption();

void PrintMenu() {
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n"; //adding new lines to place the menu in the center of the cmd promt
	cout << " \t\t\t\tType" << Insert << " Please insert an item into the AVL Tree." << endl;
	cout << " \t\t\t\tType" << PrintTree << " to print the inserted items into the AVL Tree." << endl;
	cout << " \t\t\t\tType" << PrintMenuSelection << " to Print the Menu to the screen." << endl;
	cout << " \t\t\t\tType" << SearchTree << " To search for an Item withen the AVL Tree." << endl;
	cout << " \t\t\t\tType" << DeleteNode << " To select the Item that you wish to delete" << endl;
	cout << " \t\t\t\tType" << Exit << " To Exit the program." << endl;

} //end of menu
void InValidOption()//start of error handling  
{
	cout << " \n  *** Invalid option entered please enter a valid option to proceed *** \n " << endl;
	PrintMenu();//prints menu to screen if an invalid option is inserted
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
			avl.InsertItem(item);//inserting name 
			cout << "\n Item has been added\n ";
		}
	} while (item != "9");

}//end of tree insert

void PrintAVLTree()
{
	cout << "PrintAVLTree" << endl;
	cout << "AVL TREE";
	avl.PrintTree();
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
			avl.PrintTree();
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
		avl.Contains(item);//checking to see if item entered is contained in avl tree

		if (Located == true)//if statement runs if item is found
		{
			cout << "\n item now being deleted... \n" << item << endl;
			avl.DeleteItem(item);//item gets deleted from tree
		}
		else if (Located == false)
		{
			cout << item << "\n could not delete item as item not found in the tree...\n " << endl;//if item is not in tree error message displays
		}

		avl.PrintTree();
	} while (item != "9");//keeps looping until 9 is selected.


}






void InitializeAvlTree()
{
	avl.InsertItem("Tom");
	avl.InsertItem("Ursula");
	avl.InsertItem("Mary");
	avl.InsertItem("Zaki");
	avl.InsertItem("Tim");
	avl.InsertItem("Amy");



}




int main()
{
	bool run = true;//while the program is true it will run
	int Selection = -1;

	PrintMenu();

	InitializeAvlTree();
	do
	{
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

		case Exit:
			run = false;
			break;
		default:
			InValidOption();
			break;
		}
	} while (run);
}
