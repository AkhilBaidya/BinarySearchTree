#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

node::node() {
  left = NULL;
  right = NULL;
  data = 0;
}

node::node(int newData) {
  left = NULL;
  right = NULL;
  data = newData;
}

node::~node() {
  delete left;
  delete right;
}

void node::setL(node* child) {
  left = new node();
  left = child;
  //*left = *child;
}

void node::setR(node* child) {
  right = new node();
  right = child;
  //*right = *child;
}

void node::setData(int newData) {
  data = newData;
}

node* node::getL() {
  return left;
}

node* node::getR() {
  return right;
}

int node::getData() {
  return data;
}
