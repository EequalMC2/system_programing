#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mybsort(void *base, size_t count, size_t width, int(*cmp)(const void*, const void*))
{

	size_t i, k ,m;
	char *cbase = (char *)base;
	char *p1, *p2;
	char temp;

	for (i = 0; i < count; ++i)
	   for(k = 0; k < count - 1 - i; ++k){
		p1 = cbase + k* width;
		p2 = cbase + (k + 1) * width;
		if(cmp(p1,p2) > 0){
		   for(m = 0; m < width; ++m){
			temp = p1[m];
			p1[m] = p2[m];   
			p2[m] = temp;
			}
		   }

		}

}

struct PERSON {
    char name[32];
    int no;
};

int mycmp(const void *p1, const void *p2)
{
	const struct PERSON *pi1 = (const struct PERSON* )p1;
	const struct PERSON  *pi2 = (const struct PERSON* )p2;

	if(pi1->no > pi2->no)
	  return 1;

	if(pi1->no < pi2->no )
	  return -1;

	 return 0;

}




int main()
{
int i;
struct PERSON people[] = {

	{"samebody1", 54},
	{"somebody4", 23},
	{"somebody3", 47},
	{"somebody2",   20},
};



mybsort(people, 4, sizeof(struct PERSON), mycmp);
//qsort(people, 4, sizeof(struct PERSON), mycmp);
for(i = 0; i < sizeof( people ) / sizeof(struct PERSON); ++i)
  printf("%s  %d \n", people[i].name , people[i].no );
printf("------------------\n");


}

