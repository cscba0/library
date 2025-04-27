---
title: Persistent Union Find<br>
documentation_of: data_structure/persistent_unionfind.hpp
---
更新前の状態を保持したまま集合の併合や判定ができる Union-Find です。各更新操作 (merge) は新しいバージョンの Union-Find を生成します。

# 使い方
## コンストラクタ

```cpp
PersistentUnionfind()
PersistentUnionfind(int n)
```

### 説明

指定された要素数を持つ Persistent Union-Find を構築します。最初は各要素がそれぞれ異なる集合に属しています。

- `n`: 要素数。

### 計算量

$O(N)$

## merge

```cpp
int merge(int a, int b, int t = -1)
```

### 説明

指定されたバージョン `t` の Union-Find において、要素 `a` と要素 `b` が属する集合を併合し、新しいバージョンを生成します。`a` と `b` が既に同じ集合に属している場合は何も行いません。`t` を指定しない場合、最新のバージョンに対して操作を行います。

- `a`: 要素のインデックス (0-indexed)。
- `b`: 要素のインデックス (0-indexed)。
- `t`: 操作を行う Union-Find のバージョンインデックス。-1 の場合は最新バージョン。
- 戻り値: 新しいバージョンのインデックス。

### 制約

$0 \le a < n$<br>
$0 \le b < n$<br>
$0 \le t < \text{バージョン数}$

### 計算量

$O(\log N)$

## same

```cpp
bool same(int a, int b, int t = -1)
```

### 説明

指定されたバージョン `t` の Union-Find において、要素 `a` と要素 `b` が同じ集合に属しているかを判定します。`t` を指定しない場合、最新のバージョンに対して操作を行います。

- `a`: 要素のインデックス (0-indexed)。
- `b`: 要素のインデックス (0-indexed)。
- `t`: 判定を行う Union-Find のバージョンインデックス。-1 の場合は最新バージョン。
- 戻り値: `a` と `b` が同じ集合に属していれば `true`、そうでなければ `false`。

### 制約

$0 \le a < n$<br>
$0 \le b < n$<br>
$0 \le t < \text{バージョン数}$

### 計算量

$O(\log N)$

## leader

```cpp
int leader(int a, int t = -1)
```

### 説明

指定されたバージョン `t` の Union-Find において、要素 `a` が属する集合の代表元を返します。`t` を指定しない場合、最新のバージョンに対して操作を行います。

- `a`: 要素のインデックス (0-indexed)。
- `t`: 代表元を取得する Union-Find のバージョンインデックス。-1 の場合は最新バージョン。
- 戻り値: 要素 `a` が属する集合の代表元のインデックス。

### 制約

$0 \le a < n$<br>
$0 \le t < \text{バージョン数}$

### 計算量

$O(\log N)$

## size

```cpp
int size(int a, int t = -1)
```

### 説明

指定されたバージョン `t` の Union-Find において、要素 `a` が属する集合の要素数を返します。`t` を指定しない場合、最新のバージョンに対して操作を行います。

- `a`: 要素のインデックス (0-indexed)。
- `t`: サイズを取得する Union-Find のバージョンインデックス。-1 の場合は最新バージョン。
- 戻り値: 要素 `a` が属する集合のサイズ。

### 制約

$0 \le a < n$<br>
$0 \le t < \text{バージョン数}$

### 計算量

$O(\log N)$
