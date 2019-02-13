byte inputWait() {
  byte result = 0;
  do {
    arduboy.pollButtons();
    if (arduboy.justPressed(LEFT_BUTTON)) result = 1;
    if (arduboy.justPressed(UP_BUTTON)) result = 2;
    if (arduboy.justPressed(RIGHT_BUTTON)) result = 3;
    if (arduboy.justPressed(DOWN_BUTTON)) result = 4;
    if (arduboy.justPressed(A_BUTTON)) result = 5;
    if (arduboy.justPressed(B_BUTTON)) result = 6;
  } while (result == 0);
  clearBuf();
  return result;
}

void drawInventry(byte st, byte mode) {
  byte ed;
  arduboy.clear();
  locate(0, 0);
  if(mode==0){
//    arduboy.setTextBackground(WHITE);
    arduboy.fillRect(0,0,128,8,WHITE);
    font5x7.setTextColor(BLACK);
    font5x7.print(F(" Inventory     "));
    font5x7.print( hh );
    font5x7.print(F("  "));
  } else {
    font5x7.print(F(" which}"));
  }
  locate(0, 1);
//  arduboy.setTextBackground(BLACK);
  font5x7.setTextColor(WHITE);
  font5x7.print('>');

  if (st + 7 > im) {
    ed = im;
  } else {
    ed = st + 7;
  }
  for (int i = st; i < ed; i++) {
    locate(1, i - st + 1);
    char buff;
    if(bitRead(i4[i],3)==1){
      buff='{';
    } else {
      buff = pgm_read_byte(tsym + ii[i] / 16 - 1);
    }
    font5x7.print(buff);
    font5x7.print(' ');

    if(bitRead(i4[i],7)==1){
        font5x7.print(i1[i]);
        font5x7.print(' ');      
    }
    if(ii[i]/16<5){
      itmToGitm(ii[i]/16,ii[i]%16,0);
    } else {
      itmToGitm(ii[i]/16,ii[i]%16,bitRead(tknow[ii[i]/16-5],ii[i]%16));
    }
    font5x7.print(gitm);
    if(bitRead(i4[i],5)==1){
      if(ii[i]/16 == 3){           //weapon
        font5x7.print('^');
        font5x7.print((int)i2[i]);
        font5x7.print('<'); //replacement for ','
        font5x7.print((int)i3[i]);
        font5x7.print(']');      
      } else if(ii[i]/16 == 4 || ii[i]/16 == 8){      //armor or ring
        font5x7.print('^');
        font5x7.print((int)i2[i]);
        font5x7.print(']');
      } else if(ii[i]/16 == 7){
        if(i2[i] != 0){
          font5x7.print('^');
          font5x7.print((int)i2[i]);
          font5x7.print(']');
        }
      }
    }
    if(bitRead(i4[i],4)==1){
      font5x7.print(F(" E"));
    }
    if(bitRead(i4[i],6)==1 && bitRead(i4[i],1)==1){
      font5x7.print(F(" C"));
    }
  }
  arduboy.display();
}

byte inventry(byte mode) {
  byte st = 0;
  byte ex = 0;
  do {
    drawInventry(st, mode);
    byte a = inputWait();
    if (a == 2) {
      if (st > 0) st--;
    }
    if (a == 4) {
      if (st < im - 1) st++;
    }
    if (a == 5) {
      if(mode==0){
        ex = action(st);
      } else {
        ex=1;
      }
    }
    if (a == 6) {
      ex = 1;
    }
  } while (ex == 0);
  return st;
}

