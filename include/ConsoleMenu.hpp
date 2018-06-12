#pragma once

#include <string.h>
#include <stdio.h>
#include <vector>

#include <switch.h>

class ConsoleMenu {
private:
	std::vector<std::string> Entries;
	unsigned char CurrentEntry = 0;
public:
	unsigned int GetCurrentEntryIndex() {
		return this->CurrentEntry;
	};

	unsigned int GetEntryCount() {
		return this->Entries.size();
	};

	std::string GetEntry(unsigned int index) {
		if (this->GetEntryCount() > index) {
			return this->Entries[index];
		}

		return NULL;
	};

	std::string GetCurrentEntry() {
		return this->GetEntry(this->GetCurrentEntryIndex());
	};

	void SetCurrentEntryIndex(unsigned int index) {
		this->CurrentEntry = index;
	}

	void MoveUp() {
		if (this->GetCurrentEntryIndex() == 0) {
			this->SetCurrentEntryIndex(this->GetEntryCount() - 1);
		}
		else {
			this->SetCurrentEntryIndex(this->GetCurrentEntryIndex() - 1);
		}
	}

	void MoveDown() {
		if (this->GetCurrentEntryIndex() == this->GetEntryCount() - 1) {
			this->SetCurrentEntryIndex(0);
		}
		else {
			this->SetCurrentEntryIndex(this->GetCurrentEntryIndex() + 1);
		}
	}

	void AddEntry(std::string entry) {
		this->Entries.push_back(entry);
	};

	void PrintMenu() {
		for(unsigned int i = 0; i < this->GetEntryCount(); i++) {
			std::string CurrentEntry = this->GetEntry(i);
			if (this->GetCurrentEntryIndex() == i) {
				printf(">>");
			} else {
				printf("  ");
			}

			printf("%s\n", CurrentEntry.c_str());
		}
	};
};