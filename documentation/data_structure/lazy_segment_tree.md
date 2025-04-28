---
title: Lazy Segment Tree
documentation_of: data_structure/lazy_segment_tree.hpp
---
**ac-libraryをそのまま持ってきただけです**<br>
遅延評価セグメントツリーは、区間に対する更新と区間に対するクエリを高速に行うデータ構造です。

# 使い方
## コンストラクタ

```cpp
LazySegmentTree()
LazySegmentTree(int n)
explicit LazySegmentTree(const std::vector<S>& v)
```

### 説明

Lazy Segment Tree を構築します。
- `LazySegmentTree()`: 要素数 0 の Lazy Segment Tree を構築します。
- `LazySegmentTree(int n)`: 要素数 `n` の Lazy Segment Tree を構築します。初期値は単位元 `e()` で埋められます。
- `LazySegmentTree(const std::vector<S>& v)`: ベクトル `v` の要素で Lazy Segment Tree を構築します。

- `n`: 要素数。
- `v`: 初期値となる要素のベクトル。

### 計算量

$O(N)$ または $O(|v|)$

## set

```cpp
void set(int p, S x)
```

### 説明

位置 `p` の要素を `x` に更新します。

- `p`: 更新する要素のインデックス (0-indexed)。
- `x`: 更新後の値。

### 制約

$0 \le p < n$

### 計算量

$O(\log N)$

## operator[]

```cpp
S operator[](int p)
```

### 説明

位置 `p` の要素の値を取得します。

- `p`: 取得する要素のインデックス (0-indexed)。
- 戻り値: 位置 `p` の要素の値。

### 制約

$0 \le p < n$

### 計算量

$O(\log N)$

## operator()

```cpp
S operator()(int l, int r)
```

### 説明

区間 $[l, r)$ の要素に対する集約結果を取得します。

- `l`: 区間の開始インデックス (0-indexed, 含む)。
- `r`: 区間の終了インデックス (0-indexed, 含まない)。
- 戻り値: 区間 $[l, r)$ の要素に対する集約結果。

### 制約

$0 \le l \le r \le n$

### 計算量

$O(\log N)$

## all_prod

```cpp
S all_prod()
```

### 説明

区間 $[0, n)$ の要素に対する集約結果を取得します。

- 戻り値: 区間 $[0, n)$ の要素に対する集約結果。

### 計算量

$O(1)$

## apply

```cpp
void apply(int p, F f)
void apply(int l, int r, F f)
```

### 説明

- `apply(int p, F f)`: 位置 `p` の要素に作用素 `f` を適用します。
- `apply(int l, int r, F f)`: 区間 $[l, r)$ の各要素に作用素 `f` を適用します。

- `p`: 作用素を適用する要素のインデックス (0-indexed)。
- `l`: 作用素を適用する区間の開始インデックス (0-indexed, 含む)。
- `r`: 作用素を適用する区間の終了インデックス (0-indexed, 含まない)。
- `f`: 適用する作用素。

### 制約

- `apply(int p, F f)`: $0 \le p < n$
- `apply(int l, int r, F f)`: $0 \le l \le r \le n$

### 計算量

$O(\log N)$

## max_right

```cpp
int max_right(int l, auto g)
```

### 説明

区間 $[l, r)$ において、左端 `l` から始めて条件 `g` を満たす最大の `r` を二分探索で求めます。つまり、$g(\text{op}(a_l, a_{l+1}, \dots, a_{r-1}))$ が真となる最大の `r` を返します。

- `l`: 探索を開始する左端のインデックス (0-indexed)。
- `g`: 条件を表す関数オブジェクト。引数として集約結果を取り、bool を返します。`g(e())` は常に真である必要があります。
- 戻り値: 条件を満たす最大の `r`。

### 制約

$0 \le l \le n$

### 計算量

$O(\log N)$

## min_left

```cpp
int min_left(int r, auto g)
```

### 説明

区間 $[l, r)$ において、右端 `r` から始めて条件 `g` を満たす最小の `l` を二分探索で求めます。つまり、$g(\text{op}(a_l, a_{l+1}, \dots, a_{r-1}))$ が真となる最小の `l` を返します。

- `r`: 探索を終了する右端のインデックス (0-indexed)。
- `g`: 条件を表す関数オブジェクト。引数として集約結果を取り、bool を返します。`g(e())` は常に真である必要があります。
- 戻り値: 条件を満たす最小の `l`。

### 制約

$0 \le r \le n$

### 計算量

$O(\log N)$
