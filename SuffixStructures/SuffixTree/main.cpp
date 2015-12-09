#include <iostream>
#include <vector>

// McCreight
class MCSuffixTreeBuilder {
private:
    class Node;
    std::vector<unsigned int> s;
    Node *superRoot;
    Node *root;

    Node *addSuffix(Node *head, int position);
    int runDFS(Node *vertex);
public:
    MCSuffixTreeBuilder();
    template <typename __Iterator>
    MCSuffixTreeBuilder(__Iterator begin, __Iterator end);
    ~MCSuffixTreeBuilder();

    int getAnswer();
};


int main() {
    //std::ios_base::sync_with_stdio(false);
    int k;
    std::string s;
    std::cin >> k;
    std::getline(std::cin, s);
    std::getline(std::cin, s);
    int n = s.size();
    for (int i = 0; i < k; ++i) {
        s.push_back(s[i]);
    }
    for (int i = 0; i < n; ++i) {
        MCSuffixTreeBuilder md(s.begin() + i, s.begin() + i + k);
        std::cout << md.getAnswer() << " ";
    }
    std::cout << "\n";
    return 0;
}

const int ALPHABET_SIZE = 27;

class MCSuffixTreeBuilder::Node {
public:
    std::vector<unsigned int> const &s;
    Node *parent;
    Node *suffix;
    int start, end, depth;
    std::vector<Node*> children;
    Node(std::vector<unsigned int> const &_s, Node *_parent, int _start, int _end, int _depth) :
            s(_s), parent(_parent), suffix(NULL), start(_start), end(_end),
            depth(_depth), children(ALPHABET_SIZE, NULL) {}
    ~Node() {
        for (int i = 0; i < (int)children.size(); ++i) {
            if (children[i] != NULL && dynamic_cast<Node*>(children[i])) {
                delete children[i];
            }
        }
    }

    Node *getSuffixLink() {
        if (suffix == NULL) {
            int length = getLength();
            int _start = start;
            suffix = parent->getSuffixLink();
            while (length > 0) {
                Node *current_vertex = suffix->children[s[_start]];
                if (current_vertex->getLength() > length) {
                    current_vertex->cut(length);
                    current_vertex = current_vertex->parent;
                }
                _start += std::max(1, current_vertex->getLength());
                length -= std::max(1, current_vertex->getLength());
                suffix = current_vertex;
            }
        }
        return suffix;
    }

    int getLength() const {
        return (end - start);
    }

    void cut(int prefix_length) {
        Node *prefix = new Node(s, parent, start, start + prefix_length, parent->depth + prefix_length);
        parent->children[s[start]] = prefix;
        prefix->children[s[start + prefix_length]] = this;
        start += prefix_length;
        parent = prefix;
    }
};

MCSuffixTreeBuilder::MCSuffixTreeBuilder() : s(), superRoot(NULL), root(NULL) {}

template <typename __Iterator>
MCSuffixTreeBuilder::MCSuffixTreeBuilder(__Iterator begin, __Iterator end) :
        superRoot(NULL), root(NULL) {
    s.clear();
    for (__Iterator it = begin; it != end; it++) {
        s.push_back(*it - 'a' + 1);
    }
    s.push_back(0);
}

MCSuffixTreeBuilder::~MCSuffixTreeBuilder() {
    if (root != NULL) {
        delete root;
    }
}

int MCSuffixTreeBuilder::getAnswer() {
    superRoot = new Node(s, NULL, 0, 0, 0);
    root = new Node(s, superRoot, 0, 0, 0);
    root->suffix = superRoot;
    for (char i = 0; i < (int)superRoot->children.size(); ++i) {
        superRoot->children[i] = root;
    }
    Node *head = root;
    for (int i = 0; i < (int)s.size(); ++i) {
        head = addSuffix(head, i);
    }
    return runDFS(root);
}

MCSuffixTreeBuilder::Node *MCSuffixTreeBuilder::addSuffix(Node *head, int position) {
    head = head->getSuffixLink();
    int i = head->depth + position;
    while (true) {
        if (head->children[s[i]] != NULL) {
            head = head->children[s[i]];
            int j = head->start;
            while (j < head->end && s[i] == s[j]) {
                i++;
                j++;
            }
            if (j != head->end) {
                head->cut(j - head->start);
                head = head->parent;
                break;
            }
        } else {
            break;
        }
    }
    head->children[s[i]] = new Node(s, head, i, s.size(), head->depth + s.size() - i);
    return head;
}

int MCSuffixTreeBuilder::runDFS(Node *vertex) {
    if (vertex == NULL) {
        return 0;
    }
    int ans = 0;
    for (int i = 0; i < (int)vertex->children.size(); ++i) {
        ans += runDFS(vertex->children[i]);
    }
    if (vertex->end == (int)s.size()) {
        ans--;
    }
    return (ans + vertex->getLength());
}