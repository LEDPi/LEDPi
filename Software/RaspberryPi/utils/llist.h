#ifndef _H_LLIST_
#define _H_LLIST_

////////////////////////////////////////////////////////////////////////////////
/// FILE: llist 
/// DESC: Describes a simple doubly linked list. The list is in an object 
///	  oriented style, so it needs to be constructed and to be released using 
///	  the create and delete methods.
////////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct __llist_internal_node
{
	struct __llist_internal_node* Next;
	struct __llist_internal_node* Prev;

	void *Data;
} ll_node_t, *p_ll_node_t;

typedef struct
{
	uint32_t Size;
	p_ll_node_t First;
	p_ll_node_t Last;
	p_ll_node_t Current;

	void (*FreeData)(void *);
} ll_list_t, *p_ll_list_t;

/// //////////////////////////////////////////////////////////////////////////// 
/// Creates a empty linked list. Don't forget to free the memory after using the
/// linked list.
/// 
/// PARA:
///	freeData:	function to release a data item in a list's node. Will 
///			be called before deleting the list item.
/// //////////////////////////////////////////////////////////////////////////// 
p_ll_list_t ll_create(void (*freeData)(void *));  

/// //////////////////////////////////////////////////////////////////////////// 
/// Deletes and releases the linked lists memory
///
/// PARA:
/// 	list:	Pointer to the linked list. 
/// //////////////////////////////////////////////////////////////////////////// 
void ll_delete(p_ll_list_t list);

/// //////////////////////////////////////////////////////////////////////////// 
/// Returns the data from the current selected list item if there is one. 
/// Otherwise it will return NULL.
///
/// PARA:
/// 	list:	Pointer to the linked list. 
/// //////////////////////////////////////////////////////////////////////////// 
void *ll_get(p_ll_list_t list);

/// //////////////////////////////////////////////////////////////////////////// 
/// Will select the next element in the linked list. The return value is set to 
/// true if there was a following element, otherwise it is set to false.
/// 
/// PARA:
/// 	list:	Pointer to the linked list. 
/// //////////////////////////////////////////////////////////////////////////// 
bool ll_next(p_ll_list_t list);

/// //////////////////////////////////////////////////////////////////////////// 
/// Will select the previous element in the linked list. The return valiue is 
/// set to true, it there was a previous element, otherwise it is set to false.
///
/// PARA:
/// 	list:	Pointer to the linked list. 
/// //////////////////////////////////////////////////////////////////////////// 
bool ll_prev(p_ll_list_t list);

/// //////////////////////////////////////////////////////////////////////////// 
/// Will select the item after the last list element. 
///
/// PARA:
/// 	list:	Pointer to the linked list. 
/// //////////////////////////////////////////////////////////////////////////// 
void ll_last(p_ll_list_t list);

/// //////////////////////////////////////////////////////////////////////////// 
/// Will select the item before the first list element.
///
/// PARA:
/// 	list:	Pointer to the linked list. 
/// //////////////////////////////////////////////////////////////////////////// 
void ll_first(p_ll_list_t list);

/// //////////////////////////////////////////////////////////////////////////// 
/// Will remove the current element from the list.
/// 
/// PARA:
/// 	list:	Pointer to the linked list. 
/// //////////////////////////////////////////////////////////////////////////// 
void ll_remove(p_ll_list_t list);

/// //////////////////////////////////////////////////////////////////////////// 
/// Appends an item at the end of the list.
/// 
/// PARA:
/// 	list:	Pointer to the linked list. 
/// //////////////////////////////////////////////////////////////////////////// 
void ll_append(p_ll_list_t list, void *data);

/// //////////////////////////////////////////////////////////////////////////// 
/// Inserts an item at the lists first item.
/// 
/// PARA:
/// 	list:	Pointer to the linked list. 
/// //////////////////////////////////////////////////////////////////////////// 
void ll_prepend(p_ll_list_t list, void *data);

/// //////////////////////////////////////////////////////////////////////////// 
/// Inserts an item after the current item.
/// 
/// PARA:
/// 	list:	Pointer to the linked list. 
/// //////////////////////////////////////////////////////////////////////////// 
void ll_insert(p_ll_list_t list, void *data); 

/// //////////////////////////////////////////////////////////////////////////// 
/// Iserts an item before the current item.
/// 
/// PARA:
/// 	list:	Pointer to the linked list. 
/// //////////////////////////////////////////////////////////////////////////// 
void ll_insert_before(p_ll_list_t list, void *data);

#endif // _H_LLIST_
