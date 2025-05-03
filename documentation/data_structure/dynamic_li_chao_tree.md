---
title: Dynamic Li Chao Tree
documentation_of: data_structure/dynamic_li_chao_tree.hpp
---
Li Chao Tree は、区間内の直線群に対する最小値（または最大値）クエリを高速に処理するためのデータ構造です。ここでは、動的にノードを作成するバージョンを提供します。

テンプレートパラメータ:
- `T`: 直線の係数および座標の型。
- `Left`: 管理する区間の左端 (inclusive)。
- `Right`: 管理する区間の右端 (exclusive)。
- `e`: 最小値（または最大値）の単位元を返す関数。`T e()` の形式である必要があります。最小値を求める場合は十分に大きな値を、最大値を求める場合は十分に小さな値を返します。

# 使い方
## コンストラクタ

```cpp
DynamicLiChaoTree()
```

### 説明

空の Dynamic Li Chao Tree を構築します。

### 計算量

$O(1)$

## add (直線追加)

```cpp
void add(T a, T b)
```

### 説明

管理する区間 `[Left, Right)` 全体に直線 $y = ax + b$ を追加します。

- `a`: 直線の傾き。
- `b`: 直線の切片。

### 計算量

$O(\log (Right - Left))$

```cpp
void add(T a, T b, T L, T R)
```

### 説明

区間 `[L, R)` に直線 $y = ax + b$ を追加します。

- `a`: 直線の傾き。
- `b`: 直線の切片。
- `L`: 直線を追加する区間の左端 (inclusive)。
- `R`: 直線を追加する区間の右端 (exclusive)。

### 制約

$Left \le L < R \le Right$

### 計算量

$O(\log^2 (Right - Left))$

## operator() (クエリ)

```cpp
T operator()(T x)
```

### 説明

座標 `x` における、追加された全ての直線の最小値（または最大値）を返します。

- `x`: クエリ座標。
- 戻り値: 座標 `x` における最小値（または最大値）。

### 制約

$Left \le x < Right$

### 計算量

$O(\log (Right - Left))$

