//
//  binarySearchFunctions.h
//  ProjectTwo - Binary Search Tree
//
//  Created by Chip Brommer on 3/8/19.
//  Copyright © 2019 Chip Brommer. All rights reserved.
//

#ifndef binarySearchFunctions_h
#define binarySearchFunctions_h

#include <cstdlib>
#include <fstream>

using namespace std;

//Defining the node for the tree
struct node
{
    int key;
    struct node *left;
    struct node *right;
    struct node *parent;
};

//Function to create a new node
node* newNode(int key)
{
    node* tempNode = new node();
    tempNode->key = key;
    tempNode->left = NULL;
    tempNode->right = NULL;
    tempNode->parent = NULL;
    
    return tempNode;
}

//-------------------------------------------------------------------------------------------------
//insertNode - This function allows the program and user to insert nodes into the tree. If the
//              value being entered is smaller, it goes to the left. Larger goes to the right.
//-------------------------------------------------------------------------------------------------
node* insertNode(node* root, int key)
{
    //If the tree is empty, create a new node and set it equal to root
    if (root == NULL)
    {
        root = newNode(key);
    }
    //Root is not null, looking down the tree
    else if (key <= root->key)
    {
        node *leftLeaf = insertNode(root->left, key);
        root->left  = leftLeaf;
        
        // Set parent of root of left leaf
        leftLeaf->parent = root;
    }
    else if (key > root->key)
    {
        node *rightLeaf = insertNode(root->right, key);
        root->right = rightLeaf;
        
        // Set parent of root of right leaf
        rightLeaf->parent = root;
    }
    
    // return the root. 
    return root;
}

//-------------------------------------------------------------------------------------------------
//findNode - This function will check if a specified number is in the tree. if it is, returns true,
//           else it will return false.
//-------------------------------------------------------------------------------------------------
bool findNode(node* root, int key)
{
    //If the node recieved is NULL = list is empty.
    if(root == NULL)
    {
        return false;
    }
    if(root->key == key) // If the value in the recieving node is what we are searching for, true.
    {
        return true;
    }
    bool left = findNode(root->left, key); //Recursive call for left side.
    
    bool right = findNode(root->right, key); //Recursive call for right side.
    
    //returning left or right, which ever one finds the value.
    return left || right;
}

//-------------------------------------------------------------------------------------------------
//deleteNode - This function will delete a desired node from the tree. If the node has children, it
//             will move them accordinly.
//-------------------------------------------------------------------------------------------------
node * deleteNode(node* root, int key)
{
    //List is empty.
    if (root == NULL)
    {
        return root;
    }
    
    //If the key is smaller than the value of the root, then the value searched is on the left.
    //We then recursively call this function again.
    if (key < root->key)
    {
        root->left = deleteNode(root->left, key);
        return root;
    }
    
    //If the key is bigger than the value of the root, then the value searched is on the right.
    //We then recursively call this function again.
    else if (key > root->key)
    {
        root->right = deleteNode(root->right, key);
        return root;
    }
   
    //Value is found.
    //If the node with desired value only has a right leaf, create a temp node with the child value
    //and then use it to replace the current node we are deleting.
    if (root->left == NULL)
    {
        node* temp = root->right;
        delete root; //Deleting desired value
        return temp; //Returning the only leaf in a temp node
    }
    //If the node with desired value only has a left leaf, create a temp node with the leaf value
    //and then use it to replace the current node we are deleting.
    else if (root->right == NULL)
    {
        node* temp = root->left;
        delete root; //Deleting desired value
        return temp; //Returning the only leaf in a temp node
    }
    
    //The node desired has 2 children. Therefor we need to store each leaf and move then accordingly before deleting
    else
    {
        //Setting the temporary parent node to the nodes higher value.
        node* successorParent = root->right;
        
        //Grabbing the successor from the right child
        node* successor = root->right;
        
        //Setting successorParent (node that is swithcing places, to the right be moved equal to the deleted nodes right leaf
        while (successor->left != NULL)
        {
            successorParent = successor;
            successor = successor->left;
        }
        
        //Setting the lower value(right lead of successor to the left side of the parent.
        successorParent->left = successor->right;
        
        // Copy Successor Data to the root
        root->key = successor->key;
        
        // Delete Successor and return root
        delete successor;
        return root;
    }
}

