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
  FILE fileArray[10];
  int num = 1000 * 1000 / sizeof(int); //約1MB分
  int* buffer = (int*)malloc(num * sizeof(int));
  int count = 0;
  while (1) {
    size_t ret = fread(buffer, sizeof(int), num, fp);
    if (ret == 0) {
      break;
    }
    qsort(buffer, ret, sizeof(int), (int(*)(const void*, const void*))int_cmp);
    //ここで一時ファイルを作成
    FILE* fpT;
    fpT = tmpfile();

    size_t test = fwrite(buffer, sizeof(int), ret, fpT);
    rewind(fpT);
    fread(buffer, sizeof(int), ret, fpT);
    int i;
    for(i = 0; i < ret; i++){
      printf("%d\n", buffer[i]);
    }
    //fileArray[count++] = fpT;
  }

  size_t ret = fwrite(buffer, sizeof(int), num, fpW);
  free(buffer);
  fclose(fp);
  fclose(fpW);
  return 0;
}


