#include<reg52.h>

sbit KEY_OUT_1 = P2^3;
sbit KEY_OUT_2 = P2^2;
sbit KEY_OUT_3 = P2^1;
sbit KEY_OUT_4 = P2^0;
sbit KEYSTART = P2^6;
sbit KEYTOWARD = P2^7;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char code LedNum[17] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
								0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E, 0x7F};
unsigned char LedBuff[4] = {0xC0, 0xC0, 0xC0, 0xC0};

unsigned int LedCnt = 0;	//��¼T0�жϴ��� 
unsigned int score = 0;		//��ǰ�÷�
bit start = 0;	//�ж��Ƿ�ʼ��0Ϊ��ͣ 1Ϊ��ʼ/����

unsigned char NowPicture[8] = {0xFF, 0xBF, 0xFF, 0xFF, 
								0xFD, 0xFD, 0xFD, 0xFF};	//��ǰˢ���д���P0ֵ
/*
0Ϊ������NowPicture��ͬ
unsigned char map[8][8] = {
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,0,1},
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1},
	{1,0,1,1,1,1,1,1},
	{1,0,1,1,1,1,1,1},
	{1,0,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1}
};*/
unsigned char FoodPosition[2] = {1,6};	//Ĭ��ʳ��λ�� ���������к�
unsigned int body[3][2] = {
	{4,1},{5,1},{6,1}
	//ͷ ���� β
};
char toward[4][2] = {
	{-1,0},{1,0},{0,-1},{0,1}
	//��������
};
char NowToward = 0;	//Ĭ������
//��ǰ����״̬
bit KeyUp = 1;
bit KeyDown = 1;
bit KeyLeft = 1;
bit KeyRight = 1;
bit KeyStart = 1;

void LedScan();	//ɨ��led
void KeyScan();	//ɨ�����

void main()
{
    EA = 1;       //ʹ�����ж�
    ENLED = 0;    //ʹ��U3��ѡ����������

    TMOD = 0x11;  //����T0 T1Ϊģʽ1
    TH0  = 0xFC;  //ΪT0����ֵ0xEC67����ʱ1ms
    TL0  = 0x67;
    ET0  = 1;     //ʹ��T0�ж�
    TR0  = 1;     //����T0
	TR1  = 1;     //����T1

	while(1)
	{
        if (LedCnt >= 500 && start)  //�ж�0.5�붨ʱ��־����������Ϊ��ֹ��ͣʱledcnt���ڼӣ�  Ĭ��0.5s��һ�λ���
        {
            //0.5�붨ʱ��־����
			LedCnt = 0;
			
			//�ƶ���
			//Ϩ���β��
			NowPicture[body[2][0]] = 1 << body[2][1] | NowPicture[body[2][0]];
			body[2][0] = body[1][0];
			body[2][1] = body[1][1];
			
			body[1][0] = body[0][0];
			body[1][1] = body[0][1];
			
			body[0][0] = body[0][0] + toward[NowToward][0];
			body[0][1] = body[0][1] + toward[NowToward][1];
			if(body[0][0] == -1)	body[0][0] = 7;
			if(body[0][0] == 8)		body[0][0] = 0;
			if(body[0][1] == -1)	body[0][1] = 7;
			if(body[0][1] == 8)		body[0][1] = 0;				
			//������ͷ��
			NowPicture[body[0][0]] = ~(1 << body[0][1]) & NowPicture[body[0][0]];
			
			//�Ե�ʳ��
			if(body[0][0] == FoodPosition[0] && body[0][1] == FoodPosition[1])
			{
				score++;
				//��ʳ��λ�� ��T1��ʱ������
				FoodPosition[0] = TL1 % 8;
				FoodPosition[1] = TH1 % 8;
			}
			
			//����ʳ��
			NowPicture[FoodPosition[0]] = ~(1 << FoodPosition[1]) & NowPicture[FoodPosition[0]];
			
			//���´��뽫score��ʮ����λ�ӵ͵���������ȡ��תΪ�������ʾ�ַ�
            LedBuff[0] = LedNum[score%10];
            LedBuff[1] = LedNum[score/10%10];
            LedBuff[2] = LedNum[score/100%10];
            LedBuff[3] = LedNum[score/1000%10];       
        }	
	}
}

