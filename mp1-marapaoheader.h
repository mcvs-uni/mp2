#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <regex>
#include <filesystem>
using namespace std;

struct CinemaDetails {
	int Capacity{ }, NumberOfRows{ }, TicketPrice{ };
	string CinemaName, StreetName, BuildingName, BarangayName, AreaName, ContactNumber, CinemaType, CinemaCode;
};

namespace fs = std::filesystem;

void DisplayAccessCodeInputPrompt() {
	cout << "Welcome to the cinema registration system.\n";
	cout << "Please input your three-digit access code.\n";
}

bool AccessCodeValidity(int AccessCode) {
	if (AccessCode == 230) {
		return true;
	}
	else {
		return false;
	}
}

bool ProgramRunning = true;

void DisplayMainMenu() {
	cout << "\nMain menu of the cinema registration system:\n";
	cout << "Please input the number of the task you would like to do.\n";
	cout << "1. Add cinema\n";
	cout << "2. Show cinema(s)\n";
	cout << "3. Delete cinema\n";
	cout << "4. Exit program\n";
}

void IfIntegerInputIsWrong() {
	cin.clear();
	cin.ignore(1000, '\n');
	cout << "Invalid input. Try again.\n";
}

void IfInputIsWrong() {
	cout << "Invalid input. Try again.\n";
}

bool ContactNumberValidity(const string& ContactNumber) {
	static const regex ContactNumberPattern(R"(^\+639[0-9]{9}$)");
	return regex_match(ContactNumber, ContactNumberPattern);
}

bool CinemaTypeValidity(string CinemaType) {
	if (CinemaType == "Regular" || CinemaType == "IMAX" || CinemaType == "IMAX with 3D" || CinemaType == "Digital Theater" || CinemaType == "ScreenX" || CinemaType == "Director's Club" || CinemaType == "4DX") {
		return true;
	}
	else {
		return false;
	}
}

CinemaDetails AddCinemaDetails() {
	CinemaDetails Cinema;

	cout << "\nAdding cinema details:\n";

	cout << "Add cinema name:\n";
	cin.ignore(1000, '\n');
	getline(cin, Cinema.CinemaName);

	cout << "\nAdding address: add the cinema's street name:\n";
	getline(cin, Cinema.StreetName);

	cout << "\nAdding address: add the cinema's building/subdivision name:\n";
	getline(cin, Cinema.BuildingName);

	cout << "\nAdding address: add the cinema's barangay name:\n";
	getline(cin, Cinema.BarangayName);

	cout << "\nAdding address: add the cinema's city/municipality name:\n";
	getline(cin, Cinema.AreaName);

	cout << "\nAdd the cinema's capacity:\n";
	while (!(cin >> Cinema.Capacity) || Cinema.Capacity <= 0) {
		IfIntegerInputIsWrong();
	}

	cout << "\nAdd the cinema's number of rows:\n";
	while (!(cin >> Cinema.NumberOfRows) || Cinema.NumberOfRows <= 0) {
		IfIntegerInputIsWrong();
	}

	cout << "\nAdd the cinema's contact number:\n";
	cout << "The only accepted format is +639XXXXXXXXX (mobile number format).\n";
	cin.ignore(1000, '\n');
	getline(cin, Cinema.ContactNumber);
	while (!ContactNumberValidity(Cinema.ContactNumber)) {
		IfInputIsWrong();
		getline(cin, Cinema.ContactNumber);
	}

	cout << "\nAdd the cinema's ticket price:\n";
	while (!(cin >> Cinema.TicketPrice) || Cinema.TicketPrice <= 0) {
		IfIntegerInputIsWrong();
	}

	cout << "\nAdd the cinema's type:\n";
	cout << "The only accepted types (case-sensitive) are: Regular, IMAX, IMAX with 3D,\n";
	cout << "Digital Theater, ScreenX, Director's Club, and 4DX.\n";
	cin.ignore(1000, '\n');
	getline(cin, Cinema.CinemaType);
	while (!CinemaTypeValidity(Cinema.CinemaType)) {
		IfInputIsWrong();
		getline(cin, Cinema.CinemaType);
	}

	return Cinema;
}

string FileNameInput(int FileNameCount, const CinemaDetails& Cinema) {
	
	ostringstream FileName;
	FileName << "I-" << setw(3) << setfill('0') << FileNameCount;

	fstream CinemaFile;

	CinemaFile.open(FileName.str() + ".txt", ios::out);
	CinemaFile << "Cinema name: " << Cinema.CinemaName << '\n';
	CinemaFile << "Address:\n";
	CinemaFile << Cinema.StreetName << ", " << Cinema.BuildingName << '\n';
	CinemaFile << Cinema.BarangayName << ", " << Cinema.AreaName << '\n';
	CinemaFile << "Capacity: " << Cinema.Capacity << '\n';
	CinemaFile << "Number of rows: " << Cinema.NumberOfRows << '\n';
	CinemaFile << "Number of seats per row: " << Cinema.Capacity / Cinema.NumberOfRows << '\n';
	CinemaFile << "Contact number (mobile): " << Cinema.ContactNumber << '\n';
	CinemaFile << "Ticket price: PHP " << Cinema.TicketPrice << '\n';
	CinemaFile << "Cinema type: " << Cinema.CinemaType << '\n';
	CinemaFile << "Cinema Code # " << FileName.str() << '\n';
	CinemaFile.close();

	CinemaFile.open("Cinema List.txt", ios::app);
	if (CinemaFile.is_open()) {
		CinemaFile << FileName.str() << " " << Cinema.CinemaName << '\n';
		CinemaFile.close();
	}

	return FileName.str();
}

