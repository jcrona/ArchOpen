/**************************************************************************/
/*
      libsnss.c

      (C) 2000 The SNSS Group
      See README.TXT file for license and terms of use.

      $Id: snss.c,v 1.4 2006/07/25 20:38:36 sfxgligli Exp $
*/
/**************************************************************************/

#include "snss.h"

/**************************************************************************/
/* This section deals with endian-specific code. */
/**************************************************************************/

unsigned int swap32 (unsigned int source)
{
#ifdef USE_LITTLE_ENDIAN
   unsigned char buffer[4];
   
   buffer[0] = ((unsigned char *) &source)[3];
   buffer[1] = ((unsigned char *) &source)[2];
   buffer[2] = ((unsigned char *) &source)[1];
   buffer[3] = ((unsigned char *) &source)[0];

   //return *((unsigned int *) buffer);
   return (buffer[3]<<24|buffer[2]<<16|buffer[1]<<8|buffer[0]);
#else /* !USE_LITTLE_ENDIAN */
   return source;
#endif /* !USE_LITTLE_ENDIAN */
}

unsigned short swap16 (unsigned short source)
{
#ifdef USE_LITTLE_ENDIAN
   unsigned char buffer[2];
   
   buffer[0] = ((unsigned char *) &source)[1];
   buffer[1] = ((unsigned char *) &source)[0];

   return (buffer[1]<<8|buffer[0]);//*((unsigned short *) buffer);
#else /* !USE_LITTLE_ENDIAN */
   return source;
#endif /* !USE_LITTLE_ENDIAN */
}

SNSS_RETURN_CODE SNSS_ReadBlockHeader (SnssBlockHeader *header, SNSS_FILE *snssFile)
{
   unsigned char *headerBytes=malloc(12);

   if (read (snssFile->fp,headerBytes, 12)<=0)
   {
      free(headerBytes);
      return SNSS_READ_FAILED;
   }
   strncpy (header->tag, &headerBytes[0], TAG_LENGTH);
   header->tag[4] = '\0';
   header->blockVersion = headerBytes[7]<<24|headerBytes[6]<<16|headerBytes[5]<<8|headerBytes[4];//*((unsigned int *) &headerBytes[4]);
   header->blockVersion = swap32 (header->blockVersion);
   header->blockLength = headerBytes[11]<<24|headerBytes[10]<<16|headerBytes[9]<<8|headerBytes[8];//*((unsigned int *) &headerBytes[8]);
   header->blockLength = swap32 (header->blockLength);

   free(headerBytes);
   return SNSS_OK;
}

/**************************************************************************/

SNSS_RETURN_CODE SNSS_WriteBlockHeader (SnssBlockHeader *header, SNSS_FILE *snssFile)
{
   unsigned char *headerBytes=malloc(12);
   unsigned int tempInt;

   strncpy (&headerBytes[0], header->tag, TAG_LENGTH);

   tempInt = swap32 (header->blockVersion);
   headerBytes[4] = ((unsigned char *) &tempInt)[0];
   headerBytes[5] = ((unsigned char *) &tempInt)[1];
   headerBytes[6] = ((unsigned char *) &tempInt)[2];
   headerBytes[7] = ((unsigned char *) &tempInt)[3];

   tempInt = swap32 (header->blockLength);
   headerBytes[8] = ((unsigned char *) &tempInt)[0];
   headerBytes[9] = ((unsigned char *) &tempInt)[1];
   headerBytes[10] = ((unsigned char *) &tempInt)[2];
   headerBytes[11] = ((unsigned char *) &tempInt)[3];

   if (write (snssFile->fp,headerBytes, 12)<=0)
   {
      free(headerBytes);
      return SNSS_WRITE_FAILED;
   }

   free(headerBytes);
   return SNSS_OK;
}

/**************************************************************************/

