#ifndef __THEZG_H__
#define __THEZG_H__

//INTERMITTENT_SERVICE ʵ�� ��ʱһ��ʱ�� ִ�д���
//ʹ�� tTimeCounterCC ������Աʱ,��ʼ������Ϊ { 0, 0 }
//���� INTERMITTENT_SERVICE( tTimeCounterCC x , ϵͳ�������� , ��Ҫ��ʱ��ʱ��){}

typedef struct {
	unsigned long long LastSysTickMs;
	unsigned char RunState;
}tTimeCounterCC;

extern unsigned char TimeCounter( tTimeCounterCC * tc1,  unsigned long long SysTickMs , unsigned int SysRunTime );
	
#define INTERMITTENT_SERVICE(xTC,xSysTickMs,xSysRunTime)	if(TimeCounter(&xTC,xSysTickMs,xSysRunTime))

//�������˲�����
//KFP ������Ա �Ƽ���ʼ�� Ϊ{ 0.02, 0, 0, 0, 0.001, 0.543 }
//kalmanFilter Ϊһ���˲� ,һ������¹���
//kalmanFilter_update Ϊ�������˲� ,��Ҫ��������,Ч������
typedef struct 
{
    float LastP;        
    float Now_P;       
    float out;                
    float Kg;               
    float Q;                
    float R;
}KFP;

extern float kalmanFilter(KFP *kfp,float input);
extern float kalmanFilter_update(KFP *kfp,float input);

//�����ź���
extern float CosmicSuperInvincibleMagicFunction( float A_Strange_Thing);

//����ӳ�亯��
//����ֵ   ����ֵ����Сֵ    ����ֵ�����ֵ    ӳ�����Сֵ    ӳ������ֵ
#define DATA_MAP(x, in_min, in_max, out_min, out_max) \
		( (in_max == in_min) ? (out_min) : \
		( ( (int64_t)(x - in_min)*(out_max - out_min) ) / (in_max - in_min) + out_min ) )

extern int data_map(int x, int in_min, int in_max, int out_min, int out_max);

//ӳ���ݺ���
int power_function_map(int x);

//ӳ�����κ��� 4k
extern int cubic_function_map(int x,int out_min, int out_max);

//����Լ��
extern int data_constraint( int x , int min , int max );

//�� src ������ ���Ƶ� dst , num Ϊ����
//extern void Upmemcpy(void *dst, const void *src, unsigned int num );

//ϵͳ��ĳ��־λ����
//ʹ��ʱ,�Ƽ� tFlagClassMember �����ṹ�������Ա,��ʼ��Ϊ { ����ֵ , 0 ,0 }
/*
		THEZG.GetFlag( &SysTargetState[x] )
		THEZG.SetFlag( &SysTargetState[x] ,1)
		THEZG.GetData( &SysTargetState[x] )
		THEZG.SetData( &SysTargetState[x] ,3)
*/
typedef struct DrivingMark2{
	unsigned char Index;
	unsigned char FlagStatus;
	signed short S16Data;
}tFlagClassMember;

typedef struct DrivingMark{
	unsigned char (*GetFlag)( struct DrivingMark2 * xC );
	void (*SetFlag)( struct DrivingMark2 * xC ,int state );
	signed short (*GetData)(struct DrivingMark2 * xC);				
	void (*SetData)(struct DrivingMark2 * xC , signed short data );	
}tFlagClassStructure;

extern tFlagClassStructure THEZG;
extern tFlagClassMember SysTargetState[]; //��4����־��Ա,���ض���

//tExpSim Simulation_Mem_G = {0,1,0.05,0.92, &sActualExpected}; 0.05 ���Ի�Ϊ0.02 ,���ٱ���
//���������ݱ䶯����ģ�⺯��
//Expected_Simulation ����һ��Ŀ��ֵ,sActualExpected ���ݻ��������� ��Ŀ��ֵ
typedef struct {
	int velocity;
	int tolerance; 			// ���Ը�����Ҫ������������
	double learningRate;	// ѧϰ��
	double damping;			// ����ϵ��
	int * xActualExpected;	// ���ݵ�ָ��
}tExpSim;

int Expected_Simulation( int xTargetExpected, tExpSim * ESmember);

//tFOFM FOFMember = {0,0};

typedef struct{
	int OutRData;
	int OutRDataPrev;
	
}tFOFM;

extern int DataFirstOrderFilter(tFOFM *xMember,int InputData);

#endif
