#include <iostream>
#include "node.h"
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;

void print(node*, int);
void add(node**, node*, int);
void read(node**);
void leftro(node**, node*);
void rightro(node**, node*);
void fix(node**, node*);
node* search(node*, int);
void del(node**, int);
node* successor(node*);
void fixdel(node**, node*);

int main() {
  node* root = new node(); //will be root of tree
  bool s = true;
  while(s == true) {//repeats till quit is typed
    cout << "Please choose to either add, read, print, search, delete or quit" << endl;
    char input [80];
    cin >> input;//Takes in command from console
    if (strcmp(input, "add") == 0) {
      cout << "What number do you want to add" << endl;
      int in;
      cin >> in;//takes in number
      add(&root, root, in);//runs add
    }
    else if (strcmp(input, "quit") == 0) {
      s = false;//exits loop and program
    }
    else if (strcmp(input, "print") == 0) {
      print(root, 0);//prints the tree
    }
    else if (strcmp(input, "read") == 0) {//will read in a file separated only by commas
      read(&root); //Passes root by reference so it changes if edited outside main
    }
    else if (strcmp(input, "search") == 0) {
      int in;
      cout << "What number do you want to search for" << endl;
      cin.ignore();
      cin >> in;
      search(root, in);//looks through tree for value
    }
    else if (strcmp(input, "delete") == 0) {
      cout << "What number do you want to delete" << endl;
      int in;
      cin >> in;//takes in number  
      del(&root, in); //Passes root by reference so it can be changed in main.cpp
    }
  }
}

void add (node** root, node* parent, int toin){
  if (parent -> getData() == 0) {//Will only be the case with the first pass in of root
    parent -> setCol(1);//becomes black
    parent -> setData(toin);//sets the data to be input
  }
  else { //adds like basic binary tree
    if(toin < parent -> getData()) {//if less than data of parent
      if (parent -> getLeft() == NULL) {//if left doesn't exists
	node* newnode = new node(); //Makes new node
	newnode -> setData(toin); //Sets node data to be input
	newnode -> setParent(parent); //Sets the new nodes parents
	parent -> setLeft(newnode);//adds on left
	fix(root, newnode); //Preserves red black properties
      }
      else {
	add(root, parent -> getLeft(), toin);//runs with node to the left
      }
    }
    else { //if right or equal
      if (parent -> getRight() == NULL) { //if right doesn't exist
	node* newnode = new node(); //Makes new node
	newnode -> setData(toin);///Sets data to input
	newnode -> setParent(parent); //sets parent of new node
	parent -> setRight(newnode);//inserted to right
	fix(root, newnode); //Preserves red black properties
      }
      else{
	add(root, parent -> getRight(), toin);//runs with one to the right
      }
    }
  }
}

void read(node** root) { //read in file
  cout << "Please input a filename" << endl;
  char filename[80];//for name of file
  cin.ignore();//ignores past cin
  cin.getline(filename, 80);//takes in the name
  ifstream newFile; //new file
  newFile.open(filename);//opens file with the name put in
  if (newFile == NULL) {//if file doesn't exist
    cout << "There was an error reading the file" << endl;
  }
  else {
    while (newFile.eof() != true) {//while not end of file
      char* s = new char[4]; //will hold number in char array
      newFile.getline(s, 5, ',');//gets line splitting over comma
      int in = atoi(s); //converts to int
      add(&(*root), (*root), in); //Runs add with each data segment
    }
  }
  newFile.close();//closes file
}

void print(node* parent, int count) {
  if(parent -> getRight() != NULL) {//if there is right
    print(parent -> getRight(), count + 1); //runs for one to right
  }
  int temp = count;//holds count for left side
  while (count > 0) {
    cout << "   "; //prints tabs for each level of tree
    count --;
  }
  if (parent -> getCol() == 0) {
    cout << "\033[31m" << parent -> getData()<< "\033[0m" << endl;//prints the node data (Red)
  }
  else{
    cout << parent -> getData() << endl;//prints the node data (Black, but will display as white)
  }
  if (parent -> getLeft() != NULL) {//if left exists
    print(parent -> getLeft(), temp + 1);//runs for one to the left
  }
}

