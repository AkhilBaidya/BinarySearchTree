/*
C++ Data Structures: Node Class Header by Akhil Baidya

Submission Date: 3/20/24

Notes:
This is the header file for the node class. It lists the values and functions in a node.
A node contains data (as an integer) and a pointer to a left and right node.
It additionally will have functions (on top of a constructor and destructor) to set and get these values.
 */

#include <iostream>
#include <cstring>

using namespace std;

class node {

 public:

  //Constructors:
  node();
  node(int);

  //Destructor:
  ~node();

  //Set functions:
  void setL(node*); //set left node
  void setR(node*); //set right node
  void setData(int);

  //Get functions
  node* getL(); //get left node
  node* getR(); //get right node
  int getData();
  
 private:
  //Values:
  node* left;
  node* right;
  int data;
};
