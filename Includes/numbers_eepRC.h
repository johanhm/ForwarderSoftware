/***************************************************************************************************
*                                                                                                  *
*  FILENAME:                                                                                      */
/**\file        numbers_eepRC.h
*
*  \brief       Description of the modul numbers, function numbers and error codes in one place.
*               For eeprom RC module.
*
*
*/
/***************************************************************************************************
* (c) Copyright by BOSCH REXROTH AG, all rights reserved                                           *
****************************************************************************************************
*
* PROJECT:                   API RC30 platform
*
* FILE VERSION INFORMATION:  $Revision: 5901 $
*                            $Date: 2013-06-03 13:30:05 +0200 (Mo, 03 Jun 2013) $
*                            $Author: gtg2si $
*
* REVISION HISTORY:
*
*
***************************************************************************************************/

#ifndef _NUMBERS_EEPRC_H_D     /* replace it with the filename in capital letters */
#define _NUMBERS_EEPRC_H_D     /* replace it with the filename in capital letters */

// PRQA S 4870 ++

/* Definition of the function numbers for the EEP module. */
// 1. Parameter: Modul | Function

/*--- check mirror ram of eeprom data
      remark: For errors which can repaired automatically an error is logged if error occured
              5 times or more!
*/
/* compare error of page with shadow page
   <error parameter> = number of page
 */
#define EEP_CHECK_CORR1_DU16        (EEP_DU16 | 0x01)
/* CRC error shadow page
   <error parameter> = number of page
*/
#define EEP_CHECK_CORR2_DU16        (EEP_DU16 | 0x02)
/* compare error of page with shadow page and CRC error shadow page
   <error parameter> = number of page
*/
#define EEP_CHECK_CORR3_DU16        (EEP_DU16 | 0x03)
/* CRC error page (page with shadow page)
   <error parameter> = number of page
*/
#define EEP_CHECK_CORR4_DU16        (EEP_DU16 | 0x04)
/* compare error of page with shadow page and CRC error page
   <error parameter> = number of page
*/
#define EEP_CHECK_CORR5_DU16        (EEP_DU16 | 0x05)
/* CRC error page and CRC error shadow page
   <error parameter> = number of page
*/
#define EEP_CHECK_CORR6_DU16        (EEP_DU16 | 0x06)
/* compare error and CRC error of page and CRC error of shadow page of shadow page
  (worst error)
   <error parameter> = number of page
*/
#define EEP_CHECK_COMP_CRC_DU16     (EEP_DU16 | 0x07)
/* CRC error
   remark: page without a shadow page
   <error parameter> = number of page
*/
#define EEP_CHECK_CRC_DU16          (EEP_DU16 | 0x08)
/* Generally check error
   It is relatated to the program flow.
   <error parameter> = number of page
*/
#define EEP_CHECK_General_DU16      (EEP_DU16 | 0x09)

/*--- ee_saveSysValue_s16()
   <error parameter> = number of parameter
                       0xFF: buffer (queue) overflow of eeprom server
*/
#define EEP_EESAVESYSVALUE_DU16     (EEP_DU16 | 0x0A)

/*--- ee_saveSysArray_s16()
   <error parameter> = number of parameter
                       0xFF: buffer (queue) overflow of eeprom server
*/
#define EEP_EESAVESYSARRAY_DU16     (EEP_DU16 | 0x0B)

/*--- ee_saveSysPage_s16()
   <error parameter> = number of parameter
                       0xFF: buffer (queue) overflow of eeprom server
*/
#define EEP_EESAVESYSPAGE_DU16      (EEP_DU16 | 0x0C)

/*--- ree_setSysValue()
   <error parameter> = number of parameter
*/
#define EEP_REESETSYSVALUE_DU16     (EEP_DU16 | 0x0D)

/*--- ree_setSysArray()
   <error parameter> = number of parameter
*/
#define EEP_REESETSYSARRAY_DU16     (EEP_DU16 | 0x0E)

/*--- ee_saveValue()
   <error parameter> = number of parameter
                       0xFF: buffer (queue) overflow of eeprom server
*/
#define EEP_EESAVEVALUE_DU16        (EEP_DU16 | 0x0F)

