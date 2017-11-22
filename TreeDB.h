#ifndef _TREEDB_H
#define _TREEDB_H

#include "TreeNode.h"
#include "DBentry.h"

class TreeDB {

private:
   TreeNode* root;
   int probesCount;
   // You will need to add additional private functions
    
    
    
public:
   // the default constructor, creates an empty database.
   TreeDB();

   // the destructor, deletes all the entries in the database.
   ~TreeDB();
   void deleteTree();//the function of delete in the destructor
    
    
   TreeNode* getRoot() const;
   bool exist(string _name);
   // inserts the entry pointed to by newEntry into the database. 
   // If an entry with the same key as newEntry's exists 
   // in the database, it returns false. Otherwise, it returns true.
   bool insert(DBentry* newEntryPtr); 

   // searches the database for an entry with a key equal to name.
   // If the entry is found, a pointer to it is returned.
   // If the entry is not found, the NULL pointer is returned.
   // Also sets probesCount
   DBentry* find(string name);

   // deletes the entry with the specified name (key)  from the database.
   // If the entry was indeed in the database, it returns true.
   // Returns false otherwise.
   // See section 6 of the lab handout for the *required* removal method.
   // If you do not use that removal method (replace deleted node by
   // maximum node in the left subtree when the deleted node has two children)
   // you will not match exercise's output.
   bool remove(string name);
	
   // deletes all the entries in the database.
   //this is the remove all
   void removeall();
    
   // prints the number of probes stored in probesCount
   int printProbes(string _name);
   
   // computes and prints out the total number of active entries
   // in the database (i.e. entries with active==true).
   void countActive () const;

    
    
   // Prints the entire tree, in ascending order of key/name
    friend void operator<< (ostream& out, const TreeDB& rhs){
        if (rhs.root == NULL) {
            cout << " This is an empty tree" <<endl;
            return; // do nothing if
        }else{
            rhs.root->printInorder();
        }
    }
    
    
}; 

// You *may* choose to implement the function below to help print the 
// tree.  You do not have to implement this function if you do not wish to.

//ostream& operator<< (ostream& out, TreeNode* rhs);

#endif 

