void setKnown(byte x, byte y) {
  bitWrite(known[x / 8][y], x % 8, 1);
}

byte getKnown(byte x, byte y) {
  return bitRead(known[x / 8][y], x % 8);
}

void clearKnown() {
  for (int i = 0; i < 21; i++) {
    for (int j = 0; j < 8; j++) {
      monst[i][j] = 0;
      thing[i][j] = 0;
    }
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 8; j++) {
      known[i][j] = 0;
    }
  }
  for (int i = 0; i < TMAX; i++) {
    id[i] = 0;
    t1[i] = 0;
    t2[i] = 0;
    t3[i] = 0;
    t4[i] = 0;
  }
  for (int i = 0; i < MMAX; i++) {
    mx[i] = 0;
    my[i] = 0;
    ms[i] = 0;
    mh[i] = 0;
    m1[i] = 0;
    m2[i] = 0;
  }
}

void allKnown() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 8; j++) {
      known[i][j] = 255;
    }
  }
}

void makeKnown() {
  if (dungeon[hx][hy] >= 1 && dungeon[hx][hy] <= 6 && isDark[dungeon[hx][hy] - 1] == 0 ) {
    //  if (dungeon[x][y] >= 1 && dungeon[x][y] <= 6 ) {
    for (int i = 0; i < 21; i++) {
      for (int j = 0; j < 8; j++) {
        if (dungeon[i][j] % 10 == dungeon[hx][hy]) {
          //          known[i][j] = 1;
          setKnown(i, j);
        }
      }
    }
  } else {
    for (int i = 0; i <= 2; i++) {
      for (int j = 0; j <= 2; j++) {
        int tx = hx + i - 1;
        int ty = hy + j - 1;
        if (tx >= 0 && tx <= 20 && ty >= 0 && ty <= 7) {
          //          known[tx][ty] = 1;
          setKnown(tx, ty);
        }
      }
    }
  }
}

void clearDungeon() {
  for (int x = 0; x < 21; x++) {
    for (int y = 0; y < 8; y++) {
      dungeon[x][y] = 0;
    }
  }
}

void locate(int x, int y) {
  font5x7.setCursor(1 + x * 6, y * 8-1);
}

void drawMap() {    //@Pharap's sharp eye
  for (int i = 0; i < 21; i++) {
    for (int j = 0; j < 8; j++) {
      locate(i, j);
      //      if (known[i][j] == 1) {

      char c = ' ';
      if (getKnown(i, j) == 1) {
        if (dungeon[i][j] == 0) {
          c = ' '; //arduboy.print(F(" "));
        } else if (dungeon[i][j] >= 1 && dungeon[i][j] <= 6 && isDark[dungeon[hx][hy] % 10 - 1] == 0) {
          //        } else if (dungeon[i][j] >= 1 && dungeon[i][j] <= 6 ) {
          //          if ((dungeon[i][j] == dungeon[hx][hy]) || (dungeon[i][j] == dungeon[hx][hy] - 10)) {
          if ( dungeon[i][j] < 40 && dungeon[i][j] % 10 == dungeon[hx][hy] % 10 ) {
            c = '.'; //arduboy.print(F("."));
          } else {
            c = ' '; //arduboy.print(F(" "));
          }
        } else if (dungeon[i][j] == 8) {
          c = '#'; //arduboy.print(F("#"));
        } else if (dungeon[i][j] >= 11 && dungeon[i][j] <= 16) {
          c = '%'; //arduboy.print(F("%"));
        } else if (dungeon[i][j] >= 21 && dungeon[i][j] <= 26) {
          c = '+'; //arduboy.print(F("+"));
        } else if (dungeon[i][j] >= 31 && dungeon[i][j] <= 38) {
          c = '?'; //arduboy.print(F("?"));
        } else if (dungeon[i][j] >= 41 && dungeon[i][j] <= 46) {
          c = '-'; //arduboy.print(F("-"));
        } else if (dungeon[i][j] >= 51 && dungeon[i][j] <= 56) {
          c = '|'; //arduboy.print(F("|"));
        } else if (dungeon[i][j] >= 61 && dungeon[i][j] <= 66) {
          c = '-'; //arduboy.print(F("-"));
        } else if (dungeon[i][j] == 68) {
          c = ' '; //arduboy.print(F(" "));
        } else if (dungeon[i][j] >= 71 && dungeon[i][j] <= 76) {
          c = '|'; //arduboy.print(F("|"));
        }
      } else {
        c = ' '; //arduboy.print(F(" "));
      }
      font5x7.print(c);
    }
  }
}


