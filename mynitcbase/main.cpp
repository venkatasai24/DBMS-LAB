#include "Buffer/StaticBuffer.h"
#include "Cache/OpenRelTable.h"
#include "Disk_Class/Disk.h"
#include "FrontendInterface/FrontendInterface.h"

#include <cstring>
#include <iostream>

int main(int argc, char *argv[]) {
  Disk disk_run;
  StaticBuffer buffer;
  OpenRelTable cache;

  
  for (int i = 0; i <= ATTRCAT_RELID; i++) {

      // get the relation catalog entry using RelCacheTable::getRelCatEntry()
      RelCatEntry rel;
      RelCacheTable::getRelCatEntry(i, &rel);
      printf("Relation: %s\n", rel.relName);

      for (int j = 0; j < rel.numAttrs; j++) {
          /*
            get the attribute catalog entry for (rel-id i, attribute offset j)
            in attrCatEntry using AttrCacheTable::getAttrCatEntry()
          */
          AttrCatEntry att;
          AttrCacheTable::getAttrCatEntry(i, j, &att);

          const char *attrType = att.attrType == NUMBER ? "NUM" : "STR";
          printf("  %s: %s\n", att.attrName, attrType);
      }
  }

  return 0;
}