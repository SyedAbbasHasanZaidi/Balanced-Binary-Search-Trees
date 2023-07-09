#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "bBST.h"
#include "List.h"

////////////////////////////////////////////////////////////////////////
/* IMPORTANT:
   Do NOT modify the code above this line.
*/

//////////////////////////////////////////////
//*REFERENCES
/*
SOURCE URL: https://www.cse.unsw.edu.au/~cs2521/23T1/lecs/trees2/slides.html#s10
fn: static Node RotateRight(Node); (slide 7)
fn: static Node RotateLeft(Node); (slide 8)

Inspiration from Psuedocode was taken from the above mentioned sources 

SOURCE URL: https://www.cse.unsw.edu.au/~cs2521/23T1/lecs/avl/slides.html#s6
fn: static Tree DoTreeInsert(Tree t ,int key); (slide 6)
fn: static int UpdateBalanceFactor(Node root); (slide 7)

Inspiration from Psuedocode was taken from the above mentioned sources
*/
////////////////////////////////////////////////////////////////////////
//MACROS
#define data(tree)  ((tree)->root->key)
#define left(tree)  ((tree)->root->left)
#define right(tree) ((tree)->root->right)



////////////////////////////////////////////////////////////////////////
// Auxiliary function prototypes

// Write Auxiliary function prototypes here, and declare them as static

////////////////////////////////////////////////////////////////////////

static int Max(int,int);
static void UpdateHeight(Node);
static int UpdateBalanceFactor(Node);
static Node RotateRight(Node);
static Node RotateLeft(Node);
static int Height(Node);
static Node TreeJoin(Node,Node);
static void PostOrder(Node,void (*p)());

static Tree CreateSubtree(Node);
static Node CreateNode(int);
static void FreeSubtree(Tree t);

static Tree DoTreeInsert(Tree,int);
static Node DoTreeDelete(Node,int);
static List DoTreeToList(Node,List);
static void DoTreeKthSmallest(Node,Node*,int,int*);
static void DoTreeKthLargest(Node, Node*, int, int*);
static void DoTreeLCA(Node, Node*, int, int);
static void DoTreeFloor(Node,Node*,int);
static void DoTreeCeiling(Node, Node*, int);
static void DoTreeSearchBetween(Node,List*,int,int);

////////////////////////////////////////////////////////////////////////

/**
 * Creates a new empty tree.
 * The time complexity of this function must be O(1).
 */
Tree TreeNew(void) {

    Tree t = malloc(sizeof(struct tree));

    if (t == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }

    t->root = NULL;
    return t;
}

////////////////////////////////////////////////////////////////////////

/**
 * Frees all memory allocated for the given tree.
 * The time complexity of this function must be O(n).
 */
void TreeFree(Tree t) {
     
    PostOrder(t->root,free); //Freeing all nodes in post order 
    free(t);                  //Freeing overarching tree structure  
}

////////////////////////////////////////////////////////////////////////

/**
 * Searches the tree for a given key and returns true if the key is in
 * the tree or false otherwise.
 * The time complexity of this function must be O(log n).
 */
bool TreeSearch(Tree t, int key) {

    bool return_val = true;

    if (t == NULL || t->root == NULL) return false;
    
    if (data(t) > key) {
        Tree t_left = CreateSubtree(left(t)); // creating subtree for recursive calls
        return_val = TreeSearch(t_left,key);
        FreeSubtree(t_left);                        // Freeing said subtree 
    }
    else if (data(t) < key) {
        Tree t_right = CreateSubtree(right(t)); 
        return_val = TreeSearch(t_right,key);
        FreeSubtree(t_right);                         
    }
    
    return return_val;
}

////////////////////////////////////////////////////////////////////////

/**
 * Inserts the given key into the tree.
 * You must use the proper AVL insertion algorithm.
 * Returns true if the key was inserted successfully, or false if the
 * key was already present in the tree.
 * The time complexity of this function must be O(log n).
 */
bool TreeInsert(Tree t, int key) {

    if (!TreeSearch(t,key) && key != UNDEFINED) {       // checking if not in tree
        t = DoTreeInsert(t,key);    // NULL case checked in DoTreeInsert function
        return true;
    }  
    return false;
}
////////////////////////////////////////////////////////////////////////

/**
 * Deletes the given key from the tree if it is present.
 * You must use the proper AVL deletion algorithm.
 * Returns true if the key was deleted successfully, or false if the key
 * was not present in the tree.
 * The time complexity of this function must be O(log n).
 */
