void eat(byte r) {
/*
  if (r == 0 && random(3) == 0) {
    mess(7);
//    hh = hh / 3 + 700 + random(200);
    hh = hh / 3 + 300 + random(50);
    ex = ex + 2;
  } else {
*/
    mess(8);
//    hh = hh / 3 + 900 + random(200);
    hh = hh / 3 + 350 + random(50);
//  }
}

void wield(byte r) {
  if (bitRead(i4[r], 4) == 1) {
    if (bitRead(i4[r], 6) == 1) {
      mess(9);            // cursed
    } else {
      bitWrite(i4[r], 4, 0);
      mess(10);           //remove
      if (ii[r] / 16 == 7) ringPut(r, -1);
    }
  } else {
    switch (ii[r] / 16) {
      case 3:
      case 4:
        if (equip(ii[r] / 16, 1) != 0) {
          mess(12);       //already wield
        } else {
          bitWrite(i4[r], 1, 1);
          bitWrite(i4[r], 4, 1);
          mess(11);       //ready go
        }
        break;
      case 7:
        if (equip(7, 1)*equip(7, 2) != 0) {
          mess(12);
        } else {
          bitWrite(i4[r], 1, 1);
          bitWrite(i4[r], 4, 1);
          mess(11);       //ready go
          ringPut(r, 1);
        }
        break;
    }
  }
}

void ringPut(byte r, char i) {
  switch (ttab[2][ii[r] % 16]) {
    case 4:
      rstr = rstr + i2[r] * i;
      break;
    case 6:
      rdex = rdex + i2[r] * i;
      break;
  }
}

void drink(byte r) {
  switch (ttab[0][r]) {
    case 0:       //power
      if (st == stm) {      //@Pharap's sharp eye
        st++;
        stm++;
      } else {
        st++;
      }
      break;
    case 1:       //restore
      st = stm;
      break;
    case 2:       //heal
      if (hp == hpm) {
        hp++;
        hpm++;
      } else {
        hp = (hpm + hp) / 2;
      }
      break;
    case 3:       //e.heal
      if (hp == hpm) {
        hp = hp + 2;
        hpm = hpm + 2;
      } else {
        hp = hpm;
      }
      break;
    case 4:       //poison
      if (st > 3) st = st - random(3) - 1;
      hhall = 0;
      break;
    case 5:       //level
      ex = nl;
      break;
    case 6:       //blind
      hblnd = 50;
      break;
    case 7:       //hallu
      hhall = 50;
      break;
    case 8:       //m.dtect
      hmdet = 1;
      break;
    case 9:       //i.dtect
      for (int x = 0; x < 21; x++) {
        for (int y = 0; y < 8; y++) {
          if (thing[x][y] != 0) {
            setKnown(x, y);
          }
        }
      }
      break;
    case 10:      //confuse
      hconf = 10;
      break;
    case 11:      //levtate
      hheld = 0;
      hlevi = 30;
      break;
    case 12:      //speed
      hfast = 20;
      break;
    case 13:      //look
      hisee = 1;
      break;
  }
}

