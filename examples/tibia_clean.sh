#!/bin/sh

echo Removing common files

rm -fr common/cmd common/web common/daisy-seed common/lv2 common/vst3 common/android common/ios

dirs="fx_ap1 fx_ap2 fx_balance fx_bitcrush fx_cab fx_chorus fx_clip fx_comb fx_comp fx_delay fx_dist fx_drive fx_eq_3band fx_flanger fx_fuzz fx_hp1 fx_hs1 fx_lp1 synth_simple fxpp_ap1 fxpp_ap2 fxpp_balance fxpp_bitcrush fxpp_cab fxpp_chorus fxpp_clip fxpp_comb fxpp_comp fxpp_delay fxpp_dist fxpp_drive fxpp_eq_3band fxpp_flanger fxpp_fuzz fxpp_hp1 fxpp_hs1 fxpp_lp1 synthpp_simple"

for d in $dirs; do
	echo Removing data files for $d

	rm -fr $d/cmd $d/web $d/daisy-seed $d/lv2 $d/vst3 $d/android $d/ios
done
