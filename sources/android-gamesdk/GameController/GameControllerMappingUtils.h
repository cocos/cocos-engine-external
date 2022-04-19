/*
 * Copyright (C) 2021 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <cstdint>

#ifndef PADDLEBOAT_H
#include "paddleboat.h"
#endif

namespace paddleboat {
class MappingTableSearch {
   public:
    MappingTableSearch();

    MappingTableSearch(Paddleboat_Controller_Mapping_Data *mapRoot,
                       int32_t entryCount);

    void initSearchParameters(const int32_t newVendorId,
                              const int32_t newProductId,
                              const int32_t newMinApi, const int32_t newMaxApi);

    Paddleboat_Controller_Mapping_Data *mappingRoot;
    int32_t vendorId;
    int32_t productId;
    int32_t minApi;
    int32_t maxApi;
    int32_t tableIndex;
    int32_t mapEntryCount;
    int32_t tableEntryCount;
    int32_t tableMaxEntryCount;
};

class GameControllerMappingUtils {
   public:
    static bool findMatchingMapEntry(MappingTableSearch *searchEntry);

    static bool insertMapEntry(
        const Paddleboat_Controller_Mapping_Data *mappingData,
        MappingTableSearch *searchEntry);

    static const Paddleboat_Controller_Mapping_Data *validateMapTable(
        const Paddleboat_Controller_Mapping_Data *mappingRoot,
        const int32_t tableEntryCount);
};
}  // namespace paddleboat