const char *
SNSS_GetErrorString (SNSS_RETURN_CODE code)
{
   switch (code)
   {
   case SNSS_OK:
      return "no error";

   case SNSS_BAD_FILE_TAG:
      return "not an SNSS file";

   case SNSS_OPEN_FAILED:
      return "could not open SNSS file";

   case SNSS_CLOSE_FAILED:
      return "could not close SNSS file";

   case SNSS_READ_FAILED:
      return "could not read from SNSS file";

   case SNSS_WRITE_FAILED:
      return "could not write to SNSS file";

   case SNSS_OUT_OF_MEMORY:
      return "out of memory";

   case SNSS_UNSUPPORTED_BLOCK:
      return "unsupported block type";

   default:
      return "unknown error";
   }
}

/**************************************************************************/
/* functions for reading and writing SNSS file headers */
/**************************************************************************/

SNSS_RETURN_CODE SNSS_ReadFileHeader (SNSS_FILE *snssFile)
{
   if (read (snssFile->fp, snssFile->headerBlock.tag, 4)<=0)
   {
      return SNSS_READ_FAILED;
   }

   if (0 != strncmp(snssFile->headerBlock.tag, "SNSS", 4))
   {
      return SNSS_BAD_FILE_TAG;
   }
   
   snssFile->headerBlock.tag[4] = '\0';

   if (read (snssFile->fp, &snssFile->headerBlock.numberOfBlocks, sizeof (unsigned int))<=0)
   {
      return SNSS_READ_FAILED;
   }
   snssFile->headerBlock.numberOfBlocks = swap32 (snssFile->headerBlock.numberOfBlocks);

   return SNSS_OK;
}

/**************************************************************************/

SNSS_RETURN_CODE SNSS_WriteFileHeader (SNSS_FILE *snssFile)
{
   unsigned int tempInt;
   unsigned char writeBuffer[8];

   /* always place the SNSS tag in this field */
   strncpy (&writeBuffer[0], "SNSS", 4);
   tempInt = swap32 (snssFile->headerBlock.numberOfBlocks);
   writeBuffer[4] = ((unsigned char *) &tempInt)[0];
   writeBuffer[5] = ((unsigned char *) &tempInt)[1];
   writeBuffer[6] = ((unsigned char *) &tempInt)[2];
   writeBuffer[7] = ((unsigned char *) &tempInt)[3];

   if (write (snssFile->fp, writeBuffer, 8)<=0)
   {
      return SNSS_WRITE_FAILED;
   }

   return SNSS_OK;
}

/**************************************************************************/
/* general file manipulation functions */
/**************************************************************************/
SNSS_RETURN_CODE
SNSS_OpenFile (SNSS_FILE **snssFile, char *filename, SNSS_OPEN_MODE mode)
{
   *snssFile = (SNSS_FILE*)malloc(sizeof(SNSS_FILE));
   if (NULL == *snssFile)
   {
      return SNSS_OUT_OF_MEMORY;
   }

   (*snssFile)->mode = mode;

   if (SNSS_OPEN_READ == mode)
      (*snssFile)->fp = open (filename, O_RDONLY);

   else
   {
      (*snssFile)->fp = open (filename, O_RDWR | O_CREAT);
      (*snssFile)->headerBlock.numberOfBlocks = 0;
   }

   if ((*snssFile)->fp<0)
   {
      free(*snssFile);
      *snssFile = NULL;
      return SNSS_OPEN_FAILED;
   }

   if (SNSS_OPEN_READ == mode)
      return SNSS_ReadFileHeader(*snssFile);
   else
      return SNSS_WriteFileHeader(*snssFile);
}

/**************************************************************************/

SNSS_RETURN_CODE
SNSS_CloseFile (SNSS_FILE **snssFile)
{
//   int prevLoc;
   SNSS_RETURN_CODE code;

   /* file was never open, so this should indicate success- kinda. */
   if (NULL == *snssFile)
   {
      return SNSS_OK;
   }

   if (SNSS_OPEN_WRITE == (*snssFile)->mode)
   {
      //prevLoc = ftell((*snssFile)->fp);
      lseek((*snssFile)->fp, 0, SEEK_SET);

      /* write the header again to get block count correct */
      if (SNSS_OK != (code = SNSS_WriteFileHeader(*snssFile)))
         return SNSS_CLOSE_FAILED;

      //fseek((*snssFile)->fp, prevLoc, SEEK_SET);
   }

   if (close ((*snssFile)->fp) != 0)
   {
      return SNSS_CLOSE_FAILED;
   }

   free(*snssFile);
   *snssFile = NULL;

   return SNSS_OK;
}

