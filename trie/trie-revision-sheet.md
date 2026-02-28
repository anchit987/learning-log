# 🌳 Trie Data Structure — Complete Revision Notes

---

## 📌 1. Introduction

A **Trie** (pronounced *"try"*) is a tree-like data structure used to store strings where each node represents a **single character**. It is also called a **Prefix Tree** or **Digital Tree**.

### Key Properties
- Every node (except root) stores **one character**.
- The **root** is empty (represents an empty string).
- Each path from root to a marked node represents a **stored word**.
- Nodes can share **common prefixes**, saving space.

### Why Use a Trie?
| Operation | Hash Map | Sorted Array | Trie |
|-----------|----------|--------------|------|
| Insert    | O(L)     | O(L log n)   | O(L) |
| Search    | O(L)     | O(L log n)   | O(L) |
| Prefix Search | ❌ O(n·L) | O(L log n) | ✅ O(L) |

> `L` = length of the word, `n` = number of words

**Tries shine when you need prefix-based operations.**

---

## ⚙️ 2. Structure of a Trie Node

```cpp
struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        fill(children, children + 26, nullptr);  // init all to null
    }
};
```

**Why `array[26]`?**
- Index a character as `ch - 'a'` → `'a'=0, 'b'=1, ..., 'z'=25`
- Direct index access = **O(1) guaranteed**, no hashing overhead
- More cache-friendly and memory-efficient than `unordered_map`
- Perfect for 95% of interview problems that specify **lowercase English letters**

Each node has:
- **`children[26]`**: fixed array of 26 pointers, one per letter. `nullptr` means that child doesn't exist.
- **`isEndOfWord`**: a flag to indicate a complete word ends here.

---

## 🔧 3. Core Operations

### 3.1 Insert
Walk character by character using `ch - 'a'` as index. If a node doesn't exist, create it. Mark `isEndOfWord = true` at the last character.

```cpp
void insert(const string& word) {
    TrieNode* node = root;
    for (char ch : word) {
        int idx = ch - 'a';
        if (!node->children[idx])
            node->children[idx] = new TrieNode();
        node = node->children[idx];
    }
    node->isEndOfWord = true;
}
```
**Time:** O(L) | **Space:** O(L)

---

### 3.2 Search
Walk through each character using index. If any slot is `nullptr` → word doesn't exist. At the end, check `isEndOfWord`.

```cpp
bool search(const string& word) {
    TrieNode* node = root;
    for (char ch : word) {
        int idx = ch - 'a';
        if (!node->children[idx]) return false;
        node = node->children[idx];
    }
    return node->isEndOfWord;
}
```
**Time:** O(L)

---

### 3.3 Starts With (Prefix Search)
Same as search but **don't** check `isEndOfWord` at the end.

```cpp
bool startsWith(const string& prefix) {
    TrieNode* node = root;
    for (char ch : prefix) {
        int idx = ch - 'a';
        if (!node->children[idx]) return false;
        node = node->children[idx];
    }
    return true;
}
```
**Time:** O(L)

---

### 3.4 Delete
Three cases:
1. Word doesn't exist → do nothing.
2. Word is a **prefix** of another word → only unmark `isEndOfWord`.
3. Word has **no shared prefix** → delete nodes bottom-up.

```cpp
// Helper: returns true if the node is now safe to delete
bool deleteHelper(TrieNode* node, const string& word, int depth) {
    if (depth == (int)word.size()) {
        if (!node->isEndOfWord) return false;  // word not found
        node->isEndOfWord = false;
        // safe to delete only if this node has no other children
        for (int i = 0; i < 26; i++)
            if (node->children[i]) return false;
        return true;
    }
    int idx = word[depth] - 'a';
    if (!node->children[idx]) return false;

    bool shouldDelete = deleteHelper(node->children[idx], word, depth + 1);
    if (shouldDelete) {
        delete node->children[idx];
        node->children[idx] = nullptr;
        // delete current node too if it has no other children and isn't end of another word
        if (!node->isEndOfWord) {
            for (int i = 0; i < 26; i++)
                if (node->children[i]) return false;
            return true;
        }
    }
    return false;
}

void deleteWord(const string& word) {
    deleteHelper(root, word, 0);
}
```
**Time:** O(L)