void leftro(node** root, node* toro) {
  node* y = toro -> getRight(); //Holds onto the rotated nodes left
  toro -> setRight(y -> getLeft());//shifts the y left branch to be original node right branch
  if(y -> getLeft() != NULL) {//new parent for left branch must be toro
    y -> getLeft() -> setParent(toro);
  }
  y -> setParent(toro -> getParent());//y parent is toro parent
  if(toro == (*root)) { //if at root
    (*root) = y; //new root is the y
  }
  else {
    if(toro == toro -> getParent() -> getLeft()) {//if was the left child of parent
      toro -> getParent() -> setLeft(y); //parents left is now y
    }
    else{
      toro -> getParent() -> setRight(y); //parents right is now y
    }
  }
  y -> setLeft(toro);//y's left is the orig node
  toro -> setParent(y);//orig node parent is now y
}

void rightro(node** root, node* toro) {
  node* y = toro -> getLeft(); //Holds onto the rotated node's right
  toro -> setLeft(y -> getRight());//shifts the y right branch to be original node left branch
  if(y -> getRight() != NULL) {//new parent for right branch must be toro
    y -> getRight() -> setParent(toro);
  }
  y -> setParent(toro -> getParent()); //Y parent is toro parent
  if(toro == (*root)) { //if at root
    (*root) = y; //new root is the y
  }
  else {
    if(toro == toro -> getParent() -> getLeft()) {//if was the left child of parent
      toro -> getParent() -> setLeft(y); //parents left is now y
    }
    else{
      toro -> getParent() -> setRight(y); //parents right is now y
    }
  }
  y -> setRight(toro);//y's right is the orig node
  toro -> setParent(y);//orig node parent is now y
}

void fix (node** root, node* z) {
  while(z -> getParent() != NULL && z -> getParent() -> getCol() == 0 && z != (*root)) {//while not root and red parent
    //will stop running at case 2
    if(z -> getParent() == z -> getParent() -> getParent() -> getLeft()) {//if parent is to left of grandparent
      node* y = z -> getParent() -> getParent() -> getRight(); // uncle to z
      if(y != NULL && y -> getCol() == 0) {//if uncle was red (case 3) 
	z -> getParent() -> setCol(1); //Parent is black
	y -> setCol(1); //sets the uncle to be black
	z -> getParent() -> getParent() -> setCol(0); //Grandparent is red
	z = z -> getParent() -> getParent();//z is z grandparent
      }
      else {
 	if(z == z -> getParent() -> getRight()) {//right child (case 4 triangle)
	  z = z -> getParent(); //Runs leftro with parent
	  leftro(root, z); //Runs left rotation
	}	
	z -> getParent() -> setCol(1); //sets parent to black (case 4 line)
	z -> getParent() -> getParent() -> setCol(0); //Grandparent is red
	rightro(root, z -> getParent() -> getParent()); //right rotates with grandparent
      }
    }
    else {//right to granparent
      node* y = z -> getParent() -> getParent() -> getLeft(); // uncle to z
      if(y != NULL && y -> getCol() == 0) {//if uncle was red (case 3)
	z -> getParent() -> setCol(1); //Parent is black
	y -> setCol(1); //sets the new node to be black
	z -> getParent() -> getParent() -> setCol(0); //Grandparent is red
	z = z -> getParent() -> getParent();
      }
      else{
	if(z == z -> getParent() -> getLeft()) {//left child (case 4 triangle)
	  z = z -> getParent(); //Runs rightro with parent
	  rightro(root, z); //Runs right rotation
	}
	z -> getParent() -> setCol(1); //sets parent to black (case 4 line);
	z -> getParent() -> getParent() -> setCol(0); //Grandparent is red
	leftro(root, z -> getParent() -> getParent()); //left rotates with grandparent
      }
    }
  }
  (*root) -> setCol(1); //root is black (case 1)
}

node* search (node* check, int in) {
  while (check != NULL) {//until end of tree
    if (in == check -> getData()) {//If data does match
      cout << "The number " << in << " is in the tree." << endl;
      return check;//exits search
    }
    else if (in < check -> getData()){ //if the input is less than node data
      check = check -> getLeft(); //go down left branch
    }
    else{
      check = check -> getRight();//go down right branch
    }
  }
  cout << "The number " << in << " is not in the tree" << endl; //num not in tree
  return NULL;
}

