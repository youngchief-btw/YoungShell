#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// The following are Linux & MacOS ONLY Terminal color codes.
// To-Do: Work on getting colors done in Windows (see here: https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c)
#ifdef __unix__
#define RESET "\033[0m"
#define BLACK "\033[30m" /* Black */
#define RED "\033[31m" /* Red */
#define GREEN "\033[32m" /* Green */
#define YELLOW "\033[33m" /* Yellow */
#define BLUE "\033[34m" /* Blue */
#define MAGENTA "\033[35m" /* Magenta */
#define CYAN "\033[36m" /* Cyan */
#define WHITE "\033[37m" /* White */
#define BOLDBLACK "\033[1m\033[30m" /* Bold Black */
#define BOLDRED "\033[1m\033[31m" /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m" /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m" /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m" /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m" /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m" /* Bold White */
#define UNDERLINE "\033[4m" /* Underline */
#define UNDERLINE_OFF "\033[0m" /* Turn off underlining */
#endif

int recieveInput() {
  string input = WHITE;
  input = "";
	ofstream filestream;

  cout << BOLDGREEN << getenv("USER") << "@" << getenv("HOSTNAME") << RESET << ":" << BOLDBLUE << getenv("DIRS") << RESET << "$ ";
  cin >> input;

  if (input == "help") {
    cout << BOLDMAGENTA << "Commands: \n- help | Run the YoungShell help command.\n- exit | Exit out of YoungShell (and also terminal if this is your default shell)\n- reload | Reload everything!\n- clear | Clear the shell.\n- shn | Set HostName (requires elevated permissions)\n- gab | 'Globally Avaliable Binary' (requires elevated permissions)\n- update | Update YoungShell and optionally the host computer (could need elevated permissions)\n- m3 | 'Manage/Modify My Machine' \n" << RESET;
  } else if (input == "exit") {
    cout << BOLDMAGENTA << "Now exiting YoungShell...\n" << RESET;
    return 0;
  } else if (input == "reload") {
    system("bash src/Setup.sh");
    return 0;
  } else if (input == "clear") {
		system("clear");
		cout << BOLDCYAN << "Welcome to YoungShell!\nYoungShell is open-source!! ( https://github.com/youngchief-btw/YoungShell )\n© 2020 youngchief btw ツ, All rights reserved.\nType `exit` to exit!\nType `help` for help!\n-----------------------------------------------------------------------------\n" << "\033[0m";
		#ifdef _WIN32
		cout << ">| Sorry about no colored output for Windows!\n>| I'm working on it!\n-----------------------------------------------------------------------------\n";
		#endif
  } else if (input == "shn") {
    cout << "Enter your new hostname. (must have sudo access)\n$ ";
    cin >> input;
			#ifdef _WIN32
			filestream.open("\Windows\System32\etc\hostname");
			#endif
			#ifdef __unix__
			filestream.open("/etc/hostname");
			#endif
			if (filestream.is_open()) {
				filestream << input;
				filestream.close();
			} else { 
				cout << "Unable to open file! Do you have access?\n";
			}
	} else if (input == "update") {
		cout << BOLDYELLOW << "Now updating YoungShell..." << RESET << WHITE << "\n";
		system("git pull https://github.com/youngchief-btw/YoungShell.git;git fetch https://github.com/youngchief-btw/YoungShell.git");
		cout << RESET << BOLDYELLOW << "Do you want to install system & application updates as well? (might require sudo permissions) [y/N]:" << RESET << " ";
		cin >> input;
		if (input == "y") {
			#ifdef _WIN32
				system("Install-Module PWWindowsUpdate;Get-WindowsUpdate;Install-WindowsUpdate");
			#endif
			#ifdef linux
				system("sudo apt-get update;sudo apt-get upgrade;sudo apt-get full-upgrade;sudo apt-get dist-upgrade");
			#endif
			#ifdef __MACH__
				system("softwareupdate -I -a");
			#endif
			cout << BOLDYELLOW << "Some updates may require a computer reboot!\n" << RESET;
		} else {}
	} else if (input == "gab") {
		cout << BOLDMAGENTA << "Globally Avaliable Binary (GAB) [do/undo]\n" << RESET;
		cin >> input;
		if (input == "do") {
		cout << BOLDMAGENTA << "Now creating a link from here to /bin/ys\nMake sure to have sudo permissions!\n" << RESET;
		#ifdef _WIN32
		system("mklink $(echo %cd%)\ys \Windows\System32\ys");
		#endif
		#ifdef __unix__
		system("ln $(pwd)/ys /bin/ys");
		#endif
		} else if (input == "undo") {
			cout << BOLDMAGENTA << "Now unlinking the globally avaliable binary from here\nMake sure to have sudo permissions!\n" << RESET;
			system("rm -rf /bin/ys");
		}
	} else if (input == "m3") {
		cout << BOLDMAGENTA << "Welcome to Manage My Machine!!\nValid Options: dns (DNS Settings), msc (Machine Specific Commands)\n" << RESET << "$ ";
		cin >> input;
		if (input == "dns") {
			cout << BOLDMAGENTA << ">| DNS Settings\n" << RESET << "$ ";
			cin >> input;
			if (input == "setsrvs") {
				cout << BOLDMAGENTA << ">>| Setting DNS Servers\n" << RESET << "$ ";
				cin >> input;
				#ifdef __MACH__
				system("networksetup -setdnsservers Wi-Fi" << input);
				#endif
				#ifdef linux
				filestream.open("/etc/resolv.conf");
				if (filestream.is_open()) {
					filestream << "nameserver " << input;
				}
				filestream.close();
				#endif
				#ifdef _WIN32
				#endif
				cout << BOLDMAGENTA << "DNS Servers Set!\n" << RESET;
			}
		} else if (input == "msc") {
			cout << BOLDMAGENTA << ">| Machine Specific Commands\n>| Valid Options: windows (Windows), \n" << RESET << "$ ";
			cin >> input;
			if (input == "windows") {
				#ifdef __unix__
				cout << BOLDMAGENTA << "Sorry! This is only for Windows users and you don't qualify!\n";
				#endif
				#ifdef _WIN32
				cout << BOLDMAGENTA << ">>| Windows\n" << RESET << "$ ";
				cin >> input;
				if (input == "awwr") {
					cout << BOLDMAGENTA << "Have you backed up your computer? [y/N]\n" << RESET << "$ ";
					cin >> input;
					if (input == "y") {
						cout << BOLDMAGENTA << "Now attempting 'Activate Windows' watermark removal...\nIf it doesn't work try the steps manually:\n- https://computergarage.org/how-to-remove-activate-windows-10-watermark-permanently.html\n- https://msguides.com/microsoft-software-products/2-ways-activate-windows-10-free-without-software.html\nBe sure to reboot your computer!\n" << RESET;
						system("reg add HKEY_CURRENT_USER\Control Panel\Desktop /v PaintDesktopVersion /d 0 /f;bcdedit -set TESTSIGNING OFF");
						cout << BOLDMAGENTA << "Would you like to reboot now? [y/N]\n" << RESET << "$ ";
						cin >> input;
						if (input == "y") {
							cout << BOLDMAGENTA << "Rebooting in 5 seconds...\n" << RESET << "$ ";
							chrono::milliseconds timespan(5000);
							this_thread::sleep_for(timespan);
							system("shutdown /r");
						} else {
							cout << BOLDMAGENTA << "Be sure to reboot later!\n" << RESET;
						}
					} else {
						cout << BOLDMAGENTA << "Go backup your computer!\n" << RESET;
					}
					#endif
				} else if (input == "spk") {
					cout << BOLDMAGENTA << "What would you like to set your product key to?\n" << RESET;
					cin >> input;
					system("slmgr.vbs /ipk " + input);
					cout << BOLDMAGENTA << "\n" << RESET;
				}
			}
		} else {
		cout << BOLDMAGENTA << "Unknown command! Try it in Bash!\nTo get back to YoungShell, just type `exit`\n" << RESET;
    system("bash");
  }
  recieveInput();
}

int main() {
  system("clear");
  cout << BOLDCYAN << "Welcome to YoungShell!\nYoungShell is open-source!! ( https://github.com/youngchief-btw/YoungShell )\n© 2020 youngchief btw ツ, All rights reserved.\nType `exit` to exit!\nType `help` for help!\n-----------------------------------------------------------------------------\n" << "\033[0m";
	#ifdef _WIN32
	cout << ">| Sorry about no colored output for Windows!\n>I'm working on it!\n-----------------------------------------------------------------------------\n";
	#endif
  recieveInput();
  return 0;
}
