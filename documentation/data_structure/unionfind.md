---
title: Union Find<br>
documentation_of: data_structure/unionfind.hpp
---
互いに素な集合を管理します。

# 使い方
## コンストラクタ

```cpp
Unionfind(int n)
```

### 説明

`n` 個の要素を持つ Union-Find を構築します。最初は各要素がそれぞれ異なる集合に属しています。

- `n`: 要素数。

### 計算量

$O(N)$

## merge

```cpp
int merge(int a, int b)
```

### 説明

要素 `a` と要素 `b` が属する集合を併合します。`a` と `b` が既に同じ集合に属している場合は何も行いません。

- `a`: 要素のインデックス (0-indexed)。
- `b`: 要素のインデックス (0-indexed)。
- 戻り値: 併合後の集合の代表元のインデックス。

### 制約

$0 \le a < n$<br>
$0 \le b < n$

### 計算量

$O(\alpha(N))$
```cpp
bool same(int a, int b)
```

### 説明

要素 `a` と要素 `b` が同じ集合に属しているかを判定します。

- `a`: 要素のインデックス (0-indexed)。
- `b`: 要素のインデックス (0-indexed)。
- 戻り値: `a` と `b` が同じ集合に属していれば `true`、そうでなければ `false`。

### 制約

$0 \le a < n$<br>
$0 \le b < n$

### 計算量

$O(\alpha(N))$

## leader

```cpp
int leader(int a)
```

### 説明

要素 `a` が属する集合の代表元を返します。

- `a`: 要素のインデックス (0-indexed)。
- 戻り値: 要素 `a` が属する集合の代表元のインデックス。

### 制約

$0 \le a < n$

### 計算量

$O(\alpha(N))$

## size

```cpp
int size(int a)
```

### 説明

要素 `a` が属する集合の要素数を返します。

- `a`: 要素のインデックス (0-indexed)。
- 戻り値: 要素 `a` が属する集合のサイズ。

### 制約

$0 \le a < n$

### 計算量

$O(\alpha(N))$
