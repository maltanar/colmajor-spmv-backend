#include <stdio.h>
#include <stdlib.h>

void main(int argc, char * argv[])
{
  if(argc != 4)
  {
    printf("usage: addrgen-baseline <num_nz> <num_cols> <num_PE>\n");
    return;
  }
  
  unsigned int numNZ = 0;
  unsigned int numCols = 0;
  unsigned int numPE = 0;
  
  sscanf(argv[1], "%u", &numNZ);
  sscanf(argv[2], "%u", &numCols);
  sscanf(argv[3], "%u", &numPE);
  
  /*scanf("%u", &numNZ);
  scanf("%u", &numCols);
  scanf("%u", &numPE);*/
  
  unsigned int averageColLength = numNZ / numCols; // to issue row ptr requests

  unsigned long int colPtrBase = 0, colPtrLength = 4 * numCols;
  unsigned long int rowIndBase = colPtrBase + colPtrLength, rowIndLength = 4 * numNZ;
  unsigned long int matrixValueBase = rowIndBase + rowIndLength, matrixValueLength = 8 * numNZ;
  unsigned long int denseVectorBase = matrixValueBase + matrixValueLength, denseVectorLength = 8 * numCols;
  
  unsigned int numReferences = (numNZ / 8) / numPE; // the per-NZ pes take the longest, and each burst gives 8 refs
  
  for(unsigned long int i = 0; i < numReferences; i++)
  {
    for(unsigned int pe=0; pe < numPE; pe++)
    {
      // each pe (or rather, backend) maps to four streams in baseline CSC
      // - col pointer/length requests (every AvgRowLen or AvgColLen cycles, if matrix is square)
      if(i % averageColLength == 0)
      {
        // global colptr base + PE colptr base offset + PE iteration offset
        printf("0x%016lX P_FETCH %u\n", colPtrBase + pe*(colPtrLength/numPE) + 64 * (i / averageColLength), i);
      }
      
      // - row ind requests (every cycle)
      printf("0x%016lX P_FETCH %u\n", rowIndBase + pe*(rowIndLength/numPE) + 64 * i, i);
      
      // - matrix value requests (every cycle)
      printf("0x%016lX P_FETCH %u\n", matrixValueBase + pe*(matrixValueLength/numPE) + 64 * i, i);
      
      // - dense vector requests (every cycle)
      printf("0x%016lX P_FETCH %u\n", denseVectorBase + pe*(denseVectorLength/numPE) + 64 * i, i); 
    }
  }
}