/*--- ee_saveArray()
   <error parameter> = number of parameter
                       0xFF: buffer (queue) overflow of eeprom server
*/
#define EEP_EESAVEARRAY_DU16        (EEP_DU16 | 0x10)

/*--- ee_savePage()
   <error parameter> = number of parameter
                       0xFF: buffer (queue) overflow of eeprom server
*/
#define EEP_EESAVEPAGE_DU16         (EEP_DU16 | 0x11)

/*--- ree_setValue()
   <error parameter> = number of parameter
*/
#define EEP_REESETVALUE_DU16        (EEP_DU16 | 0x12)

/*--- ree_setArray()
   <error parameter> = number of parameter
*/
#define EEP_REESETARRAY_DU16        (EEP_DU16 | 0x13)

/*--- ree_getValue()
   <error parameter> = number of parameter
*/
#define EEP_REEGETVALUE_DU16        (EEP_DU16 | 0x14)

/*--- ree_getArray()
   <error parameter> = number of parameter
*/
#define EEP_REEGETARRAY_DU16        (EEP_DU16 | 0x15)

/*--- eeprom server
   write error
*/
#define EEP_EESERV_WRITE_DU16       (EEP_DU16 | 0x16)



/* writing into this EEPROM page is locked because a ree-write command was executed which
 *  was not completed by the according ee_savePage command
 */
#define ERR_EESERV_PAGE_LOCKED_DU8  (0xFE)

/* buffer (queue) overflow of eeprom server */
#define ERR_EESERV_BUF_OVFL_DU8     (0xFF)


// EEPROM version 7
// PRQA S 5000 ++
// The defines were already published and are compatible with RC/22.
#define EE_LASTSHADOWEDPAGE  15  //all pages from PAGE0 til this have a shadowpage
#define EE_OFFSET_SHADOW     16  //e.g. data stored on PAGE0,inverse data stored on PAGE16
#define EE_FIRSTSHADOWPAGE   EE_OFFSET_SHADOW
#define EE_LASTSHADOWPAGE    (EE_LASTSHADOWEDPAGE+EE_OFFSET_SHADOW)
#define EE_LASTPAGE          63
#define EE_CRCPAGE           63


#define PAGE_SIZE            256     // 256 sint16 per page within eeserver

/** page numbers for eeprom access via bios and low level functions */
/** see API documentation, prepared for 32kbyte SPI-EEPROM */
#define PAGE0      0     // this is the 'write protected' system page
#define PAGE1      1
#define PAGE2      2
#define PAGE3      3
#define PAGE4      4
#define PAGE5      5
#define PAGE6      6
#define PAGE7      7
#define PAGE8      8
#define PAGE9      9
#define PAGE10     10
#define PAGE11     11
#define PAGE12     12
#define PAGE13     13
#define PAGE14     14
#define PAGE15     15
#define PAGE16     16
#define PAGE17     17
#define PAGE18     18
#define PAGE19     19
#define PAGE20     20
#define PAGE21     21
#define PAGE22     22
#define PAGE23     23
#define PAGE24     24
#define PAGE25     25
#define PAGE26     26
#define PAGE27     27
#define PAGE28     28
#define PAGE29     29
#define PAGE30     30
#define PAGE31     31
#define PAGE32     32
#define PAGE33     33
#define PAGE34     34
#define PAGE35     35
#define PAGE36     36
#define PAGE37     37
#define PAGE38     38
#define PAGE39     39
#define PAGE40     40
#define PAGE41     41
#define PAGE42     42
#define PAGE43     43
#define PAGE44     44
#define PAGE45     45
#define PAGE46     46
#define PAGE47     47
#define PAGE48     48
#define PAGE49     49
#define PAGE50     50
#define PAGE51     51
#define PAGE52     52
#define PAGE53     53
#define PAGE54     54
#define PAGE55     55
#define PAGE56     56
#define PAGE57     57
#define PAGE58     58
#define PAGE59     59
#define PAGE60     60
#define PAGE61     61
#define PAGE62     62
#define PAGE63     63
// PRQA S 5000 --
// PRQA S 4870 --

#endif  /* _NUMBERS_EEPRC_H_D */

/* EOF ###########################################################################################*/
