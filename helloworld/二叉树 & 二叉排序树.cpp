/*
1.层次遍历（广度优先）
2.树的3种遍历方法 （深度优先） 先序，中序，后序
3.找两个子树的第一个公共节点
4.找树中和为n的路径
5.二叉树与双向链表的转换
6.重建二叉树（怎样根据先序和中序来建一颗二叉树），如果是二叉搜索树，怎么重建一颗二叉树
7.判断b是不是a的子树
8.二叉树的镜像
9.输入一个数组，判断他是不是二叉树的后序遍历序列
10.求二叉树的深度
11.二叉排序树的插入和删除
12.一个二叉树，找到二叉树中最长的一条路径
13.一个有向图用邻接矩阵表示，并且是有权图，现在问怎么判断图中有没有环。
14.写一个LRU的缓存，需要完成超时淘汰和LRU淘汰
15.用栈实现一个队列
16.算法题，给一组数字，这些数字里面每一个都重复出现了三次，只有一个数字只出现了一个，要求在时间O（n）空间O（1）内解出来
跳台阶
数组中奇数个元素
一栋楼有n层，不知道鸡蛋从第几层扔下去会碎，用最少的次数找出刚好会碎的楼层
动态规划与贪心有什么区别
连续整数求和(leetcode 第 829 题)，要求时间复杂度小于O(N)
一个无序数组找其子序列构成的和最大，要求子序列中的元素在原数组中两两都不相邻
设计一个秒杀系统
Leetcode 上有三题股票买卖，面试的时候只考了两题，分别是easy 和medium的难度
快排，找无序数组中第k大的数，找一个无序数组中的中位数
堆排，建堆和堆排
二叉树的层次遍历
Leetcode 104题。 给定一个二叉树，原地将它展开为链表。
二叉树的最近公共父亲节点
1.买卖股票的最佳时间（3个版本）
2.LRU cache的实现
*/


//1.二叉树的层次遍历 
/*
若不要求按层次遍历按行打印，，只要求打印出按层次遍历（BFS）的序列
思路：首先很符合先进先出的规则，可以用队列来实现，我们把要打印的这个节点压入队列中，从队列中获取当前
要打印的这个节点，并从队列中将这个节点pop掉，打印这个节点，判断这个节点是否还有左孩子，有的话压入队列，
判断这个节点是否还有右孩子，有的话，压入队列中，总的思路就是：打印当前节点时，判断他有无左右孩子，把左右
孩子压入栈中，打印的时候就从队列中把打印节点删掉，当队列中不再有元素时，整个层次遍历就完成来
时间复杂度 O（n)，空间复杂度哦（n)
*/

#include <deque>
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
using namespace std;

typedef struct BinaryTree
{
    int m_value;
    BinaryTree *m_left;
    BinaryTree *m_right;
};

typedef struct BinaryTree2
{
    int m_value;
    BinaryTree2 * m_left;
    BinaryTree2 * m_right;
    BinaryTree2 * m_parents;
}BinaryTree2;

typedef struct Tree
{   
    int value;
    vector<Tree*> m_child;
}Tree;

void LevelPrint(BinaryTree *proot)
{
    if(proot == NULL)
        return;

    deque<BinaryTree*> myque;
    myque.push_front(proot);
    while(!myque.empty())
    {
        BinaryTree *pNode = myque.front();
        myque.pop_front();
        cout<<pNode->m_value<<" ";
        if(pNode ->m_left != NULL)
            myque.push_front(pNode->m_left);
        if(pNode->m_right != NULL)
            myque.push_front(pNode->m_right);
    }
}

/*
若要求按层打印出二叉树的话
思路：若要按层打印的话，需要知道每层打印多少个，什么时候换行，所以，我们需要两个变量，
不断来迭代和维护，一个用来记录当前层需被打印的个数，每打印一个个数就减1，若个数为0，说明
当前层已打印完，在打印每一个节点时，若他们有左右孩子，我们把他们都压入了队列，每压入一个，我
们都需要对当前层节点的个数加1，若换行了，则此时需被打印的迭代为下层迭代的个数，当前层元素的个数清0，
重新开始计算下层的元素个数
*/

void LevelPrintBinaryTree(BinaryTree * proot)
{
    if(proot == NULL)
        return;
    deque<BinaryTree *> mydeque;
    mydeque.push_front(proot);
    int tobeprint = 1;
    int levelnum = 0;
    while (!mydeque.empty())
    {
        BinaryTree *p  = mydeque.front();
        mydeque.pop_front();
        cout<<p->m_value<<" ";
        --tobeprint;
        if(p->m_left != NULL)
        {
            mydeque.push_front(p->m_left);
            levelnum++;
        }
        if(p->m_right != NULL)
        {
            mydeque.push_front(p->m_right);
            levelnum++;
        }

        if(tobeprint == 0)
        {
            cout<<endl;
            tobeprint = levelnum;
            levelnum = 0;
        }
    }  
}

