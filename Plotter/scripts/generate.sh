for i in {1..7};
do 
	echo "scaleLumi_Region(set.SR${i}, sf);";
done

echo "\n\n"

for i in {1..7};
do 
	echo "scaleXSect_Region(set.SR${i},  ind,  sf);";
done

echo "\n\n"

for i in {1..7};
do 
	echo "scaleXSect_SigRegion(set.SR${i}, ind, sf);";
done

echo "\n\n"

for i in {1..7};
do 
	echo "setFakeRates_Region(set.SR${i}, cf, sf1, sf2, sf3, sf4);";
done

echo "\n\n"

for i in {1..7};
do 
	echo "weightData_Region(set.SR${i});";
done

echo "\n\n"

for i in {1..7};
do 
	echo "weightData_SigRegion(set.SR${i});";
done

echo "\n\n"

for i in {1..7};
do 
	echo "distrRegion* paired_SR${i}[N_unc_paired];";
	echo "distrRegion* unpaired_SR${i}[N_unc_unpaired];";
done

echo "\n\n"

for i in {1..7};
do 
	echo "paired_SR${i}[j] = (&(temp_set->SR${i}));";
done

echo "\n\n"

for i in {1..7};
do 
	echo "unpaired_SR${i}[j] = (&(temp_set->SR${i}));";
done

echo "\n\n"

for i in {1..7};
do echo "draw_Region(set.SR${i}, sig.SR${i}, paired_SR${i}, unpaired_SR${i}, fit);";
done


echo "\n\n"

for i in {1..7};
do echo "my_set->SS3L.SR${i}.fs_comb.fakes_mean, sqrt( pow(my_set->SS3L.SR${i}.fs_comb.fakes_stat,2)+ pow(std::max(my_set->SS3L.SR${i}.fs_comb.fakes_systup, my_set->SS3L.SR${i}.fs_comb.fakes_systdn),2)),";
done

echo "\n\n"

for i in {1..7};
do echo "my_set->SS3L.SR${i}.fs_comb.backgr_mean[charge_flip_ind_fit],sqrt(pow( my_set->SS3L.SR${i}.fs_comb.backgr_stat[charge_flip_ind_fit],2) + pow( std::max(my_set->SS3L.SR${i}.fs_comb.backgr_systup[charge_flip_ind_fit], my_set->SS3L.SR${i}.fs_comb.backgr_systdn[charge_flip_ind_fit]),2)),";
done



echo "\n\n"

for i in {1..7};
do echo "my_set->SS3L.SR${i}.fs_comb.backgr_mean[N_DataMC],sqrt(pow( my_set->SS3L.SR${i}.fs_comb.backgr_stat[N_DataMC],2) + pow( std::max(my_set->SS3L.SR${i}.fs_comb.backgr_systup[N_DataMC], my_set->SS3L.SR${i}.fs_comb.backgr_systdn[N_DataMC]),2)),";
done




echo "\n\n"

for i in {1..7};
do 
	echo "my_set->SS3L.SR${i}.fs_comb.NJETS[0]->Integral(0, n_bins+1),"
done