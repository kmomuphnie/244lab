//
//  Main.cpp
//  ECE244Lab5
//
//  Created by Dongfang Cui on 2017/11/18.
//  # 1003442492
//
//  Copyright © 2017年 Dongfnag Cui. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "TreeNode.h"
#include "DBentry.h"
#include "TreeDB.h"

using namespace std;

int Parser(stringstream &lineStream, string command);
//void printCheck(TreeDB & root);//debug check-used function
int insert(stringstream &commandStream, TreeDB & root);
int updatestatus(stringstream &commandStream, TreeDB & root);
int find(stringstream &commandStream, TreeDB & root);
int printProbes(stringstream &commandStream, TreeDB & root);
int removeNode(stringstream &commandStream, TreeDB & root);
//void removeall(stringstream &commandStream, TreeDB & root);

int main(void) {
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    
    TreeDB root;
    
    while ( !cin.eof () ) {
        
        
        string line;
        string command;
        int commandCode = -1;//initialize ithe codes for different command ( different return code number)
        cout << "> ";//ready to read
        getline (cin, line); // Get a line from standard input
        
        // Put the line in a stringstream for parsing
        // Making a new stringstream for each line so flags etc. are in a known state
        stringstream lineStream;//use this stream to carry the input line into the Parser
        stringstream commandStream;//use this stream to copy the input line, so if Parser indicates the command from line is correct
        //use this Stream to carry on the detail command
        lineStream << line;
        commandStream << line;
        lineStream >> command;
        
        if (cin.eof()) {//exit the program
            //free the array before exit the program !!!!!!!!!!!!!!!!!!!!!!!!!!
            break;
        }
        
        
        
        commandCode = Parser(lineStream, command);
        //the return table for the commands,
        // 0 for invalid command; 1 for syntax error;
        // 2 for insert;          3 for find;           4 for remove;       5 for removeall
        // 6 for print all;       7 for printprobes;    8 for countactive;  9 for updatestatus;
        //
        switch(commandCode) {
            case 0 ://0 for invalid command
                break;
            case 1 ://1 for syntax error;
                break;
            case 2 ://2 for insert;
                insert(commandStream, root);
                break;
            case 3 ://3 for find;
                find(commandStream, root);
                break;
            case 4 ://4 for remove;
                removeNode(commandStream, root);
                break;
            case 5 :// 5 for remove all;
                root.deleteTree();
                cout << "Success" << endl;
                break;
            case 6 ://6 for print all;
                cout << root;
                
                break;
            case 7 ://7 for printprobes;
                printProbes(commandStream, root);
                break;
            case 8 ://8 countactive;
                root.countActive();
                break;
            case 9 ://9 forupdatestatus;
                updatestatus(commandStream, root);
                break;
            default :
                cout << "Corner case for Parser shows up" << endl;
        }
        
        
    } // End input loop until EOF.
    
    //
    //free the entire TREE when exit the program !!!!!!!!!!!!!!!!!!!!!!!!!!!
    
    //delete everything:

    
//    cout <<"all clear"<<endl;
    
    return 0;
    
}

int removeNode(stringstream &commandStream, TreeDB & root){
    string command, name;
    commandStream >> command;
    commandStream >> name;
    
    bool exist = root.exist(name);
    if (!exist) {//check whether in tree first, if not show the error
        cout << "Error: entry does not exist" << endl;
        return 2;
    }
    
    
    root.remove(name);

    cout << "Success" << endl;
    return 0;
}

int printProbes(stringstream &commandStream, TreeDB & root){
    string command, name;
    commandStream >> command;
    commandStream >> name;
    
    bool exist = root.exist(name);
    if (!exist) {//check whether in tree first, if not show the error
        cout << "Error: entry does not exist" << endl;
        return 2;
    }
    
    cout << root.printProbes(name)<< endl;
    return 0;

}

int updatestatus(stringstream &commandStream, TreeDB & root){
    string command, name;
    string status;
    bool active;
    commandStream >> command;
    commandStream >> name;
    commandStream >> status;
    if (status == "active") active = true;
    else active = false;
    
    bool exist = root.exist(name);
    if (!exist) {//check whether in tree first, if not show the error
        cout << "Error: entry does not exist" << endl;
        return 2;
    }
    
    DBentry* temp = root.getRoot()->find(name);

    temp->setActive(active);
    cout << "Success" << endl;
    
    return 0;
}

int find(stringstream &commandStream, TreeDB & root){
    string command, name;
    commandStream >> command;
    commandStream >> name;
    
    bool exist = root.exist(name);
    if (!exist) {//check whether in tree first, if not show the error
        cout << "Error: entry does not exist" << endl;
        return 2;
    }
    
    root.find(name);
    return 0;
    
}

int insert(stringstream &commandStream, TreeDB & root){
    string command, name;
    unsigned int IPaddress;
    string status;
    bool active;
    commandStream >> command;
    commandStream >> name;
    commandStream >> IPaddress;
    commandStream >> status;
    if (status == "active") active = true;
    else active = false;
    
    bool exist = root.exist(name);
    if (exist) {//check whether in tree first, if is show the error
        cout << "Error: entry already exists" << endl;
        return 2;
    }
    
    DBentry* newEntryPtr = new DBentry(name, IPaddress, active);
    
    if (root.insert(newEntryPtr)) {
        cout << "Success" << endl;
    }
    
    return 0;
}

int Parser(stringstream &lineStream, string command) {
    //the return table for the commands,
    // 0 for invalid command; 1 for syntax error;
    // 2 for insert;          3 for find;           4 for remove;       5 for removeall
    // 6 for print all;       7 for printprobes;    8 for countactive;  9 for updatestatus;
    /*****************************************************************************************************/
    if (command == "insert") {
        return 2;
    }
    /*****************************************************************************************************/
    if (command == "find") {
        return 3;
    }
    /*****************************************************************************************************/
    if (command == "remove") {
        return 4;
    }
    /*****************************************************************************************************/
    if (command == "removeall") {
        return 5;
    }
    /*****************************************************************************************************/
    if (command == "printall") {
        return 6;
    }
    /*****************************************************************************************************/
    if (command == "printprobes") {
        return 7;
    }
    /*****************************************************************************************************/
    if (command == "countactive") {
        return 8;
    }
    /*****************************************************************************************************/
    if (command == "updatestatus") {
        return 9;
    }
    /*****************************************************************************************************/
    cout << "Error: invalid command" << endl;//if the input command doesn't match any cases above
    return 0;
}
