// Implentation of [Aho Corasick algorithm](https://www.wikiwand.com/en/Aho%E2%80%93Corasick_algorithm).
// You can find example at [](https://leetcode.com/problems/stream-of-characters/discuss/316110/c%2B%2B-AhoCorasick-solution-(query-in-O(1)))
// Author: Hanzhou Tang
// Email: hanzhoutang@gmail.com
#include <vector>
#include <string>
#include <utility>
#include <queue>
#include <iostream>
using namespace std;
class StreamChecker
{
public:
    class Node
    {
    public:
        Node *children[26] = {};
        bool isLeaf = false;
        Node *fail = nullptr;
        Node(Node *f) : fail(f) {}
        void add(string str)
        {
            if (children[str[0] - 'a'] == nullptr)
            {
                children[str[0] - 'a'] = new Node(this);
            }
            if (str.size() == 1)
            {
                children[str[0] - 'a']->isLeaf = true;
                return;
            }
            children[str[0] - 'a']->add(str.substr(1));
        }
        ~Node()
        {
            for (int i = 0; i < 26; i++)
            {
                if (children[i])
                {
                    delete children[i];
                }
            }
        }
        Node *query(char letter, Node *root)
        {
            if (children[letter - 'a'])
            {
                return children[letter - 'a'];
            }
            if (fail->children[letter - 'a'])
            {
                return fail->children[letter - 'a'];
            }
            if (this == root)
            {
                return this;
            }
            return fail->query(letter, root);
        }
        Node *findFail(const char &letter, Node *&root, Node *&cur)
        {
            if (root == this)
            {
                return this;
            }
            if (fail->children[letter - 'a'] && fail->children[letter - 'a'] != cur)
            {
                return fail->children[letter - 'a'];
            }
            return fail->findFail(letter, root, cur);
        }
    };
    class Tire
    {
    public:
        Node *root;
        Node *cur;
        ~Tire()
        {
            delete root;
        }
        void init(vector<string> &words)
        {
            root = new Node(nullptr);
            root->fail = root;
            cur = root;
            for (auto &x : words)
            {
                add(x);
            }
            constructFail();
        }
        void add(string str)
        {
            root->add(str);
        }
        void constructFail()
        {
            queue<pair<char, Node *>> q;
            for (int i = 0; i < 26; i++)
            {
                if (root->children[i])
                {
                    q.push(make_pair(i + 'a', root->children[i]));
                }
            }
            while (q.size())
            {
                auto t = q.front();
                q.pop();
                auto letter = get<0>(t);
                auto node = get<1>(t);
                node->fail = node->findFail(letter, root, node);
                if (node->fail->isLeaf)
                {
                    node->isLeaf = true;
                }
                for (int i = 0; i < 26; i++)
                {
                    if (node->children[i])
                    {
                        q.push(make_pair('a' + i, node->children[i]));
                    }
                }
            }
        }
        bool query(char letter)
        {
            cur = cur->query(letter, root);
            return cur->isLeaf;
        }
    };
    Tire tire;
    StreamChecker(vector<string> words)
    {
        tire.init(words);
    }

    bool query(char letter)
    {
        return tire.query(letter);
    }
};

int main()
{
    StreamChecker streamChecker({"ab", "ba", "aaab", "abab", "baa"});
    cout << "query a: " << streamChecker.query('a') << endl;
    cout << "query a: " << streamChecker.query('a') << endl;
    cout << "query a: " << streamChecker.query('a') << endl;
    cout << "query a: " << streamChecker.query('a') << endl;
    cout << "query a: " << streamChecker.query('a') << endl;
    cout << "query b: " << streamChecker.query('b') << endl;
    cout << "query a: " << streamChecker.query('a') << endl;
    cout << "query b: " << streamChecker.query('b') << endl;
    cout << "query a: " << streamChecker.query('a') << endl;
    cout << "query b: " << streamChecker.query('b') << endl;
    cout << "query b: " << streamChecker.query('b') << endl;
    cout << "query b: " << streamChecker.query('b') << endl;
    cout << "query a: " << streamChecker.query('a') << endl;
    cout << "query b: " << streamChecker.query('b') << endl;
    cout << "query a: " << streamChecker.query('a') << endl;
    cout << "query b: " << streamChecker.query('b') << endl;
    cout << "query b: " << streamChecker.query('b') << endl;
    cout << "query b: " << streamChecker.query('b') << endl;
    cout << "query b: " << streamChecker.query('b') << endl;
    cout << "query a: " << streamChecker.query('a') << endl;
    cout << "query b: " << streamChecker.query('b') << endl;
    cout << "query a: " << streamChecker.query('a') << endl;
    cout << "query b: " << streamChecker.query('b') << endl;
    cout << "query a: " << streamChecker.query('a') << endl;
    cout << "query a: " << streamChecker.query('a') << endl;
    cout << "query a: " << streamChecker.query('a') << endl;
    cout << "query b: " << streamChecker.query('b') << endl;
    cout << "query a: " << streamChecker.query('a') << endl;
    cout << "query a: " << streamChecker.query('a') << endl;
    cout << "query a: " << streamChecker.query('a') << endl;
}
