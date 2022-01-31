#include <iostream>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class node{
    public:
        int data;
        node *next,*prev;
};

void Insert1(node** head,int data)
{// Add a node at the front
    node* temp = new node();

    temp->data=data;
    temp->next=(*head);
    temp->prev=NULL;

    if(*head != NULL)
        (*head)->prev = temp;
    *head = temp;
}

void Insert2(node* prev_node,int data)
{// Add a node when given a node
    if(prev_node == NULL)
        return;
    node* temp = new node();
    temp->data = data;
    temp->next = prev_node->next;
    prev_node->next = temp;
    temp->prev = prev_node;
    if(temp->next != NULL)
        temp->next->prev = temp;
}

void Insert3(node** head,int data)
{ // Add a node at the end of DLL
    if(head == NULL)
        return;
    node* last = (*head);
    node* temp = new node();
    temp->data = data;
    temp->next = NULL;
    if(*head == NULL)
    {
        temp->prev = NULL;
        *head = temp;
        return;
    }
    while(last->next != NULL)
        last=last->next;
    last->next = temp;
    temp->prev = last;
}

void Insert4(node* head,int data)
{ // Add a node before a given node
    if(head == NULL)
        return;
    node* temp = new node();
    temp->data = data;
    temp->next = head->next;
    head->next = temp;
    temp->prev = head;
    if(temp->next!= NULL)
        temp->next->prev = temp;
}

void Delete(node** head,node* del)
{
    if((*head) == NULL || del == NULL)
        return;
    if((*head) == del)
        *head = del->next;
    if(del->next != NULL)
        del->next->prev = del->prev;
    if(del->prev != NULL)
        del->prev->next = del->next;
    delete del;
}

void deleteNodeAtGivenPos(node** head,int position)
{ // Position start from 1
    if((*head) == NULL || position<=0)
        return;
    node* curr = *head;
    int i;
    for(i=1;curr!=NULL && i<position;++i)
        curr=curr->next;
    if(curr == NULL)
        return;
    Delete(head,curr);
}

void removeDuplicates(node** head)
{
    if(*head == NULL)
        return;
    node* curr = *head;
    while(curr->next!=NULL)
    {
        if(curr->data == curr->next->data)
        {
            Delete(head,curr->next);
        }else
            curr=curr->next;
    }
}

void removeDuplicates2(node** head)
{// version not sorted
    if(*head == NULL)
        return;
    unordered_set<int> us;
    node* curr =*head,*next;
    while(curr!=NULL)
    {
        if(us.find(curr->data) != us.end())
        {
            next = curr->next;
            Delete(head,curr);
            curr = next;
        }else
        {
            us.insert(curr->data);
            curr=curr->next;
        }
    }
}

void deleteAllOccurOfX(node** head,int data)
{
    if(*head == NULL)
        return;
    node* curr = *head;
    while(curr->next!=NULL)
    {
        if(curr->data == data)
        {
            node* next = curr->next;
            Delete(head,curr);
            curr=next;
        }else
            curr=curr->next;
    }
}

void Reverse(node** head)
{
    node* temp = NULL;
    node* curr = *head;
    while(curr != NULL)
    {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr=curr->prev;
    }
    /* Before changing the head, check for the cases like empty
        list and list with only one node */
    if(temp!=NULL)
        *head = temp->prev;
}

void Reverse2(node* head)
{
    stack<int> st;
    node* temp = head;
    while(temp!=NULL)
    {
        st.push(temp->data);
        temp=temp->next;
    }
    temp = head;
    while(temp!=NULL)
    {
        temp->data = st.top();
        st.pop();
        temp=temp->next;
    }
}

