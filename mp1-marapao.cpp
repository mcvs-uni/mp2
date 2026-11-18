#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <regex>
#include <filesystem>
#include "marapao_header.h"
using namespace std;

int main() {
	int AccessCode, TriesCounter = 5, TaskChoice, ShowCinemaTaskChoice, FileNameCount = NextFileNumber();
	string CinemaCode;

	DisplayAccessCodeInputPrompt();
	cin >> AccessCode;

	do {
		if (AccessCodeValidity(AccessCode)) {
			while (ProgramRunning) {
				DisplayMainMenu();
				if (!(cin >> TaskChoice)) {
					IfIntegerInputIsWrong();
					continue;
				}
				switch (TaskChoice) {
				case 1: {
					CinemaDetails Cinema = AddCinemaDetails();
					string FileNameInput(int FileNameCount, const CinemaDetails& Cinema);
					CinemaCode = FileNameInput(FileNameCount++, Cinema);
					cout << "Cinema code: " << CinemaCode << "\n";
					cout << "\nThe cinema has been added successfully. Going back to the main menu.\n";
					break;
				}
				case 2: {
					while (ShowCinemaTaskRunning) {
						DisplayShowCinemaMenu();
						if (!(cin >> ShowCinemaTaskChoice)) {
							IfIntegerInputIsWrong();
							continue;
						}
						switch (ShowCinemaTaskChoice) {
						case 1: {
							ShowSpecificCinema();
							cout << "\nGoing back to the main menu.\n";
							break;
						}
						case 2: {
							ShowAllCinemas();
							cout << "\nGoing back to the main menu.\n";
							break;
						}
						case 3: {
							cout << "Going back to the main menu.\n";
							goto TerminateShowCinema;
						}
						default: {
							IfInputIsWrong();
							break;
						}
						}
					}
					TerminateShowCinema:
					break;
				}
					
				case 3: {
					DeleteCinema();
					FileNameCount = NextFileNumber();
					break;
				}

				case 4: {
					cout << "\nYou have exited the program.\n";
					return 0;
				}
				default: {
					IfInputIsWrong();
					break;
				}
				}
			}
		}
		else {
			TriesCounter--;
			if (TriesCounter == 0) {
				cout << "\nNo more attempts left. Exiting the program . . .\n";
				return 0;
			}
			cout << "\nNumber of attempts left: " << TriesCounter << '\n';
			IfIntegerInputIsWrong();
			cin >> AccessCode;
		}
	} while (TriesCounter > 0);
	return 0;
}
