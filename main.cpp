#include <iostream>
#include "node.h"
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;

//prototypes
void print(node*, int);
void add(node**, node*, int);
void read(node**);
void leftro(node**, node*);
void rightro(node**, node*);
void fix(node**, node*);
node* search(node*, int);
void del(node**, int);
node* predecessor(node*);
node* findsib(node*);
void delcase1(node**, node*);
void delcase2(node**, node*);
void delcase3(node**, node*);
void delcase4(node**, node*);
void delcase5(node**, node*);
void delcase6(node**, node*);

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
  if (parent -> getIsNil() == true) {//Will only be the case with the first pass in of root
    parent -> setIsNil(false);
    parent -> setCol(1);//becomes black
    parent -> setData(toin);//sets the data to be input
  }
  else { //adds like basic binary tree
    if(toin < parent -> getData()) {//if less than data of parent
      if (parent -> getLeft() == NULL) {//if left doesn't exists
	node* newnode = new node(); //Makes new node
	newnode -> setIsNil(false);
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
	newnode -> setIsNil(false);
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
  if(parent -> getIsNil() == true) {
    cout << "Empty Tree" << endl;
  }
  else {
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
  node* deleting = search((*root), del);  //searches for node that wants to be deleted
  node* tracker = NULL;
  node* trackchild;
  node* sentinel = new node(); //initiallizes sentinel node
  if (deleting != NULL) { //if in tree
    if (deleting -> getLeft() == NULL || deleting -> getRight() == NULL) {//if one child NULL or both child NULL
      tracker = deleting;
    }
    else {
      tracker = predecessor(deleting); //retrieves predecessor to tracker
    }
    if (tracker != deleting) { //got predecessor
      deleting -> setData(tracker -> getData());
    }
    if(tracker -> getLeft() != NULL) {//ensures that if there is a real child it is taken
      trackchild = tracker -> getLeft();
    }
    else {
      trackchild = tracker -> getRight();
    }
    //prepping sentinel
    if (trackchild == NULL) {
      trackchild = sentinel;
      trackchild -> setCol(1);
    }
    trackchild -> setParent(tracker -> getParent()); //updates parent
    if (tracker -> getParent() == NULL) { //root node being deleted
      (*root) = trackchild; // root updated to be child
    }
    else { //deleted node isn't root node
      //updates the parents children, tracker replaced with trackchild
      if(tracker == tracker -> getParent() -> getLeft()) {
	tracker -> getParent() -> setLeft(trackchild); //updates parent left child to be trackchild
      }
      else {
	tracker -> getParent() -> setRight(trackchild);//parent right child is trackchild
      }
    }
    if(tracker -> getCol() == 1) {  //if tracker is black
      if(trackchild -> getCol() == 1) { //if child is black
	delcase1(root, trackchild); //go to case 1
      }
      else {
	trackchild -> setCol(1); //otherwise just update to be black
      }
    }
    if((trackchild -> getIsNil() == true) && (trackchild != (*root))) {//if it is a sentinel
      if(trackchild == tracker -> getParent() -> getLeft()) {//updates parents children
	trackchild -> getParent() -> setLeft(NULL);
      }
      else {
	trackchild -> getParent() -> setRight(NULL);
      }
      trackchild -> setParent(NULL); //prep trackchild to delete
      delete trackchild;
    }
    //deallocate spliced node
    delete tracker;
  }
}

node* findsib(node* checking) {
  node* sibling;//holds sibling of checking
  if(checking -> getParent() -> getLeft() == checking){//checks parent left
    sibling = checking -> getParent() -> getRight(); //if checking parent left, sibling right
  }
  else {
    sibling = checking -> getParent() -> getLeft();//otherwise, sibling is parent left
  }
  return sibling;
}

void delcase1(node** root, node* checking) {
  if(checking -> getParent() != NULL) {//checks if root
    delcase2(root, checking); //Moves to next case
  }
  //Runs off because top of tree is reached
}

void delcase2(node** root, node* checking) { //if the sibling is red
  node* sibling = findsib(checking);

  if (sibling -> getCol() == 0) { //if sibling red
    checking -> getParent() -> setCol(0);//parent is red
    sibling -> setCol(1);//sibling is black
    if (checking == checking -> getParent() -> getLeft()) { //if left child
      leftro(root, checking -> getParent()); 
    }
    else {
      rightro(root, checking -> getParent());
    }
  }
  delcase3(root, checking); //moves to next deletion case
  //Can skip case 2 to case 3
}

void delcase3(node** root, node* checking) { //will run if parent, sibling, and sibling's child black
  node* sibling = findsib(checking);

  if((checking -> getParent() -> getCol() == 1) &&
     (sibling -> getCol() == 1) &&
     (sibling -> getLeft() == NULL || sibling -> getLeft() -> getCol() == 1) &&
     (sibling -> getRight() == NULL || sibling -> getRight() -> getCol() == 1)){//checks for parent, sibling, and sibling children being black
    
    sibling -> setCol(0); //sibling just needs to be red
    delcase1(root, checking -> getParent()); //Runs first case with one up tree
  }
  else {
    delcase4(root, checking);//moves to next case
  }
}

void delcase4(node** root, node* checking) {//sibling and its children are black, parent is red
  node* sibling = findsib(checking);
  
  if(checking -> getParent() -> getCol() == 0 && sibling -> getCol() == 1){//checks for parent red, sibling and sibling children being black
    if((sibling -> getLeft() == NULL || sibling -> getLeft() -> getCol() == 1) && (sibling -> getRight() == NULL || sibling -> getRight() -> getCol() == 1)) {
      sibling -> setCol(0); //Sibling becomes red
      checking -> getParent() -> setCol(1);//parent is black
    }
    else {
      delcase5(root, checking);
    }
  }
  else {
    delcase5(root, checking);
  }
}

void delcase5(node** root, node* checking) {
  node* sibling = findsib(checking);

  if(sibling -> getCol() == 1) { //redundancy for case 2
    /*if(checking == checking -> getParent() -> getLeft() && sibling -> getRight() == NULL && sibling -> getRight() -> getCol() == 1) { //left of parent, sib right black*/
    if((checking == checking -> getParent() -> getLeft()) &&
       ((sibling -> getRight() == NULL) || (sibling -> getRight() -> getCol() == 1))) { //left of parent, sib right black

      sibling -> setCol(0); //sibling becomes red
      sibling -> getLeft() -> setCol(1); //Was red due to case 2-4
      rightro(root, sibling);
    }
    else if((checking == checking -> getParent() -> getRight()) &&
	    ((sibling -> getLeft() == NULL) || (sibling -> getLeft() -> getCol() == 1))) { //right of parent, sib left black
      sibling -> setCol(0); //sibling becomes red
      sibling -> getRight() -> setCol(1); //Was red due to case 2-4
      leftro(root, sibling);
    }
  }
  delcase6(root, checking);
}

void delcase6(node** root, node* checking) { //s is black, checking is black, one s child is red
  node* sibling = findsib(checking);

  sibling -> setCol(checking -> getParent() -> getCol()); //copies color down
  checking -> getParent() -> setCol(1); //parent is black

  if(checking == checking -> getParent() -> getLeft()) { //left child
    sibling -> getRight() -> setCol(1); //sibling right is black
    leftro(root, checking -> getParent());
  }
  else {
    sibling -> getLeft() -> setCol(1); //sibling left is black
    rightro(root, checking -> getParent());
  }
  
}

node* predecessor(node* top) {
  if(top -> getLeft() != NULL) { //goes one left
    top = top -> getLeft();
  }
  while(top -> getRight() != NULL) {//goes all the way right
    top = top -> getRight();
  }
  return top;
}
