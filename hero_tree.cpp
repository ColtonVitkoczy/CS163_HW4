#include "hero_tree.h"


// Colton Vitkoczy
// CS163-009 Karla Fant

// The purpose of this file is to build the tree functions given in the hero_hash.h file
// First, it has a constructor and destructor. After this there's a fucntion that 
// allows the user to retrieve from tree by checking whether or not there's a match or the 
// match is greater than 0. Next, there is an insert function that allows the user to
// recursively inserts into the tree by creating a new node and inserting if empty, or
// adds to the left if the match compare is less than 0 and adds if the match compare is greater than 0.
// Next, we load in the hero text just as in program #3. After this we count the matches in the tree 
// and display all the matches of a name passed in. Finally, there is a function to remove an entry from the
// tree.

 
// Constructor
tree::tree()
{
	root = NULL;
}
//destructor
tree::~tree()
{
	destroy(root);
}
// destroys the tree
int tree::destroy(node * &root)
{
	if(!root) return 0;

	destroy(root->left);
	destroy(root->right);

	delete root;
	root = NULL;
	return 1;
}

// function that retrieves from the tree
int tree::retrieve(char * search, hero_log * array, node * root)
{
	if (!root) return 0;

	if (!root->entry.match_name(search))
	{
		array->copy_entry(root->entry);
		retrieve(search, array+1, root->right);
	}
	
	if (root->entry.match_name(search) > 0)
		retrieve(search, array, root->left);	

	else
		retrieve(search, array, root->left);
	return 1;
}

int tree::insert(hero_log & to_add)
{
	return insert(root, to_add);
}

// Function to insert into the hash table 
int tree::insert(node * & root, hero_log & to_add)
{
	if(!root)
	{
		root = new node;
		root->entry.copy_entry(to_add);
		root->right = root->left = NULL;
		return 0;
	}

	if (root->entry.compare_name(to_add) < 0)
		insert(root->left, to_add);
	else 
		insert(root->right, to_add);
	return 1;
}



// function that loads in information from a external data file
int tree::load(const char filename[])
{
/*
	hero_log to_add;//Used to copy information into the hash table
	table my_list;
	
	char name[50]; 
	char power[75]; 
	char species[75]; 
	char bio[500];
*/
	temp info;
	hero_log to_add;

	std::ifstream file_in;

	file_in.open(filename);
	if (file_in.is_open())
	{
		file_in.get(info.name, 50, '|'); 
		file_in.ignore(50, '|');
		
		while (!file_in.eof())
		{
			file_in.get(info.power, 75, '|'); 
			file_in.ignore(100, '|');
			
			file_in.get(info.species, 75, '|'); 
			file_in.ignore(100, '|');
			
			file_in.get(info.bio, 500, '\n'); 
			file_in.ignore(500, '\n');
		    
			to_add.create_entry(info.name, info.power, info.species, info.bio);
			insert(to_add);
			
			file_in.get(info.name, 50, '|'); 
			file_in.ignore(100, '|');
		}
		file_in.close();
	}
	return 1;
}
// function to count the number of matches in the data
int tree::count(char * search, node * root)
{
	if(!root) return 0;

	if(!root->entry.match_name(search))
		return 1 + count(search, root->right);
	return count(search, root->left) + count(search, root->right);
}
// displays the name of a specific hero
int tree::display(char * search)
{
	int size = count(search, root);

	if (!size) return 0;

	hero_log * collecting_heros = new hero_log[size];
	retrieve(search, collecting_heros, root);

	for (int i = 0; i < size ; ++i)
		collecting_heros[i].display();
	return 1;
} 
// displays all
int tree::display_all()
{
	return display_all(root);
}	
// recursive display all
int tree::display_all(node * root)
{
	if (!root) return 0;
	
	root->entry.display();
	display_all(root->left);
	display_all(root->right);
	return 1;
}
// remove name
int tree::remove_name(char * search)
{
	return remove_name(search, root);
}
// recursive remove name
int tree::remove_name(char * search, node * & root)
{
	if (!root) return 0;

	if (root->entry.match_name(search) > 0)
		return remove_name(search, root->right);

	if (root->entry.match_name(search) < 0)
		return remove_name(search, root->left);

	else
	{
		if(!root->left && !root->right)
		{
			delete root;
			root = NULL;
		}

		if(!root->left)
		{
			node * temp = root->right;
			delete root;
			root = temp;
		}

		if (!root->right)
		{
			node * temp = root->left;
			delete root;
			root = temp;
		}
	
		else
		{
			node * temp = NULL;
			node * current = root->right;
			node * previous = NULL;
		

			while(current->left)
			{
				previous  = current;
				current = current->left;
			}
	
			temp = current->right;
			root->entry.copy_entry(current->entry);
			delete current;
		
			if(previous)
				previous->left = temp;

			else
				root->right = temp;
		}
	
		return 1 + remove_name(search, root);
	}
}





