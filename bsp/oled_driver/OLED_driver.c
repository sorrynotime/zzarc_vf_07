/*

 * ���ͷ�ļ���oled��� [Ӳ����] ʵ���ļ�����ֲ��ʱ����Ҫ��������ļ�������

*/
#include "stm32f4xx_hal.h"
#include "OLED_driver.h"
#include "spi.h"

uint8_t OLED_DisplayBuf[64/8][128]; //�Դ�
bool OLED_ColorMode = true;
bool spi_busy = 0;

#ifdef OLED_UI_USE_HW_SPI
void OLED_Write_DATA(uint8_t data)
{
	while(spi_busy != 0);	//�ȴ�SPI����
	spi_busy = 1;

	OLED_DC_Set();    // ��������������Ϊ����ģʽ
#ifndef OLED_UI_SPI_NSS_HARD_OUTPUT
	OLED_CS_Clr();    // ѡ��OLED
#endif

	HAL_SPI_Transmit_DMA(&hspi2, &data, 1);

#ifndef OLED_UI_SPI_NSS_HARD_OUTPUT
	OLED_CS_Set();    // ȡ��ѡ��OLED
#endif
	spi_busy = 0;
}

void OLED_Write_CMD(uint8_t data)
{
	while(spi_busy != 0);	//�ȴ�SPI����
	spi_busy = 1;

	OLED_DC_Clr();    // ��������������Ϊָ��ģʽ
#ifndef OLED_UI_SPI_NSS_HARD_OUTPUT
	OLED_CS_Clr();    // ѡ��OLED
#endif

	HAL_SPI_Transmit_DMA(&hspi2, &data, 1);

#ifndef OLED_UI_SPI_NSS_HARD_OUTPUT
	OLED_CS_Set();    // ȡ��ѡ��OLED
#endif
	spi_busy = 0;
}

/**
  * ��    ����OLEDд���ݣ�Ӳ��SPI��
  * ��    ����Data Ҫд�����ݵ���ʼ��ַ
  * ��    ����Count Ҫд�����ݵ�����
  * �� �� ֵ����
  */
void OLED_WriteDataArr(uint8_t *Data, uint8_t Count)
{
	while(spi_busy != 0);	//�ȴ�SPI����
	spi_busy = 1;

	OLED_DC_Set();    // ��������������Ϊ����ģʽ
#ifndef OLED_UI_SPI_NSS_HARD_OUTPUT
	OLED_CS_Clr();    // ѡ��OLED
#endif

	HAL_SPI_Transmit_DMA(&hspi2, Data, (uint8_t)Count);

#ifndef OLED_UI_SPI_NSS_HARD_OUTPUT
	OLED_CS_Set();    // ȡ��ѡ��OLED
#endif
	spi_busy = 0;
}

#else
void OLED_Write_DATA(uint8_t data)
{
    OLED_DC_Set();    // ��������������Ϊ����ģʽ
    OLED_CS_Clr();    // ѡ��OLED

    for (uint8_t i = 0; i < 8; i++)
    {
        OLED_SCL_Clr();              // ʱ�����õͣ�׼����������λ
        if (data & 0x80)             // ������λ
            OLED_SDA_Set();          // �����1�����������߸�
        else
            OLED_SDA_Clr();          // �����0�����������ߵ�
				
        OLED_SCL_Set();              // ʱ�����øߣ�������״̬����ȡ
        data <<= 1;                  // ��������׼����һλ
    }

    OLED_CS_Set();    // ȡ��ѡ��OLED
}


/**
  * ��    ����OLEDд����
  * ��    ����Data Ҫд�����ݵ���ʼ��ַ
  * ��    ����Count Ҫд�����ݵ�����
  * �� �� ֵ����
  */
void OLED_WriteDataArr(uint8_t *Data, uint8_t Count)
{

	//CS��DC�����Ѿ���OLED_Write_DATA()��

	/*ѭ��Count�Σ���������������д��*/
	for (uint8_t i = 0; i < Count; i ++)
	{
		if(OLED_ColorMode){
			OLED_Write_DATA(Data[i]);	//���η���Data��ÿһ������
		}else{
			OLED_Write_DATA(~Data[i]);	//����Ƿ�ɫģʽ����ÿ������ȡ���ٷ���
		}
	}
}





