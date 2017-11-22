#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include "DBentry.h"
#include "TreeNode.h"

using namespace std;

TreeNode::TreeNode(DBentry* _entryPtr){
    entryPtr = _entryPtr;
    left = NULL;
    right = NULL;
}

// the destructor
TreeNode::~TreeNode(){
    //do nothing delte the pointer manully in the main function
}

void TreeNode::setEntry(DBentry* newEntry){
    entryPtr = newEntry;
}

// sets the left child of the TreeNode.
void TreeNode::setLeft(TreeNode* newLeft){
    left = newLeft;
}

// sets the right child of the TreeNode
void TreeNode::setRight(TreeNode* newRight){
    right = newRight;
}

// gets the left child of the TreeNode.
TreeNode* TreeNode::getLeft() const{
    return left;
}

// gets the right child of the TreeNode
TreeNode* TreeNode::getRight() const{
    return right;
}

// returns a pointer to the DBentry the TreeNode contains.
DBentry* TreeNode::getEntry() const{
    return entryPtr;
}

void TreeNode::insert(DBentry* newEntryPtr){
    
    if (newEntryPtr->getName() == entryPtr->getName()) {
        return;//shouldn't happen because check existence before insertion
    }
    
    if (newEntryPtr->getName() < entryPtr->getName()) {
        //insert to the left
        if (left == NULL) {
            left = new TreeNode(newEntryPtr);
        }
        else{
            left->insert(newEntryPtr);
        }
    }
    else if(newEntryPtr->getName() > entryPtr->getName()){//insert to hte right
        if (right == NULL) {
            right = new TreeNode(newEntryPtr);
        }
        else{
            right->insert(newEntryPtr);
        }
    }
    else{
        cout << " didn't insert properly " << endl;
    }
}

void TreeNode::printInorder(){
    if (left != NULL) {
        left->printInorder();
    }
    cout << *entryPtr;
    if (right != NULL) {
        right->printInorder();
    }
}


bool TreeNode::exist(string _name){
    if (entryPtr->getName() == _name) {
        return true;
    }
    else if(entryPtr->getName() > _name){
        if (left != NULL) {
            return left->exist(_name);
        }
    }
    else{
        if (right != NULL) {
            return right->exist(_name);
        }
    }
    return false;
}

DBentry* TreeNode::find(string _name){
    if (entryPtr->getName() == _name) {
        return entryPtr;
    }
    else if(entryPtr->getName() > _name){
        if (left != NULL) {
            return left->find(_name);
        }
    }
    else{
        if (right != NULL) {
            return right->find(_name);
        }
    }
    return NULL;
}

int TreeNode::probeCounts(string _name){
    int count = 0;
    if (entryPtr->getName() == _name) {
        return count = count + 1;
    }
    else if(entryPtr->getName() > _name){
        if (left != NULL) {
            return count = 1 + left->probeCounts(_name);
        }
    }
    else{
        if (right != NULL) {
            return count = 1 + right->probeCounts(_name);
        }
    }
    
    return count;
}


int TreeNode::countActive(){
    int count = 0;
    if (entryPtr->getActive() == true) {
        count = count + 1;
    }
    
    if ((left != NULL) && (right != NULL) ){//2 children
        return count + left->countActive() + right->countActive();
    }else{
        if ((left == NULL) && (right != NULL)) {//1 child
            return count +  right->countActive();
        }
        else if ((right == NULL) && (left !=NULL)){//1 child
            return count +  left->countActive();
        }else{//leaf
            return count;
        }
    }
}

void TreeNode::deleteAllNode(){
    
    if (entryPtr != NULL) {
        delete entryPtr;
    }
    
    if ((left != NULL) && (right != NULL) ){//2 children
        left->deleteAllNode();//free the subtree
        right->deleteAllNode();
        delete left;
        delete right;
    }else{
        if ((left == NULL) && (right != NULL)) {//1 right child
            right->deleteAllNode();
            delete right;
        }
        else if ((right == NULL) && (left != NULL)){//1 left child
            left->deleteAllNode();
            delete left;
        }else{//leaf
            return;
        }
    }
}

