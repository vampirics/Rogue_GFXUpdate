void makeDungeon2() {
  char areaSX[6] = {}, areaSY[6] = {}, areaEX[6] = {}, areaEY[6] = {};
  char root[2] = {};
  char doorX[2] = {}, doorY[2];
  int pass[7] = {1, 1, 1, 1, 1, 1, 1};
  int passstat = 0;
  int temp[2] = {};
  int dr, fm, to, ro;

  for(int i=0; i<6; i++){
    hasRoom[i]=0;
  }
//縦に３分割する  
  for (int i = 0; i < 7; i++) {
    int r = random(3);
    switch (r) {
      case 0:
        temp[0]++;
        break;
      case 1:
        temp[1]++;
        break;
      case 2:
        break;
    }
  }
  int r1 = temp[0] + 4;
  int r2 = temp[1] + 4;
//横に２分割する
  int r3 = random(6) + 1;
  areaSX[0] = 0; areaSY[0] = 0; areaEX[0] = r1 - 1; areaEY[0] = r3; if (r3 >= 3) hasRoom[0] = 1;
  areaSX[1] = 0; areaSY[1] = r3 + 1; areaEX[1] = r1 - 1; areaEY[1] = 7; if ((7 - r3) >= 4) hasRoom[1] = 1;
  if (r3 == 3) { pass[0] = 0; passstat=passstat + 1; }
  root[0] = r1;
  int r4 = random(6) + 1;
  areaSX[2] = r1 + 1; areaSY[2] = 0; areaEX[2] = r1 + r2; areaEY[2] = r4; if (r4 >= 3) hasRoom[2] = 1;
  areaSX[3] = r1 + 1; areaSY[3] = r4 + 1; areaEX[3] = r1 + r2; areaEY[3] = 7; if ((7 - r4) >= 4) hasRoom[3] = 1;
  if (r4 == 3) { pass[3] = 0; passstat= passstat+2; }
  root[1] = r1 + r2 + 1;
  int r5 = random(6) + 1;
  areaSX[4] = r1 + r2 + 2; areaSY[4] = 0; areaEX[4] = 20; areaEY[4] = r5; if (r5 >= 3) hasRoom[4] = 1;
  areaSX[5] = r1 + r2 + 2; areaSY[5] = r5 + 1; areaEX[5] = 20; areaEY[5] = 7; if ((7 - r5) >= 4) hasRoom[5] = 1;
  if (r5 == 3) { pass[6] = 0; passstat=passstat+4; }
//部屋間の通路を減らす
  if (passstat == 0) {
    if (random(2) == 0) {
      pass[random(4)] = 0;
    }
    if (random(2) == 0) {
      pass[random(3) + 4] = 0;
    }
  } else if( passstat==1 ){
    if (random(2) == 0) {
      pass[random(3) + 4] = 0;
    }
  } else if( passstat==2 ){
    if (random(2) == 0) {
      pass[random(7)] = 0;
    }
  } else if( passstat==4 ){
    if (random(2) == 0) {
      pass[random(4)] = 0;
    }
  }
//部屋の大きさを決める
  for (int i = 0; i <= 5; i++) {
    if (hasRoom[i] == 1) {
      int roomX = random(areaEX[i] - areaSX[i] - 2) + 2; // 2<= roomX <= areaEX-areaSX+1-2
      int roomY = random(areaEY[i] - areaSY[i] - 2) + 2;
      roomSX[i] = areaSX[i] + random(areaEX[i] - areaSX[i] - roomX) + 1;
      roomSY[i] = areaSY[i] + random(areaEY[i] - areaSY[i] - roomY) + 1;
      roomEX[i] = roomSX[i] + roomX - 1;
      roomEY[i] = roomSY[i] + roomY - 1;
    }
  }
  for (int i = 0; i <= 5; i++) {
    if (hasRoom[i] == 0) {
      if (( i % 2 ) == 0) {
        roomSX[i] = roomSX[i + 1] + random(roomEX[i + 1] - roomSX[i + 1] + 1);
        roomSY[i] = areaSY[i] + random(areaEY[i] - areaSY[i] + 1);
        roomEX[i] = roomSX[i];
        roomEY[i] = roomSY[i];
      } else {
        roomSX[i] = roomSX[i - 1] + random(roomEX[i - 1] - roomSX[i - 1] + 1);
        roomSY[i] = areaSY[i] + random(areaEY[i] - areaSY[i] + 1);
        roomEX[i] = roomSX[i];
        roomEY[i] = roomSY[i];
      }
    }
  }
//部屋を配列に書き込む
  for (int i = 0; i <= 5; i++) {
    if (hasRoom[i] == 1) {
      for (int x = roomSX[i] - 1; x <= roomEX[i] + 1; x++) {
        for (int y = roomSY[i] - 1; y <= roomEY[i] + 1; y++) {
//          dungeon[x][y] = 31 + i;
          dungeon[x][y] = 41 + i;
        }
      }
      for (int x = roomSX[i] - 1; x <= roomEX[i] + 1; x++) {
        for (int y = roomSY[i]; y <= roomEY[i]; y++) {
//          dungeon[x][y] = 41 + i;
          dungeon[x][y] = 51 + i;
        }
      }
      for (int x = roomSX[i]; x <= roomEX[i]; x++) {
        for (int y = roomSY[i]; y <= roomEY[i]; y++) {
          dungeon[x][y] = 1 + i;
        }
      }
    } else {
      //      dungeon[roomSX[i]][roomSY[i]] = 1 + i;
      dungeon[roomSX[i]][roomSY[i]] = 8;
    }
  }
//部屋間の通路をつくる
  for (int p = 0; p <= 6; p++) {
    if (pass[p] == 1) {
      switch (p) {
        case 0:
          dr = 1;
          fm = 0;
          to = 1;
          break;
        case 1:
          dr = 0;
          fm = 0;
          to = 2;
          ro = 0;
          break;
        case 2:
          dr = 0;
          fm = 1;
          to = 3;
          ro = 0;
          break;
        case 3:
          dr = 1;
          fm = 2;
          to = 3;
          break;
        case 4:
          dr = 0;
          fm = 2;
          to = 4;
          ro = 1;
          break;
        case 5:
          dr = 0;
          fm = 3;
          to = 5;
          ro = 1;
          break;
        case 6:
          dr = 1;
          fm = 4;
          to = 5;
          break;
      }
//縦の通路のとき
      if (dr == 0) {
        doorX[0] = roomEX[fm] + 1;
        doorY[0] = roomSY[fm] + random(roomEY[fm] - roomSY[fm]);
        doorX[1] = roomSX[to] - 1;
        doorY[1] = roomSY[to] + random(roomEY[to] - roomSY[to]);
        if (hasRoom[fm] == 0) {
          dungeon[doorX[0]][doorY[0]] = 8;  //31+fr
        } else {
//          dungeon[doorX[0]][doorY[0]] = 21 + fm; //31+fr
          if(random(2)==0){
            dungeon[doorX[0]][doorY[0]] = 21 + fm; //31+fr
          } else {
            dungeon[doorX[0]][doorY[0]] = 71 + fm; //31+fr
          }
        }
        if (hasRoom[to] == 0) {
          dungeon[doorX[1]][doorY[1]] = 8;  //31+fr
        } else {
          dungeon[doorX[1]][doorY[1]] = 21 + to; //31+fr
        }
        for (int x = doorX[0] + 1; x < root[ro]; x++) {
          dungeon[x][doorY[0]] = 8; //10
        }
        for (int x = doorX[1] - 1; x > root[ro]; x--) {
          dungeon[x][doorY[1]] = 8; //10
        }
        if (doorY[0] < doorY[1]) {
          for (int y = doorY[0]; y <= doorY[1]; y++) {
            dungeon[root[ro]][y] = 8; //10
          }
        } else {
          for (int y = doorY[0]; y >= doorY[1]; y--) {
            dungeon[root[ro]][y] = 8; //10
          }
        }
//横の通路のとき
      } else {
        if (hasRoom[fm] == 1) {
          doorX[0] = roomSX[fm + 1];
          doorY[0] = roomEY[fm] + 1;
          doorX[1] = roomSX[to];
          doorY[1] = roomSY[to] - 1;
//          dungeon[doorX[0]][doorY[0]] = 21 + fm; //31+fr
          if(random(2)==0){
            dungeon[doorX[0]][doorY[0]] = 21 + fm; //31+fr
          } else {
            dungeon[doorX[0]][doorY[0]] = 61 + fm; //31+fr
          }
          //            dungeon[doorX[1]][doorY[1]] = 8;  //31+to
          for (int y = doorY[0] + 1; y <= doorY[1]; y++) {
            dungeon[doorX[0]][y] = 8;
          }
        } else {
          doorX[0] = roomSX[fm];
          doorY[0] = roomEY[fm] + 1;
          doorX[1] = roomSX[to - 1];
          doorY[1] = roomSY[to] - 1;
          //            dungeon[doorX[0]][doorY[0]] = 8;  //31+fr
//          dungeon[doorX[1]][doorY[1]] = 21 + to; //31+to
          if(random(2)==0){
            dungeon[doorX[1]][doorY[1]] = 21 + to; //31+fr
          } else {
            dungeon[doorX[1]][doorY[1]] = 61 + to; //31+fr
          }
          for (int y = doorY[1] - 1; y >= doorY[0]; y--) {
            dungeon[doorX[0]][y] = 8;
          }
        }
      }
    }
  }
//６部屋の場合，縦につなぐ
  if(passstat==7){
    int r=random(2);
    for(int yy=2; yy<=5; yy++){
      dungeon[root[r]][yy]=8;
    }
  }
//隠された通路
  for(int i=0; i<21; i++){
    for(int j=0; j<8; j++){
      if(dungeon[i][j]==8 && random(5)==0){
        dungeon[i][j]=68;
      }
    }
  }
  
//階段をつくる
  int s=random(3)*2;
  if(hasRoom[s]==0) s++;
  dungeon[roomSX[s]+random(roomEX[s]-roomSX[s]+1)][roomSY[s]+random(roomEY[s]-roomSY[s]+1)] =11+s;
//暗い部屋をつくる
  for(int i=0; i<6; i++){
    if(random(5)==0){
      isDark[i]=1;
    } else {
      isDark[i]=0;
    }
  }

  clearKnown();
//ヒーローを置く
  teleportHero();
/*
  int h=random(3)*2;
  if(hasRoom[h]==0) h++;
  hx=roomSX[h]+random(roomEX[h]-roomSX[h]+1);
  hy=roomSY[h]+random(roomEY[h]-roomSY[h]+1);
*/
}

void teleportHero(){
  int h=0;
  if(isBigRoom==0) h=random(RMAX)*2;
  if(hasRoom[h]==0) h++;
  hero.hx=roomSX[h]+random(roomEX[h]-roomSX[h]+1);
  hero.hy=roomSY[h]+random(roomEY[h]-roomSY[h]+1);
  if(monst[hero.hx][hero.hy] != 0){
    ms[monst[hero.hx][hero.hy]-1]=0;
    monst[hero.hx][hero.hy]=0;
  }
}

