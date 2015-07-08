#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double get_time(){
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + tv.tv_usec * 1e-6;
}

int int_cmp(const int *a, const int *b) {
    if (*a < *b)
        return (-1);
    else if (*a > *b)
        return (1);
    return (0);
}

FILE* mergeFile(FILE* fp1, FILE* fp2){
  if(fp1 == fp2) return fp1;
  FILE* fpTemp = tmpfile();
  int i = 0, j = 0, count = 0, k;
  int num = 1000 * 1000 * 500 / sizeof(int) / 2;
  int* buff1 = (int*)malloc(num * sizeof(int));
  int* buff2 = (int*)malloc(num * sizeof(int));
  int* buffer = (int*)malloc(num * sizeof(int));
  rewind(fp1);
  rewind(fp2);
  size_t size1 = fread(buff1, sizeof(int), num, fp1);
  size_t size2 = fread(buff2, sizeof(int), num, fp2);
  while(1){
    if(size1 == 0 || size2 == 0) break;
    while(i < size1 && j < size2){
      if(buff1[i] < buff2[j]){
	buffer[count++] = buff1[i++];
      }else{
	buffer[count++] = buff2[j++];
      }
      if(count == num){
	fwrite(buffer, sizeof(int), num, fpTemp);
	count = 0;
      }
    }
    if(i == size1){
      size1 = fread(buff1, sizeof(int), num, fp1);
      i = 0;
    }
    if(j == size2){
      size2 = fread(buff2, sizeof(int), num, fp2);
      j = 0;
    }
  }
  if(i != size1){
    for(k = i; k < size1; k++){
      buffer[count++] = buff1[k];
      if(count == num){
	fwrite(buffer, sizeof(int), num, fpTemp);
	count = 0;
      }
    }
  }
  if(j != size2){
    for(k = j; k < size2; k++){
      buffer[count++] = buff2[k];
      if(count == num){
	fwrite(buffer, sizeof(int), num, fpTemp);
	count = 0;
      }
    }
  }
  free(buff1);
  free(buff2);
  free(buffer);
  return fpTemp;
}

int decideSize(int a){
  int size = a / 2;
  if(a % 2 == 1) size++;
  return size;
}

int main(int argc, char** argv){
  double begin = get_time();
  char* fileName = argv[1];
  FILE* fp = fopen(fileName, "rb");
  FILE* fpW = fopen("result", "wb");
  //一時ファイルに保存(それぞれのファイルはソート済み)
  FILE* fpT[200];
  int k;
  for(k = 0; k < 200; k++){
    fpT[k] = tmpfile();
  }
  int num = 1000 * 1000 * 500 / sizeof(int);
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
  
  int firstNum = numTemp;
  while(1){
    if(numTemp == 1)
      break;
    numTemp = decideSize(numTemp);

    int i = 0, p1, p2;
    while(i < numTemp){
      p1 = i * 2;
      p2 = i * 2 + 1;
      if(p2 == firstNum)
	p2 = p2 - 1;
      fpT[i] = mergeFile(fpT[p1], fpT[p2]);
      i++;
    }
    firstNum = numTemp;
  }

  rewind(fpT[0]);
  while(1){
    size_t ret = fread(buffer, sizeof(int), num, fpT[0]);
    if(ret == 0)
      break;
    fwrite(buffer, sizeof(int), ret, fpW);
  }

  double end = get_time();
  printf("time: %.6lf sec\n", end - begin);

  free(buffer);
  fclose(fp);
  fclose(fpW);
  return 0;
}


