/*
C++ Data Structures: Binary Search Tree by Akhil Baidya

Submission Date: 3/20/24

Notes:
In this program, the user will be able to create and interact with a Binary Search Tree!

For the purpose of this project, during insertion, the Binary Search Tree will move nodes (user inputs) with values greater than or equal to that of a node encountered in the tree to the right of that encountered node. Otherwise, nodes (user inputs) with lesser values are moved to the left of existing nodes encountered.

Guide:
Here is what the user can do (these inputs are case-sensistive):

1. The user can input "add" to add a list of positive integers (1 to 999 inclusive) to the tree. The user will have the option of choosing to read in numbers from a file or type them out manually.

To insert numbers from a file, the user must type "file" and then type the file name (such as "num.txt"). THE NUMBERS MUST BE SEPARATED BY SINGLE SPACES in the file.

To insert numbers manually, the user must type "man" and then type in a list of positive integers. THESE MUST BE SEPERATED BY SPACES AND THE LIST MUST END IN -1 (the -1 will signify the end of the list typed and will not be added). For instance, "1 2 3 -1"

2. The user can input "print" to print the current Binary Tree sideways.

3. The user can input "del" to delete a specified number from the current tree. After inputting "del", they must type the number that they want to delete.

4. The user can input "search" to search for a specified number in the current tree. After inputting "search", they must type the number that they are searching for.

5. The user can input "quit" to end the program.

Overarching Source: 
To understand this project, I referred to Mr. Galbraith's summary of the workings of a Binary Tree (https://www.youtube.com/watch?v=h5zwiQjl69g).
In particular, this taught me about deletion in a Binary Tree and how the three cases of deletion are a) deleting a node with no children, b) deleting a node with one child, and c) deleting a node with two children.This taught me, additionally, when deleting the head of the tree (or nodes with two children, in general), it can be replaced with a "successor," the smallest node bigger than it. To access this successor, one can travel to the right of the head/current node and recursively go down left, while possible. When this is no longer possible, one has arrived at the successor. 
 */
 
#include <iostream>
#include <cstring>
#include <fstream>
#include "node.h"

using namespace std;

//Function Prototypes: 
void fileIn(node**, char file[10]);
void manIn(node**);
void add(node*, node*);
void printTree(node*, int);
void searchTree(node*, int, bool &);
void del(node*, int);


/*This function is the main function where the user will input commands to change the Binary Tree
 (such as addition, printing the tree, deletion, and searching for elements in the tree)*/
