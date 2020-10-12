#ifndef INT_H
#define INT_H

#include "Node.h"
#include <stdlib.h>
#include <stdio.h>
/* Int 结构体的定义以及相关的方法
    
 example:
    1. 45123   =>   -1 -> 4 -> 5 -> 1 -> 2 -> 3 -> NULL
    2. 空       =>  -1 -> NULL
 
 operation:
    1. Plus
    2. Minus
    3. Product
    4. Div
    5. Mod
    6. Compare
*/
typedef struct
{

  // 用链表来实现大整数
  Node *head;

  // 用来标示是否出现错误的变量
  int isError;

} Int;

// 初始化一个大整数，默认值为0
Int *Int_init();

// 为大整数b设置链表为h
void Int_set_list(Int *b, Node *h);

// 获取大整数的链表头节点
Node *Int_get_list(Int *b);

// 将两个大整数相加
Int *Plus(Int *a, Int *b);

// a-b
Int *Minus(Int *a, Int *b);

// a*b
Int *Product(Int *a, Int *b);

// a * num
Int *Product_with_num(Int *a, int num);

// a/b
Int *Div(Int *a, Int *b);

// 求一个整数的位数
int Size(Int *a);

// 将long long转换为大整数
Int *Convert(long long num);

// a mod b
Int *Mod(Int *a, Int *b);

// 将 b 深拷贝
Int *Copy(Int *b);

// 释放大整数所占有的内存空间
void Free(Int *a);

// 设置 Int 为 Error
void SetError(Int *a);

// 打印一个 Int
void Print(Int *a);

// 判定 a 此时是否出现错误
int IsError(Int *a);

// 比较 a, b; a<b 则返回-1，a==b则返回0，a>b则返回1
int Compare(Int *a, Int *b);

// 判断a是否为奇数
int IsOdd(Int *a);

// 快速幂
Int *FastPower(Int *a, Int *times);

// 将 Int 转换为 long long
long long GetInt(Int *a);

#endif