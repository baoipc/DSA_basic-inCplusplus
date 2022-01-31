# Binary Search Tree

Binary Search Tree is a node-based binary tree data structure which has the following properties:  

The left subtree of a node contains only nodes with keys lesser than the node’s key.
The right subtree of a node contains only nodes with keys greater than the node’s key.
The left and right subtree each must also be a binary search tree.
There must be no duplicate nodes.

![image introduce Binary Search Tree](image/image_Introduce.png)

The above properties of Binary Search Tree provides an ordering among keys so that the operations like search, minimum and maximum can be done fast. If there is no ordering, then we may have to compare every key to search for a given key.

**Searching a key**:

Search operations in binary search tree will be very similar. Let’s say we want to search for the number, we start at the root, and then we compare the value to be searched with the value of the root, if it’s equal we are done with the search if it’s smaller we know that we need to go to the left subtree because in a binary search tree all the elements in the left subtree are smaller and all the elements in the right subtree are larger. Searching an element in the binary search tree is basically this traversal, at each step we go either left or right and at each step we discard one of the sub-trees. If the tree is balanced (we call a tree balanced if for all nodes the difference between the heights of left and right subtrees is not greater than one) we start with a search space of ‘n’ nodes and as we discard one of the sub-trees, we discard ‘n/2’ nodes so our search space gets reduced to ‘n/2’. In the next step we reduce the search space to ‘n/4’ and we repeat until we find the element or our search space is reduced to only one node. The search here is also a binary search hence the name; Binary Search Tree.

```c++
node* search(node* root, int key)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->key == key)
       return root;
    
    // Key is greater than root's key
    if (root->key < key)
       return search(root->right, key);
 
    // Key is smaller than root's key
    return search(root->left, key);
}
```

**Insertion of a key**:
A new key is always inserted at the leaf. We start searching a key from the root until we hit a leaf node. Once a leaf node is found, the new node is added as a child of the leaf node.

```Example
       100                               100
        /   \        Insert 40            /    \
      20     500    --------->          20     500 
     /  \                              /  \  
    10   30                           10   30
                                              \   
                                              40
```

```c++
node* newNode(int data)
{
    node* temp = new node();
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

node* Insert(node* root,int data)
{
    if(root == NULL)
        return newNode(data);
    if(data > root->data)
        root->right = Insert(root->right,data);
    else
        root->left = Insert(root->left,data);
    return root;
}
```

Time Complexity: The worst-case time complexity of search and insert operations is O(h) where h is the height of the Binary Search Tree. In the worst case, we may have to travel from root to the deepest leaf node. The height of a skewed tree may become n and the time complexity of search and insert operation may become O(n).

**Delete a key**: When we delete a node, three possibilities arise

**1) Node to be deleted is the leaf**: Simply remove from the tree.

```Example
              50                            50
           /     \         delete(20)      /   \
          30      70       --------->    30     70 
         /  \    /  \                     \    /  \ 
       20   40  60   80                   40  60   80
```

**2) Node to be deleted has only one child**: Copy the child to the node and delete the child

```Example
              50                            50
           /     \         delete(30)      /   \
          30      70       --------->    40     70 
            \    /  \                          /  \ 
            40  60   80                       60   80
```

**3) Node to be deleted has two children**: Find inorder successor of the node. Copy contents of the inorder successor to the node and delete the inorder successor.

```Example
              50                            60
           /     \         delete(50)      /   \
          40      70       --------->    40    70 
                 /  \                            \ 
                60   80                           80
```

```c++
node* minValuenode(node* root)
{
    while(root!= NULL && root->left!=NULL)
        root=root->left;
    return root;
}

node* Delete(node* root,int data)
{
    if(root == NULL)
        return NULL;
    if(data>root->data)
        root->right=Delete(root->right,data);
    else
    {
        if(data<root->data)
            root->left=Delete(root->left,data);
        else
        {
            if(root->left == NULL && root->right == NULL)
                return NULL;
            if(root->left == NULL)
            {
                node* temp = root->right;
                delete root;
                return temp;
            }else
            {
                if(root->right == NULL)
                {
                    node* temp = root->left;
                    delete root;
                    return temp;
                }
            }
            node* temp = minValuenode(root->right);
            root->data = temp->data;
            root->right=Delete(root->right,temp->data);
        }
    }
}
```

**Time Complexity**: The worst case time complexity of delete operation is O(h) where h is the height of the Binary Search Tree. In worst case, we may have to travel from the root to the deepest leaf node. The height of a skewed tree may become n and the time complexity of delete operation may become O(n)

## Find the node with minimum value in a Binary Search Tree

```c++
int minValue(node* root)
{
    while(root && root->left)
        root=root->left;
    return root->data;
}
```

**Time Complexity**: O(n) Worst case happens for left skewed trees.

## Inorder predecessor and successor for a given key in BST

You need to find the inorder successor and predecessor of a given key. In case the given key is not found in BST, then return the two values within which this key will lie.

```Algorithm
1. If root is NULL
      then return
2. if key is found then
    a. If its left subtree is not null
        Then predecessor will be the right most 
        child of left subtree or left child itself.
    b. If its right subtree is not null
        The successor will be the left most child 
        of right subtree or right child itself.
    return
3. If key is smaller then root node
        set the successor as root
        search recursively into left subtree
    else
        set the predecessor as root
        search recursively into right subtree
```

