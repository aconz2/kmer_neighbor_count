#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string canonical(const string& seq) {
    string out = "";
    for (unsigned int i = 0; i < seq.length(); ++i) {
        switch (seq[i]) {
        case 'A': out += 'T'; break;
        case 'T': out += 'A'; break;
        case 'C': out += 'G'; break;
        case 'G': out += 'C'; break;
        default: cerr << "ERROR in canonical" << endl; exit(1);
        }
    }
    return seq < out ? seq : out;
}

uint64_t kmerint(const string& seq) {
    uint64_t out = 0;
    for (unsigned int i = 0; i < seq.length(); ++i) {
        out <<= 2;
        switch (seq[i]) {
        case 'A': out |= 0; break;
        case 'C': out |= 1; break;
        case 'G': out |= 2; break;
        case 'T': out |= 3; break;
        default: cerr << "ERROR in kmerint" << endl; exit(1);
        }
    }
    return out;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "Required args: <infile> <kmer length (<= 32)>" << endl;
        exit(1);
    }

    unsigned int k = stoi(argv[2]);
    if (k > 32) {
        cerr << "kmer length must be <= 32" << endl;
        exit(1);
    }
    ifstream ifs(argv[1]);
    if (!ifs) {
        cerr << "Cannot open \"" << argv[1] << "\"" << endl;
    }

    unordered_map<uint64_t, unordered_set<uint32_t> > map;
    string id;
    string seq;
    unsigned int seq_i = 0;
    while (ifs) {
        getline(ifs, id);
        if (id == "") break;
        getline(ifs, seq);
        for (unsigned int i = 0; i < seq.length() - k + 1; ++i) {
            string sub = canonical(seq.substr(i, k));
            uint64_t key = kmerint(sub);
            if (map.find(key) == map.end()) {
                map.emplace(key, unordered_set<uint32_t>());
            }
            map[key].insert(seq_i);
        }
        seq_i += 1;
    }

    ifs.close();
    ifs.open(argv[1]);
    while (ifs) {
        getline(ifs, id);
        getline(ifs, seq);
        if (id == "") break;
        cout << id << endl;
        for (unsigned int i = 0; i < seq.length() - k + 1; ++i) {
            if (i != 0) cout << "\t";
            string sub = canonical(seq.substr(i, k));
            uint64_t key = kmerint(sub);
            cout << map[key].size();
        }
        cout << endl;
    }
}
