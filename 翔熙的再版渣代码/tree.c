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
            }//����˲�һ���ڵ㶼û�У�˵����һ�����½���
            if (nodeList[position].brother == 0)
            {
                nodeList[position].brother = nodeCount;
                position = nodeCount;
                nodeCount++;
                nodeList[position].content = *s;
                flag = 0;
                break;
            }//�˲�δ�ҵ����ַ������½�һ���ڵ�
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
        return -1;//��������ַ������̣��������ַ������ǣ������-1��ʾ����
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
            }//����˲�һ���ڵ㶼û�У�˵���Ҳ���Ԫ��
            if (nodeList[position].brother == 0)
            {
                return -1;
            }//�˲�δ�ҵ����ַ���˵���Ҳ���Ԫ��
            position = nodeList[position].brother;
        }
        if (nodeList[position].child == 0)
        {
            return -1;
        }//�����������һ�㣬˵�������ַ���������û�ж�ӦԪ��
        position = nodeList[position].child;
        s++;
    }
    if (nodeList[position].content != '\0')
    {
        return -1;
    }//���ѭ����ǰ������˵�������ַ������̣�û�ж�ӦԪ��
    return nodeList[position].child;
}