/**************************************************************************/

SNSS_RETURN_CODE 
SNSS_GetNextBlockType (SNSS_BLOCK_TYPE *blockType, SNSS_FILE *snssFile)
{
   unsigned char *tagBuffer;//[TAG_LENGTH + 1];

   //pos=ftell(snssFile->fp);
   tagBuffer=(unsigned char*)malloc(TAG_LENGTH+1);
   if (read (snssFile->fp, tagBuffer, TAG_LENGTH)<=0)

   {
	    free(tagBuffer);
      return SNSS_READ_FAILED;
   }
   tagBuffer[TAG_LENGTH] = 0;
//   	DrawMessage(tagBuffer,0);

   /* reset the file pointer to the start of the block */
   if (lseek (snssFile->fp, -TAG_LENGTH, SEEK_CUR)<=0)
   //if (fseek (snssFile->fp, pos, SEEK_SET) != 0)
   {
	    free(tagBuffer);
      return SNSS_READ_FAILED;
   }


   /* figure out which type of block it is */
   if (strcmp (tagBuffer, "BASR") == 0)
   {
	    free(tagBuffer);
      *blockType = SNSS_BASR;
      return SNSS_OK;
   }
   else if (strcmp (tagBuffer, "VRAM") == 0)
   {
	    free(tagBuffer);
      *blockType = SNSS_VRAM;
      return SNSS_OK;
   }
   else if (strcmp (tagBuffer, "SRAM") == 0)
   {
	    free(tagBuffer);
      *blockType = SNSS_SRAM;
      return SNSS_OK;
   }
   else if (strcmp (tagBuffer, "MPRD") == 0)
   {
	    free(tagBuffer);
      *blockType = SNSS_MPRD;
      return SNSS_OK;
   }
   else if (strcmp (tagBuffer, "CNTR") == 0)
   {
   	  free(tagBuffer);
      *blockType = SNSS_CNTR;
      return SNSS_OK;
   }
   else if (strcmp (tagBuffer, "SOUN") == 0)
   {
   	  free(tagBuffer);
      *blockType = SNSS_SOUN;
      return SNSS_OK;
   }
   else
   {
   	  free(tagBuffer);
      *blockType = SNSS_UNKNOWN_BLOCK;
      return SNSS_OK;
   }
}

/**************************************************************************/

SNSS_RETURN_CODE SNSS_SkipNextBlock (SNSS_FILE *snssFile)
{
   unsigned int blockLength;

   /* skip the block's tag and version */
   if (lseek (snssFile->fp, TAG_LENGTH + sizeof (unsigned int), SEEK_CUR)<=0)
   {
      return SNSS_READ_FAILED;
   }

   /* get the block data length */
   if (read (snssFile->fp, &blockLength, sizeof (unsigned int))<=0)
   {
      return SNSS_READ_FAILED;
   }
   blockLength = swap32 (blockLength);

   /* skip over the block data */
   if (lseek (snssFile->fp, blockLength, SEEK_CUR)<=0)
   {
      return SNSS_READ_FAILED;
   }

   return SNSS_OK;
}

/**************************************************************************/
/* functions for reading and writing base register blocks */
/**************************************************************************/

