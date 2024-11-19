/*
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "shared/source/helpers/basic_math.h"
#include "shared/source/helpers/hw_info.h"
#include "shared/test/common/test_macros/test.h"

using namespace NEO;

TEST(HwInfoTest, whenSettingDefaultFeatureTableAndWorkaroundTableThenProperFieldsAreSet) {
    HardwareInfo hwInfo{};
    FeatureTable expectedFeatureTable{};
    WorkaroundTable expectedWorkaroundTable{};

    expectedFeatureTable.flags.ftrAstcHdr2D = true;
    expectedFeatureTable.flags.ftrAstcLdr2D = true;
    expectedFeatureTable.flags.ftrCCSNode = true;
    expectedFeatureTable.flags.ftrCCSRing = true;
    expectedFeatureTable.flags.ftrFbc = true;
    expectedFeatureTable.flags.ftrGpGpuMidBatchPreempt = true;
    expectedFeatureTable.flags.ftrGpGpuThreadGroupLevelPreempt = true;
    expectedFeatureTable.flags.ftrIA32eGfxPTEs = true;
    expectedFeatureTable.flags.ftrL3IACoherency = true;
    expectedFeatureTable.flags.ftrLinearCCS = true;
    expectedFeatureTable.flags.ftrPPGTT = true;
    expectedFeatureTable.flags.ftrSVM = true;
    expectedFeatureTable.flags.ftrStandardMipTailFormat = true;
    expectedFeatureTable.flags.ftrTileMappedResource = true;
    expectedFeatureTable.flags.ftrTranslationTable = true;
    expectedFeatureTable.flags.ftrUserModeTranslationTable = true;

    expectedWorkaroundTable.flags.wa4kAlignUVOffsetNV12LinearSurface = true;

    setupDefaultFeatureTableAndWorkaroundTable(&hwInfo);

    EXPECT_EQ(expectedFeatureTable.asHash(), hwInfo.featureTable.asHash());
    EXPECT_EQ(expectedWorkaroundTable.asHash(), hwInfo.workaroundTable.asHash());
}

TEST(HwInfoTest, givenHwInfoWhenQueryNumSubSlicesPerSliceThenCorrectNumberIsReturned) {
    HardwareInfo hwInfo{};
    hwInfo.gtSystemInfo.SliceCount = 2;
    hwInfo.gtSystemInfo.SubSliceCount = 7;
    auto expectedNumSubSlicesPerSlice = static_cast<uint32_t>(Math::divideAndRoundUp(hwInfo.gtSystemInfo.SubSliceCount, hwInfo.gtSystemInfo.SliceCount));
    EXPECT_EQ(getNumSubSlicesPerSlice(hwInfo), expectedNumSubSlicesPerSlice);
}
