#pragma once

#include <stdio.h>
#include <vector>

#include <switch.h>

class SaveDataManager {
private:
	std::vector<FsSaveDataInfo> SaveDataInfoList;
public:
	inline Result ReadSaveDataInfoList() {
		this->SaveDataInfoList.clear();

		Result rc = 0;
		FsSaveDataIterator SaveIterator;
		FsSaveDataInfo SaveInfo;
		size_t EntryCount;

		rc = fsOpenSaveDataIterator(&SaveIterator, FsSaveDataSpaceId_NandUser);
		if (R_FAILED(rc)) {
			printf("Failed fsOpenSaveDataIterator\n");
			return rc;
		}

		rc = fsSaveDataIteratorRead(&SaveIterator, &SaveInfo, 1, &EntryCount);
		if (R_FAILED(rc)) {
			printf("Failed fsSaveDataIteratorRead\n");
			return rc;
		}

		if (EntryCount == 0) {
			return MAKERESULT(Module_Libnx, LibnxError_NotFound);
		}

		while (R_SUCCEEDED(rc) && EntryCount > 0) {
			if (SaveInfo.SaveDataType == FsSaveDataType_SaveData) {
				this->SaveDataInfoList.push_back(SaveInfo);
			}

			rc = fsSaveDataIteratorRead(&SaveIterator, &SaveInfo, 1, &EntryCount);
		}

		fsSaveDataIteratorClose(&SaveIterator);
		return 0;
	}

	inline std::vector<FsSaveDataInfo> GetSaveDataInfoList() {
		return this->SaveDataInfoList;
	}
};