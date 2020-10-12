#include "OctetString.h"
#include <stdlib.h>
#include <time.h>

// 根据给定的长度初始化一个 Array
OctetString *Octet_init(int len)
{

  OctetString *arr = (OctetString *)malloc(sizeof(OctetString));
  arr->arr = (int *)malloc(sizeof(int) * len);

  arr->len = len;
  arr->pos = 0;
  arr->isError = 0;
  for (int i = 0; i < len; i++)
  {
    arr->arr[i] = 0;
  }

  return arr;
}

// 反转 Array 中的 arr
void Octet_reverse(OctetString *array)
{
  int start = 0;
  int end = array->pos - 1;
  while (start < end)
  {
    int temp = array->arr[start];
    array->arr[start] = array->arr[end];
    array->arr[end] = temp;
    start++;
    end--;
  }
}

// 为 Array 增加错误描述
void Octet_assignDescription(OctetString *array, const char *dsc)
{
  // 清空上一个描述
  memset(array->description, 0, 20);

  // 增加新的描述
  strncpy(array->description, dsc, 20);

  array->isError = 1;
}

void Octet_appendVal(OctetString *array, int val)
{

  if (array->pos >= array->len)
  {
    Octet_assignDescription(array, "ERROR: the array is full\n");
    return;
  }
  array->arr[array->pos] = val;
  array->pos++;
}

int Octet_getValByIndex(OctetString *array, int index)
{
  if (array->pos < index)
  {
    Octet_assignDescription(array, "ERROR: index out of bound\n");
  }
  return array->arr[index];
}

int Octet_size(OctetString *array)
{
  return array->pos;
}

void Octet_print(OctetString *array)
{
  if (array->isError)
  {
    printf(array->description);
  }
  else
  {
    printf("[ ");
    for (int i = 0; i < Octet_size(array); i++)
    {
      printf("%d ", Octet_getValByIndex(array, i));
    }
    printf("]\n");
  }
}

// 根据整数长度获得对应的 OctetString 的长度
int Octet_getOctetlengthForInteger(Int *num)
{
  int length = 0;
  Int *zero = Int_init();
  Int *base256 = Convert(256);
  while (Compare(zero, num) != 0)
  {
    length++;
    Int *tmp = num;
    num = Div(num, base256);
    Free(tmp);
  }
  return length;
}

// Generate PS
OctetString *Octet_generatePS(int length)
{
  OctetString *ps = Octet_init(length);

  srand((unsigned)time(NULL));
  for (int i = 0; i < length; i++)
  {
    int num = rand() % 256;
    Octet_appendVal(ps, num);
  }

  return ps;
}