//-------------------------------------------------------------------------------------------------
//treeTraversal - This function will print a tree starting at the left most element and then print
//                the right most element.
//-------------------------------------------------------------------------------------------------
void treeTraversal(node *root)
{
    //if the root is not null, recurse and print.
    if (root != NULL)
    {
        //Recursive call for the left most element.
        treeTraversal(root->left);
        
        //printing the node and its parent.
        printf("Node: %d, ", root->key);
        
        //If the parent is null, its our root element.
        if (root->parent == NULL)
        {
            printf("Parent: NULL \n");
        }
        else //Node has a parent, prints its value.
        {
            printf("Parent: %d \n", root->parent->key);
        }
        
        //recursive call to the right most element. 
        treeTraversal(root->right);
    }
}

//-------------------------------------------------------------------------------------------------
//standardPrint - This function prints the tree in a standard one line with a space between the numbers
//-------------------------------------------------------------------------------------------------
void standardPrint(node *root, fstream& mytxtfile)
{
    //If the root is not NULL
    if (root != NULL)
    {
        //Recursive call to print the left most element first.
        standardPrint(root->left, mytxtfile);
        
        cout << root->key << " ";               //Spacer
        mytxtfile << root->key << " ";          //file spacer
        
        //Recursive call to print the right most element first.
        standardPrint(root->right, mytxtfile);
    }
}

//-------------------------------------------------------------------------------------------------
//maximumValue - This function will look at a node, if it has a right, it must be larger and there
//               for will continue to check until there is no right most node. At that point, we
//               should have the highest value.
//-------------------------------------------------------------------------------------------------
int maximumValue(node* root)
{
    struct node* maxNode = root;
    
    //Looping for the right most node
    while (maxNode->right != NULL)
    {
        maxNode = maxNode->right;
    }
    
    return(maxNode->key);
}

//-------------------------------------------------------------------------------------------------
//minimumValue - This function will look at a node, if it has a left child, it must be smaller. We
//               will continue to check until there is no left most node. At that point, we
//               should have the lowest value.
//-------------------------------------------------------------------------------------------------
int minimumValue(node* root)
{
    node* minNode = root;
    
    //loop down to find the leftmost leaf
    while (minNode->left != NULL)
    {
        minNode = minNode->left;
    }
    return(minNode->key);
}

//-------------------------------------------------------------------------------------------------
//minimumValue - This function will look at a node, if it has a left child, it must be smaller. We
//               will continue to check until there is no left most node. At that point, we
//               should have the lowest node. Returns the entire node.
//-------------------------------------------------------------------------------------------------
node * minimumNode(struct node* root)
{
    node * temp = root;
    
   //Looping until we find the smallest value.
    while (temp->left != NULL)
    {
        temp = temp->left;
    }
    return temp;
}

//-------------------------------------------------------------------------------------------------
//nodeSearch - This function recieves a value from the user and the root node, it will then find
//             the node with the desired value and return the node. This function will be used
//             with the findSuccessor function.
//-------------------------------------------------------------------------------------------------

node * nodeSearch(node* root, int input)
{
    //Checking if the value in input == the root value. If so, we return the node.
    if(root->key == input)
    {
        return root;
    }
    // The value is greater than current node's key
    else if(root->key < input)
    {
        return nodeSearch(root->right, input);
    }
    // The value is smaller than current node's key
    else
    {
        return nodeSearch(root->left, input);
    }
}

//-------------------------------------------------------------------------------------------------
//findSuccessor - This function will find the successor of a given value in a tree.
//-------------------------------------------------------------------------------------------------
node * findSuccessor(node* root, node* input)
{
    //Searching the right child for a right most value.
    if( input->right != NULL )
    {
        return minimumNode(input->right);
    }
    
    //Looking at the predecessor value from the input node(one we are searching for its successor)
    node *successor = input->parent;
    while(successor != NULL && input == successor->right)
    {
        input = successor;
        successor = successor->parent;
    }
    return(successor);
}

//-------------------------------------------------------------------------------------------------
//findSuccessor - This function will find the predeccessor of a given value in a tree.
//-------------------------------------------------------------------------------------------------
node * findPredecessor(node* root, node* input)
{
    // If right child exists, then it is the predecessor.
    if (input->right)
    {
        return input->right;
    }
    
    //Here because no right child exists, so we will travel up to the parent node until we reach a node that
    //has a right child.
    node * temp = input;
    node * parent = temp->parent;
    
    while (parent != NULL && parent->left == temp)
    {
        temp = temp->parent;
        parent = parent->parent;
    }
    
    // If we reach the root, then the given node has no postorder predecessor
    if (parent == NULL)
    {
        return NULL;
    }
    
    return parent->left;
}
#endif /* binarySearchFunctions_h */
