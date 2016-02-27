//--=========================================================================--
//  This file is a part of BlackBird Video Codec Modeling project
//-----------------------------------------------------------------------------
//
//       This confidential and proprietary software may be used only
//     as authorized by a licensing agreement from Chips&Media Inc.
//     In the event of publication, the following notice is applicable:
//
//            (C) COPYRIGHT 2010   CHIPS&MEDIA INC.
//                      ALL RIGHTS RESERVED
//
//       The entire notice above must be reproduced on all authorized
//       copies.
//
//-----------------------------------------------------------------------------
//--=========================================================================--

#ifndef _THO_PARSER_H_
#define _THO_PARSER_H_

#ifdef __cplusplus
extern "C" {
#endif


typedef struct tho_parser_t  tho_parser_t;
struct tho_parser_t {
	char *type;
    int  (*open)(void *handle, unsigned char *buf, int size, int *scaleInfo);
    int  (*read_frame)(void *codec_handle, unsigned char * chunkData, int chunkSize);
    int  (*close)(void *handle);
   
    void * handle; 
};


/**
 * THEORA DECODER Parser
 * Parsing the syntax and semantics of theora stream.
 * This process include below process items
 * 
 * 1. buffering quantization matrices
 * 2. process of parsing bitstream
 * 3. packing data on an MB basis
 * 
 */

int   theora_parser_init(void **parser);
int   theora_parser_end(void *parser);
/*       refer to 6.2.3.2 Macroblock order Matching,
         6.2.3.3  Macroblock Packing in Program User Guide */
int   theora_make_stream(void *handle, unsigned char *stream, int run_cmd);
/*       refer to 6.2.2 Quantization Matrices Buffering in Program User Guide */
//THEORA_PARSER_API int   theora_get_pic_info(void *handle, void *info, uint8_t *qmat);
void* theora_get_codec_info();

#ifdef __cplusplus
}
#endif

#endif //_THO_PARSER_H_
