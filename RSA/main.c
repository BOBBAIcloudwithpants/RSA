//
//  main.c
//  RSA
//
//  Created by 白家栋 on 2020/10/9.
//

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <math.h>
#include <time.h>
#define LEN 100

typedef long long Integer;

typedef struct Node {
    int val;
    struct Node * next;
} Node;

// 初始化一个链表的节点
Node* init(int a) {
    Node * n = (Node *)malloc(sizeof(Node));
    n->val = a;
    n->next = NULL;
    return n;
}

// 释放一整条链表
void list_free(Node * head) {
    Node * save = head;
    while(head && head->next) {
        Node * p = head->next;
        head = p->next;
        free(p);
    }
    free(save);
}

// 将值a放到链表的末尾
void push_val(Node* t, int a) {
    Node * p = init(a);
    Node * q = t;
    while(q->next) {
        q = q->next;
    }
    q->next = p;
}

// 将节点p放到链表的末尾
void push_back(Node* t, Node * p) {
    Node * q = t;
    while(q->next) {
        q = q->next;
    }
    q->next = p;
}

// 根据索引获取链表，由于链表的第一个节点恒为-1，所以索引0从t->next开始计算
Node* get_by_index(Node* t, int index) {
    Node * p = t->next;
    while(index) {
        index--;
        p = p->next;
    }
    
    return p;
}

// 获取链表的大小，由于链表的第一个节点恒为-1，所以长度从t->next开始计算，即 -1->1->2 长度为：2
int size(Node * head) {
    int len = 0;
    Node * p = head->next;
    while(p) {
        len++;
        p = p->next;
    }
    return len;
}

// 插入第 pos 位，t->next 的 pos=0
void insert(Node* t, Node * p, int pos) {
    Node* tmp = t->next;
    Node* prev = t;
    
    while(pos) {
        pos--;
        tmp = tmp->next;
        prev = prev->next;
    }
    
    prev->next = p;
    p->next = tmp;
}

// 得到链表的最后一个节点
Node * end(Node * t) {
    Node * p = t;
    while(p->next != NULL) {
        p = p->next;
    }
    return p;
}

// 将一个值插入 pos 位置
void insert_val(Node * t, int val, int pos) {
    Node* tmp = t->next;
    Node* prev = t;
    
    while(pos) {
        pos--;
        tmp = tmp->next;
        prev = prev->next;
    }
    
    Node * p = init(val);
    prev->next = p;
    p->next = tmp;
}

// 反转链表，头节点不动
Node * reverse(Node * head) {
    Node * new_h = init(-1);
    Node * p = head->next;
    while(p) {
        insert_val(new_h, p->val, 0);
        p = p->next;
    }
    
    return new_h;
}

// 根据pos删除某个节点
void remove_by_index(Node * head, int pos) {
    Node * p = head;
    while(pos) {
        pos--;
        p = p->next;
    }
    
    if (p->next != NULL) {
        Node * q = p->next->next;
        free(p->next);
        if (q == NULL) {
            p->next = NULL;
        } else {
            p->next = q;
        }
    }
}

// 复制一个链表 pos 以及 pos 位置之后的所有节点
Node * copy_after(Node * head,int pos) {
    Node * p = head->next;
    Node * outcome = init(-1);
    Node * p1 = outcome;
    while(pos && p) {
        p = p->next;
        pos--;
    }
    
    while(p) {
        p1->next = init(p->val);
        p = p->next;
        p1 = p1->next;
    }
    
    return outcome;
}

// 将多余的0从rev中删除，也即 -1->0->0->1->2 =====> -1->1->2
void remove_extra_0(Node * rev) {
    while(rev && rev->next && rev->next->val == 0 && size(rev) > 1) {
        remove_by_index(rev, 0);
    }
}

