#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

int main() {
    // 编译 data.cpp, std.cpp 和 force.cpp
    if (system("g++ data.cpp -o data.exe --std=c++11") != 0) {
        cerr << "Failed to compile data.cpp" << endl;
        return 1;
    }
    if (system("g++ std.cpp -o std.exe --std=c++11") != 0) {
        cerr << "Failed to compile std.cpp" << endl;
        return 1;
    }
    if (system("g++ force.cpp -o force.exe --std=c++11") != 0) {
        cerr << "Failed to compile force.cpp" << endl;
        return 1;
    }

    while (1) {
        // 生成数据并存储在 input.txt 中
        if (system("data.exe > input.txt") != 0) {
            cerr << "Failed to execute data.exe" << endl;
            return 1;
        }

        // 调用暴力代码并将结果存储在 fout.txt 中
        if (system("force.exe < input.txt > fout.txt") != 0) {
            cerr << "Failed to execute force.exe" << endl;
            return 1;
        }

        // 调用对比代码并将结果存储在 sout.txt 中
        if (system("std.exe < input.txt > sout.txt") != 0) {
            cerr << "Failed to execute std.exe" << endl;
            return 1;
        }

        // 比较两个文件的内容
        if (system("fc fout.txt sout.txt > diff.txt") == 0) {
            cout << "Accepted" << endl;
        } else {
            cout << "Wrong Answer" << endl;
            break;
        }
    }

    return 0;
}