SNSS_RETURN_CODE SNSS_ReadBaseBlock (SNSS_FILE *snssFile)
{
   unsigned char *blockBytes;//[BASE_BLOCK_LENGTH];
   SnssBlockHeader header;
         

   if (SNSS_ReadBlockHeader (&header, snssFile) != SNSS_OK)
   {
      return SNSS_READ_FAILED;
   }

   blockBytes=(unsigned char*)malloc(BASE_BLOCK_LENGTH);

   if (read (snssFile->fp, blockBytes, MIN (header.blockLength, BASE_BLOCK_LENGTH))<=0)
   {
   	  free(blockBytes);
      return SNSS_READ_FAILED;
   }

   snssFile->baseBlock.regA = blockBytes[0x0];
   snssFile->baseBlock.regX = blockBytes[0x1];
   snssFile->baseBlock.regY = blockBytes[0x2];
   snssFile->baseBlock.regFlags = blockBytes[0x3];
   snssFile->baseBlock.regStack = blockBytes[0x4];
   snssFile->baseBlock.regPc = (blockBytes[0x6]<<8)|blockBytes[0x5];//*((unsigned short *) &blockBytes[0x5]);
   snssFile->baseBlock.regPc = swap16 (snssFile->baseBlock.regPc);
   snssFile->baseBlock.reg2000 = blockBytes[0x7];
   snssFile->baseBlock.reg2001 = blockBytes[0x8];

   memcpy (&snssFile->baseBlock.cpuRam, &blockBytes[0x9], 0x800);
   memcpy (&snssFile->baseBlock.spriteRam, &blockBytes[0x809], 0x100);
   memcpy (&snssFile->baseBlock.ppuRam, &blockBytes[0x909], 0x1000);
   memcpy (&snssFile->baseBlock.palette, &blockBytes[0x1909], 0x20);
   memcpy (&snssFile->baseBlock.mirrorState, &blockBytes[0x1929], 0x4);
   snssFile->baseBlock.vramAddress = (blockBytes[0x192D+1]<<8)|blockBytes[0x192D];//*((unsigned short *) &blockBytes[0x192D]);
   snssFile->baseBlock.vramAddress = swap16 (snssFile->baseBlock.vramAddress);
   snssFile->baseBlock.spriteRamAddress = blockBytes[0x192F];
   snssFile->baseBlock.tileXOffset = blockBytes[0x1930];

   free(blockBytes);

   return SNSS_OK;
}

/**************************************************************************/

SNSS_RETURN_CODE SNSS_WriteBaseBlock (SNSS_FILE *snssFile)
{
   SnssBlockHeader header;
   SNSS_RETURN_CODE returnCode;
   unsigned char *blockBytes;//[BASE_BLOCK_LENGTH];
   unsigned short tempShort;

   strcpy (header.tag, "BASR");
   header.blockVersion = SNSS_BLOCK_VERSION;
   header.blockLength = BASE_BLOCK_LENGTH;
   if ((returnCode = SNSS_WriteBlockHeader (&header, snssFile)) != SNSS_OK)
   {
      return returnCode;
   }

   blockBytes=(unsigned char*)malloc(BASE_BLOCK_LENGTH);

   blockBytes[0x0] = snssFile->baseBlock.regA;
   blockBytes[0x1] = snssFile->baseBlock.regX;
   blockBytes[0x2] = snssFile->baseBlock.regY;
   blockBytes[0x3] = snssFile->baseBlock.regFlags;
   blockBytes[0x4] = snssFile->baseBlock.regStack;
   tempShort = swap16 (snssFile->baseBlock.regPc);
   blockBytes[0x5] = ((char *) &tempShort)[0];
   blockBytes[0x6] = ((char *) &tempShort)[1];
   blockBytes[0x7] = snssFile->baseBlock.reg2000;
   blockBytes[0x8] = snssFile->baseBlock.reg2001;
   memcpy (&blockBytes[0x9], &snssFile->baseBlock.cpuRam, 0x800);
   memcpy (&blockBytes[0x809], &snssFile->baseBlock.spriteRam, 0x100);
   memcpy (&blockBytes[0x909], &snssFile->baseBlock.ppuRam, 0x1000);
   memcpy (&blockBytes[0x1909], &snssFile->baseBlock.palette, 0x20);
   memcpy (&blockBytes[0x1929], &snssFile->baseBlock.mirrorState, 0x4);
   tempShort = swap16 (snssFile->baseBlock.vramAddress);
   blockBytes[0x192D] = ((unsigned char *) &tempShort)[0];
   blockBytes[0x192E] = ((unsigned char *) &tempShort)[1];
   blockBytes[0x192F] = snssFile->baseBlock.spriteRamAddress;
   blockBytes[0x1930] = snssFile->baseBlock.tileXOffset;

   if (write (snssFile->fp, blockBytes, BASE_BLOCK_LENGTH)<=0)
   {
      free(blockBytes);
      return SNSS_WRITE_FAILED;
   }

   free(blockBytes);
   snssFile->headerBlock.numberOfBlocks++;

   return SNSS_OK;
}