// 将两个链表对应的数相加，如 1234+5678 ===== -1->1->2->3->4 + -1->5->6->7->8
Node * plus_list(Node * l1, Node * l2) {
    Node * a = reverse(l1);
    Node * b = reverse(l2);
    
    Node * p1 = a->next;
    Node * p2 = b->next;
    int c1 = 0;
    Node * c = init(-1);
    Node * p3 = c;
    
    while(p1 != NULL && p2 != NULL) {
        int temp = c1 + p1->val + p2->val;
            c1 = temp / 10;
            c->next = init(temp % 10);
            c = c->next;
            p1 = p1->next;
            p2 = p2->next;
    }
    
    if (p1 == NULL && p2 == NULL && c1) {
        c->next = init(1);
    } else {
        Node * s = NULL;
        if(p1 != NULL) {
            s = p1;
        } else if(p2 != NULL) {
            s = p2;
        }
        while (s) {
            int temp = s->val + c1;
            
                c->next = init(temp % 10);
                c1 = temp / 10;
                c = c->next;
                s = s->next;
        }
    }
    
    if (c1) {
        c->next = init(1);
    }
    Node * rev = reverse(p3);
    list_free(p3);
    remove_extra_0(rev);
    return rev;
}

// l1-l2, 请确保l1 >= l2 5678-1234 ===== -1->5->6->7->8 - -1->1->2->3->4
Node * minus_list(Node * l1, Node * l2) {
    Node * a = reverse(l1);
    Node * b = reverse(l2);
    
    Node * p1 = a->next;
    Node * p2 = b->next;
    int c1 = 0;
    Node * c = init(-1);
    Node * p3 = c;
    
    while(p1 != NULL && p2 != NULL) {
        int temp = c1 + p1->val - p2->val;
        if (temp <  0) {
            temp += 10;
            c1 = -1;
        } else {
            c1 = 0;
        }
            c->next = init(temp % 10);
            c = c->next;
            p1 = p1->next;
            p2 = p2->next;
    }
    
        Node * s = NULL;
        if(p1 != NULL) {
            s = p1;
        } else if(p2 != NULL) {
            s = p2;
        }
        while (s) {
            int temp = s->val + c1;
            if(temp < 0) {
                temp += 10;
                c1 = -1;
                
            } else {
                c1 = 0;
            }
            c->next = init(temp % 10);
            c = c->next;
            s = s->next;
        }
    
    Node * rev = reverse(p3);
    list_free(p3);
    remove_extra_0(rev);
    return rev;
}


// 将链表n深复制，返回其头节点
Node * copy(Node * n) {
    Node * s = init(-1);
    Node * ret = s;
    Node * p = n->next;
    while(p) {
        s->next = init(p->val);
        p = p->next;
        s = s->next;
    }
    return ret;
}


// 将一串子序列b插入a的idx位置，要注意a, b 都以 -1 作为开头，因此在合并的时候要去掉b的-1
void insert_sublist_by_index(Node * a, Node * b, int idx) {
    Node * prev = a;
    Node * p1 = a->next;
    
    while(idx) {
        idx--;
        prev = prev->next;
        p1 = p1->next;
    }
    
    Node * t = b;
    Node * e = end(b);
    b = b->next;
    free(t);
    
    prev->next = b;
    e->next = p1;
}

// 将一个整数转成链表表达的方式
Node * convert_int_to_list(long long num) {
    Node * p = init(-1);
    Node * q = p;
    if(!num) {
        p->next = init(0);
        return p;
    }
    while(num) {
        q->next = init(num%10);
        num /= 10;
        q = q->next;
    }
    Node * ret = reverse(p);
    list_free(p);
    return ret;
}

