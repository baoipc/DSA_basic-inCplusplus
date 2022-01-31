#include <iostream>

using namespace std;

class node{
public:
    int data;
    node* left,*right;
};

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

int minValue(node* root)
{
    while(root && root->left)
        root=root->left;
    return root->data;
}

void findPreSuc(node* root,node*& pre,node*& suc,int data)
{
    if(root == NULL)
        return;
    if(root->data == data)
    {
        // the maximum value in left subtree is predecessor
        if(root->left!=NULL)
        {
            node* temp = root->left;
            while(temp->right!=NULL)
                temp=temp->right;
            pre = temp;
        }

        // the minimum value in right subtree is successor
        if(root->right!=NULL)
        {
            node* temp = root->right;
            while(temp->left!=NULL)
                temp=temp->left;
            suc = temp;
        }
        return;
    }

    // If key is smaller than root's key, go to left subtree
    if(root->data>data)
    {
        suc=root;
        findPreSuc(root->left,pre,suc,data);
    }else // go to right subtree
    {
        pre=root;
        findPreSuc(root->right,pre,suc,data);
    }
}

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

node* lca(node* root,int n1,int n2)
{
    if(root == NULL)
        return root;
    if(root->data>n1 && root->data>n2)
        return lca(root->left,n1,n2);
    if(root->data<n1 && root->data<n2)
        return lca(root->right,n1,n2);
    return root;
}

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
}

void PrintInorder(node* root)
{
    if(root == NULL)
        return;
    PrintInorder(root->left);
    cout << root->data << ' ';
    PrintInorder(root->right);
}

int main()
{
    return 0;
}
