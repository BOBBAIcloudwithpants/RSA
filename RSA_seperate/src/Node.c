#include "Node.h"

// 初始化一个链表的节点
Node *init(int a)
{
  Node *n = (Node *)malloc(sizeof(Node));
  n->val = a;
  n->next = NULL;
  return n;
}

// 释放一整条链表
void list_free(Node *head)
{
  Node *save = head;
  while (head && head->next)
  {
    Node *p = head->next;
    head = p->next;
    free(p);
  }
  free(save);
}

// 将值a放到链表的末尾
void push_val(Node *t, int a)
{
  Node *p = init(a);
  Node *q = t;
  while (q->next)
  {
    q = q->next;
  }
  q->next = p;
}

// 将节点p放到链表的末尾
void push_back(Node *t, Node *p)
{
  Node *q = t;
  while (q->next)
  {
    q = q->next;
  }
  q->next = p;
}

// 根据索引获取链表，由于链表的第一个节点恒为-1，所以索引0从t->next开始计算
Node *get_by_index(Node *t, int index)
{
  Node *p = t->next;
  while (index)
  {
    index--;
    p = p->next;
  }

  return p;
}

// 获取链表的大小，由于链表的第一个节点恒为-1，所以长度从t->next开始计算，即 -1->1->2 长度为：2
int size(Node *head)
{
  int len = 0;
  Node *p = head->next;
  while (p)
  {
    len++;
    p = p->next;
  }
  return len;
}

// 插入第 pos 位，t->next 的 pos=0
void insert(Node *t, Node *p, int pos)
{
  Node *tmp = t->next;
  Node *prev = t;

  while (pos)
  {
    pos--;
    tmp = tmp->next;
    prev = prev->next;
  }

  prev->next = p;
  p->next = tmp;
}

// 得到链表的最后一个节点
Node *end(Node *t)
{
  Node *p = t;
  while (p->next != NULL)
  {
    p = p->next;
  }
  return p;
}

// 将一个值插入 pos 位置
void insert_val(Node *t, int val, int pos)
{
  Node *tmp = t->next;
  Node *prev = t;

  while (pos)
  {
    pos--;
    tmp = tmp->next;
    prev = prev->next;
  }

  Node *p = init(val);
  prev->next = p;
  p->next = tmp;
}

// 反转链表，头节点不动
Node *reverse(Node *head)
{
  Node *new_h = init(-1);
  Node *p = head->next;
  while (p)
  {
    insert_val(new_h, p->val, 0);
    p = p->next;
  }

  return new_h;
}

// 根据pos删除某个节点
void remove_by_index(Node *head, int pos)
{
  Node *p = head;
  while (pos)
  {
    pos--;
    p = p->next;
  }

  if (p->next != NULL)
  {
    Node *q = p->next->next;
    free(p->next);
    if (q == NULL)
    {
      p->next = NULL;
    }
    else
    {
      p->next = q;
    }
  }
}

// 复制一个链表 pos 以及 pos 位置之后的所有节点
Node *copy_after(Node *head, int pos)
{
  Node *p = head->next;
  Node *outcome = init(-1);
  Node *p1 = outcome;
  while (pos && p)
  {
    p = p->next;
    pos--;
  }

  while (p)
  {
    p1->next = init(p->val);
    p = p->next;
    p1 = p1->next;
  }

  return outcome;
}

// 将多余的0从rev中删除，也即 -1->0->0->1->2 =====> -1->1->2
void remove_extra_0(Node *rev)
{
  while (rev && rev->next && rev->next->val == 0 && size(rev) > 1)
  {
    remove_by_index(rev, 0);
  }
}

