#include "hero_tree.h"
using namespace std;


// Colton Vitkoczy
// CS163-009 Karla Fant

// function that allows the client to test the bounary conditiong of the binary tree.
// Option 1 prints the entire binary tree, option 2 allows the user to enter information into the
// tree, it starts by entering a while loop that allows the user to enter information about
// the hero, it then creates an entry and adds it into the tree, option 3 allows the user to 
// search for a heros name and display those heroes, and option 4 allows for the user to remove a 
// hero.

int client_option(int selection, tree & my_list, hero_log & to_add)
{

	char response = 'Y';
	char name[50]; 
	char power[75]; 
	char species[75]; 
	char bio[500];
	
	if (selection == 1)
	{
		my_list.display_all();
	}	
	if (selection == 2)
	{
		while(toupper(response) == 'Y')
		{
			cout<< "enter a hero name: " << endl;
			cin.get(name, 50, '\n');
			cin.ignore(100, '\n');
		 
			cout<< "enter their super power: " << endl;
			cin.get(power, 75, '\n');
			cin.ignore(100, '\n');

			cout<< "enter a species type " << endl;
			cin.get(species, 75, '\n');
			cin.ignore(100, '\n');

			cout<< "enter a bio: " << endl;
			cin.get(bio, 500, '\n');
			cin.ignore(500, '\n');
			
			to_add.create_entry(name, power, species, bio);
			my_list.insert(to_add);
			
			cout << "Would you like to enter another? " ;
			cin >> response;
			cin.ignore(100, '\n');
		}
	}

	if (selection == 3)
	{
		char * search = NULL;
		char temp_name[50];
		
		cout << "Please enter a hero's name to search for :" ; 
		cin.get(temp_name, 50, '\n');
		cin.ignore(100, '\n');
		
		search = new char[strlen(temp_name)+1];
		strcpy(search, temp_name); 
		
		if(!my_list.display(search))
			cout << "This hero is not in the log: ";
		delete [] search;
	}

	if(selection == 4)
	{
		cout << "Please enter a heros name to remove: " ;
		cin.get(name, 50, '\n');
		cin.ignore(100, '\n');

		my_list.remove_name(name);
	}
	
	if (selection == 5)
	{
		char * search = NULL;
		char temp_name[50];
		
		cout << "Please enter a power to search for :" ; 
		cin.get(temp_name, 50, '\n');
		cin.ignore(100, '\n');
		
		search = new char[strlen(temp_name)+1];
		strcpy(search, temp_name); 
		
		if(!my_list.display(search))
			cout << "There is no such power : ";
	}
	
	return 0;
}

