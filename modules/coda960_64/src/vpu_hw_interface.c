#include "vpu_hw_interface.h"

#define	NX_DTAG		"[DRV|REG_ACC]"
#include "../include/drv_osapi.h"

#define DBG_VBS 0

#define	VIR_ADDR_BASE			0xF0000000
#define	NX_VPU_PHY_BASE			0xC0080000
#define	NX_VPU_VIR_BASE			(VIR_ADDR_BASE + 0x00080000)


static void *gstBaseAddr = NULL;

//----------------------------------------------------------------------------
//						Register Interface

void VpuWriteReg( uint32_t offset, uint32_t value )
{
	uint32_t *addr = (uint32_t *)((void*)(gstBaseAddr + offset));
#if NX_REG_EN_MSG
	NX_DbgMsg(NX_REG_EN_MSG, ("write( 0x%08x, 0x%08x )addr(%p)\n", offset, value, addr));
#endif
	*addr = value;
}

uint32_t VpuReadReg( uint32_t offset )
{
#if NX_REG_EN_MSG
	NX_DbgMsg(NX_REG_EN_MSG, ("read( 0x%08x, 0x%08x )\n", offset, *(gstBaseAddr + offset)));
#endif
	return *((uint32_t*)(gstBaseAddr+offset));
}

void WriteRegNoMsg( uint32_t offset, uint32_t value )
{
	uint32_t *addr = gstBaseAddr + offset;
	*addr = value;
}

uint32_t ReadRegNoMsg( uint32_t offset )
{
	return *((uint32_t*)(gstBaseAddr+offset));
}

void WriteReg32( uint32_t *address, uint32_t value )
{
	*address = value;
}

uint32_t ReadReg32( uint32_t *address )
{
	return *address;
}


void InitVpuRegister( void *virAddr )
{
	gstBaseAddr = virAddr;
}

uint32_t *GetVpuRegBase( void )
{
	return gstBaseAddr;
}

//----------------------------------------------------------------------------
//						Host Command
void VpuBitIssueCommand(NX_VpuCodecInst *inst, NX_VPU_CMD cmd)
{
	NX_DbgMsg( DBG_VBS, ("VpuBitIssueCommand : cmd = %d, address=0x%llx, instIndex=%d, codecMode=%d, auxMode=%d\n", 
		cmd, inst->instBufPhyAddr, inst->instIndex, inst->codecMode, inst->auxMode) );

	VpuWriteReg(BIT_WORK_BUF_ADDR, (uint32_t)inst->instBufPhyAddr);
	VpuWriteReg(BIT_BUSY_FLAG, 1);
	VpuWriteReg(BIT_RUN_INDEX, inst->instIndex);
	VpuWriteReg(BIT_RUN_COD_STD, inst->codecMode);
	VpuWriteReg(BIT_RUN_AUX_STD, inst->auxMode);
	VpuWriteReg(BIT_RUN_COMMAND, cmd);
}
