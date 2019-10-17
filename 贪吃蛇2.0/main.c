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

unsigned char WinIndex = 0;
unsigned char code WinPicture[24][8] = {
	{0xFF,0xEF,0xEF,0xDF,0xDF,0x3F,0xBF,0xFF},
	{0xFF,0xF7,0x77,0x6F,0x6F,0x9F,0xDF,0xFF},
	{0xFF,0xFB,0xBB,0xB7,0xB7,0x4F,0xEF,0xFF},
	{0xFF,0xFD,0xDD,0xDB,0xDB,0x27,0x77,0xFF},
	{0xFF,0xFE,0xEE,0x6D,0x6D,0x93,0xBB,0xFF},
	{0xFF,0x7F,0x77,0xB6,0xB6,0xC9,0xDD,0xFF},
	{0xFF,0xBF,0xBB,0xDB,0xDB,0xE4,0xEE,0xFF},
	{0xFF,0x5F,0xDD,0xED,0xED,0xF2,0x77,0xFF},
	{0xFF,0x2F,0x6E,0x76,0x76,0x79,0x3B,0xFF},
	{0xFF,0x17,0xB7,0xBB,0xBB,0xBC,0x1D,0xFF},
	{0xFF,0x8B,0xDB,0xDD,0xDD,0xDE,0x8E,0xFF},
	{0xFF,0x45,0x6D,0x6E,0x6E,0x6F,0x47,0xFF},
	{0xFF,0xA2,0x36,0xB7,0xB7,0xB7,0xA3,0xFF},
	{0xFF,0xD1,0x9B,0x5B,0xDB,0xDB,0xD1,0xFF},
	{0xFF,0xE8,0xCD,0xAD,0x6D,0xED,0xE8,0xFF},
	{0xFF,0xF4,0xE6,0xD6,0xB6,0x76,0xF4,0xFF},
	{0xFF,0x7A,0x73,0x6B,0x5B,0x3B,0x7A,0xFF},
	{0xFF,0xBD,0xB9,0xB5,0xAD,0x9D,0xBD,0xFF},
	{0xFF,0xDE,0xDC,0xDA,0xD6,0xCE,0xDE,0xFF},
	{0xFF,0xEF,0xEE,0xED,0xEB,0xE7,0xEF,0xFF},
	{0xFF,0xF7,0xF7,0xF6,0xF5,0xF3,0xF7,0xFF},
	{0xFF,0x7B,0x7B,0xFB,0xFA,0xF9,0xFB,0xFF},
	{0xFF,0xBD,0xBD,0x7D,0x7D,0xFC,0xFD,0xFF},
	{0xFF,0xDE,0xDE,0xBE,0xBE,0x7E,0x7E,0xFF}
};
unsigned char LoseIndex = 0;
unsigned char code LosePicture[24][8] = {
	{0xFF,0xEF,0xEF,0xEF,0xEF,0xEF,0x0F,0xFF},
	{0xFF,0xF7,0xF7,0xF7,0xF7,0xF7,0x87,0xFF},
	{0xFF,0xFB,0x7B,0x7B,0x7B,0x7B,0xC3,0xFF},
	{0xFF,0x7D,0xBD,0xBD,0xBD,0xBD,0x61,0xFF},
	{0xFF,0x3E,0xDE,0xDE,0xDE,0xDE,0x30,0xFF},
	{0xFF,0x1F,0xEF,0xEF,0xEF,0xEF,0x18,0xFF},
	{0xFF,0x8F,0x77,0x77,0x77,0x77,0x8C,0xFF},
	{0xFF,0xC7,0xBB,0xBB,0xBB,0xBB,0xC6,0xFF},
	{0xFF,0xE3,0x5D,0x5D,0xDD,0xDD,0x63,0xFF},
	{0xFF,0x71,0xAE,0xAE,0x6E,0xEE,0x31,0xFF},
	{0xFF,0x38,0xD7,0xD7,0x37,0xF7,0x18,0xFF},
	{0xFF,0x1C,0xEB,0xEB,0x9B,0x7B,0x8C,0xFF},
	{0xFF,0x8E,0xF5,0xF5,0xCD,0xBD,0xC6,0xFF},
	{0xFF,0x47,0x7A,0x7A,0x66,0x5E,0x63,0xFF},
	{0xFF,0x23,0xBD,0x3D,0xB3,0xAF,0x31,0xFF},
	{0xFF,0x11,0xDE,0x1E,0xD9,0xD7,0x18,0xFF},
	{0xFF,0x08,0xEF,0x0F,0xEC,0xEB,0x0C,0xFF},
	{0xFF,0x84,0xF7,0x87,0xF6,0xF5,0x86,0xFF},
	{0xFF,0xC2,0xFB,0xC3,0xFB,0xFA,0xC3,0xFF},
	{0xFF,0xE1,0xFD,0xE1,0xFD,0xFD,0xE1,0xFF},
	{0xFF,0xF0,0xFE,0xF0,0xFE,0xFE,0xF0,0xFF},
	{0xFF,0x78,0x7F,0x78,0x7F,0x7F,0x78,0xFF},
	{0xFF,0xBC,0xBF,0xBC,0xBF,0xBF,0x3C,0xFF},
	{0xFF,0xDE,0xDF,0xDE,0xDF,0xDF,0x1E,0xFF},
};
unsigned char code LedNum[17] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
								0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E, 0x7F};
unsigned char LedBuff[2] = {0xC0, 0xC0};	//��ΪҪ�䳤�����64��

