## 実験１
パターンを記憶させ、想起性能を調べた。ノイズはすべて20%
* 【画像１】横軸が記憶させた画像数、縦軸が正答率
![画像1](./photo/jikken1-1.png)
* 【画像２】横軸が記憶させた画像数、縦軸が正解との類似度（全試行に渡る平均）
![画像2](./photo/jikken1-2.png)

## 実験2
ノイズと想起性能の関係を調べた。「正解との類似度」はこの実験において意味がないので、正答率についてのみ調べる。また、ピクセル値が反転した結果が得られたものについても、正解したということにする。
### 画像が2種類の時
* 横軸がノイズ頻度、縦軸が正答率
![画像1](./photo/jikken2-1.png)
### 画像が4種類の時
* 横軸がノイズ頻度、縦軸が正答率
![画像1](./photo/jikken2-2.png)



## 追加実験
完全にランダムに生成した初期値（＝ノイズ50%）を使うとき、どの程度の割合で正解データにたどり着けるのかを調べた。

![ランダム初期値の結果](./photo/random.png)

以下のグラフは記憶させるパターン数と正答率の関係である。2パターンまでは100%で正答できるが、そのあとは記憶させるパターン数が増えるにつれ正答率が減っていることがわかる。ここで、hopfieldのアルゴリズムを改善することで多数のパターンについてもより高い正答率を出せるようにしたい。

そこで、以下のように、hopfieldの重みを三次元に拡張した。

```cpp
#pragma once
#include "pattern.hpp"
#include <tuple>

class Hopfield3D {
public:
    Hopfield3D(int size) : newrons{Pattern(size)}, N(size) {
        if (size <= 0) {
            throw std::invalid_argument("Size must be a positive integer.");
        }
        weights.resize(size, std::vector<std::vector<int>>(size, std::vector<int>(size, 0)));
    }

    void train(const Pattern& pattern) {
        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                for (int k = j+1; k < N; ++k) {
                    weights[i][j][k] += pattern.data[i] * pattern.data[j] * pattern.data[k];
                }
            }
        }
    }

    void recall(const int idx) {
        int sum = 0;
        for (int j = 0; j < N; ++j) {
            if (j == idx) continue;
            for (int k = j+1; k < N; ++k) {
                if (k == idx) continue;
                int idx1 = idx, idx2 = j, idx3 = k;
                if (idx1 > idx2) std::swap(idx1, idx2);
                if (idx1 > idx3) std::swap(idx1, idx3);
                if (idx2 > idx3) std::swap(idx2, idx3);
                sum += weights[idx1][idx2][idx3] * newrons.data[j] * newrons.data[k];
            }
        }
        if (sum == 0) return;
        newrons.data[idx] = (sum < 0 ? -1 : +1);
    }

    int energy() const {
        int energy = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                for (int k = j+1; k < N; ++k) {
                    energy -= weights[i][j][k] * newrons.data[i] * newrons.data[j] * newrons.data[k];
                }
            }
        }
        return energy;
    }

    void initNewrons(const Pattern& pattern) {
        for (int i = 0; i < N; ++i) {
            newrons.data[i] = pattern.data[i];
        }
    }

    Pattern newrons;
    std::vector<std::vector<std::vector<int>>> weights;
    int N;
};
```
変更点は以下の通り
* 通常のhopfieldでは２つのニューロン間のデータを掛け合わせたものを、パターンの数だけ足し合わせて重み行列を決定するが、重みを３次元テンソルとして用意し、３つのニューロン間のデータを掛け合わせたものを、パターンの数だけ足し合わせて決定する。
* 想起する際に、「∑(重み[想起するインデックス][i]) x (ニューロンの状態[i])」の値に応じて想起後の値を計算していたものを、「∑∑(重み[想起するインデックス][i][j]) x (ニューロンの状態[i]) x (ニューロンの状態[j])」を使うように変更
* エネルギーを、「∑∑(重み[i][j][k]) x (ニューロンの状態[i]) x (ニューロンの状態[j]) x (ニューロンの状態[k])」に変更

この変更によって、ランダム画像（ノイズ50%）に対しての正答率を調べると、以下の画像のようになった。

![ランダム初期値の結果](./photo/3d_500まで_scatter.png)

この結果を見ると、数個程度の少ないパターン数に対してはむしろ正答率は悪化しているが、10から20程度の、二次元hopfieldでほとんど正答できなかったパターン数に対してよく対応できていることがわかる。それ以降はだんだんと正答率は減少し、減少曲線は二次元のときに見られたものと似たような形になった。

数個程度の少ないパターン数に対して正答率が悪化している減少については、以下のように考えられる。

通常のhopfieldでは