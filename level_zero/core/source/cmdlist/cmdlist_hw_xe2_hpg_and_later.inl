/*
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once
#include "level_zero/core/source/cmdlist/cmdlist_hw.h"
#include "level_zero/core/source/kernel/kernel.h"

namespace L0 {

template <GFXCORE_FAMILY gfxCoreFamily>
inline NEO::PreemptionMode CommandListCoreFamily<gfxCoreFamily>::obtainKernelPreemptionMode(Kernel *kernel) {
    auto kernelDescriptor = &kernel->getImmutableData()->getDescriptor();
    bool disabledMidThreadPreemptionKernel = kernelDescriptor->kernelAttributes.flags.requiresDisabledMidThreadPreemption ||
                                             (kernelDescriptor->kernelAttributes.flags.hasRTCalls && kernel->isMidThreadPreemptionDisallowedForRayTracingKernels());
    bool debuggingEnabled = device->getNEODevice()->getDebugger();
    disabledMidThreadPreemptionKernel |= debuggingEnabled;
    disabledMidThreadPreemptionKernel |= device->getNEODevice()->getPreemptionMode() != NEO::PreemptionMode::MidThread;
    return disabledMidThreadPreemptionKernel ? NEO::PreemptionMode::ThreadGroup : NEO::PreemptionMode::MidThread;
}

template <GFXCORE_FAMILY gfxCoreFamily>
void CommandListCoreFamily<gfxCoreFamily>::adjustWriteKernelTimestamp(uint64_t globalAddress, uint64_t contextAddress, uint64_t baseAddress, CommandToPatchContainer *outTimeStampSyncCmds, bool maskLsb, uint32_t mask,
                                                                      bool workloadPartition, bool copyOperation) {
    uint64_t globalHighAddress = globalAddress + sizeof(uint32_t);
    uint64_t contextHighAddress = contextAddress + sizeof(uint32_t);

    void **globalPostSyncCmdBuffer = nullptr;
    void **contextPostSyncCmdBuffer = nullptr;

    void *globalPostSyncCmd = nullptr;
    void *contextPostSyncCmd = nullptr;

    if (outTimeStampSyncCmds != nullptr) {
        globalPostSyncCmdBuffer = &globalPostSyncCmd;
        contextPostSyncCmdBuffer = &contextPostSyncCmd;
    }

    if (maskLsb) {
        NEO::EncodeMathMMIO<GfxFamily>::encodeBitwiseAndVal(commandContainer, RegisterOffsets::globalTimestampUn, mask, globalHighAddress, workloadPartition, globalPostSyncCmdBuffer, copyOperation);
        NEO::EncodeMathMMIO<GfxFamily>::encodeBitwiseAndVal(commandContainer, RegisterOffsets::gpThreadTimeRegAddressOffsetHigh, mask, contextHighAddress, workloadPartition, contextPostSyncCmdBuffer, copyOperation);
    } else {
        NEO::EncodeStoreMMIO<GfxFamily>::encode(*commandContainer.getCommandStream(), RegisterOffsets::globalTimestampUn, globalHighAddress, workloadPartition, globalPostSyncCmdBuffer);
        NEO::EncodeStoreMMIO<GfxFamily>::encode(*commandContainer.getCommandStream(), RegisterOffsets::gpThreadTimeRegAddressOffsetHigh, contextHighAddress, workloadPartition, contextPostSyncCmdBuffer);
    }

    if (outTimeStampSyncCmds != nullptr) {
        CommandToPatch ctxCmd;
        ctxCmd.type = CommandToPatch::TimestampEventPostSyncStoreRegMem;

        ctxCmd.offset = globalHighAddress - baseAddress;
        ctxCmd.pDestination = globalPostSyncCmd;
        outTimeStampSyncCmds->push_back(ctxCmd);

        ctxCmd.offset = contextHighAddress - baseAddress;
        ctxCmd.pDestination = contextPostSyncCmd;
        outTimeStampSyncCmds->push_back(ctxCmd);
    }
}

} // namespace L0