/*
树的先序遍历，中序遍历，后序遍历

*/

//根左右
void PreOrder(BinaryTree * pnode)
{
    if(pnode)
    {
        cout<<pnode->m_value<<" ";
        PreOrder(pnode->m_left);
        PreOrder(pnode->m_right);
    }
}

//左根右
void InOrder(BinaryTree * pnode)
{
    if(pnode)
    {
        PreOrder(pnode->m_left);
        cout<<pnode->m_value<<" ";
        PreOrder(pnode->m_right);
    }
}

//左右根
void PosOrder(BinaryTree * pnode)
{
    if(pnode)
    {
        PreOrder(pnode->m_left);
        PreOrder(pnode->m_right);
        cout<<pnode->m_value<<" ";
    }
}

/*
找树中两个节点的最低公共祖先
1.首先看这棵树是不是二叉搜索树，如果是的话，二叉搜索树的特点是每一个子树都满足父节点比左边的孩子大，
比右边的孩子小，所以求两个节点的最低公共祖先的话我们可以将这两个节点和根节点做比较，如果说这两个数都比
根节点小，则他们的最低公共祖先肯定在左子数中，如果这两个数都比根节点大，则他们的最低公共祖先肯定在右子数中，
然后继续递归的从上往下的找，如果找到一个节点是在他们两个中间的（还有什么限制条件吗？），则这个节点就是他们的最低公共祖先
2.就是普通的树的话的话怎么解决，那他的每个子节点有指向父节点的前驱指针吗，如果有的话，这就相当于找
两个链表的第一个公共节点，可以从下往上的进行比较，看pre父亲节点是否相同，直到找到第一个相同的节点，则
这个节点就是她们的最低公共祖先
3.如果说他也没有前驱指针呢？
如果也没有前驱指针，则还是可以转成求两个链表的第一个公共节点，我们可以找从根节点到这两个节点的路径，然后求
这两个路径他们的第一个公共节点，求路径的话我们可以用树的先序遍历，一直到叶子节点，如果到这跟路径到叶子节点
了，还是么有我们这个节点，就进行回退，回退到上一层，看右孩子是否是。如果左右孩子都访问了还不是，那就再向上回退，
这样递归的找，直到找到我们这两个节点的路径，然后求这两个路径的第一个公共节点
*/

//假定他是一颗二叉搜索树
BinaryTree * FindFirstComNode(BinaryTree * proot, BinaryTree *node1, BinaryTree *node2)
{
    if(proot == NULL || node1 == NULL || node2 == NULL)
        return NULL;
    int value1 = node1->m_value;
    int value2 = node2->m_value;
    return FindFirstComNodeCore(proot, value1, value2);
}

BinaryTree * FindFirstComNodeCore(BinaryTree *pNode, int value1, int value2)
{
    if(pNode->m_value > value1 && pNode->m_value > value2)
        return FindFirstComNodeCore(pNode->m_left, value1, value2);
    if(pNode->m_value < value1 && pNode->m_value < value2)
        return FindFirstComNodeCore(pNode->m_right, value1, value2);
    if(min(value1, value2) < pNode->m_value && pNode->m_value < max(value1, value2))
        return pNode;
}

// 若他不是二叉搜素树，是一个有前驱指针即有指向父节点的指针的树的话,假定这两个节点绝对在这颗树中
BinaryTree2 * FindFirstComNode2(BinaryTree2 *proot, BinaryTree2 *node1, BinaryTree2 *node2)
{
    BinaryTree2 * p1 = node1;
    BinaryTree2 * p2 = node2;
    BinaryTree2 * commNode = NULL;
    while(p1->m_parents != NULL && p2->m_parents != NULL)
    {
        if(p1->m_parents == p2->m_parents)
        {
            commNode = p1->m_parents;
            break;
        }
        p1 = p1->m_parents;
        p2 = p2->m_parents;
    }
    return commNode;
}

/*若他也没有指向父节点的前驱指针呢，我们需要找到这两两个节点的他们的两个路径，然后再进行对比，路径
需要保存起来，我们用两个链表进行保存，回溯法：先把所有的可能都走了，如果发现不是最优的，就回退一步，继续找最优的
(先压后回溯，但是感觉思路不是特别清晰，回溯的这个过程)
*/

