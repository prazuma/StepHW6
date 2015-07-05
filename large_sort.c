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
  FILE* fpT;
  FILE fileArray[10];
  int num = 1000 * 1000 / sizeof(int); //約1MB分
  int* buffer = (int*)malloc(num * sizeof(int));
  int* bufferW = (int*)malloc(num * sizeof(int) * 2);
  int isTemp = 0;
  while (1) {
    size_t ret = fread(buffer, sizeof(int), num, fp);
    if (ret == 0) {
      break;
    }
    qsort(buffer, ret, sizeof(int), (int(*)(const void*, const void*))int_cmp);
    //ここで一時ファイルを作成
    if(isTemp != 0){
      int* buffer2 = (int*)malloc(num * sizeof(int));
      size_t ret2 = fread(buffer2, sizeof(int), num, fpT);
      int i = 0, j = 0, count = 0;
      while(i < ret && j < ret2){
	if(buffer[i] < buffer2[j]){
	  bufferW[count++] = buffer[i++];
	}
	else{
	  bufferW[count++] = buffer2[j++];
	}
      }
      int k;
      if(i != ret){
	for(k = i; k < ret; k++){
	  bufferW[count++] = buffer[k];
	}
      }
      else{
	for(k = j; j < ret2; j++){
	  bufferW[count++] = buffer2[k];
	}
      }
      fwrite(bufferW, sizeof(int), ret+ret2, fpW);
    }
    fpT = tmpfile();

    size_t test = fwrite(buffer, sizeof(int), ret, fpT);
    rewind(fpT);
    isTemp = 1;
    /*
    fread(buffer, sizeof(int), ret, fpT);
    int i;
    for(i = 0; i < ret; i++){
      printf("%d\n", buffer[i]);
    }
    */
    //fileArray[count++] = fpT;
  }

  //size_t ret = fwrite(buffer, sizeof(int), num, fpW);
  free(buffer);
  fclose(fp);
  fclose(fpW);
  return 0;
}