void drawHero() {     //@Pharap's sharp eye
  if (hblnd == 0) {
    for (int i = 0; i <= 2; i++) {
      for (int j = 0; j <= 2; j++) {
        int tx = hx + i - 1;
        int ty = hy + j - 1;
        if (dungeon[tx][ty] >= 1 && dungeon[tx][ty] <= 6) { // (tx >= 0 && tx <= 20 && ty >= 0 && ty <= 7)
          locate(tx, ty);
          font5x7.print('.');
        }
      }
    }
  }
  locate(hx, hy);
  font5x7.print('@');
}

void drawMonst() {

  for (int i = 0; i < MMAX; i++) {
    if (ms[i] / 32 != 0) {
      if (hmdet == 0) {
        if (isDark[dungeon[hx][hy] % 10 - 1] == 0 && dungeon[hx][hy] != 8 &&
            dungeon[hx][hy] % 10 == dungeon[mx[i]][my[i]] % 10) {
          locate(mx[i], my[i]);
          //        arduboy.print((char)(65 + i));
          drawMonstSub(i);
        }
        if (abs(hx - mx[i]) <= 1 && abs(hy - my[i]) <= 1) {
          locate(mx[i], my[i]);
          drawMonstSub(i);
        }
      } else {
        locate(mx[i], my[i]);
        //        arduboy.print((char)(65 + i));
        drawMonstSub(i);
      }
    }
  }
}

void drawMonstSub(byte i) {
  if (bitRead(m1[i], 6) == 0 || hasRing(8) > 0 || hisee == 1) {
    if (hhall > 0) {
      if (ms[i] / 32 == 3) {
        font5x7.print((char)pgm_read_byte(tsym + random(9)));
      } else {
        font5x7.print((char)pgm_read_byte(mname + random(26) ));
      }
    } else {
      if (ms[i] / 32 == 3) {
        font5x7.print('*');
      } else {
        font5x7.print((char)pgm_read_byte(mname + (ms[i] % 32)));    //mimic is ms[i]%32==19 ms[i]/32==3
      }
    }
  }
}

byte canBless() {
  byte result = 0;
  int dra;
  for (int i = 1; i <= 4; i++) {
    dra = checkHit(i, 5);
    if ( ms[dra / 256 - 1] % 32 == 25) result++;
  }
  return result;
}

void moveMonst() {
  for (int i = 0; i < MMAX; i++) {
    if (ms[i] == 0) {
      if (random(128) == 0) {
        generateMon(i);
      }
    } else {
      byte fly = bitRead(m1[i], 7) + 1;
      if ( bitRead(m1[i], 2) == 0 || (bitRead(m1[i], 2) == 1 && ht % 2 == 0)) {
        for (int tt = 0; tt < fly; tt++) {
          int r;  //= random(4);
          if (ms[i] / 32 >= 2 && ms[i] / 32 <= 6) {
            r = 5;
          } else if (ms[i] % 32 == 21 && dungeon[hx][hy] != 8 &&
                     dungeon[mx[i]][my[i]] % 10 == dungeon[hx][hy] % 10 && bitRead(m1[i], 3) == 1) {
            flashHero();
            mess(18);
            hconf = 10;
            bitWrite(m1[i], 3, 0);
          } else if (ms[i] % 32 == 25 && canBless() > 0 && random(2) == 0) {
            byte dmg = random(10)+10;
            if( hp > dmg ){
              flashHero();
              mess(19);
              hp = hp - dmg; 
            }
          } else {
            
            char d=1;
            if(ms[i]/32 == 7) d=-1;
            
            if ( mx[i] > hx && monst[mx[i] - d][my[i]] == 0
                && dungeon[mx[i] - d][my[i]] >= 1 && dungeon[mx[i] - d][my[i]] <= 26) {
              r=2-d;
//              r = 1;
//              if(ms[i]/32 ==7) r=3;
            } else if ( my[i] > hy && monst[mx[i]][my[i] - d] == 0
                       && dungeon[mx[i]][my[i] - d] >= 1 && dungeon[mx[i]][my[i] - d] <= 26) {
              r=3-d;
//              r = 2;
//              if(ms[i]/32 ==7) r=4;
            } else if ( mx[i] < hx && monst[mx[i] + d][my[i]] == 0
                       && dungeon[mx[i] + d][my[i]] >= 1 && dungeon[mx[i] + d][my[i]] <= 26) {
              r=2+d;
//              r = 3;
//              if(ms[i]/32 ==7) r=1;
            } else if ( my[i] < hy && monst[mx[i]][my[i] + d] == 0
                       && dungeon[mx[i]][my[i] + d] >= 1 && dungeon[mx[i]][my[i] + d] <= 26) {
              r=3+d;
//              r = 4;
//              if(ms[i]/32 ==7) r=2;
            } else {
              r = random(4) + 1;
            }
          }
          if (bitRead(m1[i], 5) == 1 && random(3) == 0) r = random(4) + 1;

          char dx = (r - 2) * (r % 2);              //d=1(right), 2(up), 3(left), 4(down)
          char dy = (r - 3) * ((r - 1) % 2);

          switch (r) {
            case 1:
            case 2:
            case 3:
            case 4:
              if (mx[i] + dx == hx && my[i] + dy == hy) {
                //            msgc = "Mon hit.";
                if (tt == 0) hitHero(ms[i] % 32, i);
              } else if (ms[i]%32 != 15 &&
                         mx[i] + dx >= 0 && mx[i] + dx <= 20 &&
                         my[i] + dy >= 0 && my[i] + dy <= 7 &&
                         monst[mx[i] + dx][my[i] + dy] == 0 &&
                         dungeon[mx[i] + dx][my[i] + dy] >= 1 && dungeon[mx[i] + dx][my[i] + dy ] <= 26) {
                monst[mx[i]][my[i]] = 0;
                mx[i] = mx[i] + dx;
                my[i] = my[i] + dy;
                monst[mx[i]][my[i]] = i + 1;
              }
              break;
            case 5:
              break;
          }
        }
      }
    }
  }
}

