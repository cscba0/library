---
title: UnionfindWithPotential
documentation_of: data_structure/unionfind_with_potential.hpp
---
集合内の要素間の重みの差を持ちながら、互いに素な集合を管理します。

## コンストラクタ

```cpp
UnionfindWithPotential(int n)
```

### 説明

`n` 個の要素を持つ Weighted Union-Find を構築します。最初は各要素がそれぞれ異なる集合に属しています。

- `n`: 要素数。

### 計算量

$O(N)$

## merge

```cpp
int merge(int a, int b, T W)
```

### 説明

要素 `a` と要素 `b` を同じ集合にマージし、$b - a = W$ という関係を確立します。
もし `a` と `b` が既に同じ集合に属している場合、この操作は $b - a = W$ という関係が既存の関係と矛盾しないかチェックする役割も果たしますが、この実装では矛盾の検出は行わず、単にマージ操作を行います。

- `a`: 要素のインデックス (0-indexed)。
- `b`: 要素のインデックス (0-indexed)。
- `W`: `b - a` の重み差分。
- 戻り値: マージ後の集合の代表元のインデックス。

### 制約

$0 \le a < n$ <br>
$0 \le b < n$

### 計算量

$O(\alpha(N))$

## same

```cpp
bool same(int a, int b)
```

### 説明

要素 `a` と要素 `b` が同じ集合に属しているかを判定します。

- `a`: 要素のインデックス (0-indexed)。
- `b`: 要素のインデックス (0-indexed)。
- 戻り値: `a` と `b` が同じ集合に属していれば `true`、そうでなければ `false`。

### 制約

$0 \le a < n$ <br>
$0 \le b < n$

### 計算量

$O(\alpha(N))$

## weight

```cpp
T weight(int a, int b)
```

### 説明

要素 `a` と要素 `b` が同じ集合に属している場合、$b - a$ の重み差分を返します。
異なる集合に属している場合の挙動は未定義です。

- `a`: 要素のインデックス (0-indexed)。
- `b`: 要素のインデックス (0-indexed)。
- 戻り値: `b - a` の重み差分。

### 制約

$0 \le a < n$ <br>
$0 \le b < n$

### 計算量

$O(\alpha(N))$

## leader

```cpp
std::pair<int, T> leader(int a)
```

### 説明

要素 `a` が属する集合の代表元と、`a` からその代表元までの重み差分を返します。
具体的には、代表元を $r$ とすると、戻り値は `{r, r - a}` となります。

- `a`: 要素のインデックス (0-indexed)。
- 戻り値: `{代表元のインデックス, 代表元 - a の重み差分}` のペア。

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
