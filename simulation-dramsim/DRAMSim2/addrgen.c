#include <stdio.h>

void main()
{
  unsigned int numStreams = 4;
  
//    printf("Enter number of parallel streams: ");
  scanf("%u", &numStreams);
  
  
  unsigned int numReferences = 100000;  // 4194304
  unsigned long int streamBase =(unsigned long int)(2048 * 1024 * 1024) / numStreams;
  unsigned int unitStride = 8;
  
  scanf("%u", &unitStride);

/*  

  
  printf("Enter number of references per stream: ");
  scanf("%u", &numReferences);
  
  printf("Enter stream base: ");
  scanf("%u", &streamBase);
*/
  
  for(unsigned long int i = 0; i < numReferences; i++)
  {
    for(unsigned int stream=0; stream < numStreams; stream++)
      printf("0x%016lX P_FETCH %u\n", streamBase*stream+unitStride*i, i*numStreams+stream);
  }
}
