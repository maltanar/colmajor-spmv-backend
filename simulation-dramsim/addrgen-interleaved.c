#include <stdio.h>

void main(int argc, char *argv[])
{
  if(argc != 4)
  {
    printf("usage: addrgen-interleaved <num_nz> <num_cols> <num_PE>\n");
    return;
  }
  
  unsigned int numNZ = 0;
  unsigned int numCols = 0;
  unsigned int numPE = 0;
  
  sscanf(argv[1], "%u", &numNZ);
  sscanf(argv[2], "%u", &numCols);
  sscanf(argv[3], "%u", &numPE);
  
  // 8 bytes for matrix value per NZ
  // 8 bytes for dense vector value per column
  // 4 bytes for row index per NZ
  // 4 bytes for column length per column
  unsigned int totalSpMVData = numNZ*8 + numCols*8 + numNZ*4 + numCols*4;
  unsigned int memRequestsPerPE = (totalSpMVData / numPE) / 8; // 8 elements per burst 

  // assuming 2 GB DIMM here for round-robin distribution of banks for each PE
  unsigned long int peBase =(unsigned long int)(2048 * 1024 * 1024) / numPE;
  unsigned int unitStride = 64; // corresponds to burst length of bytes
  
  for(unsigned long int i = 0; i < memRequestsPerPE; i++)
  {
    for(unsigned int pe=0; pe < numPE; pe++)
      printf("0x%016lX P_FETCH %u\n", peBase*pe+unitStride*i, i);
  }
}
