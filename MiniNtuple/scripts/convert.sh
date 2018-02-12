#!/bin/bash

echo "Float_t/Int_t"
for i in $(cat variables.txt)
do
	printf "	       	evt->%s = oldTree->%s;\n" "$i" "$i";
done
echo "\n\n"
echo "vector"
for i in $(cat variables.txt)
do
	printf "	       	evt->%s[j] = oldTree->%s->at(i);\n" "$i" "$i";
done
echo "\n\n"
echo "/O:"
for i in $(cat variables.txt)
do
	printf "%s/IOF:" "$i";
done
echo "setnewntpbranches"
for i in $(cat variables.txt)
do
	printf "   b->GetLeaf("\"%s\"")->SetAddress(&(evt->%s));\n" "$i" "$i";
done