---

## 🖼️ 4. Visual Example

Let's insert: `["cat", "car", "card", "care", "bat"]`

```
root
├── [2] c
│        └── [0] a
│                  ├── [19] t ✅ (cat)
│                  └── [17] r ✅ (car)
│                             ├── [3] d ✅ (card)
│                             └── [4] e ✅ (care)
└── [1] b
         └── [0] a
                   └── [19] t ✅ (bat)
```
> Numbers in brackets = array index (`ch - 'a'`)

**Searching `"car"`** → root → `[2]c` → `[0]a` → `[17]r` → `isEndOfWord = true` ✅  
**Searching `"ca"`** → root → `[2]c` → `[0]a` → `isEndOfWord = false` ❌  
**Prefix `"car"`** → root → `[2]c` → `[0]a` → `[17]r` → not nullptr ✅ (matches car, card, care)

---

## 💡 5. Complete Trie Implementation (C++)

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        fill(children, children + 26, nullptr);
    }
};

class Trie {
private:
    TrieNode* root;

    void dfs(TrieNode* node, string& current, vector<string>& results) {
        if (node->isEndOfWord)
            results.push_back(current);
        for (int i = 0; i < 26; i++) {
            if (node->children[i]) {
                current.push_back('a' + i);
                dfs(node->children[i], current, results);
                current.pop_back();
            }
        }
    }

    bool deleteHelper(TrieNode* node, const string& word, int depth) {
        if (depth == (int)word.size()) {
            if (!node->isEndOfWord) return false;
            node->isEndOfWord = false;
            for (int i = 0; i < 26; i++)
                if (node->children[i]) return false;
            return true;
        }
        int idx = word[depth] - 'a';
        if (!node->children[idx]) return false;
        bool shouldDelete = deleteHelper(node->children[idx], word, depth + 1);
        if (shouldDelete) {
            delete node->children[idx];
            node->children[idx] = nullptr;
            if (!node->isEndOfWord) {
                for (int i = 0; i < 26; i++)
                    if (node->children[i]) return false;
                return true;
            }
        }
        return false;
    }

public:
    Trie() { root = new TrieNode(); }

    void insert(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (!node->children[idx])
                node->children[idx] = new TrieNode();
            node = node->children[idx];
        }
        node->isEndOfWord = true;
    }

    bool search(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (!node->children[idx]) return false;
            node = node->children[idx];
        }
        return node->isEndOfWord;
    }

    bool startsWith(const string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            int idx = ch - 'a';
            if (!node->children[idx]) return false;
            node = node->children[idx];
        }
        return true;
    }

    // Returns all words that start with the given prefix
    vector<string> getWordsWithPrefix(const string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            int idx = ch - 'a';
            if (!node->children[idx]) return {};
            node = node->children[idx];
        }
        vector<string> results;
        string current = prefix;
        dfs(node, current, results);
        return results;
    }

    void deleteWord(const string& word) {
        deleteHelper(root, word, 0);
    }
};
```

---

## 📊 6. Complexity Summary

| Operation        | Time    | Space   |
|------------------|---------|---------|
| Insert           | O(L)    | O(L)    |
| Search           | O(L)    | O(1)    |
| Prefix Search    | O(L)    | O(1)    |
| Delete           | O(L)    | O(1)    |
| Space (overall)  | —       | O(N·L·26) |

> `N` = number of words, `L` = average word length  
> Each node allocates 26 pointers regardless of usage — trade-off for speed.

---

## 💾 7. Why Trie is Space-Inefficient

Trie is excellent **time-wise** (O(L) for everything), but pays a heavy **space price**. Here's why.

### The Core Problem — Every Node Pre-allocates 26 Pointers

Each `TrieNode` holds `children[26]` regardless of how many children it actually has. Most of those slots sit as wasted `nullptr`.

For just one word `"cat"`, you create 4 nodes (root → c → a → t):

```
root:  [nullptr x2, 'c'→..., nullptr x23]   ← 25 wasted
  c:   ['a'→..., nullptr x25]               ← 25 wasted
    a: [nullptr x19, 't'→..., nullptr x6]   ← 25 wasted
      t: [nullptr x26]                       ← 26 wasted  ← leaf!
