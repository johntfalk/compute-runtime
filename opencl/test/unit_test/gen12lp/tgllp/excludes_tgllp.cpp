/*
 * Copyright (C) 2020-2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "test.h"

HWTEST_EXCLUDE_PRODUCT(BufferSetSurfaceTests, givenBufferSetSurfaceThatMemoryIsUnalignedToCachelineButReadOnlyThenL3CacheShouldBeStillOn, IGFX_TIGERLAKE_LP)
HWTEST_EXCLUDE_PRODUCT(BufferSetSurfaceTests, givenAlignedCacheableReadOnlyBufferThenChoseOclBufferPolicy, IGFX_TIGERLAKE_LP);
HWTEST_EXCLUDE_PRODUCT(HwInfoConfigTest, givenHwInfoConfigWhenAskedIfPipeControlWAIsRequiredThenFalseIsReturned, IGFX_TIGERLAKE_LP);
HWTEST_EXCLUDE_PRODUCT(HwInfoConfigTest, givenHwInfoConfigWhenAskedIfImagePitchAlignmentWAIsRequiredThenFalseIsReturned, IGFX_TIGERLAKE_LP);
HWTEST_EXCLUDE_PRODUCT(HwInfoConfigTest, givenHwInfoConfigWhenAskedIfForceEmuInt32DivRemSPWAIsRequiredThenFalseIsReturned, IGFX_TIGERLAKE_LP);
HWTEST_EXCLUDE_PRODUCT(HwInfoConfigTest, givenHwInfoConfigWhenAskedIf3DPipelineSelectWAIsRequiredThenFalseIsReturned, IGFX_TIGERLAKE_LP);
