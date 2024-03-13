#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string readFile(const string& path) {
    ifstream inputFile;
    string fileContent;
    inputFile.open(path);
    if (inputFile.is_open()) {
        char ch;
        while (inputFile.get(ch))
        {
            fileContent.push_back(ch);
        }
    }
    else {
        cout << "Input File not open!" << endl;
        inputFile.close();
        return fileContent;
    }
    inputFile.close();
    return fileContent;
}

vector<int> stringToVector(const string& input) {
    vector<int> output;
    string currentNumber;
    for (int i = 0; i < input.size(); i++) {
        if (input[i] != ' ') {
            currentNumber.push_back(input[i]);
        }
        if (input[i] == ' ' || (i + 1 == input.size())) {
            int sum = 0;

            for (int j = 0; j < currentNumber.size(); j++) {
                if ((int)currentNumber[j] > 47 && (int)currentNumber[j] < 58)
                {
                    int multiplier = 1;
                    for (int k = 1; k < currentNumber.size() - j; k++) {
                        multiplier *= 10;
                    }
                    sum += ((int)currentNumber[j] - 48) * multiplier;
                }
                else {
                    return vector<int>(0);
                }
            }

            output.push_back(sum);
            currentNumber = "";
        }
    }

    return output;
}

bool isTriangle(int triangleSize) {
    int k = 0;
    for (int i = 0; i <= triangleSize; i += k) {
        if (i == triangleSize) {
            return true;
        }
        k++;
    }
    return false;
}

bool isPascalsTriangle(const vector<int>& triangle) {
    if (!isTriangle(triangle.size())) {
        return false;
    }

    int elementsChecked = 0;
    int stringElementCount = 1;

    for (int i = 0; elementsChecked < triangle.size(); i++) {

        int val = 1;
        for (int j = 0; j < stringElementCount; j++) {
            if (triangle[elementsChecked + j] != val) {
                return false;
            }
            val *= ((double)(i - j) / (j + 1));
        }
        elementsChecked += stringElementCount;
        stringElementCount++;
    }

    return true;
}

void trianglePrint(const vector<int>& triangle, ofstream& outputFile) {
    if (isTriangle(triangle.size())) {
        int elementsChecked = 0;
        int stringElementCount = 1;
        for (int i = 0; elementsChecked < triangle.size(); i++) {
            for (int j = 0; j < stringElementCount; j++) {
                outputFile << triangle[elementsChecked + j] << ' ';
            }
            outputFile << endl;
            elementsChecked += stringElementCount;
            stringElementCount++;
        }
    }
}

vector<vector<int>> mistakesSearch(const vector<int>& triangle) {
    vector<vector<int>> mistakeStrings;

    if (!isTriangle(triangle.size())) {
        return mistakeStrings;
    }

    int elementsChecked = 0;
    int stringElementCount = 1;

    for (int i = 0; elementsChecked < triangle.size(); i++) {
        vector<int> currentString = vector<int>(0);
        int val = 1;
        bool isMistake = false;
        for (int j = 0; j < stringElementCount; j++) {
            if (triangle[elementsChecked + j] != val) {
                isMistake = true;
            }
            currentString.push_back(triangle[elementsChecked + j]);
            val *= ((double)(i - j) / (j + 1));
        }
        elementsChecked += stringElementCount;
        stringElementCount++;
        if (isMistake) {
            mistakeStrings.push_back(currentString);
        }
    }

    return mistakeStrings;
}

vector<int> mistakesCorrection(vector<int> triangle) {
    if (!isTriangle(triangle.size())) {
        return triangle;
    }

    int elementsChecked = 0;
    int stringElementCount = 1;

    for (int i = 0; elementsChecked < triangle.size(); i++) {

        int val = 1;
        for (int j = 0; j < stringElementCount; j++) {
            if (triangle[elementsChecked + j] != val) {
                triangle[elementsChecked + j] = val;
            }
            val *= ((double)(i - j) / (j + 1));
        }
        elementsChecked += stringElementCount;
        stringElementCount++;
    }

    return triangle;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Incorrect input! (CurseWork.exe {FileName})";
        return 1;
    }
    vector<int> triangle = stringToVector(readFile(argv[1]));
    cout << ("Is it triangle? : ") << (isTriangle(triangle.size()) ? "Yes\n" : "No\n");
    cout << ("Is it Pascal triangle? : ") << (isPascalsTriangle(triangle) ? "Yes\n" : "No\n");

    if (!isTriangle(triangle.size())) {
        return 1;
    }

    ofstream outputFile;
    outputFile.open(argv[1]);
    if (!outputFile.is_open()) {
        outputFile.close();
        cout << "Out File not open!" << endl;
        return 1;
    }

    cout << endl << "Mistake strings: " << endl;

    vector<vector<int>> mStrings = mistakesSearch(triangle);
    for (int i = 0; i < mStrings.size(); i++) {
        for (int j = 0; j < mStrings[i].size(); j++) {
            cout << mStrings[i][j] << ' ';
        }
        cout << endl;
    }

    outputFile << "Input string:" << endl;
    trianglePrint(triangle, outputFile);

    outputFile << endl << "After correction:" << endl;
    trianglePrint(mistakesCorrection(triangle), outputFile);

    outputFile.close();
    return 0;
}