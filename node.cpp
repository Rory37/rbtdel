#include "node.h"
#include <iostream>
//Adapted from binary tree
node :: node() { //constructor
  left = NULL;
  right = NULL;
  parent = NULL;
  color = 0;
  data = 0;
  isNil = true;
}

node :: ~node() {//destructor
  left = NULL;
  right = NULL;
}

void node :: setLeft(node* newLeft) {//sets left
  left = newLeft;
}

void node :: setRight(node* newRight) {//sets right
  right = newRight;
}

void node :: setParent(node* newParent) {//sets parent
  parent = newParent;
}

node* node :: getLeft() {//gets left
  return left;
}

node* node :: getRight() {//gets right
  return right;
}

node* node :: getParent() {//gets parent
  return parent;
}

void node :: setData(int newdata) {//sets data
  data = newdata;
}

int node :: getData() {//gets data
  return data;
}

void node :: setCol(bool newcol) {//sets color
  color = newcol;
}

bool node :: getCol() {//returns color
  return color;
}

void node :: setIsNil(bool newNil) {
  isNil = newNil;
}

bool node :: getIsNil() {
  return isNil;
}

void node :: reset() {
  left = NULL;
  right = NULL;
  parent = NULL;
  color = 0;
  data = 0;
  isNil = true;
}
