#include "super_entry.h"

// Colton Vitkoczy
// cs163-009 Karla Fant

// The purpose of this file is to store the node struct and tree
// class for the binary tree of hero logs. It contains member functions to 
// insert, retrieve, and diplay all 


struct node
{
	hero_log entry;
	node * right;
	node * left;
};

class tree
{
	public:
		tree();
		~tree();
		int insert(hero_log & to_add);
		int retrieve(char * search, hero_log * array, node * root);
		int load(const char filename[]);
		int display_all(node * root);
		int display(char * search);	
		int display_all();
		int remove_name(char * search);
		int count(char * search, node * root);

	private:
		int insert(node * & root, hero_log & to_add);
		int destroy(node * & root);
		int remove_name(char * search, node * & root);
		node * root;	
};
