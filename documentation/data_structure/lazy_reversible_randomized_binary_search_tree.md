---
title: Lazy Reversible Randomized Binary Search Tree
documentation_of: data_structure/lazy_reversible_randomized_binary_search_tree.hpp
---
要素の挿入、削除、区間に対する更新（遅延伝播）、区間反転、区間集約を高速に行うことができるデータ構造です。ランダム化平衡二分探索木をベースに、遅延伝播と区間反転の機能を加えています。
俗にいう、遅延伝搬反転可能乱択平衡二分探索木です。

テンプレートパラメータ:
- `T`: 要素の型。
- `op`: 要素の二項演算 (モノイド)。`T op(T, T)` の形式である必要があります。
- `e`: モノイドの単位元を返す関数。`T e()` の形式である必要があります。
- `S`: 遅延伝播させる作用素の型。
- `mapping`: 要素に作用素を適用する関数。`T mapping(S, T)` の形式である必要があります。
- `composition`: 作用素の合成を行う関数。`S composition(S, S)` の形式である必要があります。
- `id`: 作用素の単位元を返す関数。`S id()` の形式である必要があります。

# 使い方

## insert

```cpp
void insert(nptr& ptr, int k, T v)
```

### 説明

現在の木 `ptr` のインデックス `k` の位置に値 `v` を挿入します。

- `ptr`: 操作対象の木のルートノードへのポインタ。
- `k`: 挿入する位置のインデックス (0-indexed)。
- `v`: 挿入する値。

### 計算量

$O(\log N)$ (期待値)

## erase

```cpp
void erase(nptr& ptr, int k)
```

### 説明

現在の木 `ptr` のインデックス `k` の要素を削除します。

- `ptr`: 操作対象の木のルートノードへのポインタ。
- `k`: 削除する要素のインデックス (0-indexed)。

### 計算量

$O(\log N)$ (期待値)

## reverse

```cpp
void reverse(nptr& ptr, int l, int r)
```

### 説明

現在の木 `ptr` の区間 `[l, r)` (半開区間) の要素の並びを反転させます。

- `ptr`: 操作対象の木のルートノードへのポインタ。
- `l`: 区間の開始インデックス (0-indexed)。
- `r`: 区間の終了インデックス (0-indexed)。

### 計算量

$O(\log N)$ (期待値)

## apply

```cpp
void apply(nptr& ptr, int l, int r, S x)
```

### 説明

現在の木 `ptr` の区間 `[l, r)` (半開区間) の各要素に作用素 `x` を適用します。

- `ptr`: 操作対象の木のルートノードへのポインタ。
- `l`: 区間の開始インデックス (0-indexed)。
- `r`: 区間の終了インデックス (0-indexed)。
- `x`: 適用する作用素。

### 計算量

$O(\log N)$ (期待値)

## operator()

```cpp
T operator()(nptr& ptr, int l, int r)
```

### 説明

現在の木 `ptr` の区間 `[l, r)` (半開区間) の要素に対する二項演算 `op` の結果を返します。

- `ptr`: 操作対象の木のルートノードへのポインタ。
- `l`: 区間の開始インデックス (0-indexed)。
- `r`: 区間の終了インデックス (0-indexed)。
- 戻り値: 区間 `[l, r)` の要素に対する `op` の結果。

### 計算量

$O(\log N)$ (期待値)

