/*
用两个栈模拟队列的先进先出 push/pop
思路：队列的特点是先进先出，那用两个栈s1 ,s2来模拟队列的话，模拟他的push操作的话
可以直接push进s1,
模拟他的pop操作的话，因为元素被压在s1了，所以我们需要判断，如果s2中有元素，就直接出，如果没有的
话，就把s1中的元素全都出栈压进s2
*/

#include <stack>
#include <queue>
using namespace std;
class myqueue
{
public:
    myqueue(){}
    ~myqueue(){}

    void push(int tmp);
    int pop(){};
private:
    stack<int> s1;
    stack<int> s2;
};

void myqueue::push(int tmp)
{
    s1.push(tmp);
}

int myqueue::pop()
{
    int value = 0;
    if(!s2.empty())
    {
        int value = s2.top();
        s2.pop();
    }
    else
    {
        while (!s1.empty())
        {
            s2.push(s1.top());
            s1.pop();
        }
        value = s2.top();
        s2.pop();
    }
    return value;
}

/*
用两个队列模拟栈的先进后出
*/

class mysatck
{
public:
    void push(int tmp);
    int pop();
private:
    queue<int> q1;
    queue<int> q2;
};

void mysatck::push(int tmp)
{

}

int mysatck::pop()
{
    
}

