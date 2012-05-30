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

    LIST_Append(list, &num1, sizeof(num1));
    LIST_Append(list, &num2, sizeof(num2));
    LIST_Append(list, &num3, sizeof(num3));
   
    node=list->next;
    g_assert(*((int*)(node->val))==num1);

    node=node->next;
    g_assert(*((double*)(node->val))==num2);

    node=node->next;
    g_assert(*((char*)(node->val))==num3);

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

    LIST_Append(list, &num0, sizeof(num0));
    LIST_Append(list, &num1, sizeof(num1));
    LIST_Append(list, &num2, sizeof(num2));
   
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
