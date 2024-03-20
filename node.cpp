/*
C++ Data Structures: Node Class by Akhil Baidya

Submission Date: 3/20/24

Notes: This is the file defining the Node class functions. The constructor, destructor, and get and set functions are defined here.
 */

#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

//Constructor 1:
node::node() {
  left = NULL;
  right = NULL;
  data = 0; //by default set pointers to null and data to 0
}

//Constructor 2:
node::node(int newData) {
  left = NULL;
  right = NULL;
  data = newData; //set data to specified data
}

//Destructor:
node::~node() {
  delete left;
  delete right; //delete pointers
}

//Set left child:
void node::setL(node* child) {
  left = new node();
  left = child;
}

//Set right child:
void node::setR(node* child) {
  right = new node();
  right = child;
}

//Set data to specified integer:
void node::setData(int newData) {
  data = newData;
}

//Get left child:
node* node::getL() {
  return left;
}

//Get right child:
node* node::getR() {
  return right;
}

//Get data:
int node::getData() {
  return data;
}
