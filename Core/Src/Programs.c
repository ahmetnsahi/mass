 /* Msg.c
 *
 *  Created on: Sep 14, 2023
 *      Author: ahmet
 */

#include "Programs.h"
#include "Msg.h"
#include "main.h"
#include "stdio.h"

Massage ms;
struct Motor M[16];

extern uint8_t RxBuf[];
uint16_t motor_sayısı = 0;
uint16_t ch=0;


                                                                   /* Tüm Programlar
   NOT :önce time, temp ,duty  , sonra motor sırası;*/


//Agrı Terapi
struct prg GA={4,1,140,495};
struct prg BS={4,1,150,495};
struct prg BK={4,1,160,495};
struct prg AT={4,1,170,495};
struct prg BT={4,1,180,495};
struct prg DK={4,1,190,495};
struct prg BF={4,1,200,495};



//Tıbbı Seans

struct prg DG={3,1,160,1365};
struct prg KD={2,1,175,1663};
struct prg LF={3,1,170,1659};
struct prg AÜ={3,1,180,1659};
struct prg MH={3,1,190,1659};
struct prg KT={1,1,200,65535};  //ikinci tur hızlı demiş

//Zayıflatma

struct prg TV={3,1,160,495};
struct prg KG={3,1,160,495};
struct prg BA={3,1,160,495};
struct prg KY={3,1,160,495};
struct prg ÖA={4,1,160,495};
struct prg GS={4,1,160,495};
struct prg KB={4,1,160,495};




extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim16;
extern TIM_HandleTypeDef htim17;


void pinit(void){

	  M[0].Channel=TIM_CHANNEL_1;  M[0].Duty=0;   M[0].Tımer=htim1;
	  M[1].Channel=TIM_CHANNEL_2;  M[1].Duty=0;   M[1].Tımer=htim1;
	  M[2].Channel=TIM_CHANNEL_3;  M[2].Duty=0;   M[2].Tımer=htim1;
	  M[3].Channel=TIM_CHANNEL_4;  M[3].Duty=0;   M[3].Tımer=htim1;//


	  M[4].Channel=TIM_CHANNEL_1;  M[4].Duty=0;   M[4].Tımer=htim3;
	  M[5].Channel=TIM_CHANNEL_2;  M[5].Duty=0;   M[5].Tımer=htim3;//
	  M[6].Channel=TIM_CHANNEL_3;  M[6].Duty=0;   M[6].Tımer=htim4;
	  M[7].Channel=TIM_CHANNEL_4;  M[7].Duty=0;   M[7].Tımer=htim4;


	  M[8].Channel=TIM_CHANNEL_1;  M[8].Duty=0;   M[8].Tımer=htim17;
	  M[9].Channel=TIM_CHANNEL_4;  M[9].Duty=0;   M[9].Tımer=htim2;
	  M[10].Channel=TIM_CHANNEL_3; M[10].Duty=0;  M[10].Tımer=htim2;
	  M[11].Channel=TIM_CHANNEL_4; M[11].Duty=0;  M[11].Tımer=htim3;

	  M[12].Channel=TIM_CHANNEL_3; M[12].Duty=0;  M[12].Tımer=htim3;
	  M[13].Channel=TIM_CHANNEL_1; M[13].Duty=0;  M[13].Tımer=htim2;
	  M[14].Channel=TIM_CHANNEL_2; M[14].Duty=0;  M[14].Tımer=htim2;
	  M[15].Channel=TIM_CHANNEL_1; M[15].Duty=0;  M[15].Tımer=htim16;












}

void Pwm_Start(Massage Ms){




	// __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,500);


	for ( uint16_t var = 0;  var < 16; var++) {



		if (Ms.MSayi & (1 << var)) {  // n. bit 1
			M[var].Duty=Ms.Speeds;
		   __HAL_TIM_SET_COMPARE(&M[var].Tımer,M[var].Channel,M[var].Duty);

	     }
		else{                 // n. bit 0

		   M[var].Duty=0;
		  __HAL_TIM_SET_COMPARE(&M[var].Tımer,M[var].Channel,M[var].Duty);
	   }


       }

}


prg prgSel(){
ch=RxBuf[2];


switch (ch) {
    case 1:
    	return GA;
        break;
    case 2:
    	return BS;
        break;
    case 3:
    	return BK;
        break;
    case 4:
    	return AT;
        break;
    case 5:
    	return BT;
        break;
    case 6:
    	return DK;
        break;
    case 7:
    	return BF;   //AGRI TERAPİ
        break;
    case 8:
    	return DG;
        break;
    case 9:
    	return KD;
        break;
    case 10:
    	return LF;
        break;
    case 11:
    	return AÜ;
        break;
    case 12:
    	return MH;
        break;
    case 13:
    	return KT;   //TIBBI TERAPİ
        break;
    case 14:
    	return TV;
        break;
    case 15:
    	return KG;
        break;
    case 16:
    	return BA;
        break;
    case 17:
    	return KY;
        break;
    case 18:
    	return ÖA;
        break;
    case 19:
    	return GS;
        break;
    case 20:
    	return KB;  //zayiflama
        break;
    default:

        return;

        break;
}



}


uint8_t  Stop_Full(void){
	uint8_t bool;
      Massage mX;
	 mX.MSayi=0b1111111111111111; //motor sayıları için pwm
	 mX.Speeds=0;
	   if (RxBuf[0]=='z' ||RxBuf[0]=='y' ) {    //kodu kesiyor.stop char d
		   Pwm_Start(mX);         //pwm out veriyor.
		   RxBuf[0]=0;
		   bool=1;
	    }else return bool=0;


}




void program(){




Massage msP;
msP.MSayi=0;
msP.Speeds=prgSel().speed*5; //1den5 e kadar





//motorları dönen kod
    for (uint8_t var = 0;  var < 10; ++ var) {

        if (Stop_Full()==1) {
             break;
		}else{

    	if (prgSel().motor & ( 1 <<var)) //hangi motorların açık olacagına bakıyor.
    		{  /* n. bit 1 */
    	     uint16_t t =0;

    	     t |=1<<var+1 ;           //fazladan tam sıra için
    	     t |=1<<var ;            //açık olan motor bitini çekiyor.,
    	     t=t+57344;              //ısıtıcılar açıldı;
    	     msP.MSayi=t;            //motoru yüklüyor.
    	     Pwm_Start(msP);         //pwm out veriyor.

            HAL_Delay(prgSel().time*1000); //progrma süresini çekiyor.
             var++;
    		}
    		else {
    		   /* n. bit 0 */
                               //genel olarak işlem yok.
    		}

         }

	}

}