byte action(byte st) {
  byte curs = 0;
//  arduboy.setTextBackground(WHITE);
  arduboy.fillRect(6,8,75,8,WHITE);
  font5x7.setTextColor(BLACK);
  locate(2, 1);
  font5x7.print(F("Action"));
//  arduboy.setTextBackground(BLACK);
  font5x7.setTextColor(WHITE);
  locate(1, 2);
  font5x7.print(F("  use          "));
  locate(1, 3);
  font5x7.print(F("  throw        "));
  locate(1, 4);
  font5x7.print(F("  drop         "));
  locate(1, 5);
  font5x7.print(F("               "));
//  arduboy.print(F("  save and quit"));
//  locate(1, 6);
//  arduboy.print(ii[st] / 16);
//  arduboy.print(F(" "));
//  arduboy.print(ii[st] % 16);
//  arduboy.print(F("   "));
  locate(1, curs + 2);
  font5x7.print('>');

  arduboy.display();
  byte ex = 0;
  do {
    byte a = inputWait();
    switch (a) {
      case 2:
        if (curs > 0) {
          locate(1, curs + 2);
          font5x7.print(' ');
          curs--;
          locate(1, curs + 2);
          font5x7.print('>');
          arduboy.display();
        }
        break;
      case 4:
        if (curs < 2) {
          locate(1, curs + 2);
          font5x7.print(' ');
          curs++;
          locate(1, curs + 2);
          font5x7.print('>');
          arduboy.display();
        }
        break;
      case 5:
        if(curs==0){
          if(hslep == 0) {
            useItem(st);
            sortItem();
            moveMonst();
            tweatHero();
          } else {
            mess(22);
          }
          ex=1;
        } else if(curs==1){
          if(hslep == 0) {
            throwItem(st);
            sortItem();
          } else {
            mess(22);
          }  
          ex=1;
        } else if(curs==2){
          if(hslep == 0){
            dropItem(hx, hy, st);
            sortItem();
            moveMonst();
            tweatHero();
          } else {
            mess(22);
          }
          ex=1;
//        } else if(curs==3){
//          saveStatus();
//          gstate=2;
//          ex=1;
        }
        break;
      case 6:
        ex = 1;
        break;
    }
  } while (ex == 0);
  return 1;
}

void showStatus() {
  byte h = 0;
  if (hx < 10) {
    h = 11;
  }
  if(hblnd==0) drawMap();
  drawHero();
  if(hblnd==0) drawThing();
  if(hblnd==0) drawMonst();

//  arduboy.setTextBackground(WHITE);
  arduboy.fillRect(h*6,0,60,8,WHITE);
  font5x7.setTextColor(BLACK);
  locate(h+2, 0);
  font5x7.print(F("Status"));
//  arduboy.setTextBackground(BLACK);
  font5x7.setTextColor(WHITE);
  for (int i = 1; i < 8; i++) {
    locate(h, i);
    font5x7.print(F("          "));
  }
  locate(h, 1);
  font5x7.print(F("Lv;"));
  font5x7.print(dlv);
  locate(h, 2);
  font5x7.print(F("Au;"));
  font5x7.print(au);
  locate(h, 3);
  font5x7.print(F("Hp;"));
  font5x7.print(hp);
  font5x7.print('~'); //replacement for slash
  font5x7.print(hpm);
  locate(h, 4);
  font5x7.print(F("St;"));
  font5x7.print(st);
  font5x7.print('~'); //replacement for slash
  font5x7.print(stm);
  locate(h, 5);
  font5x7.print(F("AC;"));
  byte a=equip(4,1);
  byte ac=0;
  if(a==0){
    ac=0;
  } else {
    ac=pgm_read_byte(astat + ii[a-1] % 16 ) + i2[a-1];
  }
  font5x7.print((int)ac);
  locate(h, 6);
  font5x7.print(F("Ex;"));
  font5x7.print(lv);
  font5x7.print('~'); //replacement for slash
  locate(h + 3, 7);
  font5x7.print(ex);
}

void search() {
  for (int i = hx - 1; i <= hx + 1; i++) {
    for (int j = hy - 1; j <= hy + 1; j++) {
      if (dungeon[i][j] >= 31 && dungeon[i][j] <= 106) {
        dungeon[i][j] = dungeon[i][j] + 80;
      } else if (dungeon[i][j] >= 221 && dungeon[i][j] <= 226) {
        dungeon[i][j] = dungeon[i][j] - 200;
      } else if (dungeon[i][j] == 228) {
        dungeon[i][j] = dungeon[i][j] - 220;
      } else if (dungeon[i][j] >= 231 && dungeon[i][j] <= 236) {
        dungeon[i][j] = dungeon[i][j] - 210;
      }
    }
  }
}

