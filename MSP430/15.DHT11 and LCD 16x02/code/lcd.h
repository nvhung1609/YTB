
void PulseLcm();
void SendByte(char ByteToSend, int IsData);
void LcmSetCursorPosition(char Row, char Col);
void ClearLcmScreen();
void InitializeLcm(void);
void PrintStr(char *Text);
void LCD_Custom_Char(unsigned char vt, unsigned char*mgs);
void ftoa(char* string,int a,int b);
void ftoa_1(char* string, unsigned int a);
void ftoa_2(char* string, unsigned int a);
void PrintChar(int m);