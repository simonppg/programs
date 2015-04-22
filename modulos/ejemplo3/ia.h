
#define BLOCK_SIZE 10
struct infinite_array {
	/* the data for this block */
	float
	data[BLOCK_SIZE];
	/* pointer to the next array */
	struct infinite_array *next;
};

#define ia_init(array_ptr) {(array_ptr)->next = NULL;}

extern int ia_get(struct infinite_array *array_ptr, int index);

extern void ia_store(struct infinite_array * array_ptr, int index, int store_data);