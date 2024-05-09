// xref.cpp

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "split2.h"

using namespace std;

// 입력에서 각 단어가 등장한 모든 행을 찾음.
map<string, vector<vector<int>> > xref(istream& in, vector<string> find_words(const string&) = split) {
	string line;
	int line_number = 0;
	map<string, vector<vector<int>> > ret;

	// 다음 행을 읽음.
	while (getline(in, line)) {
		++line_number;

		// 입력한 행을 단어로 나눔.
		vector<string> words = find_words(line);

		// 현재 행에 등장한 모든 단어를 저장
		for (const auto& word : words)
			// 단일 행 번호 대신 벡터에 행 번호를 추가하였습니다.
			ret[word].push_back({ line_number });
	}
	return ret;
}

int main() {
    cout << "Enter words (CTRL+Z to stop): " << endl;

    // 기본 인수인 split 함수를 사용하여 xref 함수를 호출
    map<string, vector<vector<int>>> ret = xref(cin);

    // 결과를 출력
    for (const auto& entry : ret) {
        // 단어를 출력
        cout << "\"" << entry.first << "\" occurs on line(s): ";

        // 이어서 하나 이상의 행 번호를 출력
        for (const auto& lines : entry.second) {
            cout << lines[0]; // 첫 번째 행 번호 출력
            // 추가 행 번호가 있으면 출력
            for (size_t i = 1; i < lines.size(); ++i)
                cout << "," << lines[i];
        }

        // 각 단어를 다음 단어와 구분하려고 새로운 행을 출력
        cout << endl;
    }
    return 0;
}