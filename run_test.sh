./nm $1 > test1
nm $1 > test2
diff test1 test2
