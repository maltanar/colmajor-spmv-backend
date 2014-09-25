#!/bin/sh

PE_COUNTS="2 4 8 16"

matrices=(bcsstm21 p0548 webbase-1M mc2depi cryg2500 scircuit ex36 shipsec1 cant psmigr_1)
nonzero_counts=(3600 1887 3105536 2100225 12349 958936 53099 3568176 4007383 543160)
col_counts=(3600 724 1000005 525825 2500 170998 3079 140874 62541 3140)

OUTPUT_DIR="traces-interleaved"

mkdir -p $OUTPUT_DIR

for peCount in $PE_COUNTS; do
  for i in {0..9}; do
    matrix=${matrices[$i]}
    nzcnt=${nonzero_counts[$i]}
    colcnt=${col_counts[$i]}
    echo "./addrgen-interleaved $nzcnt $colcnt $peCount > $OUTPUT_DIR/k6_${matrix}_${peCount}_interleaved.trc"
    ./addrgen-interleaved $nzcnt $colcnt $peCount > $OUTPUT_DIR/k6_${matrix}_${peCount}_interleaved.trc
  done
done
