// xref.cpp

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "split2.h"

using namespace std;

// �Է¿��� �� �ܾ ������ ��� ���� ã��.
map<string, vector<vector<int>> > xref(istream& in, vector<string> find_words(const string&) = split) {
	string line;
	int line_number = 0;
	map<string, vector<vector<int>> > ret;

	// ���� ���� ����.
	while (getline(in, line)) {
		++line_number;

		// �Է��� ���� �ܾ�� ����.
		vector<string> words = find_words(line);

		// ���� �࿡ ������ ��� �ܾ ����
		for (const auto& word : words)
			// ���� �� ��ȣ ��� ���Ϳ� �� ��ȣ�� �߰��Ͽ����ϴ�.
			ret[word].push_back({ line_number });
	}
	return ret;
}

int main() {
    cout << "Enter words (CTRL+Z to stop): " << endl;

    // �⺻ �μ��� split �Լ��� ����Ͽ� xref �Լ��� ȣ��
    map<string, vector<vector<int>>> ret = xref(cin);

    // ����� ���
    for (const auto& entry : ret) {
        // �ܾ ���
        cout << "\"" << entry.first << "\" occurs on line(s): ";

        // �̾ �ϳ� �̻��� �� ��ȣ�� ���
        for (const auto& lines : entry.second) {
            cout << lines[0]; // ù ��° �� ��ȣ ���
            // �߰� �� ��ȣ�� ������ ���
            for (size_t i = 1; i < lines.size(); ++i)
                cout << "," << lines[i];
        }

        // �� �ܾ ���� �ܾ�� �����Ϸ��� ���ο� ���� ���
        cout << endl;
    }
    return 0;
}