void placeMonst() {
  byte stt, mon;
  for (int i = 0; i <= 8 + isBigRoom * 7; i++) {
    if ( random(3) == 0) {
      int h = 0;
      if(isBigRoom==0) h=random(RMAX) * 2;
      if (hasRoom[h] == 0) h++;
      mx[i] = roomSX[h] + random(roomEX[h] - roomSX[h] + 1);
      my[i] = roomSY[h] + random(roomEY[h] - roomSY[h] + 1);
      if (mx[i] != hx && my[i] != hy && monst[mx[i]][my[i]] == 0) {
        placeMonXY(i, mx[i], my[i]);
      } else {
        ms[i] = 0;
      }
    } else {
      ms[i] = 0;
    }
  }
}

void generateMon(byte m) {
  byte stt, mon;
  int hr = ((dungeon[hx][hy] - 1) % 10 - ((dungeon[hx][hy] - 1) % 10) % 2) / 2;
  //  int h = ((hr + random(2) + 1) % RMAX) * 2;
  int h = 0;
  if(isBigRoom==0) h=((hr + 1) % RMAX) * 2;
  if (hasRoom[h] == 0) h++;
  mx[m] = roomSX[h] + random(roomEX[h] - roomSX[h] + 1);
  my[m] = roomSY[h] + random(roomEY[h] - roomSY[h] + 1);
  if (monst[mx[m]][my[m]] == 0 ) {
    placeMonXY(m, mx[m], my[m]);
  }
}

void placeMonXY( byte i, byte x, byte y) {
  byte mon = randMonst(dlv);
  byte stt = initState(mon);
  ms[i] = stt * 32 + mon;
  mh[i] = pgm_read_byte(mstat[mon]);
  m1[i] = pgm_read_byte(mstat[mon] + 6) / 16 * 16;
  bitWrite(m1[i], 3, 1);
  //    bitWrite(m1[m],6,random(2));
  monst[x][y] = i + 1;
}

void showMsg() {
  if (hy >= 4) {
    locate(0, 0);
  } else {
    locate(0, 7);
  }
  font5x7.print(gbuf);
}

