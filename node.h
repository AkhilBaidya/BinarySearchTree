#include <iostream>
#include <cstring>

using namespace std;

class node {

 public:
  node();
  node(int);
  ~node();

  //set
  void setL(node*);
  void setR(node*);
  void setData(int);

  //get
  node* getL();
  node* getR();
  int getData();
  
 private:
  node* left;
  node* right;
  int data;
};
