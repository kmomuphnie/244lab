#ifndef _TREENODE_H
#define _TREENODE_H

#include "DBentry.h"

class TreeNode {
private:
    DBentry* entryPtr;
    TreeNode* left;
    TreeNode* right;

public:
    // A useful constructor
    TreeNode(DBentry* _entryPtr);

    // the destructor
    ~TreeNode();
    
    void setEntry(DBentry* newEntry);
    // sets the left child of the TreeNode.
    void setLeft(TreeNode* newLeft);

    // sets the right child of the TreeNode
    void setRight(TreeNode* newRight);

    // gets the left child of the TreeNode.
    TreeNode* getLeft() const;

    // gets the right child of the TreeNode
    TreeNode* getRight() const;

    // returns a pointer to the DBentry the TreeNode contains. 
    DBentry* getEntry() const;
    
    void insert(DBentry* newEntryPtr);
    
    void printInorder();
    
    bool exist(string _name);
    
    DBentry* find(string _name);
    
    int probeCounts(string _name);
    
    int countActive();
    
    void deleteAllNode();
    
    void deleteLeaf(string _name,TreeNode* & parentNode);
    TreeNode* minimum();
    TreeNode* maximum();
    
    void removeNode(string _name, TreeNode* & _root,TreeNode* & parentNode);
    
    
};

#endif 

