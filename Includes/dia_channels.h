//**************************************************************************************************
//
//  FILENAME:    dia_channels.h
//
//  DESCRIPTION:
//! \file        dia_channels.h
//! \brief       header file with I/O channel indices for diagnostic functions
//
//**************************************************************************************************
// (c) Copyright by BOSCH REXROTH AG, all rights reserved
//**************************************************************************************************
//
// PROJECT:                   RC30_CNH_HVT
//                            Hardware: RC30-00D7
//
// FILE VERSION INFORMATION:  $Revision: 5903 $
//                            $Date: 2013-06-03 13:41:38 +0200 (Mo, 03 Jun 2013) $
//                            $Author: oub2si $
//
// REVISION HISTORY:
//
//
//**************************************************************************************************

#ifndef _DIA_CHANNELS_H_D
   #define _DIA_CHANNELS_H_D

//*** include files ********************************************************************************
// List of include files needed in this module.
#include "std_type.h"     //standard type definitions

#ifdef _DIA_CHANNELS_D
   #define SCOPE_D
#else
   #define SCOPE_D extern
#endif   // _DIA_CHANNELS_D

//*** defines **************************************************************************************
// List of defines needed in this header file and defines to be made available to other modules.

//! reserved spare entry within channel index translation table
#define DIA_SPARE_DU32                  (uint32)0xFFFFFFFFu

//! channel index of the last analog input within the translation table
#define DIA_CHNLIDX_LAST_ANALOG_DU16    (uint16)100

//! channel index of the first digital input within the translation table
#define DIA_CHNLIDX_FIRST_DIGITAL_DU16  (uint16)101

//! channel index of the last digital input within the translation table
#define DIA_CHNLIDX_LAST_DIGITAL_DU16   (uint16)200

//! size of the channel index translation table
#define DIA_CHNLIDX_TABLE_SIZE_DU16     (uint16)286

// defines for channel index numbers
// ----- analog voltage input channels -----
#define CHNL_1                          (uint16)1
#define CHNL_2                          (uint16)2
#define CHNL_3                          (uint16)3
#define CHNL_4                          (uint16)4
#define CHNL_5                          (uint16)5
#define CHNL_6                          (uint16)6
#define CHNL_7                          (uint16)7
#define CHNL_8                          (uint16)8
#define CHNL_9                          (uint16)9
#define CHNL_10                         (uint16)10
#define CHNL_11                         (uint16)11
#define CHNL_12                         (uint16)12
#define CHNL_13                         (uint16)13
#define CHNL_14                         (uint16)14
#define CHNL_15                         (uint16)15
#define CHNL_16                         (uint16)16
#define CHNL_17                         (uint16)17
#define CHNL_18                         (uint16)18
#define CHNL_19                         (uint16)19
#define CHNL_20                         (uint16)20
#define CHNL_21                         (uint16)21
#define CHNL_22                         (uint16)22
#define CHNL_23                         (uint16)23
#define CHNL_24                         (uint16)24
#define CHNL_25                         (uint16)25
#define CHNL_26                         (uint16)26
#define CHNL_27                         (uint16)27
#define CHNL_28                         (uint16)28
#define CHNL_29                         (uint16)29
#define CHNL_30                         (uint16)30
#define CHNL_31                         (uint16)31
#define CHNL_32                         (uint16)32
#define CHNL_33                         (uint16)33
#define CHNL_34                         (uint16)34
#define CHNL_35                         (uint16)35
#define CHNL_36                         (uint16)36
#define CHNL_37                         (uint16)37
#define CHNL_38                         (uint16)38
#define CHNL_39                         (uint16)39
#define CHNL_40                         (uint16)40
#define CHNL_41                         (uint16)41
#define CHNL_42                         (uint16)42
#define CHNL_43                         (uint16)43
#define CHNL_44                         (uint16)44
#define CHNL_45                         (uint16)45
#define CHNL_46                         (uint16)46
#define CHNL_47                         (uint16)47
#define CHNL_48                         (uint16)48
#define CHNL_49                         (uint16)49
#define CHNL_50                         (uint16)50
#define CHNL_51                         (uint16)51
#define CHNL_52                         (uint16)52
#define CHNL_53                         (uint16)53
#define CHNL_54                         (uint16)54
#define CHNL_55                         (uint16)55
#define CHNL_56                         (uint16)56
#define CHNL_57                         (uint16)57
#define CHNL_58                         (uint16)58
#define CHNL_59                         (uint16)59
#define CHNL_60                         (uint16)60
#define CHNL_61                         (uint16)61
#define CHNL_62                         (uint16)62
#define CHNL_63                         (uint16)63
#define CHNL_64                         (uint16)64
#define CHNL_65                         (uint16)65
#define CHNL_66                         (uint16)66
#define CHNL_67                         (uint16)67
#define CHNL_68                         (uint16)68
#define CHNL_69                         (uint16)69
#define CHNL_70                         (uint16)70

