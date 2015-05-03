#include <stdio.h>
#include <stdlib.h>
#define NODE_NUMBER 100

typedef struct
{
    char content;
    int child;
    int brother;
}node;

node nodeList[NODE_NUMBER];
int nodeCount = 2;
int leafCount = 0;

int writeTree(char *s);
int checkTree(char *s);

int main()
{
    char s[80];
    int i;
    printf("First, let's write in some elements.\n");
    for (i = 0; i < 10; i++)
    {
        gets(s);
        printf("The leafCount is %d\n", writeTree(s));
    }
    printf("Then,let's check some strings.\n");
    for (i = 0; i < 10; i++)
    {
        gets(s);
        printf("The check result is %d\n", checkTree(s));
    }
    return 0;
}

int writeTree(char *s)
{
    int position = 1;
    int flag = 1;
    while (*s != '\0')
    {
        while (nodeList[position].content != *s)
        {
            if (nodeList[position].content == 0)
            {
                nodeList[position].content = *s;
                flag = 0;
                break;
            }//如果此层一个节点都没有，说明这一层是新建的
            if (nodeList[position].brother == 0)
            {
                nodeList[position].brother = nodeCount;
                position = nodeCount;
                nodeCount++;
                nodeList[position].content = *s;
                flag = 0;
                break;
            }//此层未找到该字符，则新建一个节点
            position = nodeList[position].brother;
        }
        if (nodeList[position].child == 0)
        {
            nodeList[position].child = nodeCount;
            nodeCount++;
            if (nodeCount >= NODE_NUMBER)
            {
                printf("node number not enough!\n");
                exit(1);
            }
        }
        position = nodeList[position].child;
        s++;
    }
    if (flag == 0)
    {
        nodeList[position].child = leafCount;
        nodeList[position].content = '\0';
        leafCount++;
    }
    if (nodeList[position].content != '\0')
        return -1;//如果输入字符串过短，被已有字符串覆盖，则输出-1表示错误
    return nodeList[position].child;
}

int checkTree(char *s)
{
    int position = 1;
    while (*s != '\0')
    {
        while (nodeList[position].content != *s)
        {
            if (nodeList[position].content == 0)
            {
                return -1;
            }//如果此层一个节点都没有，说明找不到元素
            if (nodeList[position].brother == 0)
            {
                return -1;
            }//此层未找到该字符，说明找不到元素
            position = nodeList[position].brother;
        }
        if (nodeList[position].child == 0)
        {
            return -1;
        }//如果不存在下一层，说明输入字符串过长，没有对应元素
        position = nodeList[position].child;
        s++;
    }
    if (nodeList[position].content != '\0')
    {
        return -1;
    }//如果循环提前结束，说明输入字符串过短，没有对应元素
    return nodeList[position].child;
}
