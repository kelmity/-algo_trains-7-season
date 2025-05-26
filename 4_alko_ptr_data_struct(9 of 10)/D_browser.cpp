#include <list>
#include <string>
#include <iostream>

using namespace std;

struct CustomList {
private:
    list<string> data;

public:
    void add(const string& value) {
        //cout << value << endl;
        data.push_front(value);
    }

    string get(int index) {

        auto it = data.begin();
        advance(it, index);
        
        string value = *it;
         
        data.splice(data.begin(), data, it);
        
        return value;
    }

    int size() {
        return data.size();
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    CustomList apps;
    int n;
    cin >> n;
    cin.ignore();
    int m = 0;
    for (int i = 0; i < n; ++i) {
        string line;
        getline(cin, line);

        if (line.substr(0, 3) == "Run") {
            if (line.length() > 3) {
                string name = line.substr(4);
                apps.add(name);
                cout << name << endl;
                m += 1;
            } else {
                cout << endl;
            }
        } else {
            if (m != 0) {
                int k = 0;
                int pos = line.find('+');
                while (pos != string::npos) {
                    k++;
                    pos = line.find('+', pos + 1);
                }
                int cnt = k;
                
                int ind = (cnt % m);
                string active_app = apps.get(ind);
                cout << active_app << endl;
            }
            else {
                cout << endl;
            }
        }
    }

    return 0;
}