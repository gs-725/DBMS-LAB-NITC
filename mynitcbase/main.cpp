#include "Buffer/StaticBuffer.h"
#include "Cache/OpenRelTable.h"
#include "Disk_Class/Disk.h"
#include "FrontendInterface/FrontendInterface.h"
#include<cstring>
#include<iostream>

int main(int argc, char *argv[]) {
  /* Initialize the Run Copy of Disk */
  Disk disk_run;
 

   unsigned char buffer[BLOCK_SIZE];// this means the buffer is containing 2048 bytes we have to access each byte and do int cast and also this is just the block 0 first 10 bytes actually for Block allocation map block 0-3 is allocated so there is 4*2048 bytes
   Disk::readBlock(buffer, 0);
  for(int j=0;j<10;j++)
  	std::cout <<int(buffer[j])<<std::endl;
  			

  return 0;
  // StaticBuffer buffer;
  // OpenRelTable cache;

  //return FrontendInterface::handleFrontend(argc, argv);
}
