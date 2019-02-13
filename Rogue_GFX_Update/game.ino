void title() {
  arduboy.setRGBled(0, 0, 0);
  locate(6, 2);
  font5x7.print(F("@ Rogue"));
  locate(5, 5);
  font5x7.print(F("A] New Game"));
  //locate(5, 6);
  //font5x7.print(F("B] Continue"));
  if ((millis() / 300) % 2 == 0) {
    locate(13, 2);
    font5x7.print('"');
  } else {
    locate(13, 2);
    font5x7.print(' ');
  }

  if (arduboy.justPressed(A_BUTTON)) {
    initTable();
    initHero();
    clearKnown();
    buildDungeon();
    mess(0);
    //    clearDungeon();
    //    makeDungeon4();
    //    placeMonst();
    //    placeThing();
    //    mess(0);
    //    addBuf( dlv );
    welc = 1;
    gstate = 1;
  }
  //if (arduboy.justPressed(B_BUTTON) && welc == 1) {
    //gstate = 1;
  //}
}

void gameover() {
  wiz = 0;
  adepth = 26;
  hp = hpm;
  hh = 400;


  locate(5, 1);
  font5x7.print(F("(  R I P  ("));
  locate(4, 3);
  font5x7.print(F("_   Hero    _"));


  if (death == 0) {
    locate(7, 5);
    font5x7.print(F("Starve"));
  } else if (death == 1) {
    locate(7, 5);
    font5x7.print(F("Frozen"));
  } else if(death==2){
    locate(7, 4);
    font5x7.print(F("lack of"));
    locate(8, 5);
    font5x7.print(F("luck"));
  } else if(death==3){
    locate(7, 4);    
    font5x7.print(F("hellfire"));
  } else {
    locate(7, 4);
    font5x7.print(F("Killed"));
    locate(8, 5);
    font5x7.print(F("by"));
    locate(11, 5);
    font5x7.print((char)pgm_read_byte(mname + death - 4));
  }
  locate(11 - digits(au), 6);
  font5x7.print(F("$"));
  font5x7.print(au);
  if (arduboy.justPressed(A_BUTTON)) {
    rank = checkHiScore();
    gstate = 4;
  }
}

byte digits(long int num) {
  byte ans = 1;
  while (num > 10) {
    ans++;
    num /= 10;
  }
  return ans;
}

void winner() {
  wiz = 0;
  adepth = 26;
  welc = 0;


  locate(0, 1);
  font5x7.print(F("   , CONGRATULATION ,   "));
  locate(0, 2);
  font5x7.print(F("YOU MADE IT OUT WITH THE"));
  locate(0, 3);
  font5x7.print(F("    AMULET OF YENDOR    "));



  if (arduboy.justPressed(A_BUTTON)) {
    rank = checkHiScore();
    gstate = 4;
  }
}

void score() {
  //  byte rank = checkHiScore();

  locate(4, 0);
  font5x7.print(F("Hall Of Fame"));
;
  //locate(12, 7);
  //font5x7.print(F("B]Clear"));

  for (int i = 0; i < 5; i++) {
    if (rank == i + 1) {
//      arduboy.setTextBackground(WHITE);
      arduboy.fillRect(0,(2+i)*8,128,8,WHITE);
      font5x7.setTextColor(BLACK);
    } else {
//      arduboy.setTextBackground(BLACK);
      font5x7.setTextColor(WHITE);
    }
//    locate(0, 2 + i);
//    font5x7.print(F("                     "));
    locate(1, 2 + i);
    font5x7.print(i + 1);
    locate(3, 2 + i);
    font5x7.print(glory[4 - i].gold);
    locate(14, 2 + i);
    if (glory[4 - i].depth == 255) {
      font5x7.print(F("Win ,"));
    } else {
      font5x7.print(glory[4 - i].depth);
    }
  }
//  arduboy.setTextBackground(BLACK);
  font5x7.setTextColor(WHITE);

  if (arduboy.justPressed(A_BUTTON)) {
    gstate = 0;
  }
  if (arduboy.justPressed(UP_BUTTON) && arduboy.justPressed(DOWN_BUTTON)) {
    for (int i = 0; i < 5; i++) {
      glory[i] = {0, 0};
    }
    clearHiScore();
  }
}

byte checkHiScore() {
  byte result = 0;
  if (dlv == 0) dlv = 255;
  if (glory[0].gold < au) {
    glory[0] = {au, dlv};
    for (int i = 0; i < 5; ++i) {
      for (int j = i + 1; j < 5; ++j) {
        if ( glory[i].gold > glory[j].gold ) {
          tglory = glory[i];
          glory[i] = glory[j];
          glory[j] = tglory;
        }
      }
    }
    saveHiScore();
    for (int i = 0; i < 5; i++) {
      if (glory[i].gold == au) {
        result = 5 - i;
      }
    }
  }
  return result;
}

