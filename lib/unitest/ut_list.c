#include "glib.h"
#include "vaspC.h"

void check_LIST_Append()
{
    int num1=10;
    double num2=20;
    char num3='w';
    LIST* node=NULL;

    LIST* list=NULL;
    LIST_Init(list);

    LIST_Append(list, POINTER_MALLOC(&num1, int, 1));
    LIST_Append(list, POINTER_MALLOC(&num2, double, 1));
    LIST_Append(list, POINTER_MALLOC(&num3, char, 1));
   
    node=list->next;
    g_assert(*((int*)(node->val))==10);

    node=node->next;
    g_assert(*((double*)(node->val))==20);

    node=node->next;
    g_assert(*((char*)(node->val))=='w');

    LIST_Free(list);
}

void check_LIST_Item()
{
    LIST* list=NULL;

    int    num0=10;
    double num1=20;
    char   num2='w';

    LIST* node0= NULL;
    LIST* node1= NULL;
    LIST* node2= NULL;
    LIST* item0= NULL;
    LIST* item1= NULL;
    LIST* item2= NULL;

    LIST_Init(list);

    LIST_Append(list, POINTER_MALLOC(&num0, int, 1));
    LIST_Append(list, POINTER_MALLOC(&num1, double, 1));
    LIST_Append(list, POINTER_MALLOC(&num2, char, 1));

    node0=list->next;
    node1=node0->next;
    node2=node1->next;

    item0= LIST_Item(list,0);    
    item1= LIST_Item(list,1);    
    item2= LIST_Item(list,2);    

    g_assert(node0==item0);
    g_assert(node1==item1);
    g_assert(node2==item2);

    item0= LIST_Item(list,-3);    
    item1= LIST_Item(list,-2);    
    item2= LIST_Item(list,-1);    

    g_assert(node0==item0);
    g_assert(node1==item1);
    g_assert(node2==item2);

    g_assert(*((int*)item0->val)==num0);
    g_assert(*((double*)item1->val)==num1);
    g_assert(*((char*)item2->val)==num2);

    LIST_Free(list);
}

void check_LIST_NItem()
{
    int    num0=10;
    double num1=20;
    char   num2='w';
    LIST* list=NULL;
    
    g_assert_cmpint(LIST_NItem(list),==,0);

    LIST_Init(list);
    g_assert_cmpint(LIST_NItem(list),==,0);

    LIST_Append(list, POINTER_MALLOC(&num0, int, 1));
    g_assert_cmpint(LIST_NItem(list),==,1);

    LIST_Append(list, POINTER_MALLOC(&num1, double, 1));
    g_assert_cmpint(LIST_NItem(list),==,2);

    LIST_Append(list, POINTER_MALLOC(&num2, char, 1));
    g_assert_cmpint(LIST_NItem(list),==,3);

    LIST_Free(list);
}

void check_LIST_Get()
{
    int    num0=10;
    double num1=20;
    char   num2='w';

    LIST* list=NULL;
    LIST_Init(list);

    LIST_Append(list, POINTER_MALLOC(&num0, int, 1));
    LIST_Append(list, POINTER_MALLOC(&num1, double, 1));
    LIST_Append(list, POINTER_MALLOC(&num2, char, 1));
  
    int*    p0= LIST_Get(list, 0);
    double* p1= LIST_Get(list, 1);
    char*   p2= LIST_Get(list, 2);

    g_assert_cmpint(*p0,==,10);
    g_assert_cmpfloat(*p1,==,20);
    g_assert(*p2=='w');

    LIST_Free(list);
}
