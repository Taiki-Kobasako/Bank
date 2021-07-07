/*
  @author 木場迫大樹　
  @version 1
*/

//ヘッダー
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <string.h>
#include <locale.h>//日本語化のおまじない1
#define wait_time 5

//構造体
 typedef struct PASSBOOK{ //通帳用構造体
   int bank;         //金融機関ID
   int id;           //口座番号
   char firstname[30];        //名前
   char secondname[30];
   int password;     //暗証番号
   int balance;      //残高
 }Passbook;

typedef struct DUMMY{
  char a[50];
  char b[50];
  char c[50];
  char d[50];
  char e[50];
}Dummy;


typedef struct POINT{
  int x;
  int y;
}Point;

//プロトタイプ宣言
void payment(Point a,Passbook l,Dummy t);         //入金関数
void hikidasi(Point a,Passbook l, Dummy t);       //引き出し関数
void changeppasword(Point a, Passbook l,Dummy t); //暗証番号変更関数
void balance(Point a,Passbook);
void welcome(Point a);
char opening(Point a);
char exitcheck(Point a);
void thankyou(Point a);
int password(Point a,Passbook l);

//以下メイン
int main(){
  setlocale( LC_ALL, "" );//日本語化のおまじない2
  FILE *fp;
  Point a;
  char c[10],key;
  int i,maxlen=4,test=0;
  int max_x, max_y;         // 画面のサイズ
  Dummy t;
  Passbook l;

  //以下通帳読み込み開始
  fp= fopen("passbook.dat", "r"); //通帳読み込み開始
  if ( fp == NULL ) {   //指定したファイルが読み込めなかった処理
    printf("通帳が存在しません\n");
    return 1;
  }
 

  //以下画面制御準備
  initscr();                       // 画面制御開始
  timeout(-1);                      // キー入力の待ち時間
  curs_set(0);                     // カーソルの表示をしない
  cbreak();                        //　キー入力設定
  getmaxyx( stdscr, max_y, max_x); //　画面範囲値取得
  a.y=max_y;
  a.x=max_x;

  welcome(a);
  while(1){
    noecho();                        // キー入力した際に入力文字を表示しない設定
    fopen("passbook.dat", "r");
    fscanf(fp, "%s %s %s %s %s", t.a, t.b, t.c, t.d, t.e);
    fscanf(fp, "%d %d %s %s %d %d" , &l.bank, &l.id ,l.secondname, l.firstname, &l.password, &l.balance); //通帳データ読み込み
    fclose(fp);
    key=opening(a);
    clear();

    if(key=='1'){
      payment(a,l, t);
    }else if(key=='2'){
      if(password(a,l)==1){
      }else{
	hikidasi(a,l, t);
      }
    }else if(key=='3'){
      if(password(a,l)==1){
      }else{
	balance(a,l);
      }
    }else if(key=='4'){
      if(password(a,l)==1){
	
      }else{
	changeppasword(a,l,t);
      }
    }else if(key=='5'){
      break;
    }
  }
  thankyou(a);
  endwin();

  return 0;
}

/*基本プログラム関数*/
void welcome(Point a){ //オープニング
  Point b;
  int i;
  b.x=a.x/2;
  b.y=a.y/2;
  move(b.y, b.x-9);
  printw("ようこそ");
  refresh();
  sleep(1);
  move(b.y,b.x);
  printw("@@@@銀行");
  refresh();
  sleep(1);
  move(b.y+1,b.x-2);
  printw("ATM");
  refresh();
  sleep(2);
  clear();
}

char opening (Point a){ //メインメニュー画面
  Point b;
  char key;
  b.x=a.x/2;
  b.y=a.y/2;
  move(b.y-2,b.x-6);
  addstr("Menu");
  move(b.y-1,b.x-6);
  addstr("1:入金");
  move(b.y,b.x-6);
  addstr("2:お引き出し");
  move(b.y+1,b.x-6);
  addstr("3:残高確認");
  move(b.y+2,b.x-6);
  addstr("4:パスワード変更");
  move(b.y+3,b.x-6);
  addstr("5:お取引中止");
  refresh();
  while(1){
    key =  getch();
    if(key=='1'||key=='2'||key=='3'||key=='4'||key=='5'){
      break;
    }
  }
  clear();
  return key;
}