void TreeNode::deleteLeaf(string _name,TreeNode* & parentNode){
    if (_name < entryPtr->getName()) {
        if (left != NULL) {
            TreeNode* tempParent = this;
            left->deleteLeaf(_name, tempParent);
        }
        return;
    }else if (_name > entryPtr->getName()){
        if (right != NULL) {
            TreeNode* tempParent = this;
            right->deleteLeaf(_name, tempParent);
        }
        return;
    }else{
        if ((left == NULL) && (right == NULL)) {//no children is a leaf
            if (parentNode->getLeft() == this) {
                parentNode->setLeft(NULL);//if is the left child of the parent, set the left child of parent to NULL
            }
            if (parentNode->getRight() == this) {
                parentNode->setRight(NULL);
            }
            delete entryPtr;
            delete this;
        }
        return;
    }
}

TreeNode* TreeNode::minimum(){
    if (left == NULL) {
        return this;
    }
    return left->minimum();
}

TreeNode* TreeNode::maximum(){
    if (right == NULL) {
        return this;
    }
    return right->maximum();
}

void TreeNode::removeNode(string _name, TreeNode* & _root, TreeNode* & parentNode){
    
    if (_name < entryPtr->getName()) {
        if (left != NULL) {
            TreeNode* tempParent = this;
            left->removeNode(_name, _root, tempParent);
        }
        return;
        
    }else if (_name > entryPtr->getName()){
        if (right != NULL) {
            TreeNode* tempParent = this;
            right->removeNode(_name, _root, tempParent);
        }
        return;
        
    }else{//we locate where the node to be deleted is
        if ((left == NULL) && (right == NULL)) {//no children
            if (this == _root) {//it is the root node of the tree to be deleted
                _root = NULL;
                delete entryPtr;
                delete this;
            }else{
                if (parentNode->getLeft() == this) {
                    parentNode->setLeft(NULL);//if is the left child of the parent, set the left child of parent to NULL
                }
                if (parentNode->getRight() == this) {
                    parentNode->setRight(NULL);
                }
                delete entryPtr;
                delete this;//hopefully wont cause any bug
            }
        }else if((left != NULL) && (right == NULL)) {
            if (this == _root) {//it is the root node of the tree to be deleted
                _root = left;
                delete entryPtr;
                delete this;
            }else{
                if (parentNode->getLeft() == this) {
                    parentNode->setLeft(left);//if is the left child of the parent, set the left child of parent to NULL
                }
                if (parentNode->getRight() == this) {
                    parentNode->setRight(left);
                }
                
                delete entryPtr;
                delete this;//hopefully wont cause any bug
            }
            
            
            
        }else if ((left == NULL) && (right != NULL)){
            if (this == _root) {//it is the root node of the tree to be deleted
                _root = right;
                delete entryPtr;
                delete this;
            }else{
                if (parentNode->getLeft() == this) {
                    parentNode->setLeft(right);//if is the left child of the parent, set the left child of parent to NULL
                }
                if (parentNode->getRight() == this) {
                    parentNode->setRight(right);
                }
                
                delete entryPtr;
                delete this;//hopefully wont cause any bug
            }
            
            
        }else{
//            TreeNode* minimumOfRightSubTree = right->minimum();//get the pointer points to the minimum node of right sub tree
            //copy the content of the right minimum leaf
//            string tempName = minimumOfRightSubTree->getEntry()->getName();
//            unsigned int tempAddress = minimumOfRightSubTree->getEntry()->getIPaddress();
//            bool tempActive = minimumOfRightSubTree->getEntry()->getActive();
            
            TreeNode* maximumOfLeftSubTree = left->maximum();//get the pointer points to the maximum node of left sub tree
            
            //copy the content of the left maximum leaf
            
            string tempName = maximumOfLeftSubTree->getEntry()->getName();
            unsigned int tempAddress = maximumOfLeftSubTree->getEntry()->getIPaddress();
            bool tempActive = maximumOfLeftSubTree->getEntry()->getActive();
            
            TreeNode* tempParent = this;
//            deleteLeaf(tempName, tempParent);//delete that leaf
            removeNode(tempName, tempParent, tempParent);
            
            entryPtr->setName(tempName);
            entryPtr->setIPaddress(tempAddress);
            entryPtr->setActive(tempActive);
            
        }
        return;
    }
}