```c++
void findPreSuc(node* root,node*& pre,node*& suc,int data)
{
    if(root == NULL)
        return;
    if(root->data == data)
    {
        if(root->left!=NULL)
        {
            node* temp = root->left;
            while(temp->right!=NULL)
                temp=temp->right;
            pre = temp;
        }
        if(root->right!=NULL)
        {
            node* temp = root->right;
            while(temp->left!=NULL)
                temp=temp->left;
            suc = temp;
        }
        return;
    }
    if(root->data>data)
    {
        suc=root;
        findPreSuc(root->left,pre,suc,data);
    }else
    {
        pre=root;
        findPreSuc(root->right,pre,suc,data);
    }
}
```

## A program to check if a binary tree is BST or not

**METHOD 1 (Simple but Wrong)**:

```c
int isBST(struct node* node)
{
if (node == NULL)
    return 1;

/* false if left is > than node */
if (node->left != NULL && node->left->data > node->data) 
    return 0;

/* false if right is < than node */
if (node->right != NULL && node->right->data < node->data) 
    return 0;

/* false if, recursively, the left or right is not a BST */
if (!isBST(node->left) || !isBST(node->right)) 
    return 0;

/* passing all that, it's a BST */
return 1;
}
```

**METHOD 2 (Correct but not efficient)**: For each node, check if max value in left subtree is smaller than the node and min value in right subtree greater than the node.

```c
/* Returns true if a binary tree is a binary search tree */
int isBST(struct node* node)
{
if (node == NULL)
    return 1;

/* false if the max of the left is > than us */
if (node->left != NULL && maxValue(node->left) >= node->data)
    return 0;

/* false if the min of the right is <= than us */
if (node->right != NULL && minValue(node->right) <= node->data)
    return 0;

/* false if, recursively, the left or right is not a BST */
if (!isBST(node->left) || !isBST(node->right))
    return 0;

/* passing all that, it's a BST */
return 1;
}

```

It is assumed that you have helper functions minValue() and maxValue() that return the min or max int value from a non-empty tree

**METHOD 3 (Correct and Efficient)**:

The trick is to write a utility helper function `isBSTUtil (node* node, int min, int max)` that traverses down the tree keeping track of the narrowing min and max allowed values as it goes, looking at each node only once. The initial values for min and max should be `INT_MIN` and `INT_MAX`.

Note: This method is not applicable if there are duplicate elements with value INT_MIN or INT_MAX.

```c++
bool isBSTUtil(node* root,int Min,int Max)
{
    if(root == NULL)
        return 1;
    if(root->data < Min || root->data > Max)
        return 0;
    return
        isBSTUtil(root->left,Min,root->data-1) &&
        isBSTUtil(root->right,root->data+1,Max);
}

bool isBST(node* root)
{
    return isBSTUtil(root,INT_MIN,INT_MAX);
}
```

**Time Complexity**: O(n)
**Auxiliary Space**: O(1) if Function Call Stack size is not considered, otherwise O(n)

## Lowest Common Ancestor in a Binary Search Tree

Given values of two values n1 and n2 in a Binary Search Tree, find the **L**owest **C**ommon **A**ncestor (LCA). You may assume that both the values exist in the tree.

![image Example Tree of LCA](image/image_LCA.gif)

```Example
Input: LCA of 10 and 14
Output:  12
Explanation: 12 is the closest node to both 10 and 14 
which is a ancestor of both the nodes.

Input: LCA of 8 and 14
Output:  8
Explanation: 8 is the closest node to both 8 and 14 
which is a ancestor of both the nodes.

Input: LCA of 10 and 22
Output:  20
Explanation: 20 is the closest node to both 10 and 22 
which is a ancestor of both the nodes.
```

**Algorithm**:  

- Create a recursive function that takes a node and the two values n1 and n2.
- If the value of the current node is less than both n1 and n2, then LCA lies in the right subtree. Call the recursive function for the right subtree.
- If the value of the current node is greater than both n1 and n2, then LCA lies in the left subtree. Call the recursive function for the left subtree.
- If both the above cases are false then return the current node as LCA.

```c++
node* lca(node* root,int n1,int n2)
{
    if(root == NULL)
        return root;
    if(root->data>n1 && root->data>n2)
        return(root->left,n1,n2);
    if(root->data<n1 && root->data<n2)
        return(root->right,n1,n2);
    return root;
}
```

**Time Complexity**: O(h).
The time Complexity of the above solution is O(h), where h is the height of the tree.
**Space Complexity**: O(h).
If recursive stack space is ignored, the space complexity of the above solution is constant.

## Find k-th smallest element in BST (Order Statistics in BST)

Given the root of a binary search tree and K as input, find Kth smallest element in BST.

```Example
For example, in the following BST, 
if k = 3, then the output should be 10, 
and if k = 5, then the output should be 14.
```

![image Example BST](image/image_LCA.gif)

**Using Inorder Traversal**: While traversing, keep track of the count of the nodes visited. If the count becomes k, print the node

```c++
node* kthSmallest(node* root,int k)
{
    if(root == NULL)
        return NULL;
    node* left=kthSmallest(root->left,k);
    if(left != NULL)
        return left;
    --k;
    if(k == 0)
        return root;
    return kthSmallest(root->right,k);
}`
```

**Time Complexity**: O(n)
**Space Complexity**: O(h)
