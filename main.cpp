#include <iostream>
#include "node.h"
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;

void print(node*, int);
void add(node*, node*, int);
void leftro(node*, node*);
void rightro(node*, node*);
void fix(node*, node*);

int main() {
  node* root = new node();
  bool s = true;
  while(s == true) {//repeats till quit is typed
    cout << "Please choose to either add, read, print or quit" << endl;
    char input [80];
    cin >> input;
    if (strcmp(input, "add") == 0) {
      cout << "What number do you want to add" << endl;
      int in;
      cin >> in;
      add(root, root, in);//runs add
    }
    else if (strcmp(input, "quit") == 0) {
      s = false;//exits loop and program
    }
    else if (strcmp(input, "print") == 0) {
      print(root, 0);//prints the tree
    }
  }
}

void add (node* root, node* parent, int toin){
  if (parent -> getData() == 0) {
    parent -> setCol(1);
    parent -> setData(toin);
  }
  else { //adds like basic binary tree
    if(toin < parent -> getData()) {//if less than data of parent
      if (parent -> getLeft() == NULL) {//if left doesn't exists
	node* newnode = new node();
	newnode -> setData(toin);
	newnode -> setParent(parent);
	parent -> setLeft(newnode);//adds on left
	fix(root, newnode);
      }
      else {
	add(root, parent -> getLeft(), toin);//runs with node to the left
      }

    }
    else { //if right or equal
      if (parent -> getRight() == NULL) { //if right doesn't exist
	node* newnode = new node();
	newnode -> setData(toin);
	newnode -> setParent(parent);
	parent -> setRight(newnode);//inserted to right
	fix(root, newnode);
      }
      else{
	add(root, parent -> getRight(), toin);//runs with one to the right
      }
    }

  }
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
    cout << "\033[32m" << parent -> getData()<< "\033[0m" << endl;//prints the node data
  }
      else{
	cout << parent -> getData() << endl;//prints the node data
      }
  if (parent -> getLeft() != NULL) {//if left exists
    print(parent -> getLeft(), temp + 1);//runs for one to the left
  }
}

void leftro(node* root, node* toro) {
  node* y = toro -> getLeft(); //Holds onto the rotated nodes left
  toro -> setRight(y -> getLeft());//shifts the y left branch to be original node right branch
  if(y -> getLeft() != NULL) {//new parent for left branch must be toro
    y -> getLeft() -> setParent(toro);
  }
  if(toro == root) { //if at root
    root = y; //new root is the y
  }
  else {
    if(toro = toro -> getParent() -> getLeft()) {//if was the left child of parent
      toro -> getParent() -> setLeft(y); //parents left is now y
    }
    else{
      toro -> getParent() -> setRight(y); //parents right is now y
    }
  }
  y -> setLeft(toro);//y's left is the orig node
  toro -> setParent(y);//orig node parent is now y
}

void rightro(node* root, node* toro) {
  node* y = toro -> getLeft(); //Holds onto the rotated node's right
  toro -> setLeft(y -> getRight());//shifts the y right branch to be original node left branch
  if(y -> getRight() != NULL) {//new parent for right branch must be toro
    y -> getRight() -> setParent(toro);
  }
  if(toro == root) { //if at root
    root = y; //new root is the y
  }
  else {
    if(toro = toro -> getParent() -> getLeft()) {//if was the left child of parent
      toro -> getParent() -> setLeft(y); //parents left is now y
    }
    else{
      toro -> getParent() -> setRight(y); //parents right is now y
    }
  }
  y -> setRight(toro);//y's right is the orig node
  toro -> setParent(y);//orig node parent is now y
}

void fix (node* root, node* wasin) {
  while(wasin -> getParent() -> getCol() == 0) {
    //if wasin parent is grandparents left
    if(wasin -> getParent() == wasin -> getParent() -> getParent() -> getLeft()) {
      node* y = wasin -> getParent() -> getParent() -> getRight(); // uncle to wasin
      if(y -> getCol() == 0) {//if uncle was red
	wasin -> getParent() -> setCol(1); //Parent is black
	wasin -> setCol(1); //sets the new node to be black
	wasin -> getParent() -> getParent() -> setCol(0); //Grandparent is red
      }
      else if(wasin = wasin -> getParent() -> getRight()) {//right child
	wasin = wasin -> getParent(); //Runs leftro with parent
	leftro(root, wasin); //Runs left rotation
	wasin -> getParent() -> setCol(1); //sets parent to black
	wasin -> getParent() -> getParent() -> setCol(0); //Grandparent is red
	rightro(root, wasin -> getParent() -> getParent()); //right rotates with grandparent
      }
      else {
	wasin = wasin -> getParent(); //Runs leftro with parent
	rightro(root, wasin); //Runs right rotation
	wasin -> getParent() -> setCol(1); //sets parent to black
	wasin -> getParent() -> getParent() -> setCol(0); //Grandparent is red
	leftro(root, wasin -> getParent() -> getParent()); //left rotates with grandparent
      }
    }
  }
  root -> setCol(1); //root is black
}
