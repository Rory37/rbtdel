//Adapted from Binary tree
#ifndef guard
#define guard
class node {
 public:
  node();//constructor
  ~node();//destructor
  //all function prototype
  void setLeft(node*);
  void setRight(node*);
  void setParent(node*);
  node* getLeft();
  node* getRight();
  node* getParent();
  void setData(int);
  int getData();
  void setCol(bool);
  bool getCol();
  void setIsNil(bool);
  bool getIsNil();
  void reset();
  
 private:
  node* left;//holds left node
  node* right;//holds right node
  node* parent;//holds parent node
  int data;//holds data
  bool color;//holds color -- 0 = red, 1 = black
  bool isNil;//Placeholder during empty tree
};

#endif
