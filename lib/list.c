#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void _LIST_Init(LIST** plist)
{
    _LIST_Free(plist);
    *plist= malloc(sizeof(LIST));
    (*plist)->val=NULL;
    (*plist)->prev=NULL; /*if prev==NULL, it's a root.*/
    (*plist)->next=NULL;
}

void _LIST_Free(LIST** plist)
{
    LIST* list_save=NULL;
    LIST* list=NULL;

    if ((*plist)==NULL)
        return;
    else
        list= *plist;

    while (list->next!=NULL)
        list= list->next; /*Get the last one*/       

    while(list!=NULL)
    {
        list_save=list->prev;      
        if (list->val!=NULL)
        {
            free(list->val); 
            list->val=NULL;
        }
        free(list);
        list=list_save;
    }
    *plist=NULL;
}

void LIST_Append(LIST* list, void* data)
{
    LIST* last_node=NULL;
        
    /*Create List Note*/
    LIST* node=NULL; 
    node= malloc(sizeof(LIST));
    node->val= data;
    node->next=NULL;
    node->prev=NULL;

    /* Connect List Note */
    last_node= list;
    while(last_node->next!=NULL)
    {
        last_node= last_node->next;
    }
    last_node->next= node;
    node->prev= last_node;
}

LIST* LIST_Item(LIST* list, int index)
{
    int i;
    LIST* node= NULL;

    if (list==NULL)
        return NULL;
    else 
        node= list->next; /*node -> first_node*/

    if (index>=0)
    {
        for (i=0; i<index; i++)
        {
            if (list->next==NULL)
            {
                fprintf(stderr,"LIST_ITEM: index out of range. %d %d",i,index);
                exit(1);
            }
            else
            {
                node= node->next;
            }
        }
    }
    else
    {
        while(node->next!=NULL) node= node->next;
        for (i=index; i<-1;i++)
        {
            if (node->prev->prev==NULL)
            {
                fprintf(stderr,"LIST_ITEM: index out of range. %d %d",i,index);
                exit(1);
            }
            else
            {
                node= node->prev;
            }
        }
    }
    return node;
}

int LIST_NItem(LIST* list)
{
    int ncount=0;
    if (list==NULL) return 0;
    LIST* next=list->next;
    while(next) 
    {
        next= next->next;
        ncount++; 
    }
    return ncount; 
}