void placeThing() {
  for ( int i = 0; i < RMAX * 2; i++) {
    if (hasRoom[i] == 1) {
      for (int j = 0; j < 3 + isBigRoom * 7; j++) {
        byte ix = random(roomSX[i], roomEX[i] + 1);
        byte iy = random(roomSY[i], roomEY[i] + 1);
        placeThingXY(ix, iy, 0);
      }
    }
  }

  if( dlv % 3 ==0){
    for ( int i = 0; i < RMAX * 2; i++) {
      if (hasRoom[i] == 1) {
        byte ix = random(roomSX[i], roomEX[i] + 1);
        byte iy = random(roomSY[i], roomEY[i] + 1);
        placeThingXY(ix, iy, 2);
      }
    }
  }

  if (dlv >= adepth && ii[im - 1] != 144) {
    byte a = 0;
    if(isBigRoom==0) a=random(RMAX) * 2;
    if (hasRoom[a] == 0) a++;
    byte ax = roomSX[a] + random(roomEX[a] - roomSX[a] + 1);
    byte ay = roomSY[a] + random(roomEY[a] - roomSY[a] + 1);
    byte t = freeSlot();
    thing[ax][ay] = t + 1;
    id[t] = 144;
    t1[t] = 1;
    t2[t] = 0;
    t3[t] = 0;
    t4[t] = 0b00000000;
  }
}

void placeThingXY(byte ix, byte iy, byte r) {
  byte r1, r2, r3, vari, kind;
  if (thing[ix][iy] == 0) {
    byte t = freeSlot();
    thing[ix][iy] = t + 1;
    t1[t] = 1;
    t2[t] = 0;
    t3[t] = 0;
    t4[t] = 0;
    if(r==0){
      kind = randThing();
    } else {
      kind = r;
    }
    switch (kind) {
      case 1: //gold
        id[t] = 16;
        t1[t] = random(100) + dlv;
        break;
      case 2: //food
        if (random(5) == 0) {
          id[t] = 16 * 2 + 1;
        } else {
          id[t] = 16 * 2 + 0;
        }
        t1[t] = 1 + random(2);
        bitWrite(t4[t], 7, 1);
        break;
      case 3: //weapon
        vari = random(WEMAX);
        id[t] = 48 + vari;
        if (vari < 4) {
          t1[t] = 1;
        } else {
          t1[t] = 3 + random(13);
          bitWrite(t4[t], 7, 1);
        }
        r1 = random(6);
        if (r1 == 0) {
          r2 = random(3) + 1;
          r3 = random(r2 + 1);
          t2[t] = r3;
          t3[t] = r2 - r3;
        } else if (r1 == 1) {
          r2 = random(3) + 1;
          r3 = random(r2 + 1);
          t2[t] = r3 * (-1);
          t3[t] = (r2 - r3) * (-1);
          bitWrite(t4[t], 6, 1);
        }
        break;
      case 4: //armor
        vari = random(ARMAX);
        id[t] = 64 + vari;
        t1[t] = 1;
        r1 = random(6);
        if (r1 == 0) {
          t2[t] = random(3) + 1;
        } else if (r1 == 1) {
          t2[t] = (random(3) + 1) * (-1);
          bitWrite(t4[t], 6, 1);
        }
        if (vari == 0) {
          bitWrite(t4[t], 3, 1);
        }
        break;
      case 5: //potion
        vari = randPS(0);
        id[t] = 80 + vari;
        t1[t] = 1 ;//+ random(2);
        bitWrite(t4[t], 7, 1);
        break;
      case 6: //scroll
        vari = randPS(1);
        id[t] = 96 + vari;
        t1[t] = 1 ;//+ random(2);
        bitWrite(t4[t], 7, 1);
        break;
      case 7: //ring
        vari = random(RGMAX);
        id[t] = 112 + vari;
        t1[t] = 1;
        switch ( ttab[2][vari] ) {
          case 1:
            bitWrite(t4[t], 6, 1);
            break;
          case 4:
          case 6:
            r1 = random(2);
            if (r1 == 0) {
              t2[t] = random(2) + 1;
            } else {
              t2[t] = (random(2) + 1) * (-1);
              bitWrite(t4[t], 6, 1);
            }
            break;
          case 7:
            if (random(2) == 0) {
              bitWrite(t4[t], 6, 1);
            }
            break;
        }
        break;
      case 8:
        vari = random(WDMAX);
        id[t] = 128 + vari;
        t1[t] = 1;
        t2[t] = 3 + random(4);
        break;
    }
  }
}

