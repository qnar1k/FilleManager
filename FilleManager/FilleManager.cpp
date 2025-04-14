#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;
using namespace std;

void listFiles(const string& path) {
    cout << "Listing files in: " << path << "\n";
    for (const auto& entry : fs::directory_iterator(path)) {
        cout << (entry.is_directory() ? "[DIR]  " : "[FILE] ")
            << entry.path().filename()
            << " (Size: " << fs::file_size(entry.path()) << " bytes)\n";
    }
    cout << endl;
}

void deleteFile(const string& path) {
    if (fs::exists(path) && fs::is_regular_file(path)) {
        fs::remove(path);
        cout << "File deleted.\n";
    }
    else {
        cout << "File not found.\n";
    }
}

void moveFile(const string& from, const string& to) {
    if (fs::exists(from)) {
        fs::rename(from, to);
        cout << "Moved.\n";
    }
    else {
        cout << "Source file not found.\n";
    }
}

int main() {
    string command;
    cout << "Welcome to FileManager 1.0\n";

    while (true) {
        cout << "\nCommands: ls [path] | rm [file] | mv [from] [to] | quit\n> ";
        getline(cin, command);

        if (command == "quit") break;

        if (command.rfind("ls", 0) == 0) {
            string path = ".";
            if (command.length() > 3)
                path = command.substr(3);
            listFiles(path);
        }
        else if (command.rfind("rm", 0) == 0) {
            string file = command.substr(3);
            deleteFile(file);
        }
        else if (command.rfind("mv", 0) == 0) {
            size_t space1 = command.find(' ', 3);
            if (space1 != string::npos) {
                string from = command.substr(3, space1 - 3);
                string to = command.substr(space1 + 1);
                moveFile(from, to);
            }
            else {
                cout << "Invalid syntax. Use: mv [from] [to]\n";
            }
        }
        else {
            cout << "Unknown command.\n";
        }
    }

    cout << "Bye!\n";
    return 0;
}