bool FindPath(Tree *proot, Tree *node1, list<Tree*> &path)
{
    if(proot == node1)
        return true;
    path.push_back(proot);
    bool found = false;
    vector<Tree*>::iterator it1 = proot->m_child.begin();
    while(!found && it1 != proot->m_child.end())
    {
        FindPath(*it1, node1, path);
        it1++;
    }

    if(!found)
    {
        path.pop_back();
    }
    return found;
}

Tree* FindFirstCommNodeCore(list<Tree*> &path1, list<Tree*> &path2)
{
    list<Tree*>::const_iterator it1 = path1.begin();
    list<Tree*>::const_iterator it2 = path2.begin();
    Tree *pCommNode = NULL;
    while (it1 != path1.end() && it2 != path2.end())
    {
        if(*it1 == *it2)
        {
            pCommNode = *it1;
        }
        it1++;
        it2++;
    }
    return pCommNode; 
}

Tree * FindFirstCommNode(Tree * proot, Tree *node1, Tree *node2)
{
    if(proot == NULL || node1 == NULL || node2 == NULL)
        return NULL;
    list<Tree*> path1;
    list<Tree*> path2;
    FindPath(proot, node1, path1);
    FindPath(proot, node2, path2);
    return FindFirstCommNodeCore(path1, path2);
}

/*
找树中和为n的路径
*/

/*
求二叉树的高度
二叉搜索树怎么插入和删除元素

*/


/*

买卖股票的最佳时间
*/

/*
动态规划：



*/


/*
递归和分治
你思想什么是递归：函数自己调自己，先不断递归然后到达某个条件点，递归终止，往会返，所以一定
要有递归终止条件，分治（他和递归相比没有重复计算，如果有重复计算，即可以利用动态规划，则把之前的值都保存起来，可以回退的），
不断分治，大问题分为小问题，每个局部有效，达成整体有效

fab斐波拉契序列用递归解决存在什么问题，用循环最后怎么解决的？
*/

/*
leetcode 50  pow(x,n);(底数和指数，只要考察代码的鲁棒性) log(n)
y=x^n/2

leetcode    169 求众数（4种解法，可以写下）
*/


/*
贪心算法：
在当前看起来是最好的，局部最优，也可以达到整体有效的（有些问题很适合贪心算法）
问题可以分为子问题来解决，子问题的最优解可以得到全局的最优解，最优子结构


动态规划
每一个子问题选择结果可能不一定选最优解，把之前你认为可以的结果，把之前的运算结果选择保存起来，并根据之前的结果
左当前的最优解，可回退
*/


/*
leetcode 122 买卖股票的最佳时间 DFS  （每天只能持有1股，可以买卖无数次）(可用贪心算法，只要后一天
比前一条高，就在前一天买进，后一天卖出，最把利益加到总利益上来) （买卖无数次，是指在这个区间里，可以买卖无数次，
如果限制了k的话，则说明频繁操作，大于k了，你就不能再对序列进行操作）
*/

/*
树：树的广度优先 （BFS）
   树的深度优先 （DFS）回溯（怎么写）
leetcode 104 111   在一颗树中找他的最大深度 和 最小深度（思路r:用BFS
）


leetcode 22 输出所有的括号形式  （递归的搜索方式）
1.数组长度一定，先把所有组合找出来，再判断找有效的 
2.局部已经不合法了，我们就不再递归（剪枝）要记录你的左括号用了多少个，右括号用了多少括号

二分查找（在一个有序的序列中的话去找） （704）
1.在一个有序的序列中
2.可以通过索引进行访问（数组）

69 sqrt函数的实现（35）

*/


/*
树，链表和动态规划

*/

/*
字典树：
用空间换时间，利用字符串的公共前缀
*/


/*
位运算：
以及常见面试题：（39 ～ 58）
*/


/*
动态规划：
三角形的最短路径 （leetcode 120）
思想:用动态规划，dp方程如下：
dp[i,j] = min(dp(i+1,j), dp(i+1,j+1)）+dp(i,j)
难点：我知道状态dp方程，但是我不知道怎么递推这去写？
*/

class triangle
{
public:
    int GetMinNum()
    {
        for(int i = m-2; i>0;i--)
        {
            for(int j=0; j<n; j++)
            {
                num = min(triangle)

            }
        }
    }
private:
    int m;  //三角形的高，即多少层
    int n; //三角形的长，即每层有多少个元素
};

