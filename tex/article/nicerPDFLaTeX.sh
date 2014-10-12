#!/bin/bash

clear ;

initialPath=$(pwd) ;											# relative path of this script
finalPath=$(pwd) ;											# destination path for the .pdf files

if [ $1 ] && [ ${1/*./} = tex ] ; then									# first option is a .tex file
 	# fileWOHidden=${1/./} ;									# for hidden .tex files
 	# fileName=${fileWOHidden/.*/} ;
 	fileName=${1/.*/} ;
	if [ $2 ] ; then
		echo $2 ;
		if [ $2 = -a ] ; then
			pdflatex -halt-on-error -jobname=$fileName -output-directory=$finalPath $1 ;
			bibtex $fileName.aux ;
			pdflatex -halt-on-error -jobname=$fileName -output-directory=$finalPath $1 ;
		elif [ $2 = -d ] ; then
			pdflatex -halt-on-error -jobname=$fileName -output-directory=$finalPath $1 ;
		fi
	fi
	pdflatex -halt-on-error -jobname=$fileName -output-directory=$finalPath $1 ;

	cd $finalPath ;											# delete temporary files
	open $fileName.pdf ;										# open PDF
else
	echo "No files given, compile everything within this folder." ;
 	
	for f in $(ls -a | grep '.tex') ; do
 		# fileWOHidden=${f/./} ;								# for hidden .tex files
 		# fileName=${fileWOHidden/.*/} ;
 		fileName=${f/.*/} ;
		if [ $1 ] ; then
			if [ $1 = -a ] ; then
				pdflatex -interaction=batchmode  -halt-on-error -jobname=$fileName -output-directory=$finalPath $f ;
				pdflatex -interaction=batchmode  -halt-on-error -jobname=$fileName -output-directory=$finalPath $f ;
				bibtex $finalPath/$fileName.aux ;
			elif [ $1 = -d ] ; then
				pdflatex -interaction=batchmode -halt-on-error -jobname=$fileName -output-directory=$finalPath $f ;
			fi
		fi
		pdflatex -interaction=batchmode -halt-on-error -jobname=$fileName -output-directory=$finalPath $f ;
 	done

 	cd $finalPath ;
	open *.pdf ;
fi
 	
rm $(ls -a | egrep '.log|.aux|.bbl|.blg|.lof|.lol|.lot|.toc|.out') ;
cd Sections;
rm $(ls -a | egrep '.log|.aux|.bbl|.blg|.lof|.lol|.lot|.toc|.out') ;
echo "Finished."
