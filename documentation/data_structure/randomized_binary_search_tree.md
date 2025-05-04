---
title: Randomized Binary Search Tree
documentation_of: data_structure/randomized_binary_search_tree.hpp
---
ランダム化二分探索木（Randomized Binary Search Tree, RBST）は、暗黙的なキー（配列のようなインデックス）を用いて要素の挿入、削除、区間に対する操作（反転、集約値取得）を高速に行うことができるデータ構造です。遅延評価（Lazy Propagation）により区間反転をサポートしています。

テンプレートパラメータ:
- `T`: 要素の型。
- `op`: 二項演算 (モノイド)。`T op(T, T)` の形式である必要があります。
- `e`: モノイドの単位元を返す関数。`T e()` の形式である必要があります。

# 使い方

RandomizedBinarySearchTree はノードへのポインタ (`nptr`) を根として操作を行います。初期状態は `nullptr` です。

## insert

```cpp
void insert(nptr& ptr, int k, T v)
```

### 説明

根が `ptr` である木に対し、インデックス `k` の位置に値 `v` を挿入します。既存の要素は後方にシフトされます。

- `ptr`: 木の根への参照。操作後、根が変更される可能性があります。
- `k`: 挿入する位置のインデックス (0-indexed)。
- `v`: 挿入する値。

### 制約

$0 \le k \le N$ (Nは挿入前の要素数)

### 計算量

$O(\log N)$ (期待計算量)

## erase

```cpp
void erase(nptr& ptr, int k)
```

### 説明

根が `ptr` である木に対し、インデックス `k` の要素を削除します。後方の要素は前方にシフトされます。

- `ptr`: 木の根への参照。操作後、根が変更される可能性があります。
- `k`: 削除する要素のインデックス (0-indexed)。

### 制約

$0 \le k < N$ (Nは削除前の要素数)

### 計算量

$O(\log N)$ (期待計算量)

## reverse

```cpp
void reverse(nptr& ptr, int l, int r)
```

### 説明

根が `ptr` である木に対し、区間 `[l, r)` (半開区間) の要素の並びを反転します。

- `ptr`: 木の根への参照。操作後、根が変更される可能性があります。
- `l`: 反転する区間の開始インデックス (0-indexed)。
- `r`: 反転する区間の終了インデックス (0-indexed)。

### 制約

$0 \le l \le r \le N$ (Nは要素数)

### 計算量

$O(\log N)$ (期待計算量)

## operator()

```cpp
T operator()(nptr& ptr, int l, int r)
```

### 説明

根が `ptr` である木に対し、区間 `[l, r)` (半開区間) の要素に対する二項演算 `op` の結果を返します。

- `ptr`: 木の根への参照。操作後、根が変更される可能性があります。
- `l`: 集約値を取得する区間の開始インデックス (0-indexed)。
- `r`: 集約値を取得する区間の終了インデックス (0-indexed)。
- 戻り値: 区間 `[l, r)` の要素に対する `op` の結果。区間が空の場合は単位元 `e()` を返します。

### 制約

$0 \le l \le r \le N$ (Nは要素数)

### 計算量

$O(\log N)$ (期待計算量)

