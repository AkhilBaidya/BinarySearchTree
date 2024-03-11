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

}

void node::setR(node* child) {

}

void node::setData(int newData) {

}

node* node::getL() {

}

node* node::getR() {

}

int node::getData() {

}
