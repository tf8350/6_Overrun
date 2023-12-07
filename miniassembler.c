/*--------------------------------------------------------------------*/
/* miniassembler.c                                                    */
/* Author: Bob Dondero, Donna Gabai                                   */
/*--------------------------------------------------------------------*/

#include "miniassembler.h"
#include <assert.h>
#include <stddef.h>

/*--------------------------------------------------------------------*/
/* Modify *puiDest in place,
   setting uiNumBits starting at uiDestStartBit (where 0 indicates
   the least significant bit) with bits taken from uiSrc,
   starting at uiSrcStartBit.
   uiSrcStartBit indicates the rightmost bit in the field.
   setField sets the appropriate bits in *puiDest to 1.
   setField never unsets any bits in *puiDest.                        */
static void setField(unsigned int uiSrc, unsigned int uiSrcStartBit,
                     unsigned int *puiDest, unsigned int uiDestStartBit,
                     unsigned int uiNumBits)
{
   /* Your code here */
   unsigned int uiSrcIso = 1;
   unsigned int uiIndex;

   /* calculate the value to AND with the soures to isolate the bits */
   for (uiIndex = 0; uiIndex < uiNumBits; uiIndex++) {
      uiSrcIso *= 2; /* get to the correct power of 2 */
   }
   uiSrcIso -= 1; /* subtract 1 */
   /* start at beginning of src bits */
   uiSrcIso = uiSrcIso << uiSrcStartBit;

   /* uiSrc AND uiSrcIso to isolate correct bits of Src */
   uiSrc = uiSrc & uiSrcIso;

   /* shift isolated source to start at dest start bit */
   uiSrc = uiSrc >> uiSrcStartBit;
   uiSrc = uiSrc << uiDestStartBit;

   /* set bits of *puiDest */
   *puiDest = *puiDest | uiSrc;

}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_mov(unsigned int uiReg, int iImmed)
{
   /* Your code here */
   unsigned int uiInstr = 0x52800000; /* op code for 32 bits */

   /* set dest reg */
   setField(uiReg, 0, &uiInstr, 0, 5);

   /* set immediate value */
   setField(iImmed, 0, &uiInstr, 5, 16);

   return uiInstr;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_adr(unsigned int uiReg, unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr;
   unsigned int uiDisp;

   /* Base Instruction Code */
   uiInstr = 0x10000000;

   /* register to be inserted in instruction */
   setField(uiReg, 0, &uiInstr, 0, 5);

   /* displacement to be split into immlo and immhi and inserted */
   uiDisp = (unsigned int)(ulAddr - ulAddrOfThisInstr);

   setField(uiDisp, 0, &uiInstr, 29, 2);
   setField(uiDisp, 2, &uiInstr, 5, 19);

   return uiInstr;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_strb(unsigned int uiFromReg,
   unsigned int uiToReg)
{
   unsigned int uiInstr = 0x39000000; /* set op codes and offset 0 */

   /* set "destination" register */
   setField(uiFromReg, 0, &uiInstr, 0, 5);

   /* set "source" register */
   setField(uiToReg, 0, &uiInstr, 5, 5);

   return uiInstr;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_b(unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr = 0x14000000; /* op code */
   unsigned int uiImmed;

   /* calculate immediate value */
   uiImmed = ulAddr - ulAddrOfThisInstr;

   /* set immediate value field */
   setField(uiImmed, 0, &uiInstr, 0, 26);

   return uiInstr;
}
