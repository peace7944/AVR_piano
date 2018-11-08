for(int x=0;x<8;x++){
  for(int y=0;y<8;y++){
    if(dotMatrix[x][7-y] == 1) display[x] = dixplay[x] | (dotMatrix[x][7-y] << y);
    if(dotMatrix[x][7-y] == 2) display[x] = dixplay[x] | (dotMatrix[x][7-y] << y);
  }
}