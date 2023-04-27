/*
 * Copyright (C) 2020-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "shared/source/compiler_interface/default_cache_config.h"

#include "shared/source/helpers/constants.h"
#include "shared/source/os_interface/sys_calls_common.h"
#include "shared/source/utilities/debug_settings_reader.h"

#include "opencl/source/os_interface/ocl_reg_path.h"

#include "config.h"
#include "os_inc.h"

#include <string>

namespace NEO {
CompilerCacheConfig getDefaultCompilerCacheConfig() {
    CompilerCacheConfig ret;

    std::string keyName = oclRegPath;
    keyName += "cl_cache_dir";
    std::unique_ptr<SettingsReader> settingsReader(SettingsReader::createOsReader(false, keyName));
    ret.cacheDir = settingsReader->getSetting(settingsReader->appSpecificLocation(keyName), static_cast<std::string>(CL_CACHE_LOCATION));

    if (NEO::SysCalls::pathExists(ret.cacheDir)) {
        ret.enabled = true;
        ret.cacheSize = MemoryConstants::gigaByte;
        ret.cacheFileExtension = ".cl_cache";
    } else {
        ret.enabled = false;
        ret.cacheSize = 0u;
        ret.cacheFileExtension = ".cl_cache";
    }

    return ret;
}

} // namespace NEO
