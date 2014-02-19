#!/bin/bash

if ! [ -x "$(which ant)" ]; then
	echo "Please install ANT"
	exit
fi

if [ $# -eq 1 ]; then
	if [ "$1" = "full" ]; then
		if ! [ -x "$(which ndk-build)" ]; then
			echo "You asked for full native compilation, but ndk-build is not in your PATH"
			exit
		fi
		echo "Will now compile JNI code"
		echo "========================="
		ndk-build clean
		ndk-build -j4
	fi
fi

# Temporarily remove the source code from the tree
cd assets
if ! [ -d $HOME/tmp ]; then
    mkdir $HOME/tmp
fi

for i in main.prg monkey_vs_robots.sav libraries includes; do
    mv $i $HOME/tmp
done

cd ..

ant clean
ant release
cp bin/MvR-release.apk ../../../releases/Android/MvR-release.apk

# And copy the sources back
cd assets

for i in main.prg monkey_vs_robots.sav libraries includes; do
    mv $HOME/tmp/$i $i
done
