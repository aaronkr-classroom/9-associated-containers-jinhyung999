#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <regex>

using namespace std;

// 정규 표현식을 사용하여 텍스트에서 URL을 추출합니다.
vector<string> find_urls(const string& text) {
    static const regex url_regex(R"(https?://\S+)");
    vector<string> urls;
    auto words_begin = sregex_iterator(text.begin(), text.end(), url_regex);
    auto words_end = sregex_iterator();
    for (auto it = words_begin; it != words_end; ++it) {
        urls.push_back(it->str());
    }
    return urls;
}

// 파일에서 각 URL이 등장한 모든 행을 찾습니다.
map<string, vector<int>> xref_urls(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Cannot open the file: " << filename << endl;
        exit(1);
    }

    string line;
    int line_number = 0;
    map<string, vector<int>> url_lines;

    while (getline(file, line)) {
        ++line_number;

        // 각 행에서 URL을 찾습니다.
        vector<string> urls = find_urls(line);

        // 각 URL이 등장한 행 번호를 저장합니다.
        for (const auto& url : urls)
            url_lines[url].push_back(line_number);
    }

    return url_lines;
}

int main() {
    string filename;
    cout << "Enter the file name: ";
    cin >> filename;

    map<string, vector<int>> url_lines = xref_urls(filename);

    // URL과 해당 URL이 등장한 모든 행을 출력합니다.
    for (const auto& entry : url_lines) {
        cout << "URL: " << entry.first << endl;
        cout << "Lines: ";
        for (const auto& line : entry.second)
            cout << line << " ";
        cout << endl;
    }

    return 0;
}