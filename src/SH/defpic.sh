#!/bin/bash

if [ "$#" -lt 3 ]; then
    echo "Illegal number of parameters"
    exit 1;
fi

tmpdir=".tmp_dir"
pic_name=$1
pic_name_no_ext=${pic_name:0:-4}
watch_dir_name=$2

#---------CHECKING TMP_DIR---------- 
if [ ! -d "$tmpdir" ]; then
	mkdir $tmpdir
fi
#------CHECKING TMP_DIR (END)-------

#----------------CHECKING WATCHDIR------------
if [[ $watch_dir_name =~ ^$tmpdir(\/)?$ ]]; then
	echo "watch directory can't be named like that.Closing"
	exit 2
fi
if [ ! -d "$watch_dir_name" ]; then
	echo "Dat dir does not exist.Closing"
	exit 3
fi
if [[ ! $watch_dir_name =~ ^.*\/$ ]]; then
	watch_dir_name="$watch_dir_name/"
fi
#-----------CHECKING WATCHDIR (END)-----------

pic_full_path="$watch_dir_name$pic_name"

#---------CHECKING PICTURE----------
if [ ! -f $pic_full_path ]; then
    echo "picture \"$pic_full_path\" not found.Closing"
    exit 4
fi
#-----CHECKING PICTURE (END)-------

mv $pic_full_path $tmpdir
shift
shift

#----------MAIN PART-------------
mogrify -format png $tmpdir/$pic_name || exit 5
pngquant -f --ext .png --quality 10 $tmpdir/$pic_name_no_ext.png || exit 6
#----------MAIN PART (END)-------

for outdir
do 
	if [ "$outdir" == "watch_dir_name" ]; then
		echo "output dir can't be watch dir. Closing"
	fi
	if [ ! -d "$outdir" ]; then
		mkdir -p $outdir
		echo "$outdir was created."
	fi
cp $tmpdir/$pic_name_no_ext.png $outdir
done

rm -r $tmpdir/$pic_name
rm -r $tmpdir/$pic_name_no_ext.png

exit 0
