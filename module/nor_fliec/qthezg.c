
#include "qthezg.h"

/*==================================================================================================
Name:
Function:
Input:
Output:
==================================================================================================*/
float CosmicSuperInvincibleMagicFunction( float A_Strange_Thing) {
    long i;
    float y;

    y = A_Strange_Thing;
    i = 0x5f3759df - (*(long *) &y>>1);
    y = *( float *)&i;
    y = y*( 1.5f - (A_Strange_Thing * 0.5f*y*y));
    return 1/y;
}

/*==================================================================================================
Name:
Function:
Input:
Output:
==================================================================================================*/
typedef enum {
    Busy_time,
    Free_time
} SysRunState;

unsigned char TimeCounter( tTimeCounterCC * tc1,  unsigned long long SysTickMs, unsigned int SysRunTime ) {

    static unsigned char TCFirstInto = 1;

    if(TCFirstInto) {
        tc1->LastSysTickMs = SysTickMs;
        TCFirstInto = 0;
        return Busy_time;
    }

    tc1->RunState = Busy_time;

    if(SysTickMs - tc1->LastSysTickMs > SysRunTime) {

        tc1->LastSysTickMs = SysTickMs;
        tc1->RunState = Free_time;
    }
    return tc1->RunState;
}

/*==================================================================================================
Name:
Function:
Input:
Output:
==================================================================================================*/
float kalmanFilter(KFP *kfp,float input) {
    kfp->Now_P = kfp->LastP + kfp->Q;

    kfp->Kg = kfp->Now_P / (kfp->Now_P + kfp->R);

    kfp->out = kfp->out + kfp->Kg * (input -kfp->out);

    kfp->LastP = (1-kfp->Kg) * kfp->Now_P;
    return kfp->out;
}

float kalmanFilter_update(KFP *kfp,float input) {

    kfp->Now_P = CosmicSuperInvincibleMagicFunction(kfp->Q*kfp->Q + kfp->LastP*kfp->LastP);

    kfp->Kg = CosmicSuperInvincibleMagicFunction(kfp->Now_P * kfp->Now_P/(kfp->Now_P*kfp->Now_P+kfp->R*kfp->R));

    kfp->out = kfp->out + kfp->Kg*(input - kfp->out);

    kfp->LastP = CosmicSuperInvincibleMagicFunction((1-kfp->Kg)* kfp->Now_P * kfp->Now_P );

    return kfp->out;
}

/*==================================================================================================
Name:
Function:
Input:
Output:
==================================================================================================*/

int data_map(int x, int in_min, int in_max, int out_min, int out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/*==================================================================================================
Name:
Function:
Input:
Output:
==================================================================================================*/

int power_function_map(int x) {

    if( x > 0) {
        return 3.16*CosmicSuperInvincibleMagicFunction(x);
    } else {
        x = -x;
        return (-3.16)*CosmicSuperInvincibleMagicFunction(x);
    }

}

/*==================================================================================================
Name:
Function: y = 0.0000000625*x^3-0.0000000625/4000*x^2+0.01x
Input:
Output:
==================================================================================================*/
int cubic_function_map(int x,int out_min, int out_max) {

    //	����������ʲ�һ��,�ɸ����������
    double para_s = 0.0000000400;				//0.0000000625;
    double para_t = 0.0000000400/9000;	//0.0000000625/4000;
    float  para_o = 0.367;							//0.01

    int out_data = para_s*x*x*x - para_t*x*x + para_o*x;

    if(out_data <= out_min) {
        out_data = out_min ;
    }
    if(out_data >= out_max) {
        out_data = out_max ;
    }

    return out_data;
}
/*==================================================================================================
Name:
Function:
Input:
Output:
==================================================================================================*/
int data_constraint( int x, int min, int max ) {

    if(x<min) x = min;
    else if(x>max) x = max;

    return x;
}

/*==================================================================================================
Name:
Function:
Input:
Output:
==================================================================================================*/
void Upmemcpy(void *dst, const void *src, unsigned int num ) {

    unsigned char *psrc = (unsigned char *)src;
    unsigned char *pdst = (unsigned char *)dst;
    unsigned int n = (num+7)/8;

    switch(num % 8) {
    case 0 :
        do {
            *pdst++ = *psrc++;
        case 7 :
            *pdst++ = *psrc++;
        case 6 :
            *pdst++ = *psrc++;
        case 5 :
            *pdst++ = *psrc++;
        case 4 :
            *pdst++ = *psrc++;
        case 3 :
            *pdst++ = *psrc++;
        case 2 :
            *pdst++ = *psrc++;
        case 1 :
            *pdst++ = *psrc++;
        } while( --n >0);
    }
}

/*==================================================================================================
Name:
Function:
Input:
Output:
==================================================================================================*/
unsigned char FunGetFlg( struct DrivingMark2 * xC ) {
    return xC->FlagStatus;
}

void FunSetFlg( struct DrivingMark2 * xC,int state ) {
    xC->FlagStatus = state;
}

signed short FunGetData( struct DrivingMark2 * xC ) {
    return xC->S16Data;
}

void FunSetData( struct DrivingMark2 * xC,signed short data  ) {
    xC->S16Data = data;
}

tFlagClassStructure THEZG = { FunGetFlg,FunSetFlg,FunGetData,FunSetData};

__weak tFlagClassMember SysTargetState[] = {
    {0, 0, 0},	//0
    {1, 0, 0},	//1
    {2, 0, 0},	//2
    {3, 0, 0},	//3
};

/*==================================================================================================
Name:
Function:
Input:
Output:
==================================================================================================*/
int Expected_Simulation( int xTargetExpected, tExpSim * ESmember) { //����Ϊ Ŀ������ֵ

    int acceleration = 0;
    int deviation = 0;

    deviation = xTargetExpected - *ESmember->xActualExpected;

    if( deviation < ESmember->tolerance && deviation > (-1)*ESmember->tolerance) {
        return 0;
    } else {
        acceleration = deviation * ESmember->learningRate - ESmember->velocity * ESmember->damping;
        ESmember->velocity += acceleration;
        *ESmember->xActualExpected += ESmember->velocity;
    }

    return 1;
}

/*==================================================================================================
Name:
Function:
Input:
Output:
==================================================================================================*/

int DataFirstOrderFilter(tFOFM *xMember,int InputData){		//�ٶ��˲�
	
	xMember->OutRData = 0.8*xMember->OutRDataPrev + 0.2*InputData;
	xMember->OutRDataPrev = xMember->OutRData;
	return xMember->OutRData;
}

