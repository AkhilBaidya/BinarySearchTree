#include <iostream>
#include <cstring>
#include <fstream>
#include "node.h"

using namespace std;

void fileIn(node*, char file[10]);
void manIn(node*);
void add(node*, node*);
void printTree(node*, int);
void searchTree(node*, int, bool &);
void del(node*, int);

int main() {

  bool editing = true;
  char choice[15];
  node* head = NULL;

  while (editing) {
    cout << "Hi, there. Would you like to create, print, delete_from, or search a Binary Tree? Or quit the program? " << endl;
    cin >> choice;

    cout << "OK" << endl;
    
    if (!strcmp(choice, "quit")) {
      editing = false;
    }

    else if (!strcmp(choice, "create")) {
      char choice2[15];
      
      cout << "Would you like to read in numbers from a file (file) or input manually (man)? " << endl;
      cin >> choice2;

      if (!strcmp(choice2, "file")) {
	char file[10];

	cout << "Please input the name of the file you want to read in: " << endl;
	cin >> file;

	fileIn(head, file);
      }

      else if (!strcmp(choice2, "man")) {

	cout << "Please input your numbers manually, seperated by spaces: " << endl;
	manIn(head);
      }

      cout << "Created Binary Search Tree!" << endl;
    }

    else if (!strcmp(choice, "print")) {
      cout << "Here is the tree: " << endl;

      if (head == NULL) {
	cout << "huh" << endl;
      }
      //cout << head -> getData() << endl;
      //printTree(head, 0);
    }

    else if (!strcmp(choice, "delete_from")) {
      int hated;

      cout << "What number do you want to delete? " << endl;
      cin >> hated;
      del(head, hated);
      cout << "Deleted number from Binary Search Tree!" << endl;
      
    }

    else if (!strcmp(choice, "search")) {
      int wanted;
      bool there = false;

      cout << "What number are you looking for? " << endl;
      cin >> wanted;
      searchTree(head, wanted, there);
      
      if (there) {
	cout << "Yeah, it is in the tree" << endl;
      }

      else {
	cout << "No, it isn't in the tree" << endl;
      }
    }
    
  }
  return 0;
}

void fileIn(node* head, char file[10]) {

  //https://www.udacity.com/blog/2021/05/how-to-read-from-a-file-in-cpp.html
  
  ifstream theFile(file);
  int toAdd;
  
  while (theFile) {
    theFile >> toAdd;
    node* n = new node(toAdd);

    if (head == NULL) {
      head = n;
    }
    else {
      add(head, n);
    }
  }

}

void manIn(node* head) {

  int toAdd;
  
  while (cin >> toAdd) {
    node* n = new node(toAdd);

    if (head == NULL) {
      head = n;
    }
    else {
      add(head, n);
    }
  }
  
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
    add(head -> getL(), toAdd);
  }

  else if (toAdd -> getData() >= head -> getData()) {
    add(head -> getR(), toAdd);
  }

  return;
}

void printTree(node* head, int depth) {

  cout << head -> getData() << endl;
  
  if (head -> getL() == NULL && head -> getR() == NULL) {

    cout << "at end" << endl;
    
    for (int i = 0; i < depth; i++) {
      cout << " ";
    }
    cout << head -> getData() << endl;

    return;
  }

  //print right, parent, then left
  cout << "going right" << endl;
  printTree(head -> getR(), depth + 1);

  for (int i = 0; i < depth; i++) {
    cout << " ";
  }

  cout << "current" << endl;
  cout << head -> getData() << endl;

  cout << "going left" << endl;
  printTree(head -> getL(), depth + 1);
  
}

void searchTree(node* head, int wanted, bool &there) {
  if (head -> getData() == wanted) {
    there = true;
  }

  if (head -> getL() == NULL && head -> getR() == NULL) {
    return;
  }

  if (wanted > head -> getData()) {
    searchTree(head -> getR(), wanted, there); //recurse right
  }

  if (wanted < head -> getData()) {
    searchTree(head -> getL(), wanted, there); //recurse left
  }
  
  return;
}

void del(node* head, int hated) {

  //referred to https://www.youtube.com/watch?v=h5zwiQjl69g&t=112s (Mr. Galbraith's summary of a binary tree and deletion scenarios)

  if (head -> getData() == hated) {

    if (head -> getL() == NULL && head -> getR() == NULL) {
      head = NULL; //case one: deleting node with no children
      return;
    }

    else if (head -> getL() != NULL && head -> getR() != NULL) {
      //case two: deleting node with two children

      node* replaceWith = head -> getR(); //get the smallest # larger than the deleted node to replace it with

      
      while (replaceWith -> getL() != NULL) {
	replaceWith = replaceWith -> getL();
      }

      node* end = replaceWith; //end of tree
      if (end -> getR() != NULL) { //if there is a right child
	end = end -> getR();
      }

      replaceWith -> setL(head -> getL());
      replaceWith -> setR(head -> getR());

      head = replaceWith; //replace head
    }

    else { //case three: deleting node with one child

      if (head -> getL() != NULL) {
	node* prevHead = head;
	prevHead -> setL(NULL);
	prevHead -> setR(NULL);
	head = head -> getL();
	delete prevHead;
      }

      else if (head -> getR() != NULL) {
	node* prevHead = head;
	prevHead -> setL(NULL);
	prevHead -> setR(NULL);
	head = head -> getR();
	delete prevHead;
      }
    }
  }

  if (hated > head -> getData()) {
    del(head -> getR(), hated);
  }

  if (hated < head -> getData()) {
    del(head -> getL(), hated);
  }

  return;
}

