#ifndef __VPU_HW_INTERFACE_H__
#define	__VPU_HW_INTERFACE_H__

#include "../include/nx_vpu_config.h"
#include "regdefine.h"
#include "../include/nx_vpu_api.h"

#ifdef __cplusplus
extern "C"{
#endif

//----------------------------------------------------------------------------
//						Register Interface


//	Offset Based Register Access for VPU
void VpuWriteReg( uint32_t offset, uint32_t value );
uint32_t VpuReadReg( uint32_t offset );
void WriteRegNoMsg( uint32_t offset, uint32_t value );
uint32_t ReadRegNoMsg( uint32_t offset );


//	Direct Register Access API
void WriteReg32( uint32_t *address, uint32_t value );
uint32_t ReadReg32( uint32_t *address );

void InitVpuRegister( void *virAddr );
uint32_t *GetVpuRegBase( void );

//----------------------------------------------------------------------------
//					Host Command Interface
void VpuBitIssueCommand(NX_VpuCodecInst *inst, NX_VPU_CMD cmd);

#ifdef __cplusplus
};
#endif

#endif	//	__VPU_HW_INTERFACE_H__