void Swap(int* a,int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

node* Partition(node* l,node* r)
{
    int data = r->data;
    node* i = l->prev;
    for(node* j = l;j!=r;j = j->next)
    {
        if(j->data<=data)
        {
            i = (i==NULL) ? l : i->next;
            Swap(&(i->data),&(j->data));
        }
    }
    i = (i==NULL) ? l : i->next;
    Swap(&(i->data),&(r->data));
    return i;
}

void _quicksort(node* l,node* r)
{
    if(l!= NULL && r!=NULL && l!=r->next && l!=r)
    {
        node* mid = Partition(l,r);
        _quicksort(l,mid->prev);
        _quicksort(mid->next,r);
    }
}

node* lastnode(node* head)
{
    while(head!=NULL && head->next!=NULL)
        head=head->next;
    return head;
}

void quickSort(node* head)
{
    node* last = lastnode(head);
    _quicksort(head,last);
}

node* spilt(node* head)
{
    node* first = head;
    node* second = head;
    while(first->next && first->next->next)
    {
        first=first->next->next;
        second=second->next;
    }
    node* result = second->next;
    second->next=NULL;
    return result;
}

// Function to merge two linked lists
node* _merge(node* first,node* second)
{
    if(!first)
        return second;
    if(!second)
        return first;
    if(first->data<second->data)
    {
        first->next=_merge(first->next,second);
        first->next->prev=first;
        first->prev=NULL;
        return first;
    }else
    {
        second->next=_merge(first,second->next);
        second->next->prev=second;
        second->prev=NULL;
        return second;
    }
}

node* mergeSort(node* head)
{
    if(!head || !head->next)
        return head;
    node* last = spilt(head);

    // Recur for left and right halves
    head = mergeSort(head);
    last = mergeSort(last);

    // Merge the two sorted halves
    return _merge(head,last);
}

void pairSum(node* head,int data)
{
    node* first = head;
    node* second = lastnode(head);
    bool found = false;
    while(first != second && second->next != first)
    {
        if((first->data + second->data) == data)
        {
            found = true;
            cout << "(" << first->data<< ", " << second->data << ")" << endl;
            // move first in forward direction
            first = first->next;
            // move second in backward direction
            second = second->prev;
        }else
        {
            if((first->data+second->data)>data)
                second=second->prev;
            else
                first=first->next;
        }
    }
    if(found == false)
        cout << "No pair found\n";
}

node* getNode(node* new_node,int data)
{
    new_node = new node();
    new_node->data=data;
    new_node->prev=NULL;
    new_node->next=NULL;
    return new_node;
}

void sortedInsert(node** head,node* new_node)
{
    if(*head == NULL)
        *head = new_node;
    else
    {
        if((*head)->data >= new_node->data)
        {
            new_node->next = *head;
            new_node->next->prev = new_node;
            *head = new_node;
        }else
        {
            node* curr = *head;
            while(curr->next != NULL & curr->next->data<new_node->data)
                curr=curr->next;
            new_node->next=curr->next;
            if(curr->next!=NULL)
                new_node->next->prev=new_node;
            curr->next=new_node;
            new_node->prev=curr;
        }
    }
}

int countTriplets(node* head,int sum)
{
    int result=0;
    unordered_map<int,node*> um;
    for(node* ptr=head;ptr!=NULL;ptr=ptr->next)
        um[ptr->data]=ptr;
    for(node* p1=head;p1!=NULL;p1=p1->next)
    {
        for(node* p2=p1->next;p2!=NULL;p2=p2->next)
        {
            int currentSum = p1->data+p2->data;
            if(um.find(sum-currentSum)!=um.end() && um[sum-currentSum]!=p1 && um[sum-currentSum]!=p2)
                ++result;
        }
    }
    return result/3;
}

int countPairs(node* st,node* en,int sum)
{
    int result=0;

    // The loop terminates when either of two pointers become NULL, or they cross each other
    while(st!=NULL && en!=NULL && st!=en && en->next != st)
    {
        if(st->data+en->data == sum)
        {
            ++result;
            st=st->prev;
            en=en->next;
        }else
        {
            if(st->data+en->data>sum)
                st=st->prev;
            else
                en=en->next;
        }
    }
    return result;
}

int countTriplets2(node* head,int sum)
{
    if(head == NULL)
        return 0;
    int result=0;
    node* last=head;
    while(last->next!=NULL)
        last=last->next;
    for(node* curr=head,*first;curr;curr=curr->next)
    {
        first=curr->next;
        result+=countPairs(first,last,sum-curr->data);
    }
    return result;
}

void rotateN(node*& head,int position)
{
    if(position == 0)
        return;
    node* last = head;
    while(last->next!= NULL)
        last=last->next;
    last->next=head;
    head->prev=last;
    int cnt=1;
    while(cnt<=position)
    {
        head=head->next;
        last=last->next;
        ++cnt;
    }
    last->next=NULL;
    head->prev=NULL;
}

void push(node** head,node* newNode)
{ // insert a node at the beginning
    newNode->prev=NULL;
    newNode->next=*head;
    if(*head!=NULL)
        (*head)->prev=newNode;
    *head=newNode;
}

node* revListInGroupOfGivenSize(node* head,int k)
{
    node* curr = head;
    node* next = NULL;
    node* newHead = NULL;
    int cnt = 0;
    while(curr!=NULL && cnt<k)
    {
        next=curr->next;
        push(&newHead,curr);
        curr=next;
        ++cnt;
    }
    if(next!=NULL)
    {
        head->next = revListInGroupOfGivenSize(next,k);
        head->next->prev=head;
    }
    newHead->prev=NULL;
    return newHead;
}

int GetSize(node* head)
{
    int result=0;
    while(head)
    {
        ++result;
        head=head->next;
    }
    return result;
}

void PrintList(node* curr)
{
    while(curr != NULL)
    {
        cout << curr->data << ' ';
        curr = curr->next;
    }
}

int main()
{
    return 0;
}
