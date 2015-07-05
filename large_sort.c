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
  FILE* fpW = fopen("result", "wb");
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
  int *buffList[numTemp];
  size_t sizeList[numTemp];
  for(i = 0; i < numTemp; i++){
    buffList[i] = (int*)malloc(num * sizeof(int));
  }

  for(i = 0; i < numTemp; i++){
    rewind(fpT[i]);
    sizeList[i] = fread(buffList[i], sizeof(int), num, fpT[i]);
  }
  int count = 0;
  int point1 = 0, point2 = 0;
  int size1 = sizeList[0], size2 = sizeList[1];
  while(point1 < size1 && point2 < size2){
    if(buffList[0][point1] < buffList[1][point2])
      buffer[count++] = buffList[0][point1++];
    else
      buffer[count++] = buffList[1][point2++];
    if(count == num){
      fwrite(buffer, sizeof(int), num, fpW);
      count = 0;
    }
  }
  if(point1 != size1){
    for(i = point1; i < size1; i++){
      buffer[count++] = buffList[0][i];
      if(count == num){
	fwrite(buffer, sizeof(int), num, fpW);
	count = 0;
      }
    }
  }
  if(point2 != size2){
    for(i = point2; i < size2; i++){
      buffer[count++] = buffList[1][i];
      if(count == num){
	fwrite(buffer, sizeof(int), num, fpW);
	count = 0;
      }
    }
  }
  free(buffer);
  fclose(fp);
  fclose(fpW);
  return 0;
}