// ----- digital input channels -----
#define CHNL_101                        (uint16)101
#define CHNL_102                        (uint16)102
#define CHNL_103                        (uint16)103
#define CHNL_104                        (uint16)104
#define CHNL_105                        (uint16)105
#define CHNL_106                        (uint16)106
#define CHNL_107                        (uint16)107
#define CHNL_108                        (uint16)108
#define CHNL_109                        (uint16)109
#define CHNL_110                        (uint16)110
#define CHNL_111                        (uint16)111
#define CHNL_112                        (uint16)112
#define CHNL_113                        (uint16)113
#define CHNL_114                        (uint16)114
#define CHNL_115                        (uint16)115
#define CHNL_116                        (uint16)116
#define CHNL_117                        (uint16)117
#define CHNL_118                        (uint16)118
#define CHNL_119                        (uint16)119
#define CHNL_120                        (uint16)120
#define CHNL_121                        (uint16)121
#define CHNL_122                        (uint16)122
#define CHNL_123                        (uint16)123
#define CHNL_124                        (uint16)124
#define CHNL_125                        (uint16)125
#define CHNL_126                        (uint16)126
#define CHNL_127                        (uint16)127
#define CHNL_128                        (uint16)128
#define CHNL_129                        (uint16)129
#define CHNL_130                        (uint16)130
#define CHNL_131                        (uint16)131
#define CHNL_132                        (uint16)132
#define CHNL_133                        (uint16)133
#define CHNL_134                        (uint16)134
#define CHNL_135                        (uint16)135
#define CHNL_136                        (uint16)136
#define CHNL_137                        (uint16)137
#define CHNL_138                        (uint16)138
#define CHNL_139                        (uint16)139
#define CHNL_140                        (uint16)140
#define CHNL_141                        (uint16)141
#define CHNL_142                        (uint16)142
#define CHNL_143                        (uint16)143
#define CHNL_144                        (uint16)144
#define CHNL_145                        (uint16)145
#define CHNL_146                        (uint16)146
#define CHNL_147                        (uint16)147
#define CHNL_148                        (uint16)148
#define CHNL_149                        (uint16)149
#define CHNL_150                        (uint16)150
#define CHNL_151                        (uint16)151
#define CHNL_152                        (uint16)152
#define CHNL_153                        (uint16)153
#define CHNL_154                        (uint16)154
#define CHNL_155                        (uint16)155
#define CHNL_156                        (uint16)156
#define CHNL_157                        (uint16)157
#define CHNL_158                        (uint16)158
#define CHNL_159                        (uint16)159
#define CHNL_160                        (uint16)160
#define CHNL_161                        (uint16)161
#define CHNL_162                        (uint16)162
#define CHNL_163                        (uint16)163
#define CHNL_164                        (uint16)164
#define CHNL_165                        (uint16)165
#define CHNL_166                        (uint16)166
#define CHNL_167                        (uint16)167
#define CHNL_168                        (uint16)168
#define CHNL_169                        (uint16)169
#define CHNL_170                        (uint16)170
#define CHNL_171                        (uint16)171
#define CHNL_172                        (uint16)172
#define CHNL_173                        (uint16)173
#define CHNL_174                        (uint16)174
#define CHNL_175                        (uint16)175

  // ----- frequency input channels must have an index >= 0x0100-----
#define CHNL_258                        (uint16)258
#define CHNL_259                        (uint16)259
#define CHNL_260                        (uint16)260
#define CHNL_261                        (uint16)261
#define CHNL_262                        (uint16)262
#define CHNL_263                        (uint16)263
#define CHNL_264                        (uint16)264
#define CHNL_265                        (uint16)265
#define CHNL_266                        (uint16)266
#define CHNL_267                        (uint16)267
#define CHNL_268                        (uint16)268
#define CHNL_269                        (uint16)269
#define CHNL_270                        (uint16)270
#define CHNL_271                        (uint16)271
#define CHNL_272                        (uint16)272
#define CHNL_273                        (uint16)273
#define CHNL_274                        (uint16)274
#define CHNL_275                        (uint16)275
#define CHNL_276                        (uint16)276
#define CHNL_277                        (uint16)277
#define CHNL_278                        (uint16)278
#define CHNL_279                        (uint16)279
#define CHNL_280                        (uint16)280
#define CHNL_281                        (uint16)281
#define CHNL_282                        (uint16)282
#define CHNL_283                        (uint16)283
#define CHNL_284                        (uint16)284
#define CHNL_285                        (uint16)285