/**************************************************************************/
/* functions for reading and writing VRAM blocks */
/**************************************************************************/

SNSS_RETURN_CODE SNSS_ReadVramBlock (SNSS_FILE *snssFile)
{
   SnssBlockHeader header;
   unsigned char *tmp;
   int i;

   if (SNSS_ReadBlockHeader (&header, snssFile) != SNSS_OK)
   {
      return SNSS_READ_FAILED;
   }

   tmp=(unsigned char*)malloc(header.blockLength);
   if (read (snssFile->fp, tmp/*snssFile->vramBlock.vram*/, header.blockLength)<=0)
   {
   	  free(tmp);
      return SNSS_READ_FAILED;
   }

   for (i=0;i<header.blockLength;i++) snssFile->vramBlock.vram[i]=tmp[i];
   free(tmp);
   snssFile->vramBlock.vramSize = header.blockLength;

   return SNSS_OK;
}

/**************************************************************************/

SNSS_RETURN_CODE SNSS_WriteVramBlock (SNSS_FILE *snssFile)
{
   SnssBlockHeader header;
   SNSS_RETURN_CODE returnCode;

   strcpy (header.tag, "VRAM");
   header.blockVersion = SNSS_BLOCK_VERSION;
   header.blockLength = snssFile->vramBlock.vramSize;
   if ((returnCode = SNSS_WriteBlockHeader (&header, snssFile)) != SNSS_OK)
   {
      return returnCode;
   }

   if (write (snssFile->fp, snssFile->vramBlock.vram, snssFile->vramBlock.vramSize)<=0)
   {
      return SNSS_WRITE_FAILED;
   }

   snssFile->headerBlock.numberOfBlocks++;

   return SNSS_OK;
}

/**************************************************************************/
/* functions for reading and writing SRAM blocks */
/**************************************************************************/

SNSS_RETURN_CODE SNSS_ReadSramBlock (SNSS_FILE *snssFile)
{
   SnssBlockHeader header;
   unsigned char *tmp;
   int i;

   if (SNSS_ReadBlockHeader (&header, snssFile) != SNSS_OK)
   {
      return SNSS_READ_FAILED;
   }

   if (read (snssFile->fp, &snssFile->sramBlock.sramEnabled, 1)<=0)
   {
      return SNSS_READ_FAILED;
   }

   /* read blockLength - 1 bytes to get all of the SRAM */
   tmp=(unsigned char*)malloc(MIN (header.blockLength - 1, SRAM_8K));
   if (read (snssFile->fp, tmp/*snssFile->sramBlock.sram*/, MIN (header.blockLength - 1, SRAM_8K))<=0)
   {
   	free(tmp);
      return SNSS_READ_FAILED;
   }

   for (i=0;i<MIN (header.blockLength - 1, SRAM_8K);i++) snssFile->sramBlock.sram[i]=tmp[i];
   
   	free(tmp);
   /* SRAM size is the size of the block - 1 (SRAM enabled byte) */
   snssFile->sramBlock.sramSize = header.blockLength - 1;

   return SNSS_OK;
}

/**************************************************************************/

SNSS_RETURN_CODE SNSS_WriteSramBlock (SNSS_FILE *snssFile)
{
   SnssBlockHeader header;
   SNSS_RETURN_CODE returnCode;

   strcpy (header.tag, "SRAM");
   header.blockVersion = SNSS_BLOCK_VERSION;
   /* length of block is size of SRAM plus SRAM enabled byte */
   header.blockLength = snssFile->sramBlock.sramSize + 1;
   if ((returnCode = SNSS_WriteBlockHeader (&header, snssFile)) != SNSS_OK)
   {
      return returnCode;
   }

   if (write (snssFile->fp, &snssFile->sramBlock.sramEnabled, 1)<=0)
   {
      return SNSS_WRITE_FAILED;
   }

   if (write (snssFile->fp, snssFile->sramBlock.sram, snssFile->sramBlock.sramSize)<=0)
   {
      return SNSS_WRITE_FAILED;
   }

   snssFile->headerBlock.numberOfBlocks++;

   return SNSS_OK;
}

/**************************************************************************/
/* functions for reading and writing mapper data blocks */
/**************************************************************************/

