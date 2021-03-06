#ifndef OCTETSTRING_H
#define OCTETSTRING_H

#include "Int.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*  Array 结构体的定义以及相关的方法  */
typedef struct
{
  int *arr;             // 数组指针
  int len;              // 数组声明时的长度
  int pos;              // 当前最后一个元素的位置
  int isError;          // 是否出现异常 0---无异常，1---有异常
  char description[20]; // 错误详细内容
} OctetString;

// 根据给定的长度初始化一个 Array
OctetString *Octet_init(int len);

// 反转 Array 中的 arr
void Octet_reverse(OctetString *array);

// 为 Array 增加错误描述
void Octet_assignDescription(OctetString *array, const char *dsc);

// 为 Octet 添加字节
void Octet_appendVal(OctetString *array, int val);

// 根据索引获取值
int Octet_getValByIndex(OctetString *array, int index);

// 获取当前 octets 中的字节数
int Octet_size(OctetString *array);

// 打印该 octets
void Octet_print(OctetString *array);

// 根据整数长度获得对应的 OctetString 的长度
int Octet_getOctetlengthForInteger(Int *num);

// Generate PS
OctetString *Octet_generatePS(int length);

#endif