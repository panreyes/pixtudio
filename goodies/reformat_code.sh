#!/bin/bash
cd ..

cd core
for i in $(find -iname "*.[c,h]" | grep -v "monolithic_includes.h"); do
	clang-format -i -style=file $i;
done