void balance(Point a,Passbook l){ //残高確認プログラム
  noecho();//保険
  char key;
  move(a.y/2-2,a.x/2-6);
  addstr("現在の口座残高");
  move(a.y/2-1,a.x/2-6);
  addstr("--------------");
  move(a.y/2,a.x/2-4);
  printw("%d",l.balance);
  move(a.y/2,a.x/2+5);
  addstr("円");
  move(a.y/2+1,a.x/2-6);
  addstr("--------------");
  move(a.y/2+2,a.x/2-6);
  addstr("0:終了");
  refresh();
  while(1){ //0だけ入力まちプログラム
    key =  getch();
    if(key=='0'){
      break;
    }
  }
  clear();
}

void payment(Point a,Passbook l, Dummy t){ //入金プログラム
  echo();//保険
  FILE *fp;
  int maxlen=9,addcash=0;
  char *cash;
  cash=(char *)malloc(255);
  clear();
  while(1){
    move(a.y/2-2,a.x/2-15);
    addstr("入金したい金額を入力してください");
    move(a.y/2-1,a.x/2-15);
    addstr("-------------------------------");
    move(a.y/2,a.x/2+5);
    addstr("円");
    move(a.y/2+1,a.x/2-15);
    addstr("-------------------------------");
    move(a.y/2+2,a.x/2-14);
    addstr("(0を入力enter keyで取引中止)");
    move(a.y/2,a.x/2-5);
    refresh();
    getnstr(cash, maxlen);
    addcash=atoi(cash); //int型変換
    if(addcash==0) break;
    if(l.balance+addcash<=100000000){
      fp= fopen("passbook.dat", "w"); //通帳読み込み開始
      fprintf(fp, "%6s %4s %s %s %s\n", t.a, t.b, t.c, t.d, t.e); //一文字表示は%c
      fprintf(fp, "%d %d %s %s %d %d\n" , l.bank, l.id ,l.secondname, l.firstname, l.password,l.balance+addcash); //一文字表示は%c
      fclose(fp);
      break;
    }else{
      clear();
      move(a.y/2-2,a.x/2-8);
      addstr("申し訳こざいません");
      move(a.y/2-1,a.x/2-26);
      addstr("お使いの口座では一億円以上の貯蓄をすることができません");
      refresh();
      sleep(1);
      clear();
      move(a.y/2,a.x/2-24);
      addstr("申し訳ございませんが、最初からやり直してください");
      refresh();
      sleep(2);
      clear();
    }
  }
  clear();
  free(cash);
}

void hikidasi(Point a,Passbook l, Dummy t){ //引き出し関数
  echo();//保険
  FILE *fp;
  int maxlen=9,addcash=0,i=0;
  char *cash;
  cash = (char *)malloc(255);
  clear();
  move(a.y/2-2,a.x/2-17);
  addstr("お引き出する金額を入力してください");
  move(a.y/2-1,a.x/2-17);
  addstr("----------------------------------");
  move(a.y/2,a.x/2+5);
  addstr("円");
  move(a.y/2+1,a.x/2-17);
  addstr("----------------------------------");
  move(a.y/2+2,a.x/2-14);
  addstr("(0を入力enter keyで取引中止)");
  move(a.y/2,a.x/2-5);
  refresh();
  getnstr(cash, maxlen);
  addcash=atoi(cash); //int型変換
  if(addcash==0){
    
  }else if(l.balance>=addcash){
    i=l.balance-addcash;
    fp= fopen("passbook.dat", "w"); //通帳読み込み開始
    fprintf(fp, "%s %s %s %s %s\n", t.a, t.b, t.c, t.d, t.e); //一文字表示は%c
    fprintf(fp, "%d %d %s %s %d %d\n" , l.bank, l.id ,l.secondname, l.firstname, l.password, i); //一文字表示は%c
    fclose(fp);
  }else{
    clear();
    move(a.y/2,a.x/2-9);
    addstr("申し訳こざいません");
    move(a.y/2-1,a.x/2-26);
    addstr("指定した金額は残高不足のため引き出すことができません");
    refresh();
    sleep(1);
  }
  clear();
  free(cash);
}