int NextFileNumber() {
	for (int FileNameCount = 1; FileNameCount <= 999; FileNameCount++) {
		ostringstream FileName;
		FileName << "I-" << setw(3) << setfill('0') << FileNameCount;
		fstream CinemaFile;
		CinemaFile.open(FileName.str() + ".txt", ios::in);
		if (!CinemaFile) {
			return FileNameCount;
		}
	}
	return -1;
}

void DisplayShowCinemaMenu() {
	cout << "\nShowing cinema details:\n";
	cout << "Please input the number of the task you would like to do.\n";
	cout << "1. Show cinema\n";
	cout << "2. Show all cinemas\n";
	cout << "3. Go back to the main menu\n";
}

bool ShowCinemaTaskRunning = true;

void ShowAllCinemas() {
	string line;
	fstream CinemaFile;
	cout << "\nCurrently registered cinemas in the system: \n";
	CinemaFile.open("Cinema List.txt", ios::in);
	if (CinemaFile.is_open()) {
		while (getline(CinemaFile, line)) {
			cout << line << '\n';
		}
		CinemaFile.close();
	}
	else {
		cout << "Unable to open file or file does not exist.\n";
	}
}

bool InputCinemaCodeValidity(string InputCinemaCode) {
	static const regex InputCinemaCodePattern(R"(^I-[0-9]{3}$)");
	return regex_match(InputCinemaCode, InputCinemaCodePattern);
}

void ShowSpecificCinema() {
	string InputCinemaCode, line;
	cout << "\nPlease input the code of the cinema you would like to see information of (I-XXX).\n";
	cin.ignore(1000, '\n');
	getline(cin, InputCinemaCode);
	while (!InputCinemaCodeValidity(InputCinemaCode)) {
		IfInputIsWrong();
		getline(cin, InputCinemaCode);
	}
	cout << "\nContents of " << InputCinemaCode << ":\n";
	fstream CinemaFile;
	CinemaFile.open(InputCinemaCode + ".txt", ios::in);
	if (CinemaFile.is_open()) {
		while (getline(CinemaFile, line)) {
			cout << line << '\n';
		}
		CinemaFile.close();
	}
	else {
		cout << "Unable to open file or file does not exist.\n";
	}
}

string FileNameInput(int FileNameCount) {
	ostringstream FileName;
	FileName << "I-" << setw(3) << setfill('0') << FileNameCount;
	return FileName.str();
}
int CinemaCodeToFileNameCount(const string& FileNameInput) {
	return stoi(FileNameInput.substr(2));
}

void RewriteCodeInsideExistingFile(const string& FileName, const string& NewCode) {
	const int MaxLines = 11;
	string Lines[MaxLines];
	int LineCount = 0;
	string line;

	fstream CinemaFile;
	CinemaFile.open(FileName, ios::in);
	while (LineCount < MaxLines && getline(CinemaFile, line)) {
		Lines[LineCount] = line;
		LineCount++;
	}
	CinemaFile.close();

	if (LineCount == MaxLines) {
		Lines[MaxLines - 1] = "Cinema Code # " + NewCode;
	}

	CinemaFile.open(FileName, ios::out | ios::trunc);
	for (int i = 0; i < LineCount; i++) {
		CinemaFile << Lines[i] << '\n';
	}
	CinemaFile.close();
}

void RewriteCinemaList() {
	static string List[999][2];
	int Count = 0;

	for (int j = 1; j <= 999 && fs::exists(FileNameInput(j) + ".txt"); j++) {
		string CinemaCode = FileNameInput(j);

		fstream CinemaList;
		CinemaList.open(CinemaCode + ".txt", ios::in);

		string line, Name;
		bool NameFound = false;
		while (!NameFound && getline(CinemaList, line)) {
			if (line.rfind("Cinema name: ", 0) == 0) {
				Name = line.substr(13);
				NameFound = true;
			}
		}

		CinemaList.close();

		List[Count][0] = CinemaCode;
		List[Count][1] = Name;
		Count++;
	}

	fstream CinemaList;
	CinemaList.open("Cinema List.txt", ios::out | ios::trunc);
	for (int k = 0; k < Count; k++) {
		CinemaList << List[k][0] << " " << List[k][1] << '\n';
	}
	CinemaList.close();
}

void DeleteCinema() {
	string InputCinemaCode;
	cout << "\nPlease input the code of the cinema you would like to delete from the system (I-XXX).\n";
	cin.ignore(1000, '\n');
	getline(cin, InputCinemaCode);

	while (!InputCinemaCodeValidity(InputCinemaCode) || !fs::exists(InputCinemaCode + ".txt")) {
		IfInputIsWrong();
		getline(cin, InputCinemaCode);
	}

	int DeletedNumber = CinemaCodeToFileNameCount(InputCinemaCode);
	fs::remove(InputCinemaCode + ".txt");

	for (int l = DeletedNumber + 1; l <= 999 && fs::exists(FileNameInput(l) + ".txt"); l++) {
		string OldFile = FileNameInput(l) + ".txt";
		string NewCode = FileNameInput(l - 1);

		fs::rename(OldFile, NewCode + ".txt");
		RewriteCodeInsideExistingFile(NewCode + ".txt", NewCode);
	}

	RewriteCinemaList();
	cout << "\nCinema " << InputCinemaCode << " has now been deleted.\n";
}
