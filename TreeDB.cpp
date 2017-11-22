#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include "DBentry.h"
#include "TreeNode.h"
#include "TreeDB.h"

using namespace std;

// the default constructor, creates an empty database.
TreeDB::TreeDB(){
    root = NULL;
}

// the destructor, deletes all the entries in the database.
TreeDB::~TreeDB(){
    if (root == NULL) return;//if is empty no need to erase;
    else deleteTree();
//    cout << "destrucotr done " << endl;
    
}

void TreeDB::deleteTree(){
    // basis case: nothing to do if no tree
    if (root == NULL) return;
    
    root->deleteAllNode();
    
    delete root;
    
    root = NULL;
}


TreeNode* TreeDB::getRoot() const{
    return root;
}


// If an entry with the same key as newEntry's exists in the database, it returns true. Otherwise, it returns false.
bool TreeDB::exist(string _name){
    
    if (root == NULL) return false;//empty tree
    else{//not empty
        if (root->exist(_name)) {
            return true;// in the tree
        }else{
            return false;//not in the tree
        }
    }
}
// inserts the entry pointed to by newEntry into the database.
// return true if insert successfully
bool TreeDB::insert(DBentry* newEntryPtr){
    if (root == NULL) {
        root = new TreeNode(newEntryPtr);
        return true;
    }
    else{
        if (exist(newEntryPtr->getName())) {
            return false;
        }
        else{
            root->insert(newEntryPtr);
            return true;
        }
    }
}
// searches the database for an entry with a key equal to name.
// If the entry is found, a pointer to it is returned.
// If the entry is not found, the NULL pointer is returned.
// Also sets probesCount
DBentry* TreeDB::find(string _name){
    if (root == NULL) {//empty tree
        cout << "Error: entry does not exists" <<endl;
        return NULL;
    }
    else{
        if (exist(_name)) {//in the tree
            DBentry* temp = root->find(_name);
            cout << *temp ;
            return root->find(_name);
        }else{
            cout << "Error: entry does not exists" <<endl;
            return NULL;//not in the tree
        }
    }
}

// deletes the entry with the specified name (key)  from the database.
// If the entry was indeed in the database, it returns true.
// Returns false otherwise.
// See section 6 of the lab handout for the *required* removal method.
// If you do not use that removal method (replace deleted node by
// maximum node in the left subtree when the deleted node has two children)
// you will not match exercise's output.
bool TreeDB::remove(string name){
    
    if (root == NULL) {//empty tree
        cout << "Error: entry does not exists" <<endl;
        return false;
    }
    else{
        root->removeNode(name, root, root);
        return true;
    }
    return true;
}

// deletes all the entries in the database.
void TreeDB::removeall(){
    if (root == NULL) return;//if is empty no need to erase;
    else deleteTree();
    
    cout << "Success " << endl;
}

// prints the number of probes stored in probesCount
int TreeDB::printProbes(string _name){
    
    if (root == NULL) {//empty tree
        cout << "Error: entry does not exists" <<endl;
        return 0;
    }
    else{
        if (exist(_name)) {//in the tree
            return root->probeCounts(_name);
        }else{
            cout << "Error: entry does not exists" <<endl;
            return 0;//not in the tree
        }
    }
}

// computes and prints out the total number of active entries
// in the database (i.e. entries with active==true).
void TreeDB::countActive () const{
    int count = 0;
    count = root->countActive();
    cout << count << endl;
}

// Prints the entire tree, in ascending order of key/name




//friend ostream& operator<< (ostream& out, const TreeDB& rhs)

