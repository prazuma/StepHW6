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
  FILE* fpW = fopen("result", "ab");
  FILE* fpT[3];
  int k;
  for(k = 0; k < 3; k++){
    fpT[k] = tmpfile();
  }
  FILE fileArray[10];
  int num = 1000 * 1000 / sizeof(int); //約1MB分
  int* buffer = (int*)malloc(num * sizeof(int));
  int* bufferW = (int*)malloc(num * sizeof(int) * 2);
  int numTemp = 0;
  while (1) {
    size_t ret = fread(buffer, sizeof(int), num, fp);
    if (ret == 0) {
      break;
    }
    qsort(buffer, ret, sizeof(int), (int(*)(const void*, const void*))int_cmp);
    fwrite(buffer, sizeof(int), ret, fpT[numTemp++]);
  }
  int i, j;
  for(i = 0; i < numTemp; i++){
    rewind(fpT[i]);
    size_t ret = fread(buffer, sizeof(int), num, fpT[i]);
    for(j = 0; j < num; j++)
      printf("b: %d\n", buffer[j]);
  }
  free(buffer);
  fclose(fp);
  fclose(fpW);
  return 0;
}


