#include "ia.h"
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

static struct infinite_array *ia_locate( struct infinite_array *array_ptr, int index, int *current_index_ptr)
{
	/* pointer to the current bucket */
	struct infinite_array *current_ptr;
	current_ptr = array_ptr;
	*current_index_ptr = index;
	while (*current_index_ptr >= BLOCK_SIZE) {
		if (current_ptr->next == NULL) {
			current_ptr->next = malloc(sizeof(struct infinite_array));
			if (current_ptr->next == NULL) {
				fprintf(stderr, "Error:Out of memory\n");
				exit(8);
			}
			memset(current_ptr->next, '\0', sizeof(struct
			infinite_array));
		}
		current_ptr = current_ptr->next;
		*current_index_ptr -= BLOCK_SIZE;
	}
	return (current_ptr);
}

void ia_store(struct infinite_array * array_ptr, int index, int store_data)
{
	/* pointer to the current bucket */
	struct infinite_array *current_ptr;
	int
	current_index;
	/* index into the current bucket */
	current_ptr = ia_locate(array_ptr, index, &current_index);
	current_ptr->data[current_index] = store_data;
}

int ia_get(struct infinite_array *array_ptr, int index)
{
	/* pointer to the current bucket */
	struct infinite_array *current_ptr;
	int
	current_index;
	/* index into the current bucket */
	current_ptr = ia_locate(array_ptr, index, &current_index);
	return (current_ptr->data[current_index]);
}