# 📦 C++ STL — Interview Revision Notes

---

## 📌 Quick Navigation

1. [map vs unordered_map vs set vs unordered_set](#1-map-vs-unordered_map)
2. [vector](#2-vector)
3. [stack & queue](#3-stack--queue)
4. [priority_queue (Heap)](#4-priority_queue--heap)
5. [deque](#5-deque)
6. [pair & tuple](#6-pair--tuple)
7. [string tricks](#7-string-tricks)
8. [algorithm header essentials](#8-algorithm-header-essentials)
9. [When to use what — Master Cheat Sheet](#9-master-cheat-sheet)

---

## 1. map vs unordered_map

### `map` — Ordered (Red-Black Tree internally)

```cpp
map<string, int> mp;
mp["apple"] = 3;
mp["banana"] = 1;
// internally sorted: apple, banana

mp.count("apple");       // 1 if exists, 0 if not
mp.find("apple");        // returns iterator
mp.erase("apple");       // remove key
mp.lower_bound("b");     // iterator to first key >= "b"
mp.upper_bound("b");     // iterator to first key > "b"

for (auto& [key, val] : mp) { }  // iterates in sorted order
```

| Operation | Time |
|-----------|------|
| Insert    | O(log n) |
| Lookup    | O(log n) |
| Delete    | O(log n) |
| Iteration | Sorted order |

**Use when:** You need keys in **sorted order**, or need `lower_bound` / `upper_bound`.

---

### `unordered_map` — Hash Table

```cpp
unordered_map<string, int> ump;
ump["apple"] = 3;

ump.count("apple");   // 1 if exists, 0 if not
ump.find("apple");    // iterator
ump.erase("apple");
ump.size();

for (auto& [key, val] : ump) { }  // order NOT guaranteed
```

| Operation | Average | Worst Case |
|-----------|---------|------------|
| Insert    | O(1)    | O(n)       |
| Lookup    | O(1)    | O(n)       |
| Delete    | O(1)    | O(n)       |

> Worst case happens due to **hash collisions** — rare in practice.

**Use when:** You need **fast lookup** and don't care about order. Default choice for frequency counts, visited maps, caching.

---

### Head-to-Head Comparison

| Feature | `map` | `unordered_map` |
|---------|-------|-----------------|
| Internal structure | Red-Black Tree | Hash Table |
| Key order | Sorted ✅ | No order ❌ |
| Lookup speed | O(log n) | O(1) avg |
| `lower_bound` support | ✅ | ❌ |
| Memory | Less | More (hash buckets) |
| Custom key types | Easy (just `<`) | Need custom hash |
| Worst case | O(log n) | O(n) |

---

### `set` vs `unordered_set`

Same relationship as map/unordered_map — but stores **only keys**, no values.

```cpp
set<int> s;           // sorted, unique keys, O(log n)
unordered_set<int> us; // unsorted, unique keys, O(1) avg

s.insert(5);
s.count(5);   // 1 or 0
s.erase(5);
s.lower_bound(3);  // only available in set, not unordered_set

// Iterating set → sorted order
for (int x : s) cout << x;  // 1 2 3 4 5...
```

**Use `set`** when you need unique elements **in sorted order**.  
**Use `unordered_set`** when you just need fast exists/insert/delete checks.

---

### `multimap` and `multiset`

Allow **duplicate keys**. Same time complexity as map/set.

```cpp
multimap<int, string> mm;
mm.insert({1, "a"});
mm.insert({1, "b"});  // duplicate key allowed

multiset<int> ms;
ms.insert(3);
ms.insert(3);  // allowed
ms.count(3);   // returns 2
ms.erase(ms.find(3));  // removes only ONE occurrence
// ms.erase(3)          // removes ALL occurrences of 3 — be careful!
```

---

## 2. vector

The most commonly used container. Dynamic array under the hood.

```cpp
vector<int> v;
v.push_back(10);        // add to end → O(1) amortized
v.pop_back();           // remove from end → O(1)
v.size();               // number of elements
v.empty();              // true if size == 0
v.front();              // first element
v.back();               // last element
v[i];                   // random access → O(1)
v.insert(v.begin(), 5); // insert at front → O(n) ⚠️ slow
v.erase(v.begin());     // erase at front → O(n) ⚠️ slow

// Initialize
vector<int> v1(5, 0);         // [0, 0, 0, 0, 0]
vector<vector<int>> grid(3, vector<int>(4, -1));  // 3x4 grid of -1

// Sorting
sort(v.begin(), v.end());                          // ascending
sort(v.begin(), v.end(), greater<int>());          // descending
sort(v.begin(), v.end(), [](int a, int b){         // custom
    return a > b;
});

// Useful algorithms
reverse(v.begin(), v.end());
int mx = *max_element(v.begin(), v.end());
int mn = *min_element(v.begin(), v.end());
int sum = accumulate(v.begin(), v.end(), 0);
```

| Operation | Time |
|-----------|------|
| push_back | O(1) amortized |
| pop_back  | O(1) |
| Access v[i] | O(1) |
| insert/erase at middle | O(n) |
| search (unsorted) | O(n) |

**⚠️ Interview Trap:** Never insert/erase at the front of a vector in a loop — it's O(n) per operation. Use `deque` instead.

---

## 3. stack & queue

### `stack` — LIFO (Last In First Out)

```cpp
stack<int> st;
st.push(10);    // add on top
st.pop();       // remove top (no return value!)
st.top();       // peek at top
st.empty();     // true if empty
st.size();
```

**Common uses:** Balanced parentheses, DFS (iterative), monotonic stack, undo operations.

---

### `queue` — FIFO (First In First Out)

```cpp
queue<int> q;
q.push(10);    // add to back
q.pop();       // remove from front (no return value!)
q.front();     // peek at front
q.back();      // peek at back
q.empty();
q.size();
```

**Common uses:** BFS, level-order traversal, task scheduling.

---

### Monotonic Stack Pattern (Very Common in Interviews!)

A stack that maintains elements in **strictly increasing or decreasing order**.

```cpp
// Next Greater Element pattern
vector<int> nextGreater(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> st;  // stores indices
    for (int i = 0; i < n; i++) {
        while (!st.empty() && nums[st.top()] < nums[i]) {
            result[st.top()] = nums[i];
            st.pop();
        }
        st.push(i);
    }
    return result;
}
```

---

## 4. priority_queue — Heap

A **max-heap** by default (largest element at top).

```cpp
// MAX-HEAP (default)
priority_queue<int> pq;
pq.push(5);
pq.push(2);
pq.push(8);
pq.top();   // 8 (largest)
pq.pop();   // removes 8
pq.size();
pq.empty();

// MIN-HEAP
priority_queue<int, vector<int>, greater<int>> minPQ;
minPQ.push(5);
minPQ.top();  // smallest element

// Custom comparator (e.g., sort pairs by second value ascending)
auto cmp = [](pair<int,int> a, pair<int,int> b) {
    return a.second > b.second;  // min-heap by second
};
priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> customPQ(cmp);
```

| Operation | Time |
|-----------|------|
| push      | O(log n) |
| pop       | O(log n) |
| top       | O(1) |

**Common uses:** Dijkstra's algorithm, K largest/smallest elements, merge K sorted lists, task scheduling.

**⚠️ Interview Trap:** `priority_queue` does NOT support random access or iteration. If you need those, use a `multiset` instead.

---

## 5. deque

Double-ended queue. Supports O(1) insert/delete at **both** front and back.

```cpp
deque<int> dq;
dq.push_back(10);    // add to back
dq.push_front(5);   // add to front → O(1) ✅
dq.pop_back();      // remove from back
dq.pop_front();     // remove from front → O(1) ✅
dq.front();
dq.back();
dq[i];              // random access → O(1)
```

| Operation | Time |
|-----------|------|
| push/pop front | O(1) |
| push/pop back | O(1) |
| Random access | O(1) |
| Insert middle | O(n) |

**Common uses:** Sliding window maximum (monotonic deque), BFS when you need priority at both ends.

### Sliding Window Maximum Pattern

```cpp
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;  // stores indices, front = max index
    vector<int> result;
    for (int i = 0; i < (int)nums.size(); i++) {
        // remove elements outside window
        if (!dq.empty() && dq.front() == i - k) dq.pop_front();
        // remove smaller elements from back
        while (!dq.empty() && nums[dq.back()] < nums[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1) result.push_back(nums[dq.front()]);
    }
    return result;
}
```

---

## 6. pair & tuple

### `pair`

```cpp
pair<int, string> p = {1, "hello"};
p.first;   // 1
p.second;  // "hello"

// make_pair
auto p2 = make_pair(3, 4);

// Sorting vector of pairs → sorts by first, then second by default
vector<pair<int,int>> v = {{3,1},{1,2},{1,1}};
sort(v.begin(), v.end());  // → {1,1}, {1,2}, {3,1}

// Custom sort by second element
sort(v.begin(), v.end(), [](auto& a, auto& b){
    return a.second < b.second;
});
```

---

### `tuple`

```cpp
tuple<int, string, double> t = {1, "hi", 3.14};
get<0>(t);  // 1
get<1>(t);  // "hi"
get<2>(t);  // 3.14

auto t2 = make_tuple(1, "hi", 3.14);

// Structured bindings (C++17)
auto [x, y, z] = t;
```

---

## 7. String Tricks

```cpp
string s = "hello";
s.length();            // or s.size()
s.substr(1, 3);        // "ell" → substr(start, length)
s.find("ll");          // index 2, or string::npos if not found
s.find('l');           // first occurrence of char
s.rfind('l');          // last occurrence
s.replace(1, 2, "xy"); // replace 2 chars at index 1 with "xy"
s.erase(1, 2);         // erase 2 chars at index 1
s += " world";         // concatenation
s.empty();
s[0];                  // char access

// Convert
int n = stoi("123");          // string to int
long long ll = stoll("123");  // string to long long
string str = to_string(123);  // int to string

// Check character type
isalpha('a');   // true
isdigit('3');   // true
isalnum('a');   // true
isupper('A');   // true
islower('a');   // true
toupper('a');   // 'A'
tolower('A');   // 'a'

// Split string by delimiter (no built-in, use stringstream)
#include <sstream>
stringstream ss("hello world foo");
string token;
while (ss >> token) {
    cout << token << "\n";  // prints hello, world, foo
}
```

**⚠️ Interview Trap:** `substr` takes **(start, length)**, not (start, end). Very common mistake!

---

## 8. Algorithm Header Essentials

```cpp
#include <algorithm>

// Sorting
sort(v.begin(), v.end());
stable_sort(v.begin(), v.end());  // preserves order of equal elements

// Binary Search (array must be sorted first!)
binary_search(v.begin(), v.end(), 5);      // true/false
lower_bound(v.begin(), v.end(), 5);        // iterator to first >= 5
upper_bound(v.begin(), v.end(), 5);        // iterator to first > 5
// Convert iterator to index:
int idx = lower_bound(v.begin(), v.end(), 5) - v.begin();

// Min / Max
min(3, 5);          // 3
max(3, 5);          // 5
min({3, 1, 5, 2});  // 1 (initializer list)
*min_element(v.begin(), v.end());
*max_element(v.begin(), v.end());

// Useful transforms
reverse(v.begin(), v.end());
rotate(v.begin(), v.begin() + k, v.end());  // rotate left by k
fill(v.begin(), v.end(), 0);                // fill with 0
count(v.begin(), v.end(), 5);               // count occurrences of 5
accumulate(v.begin(), v.end(), 0);          // sum (needs <numeric>)

// Permutations
next_permutation(v.begin(), v.end());  // modifies v to next permutation
prev_permutation(v.begin(), v.end());

// Remove duplicates (sort first!)
sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());
```

---

## 9. Master Cheat Sheet

### Which Container to Use?

| Need | Use |
|------|-----|
| Fast key→value lookup | `unordered_map` |
| Sorted key→value, range queries | `map` |
| Check if element exists (fast) | `unordered_set` |
| Unique elements in sorted order | `set` |
| Duplicate elements, sorted | `multiset` |
| Dynamic array, random access | `vector` |
| LIFO / DFS iterative | `stack` |
| FIFO / BFS | `queue` |
| Max/min element fast | `priority_queue` |
| Insert/delete at both ends | `deque` |
| Sliding window max/min | `deque` (monotonic) |
| K largest elements | `priority_queue` (min-heap of size K) |
| Frequency count | `unordered_map<T, int>` |

---

### Complexity Quick Reference

| Container | Insert | Lookup | Delete | Notes |
|-----------|--------|--------|--------|-------|
| `vector` | O(1)* | O(1) | O(n) | *amortized at back |
| `map` | O(log n) | O(log n) | O(log n) | sorted |
| `unordered_map` | O(1) avg | O(1) avg | O(1) avg | unsorted |
| `set` | O(log n) | O(log n) | O(log n) | sorted, unique |
| `unordered_set` | O(1) avg | O(1) avg | O(1) avg | unsorted, unique |
| `stack` | O(1) | O(1) top only | O(1) | LIFO |
| `queue` | O(1) | O(1) front/back | O(1) | FIFO |
| `priority_queue` | O(log n) | O(1) top | O(log n) | max by default |
| `deque` | O(1) both ends | O(1) | O(1) both ends | |

---

### Common Interview Patterns → Container Mapping

| Problem Pattern | Container |
|-----------------|-----------|
| Two Sum / Frequency Count | `unordered_map` |
| Anagram check | `unordered_map` or `array[26]` |
| Sliding window | `unordered_map` + two pointers |
| Top K frequent elements | `unordered_map` + `priority_queue` |
| Next greater element | `stack` (monotonic) |
| Sliding window max | `deque` (monotonic) |
| BFS / Level order | `queue` |
| Dijkstra shortest path | `priority_queue` (min-heap) |
| LRU Cache | `unordered_map` + doubly linked list |
| Merge K sorted lists | `priority_queue` |
| Range sum / frequency | `map` with `lower_bound` |
| Unique sorted elements | `set` |

---

### Key Tricks to Remember

```cpp
// ✅ erase only ONE element from multiset (not all!)
ms.erase(ms.find(val));   // correct
ms.erase(val);            // ❌ removes ALL occurrences

// ✅ Check existence without inserting (unordered_map)
ump.count(key);           // safer than ump[key] which inserts 0

// ✅ lower_bound on vector → index
int idx = lower_bound(v.begin(), v.end(), target) - v.begin();

// ✅ substr: (start, LENGTH) not (start, end)
s.substr(2, 3);  // 3 chars starting at index 2

// ✅ Min-heap priority_queue
priority_queue<int, vector<int>, greater<int>> minpq;

// ✅ Structured bindings for map iteration
for (auto& [key, val] : mp) { }

// ✅ Fast 2D vector initialization
vector<vector<int>> dp(m, vector<int>(n, 0));
```

---

*Happy Revising! 🚀*