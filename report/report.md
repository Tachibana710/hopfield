## 実験１
パターンを記憶させ、想起性能を調べた。ノイズはすべて20%
* 【画像１】横軸が記憶させた画像数、縦軸が正答率
* 【画像２】横軸が記憶させた画像数、縦軸が正解との類似度（全試行に渡る平均）


## 実験2
ノイズと想起性能の関係を調べた。「正解との類似度」はこの実験において意味がないので、正答率についてのみ調べる。また、ピクセル値が反転した結果が得られたものについても、正解したということにする。
### 画像が2種類の時
* 横軸がノイズ頻度、縦軸が正答率
### 画像が4種類の時
* 横軸がノイズ頻度、縦軸が正答率


## 追加実験
完全にランダムに生成した初期値（＝ノイズ50%）を使うとき、どの程度の割合で正解データにたどり着けるのかを調べた。

![ランダム初期値の結果](./photo/random.png)

以下のグラフは記憶させるパターン数と正答率の関係である。2パターンまでは100%で正答できるが、そのあとは記憶させるパターン数が増えるにつれ正答率が減っていることがわかる。ここで、hopfieldのアルゴリズムを改善することで多数のパターンについてもより高い正答率を出せるようにしたい。