void del (node** root, int del) {
  node* deleting = search((*root), del);
  node* tracker = NULL;
  node* trackchild;
  if (deleting != NULL) {
    if (deleting -> getLeft() == NULL || deleting -> getRight() == NULL) {
      tracker = deleting;
    }
    else {
      tracker = successor(deleting);
    }
    if(tracker -> getCol() == 1) {
      fixdel(root, tracker);
    }
    if(tracker -> getLeft() != NULL) {
      trackchild = tracker -> getLeft();
    }
    else{
      trackchild = tracker -> getRight();
    }
    //if(tracker -> getCol() == 1) {
      //fixdel(root, tracker);
      //}
    if(tracker == (*root)) {//is root
      (*root) = trackchild;//root becomes the child
    }
    else if (tracker == tracker -> getParent() -> getLeft()){//is left child
      tracker -> getParent() -> setLeft(trackchild); 
    }
    else {
      tracker -> getParent() -> setRight(trackchild);
    }
    if (tracker != deleting) { //got successor
      deleting -> setData(tracker -> getData());
      deleting -> setCol(tracker -> getCol());
    }
    //if(tracker -> getCol() == 1) {
    //fixdel(root, trackchild);
    //}
    //probably should return tracker to delete
  }
}

void fixdel(node** root, node* fixmain) {
  while (fixmain != (*root) && fixmain -> getCol() == 1) {//It doesn't run right since NULL isn't technically a node I think
    if(fixmain == fixmain -> getParent() -> getLeft()) {
      node* sibling = fixmain -> getParent() -> getRight();
      if(sibling != NULL && sibling -> getCol() == 0) {//Case 1 sibling is red
	sibling -> setCol(1);//sibling becomes black
	fixmain -> getParent() -> setCol(0);//parent becomes red
	leftro(root, fixmain -> getParent());
	sibling = fixmain -> getParent() -> getRight();
      }
      if((sibling -> getLeft() == NULL || sibling -> getLeft() -> getCol() == 1) && (sibling -> getRight() == NULL || sibling -> getRight() -> getCol() == 1)) { //if both childs black case 2
	sibling -> setCol(0);//sibling is red
	fixmain = fixmain -> getParent();
      }
      else if (sibling -> getRight() == NULL && sibling -> getRight() -> getCol() == 1) { //case 3 if sibling right is black
	sibling -> getLeft() -> setCol(1); //sibling left is black
	sibling -> setCol(0);//sibling is red
	rightro(root, sibling);
	sibling = fixmain -> getParent() -> getRight();
      }
      if (fixmain -> getParent() == NULL) {
	sibling -> setCol(1); //Case 4
      }
      else {
	sibling -> setCol(fixmain -> getParent() -> getCol()); //Case 4
	fixmain -> getParent() -> setCol(1);//parent black
      }
      if(sibling-> getRight() != NULL) {
	sibling -> getRight() -> setCol(1);//sibling right is black
      }
      if(fixmain -> getLeft() != NULL) {
	leftro(root, fixmain -> getParent());
      }
      fixmain = (*root);
    }
    else {
      node* sibling = fixmain -> getParent() -> getLeft();
      if(sibling != NULL && sibling -> getCol() == 0) {//Case 1
	sibling -> setCol(1);//sibling becomes black
	fixmain -> getParent() -> setCol(0);//parent becomes red
	rightro(root, fixmain -> getParent());
	sibling = fixmain -> getParent() -> getLeft();
      }
      if((sibling -> getLeft() == NULL || sibling -> getLeft() -> getCol() == 1) && (sibling -> getRight() == NULL || sibling -> getRight() -> getCol() == 1)) { //if both childs black case 2
	sibling -> setCol(0);//sibling becomes red
	fixmain = fixmain -> getParent();
	cout << "a" << endl;
      }
      else if (sibling -> getLeft() == NULL && sibling -> getLeft() -> getCol() == 1) { //case 3
	cout << "b" << endl;
	sibling -> getRight() -> setCol(1);//the sibling right becomes black
	sibling -> setCol(0); //sibling becomes red
	leftro(root, sibling);
	sibling = fixmain -> getParent() -> getLeft();
	cout << "c" << endl;
      }
      if (fixmain -> getParent() == NULL) {
	sibling -> setCol(1); //Case 4
      }
      else {
	sibling -> setCol(fixmain -> getParent() -> getCol()); //Case 4
	fixmain -> getParent() -> setCol(1);//parent black
      }
      if (sibling -> getLeft() != NULL) {
	sibling -> getLeft() -> setCol(1);//siblings left child black
      }
      if(fixmain -> getParent() != NULL) {
	rightro(root, fixmain -> getParent());
      }
      fixmain = (*root);
      cout << "d" << endl;
      
    }
  }
  if(fixmain != NULL) {
    fixmain -> setCol(1);//root becomes black
  }
}

node* successor(node* top) {
  if(top -> getRight() != NULL) {
    top = top -> getRight();
  }
  while(top -> getLeft() != NULL) {
    top = top -> getLeft();
  }
  return top;
}
