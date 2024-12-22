# Othello game

## Environment

* Windows10
* Visual Studio Code 1.56.0
* Python 3.9.13
* numpy 1.16.5
* wx 4.1.0

## DIRECTORY

**bitboard**
オセロのアルゴリズムを定義

* `_test_othello.py`：bitboard のテストコード．
* `bitboard.cpp`：オセロの盤面操作に関する演算を定義．ボードを uint64_t で表現することで計算を高速化．
* `c2python.cpp`：C++ で記述されたスクリプトを python から読み込めるように変換する．
* `othello.cpp`：実際にオセロをプレイするための手続きを記述したスクリプト．

**display**
Python を用いたオセロ GUI の定義

* `color.py`：GUI に使用される色を定義するクラスを定義．
* `gui.py`：オセロゲームの状況を表示する GUI を記述し，MyFrame に対し GamePanel と UserPanel を委譲する．
* `menu.py`：GUI のメニューバーを定義するクラスを定義．

**mathing**
自動対戦システムおよびレーティングシステムを定義

* `elorating.cpp`：イロレーティングを C++ で記述．
* `elorating.py`：イロレーティングを python で記述．
* `matching.cpp`：自動で CPU の戦略同士を対戦させ，レートを計算する．
* `true_skill.py`：trueskill を用いてレート計算を行う．

**mathing**
対戦 CPU の戦略を定義

* `basestrategy.cpp`：戦略クラスをまとめるための抽象クラス．
* `maximize.cpp`：常に次の自分の石の数が最大化される手を打つ戦略．
* `minimize.cpp`：常に次の自分の石の数が最小化される手を打つ戦略．
* `minmax.cpp`：min-max法を用いて最善手の探索を行う戦略．
* `random.cpp`：常にランダムな合法手を打つ戦略．
* `strategy.cpp`：各種戦略を切り替えることのできる派生クラス．

`playgameonGUI.py`：python 環境においてゲームをプレイすることができるスクリプト．

## DEMO

dist/playgameonGUI.exeからゲームを実行可能．

## Author

* Author：Yuki Shimomura

## License

"Othello game" is under [MIT license](https://en.wikipedia.org/wiki/MIT_License).
