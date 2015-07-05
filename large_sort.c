#include <stdio.h>
#include <stdlib.h>

int int_cmp(const int *a, const int *b) {
    if (*a < *b)
        return (-1);
    else if (*a > *b)
        return (1);
    return (0);
}

int main(int argc, char** argv){
  char* fileName = argv[1];
  FILE* fp = fopen(fileName, "rb");
  int num = 1000 * 1000 / sizeof(int); //約1MB分
  int* buffer = (int*)malloc(num * sizeof(int));
  while (1) {
    size_t ret = fread(buffer, sizeof(int), num, fp);
    if (ret == 0) {
      break;
    }
    qsort(buffer, ret, sizeof(int), (int(*)(const void*, const void*))int_cmp);
    int i;
    for (i = 0; i < num; i++) {
      printf("%d番目 = %d\n", i, buffer[i]);
    }
    buffer=sort(buffer, ret);
  }
  free(buffer);
  fclose(fp);
  return 0;
}