// 将两个链表对应的数相加，如 1234+5678 ===== -1->1->2->3->4 + -1->5->6->7->8
Node *plus_list(Node *l1, Node *l2)
{
  Node *a = reverse(l1);
  Node *b = reverse(l2);

  Node *p1 = a->next;
  Node *p2 = b->next;
  int c1 = 0;
  Node *c = init(-1);
  Node *p3 = c;

  while (p1 != NULL && p2 != NULL)
  {
    int temp = c1 + p1->val + p2->val;
    c1 = temp / 10;
    c->next = init(temp % 10);
    c = c->next;
    p1 = p1->next;
    p2 = p2->next;
  }

  if (p1 == NULL && p2 == NULL && c1)
  {
    c->next = init(1);
  }
  else
  {
    Node *s = NULL;
    if (p1 != NULL)
    {
      s = p1;
    }
    else if (p2 != NULL)
    {
      s = p2;
    }
    while (s)
    {
      int temp = s->val + c1;

      c->next = init(temp % 10);
      c1 = temp / 10;
      c = c->next;
      s = s->next;
    }
  }

  if (c1)
  {
    c->next = init(1);
  }
  Node *rev = reverse(p3);
  list_free(p3);
  remove_extra_0(rev);
  return rev;
}

// l1-l2, 请确保l1 >= l2 5678-1234 ===== -1->5->6->7->8 - -1->1->2->3->4
Node *minus_list(Node *l1, Node *l2)
{
  Node *a = reverse(l1);
  Node *b = reverse(l2);

  Node *p1 = a->next;
  Node *p2 = b->next;
  int c1 = 0;
  Node *c = init(-1);
  Node *p3 = c;

  while (p1 != NULL && p2 != NULL)
  {
    int temp = c1 + p1->val - p2->val;
    if (temp < 0)
    {
      temp += 10;
      c1 = -1;
    }
    else
    {
      c1 = 0;
    }
    c->next = init(temp % 10);
    c = c->next;
    p1 = p1->next;
    p2 = p2->next;
  }

  Node *s = NULL;
  if (p1 != NULL)
  {
    s = p1;
  }
  else if (p2 != NULL)
  {
    s = p2;
  }
  while (s)
  {
    int temp = s->val + c1;
    if (temp < 0)
    {
      temp += 10;
      c1 = -1;
    }
    else
    {
      c1 = 0;
    }
    c->next = init(temp % 10);
    c = c->next;
    s = s->next;
  }

  Node *rev = reverse(p3);
  list_free(p3);
  remove_extra_0(rev);
  return rev;
}

// 将链表n深复制，返回其头节点
Node *copy(Node *n)
{
  Node *s = init(-1);
  Node *ret = s;
  Node *p = n->next;
  while (p)
  {
    s->next = init(p->val);
    p = p->next;
    s = s->next;
  }
  return ret;
}

// 将一串子序列b插入a的idx位置，要注意a, b 都以 -1 作为开头，因此在合并的时候要去掉b的-1
void insert_sublist_by_index(Node *a, Node *b, int idx)
{
  Node *prev = a;
  Node *p1 = a->next;

  while (idx)
  {
    idx--;
    prev = prev->next;
    p1 = p1->next;
  }

  Node *t = b;
  Node *e = end(b);
  b = b->next;
  free(t);

  prev->next = b;
  e->next = p1;
}

// 将一个整数转成链表表达的方式
Node *convert_int_to_list(long long num)
{
  Node *p = init(-1);
  Node *q = p;
  if (!num)
  {
    p->next = init(0);
    return p;
  }
  while (num)
  {
    q->next = init(num % 10);
    num /= 10;
    q = q->next;
  }
  Node *ret = reverse(p);
  list_free(p);
  return ret;
}

// 比较a，b对应的整数的大小，如果a < b, 返回-1; 如果 a == b, 返回0；如果 a > b, 返回1
int compare(Node *a, Node *b)
{
  Node *p1 = a->next;
  Node *p2 = b->next;

  if (size(a) > size(b))
  {
    return 1;
  }

  if (size(a) < size(b))
  {
    return -1;
  }

  while (p1 != NULL && p2 != NULL)
  {
    if (p1->val > p2->val)
    {
      return 1;
    }
    else if (p1->val < p2->val)
    {
      return -1;
    }
    p1 = p1->next;
    p2 = p2->next;
  }
  return 0;
}

