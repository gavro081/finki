
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

//TODO your code here
template<typename T>
vector<T> filter(T* array, int n, T ob){
    vector<T>solution;
    for (int i = 0; i < n; ++i) {
        if (array[i] < ob){
            solution.push_back(array[i]);
        }
    }
    return solution;
}

int main() {
    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        // Test case 1: Filter integers
        int intSize;
        cin >> intSize;
        int* intArray = new int[intSize];
        for (int i = 0; i < intSize; i++) {
            cin >> intArray[i];
        }
        int intThreshold;
        cin >> intThreshold;
        vector<int> intResult = filter(intArray, intSize, intThreshold);
        for (int val : intResult) {
            cout << val << " ";
        }
        cout << endl;

        // Clean up dynamically allocated memory
        delete[] intArray;
    } else if (testCase == 2) {
        // Test case 2: Filter strings
        int strSize;
        cin >> strSize;
        string* strArray = new string[strSize];
        for (int i = 0; i < strSize; i++) {
            cin >> strArray[i];
        }
        string strThreshold;
        cin >> strThreshold;
        vector<string> strResult = filter(strArray, strSize, strThreshold);
        for (string val : strResult) {
            cout << val << " ";
        }
        cout << endl;

        // Clean up dynamically allocated memory
        delete[] strArray;
    }

    return 0;
}
