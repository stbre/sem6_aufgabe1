#include "dl_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <Windows.h>
#include "stopwatch.h"

uint64_t do_mac_operation(int32_t operand_a,uint32_t operand_b,uint64_t result)
{
	return result + (operand_a * operand_b);
}

listNode_t* list_get_new_element(uint32_t operand_a,uint32_t operand_b,uint64_t result)
{
	listNode_t* ret = NULL;
	int i = 0;
#ifndef STATIC_MEM
	 ret = (listNode_t*)malloc(sizeof(listNode_t));
#else
	for (i = 0; i < MEM_POOL_SIZE; i++)
	{
		if(FALSE == list_node_mem_pool[i].inUse )
		{
			list_node_mem_pool[i].inUse = TRUE;
			ret = &(list_node_mem_pool[i].node);
			break;
		}
	}
#endif
	if(NULL != ret )
	{
		ret->operand_a = operand_a;
		ret->operand_b = operand_b;
		ret->result = result;
		ret->pPrev = NULL;
		ret->pNext = NULL;
	}
	return ret;
}

int list_push_back(doubleLinkedList_t *list, listNode_t* elem)
{
	if ( NULL == elem )
	{
		return EXIT_FAILURE;
	}
	if(NULL == list->tailOfList)
	{
		return list_push_front(list,elem);
	}
	else
	{
		return list_insert_after(list, list->tailOfList, elem);
	}
}

int list_push_front(doubleLinkedList_t *list , listNode_t* elem)
{
	if(NULL == elem )
	{
		return EXIT_FAILURE;
	}
	if ( NULL == list->headOfList )
	{
         list->headOfList = elem;
         list->tailOfList  = elem;
         elem->pPrev = NULL;
         elem->pNext = NULL;
		 return EXIT_SUCCESS;
	}
	else
	{
         return  list_insert_before(list, list->headOfList, elem);
	}
}

int list_insert_after(doubleLinkedList_t *list , listNode_t* old ,listNode_t* elem)
{
	elem->pPrev = old;
	elem->pNext = old->pNext;

	if(( NULL == old ) ||  (NULL == elem ) )
	{
		return EXIT_FAILURE;
	}
    if( NULL ==  old->pNext )
	{
         list->tailOfList = elem;
	}
    else
	{
		old->pNext->pPrev = elem; /* already checked for NULL !*/
	}
	old->pNext = elem;

	return EXIT_SUCCESS;
}

int list_insert_before(doubleLinkedList_t *list , listNode_t* old ,listNode_t* elem)
{
	int ret = EXIT_FAILURE;

	elem->pPrev = old->pPrev;
	elem->pNext = old;

	if(( NULL == old ) ||  (NULL == elem ) )
	{
		return EXIT_FAILURE;
	}
	if( NULL == old->pPrev )
	{
         list->headOfList = elem;
	}
    else
	{
         old->pPrev->pNext = elem; /* already checked for NULL */
	}
	old->pPrev  = elem;

	return ret;
}

void list_free_element(const listNode_t* elem)
{
	int i = 0;
#ifndef STATIC_MEM
	if( NULL != elem )
		free(elem);
#else
	for(i = 0; i < MEM_POOL_SIZE; i++ )
	{
		if(elem == &(list_node_mem_pool[i].node))
		{
			list_node_mem_pool[i].inUse = FALSE;
		}
	}
#endif
}


void calculate_statistics(statistics_t * stat,uint32_t operand_a,uint32_t operand_b)
{
	if(NULL != stat)
	{
		stat->max_operand_a = max(stat->max_operand_a,operand_a);
		stat->max_operand_b = max(stat->max_operand_b,operand_b);
		stat->min_operand_a = min(stat->min_operand_a,operand_a);
		stat->min_operand_b = min(stat->min_operand_b,operand_b);

		stat->sum_operand_a += operand_a;
		stat->sum_operand_b += operand_b;
		stat->counter++;
		stat->avg_operand_a = stat->sum_operand_a/stat->counter;
		stat->avg_operand_b = stat->sum_operand_b/stat->counter;
	}
}

uint32_t init_list_node_mem_pool(listNodeMem_t *pool, uint32_t size)
{
	int i = 0;
	if(NULL == pool)
	{
		return EXIT_FAILURE;
	}
	else
	{
		for(i = 0; i< size; i++)
		{
			pool[i].inUse = FALSE;
		}
		return EXIT_SUCCESS;
	}
}