/*
 * Copyright (C) 2023-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "shared/source/ail/ail_configuration.h"

namespace NEO {
class MockAILConfiguration : public AILConfiguration {
  public:
    bool initProcessExecutableNameResult = true;
    bool initProcessExecutableName() override {
        return initProcessExecutableNameResult;
    }
    void modifyKernelIfRequired(std::string &kernel) override {}

    bool contextSyncFlagReturn = false;
    bool isContextSyncFlagRequired() override {
        return contextSyncFlagReturn;
    }

    bool prefetchDisableRequiredReturn = false;
    bool is256BPrefetchDisableRequired() override {
        return prefetchDisableRequiredReturn;
    }

    bool isBufferPoolEnabledReturn = true;
    bool isBufferPoolEnabled() override {
        return isBufferPoolEnabledReturn;
    }

    bool isRunAloneContextRequiredReturn = false;
    bool isRunAloneContextRequired() override {
        return isRunAloneContextRequiredReturn;
    }

    bool limitAmountOfDeviceMemoryForRecyclingReturn = false;
    bool limitAmountOfDeviceMemoryForRecycling() override {
        return limitAmountOfDeviceMemoryForRecyclingReturn;
    }

    bool fallbackToLegacyValidationLogic = false;
    bool useLegacyValidationLogic() override {
        return fallbackToLegacyValidationLogic;
    }
    bool forceRcsValue = false;
    bool forceRcs() override {
        return forceRcsValue;
    }

    bool handleDivergentBarriers() override {
        return handleDivergentBarriersValue;
    }
    void setHandleDivergentBarriers(bool val) override {
        handleDivergentBarriersValue = val;
    }
    bool handleDivergentBarriersValue = false;

    bool disableBindlessAddressing() override {
        return disableBindlessAddressingValue;
    }
    void setDisableBindlessAddressing(bool val) override {
        disableBindlessAddressingValue = val;
    }
    bool disableBindlessAddressingValue = false;

    bool drainHostptrs() override {
        return true;
    }

    bool isFallbackToPatchtokensRequired() override {
        return false;
    }

  protected:
    void applyExt(RuntimeCapabilityTable &runtimeCapabilityTable) override {}
};

template <PRODUCT_FAMILY productFamily>
class AILWhitebox : public AILConfigurationHw<productFamily> {
  public:
    using AILConfiguration::apply;
    using AILConfiguration::isKernelHashCorrect;
    using AILConfiguration::processName;
    using AILConfiguration::sourcesContain;
};

} // namespace NEO
