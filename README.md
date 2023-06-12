# Bank Program
これは、大学1年の演習時に作った、Unix系システムでの端末制御ライブラリであるcursesを用いた疑似ATMシステムである。
同じディレクトリ下にある通帳ファイル（passbook.dat）を読み込んで操作を行う。
 
# DEMO
このプログラムでは以下の動作が行える。
* 預金
* 残高確認
* 出金
* 暗証番号変更
 
# Requirement
このプログラムを動かすには以下のライブラリが必須である。
* cureses
* gcc
 
# Installation
ライブラリのインストール方法
```bash
sudo apt install libncursesw5-dev gcc
```
 
# Usage
使い方
```bash
git clone https://github.com/Taiki-Kobasako/Bank.git
cd 
gcc ATM.c -lncursesw
./a.out
```

# License
"ATM" is under [MIT license](https://en.wikipedia.org/wiki/MIT_License).
 
