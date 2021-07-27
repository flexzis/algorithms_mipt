#include <vector>
#include <string>
#include <iostream>

using std::vector, std::string;

class HashTable
{
    vector<string> table = vector<string>(8);
    vector<bool> deleted = vector<bool>(8, false);
    static const size_t a = 5;
    size_t element_count = 0;

    size_t hashHorner(const string& str, size_t M)
    {
        size_t hash = str[0] % M;
        for (size_t i = 1, strSize = str.size(); i < strSize; ++i)
            hash = (hash * a + str[i]) % M;
        return hash;
    }
    
    size_t hash(const string& str, const vector<string>& h_table)
    {
    size_t M = h_table.size();
    size_t hash = hashHorner(str, M);
        for (size_t i = 1; !h_table[hash].empty() and h_table[hash] != str; ++i)
            hash = (hash * a + i) % M;
        return hash;
    }
public:
    bool add(string& str)
    {
        size_t h = hash(str, table);

        if (!table[h].empty() and !deleted[h])
            return false;
        if (!table[h].empty() and deleted[h])
            return !(deleted[h] = true);

        size_t table_size = table.size();
        if ((element_count + 1ULL) * 4ULL >= 3ULL * table_size)
        {
            size_t new_size = table_size << 2;
            vector<string> new_table(new_size);
            for (size_t i = 0; i < table_size; ++i)
            {
                if (!table[i].empty() and !deleted[i])
                    new_table[hash(table[i], new_table)] = std::move(table[i]);
            }
            table = std::move(new_table);
            deleted = vector<bool>(new_size, false);
            element_count = 0;
            h = hash(str, table); 
        }
        table[h] = std::move(str);
        deleted[h] = false;
        ++element_count;
        return true;
    }

    bool remove(const string& str)
    {
        size_t h = hash(str, table);
        if (!table[h].empty() and !deleted[h])
        {
            deleted[h] = true;
            return true;
        }
        return false;
    }

    bool find(const string& str)
    {
    size_t h = hash(str, table);
        return !table[h].empty() and !deleted[h];
    }
};

int main()
{
    HashTable HT;
    char cmd;
    string s;
    bool res = false;
    while (std::cin >> cmd >> s)
    {
        switch(cmd)
        {
            case '+':
                res = HT.add(s);
                break;
            case '-':
                res = HT.remove(s);
                break;
            case '?':
                res = HT.find(s);
                break;
        }
        std::cout << (res ? "OK" : "FAIL") << std::endl; 
    }
}