// ��ʱ��0�жϷ����� 
void InterruptTimer0() interrupt 1
{
    TH0 = 0xFC;	//���¼��س�ֵ
    TL0 = 0x67;
    LedScan();
	KeyScan();
}
void LedScan()
{
	static unsigned char index = 0;		//��̬ɨ�������
	LedCnt++;	//�жϴ�������ֵ��1
	index++;		//��̬ɨ���������1
	if(index == 12)	index = 0;	//ѭ��
    if (index < 4)  //ˢ�¼Ʒְ�
    {
		ADDR3 = 1;	//ѡ�Ʒְ�
		
		//���´����������ܶ�̬ɨ��ˢ
		P0 = 0xFF;   //��ʾ����
		P1 = (P1 & 0xF8) | index;	//ѡ��λ��8 + index
		P0 = LedBuff[index];
		
    }
	else	//ˢ��led����
	{
		ADDR3 = 0;	//ѡ����	
		
		//���´�����ɵ���̬ɨ��ˢ��
		P0 = 0xFF;   //��ʾ����
		P1 = index - 4;	//ѡ������
		P0 = NowPicture[index - 4];
	}
}

// ����ɨ�躯�������ڶ�ʱ�ж��е��ã��Ƽ����ü��1ms 
void KeyScan()
{
	static unsigned char KeyIndex = 0;
	//ɨ�軺��������һ��ʱ���ɨ��ֵ,�������ҿ�ʼ
    static unsigned char KeyUpBuf = 0xFF;
	static unsigned char KeyDonwBuf = 0xFF;
	static unsigned char KeyLeftBuf = 0xFF;
	static unsigned char KeyRightBuf = 0xFF;
	static unsigned char KeyStartBuf = 0xFF;
	
	//�����������أ�����ǰɨ��ֵѹ�뻺����
	switch(KeyIndex)
	{
		case 0:
			KEY_OUT_1 = 0;
			KeyUpBuf = (KeyUpBuf << 1) | KEYTOWARD;
			KEY_OUT_1 = 1;	//��ʱ�رգ���ֹ����
			KeyIndex++;
			break;
		case 1:
			KEY_OUT_2 = 0;
			KeyLeftBuf = (KeyLeftBuf << 1) | KEYTOWARD;
			KEY_OUT_2 = 1;
			KeyIndex++;
			break;
		case 2:
			KEY_OUT_3 = 0;
			KeyDonwBuf = (KeyDonwBuf << 1) | KEYTOWARD;
			KEY_OUT_3 = 1;
			KeyIndex++;
			break;
		case 3:
			KEY_OUT_4 = 0;
			KeyRightBuf = (KeyRightBuf << 1) | KEYTOWARD;
			KEY_OUT_4 = 1;
			KeyIndex++;
			break;
		default:
			KEY_OUT_4 = 0;
			KeyStartBuf = (KeyStartBuf << 1) | KEYSTART;
			KEY_OUT_4 = 1;
			KeyIndex = 0;
			break;
	}
	
	//����8�ζ�Ϊ0,��40ms���ж�Ϊ����
	if(KeyUpBuf == 0x00)
	{
		NowToward = 0;
	}
	else if(KeyDonwBuf == 0x00)
	{
		NowToward = 1;
	}
	else if(KeyLeftBuf == 0x00)
	{
		NowToward = 2;
	}
	else if(KeyRightBuf == 0x00)
	{
		NowToward = 3;
	}
	else if(KeyStartBuf == 0x00)	//��ֹ������bug
	{
		KeyStart = 0;
	}
	else if(KeyStartBuf == 0xFF && KeyStart == 0)	//��ֹ������bug
	{
		KeyStart = 1;
		start = ~start;
	}
}

