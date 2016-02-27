#ifndef __NX_ALLOC_MEM_H__
#define __NX_ALLOC_MEM_H__

#include <inttypes.h>

#ifdef	__cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
//			Enum & Define
enum {
	NX_MEM_MAP_LINEAR = 0,		//	Linear Memory Type
	NX_MEM_MAP_TILED  = 1,		//	Tiled Memory Type
};


//
//	Nexell Private Memory Type
//
typedef struct
{
	uint64_t		privateDesc;		//	Private Descriptor's Address
	int32_t			align;
	int32_t			size;
	uint64_t		virAddr;
	uint64_t		phyAddr;
} NX_MEMORY_INFO, *NX_MEMORY_HANDLE;



//
//	Nexell Private Video Memory Type
//
typedef struct
{
	uint64_t		privateDesc[3];	//	Private Descriptor( for allocator's handle or descriptor )
	int32_t			align;			//	Start Address Align( L/Cb/Cr )
	int32_t			memoryMap;		//	Memory Map Type( Linear or Tiled,. etc, N/A )
	uint32_t		fourCC;			//	Four Charect Code
	int32_t			imgWidth;		//	Video Image's Width
	int32_t			imgHeight;		//	Video Image's Height

	uint64_t		luPhyAddr;
	uint64_t		luVirAddr;
	uint32_t		luStride;

	uint64_t		cbPhyAddr;
	uint64_t		cbVirAddr;
	uint32_t		cbStride;

	uint64_t		crPhyAddr;
	uint64_t		crVirAddr;
	uint32_t		crStride;
} NX_VID_MEMORY_INFO, *NX_VID_MEMORY_HANDLE;



//	Nexell Private Memory Allocator
NX_MEMORY_HANDLE NX_AllocateMemory( int32_t size, int32_t align );
void NX_FreeMemory( NX_MEMORY_HANDLE handle );


//	Video Specific Allocator Wrapper
NX_VID_MEMORY_HANDLE NX_VideoAllocateMemory( int32_t align, int32_t width, int32_t height, int32_t memMap, int32_t fourCC );
void NX_FreeVideoMemory( NX_VID_MEMORY_HANDLE handle );

//	For Interlace Camera 3 plane only
NX_VID_MEMORY_HANDLE NX_VideoAllocateMemory2( int32_t align, int32_t width, int32_t height, int32_t memMap, int32_t fourCC );


#ifdef	__cplusplus
};
#endif

#endif	//	__NX_ALLOC_MEM_H__
