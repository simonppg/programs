#if !defined (_TEST_H_)
#define _TEST_H_

#define K 2<<9
#define M 2<<19
#define G 2<<29

typedef struct KiloByte
{
	char data[K/sizeof(char)];
} KiloByte;

typedef struct MegaByte
{
	char data[M/sizeof(char)];
} MegaByte;

typedef struct s_4k
{
	KiloByte data[4];
} s_4k;

typedef struct s_16k
{
	KiloByte data[16];
} s_16k;

typedef struct s_64k
{
	KiloByte data[64];
} s_64k;

typedef struct s_256k
{
	KiloByte data[256];
} s_256k;

typedef struct s_4m
{
	MegaByte data[4];
} s_4m;

typedef struct s_16m
{
	MegaByte data[16];
} s_16m;

void test(void *arg);

#endif