/*
链表常见算法题
1.链表的逆置
2.从尾到头打印链表
3.判断链表是否有环
4.找链表中的第k个节点
6.寻找两个链表的第一个公共节点
5.合并两个有序的链表
5.将一颗二叉排序树转成一个有序的双向链表


*/
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

typedef struct ListNode
{
    int value;
    ListNode * p_next;
}ListNode;

//链表的逆置
ListNode* ReverseList(ListNode *phead)
{
    if(phead == NULL)
        return NULL;
    ListNode *pre = phead;
    ListNode *pcur = phead->p_next;
    ListNode *pnext = NULL;
    ListNode * preversehead = NULL;
    while (pcur != NULL)
    {
        pnext = pcur->p_next;
        pcur->p_next = pre;
        pre = pcur;
        pcur = pnext;
        /* code */
    }
    phead->p_next = NULL;
    preversehead = pre; 
    return preversehead;
}

//从尾到头打印链表
/*
思路1：可以采用栈，因为这个栈先进后出，很适合这个场景
*/
void ReversePrint(ListNode *phead)
{
    stack<int> mystack;
    ListNode *p = phead;
    while (p!=NULL)
    {
        mystack.push(p->value);
        p=p->p_next;
    }
    while (!mystack.empty())
    {
        int value = mystack.top();
        cout<<value<<" ";
        mystack.pop();
    }
    cout << endl;
}

/*
思路2:可以利用递归的思路，递归和栈很相似
*/
void ReversePrint2(ListNode *phead)
{
   if(phead !=NULL)
   {
       if(phead->p_next != NULL)
            ReversePrint2(phead->p_next);
   }
    cout<<phead->value<<" ";
}

//判断链表是否有环
/*
思路：判断链表是否有环的思路：
1.假定这个链表的长度是一定的，如果一直走，一直走，他的next指针为空的话，那就说明他没环，否则一直走不停的话，那说明有环，我们可以设定个时间
但是这个办法太笨了，而且不是足够准确的
2.可以利用set，这种结构，每次遍历链表时把节点存到set中，遍历下一个时候在set中看一下是否有，有就说明
已经被访问过了，说明是有环的，否则，当链表都走完了，并无重复的，说明链表没有环，这样的话时间复杂度 O(n)，空间复杂度：O（n）

3.更好的办法可以利用我们的快慢指针，就像我们的环型操场跑步一样，跑的快的和跑的慢的总会相遇的，因为有环
  如果说我们的跑的快的都跑到尽头了，即他的next指针都指向null了，那就说明没环，单程线
*/
bool IsCircleList(ListNode *phead)
{
    ListNode * slow = phead;
    ListNode * fast = phead;
    bool is_circle = false;
    while(slow && fast && fast->p_next)
    {
        fast = fast->p_next->p_next;
        slow = slow->p_next;
        if(fast == slow)
            is_circle = true;
            break;
    }

    return is_circle;
}

int GetListLenth(ListNode *phead)
{
    int lenth =0 ;
    ListNode *p = phead;
    while (p != NULL)
    {
        lenth++;
        p = p->p_next;
    }
    return lenth;  
}

//找链表倒数第k个节点
/*
思路：
如果我们知道链表长度，那么只需要走n-k+1步，就可以找到我们的倒数第k个节点，这样需要遍历链表两次
如果只遍历链表一遍，可以利用快慢指针来解决，先让快指针走k-1步，然后快慢指针再同时走，这样慢指针
就是走 n-(k-1)=n-k+1,走完这些步，此时链表所指向的节点就是我们的倒数第k个节点

注意：要注意代码的鲁棒行
1.如果这个链表为空，怎么处理，如果找倒数第0个或负数个怎么处理，因为我们是按1开始的，如果这个k超出
了链表的长度，没有这个节点怎么处理
*/

ListNode * FindNodek(ListNode *phead, int k)
{
    if(phead == NULL || k < 1)
        return NULL;
    ListNode * slow = phead;
    ListNode *fast = phead;
    int i =0;
    for(;i<(k-1); i++)
    {
        if(fast->p_next != NULL)
        {
            fast = fast->p_next;
        }
        else
        {
            return NULL;
        }     
    }
    while(fast->p_next != NULL)
    {
        fast = fast->p_next;
        slow = slow->p_next;
    }
    return slow;
}

ListNode * SetCircle(ListNode * phead)
{
    ListNode *p = phead;
    while (p->p_next != NULL)
    {
        p=p->p_next;
    }
    p->p_next = phead;
    return p;

}
//寻找两个链表的第一个公共节点
/*
思路：


*/


//合并两个有序的链表
/*
思路：在可以改变原链表的结构的情况下，我想的是利用4个指针，两个指针分别来遍历两个链表，
一个指针执行当前需要合并进链表的最新节点，一个指针用来记录新链表的头
*/

ListNode * MergeList(ListNode *phead1, ListNode *phead2)
{
    ListNode *pnew_head = NULL;
    if(phead1 == NULL)
        return phead2;
    if(phead2 == NULL)
        return phead1;
    ListNode * p1 = phead1;
    ListNode * p2 = phead2;
    ListNode * pcur = NULL;
    if(p1->value < p2->value)
    {
        pnew_head = p1;
        pcur = p1;
        p1=p1->p_next;
    }
    else
    {
        pnew_head = p2;
        pcur = p2;
        p2 = p2->p_next;
    }
    while(p1 != NULL && p2 != NULL)
    {
        if(p1->value <= p2->value)
        {
            pcur->p_next = p1;
            pcur=p1;
            p1 = p1->p_next;
        }
        else
        {
            pcur->p_next = p2;
            pcur=p2;
            p2 = p2->p_next;
        }    
    }

    //如果phead1比phead2长或者phead2比phead1长
    if(p1 != NULL  && p2 == NULL)
    {
        pcur->p_next = p1;
    }
    else if(p1 == NULL  && p2 != NULL)
    {
        pcur->p_next = p2;
    }
    
    return pnew_head;
}

//将一颗二叉排序树转成一个有序的双向链表


void PrintList(ListNode * phead)
{
    ListNode *p = phead;
    while (p != NULL)
    {
        cout<<p->value<<" ";
        p=p->p_next;
    }
    cout<<endl; 
}

ListNode* CreateList1(ListNode *phead)
{
    for(int i=0; i<5; i++)
    {
        ListNode *node = new ListNode;
        node->value = i*2;
        node->p_next = phead;
        phead = node;
    }
    return phead;
}

ListNode* CreateList2(ListNode *phead)
{
    for(int i=0; i<5; i++)
    {
        ListNode *node = new ListNode;
        node->value = i;
        node->p_next = phead;
        phead = node;
    }
    return phead;
}

int main()
{
    ListNode * phead1 = NULL;
    ListNode * phead2 = NULL;
    phead1 = CreateList1(phead1);
    phead2 = CreateList2(phead2);
    phead1 = ReverseList(phead1);
    phead2 = ReverseList(phead2);
    PrintList(phead1);
    PrintList(phead2);
    ListNode * pnew_head = MergeList(phead1, phead2);
    PrintList(pnew_head);
    //ListNode *cirhead = SetCircle(phead);
    //cout<<IsCircleList(cirhead)<<endl;
    //cout<<"end"<<endl;
    //ReversePrint(phead);
    //ReversePrint2(phead);
    //ListNode * preversehead = ReverseList(phead);
    //PrintList(preversehead);
    //ListNode * p =  FindNodek(phead, 4);
    //if(p!= NULL)
    //cout<<p->value<<endl;
}










