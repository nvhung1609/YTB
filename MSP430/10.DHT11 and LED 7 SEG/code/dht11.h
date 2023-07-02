
#define DHT11_DIR 		P1DIR
#define DHT11_OUT_PORT		P1OUT
#define DHT11_IN_PORT           P1IN
#define DHT11_PIN 		BIT3

#define DHT11_DIR_OUT()		do{DHT11_DIR |= DHT11_PIN;}while(0)
#define DHT11_DIR_IN()		do{DHT11_DIR &= ~DHT11_PIN;}while(0)
#define DHT1_IN()		(DHT11_IN_PORT & DHT11_PIN)
#define DHT11_OUT_LOW()		do{DHT11_OUT_PORT &= ~DHT11_PIN;}while(0)
#define DHT11_OUT_HIGH()	do{DHT11_OUT_PORT |= DHT11_PIN;}while(0)

unsigned char nhietDo = 0, doAm = 0, check_sum;

unsigned char readDHT11(void);

unsigned char readDHT11(void){
  unsigned timeOut = 0;
  unsigned char buffer[5]={0,0,0,0,0};//khung du lieu tra ve cua DHT11
  int i,j;
  DHT11_DIR_OUT();
  DHT11_OUT_HIGH();
  __delay_cycles(60);
  DHT11_OUT_LOW();
  __delay_cycles(18000);
  DHT11_OUT_HIGH();
  DHT11_DIR_IN();
  __delay_cycles(35);//
  timeOut = 0;
  if(DHT1_IN())
    return 0;
  else
    while(!DHT1_IN()){ //doi Data len 1
      if(++timeOut >1000)
        return 0;
    }
  __delay_cycles(60);
  timeOut = 0;
  if(!DHT1_IN())
    return 0;
  else
    while(DHT1_IN()){ //doi Data xuong 0
      if(++timeOut >1000)
        return 0;
    } 
  
  //doc du lieu
  
  for(i=0;i<5;i++){
    for(j=0;j<8;j++){
      timeOut = 0;
      while(!DHT1_IN()){ // doi len 1
        if(++timeOut >1000)
          return 0;
      }
      __delay_cycles(28);
      timeOut = 0;
      if(DHT1_IN()){
        buffer[i]|=(1<<(7-j));
        while(DHT1_IN()){
          if(++timeOut >1000)
            return 0;
        }
      }
    }
  }
  DHT11_DIR_OUT();
  DHT11_OUT_HIGH();
  doAm = buffer[0];
  nhietDo = buffer[2];
  check_sum = doAm + nhietDo;
  if(check_sum != buffer[4])
    return 0;
  
  return 1;
}
