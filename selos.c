#include <stdlib.h>
#include <stdio.h>

int cmpfunc (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}

int solve(int target, int current, int* available, int aSize, int* solution, int *sSize) {
	#ifdef DEBUG
	printf("trying to get %d with {", target);
	int i;
	for (i = 0; i < aSize; i++)
		printf("%d ", available[i]);
	printf("} current at %d\n", current);
	#endif

	if(current == target) return 1;
	if(current > target) return 0;
	if(aSize == 0) return 0;

	int solved = 0;
	int tryN = aSize-1;

	while (!solved && tryN >= 0) {
		if(available[tryN] <= target){
			int guess = current + available[tryN];
			solved = solve(target, guess, available, tryN, solution, sSize);
		}
		if(!solved)
			tryN--;
	}

	if(solved){
		solution[*sSize] = available[tryN];
		(*sSize)++;
	}

	return solved;
}

int main(int argc, char const *argv[]) {
	int value = atoi(argv[1]);
	int aSize = argc-2;
	int available[aSize];
	int solution[aSize];
	int i=0,sSize=0;

	for (i = 0; i < aSize; i++)
		available[i] = atoi(argv[i+2]);

	qsort(available,aSize,sizeof(int),cmpfunc);
	// for (i = 0; i < aSize; i++) {
	// 	printf("available[%d]:%d\n", i, available[i]);
	// }

	int solved = solve(value, 0, available, aSize, solution, &sSize);
	if(solved){
		printf("Solution: ");
		for (i = 0; i < sSize; i++)
			printf("%d ", solution[i]);
		printf("\n");
	}else
		printf("Unsolvable\n");

	return 0;
}
