#include <iostream>
#include <fstream>
#include <string>

int CountIntLen(int a) {
    int counter = 0;
    while (a != 0) {
        counter++;
        a /= 10;
    }
    return counter;
}

int CountStrLen(std::string str) {
    int counter = 0;
    while (str[counter] != '\0') {
        counter++;
    }
    return counter;
}

std::string GetFileName(int argc, char* argv[]) {
    for (int i = 2; i < argc; i++) {
        int j = 0;
        while (argv[i][j] != '\0') {
            if (argv[i][j] == '.') {
                return argv[i];
            }
            j++;
        }
    }
    std::cerr << "File name was not found!";
    return "Error";
}

char GetDelimiter(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        std::string str = argv[i];
        if (str == "-d") {
            if (CountStrLen(argv[i + 1]) == 1) {
                return argv[i + 1][0];
            }
            else if ((CountStrLen(argv[i + 1]) == 2) && (argv[i + 1][0] == '\\')) {
                switch (argv[i][1]) {
                    case 'a':
                        return '\a';
                    case 'b':
                        return '\b';
                    case 'n':
                        return '\n';
                    case 't':
                        return '\t';
                    case '0':
                        return '\0';
                    case 'v':
                        return '\v';
                    case 'f':
                        return '\f';
                    case 'r':
                        return '\r';
                }
            }
            std::cerr << "Delimiter must be a single char!";
            return '\1';
        }
        else if (str[0] == '-' && str[2] == 'd') {
            if (CountStrLen(str.substr(12)) == 1) {
                return argv[i][12];
            }
            else if ((CountStrLen(str.substr(12)) == 2) && (argv[i][12] == '\\')) {
                switch (argv[i][1]) {
                    case 'a':
                        return '\a';
                    case 'b':
                        return '\b';
                    case 'n':
                        return '\n';
                    case 't':
                        return '\t';
                    case '0':
                        return '\0';
                    case 'v':
                        return '\v';
                    case 'f':
                        return '\f';
                    case 'r':
                        return '\r';
                }
            }
            std::cerr << "Delimiter must be a single char!";
            return '\1';
        }
    }
    return '\n';
}

int GetLinesNumber(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        std::string str = argv[i];
        if (str == "-l") {
            if (CountIntLen(std::stoi(argv[i + 1])) != CountStrLen(argv[i + 1])) {
                std::cerr << "Lines argument must be int object!";
                return -1;
            }
            return std::stoi(argv[i + 1]);
        }
        if (str.substr(0, 8) == "--lines=") {
            if (CountIntLen(stoi(str.substr(8))) != CountStrLen(str.substr(8))) {
                std::cerr << "Lines argument must be int object!";
                return -1;
            }
            return stoi(str.substr(8));
        }
    }
    return 0;
}

bool CheckTailArg(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        std::string str = argv[i];
        if ((str == "-t") || (str == "--tail")) {
            return true;
        }
    }
    return false;
}

bool CheckInvalidArguments(int argc, int linesNumber, char delimiter) {
    if (argc > 8) {
        return false;
    }
    else if ((linesNumber == -1) || (delimiter == '\1')) {
        return false;
    }
    return true;
}

int main(int argc,char *argv[]) {
    std::string file_name = GetFileName(argc, argv);
    std::ifstream file;
    file.open(file_name);

    char delimiter = GetDelimiter(argc, argv);
    int lines_argument = GetLinesNumber(argc, argv);
    bool is_tail = CheckTailArg(argc, argv);


    int lines_number = 1;
    char output;
    while (file.get(output)) {
        if (output == delimiter) {
            lines_number++;
        }
    }
    file.clear();
    file.seekg(0);
    if (lines_argument == 0) {
        lines_argument = lines_number;
    }

    if (!CheckInvalidArguments(argc, lines_argument, delimiter)) {
        std::cerr << "\nWrong arguments!";
        return 0;
    }

    else if (!is_tail) {
        int ctr = 0;
        while (file.get(output)) {
            if (ctr < lines_argument) {
                std::cout << output;
            }
            if (output == delimiter) {
                ctr++;
            }
        }
    }
    else {
        int ctr = 0;
        while(file.get(output)) {
            if (ctr == lines_number - lines_argument) {
                std::cout << output;
            }
            else if (output == delimiter) {
                ctr++;
            }
        }
    }
}
