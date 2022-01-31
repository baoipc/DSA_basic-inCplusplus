#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

class node{
    public:
        int data;
        node* left;
        node* right;
};

node* newNode(int data = 0)
{
    node* temp = new node();
    temp->data=data;
    temp->left = temp->right = NULL;
    return temp;
}

int Diameter(node* root,int* height)
{
    if(root == NULL)
    {
        *height=0;
        return 0;
    }
    // lh --> Height of left subtree
    // rh --> Height of right subtree
    int lh=0;
    int rh=0;

    // ldiameter  --> diameter of left subtree
    // rdiameter  --> Diameter of right subtree
    int ldiameter = 0, rdiameter = 0;

    ldiameter = Diameter(root->left,&lh);
    rdiameter = Diameter(root->right,&rh);

    *height = max(lh,rh)+1;
    return max({lh+rh+1,ldiameter,rdiameter});
}

int maxDepth(node* root)
{
    if(root == NULL)
        return -1;
    int lDepth = maxDepth(root->left);
    int rDepth = maxDepth(root->right);
    return max(lDepth,rDepth)+1;
}

int maxDepth2(node* root)
{
    queue<node*> qu;
    qu.push(root);
    qu.push(NULL);
    int result=0;
    for(node* curr;qu.size();)
    {
        curr = qu.front();
        qu.pop();
        if(curr == NULL)
            result++;
        if(curr!=NULL)
        {
            if(curr->left)
                qu.push(curr->left);
            if(curr->right)
                qu.push(curr->right);
        }else
        {
            if(qu.size())
                qu.push(NULL);
        }
    }
    return result;
}

void PrintKDistant(node* root,int level)
{
    if(level<0 || root == NULL)
        return;
    if(level == 0)
    {
        cout << root->data << ' ';
        return;
    }
    PrintKDistant(root->left,level-1);
    PrintKDistant(root->right,level-1);
}

bool PrintAncestors(node* root,int target)
{
    if(root == NULL)
        return false;
    if(root->data == target)
        return true;
    if(PrintAncestors(root->left,target)||
       PrintAncestors(root->right,target))
    {
        cout << root->data << ' ';
        return true;
    }
    return false;
}

bool areIdentical(node* rootT,node* rootS)
{
    if(rootT == NULL && rootS == NULL)
        return true;
    if(rootT == NULL || rootS == NULL)
        return true;
    return (rootS->data == rootT->data &&
            areIdentical(rootT->left,rootS->left) &&
            areIdentical(rootS->right,rootT->right));
}

bool isSubTree(node* rootT,node* rootS)
{
    if(rootS == NULL || rootT == NULL)
        return true;
    if(areIdentical(rootT,rootS))
        return true;
    return isSubTree(rootT->left,rootS) ||
    isSubTree(rootT->right,rootS);
}

int getMaxWidth(node* root)
{
    if(root == NULL)
        return 0;
    int result=0;
    queue<node*> qu;
    qu.push(root);
    for(node* temp;qu.size();)
    {
        result=max(result,(int)qu.size());
        for(int _n=qu.size();_n;--_n)
        {
            temp = qu.front();
            qu.pop();
            if(temp->left != NULL)
                qu.push(temp->left);
            if(temp->right != NULL)
                qu.push(temp->right);
        }
    }
    return result;
}

void getMaxWidthRecur(node* root,int arr[],int level)
{
    if(root == NULL)
        return;
    ++arr[level];
    getMaxWidthRecur(root->left,arr,level+1);
    getMaxWidthRecur(root->right,arr,level+1);
}

int getMaxWidth2(node* root)
{
    if(root == NULL)
        return 0;
    int h = maxDepth(root);
    int Count[h];
    for(int i=0;i<h;++i)
        Count[i]=0;
    int level=0;
    getMaxWidthRecur(root,Count,level);
    int result=Count[0];
    for(int i=0;i<h;++i)
        result=max(result,Count[i]);
    return result;
}

void PrintPostOrder(node* temp)
{
    if(temp == NULL)
        return;
    PrintPostOrder(temp->left);
    PrintPostOrder(temp->right);
    cout << temp->data << ' ';
}

void PrintPreOrder(node* temp)
{
    if(temp == NULL)
        return;
    cout << temp->data << ' ';
    if(temp->left != NULL)
    PrintPreOrder(temp->left);
    PrintPreOrder(temp->right);
}

void PrintInOrder(node* temp)
{
    if(temp == NULL)
        return;
    PrintInOrder(temp->left);
    cout << temp->data << ' ';
    PrintInOrder(temp->right);
}

void PrintInOrderStack(node* root)
{
    stack<node*> st;
    for(node* temp = root;st.size() || temp != NULL;st.pop())
    {
        while(temp!=NULL)
        {
            st.push(temp);
            temp=temp->left;
        }
        temp=st.top();
        cout << temp->data << ' ';
        temp=temp->right;
    }
}

void MorrisTraversal(node* root)
{
    if(root == NULL)
        return;
    node* curr = root;
    for(node* pre;curr!=NULL;)
    {
        if(curr->left == NULL)
        {
            cout << curr->data << ' ';
            curr = curr->right;
        }else
        {
            pre = curr->left;
            while(pre->right != NULL && pre->right != curr)
                pre = pre->right;
            if(pre->right == NULL)
            {
                pre->right = curr;
                curr=curr->left;
            }else
            {
                pre->right = NULL;
                cout << curr->data << ' ';
                curr=curr->right;
            }
        }
    }
}

void PrintLevelOrder(node* root)
{
    if(root == NULL)
        return;
    queue<node*> qu;
    qu.push(root);
    for(node* temp;qu.size();qu.pop())
    {
        temp = qu.front();
        cout << temp->data << ' ';
        if(temp->left != NULL)
            qu.push(temp->left);
        if(temp->right != NULL)
            qu.push(temp->right);
    }
}

int main()
{
    return 0;
}
