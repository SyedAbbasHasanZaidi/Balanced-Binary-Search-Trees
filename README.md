# Balanced-Binary-Search-Trees
To implement different operations in a balanced binary search tree and analyse the time complexity of its operations

# Background
## Binary Trees
A binary tree is a data structure which can be used for searching (binary search trees), sorting (heaps), binary space partitioning (as in 3D video games), compression algorithms (Huffman Coding) to name a few.

In the Trees and Search Trees lecture, we introduced some fundamental tree operations:

insert a key into a tree

delete a key from a tree

search for a key in a tree

Traversals: preorder, inorder, postorder
These operations are only guaranteed to be efficient if the tree is relatively balanced. It was shown that the efficiency of many operations are improved if the tree is height balanced. In the class we discussed AVL trees which are examples of Balanced Binary Search Trees. Throughout this assignment we will consider implementations using AVL trees.

# Setting Up
Change into the directory you created for the assignment and run the following command:

unzip /web/cs2521/23T1/ass/ass1/downloads/files.zip
If you're working at home, download files.zip by clicking on the above link and then unzip the downloaded file.

You should now have the following files:

## Makefile
a set of dependencies used to control compilation
## bBST.h
interface to the balanced binary search tree
## bBST.c
implementation of the balanced binary search tree (incomplete)
## List.h
interface to List ADT (complete)
## List.c
implementation of the List ADT (complete)
## testBBST.c
driver code with a few basic tests
## analysis.txt
a template for you to enter your time complexity analysis for selected functions
Note that the only files that you are allowed to submit are bBST.c and analysis.txt. Therefore, the only files you should modify are bBST.c, analysis.txt and any testing files (although you will NOT be submitting your tests).

# Task 1: Implementation
Your task is to design and implement some operations on a balanced binary search tree, efficiently. We have divided the operations into groups - you must fully implement all the operations in each group before moving on to the next group.

## Note
When we say you must use a balanced binary search tree, we mean a height-balanced binary search tree. This means for every node in the tree, the absolute difference in height between its left and right subtrees must be no greater than 1.

## Important Constraint
The method of converting the given tree(s) into an array or linked list, solving the main problem using the array/linked list is strictly forbidden. You will receive zero for any functions implemented this way.

## Group 1: Basic Operations
See the comments above function prototypes for the specifics of each function, including their required time complexities.

### Operation/Function	Description
TreeNew	Creates a new empty tree
TreeFree	Frees all memory allocated for a tree
TreeSearch	Searches for a key in the tree
TreeInsert	Inserts a key into the given tree. Any integer may be inserted (including negative integers) except for the value UNDEFINED.
TreeDelete	Deletes a key from the tree
TreeToList	Creates a list containing all the keys in a tree in ascending order

## Group 2: Other Operations
See the comments above function prototypes for the specifics of each function, including their required time complexities.

Operation/Function	Description
### TreeKthSmallest	Finds the 
k
-th smallest key in the tree. 
k
 is guaranteed to be at least 1 and at most the number of nodes in the tree.
### TreeKthLargest	
Finds the k-th largest key in the tree. 
k is guaranteed to be at least 1 and at most the number of nodes in the tree.
### TreeLCA	
Given two keys, find the key of the node which is the lowest common ancestor of the nodes containing the keys. The lowest common ancestor of two nodes is the root node of the smallest subtree that contains both nodes.
### TreeFloor	Given a key 
v
, returns the largest key less than or equal 
v
 in the tree, or UNDEFINED if there is no such key.
### TreeCeiling	
Given a key 
v
, returns the smallest key greater than or equal to 
v
 in the tree, or UNDEFINED if there is no such key.
### TreeSearchBetween	Searches for all keys between the two given keys (inclusive) and returns the keys in a list in ascending order.
Examples
Consider the following tree:

Example Tree
TreeKthSmallest and TreeKthLargest
For 
k
=
1
, the 
k
-th smallest key is 3 and the 
k
-th largest key is 27
For 
k
=
4
, the 
k
-th smallest key is 10 and the 
k
-th largest key is 19
TreeLCA
The lowest common ancestor of 3 and 14 is 10
The lowest common ancestor of 3 and 27 is 16
The lowest common ancestor of 20 and 27 is 25
The lowest common ancestor of 20 and 20 is 20
The lowest common ancestor of 2 and 25 is UNDEFINED
TreeFloor and TreeCeiling
The floor of 6 is 3, and the ceiling of 6 is 7
The floor of 21 is 20, and the ceiling of 21 is 25
The floor of 10 is 10, and the ceiling of 10 is 10
TreeSearchBetween
Searching between 5 and 17 should return a list containing 7, 9, 10, 14, 15 and 16
Searching between 10 and 25 should return a list containing 10, 14, 15, 16, 19, 20 and 25
Task 2: Complexity Analysis
You are required to determine the worst-case time complexity of your implementation of the following operations, and write your answers in analysis.txt along with an explanation of each answer.

TreeKthSmallest
TreeKthLargest
TreeLCA
TreeFloor
TreeCeiling
TreeSearchBetween
Your answers should be in big-O notation and be in terms of 
n
, where 
n
 is the size of the tree.

Full marks will be given only to efficient solutions.

In your explanations, you may use time complexities established in lectures, as long as you indicate that it was established in lectures. For example, you may simply state (without explanation/proof) that the worst-case time complexity of searching in an AVL tree is 
O
(
log
n
)
, as this was established in lectures.

Testing
We have provided a main program testBBST.c containing basic test cases.

To run these tests, first run make, which compiles your code and creates an executable called testBBST, and then run ./testBBST.

We strongly recommend you to add your own tests, as the given tests are very simple. You can easily add your own tests by creating a new function in testBBST.c and then calling it from the main function. You are also free to completely restructure the testing program if you want.

You can call individual tests by specifying their number(s). For example, to run tests 4, 2, and 7, run

./testBBST 4 2 7
testTreeKthSmallest...
Test passed.

testTreeDelete...
Test passed.

testTreeFloor...
Test passed.

All 3 tests passed!
We have provided 9 functions testing basic functionality, but you can modify the tests and numTests to add your own. Providing no command-line arguments will default to running all tests:

./testBBST
testTreeInsertSearch...
Test passed.

testTreeDelete...
Test passed.

testTreeToList...
-- TreeList returned: [1, 3, 5, 10, 15, 17, 20, 21, 22, 23, 25]
Test passed.

testTreeKthSmallest...
Test passed.

testTreeKthLargest...
Test passed.

testTreeLCA...
Test passed.

testTreeFloor...
Test passed.

testTreeCeiling...
Test passed.

testTreeSearchBetween...
-- TreeSearchBetween(1, 25) returned: [1, 3, 5, 10, 15, 17, 20, 21, 22, 23, 25]
-- TreeSearchBetween(17, 17) returned: [17]
-- TreeSearchBetween(10, 30) returned: [10, 15, 17, 20, 21, 22, 23, 25]
-- TreeSearchBetween(-2, 16) returned: [1, 3, 5, 10, 15]
-- TreeSearchBetween(11, 14) returned: []
Test passed.

All 9 tests passed!
