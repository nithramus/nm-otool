path='/Users/bandre/C/ft_nm-ft_otool_binaire_de_test/hell'
rm yolo
files=`ls $path`
for file in $files;
do
	echo $path/$file
	./nm $path/$file > binary_test/test1
	nm $path/$file > binary_test/test2
	diff binary_test/test1 binary_test/test2 > binary_test/diff_$file
	echo $path/$file >> yolo
	diff binary_test/test1 binary_test/test2 >> yolo
	
done
https://github.com/UgurcanOzdemir/ft_nm-ft_otool_binaire_de_test
