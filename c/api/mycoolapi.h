struct MyCoolApi
{
	int (*add)(int x, int y);
	int (*sub)(int x, int y);
};

struct MyCoolApi* my_cool_api_initialize(void);