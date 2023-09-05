#include "Buffer/StaticBuffer.h"
#include "Cache/OpenRelTable.h"
#include "Disk_Class/Disk.h"
#include "FrontendInterface/FrontendInterface.h"

#include <cstring>
#include <iostream>
using namespace std;

// void updateAttr(char relName[], char oldAttr[], char updAttr[])
// {

//   // get attribute catalogue block and it's header
//   RecBuffer attrCatBuffer(ATTRCAT_BLOCK);
//   HeadInfo attrCatHeader;

//   attrCatBuffer.getHeader(&attrCatHeader);

//   // search through all attribute records
//   for (int i = 0; i < attrCatHeader.numEntries; i++)
//   {
//     // declare attrCatRecord
//     Attribute attrCatRecord[ATTRCAT_NO_ATTRS];

//     // now get the records one by one
//     attrCatBuffer.getRecord(attrCatRecord, i);

//     /* attribute catalog entry corresponds to the current relation */
//     if (strcmp(attrCatRecord[ATTRCAT_REL_NAME_INDEX].sVal, relName) == 0 && strcmp(attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal, oldAttr) == 0)
//     {
//       strcpy(attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal, updAttr);
//       attrCatBuffer.setRecord(attrCatRecord, i);
//       std::cout << "Updated\n";
//       break;
//     }
//     if (i == attrCatHeader.numSlots - 1)
//     {
//       // re initializing the slot index
//       i = -1;
//       // updating the buffer block with next block;
//       attrCatBuffer = RecBuffer(attrCatHeader.rblock);
//       // updating the header
//       attrCatBuffer.getHeader(&attrCatHeader);
//     }
//   }
// }

int main(int argc, char *argv[])
{
  Disk disk_run;

  /*
  to update attribue
  char rel_name[16] = "Students", old_attr[16] = "Class", upd_attr[16] = "Batch";
  updateAttr(rel_name, old_attr, upd_attr);
  */

  // create objects for the relation catalog and attribute catalog
  RecBuffer relCatBuffer(RELCAT_BLOCK);
  RecBuffer attrCatBuffer(ATTRCAT_BLOCK);

  HeadInfo relCatHeader;
  HeadInfo attrCatHeader;

  // load the headers of both the blocks into relCatHeader and attrCatHeader.
  // (we will implement these functions later)
  relCatBuffer.getHeader(&relCatHeader);
  attrCatBuffer.getHeader(&attrCatHeader);

  for (int i = 0, noOfAttrs = 0; i < relCatHeader.numEntries; i++)
  {

    Attribute relCatRecord[RELCAT_NO_ATTRS]; // will store the record from the relation catalog

    relCatBuffer.getRecord(relCatRecord, i);

    printf("Relation: %s\n", relCatRecord[RELCAT_REL_NAME_INDEX].sVal);

    for (int j = 0; j < relCatRecord[RELCAT_NO_ATTRIBUTES_INDEX].nVal; j++, noOfAttrs++)
    {

      // declare attrCatRecord and load the attribute catalog entry into it
      Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
      attrCatBuffer.getRecord(attrCatRecord, noOfAttrs);

      if (strcmp(attrCatRecord[ATTRCAT_REL_NAME_INDEX].sVal, relCatRecord[RELCAT_REL_NAME_INDEX].sVal) == 0)
      {
        const char *attrType = attrCatRecord[ATTRCAT_ATTR_TYPE_INDEX].nVal == NUMBER ? "NUM" : "STR";
        printf("  %s: %s\n", attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal, attrType);
      }
      if (noOfAttrs == attrCatHeader.numSlots - 1)
      {
        // re initializing the slot index
        noOfAttrs = -1;
        // updating the buffer block with next block;
        attrCatBuffer = RecBuffer(attrCatHeader.rblock);
        // updating the header
        attrCatBuffer.getHeader(&attrCatHeader);
      }
    }
    printf("\n");
  }

  return 0;
}
