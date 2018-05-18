path='/Users/bandre/C/ft_nm-ft_otool_binaire_de_test/hell'

files=`ls $path`
for file in $files;
do
	echo $path/$file
	./nm $path/$file > test1
	nm $path/$file > test2
	diff test1 test2
	
done
