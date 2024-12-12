/**
 * Author: Johan Sannemo, pajenegod
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Range Minimum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in constant time.
 * Usage:
 *  RMQ rmq(values);
 *  rmq.query(inclusive, exclusive);
 * Time: $O(|V| \log |V| + Q)$
 * Status: stress-tested
 */
// #pragma once

// template<class T>
// struct RMQ {
// 	vector<vector<T>> jmp;
// 	RMQ(const vector<T>& V) : jmp(1, V) {
// 		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
// 			jmp.emplace_back(sz(V) - pw * 2 + 1);
// 			rep(j,0,sz(jmp[k]))
// 				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
// 		}
// 	}
// 	T query(int a, int b) {
// 		assert(a < b); // or return inf if a == b
// 		int dep = 31 - __builtin_clz(b - a);
// 		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
// 	}
// };
#pragma once

#include "../../content/data-structures/ImplicitSegTree.h"
#include "ImplicitSegTree.h"

class SparseSegtree {
  private:
    struct Node {
        int freq = 0;
        int lazy = 0;
        Node *left = nullptr;
        Node *right = nullptr;
    };
    Node *root = new Node;
    const int n;
    int comb(int a, int b) { return a + b; }
    void apply(Node *cur, int len, int val) {
        if (val == 1) {
            (cur->lazy) = val;
            (cur->freq) = len * val;
        }
    }
    void push_down(Node *cur, int l, int r) {
        if ((cur->left) == nullptr) {
            (cur->left) = new Node;
        }
        if ((cur->right) == nullptr) {
            (cur->right) = new Node;
        }
        int m = (l + r) / 2;
        apply(cur->left, m - l + 1, cur->lazy);
        apply(cur->right, r - m, cur->lazy);
    }
    void range_set(Node *cur, int l, int r, int ql, int qr, int val) {
        if (qr < l || ql > r) {
            return;
        }
        if (ql <= l && r <= qr) {
            apply(cur, r - l + 1, val);
        } else {
            push_down(cur, l, r);
            int m = (l + r) / 2;
            range_set(cur->left, l, m, ql, qr, val);
            range_set(cur->right, m + 1, r, ql, qr, val);
            (cur->freq) = comb((cur->left)->freq, (cur->right)->freq);
        }
    }
    int range_sum(Node *cur, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return cur->freq;
        }
        push_down(cur, l, r);
        int m = (l + r) / 2;
        return comb(range_sum(cur->left, l, m, ql, qr), range_sum(cur->right, m + 1, r, ql, qr));
    }

  public:
    SparseSegtree(int n) : n(n) {}
    void range_set(int ql, int qr, int val) { range_set(root, 0, n - 1, ql, qr, val); }
    int range_sum(int ql, int qr) { return range_sum(root, 0, n - 1, ql, qr); }
};