bool TreeDelete(Tree t, int key) {
    
    if (t != NULL && TreeSearch(t,key)) {       //checking null case in the outer function and checking if key exists
        t->root = DoTreeDelete(t->root,key);    // Using auxilliary function to recurse using node 
        return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////

/**
 * Creates a list containing all the keys in the given tree in ascending
 * order.
 * The time complexity of this function must be O(n).
 */
List TreeToList(Tree t) {

    List l = ListNew();
    l = DoTreeToList(t->root,l);    // Using auxilliary function to recurse using node
    return l;
}

////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////

/**
 * Returns the k-th smallest key in the tree.
 * Assumes that k is between 1 and the number of nodes in the tree.
 * k = 1 will return the smallest value in the tree.
 * The time complexity of this function must be O(log n + k).
 */
int TreeKthSmallest(Tree t, int k) {

    Node curr = NULL;
    int count = 0;
    DoTreeKthSmallest(t->root,&curr,k,&count);  //Using auxilliary function to recurse using node and ointer indirection to store values through the recursion 
    return curr->key;
}

////////////////////////////////////////////////////////////////////////

/**
 * Returns the k-th largest key in the tree.
 * Assumes that k is between 1 and the number of nodes in the tree.
 * k = 1 will return the largest value in the tree.
 * The time complexity of this function must be O(log n + k).
 */
int TreeKthLargest(Tree t, int k) {
    
    Node curr = NULL;
    int count = 0;
    DoTreeKthLargest(t->root,&curr,k,&count); //Using auxilliary function to recurse using node and ointer indirection to store values through the recursion
    return curr->key;
}
 
////////////////////////////////////////////////////////////////////////

/**
 * Returns the least common ancestor of two keys, a and b.
 * Returns UNDEFINED if either a or b are not present in the tree.
 * a may be larger than b, or equal to each other.
 * Either a or b may be the LCA in some cases.
 * The time complexity of this function must be O(log n).
 */
int TreeLCA(Tree t, int a, int b) {
    
    if(TreeSearch(t,a) && TreeSearch(t,b)){
        Node curr = NULL;
        DoTreeLCA(t->root,&curr,a,b);
        return curr->key;
    }
    return UNDEFINED;
}
////////////////////////////////////////////////////////////////////////

/**
 * Returns the largest key less than or equal to the given value.
 * Returns UNDEFINED if there is no such key.
 * The time complexity of this function must be O(log n).
 */
int TreeFloor(Tree t, int key) {
    
    Node curr = NULL;
    DoTreeFloor(t->root,&curr,key);
    if (curr == NULL) return UNDEFINED;
    return curr->key;
}

////////////////////////////////////////////////////////////////////////

/**
 * Returns the smallest key greater than or equal to the given value.
 * Returns UNDEFINED if there is no such key.
 * The time complexity of this function must be O(log n).
 */
int TreeCeiling(Tree t, int key) {
    
    Node curr = NULL;
    DoTreeCeiling(t->root,&curr,key);
    if (curr == NULL) return UNDEFINED;
    return curr->key;
}
////////////////////////////////////////////////////////////////////////

/**
 * Searches for all keys between the two given keys (inclusive) and
 * returns the keys in a list in ascending order.
 * Assumes that lower is less than or equal to upper.
 * The time complexity of this function must be O(log n + m), where m is
 * the length of the returned list.
 */
List TreeSearchBetween(Tree t, int lower, int upper) {
    
    List l = ListNew();
    DoTreeSearchBetween(t->root,&l,lower,upper);

    return l;
}

////////////////////////////////////////////////////////////////////////


//*AUXILIARY FUNCTIONS

/**
 * Creates a node with malloc'd memory, assigning the 
 * the data of node to the arguement key.
 * TIME COMPLEXITY O(1)
 */
static Node CreateNode(int key){
    
    Node root = malloc(sizeof(struct node));
    if (root == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    root -> key = key;
    root -> left = NULL;
    root -> right = NULL;
    root-> height = 0;
    return root;
}

/**
 * Uses pointer re-arrangment to rotate a 
 * 'node' pointed to by ptr arguement right 
 * TIME COMEPLEXITY O(1) 
 */
static Node RotateRight(Node root){

    Node new_head = root->left;
    Node new_left = new_head->right;

    root->left = new_left;
    new_head->right = root;

   
    UpdateHeight(root);
    UpdateHeight(new_head);

    return new_head;
}

/**
 * Uses pointer re-arrangment to rotate a 
 * 'node' pointed to by ptr arguement left 
 * TIME COMEPLEXITY O(1) 
 */
static Node RotateLeft(Node root){
    
    Node new_head = root->right;
    Node new_right = new_head->left;

    root->right = new_right;
    new_head->left = root;

    UpdateHeight(root);
    UpdateHeight(new_head);
    
    return new_head;
  
}

/**
 * Getter for Height feild in noden with failsafes in the case where the object is NULL to pretect from segfaults 
 * TIME COMEPLEXITY O(1)
 */
static int Height(Node root){
    if(root == NULL) return -1;
    return root->height;
}

/**
 * Ensures the height of a root node is equal to the highest values of the depths of both left and right subtrees
 * TIME COMEPLEXITY O(1)
 */
static void UpdateHeight(Node root){
    if(root == NULL) return;
    root->height  = 1 + Max(Height(root->left), Height(root->right));
}

/**
 * Return the larger of two numbers
 * TIME COMEPLEXITY O(1)
 */
static int Max(int a, int b){
    return a > b ? a : b;
}

/**
 * Returns balance factor including edge casses where root is null
 * TIME COMEPLEXITY O(1)
 */
static int UpdateBalanceFactor(Node root){
    if (root == NULL) return 0;

    return Height(root->right) - Height(root->left);
}


/**
 * Wrapper function used to 'wrap' a node in a tree structure so that we can use recursive calls for left and right nodes in 
 * multiple functions where arguements are trees. 
 * TIME COMEPLEXITY O(1)
 */
static Tree CreateSubtree(Node root){
    
    Tree t = TreeNew();
    if (t == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    t->root = root;
    return t;
}

/**
 * Used specifically to free the overall tree structure, of tree created by CreateSubtree without freeing the node
 * TIME COMEPLEXITY O(1)
 */
static void FreeSubtree(Tree t){
    
    free(t);
    t = NULL;
}

/**
 * AVL insertion algorithm which return tree with new root 
 * TIME COMEPLEXITY O(log n)
 */
static Tree DoTreeInsert(Tree t ,int key){
    if (t->root == NULL) {
        t->root = CreateNode(key);
        return t;
    }

    Tree t_right = CreateSubtree(right(t));
    Tree t_left = CreateSubtree(left(t));

    if (data(t) < key) right(t) = DoTreeInsert(t_right,key)->root;
    

    else{
        left(t) = DoTreeInsert(t_left,key)->root;
    }



    UpdateHeight(t->root);

    //Balncing based on insert value 
    int balance_factor = UpdateBalanceFactor(t->root);

    if(balance_factor > 1){

        if(key < right(t)->key) right(t) = RotateRight(right(t));

        t->root = RotateLeft(t->root);
    }
    else if(balance_factor < -1){

        if(key > left(t)->key) left(t) = RotateLeft(left(t));

        t->root = RotateRight(t->root);
    }


    FreeSubtree(t_right);
    FreeSubtree(t_left);
    
    return t;
}

/**
 * AVL deletion algorithm which return tree with the given root
 * TIME COMEPLEXITY O(log n + k)
 */
static Node DoTreeDelete(Node root ,int key){

    if (root == NULL) return root;

    if (root->key < key) root->right = DoTreeDelete(root->right,key);
        
    else if (root->key > key) root->left = DoTreeDelete(root->left,key);

    else{
        Node temp = NULL;

        if (root->left == NULL && root->right == NULL) {
            free(root);
            root = NULL;
        }

        else if (root->left == NULL) temp = root->right;

        else if (root->right == NULL) temp = root->left;

        else {
            temp = TreeJoin(root->left,root->right);
        }

        free(root);
        root = temp;

        }

        if (root == NULL) return root;

        UpdateHeight(root);

        int balance_factor = Height(root->right) - Height(root->left);
    
        if (balance_factor > 1) {

            if (UpdateBalanceFactor(root->right) < 0) root->right = RotateRight(root->right);

            root = RotateLeft(root);
        }
        else if (balance_factor < -1) {

            if (UpdateBalanceFactor(root->left) > 0) root->left = RotateLeft(root->left);
        
            root = RotateRight(root);
        }

    return root;
}

/**
 * A function which applies a function p in a post order traversal of the tree
 * TIME COMEPLEXITY O(log n)
 */
static void PostOrder(Node root ,void (*p)()){
    if (root != NULL) {
        PostOrder(root->left,p);
        PostOrder(root->right,p);
        root->right = NULL;
        root->left = NULL;
        p(root);
    }
}

/**
 * Returns joined tree t1 and t2 after deleting a parent node of said subtress thus joining them
 * TIME COMEPLEXITY O(h) => h is height of the left subtree of the right subtree
 */
static Node TreeJoin(Node t1, Node t2){

    if (t1 == NULL) return t2;

    else if (t2 == NULL) return t1;
    
    else{
        Node curr = t2;
        Node parent = NULL;
        
        while (curr->left != NULL){
            parent = curr;
            curr = curr->left;
        }

        if (parent != NULL){
            parent->left = curr->right;
            curr->right = t2;
        }

        curr->left = t1;

        return curr;
    }
}

/**
 * Converts tree to list using in-order traversal
 * TIME COMEPLEXITY O(n) 
 */
static List DoTreeToList(Node root, List l){

    if (root != NULL){
        DoTreeToList(root->left,l);
        ListAppend(l,root->key);
        DoTreeToList(root->right,l);
    }

    return l;
}

/**
 * Returns kth-smallest element in the tree
 * TIME COMEPLEXITY O(log n + k) => h is height of the left subtree of the right subtree and k is size of list
 */
static void DoTreeKthSmallest(Node root, Node* curr, int k, int* counter){
    
    if(root == NULL) return;


    DoTreeKthSmallest(root->left,curr,k,counter); // The use of counter is make sure we found the K-TH smallest element

    (*counter)++;

    if (*counter == k) *curr = root;

    if (*counter != k) DoTreeKthSmallest(root->right,curr,k,counter);

}

/**
 * Returns kth-largest element in the tree
 * TIME COMEPLEXITY O(log n + k) => h is height of the left subtree of the right subtree and k is size of list 
 */
static void DoTreeKthLargest(Node root, Node* curr, int k, int* counter){
    
    if (root == NULL) return;

    DoTreeKthLargest(root->right,curr,k,counter);

    (*counter)++;

    if (*counter == k) *curr = root;

    if (*counter != k) DoTreeKthLargest(root->left,curr,k,counter);


}

/**
 * Finds the lowest common ancestor of between two nodes with values int a and int b
 * TIME COMEPLEXITY O(log n) 
 */
static void DoTreeLCA(Node root, Node* curr, int a, int b){
    if (root == NULL|| *curr != NULL) return;

    if (root->key == a || root->key == b||
            (root->key > a && root->key < b) || (root->key < a && root->key > b)) {
       
        *curr = root;
    }

    DoTreeLCA(root->left,curr,a,b);
    DoTreeLCA(root->right,curr,a,b);
    
}

/**
 * changes the node curr with the value of the node with the largest value less than key.
 * TIME COMEPLEXITY O(log n) 
 */
static void DoTreeFloor(Node root, Node* curr, int key){

    if (root == NULL) return;

    if(root->key <= key && (*curr == NULL || (*curr)->key < root->key)) *curr = root;
    

    if(root->key < key) DoTreeFloor(root->right,curr,key);        
    

    else if(root->key > key) DoTreeFloor(root->left,curr,key);  
    
}

/**
 * changes the node curr with the value of the node with a the smallest value more than key.
 * TIME COMEPLEXITY O(log n) 
 */
static void DoTreeCeiling(Node root, Node* curr, int key){

    if (root == NULL) return;


    if (root->key >= key && (*curr == NULL || (*curr)->key > root->key)) *curr = root;
    

    if (root->key < key) DoTreeCeiling(root->right,curr,key);        
    

    else if (root->key > key) DoTreeCeiling(root->left,curr,key);  
    

}

/**
 * Use in-order traversal to search for values in the range of lower and upper (inclusive)
 * TIME COMEPLEXITY O(log n + m)
 */
static void DoTreeSearchBetween(Node root,List* l,int lower,int upper){
    if (root == NULL) return;

    if (lower < root->key) DoTreeSearchBetween(root->left,l,lower,upper);

    if (lower <= root->key && root->key <= upper) ListAppend(*l,root->key);

    if (upper > root->key) DoTreeSearchBetween(root->right,l,lower,upper);
}

