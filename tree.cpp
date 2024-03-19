#include <iostream>
#include <cstring>
#include <fstream>
#include "node.h"

using namespace std;

void fileIn(node**, char file[10]);
void manIn(node**);
void add(node*, node*);
void printTree(node*, int);
void searchTree(node*, int, bool &);
void del(node*, int);

int main() {

  bool editing = true;
  char choice[15];
  node* head = new node(-1);
  node** toHead = new node*;
  (*toHead) = head;
  cout << (*toHead) -> getData() << endl;

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
	fileIn(toHead, file);
      }

      else if (!strcmp(choice2, "man")) {
	cout << "Please input your numbers manually, seperated by spaces: " << endl;
	manIn(toHead);
      }
      cout << "Created Binary Search Tree!" << endl;
    }

    else if (!strcmp(choice, "print")) {
      cout << "Here is the tree: " << endl;
      //cout << (*toHead) -> getData() << endl;
      //cout << (*toHead) -> getR() -> getData() << endl;

      //cout << "here's the actual tree plz work" << endl;
      if ((*toHead) == NULL) {
	cout << "Tree is empty" << endl;
      }
      else if ((*toHead)->getData() == -1) {
	cout << "Tree is empty" << endl;
      }
      else {
	printTree(*toHead, 0);
      }
    }

    else if (!strcmp(choice, "delete_from")) {
      int hated;

      cout << "What number do you want to delete? " << endl;
      cin >> hated;

      cout << "check first" << endl;
      if ((*toHead) -> getL() == NULL && (*toHead) -> getR() == NULL && (*toHead) -> getData() == hated) {
      (*toHead) = NULL;
      }
      else {
	cout << "going in " << endl; 
	del((*toHead), hated);
      }
      cout << "Deleted number from Binary Search Tree!" << endl; 
    }

    else if (!strcmp(choice, "search")) {
      int wanted;
      bool there = false;

      cout << "What number are you looking for? " << endl;
      cin >> wanted;

      if ((*toHead) == NULL) {
	cout << "Tree is empty" << endl;
      }
      else if ((*toHead) -> getData() == -1) {
	cout << "Tree is empty" << endl; //state in beginning
      }
      else {
	searchTree(*toHead, wanted, there);
      }
      
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

void fileIn(node** head, char file[10]) {

  //https://www.udacity.com/blog/2021/05/how-to-read-from-a-file-in-cpp.html

  cout << "getting file" << endl;
  ifstream theFile(file);
  int toAdd;
  
  while (theFile >> toAdd) {
    node* n = new node(toAdd);

    if ((*head) == NULL) {
      (*head) = n;
    }
    else if ((*head) -> getData() == -1) {
      (*head) = n;
      cout << "changed" << endl;
    }
    else {
      cout << "adding to head" << endl;
      add(*head, n);
      cout << (*head) -> getR() -> getData() << endl;

      if ((*head) -> getR() -> getR() != NULL) {
	cout << (*head) -> getR() -> getR() -> getData() << endl;
      }
    }
  }
  
  cout << "exited loop" << endl;

}

void manIn(node** head) {

  int toAdd;
  
  while (cin >> toAdd && toAdd != -1) { //idea to use -1 to end input suggested by Kevin!
    node* n = new node(toAdd);

    if ((*head) == NULL) {
      (*head) = n;
    }
    else if ((*head) -> getData() == -1) {
      (*head) = n;
    }
    else {
      add(*head, n);
    }
  }
  
}

void add(node* head, node* toAdd) {

  if (head -> getL() == NULL && toAdd -> getData() < head -> getData()) {
    cout << "reached end, going to add" << endl;
    (*head).setL(toAdd);
    return;
  }

  else if (head -> getR() == NULL && toAdd -> getData() >= head -> getData()) {
    cout << "reached end, going to add R" << endl;
    (*head).setR(toAdd);
    return;
  }

  if (toAdd -> getData() < head -> getData()) {
    cout << "recursing left" << endl;
    add(head -> getL(), toAdd);
  }

  else if (toAdd -> getData() >= head -> getData()) {
    cout << "recursing right" << endl;
    add(head -> getR(), toAdd);
  }

  //cout << head -> getData();
  return;
}

void printTree(node* head, int depth) {

  if (head -> getL() == NULL && head -> getR() == NULL) {
    for (int i = 0; i < depth; i++) {
    cout << "\t";
    }
    cout << "[";
    cout << head -> getData() << "]" << endl;
    return;
  }

  //print right, parent, then left
  if (head -> getR() != NULL) {
    printTree(head -> getR(), depth + 1);
  }
  
  for (int i = 0; i < depth; i++) {
    cout << "\t";
  }

  cout << "[";
  cout << head -> getData() << "]" << endl;

 if (head -> getL() != NULL) {
   printTree(head -> getL(), depth + 1);
  }
}

void searchTree(node* head, int wanted, bool &there) {

  cout << "looking at " << head -> getData() << endl;
  if (head -> getData() == wanted) {
    there = true;
    return;
  }

  if (head -> getL() == NULL && head -> getR() == NULL) {
    return;
  }

  if (wanted > head -> getData() && head -> getR() != NULL) {
    searchTree(head -> getR(), wanted, there); //recurse right
  }

  if (wanted < head -> getData() && head -> getL() != NULL) {
    searchTree(head -> getL(), wanted, there); //recurse left
  }
  
  return;
}

void del(node* head, int hated) {

  //referred to https://www.youtube.com/watch?v=h5zwiQjl69g&t=112s (Mr. Galbraith's summary of a binary tree and deletion scenarios)

  if (head -> getL() != NULL && head -> getL() -> getData() == hated && head -> getL() -> getL() == NULL && head -> getL() -> getR() == NULL) {
    cout << "at left" << endl;
    node* prev = head -> getL();
    cout << "set prev" << endl;
    head -> setL(NULL);
    cout << "Set" << endl;
    delete prev; //case 1
    cout << "delete" << endl;
    return;
  }

  else if (head -> getR() != NULL && head -> getR() -> getData() == hated && head -> getR() -> getL() == NULL && head -> getR() -> getR() == NULL) {
    cout << "at right" << endl;
    node* prev = head -> getR();
    cout << "Set prev" << endl;
    head -> setR(NULL);
    cout << "set" << endl;
    delete prev;
    cout << "delete" << endl;
    return;
  }
  
  else if (head -> getData() == hated) {
    cout << "found it" << endl;
    
    /*if (head -> getL() == NULL && head -> getR() == NULL) {
      cout << "case 1" << endl;
      head = head -> getL();
      
      cout << "make null" << endl;
      //delete (*head); //case one: deleting node with no children
      cout << "deleted content" << endl;
      return;
      }*/

    if (head -> getL() != NULL && head -> getR() != NULL) {
      //case two: deleting node with two children

      cout << "case 2" << endl;
      
      node* replaceWith = head; //get the smallest # larger than the deleted node to replace it with

      if (replaceWith -> getR() -> getL() != NULL) { //can go lower
	replaceWith = head -> getR();

	while (replaceWith -> getL() != NULL && replaceWith -> getL() -> getL() != NULL) {
	  replaceWith = replaceWith -> getL();
	}

	cout << "reached the end at " << replaceWith -> getData() << endl;
      
	node* actual = new node;
	*actual = *(replaceWith -> getL());
	actual -> setL(head -> getL());
	actual -> setR(head -> getR());
	cout << "get actual" << endl;
	
	*head = *actual; //copy value (but don't change left or right)
	cout << "copy" << endl;
	
	if (replaceWith -> getL() -> getR() == NULL) {
	  replaceWith -> setL(NULL);
	}
	else {
	  *(replaceWith -> getL()) = *(replaceWith -> getL() -> getR());
	}
      }

      else { //cannot go lower
	node* actual = new node;
	*actual = *(replaceWith -> getR());
	actual -> setL(head -> getL());
	actual -> setR(head -> getR());
	*head = *actual;

	if (replaceWith -> getR() -> getR() == NULL) {
	  replaceWith -> setR(NULL);
	}
	else {
	  *(replaceWith -> getR()) = *(replaceWith -> getR() -> getR());
	}
      }

      //going down left to get successor
	

      cout << "replacements made" << endl;
      return;
    }

    else { //case three: deleting node with one child

      cout << "case three" << endl;
      
      if (head -> getL() != NULL) {
	cout << "has l child" << endl;
	//node* prevHead = head;
	//prevHead -> setL(NULL);
	//prevHead -> setR(NULL);
	//cout << "created temp " << endl;
	*(head) = *(head -> getL());
	cout << "move on" << endl;
	//delete prevHead;
	cout << "deleted" << endl;
      }

      else if (head -> getR() != NULL) {
	cout << "right c" << endl;
	//node* prevHead = head;
	//node* instead = NULL;
	//prevHead -> setL(instead);
	//prevHead -> setR(instead);
	//cout << "created temp " << endl;
	*(head) = *(head -> getR());
	cout << "move on" << endl;
	//delete prevHead;
	cout << "deleted" << endl;
      }
      return;
    }
  }

  if (hated > head -> getData() && head -> getR() != NULL) {
    //node** next = new node*;
    //(*next) = (*head) -> getR();
    node* next = new node;
    next = head -> getR();
    del(next, hated);
  }

  if (hated < head -> getData() && head -> getL() != NULL) {
    //node** next = new node*;
    //(*next) = (*head) -> getL();
    node* next = new node;
    next = head -> getL();
    del(next, hated);
  }

  return;
}