// ----- channel index 'ALL' for special services -----
#define CHNL_ALL                        (uint16)0xFFFF


//*** typdefs/structures ***************************************************************************
// Typedefs/structures to be made available to other modules.


//*** public data **********************************************************************************
// Declarations of variables to be made available to other modules.

//! translation table for I/O channels usable by diagnosis into 16Bit index
#ifdef _DIA_CHANNELS_D
const uint32 diag_channel_cau32[DIA_CHNLIDX_TABLE_SIZE_DU16] =
{
//I/O-            Channel-
//channel         Index
//
  NULL  ,        //   0
  // ----- analog voltage input channels -----
  IN_1_AIV,      //   1
  IN_2_AIV,      //   2
  IN_3_AIV,      //   3
  IN_4_AIV,      //   4
  IN_5_AIV,      //   5
  IN_6_AIV,      //   6
  IN_7_AIV,      //   7
  IN_8_AIV,      //   8
  IN_9_AIV,      //   9
  IN_10_AIV,     //  10
  IN_11_AIV,     //  11
  IN_12_AIV,     //  12
  IN_13_AIV,     //  13
  IN_14_AIV,     //  14
  IN_15_AIV,     //  15
  IN_16_AIV,     //  16
  IN_17_AIV,     //  17
  IN_18_AIV,     //  18
  IN_19_AIV,     //  19
  IN_20_AIV,     //  20
  IN_21_AIV,     //  21
  IN_22_AIV,     //  22
  IN_23_AIV,     //  23
  IN_24_AIV,     //  24
  IN_25_AIV,     //  25
  IN_26_AIV,     //  26
  IN_27_AIV,     //  27
  IN_28_AIV,     //  28
  IN_29_AIV,     //  29
  IN_30_AIV,     //  30
  IN_31_AIV,     //  31
  IN_32_AIV,     //  32
  IN_33_AIV,     //  33
  IN_34_AIV,     //  34
  IN_35_AIV,     //  35
  IN_36_AIV,     //  36
  IN_37_AIV,     //  37
  IN_38_AIV,     //  38
  IN_39_AIV,     //  39
  IN_40_AIV,     //  40
  IN_41_AIV,     //  41
  DIA_SPARE_DU32,//  42
  DIA_SPARE_DU32,//  43
  DIA_SPARE_DU32,//  44
  DIA_SPARE_DU32,//  45
  DIA_SPARE_DU32,//  46
  DIA_SPARE_DU32,//  47
  DIA_SPARE_DU32,//  48
  DIA_SPARE_DU32,//  49
  DIA_SPARE_DU32,//  50
  DIA_SPARE_DU32,//  51
  IN_52_AIV,     //  52
  IN_53_AIV,     //  53
  IN_54_AIV,     //  54
  IN_55_AIV,     //  55
  IN_56_AIV,     //  56
  IN_57_AIV,     //  57
  IN_58_AIV,     //  58
  IN_59_AIV,     //  59
  IN_60_AIV,     //  60
  IN_61_AIV,     //  61
  DIA_SPARE_DU32,//  62
  DIA_SPARE_DU32,//  63
  DIA_SPARE_DU32,//  64
  DIA_SPARE_DU32,//  65
  DIA_SPARE_DU32,//  66
  DIA_SPARE_DU32,//  67
  DIA_SPARE_DU32,//  68
  DIA_SPARE_DU32,//  69
  DIA_SPARE_DU32,//  70
  DIA_SPARE_DU32,//  71
  DIA_SPARE_DU32,//  72
  DIA_SPARE_DU32,//  73
  DIA_SPARE_DU32,//  74
  DIA_SPARE_DU32,//  75
  DIA_SPARE_DU32,//  76
  DIA_SPARE_DU32,//  77
  DIA_SPARE_DU32,//  78
  DIA_SPARE_DU32,//  79
  DIA_SPARE_DU32,//  80
  DIA_SPARE_DU32,//  81
  DIA_SPARE_DU32,//  82
  DIA_SPARE_DU32,//  83
  DIA_SPARE_DU32,//  84
  DIA_SPARE_DU32,//  85
  DIA_SPARE_DU32,//  86
  DIA_SPARE_DU32,//  87
  DIA_SPARE_DU32,//  88
  DIA_SPARE_DU32,//  89
  DIA_SPARE_DU32,//  90
  DIA_SPARE_DU32,//  91
  DIA_SPARE_DU32,//  92
  DIA_SPARE_DU32,//  93
  DIA_SPARE_DU32,//  94
  DIA_SPARE_DU32,//  95
  DIA_SPARE_DU32,//  96
  DIA_SPARE_DU32,//  97
  DIA_SPARE_DU32,//  98
  DIA_SPARE_DU32,//  99
  DIA_SPARE_DU32,// 100
  // ----- digital input channels -----
  IN_1_AID ,     // 101
  IN_2_AID ,     // 102
  IN_3_AID ,     // 103
  IN_4_AID ,     // 104
  IN_5_AID ,     // 105
  IN_6_AID ,     // 106
  IN_7_AID ,     // 107
  IN_8_AID ,     // 108
  IN_9_AID ,     // 109
  IN_10_AID,     // 110
  IN_11_AID,     // 111
  IN_12_AID,     // 112
  IN_13_AID,     // 113
  IN_14_AID,     // 114
  IN_15_AID,     // 115
  IN_16_AID,     // 116
  IN_17_AID,     // 117
  IN_18_AID,     // 118
  IN_19_AID,     // 119
  IN_20_AID,     // 120
  IN_21_AID,     // 121
  IN_22_AID,     // 122
  IN_23_AID,     // 123
  IN_24_AID,     // 124
  IN_25_AID,     // 125
  IN_26_AID,     // 126
  IN_27_AID,     // 127
  IN_28_AID,     // 128
  IN_29_AID,     // 129
  IN_30_AID,     // 130
  IN_31_AID,     // 131
  IN_32_AID,     // 132
  IN_33_AID,     // 133
  IN_34_AID,     // 134
  IN_35_AID,     // 135
  IN_36_AID,     // 136
  IN_37_AID,     // 137
  IN_38_AID,     // 138
  IN_39_AID,     // 139
  IN_40_AID,     // 140
  IN_41_AID,     // 141
  IN_42_DI,      // 142
  IN_43_DI,      // 143
  IN_44_DI,      // 144
  IN_45_DI,      // 145
  IN_46_DI,      // 146
  IN_47_DI,      // 147
  IN_48_DI,      // 148
  IN_49_DI,      // 149
  IN_50_DI,      // 150
  IN_51_DI,      // 151
  IN_52_AID,     // 152
  IN_53_AID,     // 153
  IN_54_AID,     // 154
  IN_55_AID,     // 155
  IN_56_AID,     // 156
  IN_57_AID,     // 157
  IN_58_AID,     // 158
  IN_59_AID,     // 159
  IN_60_AID,     // 160
  IN_61_AID,     // 161
  IN_62_AID,     // 162
  IN_63_AID,     // 163
  IN_64_AID,     // 164
  IN_65_AID,     // 165
  IN_66_AID,     // 166
  IN_67_AID,     // 167
  DIA_SPARE_DU32,// 168
  IN_69_AID,     // 169
  IN_70_AID,     // 170
  IN_71_DI,      // 171
  IN_72_DI,      // 172
  IN_73_DI,      // 173
  IN_74_DI,      // 174
  IN_75_DI,      // 175
  DIA_SPARE_DU32,// 176
  DIA_SPARE_DU32,// 177
  DIA_SPARE_DU32,// 178
  DIA_SPARE_DU32,// 179
  DIA_SPARE_DU32,// 180
  DIA_SPARE_DU32,// 181
  DIA_SPARE_DU32,// 182
  DIA_SPARE_DU32,// 183
  DIA_SPARE_DU32,// 184
  DIA_SPARE_DU32,// 185
  DIA_SPARE_DU32,// 186
  DIA_SPARE_DU32,// 187
  DIA_SPARE_DU32,// 188
  DIA_SPARE_DU32,// 189
  DIA_SPARE_DU32,// 190
  DIA_SPARE_DU32,// 191
  DIA_SPARE_DU32,// 192
  DIA_SPARE_DU32,// 193
  DIA_SPARE_DU32,// 194
  DIA_SPARE_DU32,// 195
  DIA_SPARE_DU32,// 196
  DIA_SPARE_DU32,// 197
  DIA_SPARE_DU32,// 198
  DIA_SPARE_DU32,// 199
  DIA_SPARE_DU32,// 200
  DIA_SPARE_DU32,// 201
  DIA_SPARE_DU32,// 202
  DIA_SPARE_DU32,// 203
  DIA_SPARE_DU32,// 204
  DIA_SPARE_DU32,// 205
  DIA_SPARE_DU32,// 206
  DIA_SPARE_DU32,// 207
  DIA_SPARE_DU32,// 208
  DIA_SPARE_DU32,// 209
  DIA_SPARE_DU32,// 210
  DIA_SPARE_DU32,// 211
  DIA_SPARE_DU32,// 212
  DIA_SPARE_DU32,// 213
  DIA_SPARE_DU32,// 214
  DIA_SPARE_DU32,// 215
  DIA_SPARE_DU32,// 216
  DIA_SPARE_DU32,// 217
  DIA_SPARE_DU32,// 218
  DIA_SPARE_DU32,// 219
  DIA_SPARE_DU32,// 220
  DIA_SPARE_DU32,// 221
  DIA_SPARE_DU32,// 222
  DIA_SPARE_DU32,// 223
  DIA_SPARE_DU32,// 224
  DIA_SPARE_DU32,// 225
  DIA_SPARE_DU32,// 226
  DIA_SPARE_DU32,// 227
  DIA_SPARE_DU32,// 228
  DIA_SPARE_DU32,// 229
  DIA_SPARE_DU32,// 230
  DIA_SPARE_DU32,// 231
  DIA_SPARE_DU32,// 232
  DIA_SPARE_DU32,// 233
  DIA_SPARE_DU32,// 234
  DIA_SPARE_DU32,// 235
  DIA_SPARE_DU32,// 236
  DIA_SPARE_DU32,// 237
  DIA_SPARE_DU32,// 238
  DIA_SPARE_DU32,// 239
  DIA_SPARE_DU32,// 240
  DIA_SPARE_DU32,// 241
  DIA_SPARE_DU32,// 242
  DIA_SPARE_DU32,// 243
  DIA_SPARE_DU32,// 244
  DIA_SPARE_DU32,// 245
  DIA_SPARE_DU32,// 246
  DIA_SPARE_DU32,// 247
  DIA_SPARE_DU32,// 248
  DIA_SPARE_DU32,// 249
  DIA_SPARE_DU32,// 250
  DIA_SPARE_DU32,// 251
  DIA_SPARE_DU32,// 252
  DIA_SPARE_DU32,// 253
  DIA_SPARE_DU32,// 254
  DIA_SPARE_DU32,// 255

  // ----- frequency input channels must have an index >= 0x0100-----
  DIA_SPARE_DU32,// 256
  DIA_SPARE_DU32,// 257
  DIA_SPARE_DU32,// 258
  DIA_SPARE_DU32,// 259
  DIA_SPARE_DU32,// 260
  DIA_SPARE_DU32,// 261
  DIA_SPARE_DU32,// 262
  DIA_SPARE_DU32,// 263
  DIA_SPARE_DU32,// 264
  DIA_SPARE_DU32,// 265
  IN_66_FI,      // 266
  IN_67_FI,      // 267
  IN_68_FI,      // 268
  IN_69_FI,      // 269
  IN_70_FI,      // 270
  IN_71_FI,      // 271
  IN_72_FI,      // 272
  IN_73_FI,      // 273
  IN_74_FI,      // 274
  IN_75_FI,      // 275
  DIA_SPARE_DU32,// 276
  DIA_SPARE_DU32,// 277
  DIA_SPARE_DU32,// 278
  DIA_SPARE_DU32,// 279
  DIA_SPARE_DU32,// 280
  IN_71_DSM,     // 281
  IN_72_DSM,     // 282
  IN_73_DSM,     // 283
  IN_74_DSM,     // 284
  IN_75_DSM      // 285
};

#else
extern const uint32 diag_channel_cau32[DIA_CHNLIDX_TABLE_SIZE_DU16];
#endif // _DIA_CHANNELS_


//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.


//**************************************************************************************************

#undef SCOPE_D

#undef _DIA_CHANNELS_D         // reseting definition, prevents double definition of a variable if
                               // includes are nested
#endif  // _DIA_CHANNELS_H_D

// EOF #############################################################################################
