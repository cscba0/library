---
title: WeightedUnionfind
documentation_of: data_structure/weighted_unionfind.hpp
---
`WeightedUnionfind<T>` は、要素を互いに素な集合に分割し、さらに同じ集合に属する要素間の相対的な重み（差分）を管理するデータ構造です。例えば、$b$ は $a$ より重みが $W$ だけ大きい、すなわち $b - a = W$ という関係を表現できます。

## コンストラクタ

```cpp
WeightedUnionfind(int n)
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

## テンプレートパラメータ
## 計算量

- コンストラクタ: $O(N)$
- `merge`, `same`, `weight`, `leader`, `size`: アッカーマン関数の逆関数に比例する償却定数時間（ほぼ $O(\alpha(N))$）です。
```
