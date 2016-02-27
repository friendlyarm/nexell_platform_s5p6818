#ifndef __VPU_TYPES_H__
#define __VPU_TYPES_H__

#include <linux/types.h>

#include "nx_alloc_mem.h"

typedef struct
{
	int32_t left;
	int32_t top;
	int32_t right;
	int32_t bottom;
} VPU_RECT;

typedef struct
{
	//	Input Arguments
	int32_t codecStd;
	int32_t isEncoder;			// Encoder
	int32_t mp4Class;			// Mpeg4 Class
	int32_t chromaInterleave;	// CbCr Interleaved

	NX_MEMORY_INFO	instanceBuf;
	NX_MEMORY_INFO	streamBuf;

	//	Output Arguments
	int32_t instIndex;			// Instance Index
} VPU_OPEN_ARG;

typedef struct
{
	// input image size
	int32_t srcWidth;			// source image's width
	int32_t srcHeight;			// source image's height

	//	Set Stream Buffer Handle
	uint64_t strmBufVirAddr;
	uint64_t strmBufPhyAddr;
	int32_t strmBufSize;

	int32_t frameRateNum;		// frame rate
	int32_t frameRateDen;
	int32_t gopSize;			// group of picture size

	//	Rate Control
	int32_t	RCModule;			// 0 : VBR, 1 : CnM RC, 2 : NX RC
	int32_t bitrate;			// Target Bitrate
	int32_t disableSkip;		// Flag of Skip frame disable
	int32_t initialDelay;		// This value is valid if RCModule is 1.(MAX 0x7FFF)
								// 0 does not check Reference decoder buffer delay constraint.
	int32_t vbvBufferSize;		// Reference Decoder buffer size in bytes
								// This valid is ignored if RCModule is 1 and initialDelay is is 0.(MAX 0x7FFFFFFF)
	int32_t gammaFactor;		// It is valid when RCModule is 1.

	//	Quantization Scale [ H.264/AVC(0~51), MPEG4(1~31) ]
	int32_t maxQP;				// Max Quantization Scale
	int32_t initQP;				// This value is Initial QP whne CBR. (Initial QP is computed if initQP is 0.)
								// This value is user QP when VBR.

	//	Input Buffer Chroma Interleaved
	int32_t chromaInterleave;	//	Input Buffer Chroma Interleaved Format
	int32_t refChromaInterleave;//	Reference Buffer's Chorma Interleaved Format

	//	ME Search Range
	int32_t searchRange;		//	ME_SEARCH_RAGME_[0~3] ( recomand ME_SEARCH_RAGME_2 )
								//	0 : H(-128~127), V(-64~63)
								//	1 : H( -64~ 63), V(-32~31)
								//	2 : H( -32~ 31), V(-16~15)
								//	3 : H( -16~ 15), V(-16~15)

	//	Other Options
	int32_t intraRefreshMbs;	//	an Intra MB refresh number.
								//	It must be less than total MacroBlocks.

	int32_t rotAngle;
	int32_t mirDirection;

	//	AVC Only
	int32_t	enableAUDelimiter;	//	enable/disable Access Unit Delimiter

	//	JPEG Specific
	int32_t quality;
}VPU_ENC_SEQ_ARG;


typedef struct
{
	//	Reconstruct Buffer
	int32_t	numFrameBuffer;					//	Number Of Frame Buffers
	NX_VID_MEMORY_INFO frameBuffer[2];	//	Frame Buffer Informations

	//	Sub Sample A/B Buffer ( 1 sub sample buffer size = Framebuffer size/4 )
	NX_MEMORY_INFO subSampleBuffer[2];	//

	//	Data partition Buffer size ( MAX WIDTH * MAX HEIGHT * 3 / 4 )
	NX_MEMORY_INFO dataPartitionBuffer;	//	Mpeg4 Only
}VPU_ENC_SET_FRAME_ARG;


typedef union
{
	struct {
		uint8_t vosData[512];
		int32_t vosSize;
		uint8_t volData[512];
		int32_t volSize;
		uint8_t voData[512];
		int32_t voSize;
	} mp4Header;
	struct {
		uint8_t spsData[512];
		int32_t spsSize;
		uint8_t ppsData[512];
		int32_t ppsSize;
	} avcHeader;
	struct {
		uint8_t jpegHeader[1024];
		int32_t headerSize;
	} jpgHeader;
}VPU_ENC_GET_HEADER_ARG;


