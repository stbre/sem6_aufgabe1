#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

static const char* in_filename = "foobar.txt";
static const char* out_filename = "result.txt";

#define MAX_LINE_BUFFER  256
#define MAX_TEXT_LINES 1024 

static uint64_t result[MAX_TEXT_LINES];
static int32_t operands_a[MAX_TEXT_LINES];
static int32_t operands_b[MAX_TEXT_LINES];

typedef struct statistics 
{
	uint32_t min_operand_a;
	uint32_t max_operand_a;
	uint32_t min_operand_b;
	uint32_t max_operand_b;
	uint32_t avg_operand_a;
	uint32_t avg_operand_b;
	uint32_t sum_operand_a;
	uint32_t sum_operand_b;
	uint32_t counter;
}statistics_t;

/**
 * @struct listNode 
 * @brief This struct defines a list element or
 *        somethimes called a list node.
 */
typedef struct listNode 
{
	/**@brief Pointer to previous Element */
	struct listNode *pPrev;
	/**@brief Pointer to next Element */
	struct listNode *pNext;
	/**@brief Operant A for the MAC Operation */
	uint32_t operand_a;
	/**@brief Operant B for the MAC Operation */
	uint32_t operand_b;
	/**@brief Result the MAC Operation */
	uint64_t result;
} listNode_t ;

typedef struct listNodeMem 
{
	listNode_t node;
	uint32_t inUse;
} listNodeMem_t;

#define STATIC_MEM 1 /* use static memory pool instead of malloc/free*/
#define MEM_POOL_SIZE 124 /* memory pool size */

/** @brief the static memory pool itself */
listNodeMem_t list_node_mem_pool[MEM_POOL_SIZE];
/**
 * @struct doubleLinkedList 
 * @brief Helper struct to hold the head and Tail of the list
 */
typedef struct doubleLinkedList 
{
	/** @brief Pointer to the head of the list. NULL if list is empty. */
	listNode_t *headOfList;
	/** @brief Pointer to the tail of the list. NULL if list is empty. */
	listNode_t *tailOfList;
}doubleLinkedList_t;