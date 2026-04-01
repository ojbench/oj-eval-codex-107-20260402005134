// Problem 107 - 小恶魔的单循环链表
// Implements a singly circular linked list supporting operations 0..5.

#include <bits/stdc++.h>
using namespace std;

namespace LIST {
    struct NODE {
        int val;
        NODE* next;
    };

    NODE *head = nullptr;
    int len = 0;

    void init() {
        head = nullptr;
        len = 0;
    }

    // Move to node at index i (0-based). Assumes 0 <= i < len and len > 0
    NODE* move(int i) {
        if (len == 0) return nullptr;
        NODE* p = head;
        for (int k = 0; k < i; ++k) p = p->next;
        return p;
    }

    void insert(int i, int x) {
        NODE* node = new NODE{x, nullptr};
        if (len == 0) {
            node->next = node;
            head = node;
            len = 1;
            return;
        }
        if (i == 0) {
            // insert at head (before current head)
            NODE* tail = move(len - 1);
            node->next = head;
            tail->next = node;
            head = node;
            ++len;
            return;
        }
        if (i == len) {
            // append to tail
            NODE* tail = move(len - 1);
            node->next = head;
            tail->next = node;
            ++len;
            return;
        }
        // insert in middle before index i
        NODE* prev = move(i - 1);
        node->next = prev->next;
        prev->next = node;
        ++len;
    }

    void remove(int i) {
        if (len == 0) return; // invalid by problem guarantee
        if (len == 1) {
            // delete the only node
            delete head;
            head = nullptr;
            len = 0;
            return;
        }
        if (i == 0) {
            NODE* tail = move(len - 1);
            NODE* old = head;
            head = head->next;
            tail->next = head;
            delete old;
            --len;
            return;
        }
        NODE* prev = move(i - 1);
        NODE* cur = prev->next;
        prev->next = cur->next;
        delete cur;
        --len;
    }

    void remove_insert(int i) {
        if (len <= 1) return; // nothing changes
        if (i == len - 1) return; // already at tail
        if (i == 0) {
            NODE* tail = move(len - 1);
            NODE* old = head;
            head = head->next;
            tail->next = old;
            old->next = head;
            return; // len unchanged
        }
        // Capture tail before unlinking so traversal order doesn't change it
        NODE* tail = move(len - 1);
        NODE* prev = move(i - 1);
        NODE* cur = prev->next;
        prev->next = cur->next; // unlink from current position
        tail->next = cur;       // append to tail
        cur->next = head;
        // len unchanged
    }

    void get_length() {
        cout << len << '\n';
    }

    void query(int i) {
        if (i < 0 || i >= len || len == 0) {
            cout << -1 << '\n';
            return;
        }
        NODE* p = move(i);
        cout << p->val << '\n';
    }

    void get_max() {
        if (len == 0) {
            cout << -1 << '\n';
            return;
        }
        int mx = INT_MIN;
        NODE* p = head;
        for (int k = 0; k < len; ++k) {
            mx = max(mx, p->val);
            p = p->next;
        }
        cout << mx << '\n';
    }

    void clear() {
        if (len == 0) return;
        // delete all nodes safely in circular list
        NODE* p = head->next;
        for (int k = 1; k < len; ++k) {
            NODE* nxt = p->next;
            delete p;
            p = nxt;
        }
        delete head;
        head = nullptr;
        len = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    int op, x, p;
    LIST::init();
    for (int _ = 0; _ < n; ++_) {
        cin >> op;
        switch (op) {
            case 0:
                LIST::get_length();
                break;
            case 1:
                cin >> p >> x;
                LIST::insert(p, x);
                break;
            case 2:
                cin >> p;
                LIST::query(p);
                break;
            case 3:
                cin >> p;
                LIST::remove(p);
                break;
            case 4:
                cin >> p;
                LIST::remove_insert(p);
                break;
            case 5:
                LIST::get_max();
                break;
        }
    }
    LIST::clear();
    return 0;
}
