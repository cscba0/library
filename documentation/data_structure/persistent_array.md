---
title: Persistent Array<br>
documentation_of: data_structure/persistent_array.hpp
---
更新前の状態を保持したまま要素の更新ができる配列です。各更新操作は新しいバージョンの配列を生成します。

# 使い方
## コンストラクタ

```cpp
PersistentArray(int n)
PersistentArray(int n, T x)
PersistentArray(std::vector<T> v)
```

### 説明

指定されたサイズまたは初期値を持つ PersistentArray を構築します。

- `n`: 配列のサイズ。
- `x`: 初期値として使用する要素。
- `v`: 初期値として使用する要素の `std::vector`。

### 計算量

$O(N \log N)$ または $O(N)$ (初期化方法による)

## set

```cpp
int set(int p, T v, int t = -1)
```

### 説明

指定された位置 `p` の要素を値 `v` で更新し、新しいバージョンの配列を生成します。`t` を指定しない場合、最新のバージョンに対して操作を行います。

- `p`: 更新する要素のインデックス (0-indexed)。
- `v`: 設定する値。
- `t`: 操作を行う配列のバージョンインデックス。-1 の場合は最新バージョン。
- 戻り値: 新しいバージョンのインデックス。

### 制約

$0 \le p < N$<br>
$0 \le t < \text{バージョン数}$

### 計算量

$O(\log N)$

## get

```cpp
T get(int p, int t = -1)
```

### 説明

指定されたバージョン `t` の配列の、位置 `p` にある要素の値を取得します。`t` を指定しない場合、最新のバージョンから取得します。

- `p`: 取得する要素のインデックス (0-indexed)。
- `t`: 値を取得する配列のバージョンインデックス。-1 の場合は最新バージョン。
- 戻り値: 指定された位置の要素の値。

### 制約

$0 \le p < N$<br>
$0 \le t < \text{バージョン数}$

### 計算量

$O(\log N)$
