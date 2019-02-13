void flashHero(){
  if(hblnd==0) {
    drawMap();
    drawThing();
    drawMonst();
  }
//  arduboy.setTextBackground(WHITE);
  arduboy.fillRect(hx*6+1, hy*8, 6,8,WHITE);
  font5x7.setTextColor(BLACK);
  locate(hx, hy);
  font5x7.print('@');
  arduboy.display();
  delay(100);
//  arduboy.setTextBackground(BLACK);
  font5x7.setTextColor(WHITE);
}

void flashMonst(byte num){
  if(hblnd==0) {
    drawMap();
    drawThing();
    drawMonst();
  }
//  arduboy.setTextBackground(WHITE);
  arduboy.fillRect(mx[num]*6+1, my[num]*8, 6,8,WHITE);
  font5x7.setTextColor(BLACK);
  locate(mx[num], my[num]);
  if(hblnd == 0 && bitRead(m1[num],6)==0){
    font5x7.print((char)pgm_read_byte(mname+(ms[num] % 32)));
  } else {
    font5x7.print(' ');    
  }
  arduboy.display();
  delay(100);
//  arduboy.setTextBackground(BLACK);
  font5x7.setTextColor(WHITE);
}

void initHero(){

  for(int i=0; i<IMAX; i++){
    deleteItem(i);
//    ii[i]=0;
//    i1[i]=0;
//    i2[i]=0;
//    i3[i]=0;
//    i4[i]=0;
  }

  hx = 0, hy = 0, 
  
  im = 5, dlv = 1, st = 16, stm = 16, lv = 1;

  hconf = 0, hblnd = 0, hhall = 0, hfast = 0, hslep = 0;
  hmdet = 0, hisee = 0, hlevi = 0, hheld = 0;
  rdex = 0, rstr = 0;

  au = 0, hp = 16, hpm = 16, ex = 0, ht = 0, hh = 400, nl = 10;

  ii[0] = 2 * 16 + 0; i1[0] =  1; i2[0] = 0; i3[0] = 0; i4[0] = 0b10000000;
  ii[1] = 3 * 16 + 0; i1[1] =  1; i2[1] = 1; i3[1] = 1; i4[1] = 0b00110000;
  ii[2] = 3 * 16 + 3; i1[2] =  1; i2[2] = 1; i3[2] = 0; i4[2] = 0b00100000;
  ii[3] = 3 * 16 + 5; i1[3] = 30; i2[3] = 0; i3[3] = 0; i4[3] = 0b10100000;
  ii[4] = 4 * 16 + 1; i1[4] =  1; i2[4] = 1; i3[4] = 0; i4[4] = 0b00110000;
//  ii[5] = 6 * 16 + findScroll(11); i1[5] = 5; i2[5] = 0; i3[5] = 0; i4[5] = 0b10000000;

}

void initTable(){
  const byte vari[4] = {POMAX, SCMAX, RGMAX, WDMAX};
  for (int v = 0; v < 4; v++) {
    for (int i = 0; i < 50; i++) {
      byte r1 = random(vari[v]);
      byte r2 = random(vari[v]);
      byte tmp = ttab[v][r1];
      ttab[v][r1] = ttab[v][r2];
      ttab[v][r2] = tmp;
    }
  }
  for(int i=0; i<4; i++){
    tknow[i]=0;
  }
}

