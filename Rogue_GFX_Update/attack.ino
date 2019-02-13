void hitMonst(byte mm, byte r, char dx, char dy) { //mm=monst[x][y](1 to 16) r=kind(0 to 25
  byte rr = random(100);
  byte dmg = 0;
  byte w = equip(3, 1);
  byte hdex = 0, hdmg = 0;
  if (w != 0) {
    hdex = pgm_read_byte(wstat[ii[w - 1] % 16]) + i2[w - 1];
    hdmg = pgm_read_byte(wstat[ii[w - 1] % 16 + 1]) + i3[w - 1];
  }
  byte prob = 40 + hdex * 3 + lv * 2;

  if (rr < prob) {
    flashMonst(mm - 1);
    dmg = (random(hdex, hdex * hdmg) * 2 + strToDmg(st + rstr) * 2 + rdex + lv + 1) / 2;
    checkMonst(mm - 1, r, dmg, hx+dx, hy+dy);
  }
}

void checkMonst(byte m, byte r, byte dmg, byte x, byte y) { //m=id(0...15), r=vari, dmg, hitpos x,y
  if (mh[m] <= dmg) {
    monst[x][y] = 0;
    ms[m] = 0;
    if(r>=22){
      ex = ex + pgm_read_byte(mstat[r] + 4)*100;
    } else {
      ex = ex + pgm_read_byte(mstat[r] + 4);
    }
    if (r == 15) {
      hheld = 0;
    }
    if (pgm_read_byte(mstat[r] + 5) >= random(100)+1) {
      if(r==9){
        placeThingXY(x, y, 1);
      } else {
        placeThingXY(x, y, 0);
      }
    }
  } else {
    mh[m] = mh[m] - dmg;
    if (ms[m] / 32 > 1) {
      ms[m] = 32 + ms[m] % 32;
    }
  }
}

void hitHero(byte i, byte r) { //i=kind(0 to 25 r=ID(0 to 15)
  byte prob = pgm_read_byte(mstat[i] + 3) - lv * 2 - rdex * 2;
  byte rr = random(100);
  byte dmg = 0;
  byte a = equip(4, 1);
  byte ac = 0;
  if (a == 0) {
    ac = 0;
  } else {
    ac = pgm_read_byte(astat + ii[a - 1] % 16 ) + i2[a - 1];
  }

  if (rr < prob) {
    dmg = (random(pgm_read_byte(mstat[i] + 1), pgm_read_byte(mstat[i] + 2)) * (100 - ac * 3)) / 100;
//    if (hp <= dmg) {
//      death=i+2;
//      gstate = 2;
//    } else {
//      flashHero();
//      hp = hp - dmg;
    flashHero();
    charon(dmg, i+4); 
      if (bitRead(m1[r], 3) == 1) {
        specialAttack( i ,r );
//      }
    }
  } 
}

void specialAttack(byte mon, byte id) {  //mon=0 to 25 mon vari, @Pharas sharp eye

  bool hit = false;
  byte eq, ac, prob;
  switch (mon) {
    case 5:     //IceMon
      if (random(5) == 0) {
        hit = true; //flashHero();
        mess(13);
        hslep = random(5) + 4;
        if (random(20) == 0) {
//          hp = 0;
//          death=1;
          byte dmg=hp;
          charon(dmg,1);
        }
      }
      break;
    case 6:     //R.snake
      if (st > 3 || hasRing(5) == 0) {
        if (random(5) == 0) {
          hit = true; //flashHero();
          mess(14);
          st--;
        }
      }
      break;
    case 9:     //Leprchaun
      if ( au > 50 && random(10) != 0 ) {
        hit = true; //flashHero();
        mess(15);
        au = au - random(50);
        ms[id] += 6*32;
      }
      break;
    case 12:    //Aquator
      eq = equip(4, 1);
      if ( equip(4, 1) != 0 && bitRead(i4[eq - 1], 3) == 0) {
        if (hasRing(9) == 0) {
          hit = true; //flashHero();
          mess(16);
          i2[eq - 1]--;
        }
      }
      break;
    case 13:    //Nymph
      if (random(2) == 0) {
        byte t = random(20);
        if (bitRead(i4[t], 4) == 0) {
          hit = true; //flashHero();
          mess(15);
          deleteItem(t);
          ms[id] += 6*32;
        }
      }
      break;
    case 15:    //Flytrap
      if (hlevi == 0) {
        hit = true; //flashHero();
        mess(17);
        hheld = 1;
      }
      break;
    case 17:    //Wraith
      if (lv > 5 && random(5) == 0) {
        hit = true; //flashHero();
        mess(20);
        nl = nl / 2;
        ex = nl - 1;
        lv--;
        hpm = hpm - 3 - random(7);
        if (hp > hpm) hp = hpm;
      }
      break;
    case 22:    //Vampire
      if (random(10) < 4) {
        hit = true; //flashHero();
        mess(21);
        byte r = random(3);
        if (r % 2 == 0) {
          if (hasRing(5) == 0 || st > 5) {
            st--;
          }
        }
        if (r > 0) {
          if (hp > 9) {
            hp--;
            hpm--;
          }
        }
      }
      break;
  }
  if(hit) flashHero();
}

