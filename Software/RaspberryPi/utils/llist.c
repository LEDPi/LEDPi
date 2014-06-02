#include "utils/llist.h"

////////////////////////////////////////////////////////////////////////////////
/// Private functions declaration

static p_ll_node_t ll_create_node(void *data);

////////////////////////////////////////////////////////////////////////////////
/// Public functions implementation

p_ll_list_t ll_create(void (*freeData)(void *))
{
	p_ll_list_t list = (p_ll_list_t) malloc( sizeof(ll_list_t) );
	list->Size = 0;
	list->First = ll_create_node(NULL);
	list->Last = ll_create_node(NULL);
	list->Current = list->Last;
	list->FreeData = freeData;

	list->First->Prev = list->First;
	list->First->Next = list->Last;
	list->Last->Prev = list->First;
	list->Last->Next = list->Last;

	return list;
}

void ll_delete(p_ll_list_t list)
{
	ll_first(list);
	while(ll_next(list))
	{
		ll_remove(list);
	}
	
	free(list->First);
	free(list->Last);
	free(list);
}

void* ll_get(p_ll_list_t list)
{
	if(list->Current != NULL)
		return list->Current->Data;
	return NULL;
}

bool ll_next(p_ll_list_t list)
{
	list->Current = list->Current->Next;
	return list->Current != list->Last;
}

bool ll_prev(p_ll_list_t list)
{
	list->Current = list->Current->Prev;
	return list->Current != list->First;
}

void ll_last(p_ll_list_t list)
{
	list->Current = list->Last;
}

void ll_first(p_ll_list_t list)
{
	list->Current = list->First;
}

void ll_remove(p_ll_list_t list)
{
	if(list->Current != list->First && list->Current != list->Last && list->Size > 0)
	{
		if(list->FreeData != NULL)
			list->FreeData(list->Current->Data);

		p_ll_node_t toDelete = list->Current;
		
		list->Current = toDelete->Prev;
		list->Current->Next = toDelete->Next;
		toDelete->Next->Prev = list->Current;

		free(toDelete);
		
		list->Size--;
	}
}

void ll_append(p_ll_list_t list, void *data)
{
	p_ll_node_t newNode = ll_create_node(data);
	newNode->Next = list->Last;
	newNode->Prev = list->Last->Prev;

	newNode->Prev->Next = newNode;
	list->Last->Prev = newNode;
	list->Size++;
}	

void ll_prepend(p_ll_list_t list, void *data)
{
	p_ll_node_t newNode = ll_create_node(data);
	newNode->Next = list->First->Next;
	newNode->Prev = list->First;

	newNode->Next->Prev = newNode;
	list->First->Next = newNode;
	list->Size++;
}	

void ll_insert(p_ll_list_t list, void *data)
{
	p_ll_node_t newNode = ll_create_node(data);
	newNode->Prev = list->Current;
	newNode->Next = list->Current->Next;
	newNode->Prev->Next = newNode;
	newNode->Next->Prev = newNode;
	list->Size++;
}	
	
void ll_insert_before(p_ll_list_t list, void *data)
{
	p_ll_node_t newNode = ll_create_node(data);
	newNode->Prev = list->Current->Prev;
	newNode->Next = list->Current;
	newNode->Prev->Next = newNode;
	newNode->Next->Prev = newNode;
	list->Size++;
}	

////////////////////////////////////////////////////////////////////////////////
/// Private functions implementations

p_ll_node_t ll_create_node(void *data)
{
	p_ll_node_t node = (p_ll_node_t) malloc( sizeof(ll_node_t) );
	node->Data = data;

	return node;
}	
