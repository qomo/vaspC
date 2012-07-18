#ifndef _LIST_H_
#define _LIST_H_

typedef struct _LIST LIST;

struct _LIST
{
    void* val; 
    LIST* prev;
    LIST* next; 
};

void _LIST_Init(LIST** plist);
void _LIST_Free(LIST** plist);
#define  LIST_Init(x) _LIST_Init(&x)
#define  LIST_Free(x) _LIST_Free(&x)
void LIST_Append(LIST* list, void* data, int size);
LIST* LIST_Item(LIST* list, int index);
int LIST_NItem(LIST* list);

#endif
