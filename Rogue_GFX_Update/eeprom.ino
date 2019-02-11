void saveHiScore(){
  for(int i=0; i<5; i++){
    EEPROM.put(100+i*5, glory[i]);
  }
}

void loadHiScore(){
  for(int i=0; i<5; i++){
    EEPROM.get(100+i*5, glory[i]);
  }
}

void clearHiScore(){
  for(int i=0; i<25; i++){
    EEPROM.write(100+i, 0);
  }  
}

