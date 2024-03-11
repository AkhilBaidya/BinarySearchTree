#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

void add(node*, node*);
void print(node*);
void search(node*, int);
void del(node*, int);

int main {

  bool editing = true;
  char choice[15];
  node* head = new node();

  while (editing) {
    cout << "Hi, there. Would you like to create, print, delete_from, or search a Binary Tree? Or quit the program? " << endl;
    cin >> choice;

    if (!strcmp(choice, "quit")) {
      editing = false;
    }

    else if (!strcmp(choice, "create")) {

    }

    else if (!strcmp(choice, "print")) {

    }

    else if (!strcmp(choice, "delete_from")) {

    }

    else if (!strcmp(choice, "search")) {

    }
    
  }
  return 0;
}

void add(node* head, node* toAdd) {

  if (head -> getL() == NULL && toAdd -> getData() < head -> getData()) {
    head -> setL(toAdd);
    return;
  }

  else if (head -> getR() == NULL && toAdd -> getData() >= head -> getData()) {
    head -> setR(toAdd);
    return;
  }

  if (toAdd -> getData() < head -> getData()) {
    node* newLoc = head -> getL();
    add(newLoc, toAdd);
  }

  else if (toAdd -> getData() >= head -> getData()) {
    node* newLoc = head -> getR();
    add(newLoc, toAdd);
  }

  return;
}

void printTree(node* head) {

}

void searchTree(node* head, int wanted) {

}

void delfromTree(node* head, int hated) {

}