//乘积最大的连续子序列  （leetcode 152）
/*
如果不相邻
dp状态的定义：DP[i][2]
当前正值的最大值：
DP[i,0] = DP[i-1, 0] * a[i]   if(a[i] > 0)
DP[i,0] = DP[i-1,1] * a[i]    if(a[i] <0)
当前负值的最大值
DP[i,1] = DP[i-1,1] if(a[i] > 0)
DP[i,1] = DP[i-1,0
] if(a[i] < 0)
dp方程：
*/
/*
暴力解法：
动态规划：
*/

//股票买卖系列
/*






*/

//最长上升自序列  （leetcode 300） 自序列可以不相邻，连续子序列才需要
/*
如果是必须连续的 

dp状态： dp[i]  从头到i，把i选上子序列的最长子序列长度
dp方程：dp[i] = {max(dp[j])} +1   j: 0~i-1, 且a[j] < a[i]
i 0->n-1
j 0->i-1
O(n^2)
*/


/*
零钱兑换  最少需要多少个硬币 可以得到给的面值(leetcode 322)
动态规划：dp[i]
dp方程：dp[i] = min{dp[i-coins[j]]} + 1;
*/

int CoinsChange(vector<int> & coins, int amount)
{
    int Max = amount +1;
    vector<int> dp(amount+1, Max);
    dp[0] = 0;
    for(int i = 1; i<amount; i++)
    {
        for(int j =0; j<coins.size(); j++)
        {
            if(coins[j] <= i)
            {
                dp[i] = min(dp[i],dp[i-coins[j]]+1);
            }
        }
    }
    return dp[amount] > amount? -1:dp[amount];
}

/*
leetcode (72)
编辑最短距离 （单词1要变成单词2，最少需要多少步）（insert, delete, replace）
动态规划：
dp状态定义：dp[i][j]  i：单词1的前i个字符 j：单词2的前j个字符， word1的字符变成word2的前j个字符
最少需要多少步 
dp方程：
dp[m][n] 
dp[i,j] = dp[i-1,j-1]      如果w1[i] == w2[j]  (不用做任何操作)
min(dp[i-1,j],dp[i,j-1],dp[i-1,j-1]) +1                      如果w1[i] != w2[j]  

时间复杂度 O（m*n）
*/

/*
缓存替换机制
LRU cache（缓存替换算法）最近最少使用（least recently used）
最近最少没有被使用，则当缓存
优先级调整和淘汰最近没有被使用的
最近被使用的都回被放到最前面
双向链表

LFU 新元素替换掉最近使用次数最少的，淘汰掉
题目是什么？考什么呢？

LRU cache实现  (leetcode 146)
get
put
*/

/*
位运算

异或的一些特点：
x ^ 0 = x
x ^ 1 = ~x  (x和一个全1的进行异或的话，就相当于给x取反)
x ^ ~x = 1
x ^ x = 0
a ^b = c  a^c = b b^c =a (swap)
a^b^c = a^(b^c) = (a^b) ^c

实战：
判断奇偶：x &1 ==1 (说明是奇数，否则是偶数)
x = x&(x-1)   --> 清零最低位的1  （求二进制里面有多少个1）
x & ~x --得到最低位的1

1.输入一个无符号整数，判断他的二进制数中有多少个1 （leetcode 191）
1.x%2 count++
x=x>>1;
2.x&(x-1)
while(x!=0)
{
    count++;
    x=x & (x-1);
}
时间复杂度：就看你有多少个1

/*
2.（leetcode 231，338）
1.判断x是不是2的x次方
*/
bool IsPowOfTwo(int n)
{   
    return n >0 && !(n&(n-1));
    
}

vector<int> CountBits(int num)
{
    vector<int> bits(num+1, 0);
    for(int i=1; i <=num; ++i)
    {
        bits[i] = bits[i & (i-1)] +1;
    }
    return bits;
}
/*
(x & x-1)==0 && x !=0  只有1个1

3.给你一个数n,计算从0到n拥有多少个二进制为1的
count[i] = cunt[i&(i-1)] +1   利用位运算做下标来计算

*/


/*
n皇后的另一种解法 （位运算）
DFS(0,0,0,0)
递归终结者
void DFS(int row, int col, int pie, int na)
{
    if(row >= n)
    {
        coun++;
        return;
    }                            0000 1111
    bits = (~(col | pe | na))  & ((1<<n) -1)  //得到有效的空位，我们可以放皇后
    while(bits)
    {
        p = bits & ~bits;   //得到空位
        DFS(row+1,col | p,(pie |p) <<1,(na | p) >> 1);
        bits &= bits -1; 
    }
}
*/