int main() {
  bool editing = true; //this will loop the editing process (until the user quits)
  char choice[15]; //user input

  //The initial head of the Binary Tree:
  node* head = new node(-1);
  node** toHead = new node*; //pointer to head
  (*toHead) = head;

  //In a loop, the user will be able to input commands:
  while (editing) {
    cout << "Hi, there. Would you like to add to (add), print (print), delete from (del), or search (search) a Binary Tree? Or quit (quit) the program? " << endl;
    cin >> choice;
    cout << "OK" << endl;

    //Quit the program:
    if (!strcmp(choice, "quit")) {
      editing = false; //end loop
    }

    //Add to tree:
    else if (!strcmp(choice, "add")) {
      char choice2[15];
      
      cout << "Would you like to read in numbers from a file (file) or input manually (man)? " << endl;
      cin >> choice2;

      //Adding from a file:
      if (!strcmp(choice2, "file")) {
	char file[10];
	cout << "Please input the name of the file you want to read in: " << endl;
	cin >> file;
	fileIn(toHead, file); //read in from the file specified
      }

      //Adding in manually:
      else if (!strcmp(choice2, "man")) {
	cout << "Please input your numbers manually, seperated by spaces: " << endl;
	manIn(toHead); //begin manual addition process
      }
      cout << "Created Binary Search Tree!" << endl;
    }

    //Printing the tree:
    else if (!strcmp(choice, "print")) {
      cout << "Here is the tree: " << endl;

      //Caution: The tree could be empty (null head)
      if ((*toHead) == NULL) {
	cout << "Tree is empty" << endl;
      }

      //Caution: The tree could be empty (head value of -1 at beginning of code)
      else if ((*toHead)->getData() == -1) {
	cout << "Tree is empty" << endl;
      }

      //Otherwise (avoiding a seg fault), print the tree: 
      else {
	printTree(*toHead, 0);
      }
    }

    //Deleting from tree:
    else if (!strcmp(choice, "del")) {
      int hated; //value to delete
      cout << "What number do you want to delete? " << endl;
      cin >> hated;

      //Caution: The tree could be empty (null head)
      if ((*toHead) == NULL) {
	cout << "Tree is empty" << endl;
      }

      //Caution: The tree could be empty (head value of -1 at beginning of code)
      else if ((*toHead) -> getData() == -1) {
	cout << "Tree is empty" << endl;
      }
      
      //Caution: If the head is the only value in the tree and needs to be deleted, just set it to null
      else if ((*toHead) -> getL() == NULL && (*toHead) -> getR() == NULL && (*toHead) -> getData() == hated) {
      (*toHead) = NULL;
      }

      //Otherwise, call the deletion function:
      else { 
	del((*toHead), hated);
      }
      cout << "Deleted number from Binary Search Tree!" << endl; 
    }

    //Searching in tree:
    else if (!strcmp(choice, "search")) {
      int wanted; //value to find
      bool there = false; //whether the value is there
      cout << "What number are you looking for? " << endl;
      cin >> wanted;

      //Caution: The tree could be empty (null head)
      if ((*toHead) == NULL) {
	cout << "Tree is empty, so" << endl;
      }

      //Caution: The tree could be empty (head value of -1 at the beginning of code - state of head at start of program)
      else if ((*toHead) -> getData() == -1) {
	cout << "Tree is empty, so" << endl;
      }

      //Otherwise, check if value is in the tree:
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

/*This fileIn function reads integers in a file whose name is specified by the user.
  It takes in the file's name and a double pointer to a node in the Binary Tree
  (this node will be the head, as done in the main function)
 The file is assumed to have positive integers (1 - 999) seperated by spaces.*/
void fileIn(node** head, char file[10]) {

  //Referred to source from Udacity team for syntax on how to read a file at
  //https://www.udacity.com/blog/2021/05/how-to-read-from-a-file-in-cpp.html
  /*The source noted how one can create an ifstream class object using a constructor that takes in the file name.
    Then, the source noted how using >> after the ifstream object will read in values until a space.
    The source also mentioned how this action can be placed in a while loop (as the condition, even).
   */
  
  ifstream theFile(file); //the file
  int toAdd; //element to add to tree

  //Loop through every value in the file and add it to tree:
  while (theFile >> toAdd) {  
    node* n = new node(toAdd); //create a node from the value gotten from the file

    //Caution: The tree could be empty (null head)
    if ((*head) == NULL) {
      (*head) = n; //in this case, set the head to the created node
    }

    //Caution: The tree could be empty (head value of -1 at the beginning of code)
    else if ((*head) -> getData() == -1) {
      (*head) = n; //set head to the created node
    }

    //Otherwise, call the add function:
    else {
      add(*head, n); //add node
    }
  }  
  cout << "Read in from file" << endl;

}


/*This manIn function allows the user to type in a list of integers (assumed to be between 1 - 999) separated spaces.
  The end of the list should be -1 for the list to go through. The function loops through the input, adding each integer to the Binary Tree. It takes in a double pointer to a node in the tree (which should be the head) to find this Binary Tree and add to it.
 */
void manIn(node** head) {
  int toAdd; //value to add

  //Continously allow the user to input numbers seperated by spaces until reaching -1 (>> reads until a space and this is looped):
  while (cin >> toAdd && toAdd != -1) { //Idea to use -1 to end input, since I'm reading in positive integers, suggested by Kevin!
    node* n = new node(toAdd); //create a node from the value gotten

    //Caution: The tree could be empty (null head)
    if ((*head) == NULL) {
      (*head) = n; //set the head to the input
    }

    //Caution: The tree could be empty (head value of -1 at the beginning of code)
    else if ((*head) -> getData() == -1) {
      (*head) = n; //set the head to the input
    }

    //Otherwise, add the input:
    else {
      add(*head, n);
    }
  }
  
}

/*This add function takes in a pointer to a node in the tree and a node to add to the tree.
It recursively moves down the tree until reaching the end of the tree, adding the specified node.
It moves down right if the specified node is greater than or equal to the current node and moves down left if not. 
*/
void add(node* head, node* toAdd) {

  //If cannot move down left in the tree anymore and value of the node-to-add is smaller than the current node:
  if (head -> getL() == NULL && toAdd -> getData() < head -> getData()) {
    (*head).setL(toAdd); //add the node as the left child
    return;
  }

  //If cannot move down right in the tree anymore and value of the node-to-add is >= than the current node:
  else if (head -> getR() == NULL && toAdd -> getData() >= head -> getData()) {
    (*head).setR(toAdd); //add the node as the right child
    return;
  }

  //If node-to-add is smaller:
  if (toAdd -> getData() < head -> getData()) {
    add(head -> getL(), toAdd); //go down the tree left
  }

  //If the node-to-add is >=:
  else if (toAdd -> getData() >= head -> getData()) {
    add(head -> getR(), toAdd); //go down the tree right
  }
  return;
}

/*This printTree function recursively goes down the tree and prints it sideways (as such, it takes in a node as a point of reference in the tree). It also takes in an integer for depth down the tree to help indent elements when printing.*/
void printTree(node* head, int depth) {

  //When reaching an end (leaf) in the tree, print it out:
  if (head -> getL() == NULL && head -> getR() == NULL) {

    //Print its depth: 
    for (int i = 0; i < depth; i++) {
      cout << "\t";
    }

    //Print the value:
    cout << "[";
    cout << head -> getData() << "]" << endl;
    return;
  }

  //The idea for this recursive print is to print the right child, the parent, and then the left child:

  //Go recursively down right: 
  if (head -> getR() != NULL) {
    printTree(head -> getR(), depth + 1);
  }

  //Print the current node:
  for (int i = 0; i < depth; i++) {
    cout << "\t"; //print its depth
  }
  cout << "[";
  cout << head -> getData() << "]" << endl; //print its value

  //Go recursively down left:
 if (head -> getL() != NULL) {
   printTree(head -> getL(), depth + 1);
  }
}

/*This searchTree function takes in a wanted integer, the head of the tree, and a boolean.
  It recursively goes down the tree (using the node in the argument) and checks to see if the current node has a value equal to the wanted integer. If so, it sets the boolean to true and otherwise, it sets it to false */
void searchTree(node* head, int wanted, bool &there) {

  //If the current node has the wanted value:
  if (head -> getData() == wanted) {
    there = true; //it is found!
    return;
  }

  //Reaching the end of the tree, stop going down recursively:
  if (head -> getL() == NULL && head -> getR() == NULL) {
    return;
  }

  //Go down right if wanted integer is bigger than current node:
  if (wanted > head -> getData() && head -> getR() != NULL) {
    searchTree(head -> getR(), wanted, there);
  }

  //Go down left if wanted integer is less than current node:
  if (wanted < head -> getData() && head -> getL() != NULL) {
    searchTree(head -> getL(), wanted, there); //recurse left
  }
  return;
}


/* This del function deletes a specified number from the tree (it thus takes in a number to delete and a node in the tree to access the tree). First, it searches for a number that equals the number desired to be deleted. Then, there are three cases of deletion. For this function, I referred to Mr. Galbraith's summary of the workings of a Binary Tree (https://www.youtube.com/watch?v=h5zwiQjl69g).

   This taught me about deletion in a Binary Tree and how the three cases of deletion are a) deleting a node with no children, b) deleting a node with one child, and c) deleting a node with two children. Additionally, when deleting the head of the tree (or nodes with two children, in general), it can be replaced with a "successor," the smallest node bigger than it. To access this successor, one can travel to the right of the head/current node and recursively go down left, while possible. When this is no longer possible, one has arrived at the successor.
 */
void del(node* head, int hated) {

  //Case 1: There is no children of the node-to-delete

  //When the node to delete (equal to the desired number), with no children, is to the left of the current node:
  if (head -> getL() != NULL && head -> getL() -> getData() == hated && head -> getL() -> getL() == NULL && head -> getL() -> getR() == NULL) {
    node* prev = head -> getL();
    head -> setL(NULL); //disconnect this node (a leaf) from the tree
    delete prev; //delete the leaf
    return;
  }

  //When the node to delete (equal to the desired number), with no children, is to the right of the current node:
  else if (head -> getR() != NULL && head -> getR() -> getData() == hated && head -> getR() -> getL() == NULL && head -> getR() -> getR() == NULL) {
    node* prev = head -> getR();
    head -> setR(NULL); //disconnect node (as a leaf) from the tree by setting pointer to it, from parent, to NULL
    delete prev; //delete leaf
    return;
  }

  else if (head -> getData() == hated) {

    //Case 2: Deleting a node with two children
    
    if (head -> getL() != NULL && head -> getR() != NULL) { //node to delete has two children

      //Get the smallest node larger than the deleted node to replace it with:
      node* replaceWith = head;

      //If there are nodes smaller than the node directly to the right of the node-to-be-deleted:
      if (replaceWith -> getR() -> getL() != NULL) {
	
	replaceWith = head -> getR(); //go to node directly to the right

	//While possible, go down to lower-value nodes (down left):
	while (replaceWith -> getL() != NULL && replaceWith -> getL() -> getL() != NULL) {
	  replaceWith = replaceWith -> getL();
	}

	//Replace node-to-be-deleted with this node (its successor):
	node* actual = new node;
	*actual = *(replaceWith -> getL());
	actual -> setL(head -> getL());
	actual -> setR(head -> getR()); //has same children as node-to-be-deleted but with data of found node
	*head = *actual; //copy

	if (replaceWith -> getL() -> getR() == NULL) { //If the node moved to the deleted nodes position has no right child:
	  replaceWith -> setL(NULL); //set it to null
	}
	
	else {//Otherwise:
	  *(replaceWith -> getL()) = *(replaceWith -> getL() -> getR()); //set it to its right child
	}
      }

      //If there are not nodes smaller than the node directly to the right of the node-to-be-deleted, use that node:
      else {
	//Get node-to-be-deleted's successor:
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
      return;
    }

    //Case Three: Deleting a node with one child
    else {

      //If the node-to-be-deleted has a left child:
      if (head -> getL() != NULL) {
	*(head) = *(head -> getL()); //replace it with its left child
      }

      //If the node-to-be-deleted has a right child:
      else if (head -> getR() != NULL) {
	*(head) = *(head -> getR()); //replace it with its right child
      }
      return;
    }
  }

  //Searching the tree recursively:
  
  //If value desired is more than the current node, go down right:
  if (hated > head -> getData() && head -> getR() != NULL) {
    node* next = new node;
    next = head -> getR();
    del(next, hated);
  }

  //If value desired is less than the current node, go down left:
  if (hated < head -> getData() && head -> getL() != NULL) {
    node* next = new node;
    next = head -> getL();
    del(next, hated);
  }
  return;
}