void readScroll(byte r) {
  byte ex = 0, i = 0, st, dx, dy;
  int fp;
  switch (ttab[1][r]) {
    case 0:       //protect
      st = equip(4, 1);
      if (st != 0) bitWrite(i4[st - 1], 3, 1);
      break;
    case 1:       //hold
      for (int x = -2; x <= 2; x++) {
        for (int y = -2; y <= 2; y++) {
          st = monst[hx + x][hy + y];
          if (st != 0 ) ms[st - 1] = 4 * 32 + ms[st - 1] % 32;
        }
      }
      break;
    case 2:       //weapon
      i = equip(3, 1);
      if (i != 0) {
        //        bitWrite(he, 3, 0);
        bitWrite(i4[i - 1], 6, 0);
        if (random(2) == 0) {
          i2[i - 1]++;
          //          hdex++;
        } else {
          i3[i - 1]++;
          //          hdmg++;
        }
      }
      break;
    case 3:       //armor
      i = equip(4, 1);
      if (i != 0) {
        //        bitWrite(he, 2, 0);
        bitWrite(i4[i - 1], 6, 0);
        i2[i - 1]++;
        //        ac++;
      }
      break;
    case 4:       //identify
      st = inventry(1);
      bitWrite(i4[st], 1, 1);   //add known2
      bitWrite(i4[st], 5, 1);   //add known
      if (ii[st] / 16 >= 5) bitWrite(tknow[ii[st] / 16 - 5], ii[st] % 16, 1);
      if (ii[st] / 16 < 5 || ii[st] / 16 == 9) {
        itmToGitm(ii[st] / 16, ii[st] % 16, 0);
      } else {
        itmToGitm(ii[st] / 16, ii[st] % 16, 1);
      }
      //      itmToGitm(ii[st] / 16, ii[st] % 16, 1);
      addBuf(gitm);
      break;
    case 5:       //telport
      teleportHero();
      break;
    case 6:       //sleep
      hslep = 5;
      break;
    case 7:       //scare
      break;
    case 8:       //bless
      for (int i = 0; i < im; i++) {
        bitWrite(i4[i], 6, 0);
      }
      break;
    case 9:       //create
      for (int i = 0; i < MMAX; i++) {
        if (ms[i] == 0) {
          st = i + 1;
        }
      }
      fp = findPlace(hx, hy, 1);
      if (st != 0 && fp != 0) {
        dx = (fp - 1) % 3 - 1;
        dy = (fp - 1) / 3 - 1;
        mx[st - 1] = hx + dx;
        my[st - 1] = hy + dy;
        placeMonXY( st - 1 , hx + dx, hy + dy );
        drawMonst();
      }
      break;
    case 10:      //anger
      for (int i = 0; i < 16; i++) {
        if (ms[i] != 0) {
          ms[i] = 32 + ms[i] % 32;
        }
      }
      break;
    case 11:      //map
      for (int x = 0; x < 21; x++) {
        for (int y = 0; y < 8; y++) {
          if (dungeon[x][y] >=31 && dungeon[x][y] <= 106) dungeon[x][y] += 80;
          if (dungeon[x][y] != 0) {
            setKnown(x, y);
          }
        }
      }
      break;
  }
}

void zap(byte vari) {
  byte dir = askDir();
  int dest = checkHit(dir, 20);
  byte mon = dest / 256;
  char destx = (dest % 256) % 21;
  char desty = (dest % 256) / 21;
  if (mon != 0) hitWand( vari, mon, destx, desty);
}

byte equip(byte type, byte n) {     //type=3(weapon),4(armor),7(ring), n=1 or 2(for ring)...rtab[equip(7,2)]
  byte result = 0;
  for (int i = 0; i < 20; i++) {
    if (ii[i] / 16 == type) {
      if (bitRead(i4[i], 4) == 1) {
        n--;
        if (n == 0) {
          result = i + 1;
        }
      }
    }
  }
  return result;      //0=nothing, num=pack+1
}

byte hasRing(byte vari) {
  byte result = 0;
  for (byte i = 0; i < 2; i++) {
    if (equip(7, i + 1) != 0) {
      if (ttab[2][ii[(equip(7, i + 1) - 1)] % 16]  == vari) {
        result++;
      }
    }
  }
  return result;
}

int checkHit(byte dir, byte str) {
  char dx = (dir - 2) * (dir % 2);
  char dy = (dir - 3) * ((dir - 1) % 2);
  byte ex = 0, i = 0;
  byte mon = 0;
  byte x = hx, y = hy;
  do {
    if (monst[x + dx][y + dy] != 0) {
      mon = monst[x + dx][y + dy];
      x = x + dx;
      y = y + dy;
      ex = 1;
    } else if (dungeon[x + dx][y + dy] == 0 || dungeon[x + dx][y + dy] >= 200) {
      ex = 1;
    } else {
      x = x + dx;
      y = y + dy;
      i++;
      if (i == str) ex = 1;
    }
  } while (ex == 0);
  return mon * 256 + y * 21 + x;
}

byte findPlace(byte x, byte y, byte tm) {   //tm=0:thing, 1:monst
  byte result = 0;
  byte ex = 0, i = 0, r = random(8);
  monst[hx][hy] = 255;
  do {
    char st = (i + r) % 9;
    char dx = st % 3 - 1;
    char dy = st / 3 - 1;
    if (dungeon[x + dx][y + dy] >= 1 && dungeon[x + dx][y + dy] <= 200
        && thing[x + dx][y + dy] * !tm == 0 && monst[x + dx][y + dy]*tm == 0) {
      result = st + 1;
      ex = 1;
    } else {
      i++;
      if (i == 9) {
        ex = 1;
      }
    }
  } while (ex == 0);
  monst[hx][hy] = 0;
  return result;
}