void gameloop() {
  byte mm, r;

  if (arduboy.justPressed(LEFT_BUTTON)) {
    heroMove(1);
  }

  if (arduboy.justPressed(RIGHT_BUTTON)) {
    heroMove(3);
  }

  if (arduboy.justPressed(UP_BUTTON)) {
    heroMove(2);
  }

  if (arduboy.justPressed(DOWN_BUTTON)) {
    if (arduboy.buttonsState() == 24) {
      ss = 1;
    } else {
      heroMove(4);
    }
  }

  if (arduboy.justReleased(A_BUTTON)) {
    if (ss == 1) {
      ss = 0;
    } else {
      if (dungeon[hx][hy] >= 11 && dungeon[hx][hy] <= 16) {
        hmdet = 0;
        hisee = 0;
        if (ii[im - 1] == 144) {
          dlv--;
          if (dlv == 0) {
            gstate = 3;
          }
        } else {
          dlv++;
        }
        buildDungeon();
        //      clearDungeon();
        //      makeDungeon4();
        //      placeMonst();
        //      placeThing();
        //      mess(0);
        //      addBuf(dlv);
      } else {
        //      ss = 1;
//        clearBuf();
        search();
        wakeUp();
        tweatHero();
        moveMonst();
      }
    }
  }

  if (arduboy.justPressed(B_BUTTON)) {
    ss = 0;
    clearBuf();
    inventry(0);
  }

  makeKnown();
  if (hblnd == 0) drawMap();
  drawHero();
  if (hblnd == 0) drawThing();
  if (hblnd == 0) drawMonst();
  if (ss == 1) {
    showStatus();
  }
  showMsg();
}

void buildDungeon() {
  clearDungeon();
  makeDungeon4();
  placeMonst();
  placeThing();
  //  mess(0);
  //  addBuf((char)dlv);
}

void heroMove(byte dir) {
  if (hconf > 0) {
    dir = random(4) + 1;
  }
  char dx = (dir - 2) * (dir % 2);
  char dy = (dir - 3) * ((dir - 1) % 2);
  byte mm, r;

  if (hslep > 0) {
    dx = 0;
    dy = 0;
  }
  ss = 0;
  if (monst[hx + dx][hy + dy] == 0) {
    if ((hy + dy) <= 7 && (hy + dy) >= 0 && (hx + dx) >= 0 && (hx + dx) <= 20
        && dungeon[hx + dx][hy + dy] >= 1 && dungeon[hx + dx][hy + dy] <= 200) {
      if (hheld == 0) {
        hx = hx + dx;
        hy = hy + dy;
      }
      clearBuf();
      if (hlevi == 0) {
        checkThing(hx, hy);
        if(dungeon[hx][hy] >= 31 && dungeon[hx][hy] <= 106){
          dungeon[hx][hy] += 80;
        }
        if(dungeon[hx][hy] >= 111 && dungeon[hx][hy] <= 186){
          traped( dungeon[hx][hy]/10-11 );
        }
      }
    }
  } else {
    mm = monst[hx + dx][hy + dy];
    r = ms[mm - 1] % 32;
    clearBuf();
    hitMonst(mm, r, dx, dy);
  }
  wakeUp();
  tweatHero();
  if (hfast > 0) {
    if (ht % 2 == 0) {
      moveMonst();
    }
  } else {
    moveMonst();
  }
}

// bear?

void traped(byte vari){
  byte dmg=0;
  if(random(2)==0){
    flashHero();
  
    switch (vari){
      case 0:     //door
        dlv++;
        buildDungeon();
        break;
      case 1:     //arrow
        dmg = random(3)+1;
        charon(dmg, 2);
        break;
      case 2:     //sleep
        if(hslep==0) hslep=5;
        break;
      case 3:     //telport
        teleportHero();
        break;
      case 4:     //poison
        if (st > 3 || hasRing(5) == 0) st--;
        break;
      case 5:     //rust
        byte eq = equip(4, 1);
        if ( equip(4, 1) != 0 && bitRead(i4[eq - 1], 3) == 0) {
          if (hasRing(9) == 0) {
            i2[eq - 1]--;
          }
        }
        break;
    }
  }
  for(int i=0; i<8; i++){
    gbuf[i]=pgm_read_byte(trap[vari]+i);
  }
  addBuf(" trap");
}

void charon(byte dmg, byte reason){
  if( hp <= dmg ) {
    death = reason;
    gstate = 2;
  } else {
    hp=hp-dmg;
  }
}
// 0 :steave
// 1 :frozen
// 2 :lack of luck
// 3 :hellfire
// 4-:killed by X

