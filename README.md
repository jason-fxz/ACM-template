# ACM - template

**see [TODO](#todo)**

## Requirements

### Package minted

```python3
pip install Pygments
```

Add Python Scripts where Pygments installed to your system path (e.g. `AppData\Roaming\Python\Python38\Scripts` on Windows, and `pygmentize.exe` should exist)

Add `-shell-escape` to your TeX arguments.

### Fonts

Main font: [思源宋体 Source Han Serif SC](https://github.com/adobe-fonts/source-han-serif/tree/release/)

Cover font: [Gill Sans](tools/Gill-Sans-Font-Family.zip)


## TODO

在 `src/src/` 中编写： 代码片段 `xxx.cpp`，公式/文字 `xxx.tex` （就按照 markdown 写就行）

- Geometry 计算几何（二维/三维）：fxz
  - 基本公式
- DataStructure 数据结构（KDtree/LCT/…）：fxz
  - KDTree
  - LCT
  - seg-beats 吉司机线段树
  - fhq-treap
  - hashmap
  - lichao-tree 李超线段树
- String 字符串：hhd
- Graph 图论（tarjan/KM/霍尔定理）：zjb
  - 2-SAT
  - 极大团
  - 图论知识
  - 最小斯坦纳树
  - k短路
  - KM
  - tarjan
- NetworkFlow 网络流（算法+建模）：zjb
- DP 动态规划（斜率优化/WQS/四边形）：zjb
- Math / NumberTheory 数论：zjb
- Math / Combinatorics 组合数学（lucas/斯特林/….）：zjb
- Math / Polynomial 多项式：hhd
- Math / GameTheory 博弈论：zjb
- Miscellany 杂项：
