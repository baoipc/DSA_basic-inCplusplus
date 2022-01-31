#include <iostream>
#include <algorithm>

using namespace std;

class node{
public:
    int data;
    node* left,*right;
    int height;
};

node* newNode(int data)
{
    node* temp = new node();
    temp->data=data;
    temp->left=temp->right=NULL;
    temp->height=1;
    return temp;
}

int height(node* root)
{
    if(root == NULL)
        return 0;
    return root->height;
}
int getBalance(node* root)
{
    if(root == NULL)
        return 0;
    return height(root->left) - height(root->right);
}

node* leftRotate(node* x)
{
    node* y = x->right;
    node* T2 = y->left;

    // Perform rotation
    y->left=x;
    x->right=T2;
    x->height = max(height(x->left),
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    return y;
}

node* rightRotate(node* y)
{
    node* x = y->left;
    node* T2 = x->right;

    // Perform rotation
    x->right=y;
    y->left=T2;

    // y is child of x so update y before
    y->height = max(height(y->left),
                    height(y->right)) + 1;

    x->height = max(height(x->left),
                    height(x->right)) + 1;
    return x;
}

node* Insert(node* root,int data)
{
    if(root==NULL)
        return newNode(data);

    if(data == root->data)
        return root;
    if(data<root->data)
        root->left=Insert(root->left,data);
    if(data>root->data)
        root->right=Insert(root->right,data);

    root->height=1+max(height(root->left),height(root->right));

    int balance = getBalance(root);

    if(balance>1)
    {
        // Left Left Case
        if(data<root->left->data)
            return rightRotate(root);
        // Left Right Case
        if(data>root->left->data)
        {
            root->left=leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if(balance<-1)
    {
        // Right Right Case
        if(data>root->right->data)
            return leftRotate(root);
        // Right Left Case
        if(data<root->right->data)
        {
            root->right=rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}

node* minValueNode(node* root)
{
    node* curr = root;
    while(curr->left)
        curr=curr->left;
    return curr;
}

node* Delete(node* root,int data)
{
    if(root == NULL)
        return root;
    if(data > root->data)
        root->right=Delete(root->right,data);
    else
    {
        if(data < root->data)
            root->left=Delete(root->left,data);
        else
        {
            if(root->left == NULL || root->right == NULL)
            {
                node* temp = root->left != NULL
                            ? root->left
                            : root->right;
                if(temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }else
                    *root = *temp;
                delete temp;
            }else
            {
                node* temp = minValueNode(root);
                root->data = temp->data;
                root->right=Delete(root->right,temp->data);
            }
        }
    }
    if(root == NULL)
        return root;
    root->height = 1 + max(height(root->left),
                           height(root->right));
    int balance = getBalance(root);
    if(balance > 1)
    {
        // Left Left Case
        if(getBalance(root->left)>=0)
            return rightRotate(root);

        // Left Right Case
        if(getBalance(root->left)<0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if(balance < -1)
    {
        // Right Right Case
        if(getBalance(root->right)<=0)
            return leftRotate(root);

        // Right Left Case
        if(getBalance(root->right)>0)
        {
            root->right=rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}

void preOrder(node* root)
{
    if(root!=NULL)
    {
        cout << root->data << ' ';
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main()
{
    return 0;
}