void  OLED_Write_CMD(uint8_t data)
{	
			  
	 
	OLED_DC_Clr();	  // ��������������Ϊָ��ģʽ

	OLED_CS_Clr();    // ѡ��OLED

	for(uint8_t i = 0;i<8;i++)
	{			  
		OLED_SCL_Clr();
		if(data&0x80)
		   OLED_SDA_Set();
		else 
		   OLED_SDA_Clr();
		OLED_SCL_Set();
		data<<=1;   
	}				 		  

	OLED_CS_Set();    // ȡ��ѡ��OLED

}
#endif

//���Ժ���
void OLED_ColorTurn(uint8_t i)
{
	if(i==0)
		{
			OLED_Write_CMD(0xA6);//������ʾ
		}
	if(i==1)
		{
			OLED_Write_CMD(0xA7);//��ɫ��ʾ
		}
}

/**
  * ��    ����������Ļ��ʾ����
  * ��    ����Page 0=������ʾ��1=��Ļ���ݷ�ת180��
  * �� �� ֵ����
  * ˵    ������
  */
void OLED_DisplayTurn(uint8_t i)
{
	//������ر���Ļ��ִ��ʱ�������˸���Σ������¾��������Ҿ���
	OLED_Write_CMD(0xAE);//�ر���Ļ
	if (i == 0)
	{
		OLED_Write_CMD(0xC8); // ������ʾ
		OLED_Write_CMD(0xA1);
	}
	if (i == 1)
	{
		OLED_Write_CMD(0xC0); // ��ת��ʾ
		OLED_Write_CMD(0xA0);
	}
	OLED_Write_CMD(0xAF);//������Ļ
}

//����OLED��ʾ
void OLED_DisPlay_On(void)
{
	OLED_Write_CMD(0x8D);//��ɱ�ʹ��
	OLED_Write_CMD(0x14);//������ɱ�
	OLED_Write_CMD(0xAF);//������Ļ
}

//�ر�OLED��ʾ
void OLED_DisPlay_Off(void)
{
	OLED_Write_CMD(0x8D);//��ɱ�ʹ��
	OLED_Write_CMD(0x10);//�رյ�ɱ�
	OLED_Write_CMD(0xAE);//�ر���Ļ
}
/**
  * ��    ����OLED������ʾ���λ��
  * ��    ����Page ָ��������ڵ�ҳ����Χ��0~15
  * ��    ����X ָ��������ڵ�X�����꣬��Χ��0~127
  * �� �� ֵ����
  * ˵    ����OLEDĬ�ϵ�Y�ᣬֻ��8��BitΪһ��д�룬��1ҳ����8��Y������
  */
void OLED_SetCursor(uint8_t Page, uint8_t X)
{
	/*���ʹ�ô˳�������1.3���OLED��ʾ��������Ҫ�����ע��*/
	/*��Ϊ1.3���OLED����оƬ��SH1106����132��*/
	/*��Ļ����ʼ�н����˵�2�У������ǵ�0��*/
	/*������Ҫ��X��2������������ʾ*/
#ifdef SH1106
	X += 2;
#endif
	
	/*ͨ��ָ������ҳ��ַ���е�ַ*/
	OLED_Write_CMD(0xB0 | Page);					//����ҳλ��
	OLED_Write_CMD(0x10 | ((X & 0xF0) >> 4));	//����Xλ�ø�4λ
	OLED_Write_CMD(0x00 | (X & 0x0F));			//����Xλ�õ�4λ
}


