void addBuf(char aray[]){
  byte ex=0, i=0, i1=0;
  do{
    if(gbuf[i]=='\0'){
      ex=1;
    } else {
      i++;
    }
  }while(ex==0);
  ex=0;
  i1=i;
  do{
    if(aray[i-i1]=='\0' || i >= 22){
      gbuf[21]='\0';
      ex=1;
    } else {
      gbuf[i]=aray[i-i1];
      i++;
    }
  }while(ex==0);
}

void mesToGmes(byte id){
  for(int i=0; i<10; i++){
    gbuf[i]=pgm_read_byte(mes[id]+i);
  }
}

void itmToGitm(byte type, byte r, byte k){
  const byte index[13]={0,1,3,11,18,32,44,55,65,66,80,92,103};
  if(k==0){
    for(int i=0; i<8; i++){
      gitm[i]=pgm_read_byte(nItem[index[type-1]+r]+i);
    }
  } else {
    for(int i=0; i<8; i++){
      gitm[i]=pgm_read_byte(nItem[index[type+4]+ttab[type-5][r]]+i);
    }    
  }
}

void clearBuf(){
  for(int i=0; i<22; i++){
    gbuf[i]=0;
  }
}

void mess(byte i){
  clearBuf();
  mesToGmes(i);
}