```

3 characters stored, but **104 pointers allocated** — only 3 are used.

### The Math

On a 64-bit system, each pointer = **8 bytes**.

```
One TrieNode = 26 × 8 bytes = 208 bytes
             + 1 bool + padding ≈ 216 bytes total
```

For a dictionary of **100,000 words** averaging 7 chars each (~700,000 nodes):

```
700,000 nodes × 208 bytes ≈ 145 MB
```

A plain `vector<string>` of the same dictionary would use only a few MB.

### Sparse vs Dense — When It Hurts Most

```
Sparse Trie (worst case):       Dense Trie (best case):

  root                            root
   └── 'a'                         ├── 'a'
        └── 'p'                    ├── 'b'
             └── 'p'               ├── 'c'
                  └── 'l'          ├── ...  (all 26 used)
                       └── 'e'
                                   
Each node wastes 25/26 slots.    Each node wastes ~0 slots.
```

Tries are space-efficient only when words share **many common prefixes** and nodes are densely connected. For sparse or long-tail data, the waste is severe.

### How to Fix It

| Fix | How | Trade-off |
|-----|-----|-----------|
| `unordered_map` children | Only allocate children that exist | Slower lookup, more per-node overhead |
| **Compressed Trie (Radix Tree)** | Merge single-child chains into one edge | More complex to implement |
| **Ternary Search Tree** | Each node has only 3 children (left, mid, right) | Balanced space vs speed |

### Interview One-liner

> *"Trie gives O(L) time for all operations, but each node pre-allocates 26 pointers regardless of actual children, making overall space O(N·L·26) — which is expensive for sparse data."*

---

## 🌍 8. Real-World Applications


| Use Case | How Trie Helps |
|----------|----------------|
| 🔍 Autocomplete (Google Search) | Find all words with a given prefix |
| 🔤 Spell Checker | Quickly verify if a word exists |
| 📱 T9 Predictive Text | Map digit sequences to word suggestions |
| 🌐 IP Routing (Radix Trie) | Longest prefix matching for routing tables |
| 🧬 DNA Sequence Matching | Store and search biological sequences |
| 🎮 Word Games (Scrabble, Boggle) | Rapid dictionary lookups |

---

## 🎯 9. Interview Questions & Solutions

---

### Q1. Implement Trie (LeetCode #208) — Easy
**Problem:** Implement `insert`, `search`, and `startsWith`.  
**Solution:** Standard Trie implementation (see Section 5).  
**Key point:** `search` checks `isEndOfWord`; `startsWith` does NOT.

---

### Q2. Word Search II (LeetCode #212) — Hard
**Problem:** Find all words from a list that exist in a 2D board.  
**Approach:**
- Insert all words into a Trie.
- DFS on the board, traverse the Trie simultaneously.
- When `isEndOfWord = true`, add to result.
- **Optimization:** Remove found words from Trie to avoid duplicates.

```cpp
// Key insight: prune Trie during DFS for efficiency
if (node->isEndOfWord) {
    result.insert(currentWord);
    node->isEndOfWord = false;  // avoid re-adding
}
```

---

### Q3. Design Add and Search Words (LeetCode #211) — Medium
**Problem:** Support `.` as a wildcard (matches any character).  
**Approach:** When `.` is encountered, loop through **all 26 children**.

```cpp
bool dfs(TrieNode* node, const string& word, int i) {
    if (i == (int)word.size()) return node->isEndOfWord;
    char ch = word[i];
    if (ch == '.') {
        for (int j = 0; j < 26; j++)
            if (node->children[j] && dfs(node->children[j], word, i + 1))
                return true;
        return false;
    }
    int idx = ch - 'a';
    if (!node->children[idx]) return false;
    return dfs(node->children[idx], word, i + 1);
}