void drawThing() {
  for (int i = 0; i < 21; i++) {
    for (int j = 0; j < 8; j++) {
      //      if (known[i][j] == 1 && thing[i][j] != 0 ) {
      if (getKnown(i, j) == 1 && thing[i][j] != 0 ) {
        locate(i, j);
        byte type = id[thing[i][j] - 1] / 16;
        if (hhall > 0) type = random(8) + 1;
        font5x7.print((char)pgm_read_byte(tsym + type - 1));
      }
    }
  }
  locate(hx, hy);
  font5x7.print('@');
}

void checkThing(byte x, byte y) {
  if (thing[x][y] == 0) {
    clearBuf();
  } else {
    byte type = id[thing[x][y] - 1] / 16;
    byte r = id[thing[x][y] - 1] % 16;
    byte k;

    switch (type) {
      case 1:
      case 2:
      case 3:
      case 4:
      case 9:
        k = 0;
        break;
      case 5:
      case 6:
      case 7:
      case 8:
        k = bitRead(tknow[type - 5], r);
        break;
    }
    itmToGitm(type, r, k);
    addBuf(gitm);
    byte done = 0;
    if (id[thing[x][y] - 1] == 16) {
      au = au + t1[thing[x][y] - 1];
      deleteThing(thing[x][y] - 1);
      thing[x][y] = 0;
      done = 1;
    } else {
      if (bitRead(t4[thing[x][y] - 1], 7) == 1 ) {
        for (int i = 0; i < im; i++) {
          if (ii[i] == id[thing[x][y] - 1] &&
              i2[i] == t2[thing[x][y] - 1] &&
              i3[i] == t3[thing[x][y] - 1] &&
              bitRead(i4[i], 6) == bitRead(t4[thing[x][y] - 1], 6)) {
            i1[i] = i1[i] + t1[thing[x][y] - 1];
            deleteThing(thing[x][y] - 1);
            thing[x][y] = 0;
            done = 1;
          }
        }
      }
      if (done == 0) {
        if (im == IMAX) {
          mess(2);
        } else {
          ii[im] = id[thing[x][y] - 1];
          i1[im] = t1[thing[x][y] - 1];
          i2[im] = t2[thing[x][y] - 1];
          i3[im] = t3[thing[x][y] - 1];
          i4[im] = t4[thing[x][y] - 1];
          deleteThing(thing[x][y] - 1);
          thing[x][y] = 0;
          im++;
          sortItem();
        }
      }
    }
  }
}

void deleteThing(byte i) {
  id[i] = 0;
  t1[i] = 0;
  t2[i] = 0;
  t3[i] = 0;
  t4[i] = 0;
}

byte initState(byte mon) {
  byte result;
  byte state = pgm_read_byte(mstat[mon] + 6) % 16;
  switch (state) {
    case 1:
      result = 1;
      break;
    case 2:
      result = 2;
      break;
    case 3:
      if (random(5) == 0) {
        result = 2;
      } else {
        result = 1;
      }
      break;
    case 4:
      result = 4;
      break;
    case 5:
      if (random(5) == 0) {
        result = 4;
      } else {
        result = 1;
      }
      break;
    case 6:       //for mimic
      result = 3;
  }
  return result;
}

void tweatHero() {
  ht++;
  if (ex >= nl && lv < 21) {   //level up
    mess(6);
    lv++;
    nl = nl * 2;
    byte r2 = random(8) + 3;
    hp = hp + r2;
    hpm = hpm + r2;
  }
//  if ( hp < hpm && ht % (22 - lv) == 0) {
  if ( hp < hpm && ht % ((22 - lv)/3+1) == 0) {
    hp = hp + 1 + hasRing(2);
  }
  if (hconf > 0) hconf--;
  if (hblnd > 0) hblnd--;
  if (hhall > 0) hhall--;
  if (hfast > 0) hfast--;
  if (hslep > 0) hslep--;
  if (hlevi > 0) hlevi--;

  if ( hasRing(1) > 0 && random(12) == 0) teleportHero();

  hh = hh - 1 + hasRing(3);
  if (equip(7, 1) != 0 && ht % 2 == 0) { //ring right
    hh--;
  }
  if (equip(7, 2) != 0 && ht % 2 == 1) { //ring left
    hh--;
  }

  if( hh < 60 || hp <= hpm / 4) {
    arduboy.setRGBled(50,0,0);
  } else {
    arduboy.setRGBled(0,0,0); 
  }

  if (hh <= 0) {  //gashi
    death=0;
    gstate = 2;
  }
  for (int i = 0; i < hasRing(10) * 2; i++) {
    search();
  }
}

