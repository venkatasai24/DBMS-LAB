#include "Buffer/StaticBuffer.h"
#include "Cache/OpenRelTable.h"
#include "Disk_Class/Disk.h"
#include "FrontendInterface/FrontendInterface.h"
#include<iostream>
#include<cstring>

int main(int argc, char *argv[]) {
  Disk disk_run;

  unsigned char buffer[BLOCK_SIZE];
  for(int j=0;j<=3;j++) {
    Disk::readBlock(buffer,j);
    for(int i=0;i<BLOCK_SIZE;i++) std::cout<<(int)buffer[i]<<" ";
    std::cout<<std::endl;
  }

  return 0;
}