bool search(const string& word) {
    return dfs(root, word, 0);
}
```

---

### Q4. Longest Word in Dictionary (LeetCode #720) — Medium
**Problem:** Find the longest word that can be built one character at a time.  
**Approach:**
- Insert all words into Trie.
- DFS — only go deeper when `isEndOfWord = true` at each step.
- Track the longest valid path found.

---

### Q5. Replace Words (LeetCode #648) — Medium
**Problem:** Replace words in a sentence with their shortest root from a dictionary.  
**Approach:** Insert all roots. For each word, walk the Trie and stop at first `isEndOfWord`.

```cpp
string replaceWord(TrieNode* root, const string& word) {
    TrieNode* node = root;
    string prefix = "";
    for (char ch : word) {
        int idx = ch - 'a';
        if (!node->children[idx] || node->isEndOfWord)
            break;
        prefix += ch;
        node = node->children[idx];
    }
    return node->isEndOfWord ? prefix : word;
}
```

---

### Q6. Count Words With a Given Prefix (LeetCode #2185) — Easy
**Approach:** Use `startsWith` and count. Or add an integer `passCount` field to each TrieNode that increments on every insert pass-through.

---

### Q7. Maximum XOR of Two Numbers (LeetCode #421) — Medium
**Problem:** Find max XOR of any two numbers in an array.  
**Approach:** Build a **binary Trie** using `children[2]` (bit 0 and bit 1).

```cpp
struct BitTrieNode {
    BitTrieNode* children[2];
    BitTrieNode() { children[0] = children[1] = nullptr; }
};

// Insert num bit by bit from MSB to LSB
void insert(BitTrieNode* root, int num) {
    BitTrieNode* node = root;
    for (int bit = 31; bit >= 0; bit--) {
        int b = (num >> bit) & 1;
        if (!node->children[b])
            node->children[b] = new BitTrieNode();
        node = node->children[b];
    }
}

// Greedily pick opposite bit to maximize XOR
int maxXOR(BitTrieNode* root, int num) {
    BitTrieNode* node = root;
    int xorVal = 0;
    for (int bit = 31; bit >= 0; bit--) {
        int b = (num >> bit) & 1;
        int want = 1 - b;
        if (node->children[want]) {
            xorVal |= (1 << bit);
            node = node->children[want];
        } else {
            node = node->children[b];
        }
    }
    return xorVal;
}
```

---

## ⚠️ 10. Common Mistakes & Tips

| Mistake | Fix |
|--------|-----|
| Forgetting `isEndOfWord` | Always mark it after inserting the last char |
| `search` vs `startsWith` confusion | `search` needs `isEndOfWord = true`; `startsWith` doesn't |
| Forgetting to `fill()` children array | Always initialize all 26 pointers to `nullptr` in constructor |
| Not handling empty string | Check edge case: `insert("")`, `search("")` |
| Deleting prefix of another word | Only unmark `isEndOfWord`, don't delete the node |
| Memory leaks | Always `delete` nodes properly or use `unique_ptr<TrieNode>` |
| Using `array[26]` for non-lowercase input | Switch to `unordered_map` if input has digits, uppercase, or symbols |

---

## 🔑 11. Quick Cheat Sheet

```
Trie = Tree where each path = a string
Array[26] node → index with (ch - 'a')

Insert  → walk + create nodes → mark end       → O(L)
Search  → walk → check isEndOfWord             → O(L)
Prefix  → walk → not nullptr at end?           → O(L)
Delete  → walk → unmark/prune bottom-up        → O(L)

children[26] vs unordered_map:
  ✅ array[26]       → O(1) guaranteed, cache-friendly, simple
  ✅ unordered_map   → flexible for any character set
  ❌ map             → O(log 26) per step, avoid in Tries

Interview Rule:
  "lowercase letters" in problem → always use array[26]
  Mixed / unknown charset        → use unordered_map

Use Trie when:
  ✅ Prefix matching needed
  ✅ Autocomplete / dictionary lookups
  ✅ Multiple string searches on same dataset

Avoid Trie when:
  ❌ Only exact matches needed (use unordered_map)
  ❌ Memory is very tight (each node holds 26 pointers)
  ❌ Strings have huge/unknown character sets
```

---

*Happy Revising! 🚀*