// 返回索引0到索引idx的一串子序列，例如: -1->0->1->2; =====> idx=1, ret == -1->0->1
Node *sub_list(Node *a, int idx)
{
  Node *ret = init(-1);
  Node *p = a->next;
  Node *r = ret;
  while (idx)
  {
    idx--;
    ret->next = init(p->val);
    p = p->next;
    ret = ret->next;
  }

  ret->next = init(p->val);

  return r;
}

// 将a于一个整数相乘，整数较少
Node *product_with_single_num(Node *a, int num)
{
  Node *p = init(-1);
  p->next = init(0);
  for (int i = 0; i < num; i++)
  {
    p = plus_list(p, a);
  }
  return p;
}

// 打印一个链表
void print(Node *head)
{
  Node *p1 = head->next;
  while (p1)
  {
    printf("%d", p1->val);
    p1 = p1->next;
  }
  printf("\n");
}

// a * b
Node *product(Node *a, Node *b)
{

  Node *p2 = reverse(b)->next;
  Node *outcome = init(-1);
  outcome->next = init(0);
  for (int i = 0; i < size(b); i++)
  {
    Node *temp = product_with_single_num(a, p2->val);
    p2 = p2->next;
    for (int j = 0; j < i; j++)
    {
      insert_val(temp, 0, size(temp));
    }
    outcome = plus_list(outcome, temp);
    list_free(temp);
  }

  return outcome;
}

// c = a / b

// a除以一个较短的b
int short_div(Node *a, Node *b)
{
  int out = 0;

  Node *c = copy(b);

  while (compare(c, a) != 1)
  {
    out++;
    list_free(c);
    Node *temp = convert_int_to_list(out + 1);
    c = product(temp, b);
    list_free(temp);
  }

  list_free(c);
  return out;
}

// a/b, 支持较大的长度范围
Node *divide(Node *a, Node *b)
{
  Node *outcome = init(-1);

  //    // 若 a < b, 直接返回0
  if (compare(a, b) == -1)
  {
    outcome->next = init(0);
    return outcome;
  }

  //    // 若 a == b, 直接返回1
  if (compare(a, b) == 0)
  {
    outcome->next = init(1);
    return outcome;
  }

  // 否则，开始计算
  int idx = 0;
  Node *first_num = sub_list(a, idx);

  Node *p = a->next;
  // 从a中找到一个大于等于b的子串
  while (compare(first_num, b) == -1)
  {
    idx++;
    list_free(first_num);
    first_num = sub_list(a, idx);
    p = p->next;
  }

  if (size(first_num) == 0)
  {
    outcome->next = init(0);
    return outcome;
  }

  // 将子串与b做除法
  int o1 = short_div(first_num, b);

  Node *bo1 = product_with_single_num(b, o1);
  // 得到余数
  Node *rest = minus_list(first_num, bo1);

  // 将得到的结果放在outcome中
  Node *sd1 = convert_int_to_list(o1);
  insert_sublist_by_index(outcome, sd1, 0);

  // 得到拼接得到下一次做除法的被除数
  idx++;
  if (idx >= size(a))
  {
    // 说明此时已经到达了a的末尾
    return outcome;
  }

  // 将余数与剩余的a的部分拼接
  Node *copy_e = copy_after(a, idx);
  Node *end_res = end(rest);
  end_res->next = copy_e->next;

  if (rest && rest->next->val == 0)
  {
    remove_by_index(rest, 0);
  }

  Node *next_sub = rest;
  rest = rest->next;
  free(next_sub);
  next_sub = init(-1);

  list_free(first_num);
  list_free(bo1);

  while (rest && rest->val == 0)
  {
    Node *p = rest;
    rest = rest->next;
    free(p);
    push_val(outcome, 0);
  }
  if (rest == NULL)
  {

    return outcome;
  }
  else
  {
    next_sub->next = rest;
    // 递归调用divide, 将得到的结果与当前 outcome 进行拼接
    Node *sub_outcome = divide(next_sub, b);
    Node *end_out = end(outcome);
    end_out->next = sub_outcome->next;
    remove_extra_0(outcome);
    return outcome;
  }
}

// c = a mod b
Node *mod(Node *a, Node *b)
{
  Node *div = divide(a, b);
  return minus_list(a, product(b, div));
}