SNSS_RETURN_CODE SNSS_ReadMapperBlock (SNSS_FILE *snssFile)
{
   unsigned char *blockBytes;
   int i;
   SnssBlockHeader header;
   

   if (SNSS_ReadBlockHeader (&header, snssFile) != SNSS_OK)
   {
      return SNSS_READ_FAILED;
   }

   if ((blockBytes = (unsigned char *) malloc (0x8 + 0x10 + 0x80)) == NULL)
   {
      return SNSS_OUT_OF_MEMORY;
   }

   if (read (snssFile->fp, blockBytes, MIN (0x8 + 0x10 + 0x80, header.blockLength))<=0)
   {
      free(blockBytes);
      return SNSS_READ_FAILED;
   }

   for (i = 0; i < 4; i++)
   {
      snssFile->mapperBlock.prgPages[i] = (blockBytes[i * 2+1]<<8)|blockBytes[i * 2];//*((unsigned short *) &blockBytes[i * 2]);
      snssFile->mapperBlock.prgPages[i] = swap16 (snssFile->mapperBlock.prgPages[i]);
   }

   for (i = 0; i < 8; i++)
   {
      snssFile->mapperBlock.chrPages[i] = (blockBytes[0x8 + (i * 2)+1]<<8)|blockBytes[0x8 + (i * 2)];//*((unsigned short *) &blockBytes[0x8 + (i * 2)]);
      snssFile->mapperBlock.chrPages[i] = swap16 (snssFile->mapperBlock.chrPages[i]);
   }

   memcpy (snssFile->mapperBlock.extraData.mapperData, &blockBytes[0x18], 0x80);

   free (blockBytes);

   return SNSS_OK;
}

/**************************************************************************/

SNSS_RETURN_CODE SNSS_WriteMapperBlock (SNSS_FILE *snssFile)
{
   SnssBlockHeader header;
   unsigned char *blockBytes;//[MAPPER_BLOCK_LENGTH];
   unsigned short tempShort;
   int i;
   SNSS_RETURN_CODE returnCode;

   strcpy (header.tag, "MPRD");
   header.blockVersion = SNSS_BLOCK_VERSION;
   header.blockLength = MAPPER_BLOCK_LENGTH;
   if ((returnCode = SNSS_WriteBlockHeader (&header, snssFile)) != SNSS_OK)
   {
      return returnCode;
   }
   
	blockBytes=(unsigned char*)malloc(MAPPER_BLOCK_LENGTH);

   for (i = 0; i < 4; i++)
   {
      tempShort = swap16 (snssFile->mapperBlock.prgPages[i]);
      blockBytes[(i * 2) + 0] = ((unsigned char *) &tempShort)[0];
      blockBytes[(i * 2) + 1] = ((unsigned char *) &tempShort)[1];
   }

   for (i = 0; i < 8; i++)
   {
      tempShort = swap16 (snssFile->mapperBlock.chrPages[i]);
      blockBytes[0x8 + (i * 2) + 0] = ((unsigned char *) &tempShort)[0];
      blockBytes[0x8 + (i * 2) + 1] = ((unsigned char *) &tempShort)[1];
   }

   memcpy (&blockBytes[0x18], snssFile->mapperBlock.extraData.mapperData, 0x80);

   if (write (snssFile->fp, blockBytes, MAPPER_BLOCK_LENGTH)<=0)
   {
      free(blockBytes);
      return SNSS_WRITE_FAILED;
   }

   free(blockBytes);
   snssFile->headerBlock.numberOfBlocks++;

   return SNSS_OK;
}

/**************************************************************************/
/* functions for reading and writing controller data blocks */
/**************************************************************************/

SNSS_RETURN_CODE SNSS_ReadControllersBlock (SNSS_FILE *snssFile)
{
   return SNSS_OK;
}

/**************************************************************************/

SNSS_RETURN_CODE SNSS_WriteControllersBlock (SNSS_FILE *snssFile)
{
   return SNSS_OK;
}

/**************************************************************************/
/* functions for reading and writing sound blocks */
/**************************************************************************/

