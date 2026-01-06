#include "Buffer/StaticBuffer.h"
#include "Cache/OpenRelTable.h"
#include "Disk_Class/Disk.h"
#include "FrontendInterface/FrontendInterface.h"
#include<cstring>
#include<iostream>

int main(int argc, char *argv[]) {
  Disk disk_run;

  // create objects for the relation catalog and attribute catalog
  RecBuffer relCatBuffer(RELCAT_BLOCK);
  

  HeadInfo relCatHeader;
  

  // load the headers of both the blocks into relCatHeader and attrCatHeader.
  // (we will implement these functions later)
  relCatBuffer.getHeader(&relCatHeader);
 

  for (int i=0;i<relCatHeader.numEntries;i++/* i = 0 to total relation count */) {

    Attribute relCatRecord[RELCAT_NO_ATTRS]; // will store the record from the relation catalog

    relCatBuffer.getRecord(relCatRecord, i);

    printf("Relation: %s\n", relCatRecord[RELCAT_REL_NAME_INDEX].sVal);
    int count=relCatRecord[RELCAT_NO_ATTRIBUTES_INDEX].nVal;
    int blockNum=ATTRCAT_BLOCK;
    while(count!=0){
    	if(blockNum==-1) //this is imp for termination condition
    		break;
	RecBuffer attrCatBuffer(blockNum);
	HeadInfo attrCatHeader;
	attrCatBuffer.getHeader(&attrCatHeader);
    for (int j=0;j<attrCatHeader.numEntries;j++/* j = 0 to number of entries in the attribute catalog */) {

      // declare attrCatRecord and load the attribute catalog entry into it
      Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
      attrCatBuffer.getRecord(attrCatRecord,j);

      if (strcmp(attrCatRecord[ATTRCAT_REL_NAME_INDEX].sVal, relCatRecord[RELCAT_REL_NAME_INDEX].sVal) == 0/* attribute catalog entry corresponds to the current relation */) {
        const char *attrType = attrCatRecord[ATTRCAT_ATTR_TYPE_INDEX].nVal == NUMBER ? "NUM" : "STR";
        printf("  %s: %s\n", attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal/* get the attribute name */, attrType);
        count--;
        if((strcmp(attrCatRecord[ATTRCAT_REL_NAME_INDEX].sVal,"Students")==0)&&(strcmp(attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal,"Class")==0)){
        strcpy(attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal, "Batch");
        attrCatBuffer.setRecord(attrCatRecord, j); // this will do disk write back so changes will be reflected in xfs-interface as well
        }
        
      }
    }
  blockNum=attrCatHeader.rblock;
  }
    printf("\n");
  }
  
  //post stage2 exercise Q2 printing
  printf("Post updation of Student relation\n");
  for (int i=0;i<relCatHeader.numEntries;i++/* i = 0 to total relation count */) {

    Attribute relCatRecord[RELCAT_NO_ATTRS]; // will store the record from the relation catalog

    relCatBuffer.getRecord(relCatRecord, i);

    printf("Relation: %s\n", relCatRecord[RELCAT_REL_NAME_INDEX].sVal);
    int count=relCatRecord[RELCAT_NO_ATTRIBUTES_INDEX].nVal;
    int blockNum=ATTRCAT_BLOCK;
    while(count!=0){
    	if(blockNum==-1)
    		break;
	RecBuffer attrCatBuffer(blockNum);
	HeadInfo attrCatHeader;
	attrCatBuffer.getHeader(&attrCatHeader);
    for (int j=0;j<attrCatHeader.numEntries;j++/* j = 0 to number of entries in the attribute catalog */) {

      // declare attrCatRecord and load the attribute catalog entry into it
      Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
      attrCatBuffer.getRecord(attrCatRecord,j);

      if (strcmp(attrCatRecord[ATTRCAT_REL_NAME_INDEX].sVal, relCatRecord[RELCAT_REL_NAME_INDEX].sVal) == 0/* attribute catalog entry corresponds to the current relation */) {
        const char *attrType = attrCatRecord[ATTRCAT_ATTR_TYPE_INDEX].nVal == NUMBER ? "NUM" : "STR";
        printf("  %s: %s\n", attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal/* get the attribute name */, attrType);
        count--;
        
      }
    }
  blockNum=attrCatHeader.rblock;
  }
    printf("\n");
  }
  

  return 0;
}
