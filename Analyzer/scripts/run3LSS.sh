for i in $(cat $1);
do
	analyze run3LSS $i /UserDisk2/othrif/data/MiniNtuple/v48/$i.root
done