typedef struct
{
	//------------------------------------------------------------------------
	//	Input Prameter
	NX_VID_MEMORY_INFO	inImgBuffer;
	//	Rate Control Parameters
	int32_t changeFlag;
	int32_t enableRc;
	int32_t forceIPicture;
	int32_t quantParam;			//	User quantization Parameter
	int32_t skipPicture;

	//	Dynamic Configurable Parameters


	//------------------------------------------------------------------------
	//	Output Parameter
	int32_t frameType;					//	I, P, B, SKIP,.. etc
	uint64_t outStreamAddr;	//	mmapped virtual address
	int32_t outStreamSize;				//	Stream buffer size
	int32_t reconImgIdx;				// 	reconstructed image buffer index
}VPU_ENC_RUN_FRAME_ARG;

typedef struct
{
	int32_t chgFlg;
	int32_t gopSize;
	int32_t intraQp;
	int32_t bitrate;
	int32_t frameRateNum;
	int32_t frameRateDen;
	int32_t intraRefreshMbs;
	int32_t sliceMode;
	int32_t sliceSizeMode;
	int32_t sliceSizeNum;
	int32_t hecMode;
} VPU_ENC_CHG_PARA_ARG;

typedef struct {
	int32_t fixedFrameRateFlag;
	int32_t timingInfoPresent;
	int32_t chromaLocBotField;
	int32_t chromaLocTopField;
	int32_t chromaLocInfoPresent;
	int32_t colorPrimaries;
	int32_t colorDescPresent;
	int32_t isExtSAR;
	int32_t vidFullRange;
	int32_t vidFormat;
	int32_t vidSigTypePresent;
	int32_t vuiParamPresent;
	int32_t vuiPicStructPresent;
	int32_t vuiPicStruct;
} AvcVuiInfo;


//
//	Decoder Structures
//

typedef struct
{
	//	Input Information
	uint64_t seqData;
	int32_t seqDataSize;
	int32_t disableOutReorder;

	//	General Output Information
	int32_t outWidth;
	int32_t outHeight;
	int32_t frameRateNum;	//	Frame Rate Numerator
	int32_t frameRateDen;	//	Frame Rate Denominator
	uint32_t bitrate;

	int32_t profile;
	int32_t level;
	int32_t interlace;
	int32_t direct8x8Flag;
	int32_t constraint_set_flag[4];
	int32_t aspectRateInfo;

	//	Frame Buffer Information
	int32_t minFrameBufCnt;
	int32_t frameBufDelay;

	int32_t enablePostFilter;	// 1 : Deblock filter, 0 : Disable post filter

	//	Mpeg4 Specific Info
	int32_t mp4ShortHeader;
	int32_t mp4PartitionEnable;
	int32_t mp4ReversibleVlcEnable;
	int32_t h263AnnexJEnable;
	uint32_t mp4Class;

	//	VP8 Specific Info
	int32_t vp8HScaleFactor;
	int32_t vp8VScaleFactor;
	int32_t vp8ScaleWidth;
	int32_t vp8ScaleHeight;


	//	H.264(AVC) Specific Info
	AvcVuiInfo avcVuiInfo;
	int32_t avcIsExtSAR;
	int32_t cropLeft;
	int32_t cropTop;
	int32_t cropRight;
	int32_t cropBottom;
	int32_t numSliceSize;
	int32_t worstSliceSize;
	int32_t maxNumRefFrmFlag;

	//	VC-1
	int32_t	vc1Psf;

	//	Mpeg2
    int32_t mp2LowDelay;
    int32_t mp2DispVerSize;
    int32_t mp2DispHorSize;
	int32_t userDataNum;
	int32_t userDataSize;
	int32_t userDataBufFull;
	int32_t enableUserData;
	NX_MEMORY_INFO userDataBuffer;

}VPU_DEC_SEQ_INIT_ARG;


typedef struct
{
	//	Frame Buffers
	int32_t	numFrameBuffer;					//	Number Of Frame Buffers
	NX_VID_MEMORY_INFO frameBuffer[30];	//	Frame Buffer Informations

	//	MV Buffer Address
	NX_MEMORY_INFO colMvBuffer;

	//	AVC Slice Buffer
	NX_MEMORY_INFO sliceBuffer;

	//	VPX Codec Specific
	NX_MEMORY_INFO pvbSliceBuffer;

}VPU_DEC_REG_FRAME_ARG;

// VP8 specific display information
typedef struct {
	uint32_t hScaleFactor   : 2;
	uint32_t vScaleFactor   : 2;
	uint32_t picWidth       : 14;
	uint32_t picHeight      : 14;
} Vp8ScaleInfo;