//�����Դ浽OLED
void OLED_Update(void)
{
	uint8_t j;
	/*����ÿһҳ*/
	for (j = 0; j < 8; j ++)
	{
		/*���ù��λ��Ϊÿһҳ�ĵ�һ��*/
		OLED_SetCursor(j, 0);
		/*����д��128�����ݣ����Դ����������д�뵽OLEDӲ��*/
		OLED_WriteDataArr(OLED_DisplayBuf[j], 128);
	}

}
/**
  * ��    ������OLED�Դ����鲿�ָ��µ�OLED��Ļ
  * ��    ����X ָ���������Ͻǵĺ����꣬��Χ��0~127
  * ��    ����Y ָ���������Ͻǵ������꣬��Χ��0~127
  * ��    ����Width ָ������Ŀ�ȣ���Χ��0~128
  * ��    ����Height ָ������ĸ߶ȣ���Χ��0~127
  * �� �� ֵ����
  * ˵    �����˺��������ٸ��²���ָ��������
  *           �����������Y��ֻ��������ҳ����ͬһҳ��ʣ�ಿ�ֻ����һ�����
  * ˵    �������е���ʾ��������ֻ�Ƕ�OLED�Դ�������ж�д
  *           ������OLED_Update������OLED_UpdateArea����
  *           �ŻὫ�Դ���������ݷ��͵�OLEDӲ����������ʾ
  *           �ʵ�����ʾ������Ҫ�������س�������Ļ�ϣ�������ø��º���
  */

