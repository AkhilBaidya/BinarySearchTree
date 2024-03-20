# BinarySearchTree
Creating a Binary Search Tree! - Akhil Baidya (3/20/24)

# Notes:
In this program, the user will be able to create and interact with a Binary Search Tree!

For the purpose of this project, during insertion, the Binary Search Tree will move nodes (user inputs) with values greater than or equal to that of a node encountered in the tree to the right of that encountered node. Otherwise, nodes (user inputs) with lesser values are moved to the left of existing nodes encountered.

# Guide:
Here is what the user can do (these inputs are case-sensistive):

1. The user can input "add" to add a list of positive integers (1 to 999 inclusive) to the tree. The user will have the option of choosing to read in numbers from a file or type them out manually.

To insert numbers from a file, the user must type "file" and then type the file name (such as "num.txt"). THE NUMBERS MUST BE SEPARATED BY SINGLE SPACES in the file.
-> To test this function, you can use the included file "test.txt"

To insert numbers manually, the user must type "man" and then type in a list of positive integers. THESE MUST BE SEPERATED BY SPACES AND THE LIST MUST END IN -1 (the -1 will signify the end of the list typed and will not be added). For instance, "1 2 3 -1"

2. The user can input "print" to print the current Binary Tree sideways.

3. The user can input "del" to delete a specified number from the current tree. After inputting "del", they must type the number that they want to delete.

4. The user can input "search" to search for a specified number in the current tree. After inputting "search", they must type the number that they are searching for.

5. The user can input "quit" to end the program.

# Overarching Source: 
To understand this project, I referred to Mr. Galbraith's summary of the workings of a Binary Tree (https://www.youtube.com/watch?v=h5zwiQjl69g).
In particular, this taught me about deletion in a Binary Tree and how the three cases of deletion are a) deleting a node with no children, b) deleting a node with one child, and c) deleting a node with two children.This taught me, additionally, when deleting the head of the tree (or nodes with two children, in general), it can be replaced with a "successor," the smallest node bigger than it. To access this successor, one can travel to the right of the head/current node and recursively go down left, while possible. When this is no longer possible, one has arrived at the successor.
