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

#include "GameControllerMappingUtils.h"

#include "GameControllerManager.h"

namespace paddleboat {
MappingTableSearch::MappingTableSearch()
    : mappingRoot(nullptr),
      vendorId(0),
      productId(0),
      minApi(0),
      maxApi(0),
      tableIndex(0),
      mapEntryCount(0),
      tableEntryCount(0),
      tableMaxEntryCount(GameControllerManager::getRemapTableSize()) {}

MappingTableSearch::MappingTableSearch(
    Paddleboat_Controller_Mapping_Data *mapRoot, int32_t entryCount)
    : mappingRoot(mapRoot),
      vendorId(0),
      productId(0),
      minApi(0),
      maxApi(0),
      tableIndex(0),
      mapEntryCount(0),
      tableEntryCount(entryCount),
      tableMaxEntryCount(GameControllerManager::getRemapTableSize()) {}

void MappingTableSearch::initSearchParameters(const int32_t newVendorId,
                                              const int32_t newProductId,
                                              const int32_t newMinApi,
                                              const int32_t newMaxApi) {
    vendorId = newVendorId;
    productId = newProductId;
    minApi = newMinApi;
    maxApi = newMaxApi;
    tableIndex = 0;
}

bool GameControllerMappingUtils::findMatchingMapEntry(
    MappingTableSearch *searchEntry) {
    int32_t currentIndex = 0;

    // Starting out with a linear search. Updating the map table is something
    // that should only ever be done once at startup, if it actually takes an
    // appreciable time to execute when working with a big remap dictionary,
    // this is low-hanging fruit to optimize.
    const Paddleboat_Controller_Mapping_Data *mapRoot =
        searchEntry->mappingRoot;
    while (currentIndex < searchEntry->tableEntryCount) {
        const Paddleboat_Controller_Mapping_Data &mapEntry =
            mapRoot[currentIndex];
        if (mapEntry.vendorId > searchEntry->vendorId) {
            // Passed by the search vendorId value, so we don't already exist in
            // the table, set the current index as the insert point and bail
            searchEntry->tableIndex = currentIndex;
            return false;
        } else if (searchEntry->vendorId == mapEntry.vendorId) {
            if (mapEntry.productId > searchEntry->productId) {
                // Passed by the search productId value, so we don't already
                // exist in the table, set the current index as the insert point
                // and bail
                searchEntry->tableIndex = currentIndex;
                return false;
            } else if (searchEntry->productId == mapEntry.productId) {
                // Any overlap of the min/max API range is treated as matching
                // an existing entry
                if ((searchEntry->minApi >= mapEntry.minimumEffectiveApiLevel &&
                     searchEntry->minApi <=
                         mapEntry.maximumEffectiveApiLevel) ||
                    (searchEntry->minApi >= mapEntry.minimumEffectiveApiLevel &&
                     mapEntry.maximumEffectiveApiLevel == 0)) {
                    searchEntry->tableIndex = currentIndex;
                    return true;
                }
            }
        }
        ++currentIndex;
    }
    searchEntry->tableIndex = currentIndex;
    return false;
}

bool GameControllerMappingUtils::insertMapEntry(
    const Paddleboat_Controller_Mapping_Data *mappingData,
    MappingTableSearch *searchEntry) {
    bool insertSuccess = false;
    // Verify there is room in the table for another entry
    if (searchEntry->tableEntryCount < searchEntry->tableMaxEntryCount &&
        searchEntry->tableIndex < searchEntry->tableMaxEntryCount) {
        // Empty table, or inserting at the end, no relocation of existing data
        // required, otherwise shift existing data down starting at the insert
        // index.
        if (!(searchEntry->tableEntryCount == 0 ||
              searchEntry->tableIndex == searchEntry->tableEntryCount)) {
            const size_t copySize =
                (searchEntry->tableEntryCount - searchEntry->tableIndex) *
                sizeof(Paddleboat_Controller_Mapping_Data);
            memmove(&searchEntry->mappingRoot[searchEntry->tableIndex + 1],
                    &searchEntry->mappingRoot[searchEntry->tableIndex],
                    copySize);
        }
        // Insert the new data
        memcpy(&searchEntry->mappingRoot[searchEntry->tableIndex], mappingData,
               sizeof(Paddleboat_Controller_Mapping_Data));
        insertSuccess = true;
    }
    return insertSuccess;
}

const Paddleboat_Controller_Mapping_Data *
GameControllerMappingUtils::validateMapTable(
    const Paddleboat_Controller_Mapping_Data *mappingRoot,
    const int32_t tableEntryCount) {
    // The map table is always assumed to be sorted by increasing vendorId. Each
    // sequence of entries with the same vendorId are sorted by increasing
    // productId. Multiple entries with the same vendorId/productId range are
    // sorted by increasing min/max API ranges. vendorId
    //   productId
    //      minApi
    int32_t currentIndex = 0;
    int32_t previousVendorId = -1;
    while (currentIndex < tableEntryCount) {
        if (mappingRoot[currentIndex].vendorId < previousVendorId) {
            // failure in vendorId order, return the offending entry
            return &mappingRoot[currentIndex];
        }

        int32_t previousProductId = mappingRoot[currentIndex].productId;
        int32_t previousMinApi =
            mappingRoot[currentIndex].minimumEffectiveApiLevel;
        int32_t previousMaxApi =
            mappingRoot[currentIndex].maximumEffectiveApiLevel;
        previousVendorId = mappingRoot[currentIndex++].vendorId;

        while (currentIndex < tableEntryCount &&
               mappingRoot[currentIndex].vendorId == previousVendorId) {
            while (currentIndex < tableEntryCount &&
                   mappingRoot[currentIndex].productId == previousProductId) {
                if (mappingRoot[currentIndex].minimumEffectiveApiLevel <
                        previousMinApi ||
                    mappingRoot[currentIndex].minimumEffectiveApiLevel <
                        previousMaxApi) {
                    // failure in API order, return the offending entry
                    return &mappingRoot[currentIndex];
                }
                previousMinApi =
                    mappingRoot[currentIndex].minimumEffectiveApiLevel;
                previousMaxApi =
                    mappingRoot[currentIndex++].maximumEffectiveApiLevel;
            }
            if (mappingRoot[currentIndex].productId < previousProductId) {
                // failure in productId order, return the offending entry
                return &mappingRoot[currentIndex];
            }
            previousProductId = mappingRoot[currentIndex++].productId;
        }
    }

    // Validation success, return nullptr (no offending entries to return)
    return nullptr;
}
}  // namespace paddleboat
