## 起動コマンド

```
mkdir build
cd build
cmake ..
make

./Capstone
```

## description

- cmakeにsdlはあるがsdl_imageはないのでセット
- includeはヘッダーファイルをセット うまく動かないから却下
- 初期ループは既存のやつを参考にする
- prac_sdlをそれぞれ要素の分解してheaderとかつくって同じように動くようにする
- 初回配置場所変更
- 敵をドットで出現
- 敵を移動
- 自機が小さいドットを発射できる
- 当たり判定導入
- スコア導入
- 当たり判定 http://lazyfoo.net/tutorials/SDL/27_collision_detection/index.php