void OLED_UpdateArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height)
{
	uint8_t j;
	
	/*������飬��ָ֤�����򲻻ᳬ����Ļ��Χ*/
	if (X > 128-1) {return;}
	if (Y > 64-1) {return;}
	if (X + Width > 128) {Width = 128 - X;}
	if (Y + Height > 64) {Height = 64 - Y;}
	
	/*����ָ�������漰�����ҳ*/
	/*(Y + Height - 1) / 8 + 1��Ŀ����(Y + Height) / 8������ȡ��*/
	for (j = Y / 8; j < (Y + Height - 1) / 8 + 1; j ++)
	{
		/*���ù��λ��Ϊ���ҳ��ָ����*/
		OLED_SetCursor(j, X);
		/*����д��Width�����ݣ����Դ����������д�뵽OLEDӲ��*/
		OLED_WriteDataArr(&OLED_DisplayBuf[j][X], Width);
	}
	
}
extern void OLED_Clear(void);
//OLED�ĳ�ʼ��
void OLED_Init(void)
{

	OLED_RES_Clr();
	for(int i=0;i<1000;i++)
	{
		for(int j=0;j<1000;j++){

		}
	}
	OLED_RES_Set();
	
#ifdef SH1106
	OLED_Write_CMD(0xAE);//display off
	OLED_Write_CMD(0x02);//set lower column address
	OLED_Write_CMD(0x10);//set higher column address
	OLED_Write_CMD(0x40);//set display start line
	OLED_Write_CMD(0xB0);//set page address
//	OLED_Write_CMD(0x81);//���öԱȶȣ����ȣ�
//	OLED_Write_CMD(0x00);//0x00-0xFF							//Ӱ�����ȣ�Խ��Խ��
	OLED_Write_CMD(0xA1);//set segment remap
	OLED_Write_CMD(0xA6);//normal / reverse
	OLED_Write_CMD(0xA8);//multiplex ratio
	OLED_Write_CMD(0x3F);//duty = 1/64
	OLED_Write_CMD(0xad);//set charge pump enable
	OLED_Write_CMD(0x8b);// 0x8B �ڹ� VCC
	OLED_Write_CMD(0x32);//0X30---0X33 set VPP ��ɱõ�ѹ 		//Ӱ�����ȣ�Խ��Խ��
	OLED_Write_CMD(0xC8);//Com scan direction
	OLED_Write_CMD(0xD3);//set display offset
	OLED_Write_CMD(0x00);// 0x20 
	OLED_Write_CMD(0xD5);//set osc division
	OLED_Write_CMD(0x80);
	OLED_Write_CMD(0xD9);//set pre-charge period
	OLED_Write_CMD(0x22);//Ĭ��0x22
	OLED_Write_CMD(0xDA);//set COM pins
	OLED_Write_CMD(0x12);
	OLED_Write_CMD(0xdb);//set vcomh
	OLED_Write_CMD(0x35);//0x00 - 0x40��Ĭ��0x35				//Ӱ�����ȣ�Խ��Խ��
#endif

#ifdef SSD1306
	OLED_Write_CMD(0xAE);
	OLED_Write_CMD(0x00);
	OLED_Write_CMD(0x10);
	OLED_Write_CMD(0x40);
//	OLED_Write_CMD(0x81);//���öԱȶȣ����ȣ�
//	OLED_Write_CMD(0xCF);
	OLED_Write_CMD(0xA1);
	OLED_Write_CMD(0xC8);
	OLED_Write_CMD(0xA6);
	OLED_Write_CMD(0xA8);
	OLED_Write_CMD(0x3f);
	OLED_Write_CMD(0xD3);
	OLED_Write_CMD(0x00);
	OLED_Write_CMD(0xd5);
	OLED_Write_CMD(0x80);
	OLED_Write_CMD(0xD9);
	OLED_Write_CMD(0xF1);
	OLED_Write_CMD(0xDA);
	OLED_Write_CMD(0x12);
	OLED_Write_CMD(0xDB);
	OLED_Write_CMD(0x40);
	OLED_Write_CMD(0x20);
	OLED_Write_CMD(0x02);
	OLED_Write_CMD(0x8D);
	OLED_Write_CMD(0x14);
	OLED_Write_CMD(0xA4);
	OLED_Write_CMD(0xA6);
	OLED_Write_CMD(0xAF);
#endif

#ifdef SSD1309
	OLED_Write_CMD(0xAE);//--turn off oled panel
	OLED_Write_CMD(0xFD);
	OLED_Write_CMD(0x12);
	OLED_Write_CMD(0xd5);//--set display clock divide ratio/oscillator frequency
	OLED_Write_CMD(0xA0);
	OLED_Write_CMD(0xA8);//--set multiplex ratio(1 to 64)
	OLED_Write_CMD(0x3f);//--1/64 duty
	OLED_Write_CMD(0xD3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_Write_CMD(0x00);//-not offset
	OLED_Write_CMD(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_Write_CMD(0xA1);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	OLED_Write_CMD(0xC8);// Set COM/Row Scan Direction   0xc0���·��� 0xc8����
	OLED_Write_CMD(0xDA);//--set com pins hardware configuration
	OLED_Write_CMD(0x12);
	OLED_Write_CMD(0x81);//--set contrast control register
	OLED_Write_CMD(0xFF);// Set SEG Output Current Brightness
	OLED_Write_CMD(0xD9);//--set pre-charge period
	OLED_Write_CMD(0x25);// Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_Write_CMD(0xDB);//--set vcomh
	OLED_Write_CMD(0x34);// Set VCOM Deselect Level
	OLED_Write_CMD(0xA4);// Disable Entire Display On (0xa4/0xa5)
	OLED_Write_CMD(0xA6);// Disable Inverse Display On (0xa6/a7)
	OLED_Clear();
	OLED_Write_CMD(0xAF);
#endif

//	OLED_Brightness(-1); //��ʼ���������ú���������Ϊ-1�൱������Ϊ0
//	OLED_Clear();
//	OLED_Write_CMD(0xAF);//Display ON
	for(int i=0;i<1000;i++)
	{
		for(int j=0;j<1000;j++){
		}
	}
}

/**
  * ��    ����OLED��������
  * ��    ����Brightness ��0-255����ͬ��ʾоƬЧ�����ܲ���ͬ��
  * �� �� ֵ����
  * ˵    ������Ҫ���ù�����߹�С��
  */
void OLED_Brightness(int16_t Brightness){

	//������������Ƿ�仯���б仯ʱ�ٷ���ָ��
	static int16_t Last_Brightness;
	if (Brightness == Last_Brightness)
	{
		return;
	}
	else
	{
		Last_Brightness = Brightness;
	}

	if(Brightness>255){
		Brightness=255;
	}
	if(Brightness<0){
		Brightness=0;
	}
	OLED_Write_CMD(0x81);
	OLED_Write_CMD(Brightness);
}


/**
 * @brief ������ʾģʽ
 * @param colormode true: ��ɫģʽ��false: ��ɫģʽ
 * @return ��
 */
void OLED_SetColorMode(bool colormode){
	OLED_ColorMode = colormode;
}