// 比较a，b对应的整数的大小，如果a < b, 返回-1; 如果 a == b, 返回0；如果 a > b, 返回1
int compare(Node * a, Node * b) {
    Node * p1 = a->next;
    Node * p2 = b->next;
    
    if(size(a) > size(b)) {
        return 1;
    }
    
    if(size(a) < size(b)) {
        return -1;
    }
    
    while(p1 != NULL && p2 != NULL) {
        if(p1->val > p2->val) {
            return 1;
        } else if(p1->val < p2->val) {
            return -1;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    return 0;
}

// 返回索引0到索引idx的一串子序列，例如: -1->0->1->2; =====> idx=1, ret == -1->0->1
Node * sub_list(Node * a, int idx) {
    Node * ret = init(-1);
    Node * p = a->next;
    Node * r = ret;
    while(idx) {
        idx--;
        ret->next = init(p->val);
        p = p->next;
        ret = ret->next;
    }
    
    ret->next = init(p->val);
    
    return r;
}

// 将a于一个整数相乘，整数较少
Node * product_with_single_num(Node * a, int num) {
    Node * p = init(-1);
    p->next = init(0);
    for(int i = 0;i<num;i++) {
        p = plus_list(p, a);
    }
    return p;
}

// 打印一个链表
void print(Node * head) {
    Node * p1 = head->next;
    while(p1) {
        printf("%d", p1->val);
        p1 = p1->next;
    }
    printf("\n");
 
}

// a * b
Node * product(Node * a, Node * b) {
    
    Node * p2 = reverse(b)->next;
    Node * outcome = init(-1);
    outcome->next = init(0);
    for(int i = 0;i<size(b);i++) {
        Node * temp = product_with_single_num(a, p2->val);
        p2 = p2->next;
        for(int j = 0;j<i;j++) {
            insert_val(temp, 0, size(temp));
        }
        outcome = plus_list(outcome, temp);
        list_free(temp);
        
    }
    
    return outcome;
}


// c = a / b

// a除以一个较短的b
int short_div(Node * a, Node * b) {
    int out = 0;
    
    Node * c = copy(b);
    
    while(compare(c, a) != 1) {
        out++;
        list_free(c);
        Node * temp = convert_int_to_list(out+1);
        c = product(temp, b);
        list_free(temp);
    }
    
    list_free(c);
    return out;
}

// a/b, 支持较大的长度范围
Node * divide(Node * a, Node * b, int start) {
    Node * outcome = init(-1);
    Node * p_out = outcome;
    
//    // 若 a < b, 直接返回0
    if(compare(a, b) == -1) {
        outcome->next = init(0);
        return outcome;
    }

//    // 若 a == b, 直接返回1
    if(compare(a, b) == 0) {
        outcome->next = init(1);
        return outcome;
    }

    if(size(a)<=start) {
        outcome->next = init(0);
        return outcome;
    }
    
    // 否则，开始计算
    int idx = start;
    Node * first_num = sub_list(a, idx);
    
    
    Node * p = a->next;
    // 从a中找到一个大于等于b的子串
    while(compare(first_num, b) == -1) {
        idx++;
        list_free(first_num);
        first_num = sub_list(a, idx);
        p = p->next;
        p_out->next = init(0);
        p_out = p_out->next;
    }
    
    if(size(first_num) == 0) {
        outcome->next = init(0);
        return outcome;
    }
    
    // 将子串与b做除法
    int o1 = short_div(first_num, b);
    
    Node * bo1 = product_with_single_num(b, o1);
    // 得到余数
    Node * rest = minus_list(first_num, bo1);
    
    if (rest && rest->next && rest->next->val == 0) {
        start = 0;
    } else {
        start = size(rest);
    }
    
    // 将得到的结果放在outcome中
    Node* sd1 = convert_int_to_list(o1);
    p_out->next = sd1->next;
    
    
    
    // 得到拼接得到下一次做除法的被除数
    idx++;
    if(idx >= size(a)) {
        // 说明此时已经到达了a的末尾
        return outcome;
    }
    
    // 将余数与剩余的a的部分拼接
    Node * copy_e = copy_after(a, idx);
    Node * end_res = end(rest);
    end_res->next = copy_e->next;
    
    // 如果此时余数为0
    if(rest && rest->next->val == 0) {
        remove_by_index(rest, 0);
    }
    
    Node * next_sub = rest;
    rest = rest->next;
    free(next_sub);
    next_sub = init(-1);
    
    list_free(first_num);
    list_free(bo1);
    
    while(rest && rest->val == 0) {
        Node * p = rest;
        rest = rest->next;
        free(p);
        push_val(outcome, 0);
    }
    
    if(rest == NULL) {
        
        return outcome;
    } else {
        next_sub->next = rest;
        // 递归调用divide, 将得到的结果与当前 outcome 进行拼接
        Node * sub_outcome = divide(next_sub, b, start);
        Node * end_out = end(outcome);
        end_out->next = sub_outcome->next;
//        remove_extra_0(outcome);
        return outcome;
    }
}



// c = a mod b
Node * mod(Node * a, Node * b) {
    Node * div = divide(a, b, 0);
    return minus_list(a, product(b, div));
}



Integer power_of(Integer x, int times) {
    if (times == 0) {
        return 1;
    }
    Integer out = x;
    for(int i = 0;i<times-1;i++) {
        out *= x;
    }
    return out;
}

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
typedef struct {
    
    // 用链表来实现大整数
    Node * head;
    
    // 用来标示是否出现错误的变量
    int isError;
    
} Int;

Int * Int_init() {
    Int * bi = (Int *)malloc(sizeof(Int));
    bi->head = init(-1);
    bi->head->next = init(0);
    bi->isError = 0;
    return bi;
}

void Int_set_list(Int * b, Node * h) {
    b->head = h;
}

Node * Int_get_list(Int * b) {
    return b->head;
}

Int * Plus(Int * a, Int * b) {
    Int * ret = Int_init();
    Int_set_list(ret, plus_list(Int_get_list(a), Int_get_list(b)));
    return ret;
}

Int * Minus(Int * a, Int * b) {
    Int * ret = Int_init();
    Int_set_list(ret, minus_list(Int_get_list(a), Int_get_list(b)));
    return ret;
}

Int * Product(Int * a, Int * b) {
    Int * ret = Int_init();
    Int_set_list(ret, product(Int_get_list(a), Int_get_list(b)));
    return ret;
}

Int * Product_with_num(Int * a, int num) {
    Int * ret = Int_init();
    Int_set_list(ret, product_with_single_num(Int_get_list(a), num));
    
    return ret;
}

Int * Div(Int * a, Int * b) {
    Int * ret = Int_init();
    Node * out = divide(Int_get_list(a), Int_get_list(b), 0);
    remove_extra_0(out);
    Int_set_list(ret, out);
    return ret;
}

int Size(Int * a) {
    return size(Int_get_list(a));
}


// 只适用于比较小的整数
Int * Convert(long long num) {
    Int * ret = Int_init();
    Int_set_list(ret, convert_int_to_list(num));
    
    return ret;
}


Int * Mod(Int * a, Int * b) {
    Int * ret = Int_init();
    Int_set_list(ret, mod(Int_get_list(a), Int_get_list(b)));
    return ret;
}

Int * Copy(Int * b) {
    Int * ret = Int_init();
    Int_set_list(ret, copy(Int_get_list(b)));
    return ret;
}

void Free(Int * a) {
    list_free(Int_get_list(a));
}

void SetError(Int * a) {
    a->isError = 1;
}
void Print(Int * a) {
    print(Int_get_list(a));
}
int IsError(Int * a) {
    return a->isError;
}

Int * Power(Int * a, int times) {
    Int * ret = Convert(1);
    for(int i = 0;i<times;i++) {
        Int * temp = Copy(ret);
        Free(ret);
        ret = Product(temp, a);
        Free(temp);
    }
    return ret;
}

int Compare(Int * a, Int * b) {
    
    return compare(Int_get_list(a), Int_get_list(b));
    
}

int IsOdd(Int * a) {
    Int * two = Convert(2);
    Int * mod = Mod(a, two);
    Int * zero = Int_init();
    if(Compare(mod, zero) == 0) {
        Free(two);
        Free(mod);
        Free(zero);
        return 0;
    }
    
    Free(two);
    Free(mod);
    Free(zero);
    return 1;
    
}

Int * FastPower(Int * a, Int * times) {
    Int * zero = Int_init();
    Int * one = Convert(1);
    
    if (Compare(times, zero) == 0) {
        return Convert(1);
    }
    
    printf("num: ");
    Print(a);
    
    printf("times: ");
    Print(times);
    
    printf("\n");
    
//    if (Compare(times, one) == 0) {
//        return Copy(a);
//    }
    
    
    
    Int * ret = NULL;
    
    
    if(IsOdd(times)) {
        Int * new_t = Minus(times, one);
        Int * t1 = FastPower(a, new_t);
        ret = Product(a, t1);
        Free(t1);
        Free(new_t);
    } else {
        Int * div_num = Div(times, Convert(2));
        Int * t1 = FastPower(a, div_num);
        ret = Product(t1, t1);
        Free(t1);
        Free(div_num);
    }
    
    Free(zero);
    Free(one);
    return ret;
}



// 将 Int 转换为 long long
long long GetInt(Int * a) {
    
    Node * p = Int_get_list(a);
    long long ret = 0;
    int len = size(p);
    p = p->next;
    for(int i = len - 1;i >= 0;i--) {
        ret += pow(10, i) * p->val;
        p = p->next;
    }
    return ret;
}

// 求这个整数在字节串下的长度
int Octet_Size(Int *x)
{
  Int * zero = Convert(0);
  Int * base256 = Convert(256);
  int ret = 0;
  Int * a = Copy(x);
  
    if (Compare(a, zero) == 0) {
        free(a);
        return 1;
    }

  while (Compare(a, zero) != 0)
  {
      Print(a);
    ret++;
    Int *t = a;
    a = Div(a, base256);
      
    Free(t);
  }
  return ret;
}


void test_Int() {
    Int * a = Convert(24);
    Int * b = Convert(20);
    
    printf("a: ");
    Print(a);
    printf("b: ");
    Print(b);
    printf("\n a + b: ");
    Print(Plus(a, b));
    
    printf("\n a - b: ");
    Print(Minus(a, b));
    
    printf("\n a * b: ");
    Print(Product(a, b));
        
    printf("\n a / b: ");
    Print(Div(a, b));
    
    printf("\n b / a: ");
    Print(Div(b, a));
    
    
    printf("\n a mod b: ");
    Print(Mod(a, b));

    printf("\n a ^ a: ");
    Print(FastPower(a, Convert(200)));
    
    printf("\n octet_size a: %d", Octet_Size(a));
    

}

/*  Array 结构体的定义以及相关的方法  */
typedef struct{
    int* arr;              // 数组指针
    int len;                // 数组声明时的长度
    int pos;                // 当前最后一个元素的位置
    int isError;            // 是否出现异常 0---无异常，1---有异常
    char description[20];      // 错误详细内容
} OctetString;

// 根据给定的长度初始化一个 Array
OctetString * Octet_init(int len) {
    
    OctetString * arr = (OctetString *)malloc(sizeof(OctetString));
    arr->arr = (int*)malloc(sizeof(int) * len);

    arr->len = len;
    arr->pos = 0;
    arr->isError = 0;
    for (int i = 0;i<len;i++) {
        arr->arr[i] = 0;
    }
    
    return arr;
}

// 反转 Array 中的 arr
void Octet_reverse(OctetString* array) {
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
void Octet_assignDescription(OctetString* array, const char * dsc) {
    // 清空上一个描述
    memset(array->description, 0, 20);
    
    // 增加新的描述
    strncpy(array->description, dsc, 20);
    
    array->isError = 1;
}

void Octet_appendVal(OctetString * array, int val) {
    
    if (array->pos >= array->len) {
        Octet_assignDescription(array, "ERROR: the array is full\n");
        return;
    }
    array->arr[array->pos] = val;
    array->pos++;
}

int Octet_getValByIndex(OctetString * array, int index) {
    if (array->pos < index) {
        Octet_assignDescription(array, "ERROR: index out of bound\n");
    }
    return array->arr[index];
}

int Octet_size(OctetString * array) {
    return array->pos;
}

void Octet_print(OctetString * array) {
    if (array->isError) {
        printf(array->description);
        
    } else {
        printf("[ ");
            for (int i = 0;i<Octet_size(array);i++) {
                printf("%d ", Octet_getValByIndex(array, i));
            }
            printf("]\n");
    }
}

// 根据整数长度获得对应的 OctetString 的长度
int Octet_getOctetlengthForInteger(Int* num) {
    int length = 0;
    Int * zero = Int_init();
    Int * base256 = Convert(256);
    while (Compare(zero, num) != 0) {
        length++;
        Int * tmp = num;
        num = Div(num, base256);
        Free(tmp);
    }
    return length;
}

// Generate PS
OctetString * Octet_generatePS(int length) {
    OctetString * ps = Octet_init(length);
    
    srand((unsigned)time(NULL));
    for(int i = 0;i < length;i++) {
        int num = rand()%256;
        Octet_appendVal(ps, num);
    }
    
    return ps;
}



/* ---------------------------- */


Int * RSAEP(Int * n, Int * e, Int * M) {
    Int * ret = Int_init();
    if(Compare(M, n) >= 0) {
        SetError(ret);
        return ret;
    }
    Int * Me = FastPower(M, e);
    ret = Mod(Me, n);
    Free(Me);
    return ret;
}


OctetString * EME_Encoding(OctetString * M, int k) {
    
    OctetString * EM = Octet_init(k);
    
    
    if (M->len > k-11) {
        Octet_assignDescription(EM, "message too long");
        return EM;
    }
    OctetString * ps = Octet_generatePS(k - M->len - 3);
    
    // 0x00
    Octet_appendVal(EM, 0);
    // 0x02
    Octet_appendVal(EM, 2);
    // PS
    for(int i = 0;i<ps->len;i++) {
        Octet_appendVal(EM, ps->arr[i]);
    }
    // 0x00
    Octet_appendVal(EM, 0);
    // M
    for(int i = 0;i<M->len;i++) {
        Octet_appendVal(EM, M->arr[i]);
    }
    return EM;
}


OctetString * I2OSP( Int * x, int x_len) {
    
    OctetString * array = Octet_init(x_len);
    
    Int * base256 = Convert(256);
    Int * zero = Convert(0);
    if (Compare(x, FastPower(base256, Convert(x_len))) >= 0) {
        Octet_assignDescription(array, "integer too large\n");
        return array;
    }
    
    while(Compare(x, zero) != 0) {
        Int * mod = Mod(x, base256);
        Int * t = x;
        x = Div(x, base256);
        Octet_appendVal(array, GetInt(mod));
        Free(mod);
        Free(t);
    }
    
    int pad_num = x_len - Octet_size(array);
    for(int i = 0;i<pad_num;i++) {
        Octet_appendVal(array, 0);
    }
    Octet_reverse(array);
    
    return array;
}

Int * OS2IP (OctetString * array) {
    
    Int * num = Int_init();
    Int * base256 = Convert(256);
    
    int * arr = array->arr;
    for (int i = array->pos - 1;i >= 0;i--) {
        
        Int * t = num;
        Int * power_256 = Power(base256, i);
        Int * c = Product_with_num(power_256, arr[array->pos - 1 - i]);
        num = Plus(num, c);
        
        Free(t);
        Free(power_256);
        Free(c);
    }
    
    return num;
}



// (e, n) 为 接收者的 public key
OctetString * Encryption(Int * n, Int * e, OctetString * M) {
    int k = Octet_Size(n);
    printf("k: %d\n", k);
    
    printf("n: ");
    Print(n);
    
    printf("e: ");
    Print(e);
    
    printf("M: ");
    Octet_print(M);
    OctetString * C = Octet_init(k);
    
    
    OctetString * EM = EME_Encoding(M, k);
    
    printf("EM: ");
    Octet_print(EM);
    
    if (EM->isError) {
        Octet_assignDescription(C, EM->description);
        return C;
    }
    
    Int * m = OS2IP(EM);
    printf("EM: ");
    Print(m);
    
    Int * c = RSAEP(n, e, m);
    if (c->isError) {
        Octet_assignDescription(C, "message representative out of range");
        return C;
    }
    
    printf("c: ");
    Print(c);
    
    C = I2OSP(c, k);
    
    printf("C");
    Octet_print(C);
    return C;
}



void test_I2OSP() {
    
    
    
    Int * i = Convert(67000);
    OctetString * array = I2OSP(i, 3);
    Octet_print(array);
    
    
}

void test_OS2IP () {
    
    Int * i = Convert(67000);
    OctetString * array = I2OSP(i, 3);
    Int * j = OS2IP(array);
    
    Print(j);
}

void test_EME() {
    Int * i = Convert(67000);
    OctetString * array = I2OSP(i, 3);
    Octet_print(array);
    OctetString * pad = EME_Encoding(array, 17);
    Octet_print(pad);
}



int main(int argc, const char * argv[]) {
    Int * e = Convert(1234560);
    Int * n = Convert(1324135456555633);
    n = FastPower(n, Convert(2));
    OctetString * str = I2OSP(Convert(255), 1);
    Encryption(n, e, str);
//    test_Int();
}