// VP8 specific header information
typedef struct {
	uint32_t showFrame      : 1;
	uint32_t versionNumber  : 3;
	uint32_t refIdxLast     : 8;
	uint32_t refIdxAltr     : 8;
	uint32_t refIdxGold     : 8;
} Vp8PicInfo;

typedef struct
{
	//	Input Arguments
	uint64_t strmData;
	int32_t strmDataSize;
	int32_t iFrameSearchEnable;
	int32_t skipFrameMode;
	int32_t decSkipFrameNum;
	int32_t eos;

	//	Output Arguments
	int32_t outWidth;
	int32_t outHeight;

	VPU_RECT outRect;

	int32_t indexFrameDecoded;
	int32_t indexFrameDisplay;

	int32_t picType;
	int32_t picTypeFirst;
	int32_t isInterace;
	int32_t picStructure;
	int32_t topFieldFirst;
	int32_t repeatFirstField;
	int32_t progressiveFrame;
	int32_t fieldSequence;

	int32_t isSuccess;

	int32_t errReason;
	int32_t errAddress;
	int32_t numOfErrMBs;
	int32_t sequenceChanged;

	uint32_t strmReadPos;
	uint32_t strmWritePos;

	//	AVC Specific Informations
	int32_t avcFpaSeiExist;
	int32_t avcFpaSeiValue1;
	int32_t avcFpaSeiValue2;

	//	Output Bitstream Information
	uint32_t frameStartPos;
	uint32_t frameEndPos;

	//
	uint32_t notSufficientPsBuffer;
	uint32_t notSufficientSliceBuffer;

	//
	uint32_t fRateNumerator;
	uint32_t fRateDenominator;
	uint32_t aspectRateInfo;	//	Use vp8ScaleInfo & vp8PicInfo in VP8

	//
	uint32_t mp4ModuloTimeBase;
	uint32_t mp4TimeIncrement;

	//	VP8 Scale Info
	Vp8ScaleInfo vp8ScaleInfo;
	Vp8PicInfo vp8PicInfo;

	//  VC1 Info
	int32_t multiRes;

	NX_VID_MEMORY_INFO outFrameBuffer;

	//	MPEG2 User Data
	int32_t userDataNum;        // User Data
	int32_t userDataSize;
	int32_t userDataBufFull;
    int32_t activeFormat;

	int32_t iRet;
} VPU_DEC_DEC_FRAME_ARG;


typedef struct
{
	int32_t indexFrameDisplay;
	NX_VID_MEMORY_INFO frameBuffer;
} VPU_DEC_CLR_DSP_FLAG_ARG;


//////////////////////////////////////////////////////////////////////////////
//
//		Command Arguments
//


//	Define Codec Standard
enum {
	CODEC_STD_AVC	= 0,
	CODEC_STD_VC1	= 1,
	CODEC_STD_MPEG2	= 2,
	CODEC_STD_MPEG4	= 3,
	CODEC_STD_H263	= 4,
	CODEC_STD_DIV3	= 5,
	CODEC_STD_RV	= 6,
	CODEC_STD_AVS	= 7,
	CODEC_STD_MJPG	= 8,

	CODEC_STD_THO	= 9,
	CODEC_STD_VP3	= 10,
	CODEC_STD_VP8	= 11
};

//	Search Range
enum {
	ME_SEARCH_RAGME_0,		//	Horizontal( -128 ~ 127 ), Vertical( -64 ~ 64 )
	ME_SEARCH_RAGME_1,		//	Horizontal(  -64 ~  63 ), Vertical( -32 ~ 32 )
	ME_SEARCH_RAGME_2,		//	Horizontal(  -32 ~  31 ), Vertical( -16 ~ 15 )	//	default
	ME_SEARCH_RAGME_3,		//	Horizontal(  -16 ~  15 ), Vertical( -16 ~ 15 )
};

//	Frame Buffer Format for JPEG
enum {
    IMG_FORMAT_420 = 0,
    IMG_FORMAT_422 = 1,
    IMG_FORMAT_224 = 2,
    IMG_FORMAT_444 = 3,
    IMG_FORMAT_400 = 4
};

//	JPEG Mirror Direction
enum {
	MIRDIR_NONE,
	MIRDIR_VER,
	MIRDIR_HOR,
	MIRDIR_HOR_VER,
};

//
//
//////////////////////////////////////////////////////////////////////////////

#endif	//	__VPU_TYPES_H__
