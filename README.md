# Bank Program
これは、大学1年のプログラミング演習の時に作った、Unix系システムでの端末制御ライブラリであるcursesを用いた疑似ATMシステムである。
同じディレクトリ下にある通帳ファイル（passbook.dat）を読み込んで操作を行う。
 
# DEMO
"hoge"の魅力が直感的に伝えわるデモ動画や図解を載せる
 
# Requirement
* cureses
* gcc
 
# Installation
```bash
sudo apt install libncursesw5-dev gcc
```
 
# Usage
```bash
git clone https://github.com/Taiki-Kobasako/Bank.git
cd 
gcc ATM.c -lncursesw
./a.out
```

# License
"ATM" is under [MIT license](https://en.wikipedia.org/wiki/MIT_License).
 
