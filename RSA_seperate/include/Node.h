#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
  int val;
  struct Node *next;
} Node;

// 初始化链表
Node *init(int a);

// 释放一整条链表
void list_free(Node *head);

// 将值a放到链表的末尾
void push_val(Node *t, int a);

// 将节点p放到链表的末尾
void push_back(Node *t, Node *p);

// 根据索引获取链表，由于链表的第一个节点恒为-1，所以索引0从t->next开始计算
Node *get_by_index(Node *t, int index);

// 获取链表的大小，由于链表的第一个节点恒为-1，所以长度从t->next开始计算，即 -1->1->2 长度为：2
int size(Node *head);

// 插入第 pos 位，t->next 的 pos=0
void insert(Node *t, Node *p, int pos);

// 得到链表的最后一个节点
Node *end(Node *t);

// 将一个值插入 pos 位置
void insert_val(Node *t, int val, int pos);

// 反转链表，头节点不动
Node *reverse(Node *head);

// 根据pos删除某个节点
void remove_by_index(Node *head, int pos);

// 复制一个链表 pos 以及 pos 位置之后的所有节点
Node *copy_after(Node *head, int pos);

// 将多余的0从rev中删除，也即 -1->0->0->1->2 =====> -1->1->2
void remove_extra_0(Node *rev);

// 将两个链表对应的数相加，如 1234+5678 ===== -1->1->2->3->4 + -1->5->6->7->8
Node *plus_list(Node *l1, Node *l2);

// l1-l2, 请确保l1 >= l2 5678-1234 ===== -1->5->6->7->8 - -1->1->2->3->4
Node *minus_list(Node *l1, Node *l2);

// 将链表n深复制，返回其头节点
Node *copy(Node *n);

// 将一串子序列b插入a的idx位置，要注意a, b 都以 -1 作为开头，因此在合并的时候要去掉b的-1
void insert_sublist_by_index(Node *a, Node *b, int idx);

// 将一个整数转成链表表达的方式
Node *convert_int_to_list(long long num);

// 比较a，b对应的整数的大小，如果a < b, 返回-1; 如果 a == b, 返回0；如果 a > b, 返回1
int compare(Node *a, Node *b);

// 返回索引0到索引idx的一串子序列，例如: -1->0->1->2; =====> idx=1, ret == -1->0->1
Node *sub_list(Node *a, int idx);

// 将a于一个整数相乘，整数较少
Node *product_with_single_num(Node *a, int num);

// 打印一个链表
void print(Node *head);

// a * b
Node *product(Node *a, Node *b);

// a除以一个较短的b
int short_div(Node *a, Node *b);

// a/b, 支持较大的长度范围
Node *divide(Node *a, Node *b);

// c = a mod b
Node *mod(Node *a, Node *b);

#endif