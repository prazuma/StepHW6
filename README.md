# StepHW6
##### 1GB程度のメモリしか使わないという制約のもと、バイナリファイルをソートするもの  

- 入力ファイルは、*generate_array.c*で作成してください  
  
```
$ gcc generate_array.c -o genarate_array  
$ ./gennerate_array test10000 10000  //10GBのファイルをtest10000という名前で生成  
```

- ソート実行
```
$ gcc large_sort.c -o large_sort
$ ./large_sort test10000
```

- 出力ファイルは、*check_array.c*で正しくソートされているかを確認  
  
```
$ gcc check_array.c -o check_array
$ ./check_array result  //result10000が正しくソートされているかチェック  
```
