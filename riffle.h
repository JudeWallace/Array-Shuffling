#if !defined(RIFFLE_H)
#define RIFFLE_H

void riffle_once(void *L, int len, int size, void *work);
void riffle(void *L, int len, int size, int N);
int cmp_int(void *a, void *b);
int cmp_str(void *a, void *b);
int check_shuffle(void *L, int len, int size, int (*cmp)(void *, void *));
float quality(int *numbers, int len);
float average_quality(int N, int shuffles, int trials);

#endif