void changeppasword(Point a, Passbook l,Dummy t){ //暗証番号変更関数
  char *pass1,*pass2;
  int newp1=0, newp2=0,maxlen=4,k=0,s=0;
  FILE *fp;
  pass1=(char *)malloc(255);
  pass2=(char *)malloc(255);
  echo();
  while(1){
    while (1){
      clear();
      move(a.y/2-2,a.x/2-21);
      addstr("新しい暗証番号入力後Enterキーを押してください");
      move(a.y/2-1,a.x/2-18);
      addstr("---------------------------------------");
      move(a.y/2+1,a.x/2-18);
      addstr("---------------------------------------");
      move(a.y/2+2,a.x/2-22);
      addstr("暗証番号は必ず数字(1000~9999)で入力してください");
      move(a.y/2+3,a.x/2-12);
      addstr("Back Spaceで訂正できます");
      move(a.y/2,a.x/2-2);
      getnstr(pass1, maxlen);
      newp1=atoi(pass1); //int型変換
      refresh();
      if(1000<=newp1&&newp1<=9999){
	break;
      }else{
	clear();
	move(a.y/2,a.x/2-22);
	addstr("暗証番号は必ず数字(1000~9999)で入力してください");
	refresh();
	sleep(2);
      }
    }
  
    while (1){
      clear();
      move(a.y/2-3,a.x/2-17);
      addstr("確認のためもう一度新しい暗証番号入力後");
        move(a.y/2-2,a.x/2-10);
      addstr("Enterキーを押してください");
      move(a.y/2-1,a.x/2-18);
      addstr("---------------------------------------");
      move(a.y/2+1,a.x/2-18);
      addstr("---------------------------------------");
      move(a.y/2+2,a.x/2-10);
      addstr("Back Spaceで訂正できます");
      move(a.y/2,a.x/2-2);
      getnstr(pass2, maxlen);
      newp2=atoi(pass2); //int型変換
      refresh();
      if(newp1==newp2){
	clear();
	s=1;
	break;
      }else{
	clear();
	move(a.y/2,a.x/2-28);
        addstr("パスワードが違います。もう一度最初からやり直してください。");
	refresh();
	sleep(2);
	break;
      }
    }
    if(s==1){
      fp= fopen("passbook.dat", "w"); //通帳読み込み開始
      fprintf(fp, "%s %s %s %s %s\n", t.a, t.b, t.c, t.d, t.e); //一文字表示は%c
      fprintf(fp, "%d %d %s %s %d %d\n" , l.bank, l.id ,l.secondname, l.firstname, newp2, l.balance); //一文字表示は%c
      fclose(fp);
      break;
    }
  }
  free(pass1);
  free(pass2);
}

char exitcheck(Point a){
  noecho();
  char key;
  move(a.y/2-1,a.x/2-8);
  addstr("お取引を続けますか");
  move(a.y/2,a.x/2-8);
  addstr("1:はい");
  move(a.y/2+1,a.x/2-8);
  addstr("2:いいえ");
  refresh();
  while(1){
    key =  getch();
    if(key=='1'||key=='2'){
      break;
    }
  }
  clear();
  return key;
}

void thankyou(Point a){ //終了画面
  move(a.y/2,a.x/2-10);
  addstr("ご利用ありがとうござました");
  move(a.y/2+1,a.x/2-2);
  addstr("@@@@銀行");
  refresh();
  sleep(2);
}

int password(Point a,Passbook l){ //暗証番号認証プログラム
  int maxlen=4,answer=0;
  char *pass;
  echo();
  int u=0;
  pass =(char *)malloc(255);
  while(1){
    move(a.y/2-2,a.x/2-18);
    addstr("暗証番号入力後Enterキーを押してください");
    move(a.y/2-1,a.x/2-18);
    addstr("---------------------------------------");
    move(a.y/2+1,a.x/2-18);
    addstr("---------------------------------------");
    move(a.y/2+2,a.x/2-16);
    addstr("暗証番号は必ず数字で入力してください");
    move(a.y/2+3,a.x/2-12);
    addstr("Back Spaceで訂正できます");
    move(a.y/2,a.x/2-2);
    refresh();
    getnstr(pass, maxlen);
    answer=atoi(pass); //int型変換
    clear();
    if(answer==l.password){
      break; //暗証番号一致なら認証プロトコルから脱出
    }else{
      ++u;
    }
    if(u==3) break; //三回失敗時脱出
    move(a.y/2,a.x/2-8);
    addstr("暗証番号が違います");
    move(a.y/2+1,a.x/2-11);
    addstr("もう一度入力してください");
    refresh();
    sleep(1);
    clear();
  }
  if(u==3){ //認証三回失敗時処理
    move(a.y/2,a.x/2-12);
    addstr("暗証番号を三回間違えました");
    refresh();
    sleep(1);
    clear();
    return 1;
  }else { //暗証番号二回以内成功時処理
    clear();
    return 0;
  }
  free(pass);
}
