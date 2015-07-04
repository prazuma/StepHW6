# StepHW6
1GB程度のメモリしか使わないという制約のもと、10GBのファイルをソートするもの  
入力ファイルは、*generate_array.c*で作成
$ gcc generate_array.c -o genarate_array  
$ ./gennerate_array test10000 10000 //10GBのファイルをtest10000という名前で生成  
出力ファイルは、*check_array.c*で正しくソートされているかを確認
$ gcc check_array.c -o check_array
$ ./check_array result10000 //result10000が正しくソートされているかチェック  