unsigned char RefreshFrequency = 500;	//ˢ��Ƶ�ʣ�������Ϸ�ٶȣ�Ĭ��500ms
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

struct Position
{
	unsigned char x, y;	//x�� y��
};
unsigned char Tail = 2;	//β��λ��
struct Position body[64] = {
	{4,1},{5,1},{6,1}
	//ͷ ���� β
};
struct Position Food = {1,6};	//Ĭ��ʳ��λ�� 
struct Position LastTail;	//�ųԵ���ʳ��

char toward[4][2] = {
	{-1,0},{1,0},{0,-1},{0,1}
	//��������
};
char NowToward = 0;	//Ĭ������
//��ǰ����״̬
bit KeyStart = 1;
bit KeyUp = 1;
bit KeyDown = 1;
bit KeyLeft = 1;
bit KeyRight = 1;
//��Ӯ
bit Win = 0;
bit Lose = 0;

void LedScan();	//ɨ��led
void KeyScan();	//ɨ�����

void main()
{
	char ttt = 0;	//ֻ�Ǹ���ʱ����
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
        if (LedCnt >= RefreshFrequency && start)  //�ж�0.5�붨ʱ��־����������Ϊ��ֹ��ͣʱledcnt���ڼӣ�  Ĭ��0.5s��һ�λ���
        {
            //0.5�붨ʱ��־����
			LedCnt = 0;
			if(Lose)
			{
				for(ttt = 0; ttt < 8; ttt++)
				{
					NowPicture[ttt] = LosePicture[LoseIndex][ttt];
				}
				++LoseIndex;
				if(LoseIndex == 24) LoseIndex = 0;
			}
			else if(Win)
			{
				for(ttt = 0; ttt < 8; ttt++)
				{
					NowPicture[ttt] = WinPicture[WinIndex][ttt];
				}
				++WinIndex;
				if(WinIndex == 24) WinIndex = 0;
			}
			else
			{
				LastTail = body[Tail];
				//Ϩ���β��
				NowPicture[body[Tail].x] = 1 << body[Tail].y | NowPicture[body[Tail].x];
				
				//�ƶ���
				for(ttt = Tail; ttt > 0; --ttt)
				{
					body[ttt] = body[ttt - 1];
				}
				//������ͷ��
				body[0].x = body[0].x + toward[NowToward][0];
				body[0].y = body[0].y + toward[NowToward][1];
				if(body[0].x == -1)	body[0].x = 7;
				if(body[0].x == 8)	body[0].x = 0;
				if(body[0].y == -1)	body[0].y = 7;
				if(body[0].y == 8)	body[0].y = 0;	
				
				//�Ե�ʳ��
				if(body[0].x == Food.x && body[0].y == Food.y)
				{
					//������
					body[++Tail] = LastTail;
					NowPicture[body[Tail].x] = ~(1 << body[Tail].y) & NowPicture[body[Tail].x];
					
					score++;
					if(score == 64)
					{
						Win = 1;
						continue;
					}
					//��ʳ��λ�� ��T1��ʱ������
					do
					{
						Food.x = TL1 % 8;
						Food.y = TH1 % 8;
					}while(!(NowPicture[Food.x] & (1 << Food.y)));	//����������
					//Ϩ���ʳ���ֹ������Ϊ��ײ���Լ�
					NowPicture[Food.x] = 1 << Food.y | NowPicture[Food.x];
					//����ʳ��
					NowPicture[Food.x] = ~(1 << Food.y) & NowPicture[Food.x];
					
				}
				//���ײ��������
				for(ttt = 1; ttt <= Tail; ttt++)
				{
					if(body[0].x == body[ttt].x && body[0].y == body[ttt].y)
					{
						Lose = 1;
						score = 0;
					}
				}
				/*��֪��Ϊɶû��
				if(NowPicture[body[0].x] & (1 << body[0].y) == 0)
				{
					Lose = 1;
					score = 0;
				}*/
				//������ͷ��
				NowPicture[body[0].x] = ~(1 << body[0].y) & NowPicture[body[0].x];
				
				//���´��뽫score��ʮ����λ�ӵ͵���������ȡ��תΪ�������ʾ�ַ�
				LedBuff[0] = LedNum[score%10];
				LedBuff[1] = LedNum[score/10%10]; 
			}				
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
	if(index == 10)	index = 0;	//ѭ��
    if (index < 2)  //ˢ�¼Ʒְ�
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
		P1 = index - 2;	//ѡ������
		P0 = NowPicture[index - 2];
	}
}

// ����ɨ�躯�������ڶ�ʱ�ж��е��ã��Ƽ����ü��1ms 
void KeyScan()
{
	static unsigned char KeyIndex = 0;
	//ɨ�軺��������һ��ʱ���ɨ��ֵ,�������ҿ�ʼ
    static unsigned char KeyUpBuf = 0xFF;
	static unsigned char KeyDownBuf = 0xFF;
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
			KeyDownBuf = (KeyDownBuf << 1) | KEYTOWARD;
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
	if(KeyUpBuf == 0x00 && NowToward != 1)
	{
		//RefreshFrequency = NowToward == 0 ? 250 : 500;
		NowToward = 0;
	}
	else if(KeyDownBuf == 0x00 && NowToward != 0)
	{
		NowToward = 1;
	}
	else if(KeyLeftBuf == 0x00 && NowToward != 3)
	{
		NowToward = 2;
	}
	else if(KeyRightBuf == 0x00 && NowToward != 2)
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