SNSS_RETURN_CODE SNSS_ReadSoundBlock (SNSS_FILE *snssFile)
{
   SnssBlockHeader header;
   

   if (SNSS_ReadBlockHeader (&header, snssFile) != SNSS_OK)
   {
      return SNSS_READ_FAILED;
   }

   if (read (snssFile->fp, snssFile->soundBlock.soundRegisters, MIN (header.blockLength, 0x16))<=0)
   {
      return SNSS_READ_FAILED;
   }

   return SNSS_OK;
}

/**************************************************************************/

SNSS_RETURN_CODE SNSS_WriteSoundBlock (SNSS_FILE *snssFile)
{
   SnssBlockHeader header;
   SNSS_RETURN_CODE returnCode;

   strcpy (header.tag, "SOUN");
   header.blockVersion = SNSS_BLOCK_VERSION;
   header.blockLength = SOUND_BLOCK_LENGTH;
   if ((returnCode = SNSS_WriteBlockHeader (&header, snssFile)) != SNSS_OK)
   {
      return returnCode;
   }

   if (write (snssFile->fp, snssFile->soundBlock.soundRegisters, SOUND_BLOCK_LENGTH)<=0)
   {
      return SNSS_WRITE_FAILED;
   }

   snssFile->headerBlock.numberOfBlocks++;

   return SNSS_OK;
}

/**************************************************************************/
/* general functions for reading and writing SNSS data blocks */
/**************************************************************************/

SNSS_RETURN_CODE
SNSS_ReadBlock (SNSS_FILE *snssFile, SNSS_BLOCK_TYPE blockType)
{
   switch (blockType)
   {
   case SNSS_BASR:
      return SNSS_ReadBaseBlock (snssFile);

   case SNSS_VRAM:
      return SNSS_ReadVramBlock (snssFile);

   case SNSS_SRAM:
      return SNSS_ReadSramBlock (snssFile);

   case SNSS_MPRD:
      return SNSS_ReadMapperBlock (snssFile);

   case SNSS_CNTR:
      return SNSS_ReadControllersBlock (snssFile);

   case SNSS_SOUN:
      return SNSS_ReadSoundBlock (snssFile);

   case SNSS_UNKNOWN_BLOCK:
   default:
       return SNSS_UNSUPPORTED_BLOCK;
   }
}

/**************************************************************************/

SNSS_RETURN_CODE
SNSS_WriteBlock (SNSS_FILE *snssFile, SNSS_BLOCK_TYPE blockType)
{
   switch (blockType)
   {
   case SNSS_BASR:
      return SNSS_WriteBaseBlock (snssFile);

   case SNSS_VRAM:
      return SNSS_WriteVramBlock (snssFile);

   case SNSS_SRAM:
      return SNSS_WriteSramBlock (snssFile);

   case SNSS_MPRD:
      return SNSS_WriteMapperBlock (snssFile);

   case SNSS_CNTR:
      return SNSS_WriteControllersBlock (snssFile);

   case SNSS_SOUN:
      return SNSS_WriteSoundBlock (snssFile);

   case SNSS_UNKNOWN_BLOCK:
   default:
       return SNSS_UNSUPPORTED_BLOCK;
   }
}

/*
** $Log: snss.c,v $
** Revision 1.4  2006/07/25 20:38:36  sfxgligli
** - aones update
** - widgets: added setRect to WIDGET, added menu_indexFromCaption and non focudable items to MENU
** - other minor changes
**
** Revision 1.3  2006/06/13 20:07:48  sfxgligli
** aoNes update
**
** Revision 1.2  2006/05/23 20:44:21  sfxgligli
** - fixes for min & max
** - re-added dsp & osd irqs
**
** Revision 1.1  2006/05/22 23:18:55  sfxgligli
** Adding aoNES (port of LittleJohnGP by yoyo)
**
** Revision 1.5  2000/07/09 15:37:21  matt
** all block read/write calls now pass through a common handler
**
** Revision 1.4  2000/07/09 03:39:06  matt
** minor modifications
**
** Revision 1.3  2000/07/08 16:01:39  matt
** added bald's changes, made error checking more robust
**
** Revision 1.2  2000/07/04 04:46:06  matt
** simplified handling of SNSS states
**
** Revision 1.1  2000/06/29 14:13:28  matt
** initial revision
**
*/