#!/bin/sh

TRACE_DIR="traces-baseline"

TRACES=$(ls $TRACE_DIR)
PATH_TO_SIM="DRAMSim2/DRAMSim"
SYS_CONFIG="system-baseline.ini"
OUTPUT_FOLDER="results-baseline"
DRAM_DEVICE="DRAMSim2/ini/DDR3_micron_32M_8B_x4_sg125.ini"
DRAM_SIZE="2048"

mkdir -p $OUTPUT_FOLDER

for trace in $TRACES; do
  echo "Now Processing: $trace"
  $PATH_TO_SIM -t $TRACE_DIR/$trace -s $SYS_CONFIG -d $DRAM_DEVICE -S $DRAM_SIZE -n -c 10000000 > "$OUTPUT_FOLDER/result-$trace" 2> /dev/null
  cat "$OUTPUT_FOLDER/result-$trace" | grep "aggregate average bandwidth" | tail -n 1
  cat "$OUTPUT_FOLDER/result-$trace" | grep "Power Data" -A5 | tail -n 6
  echo "***********************************************************************"
done

