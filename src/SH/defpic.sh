#!/bin/sh
tmpdir=".tmp_dir" 

if [ ! -d "$tmpdir" ]; then
	mkdir $tmpdir
fi

pic_name=$1
watch_dir_name=$2
shift
shift

for outdir
do 
  echo $outdir
done

exit 0;
