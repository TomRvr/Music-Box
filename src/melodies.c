#include "notes.c"
#include <stdint.h>

/*Melodies*/
/*Placer 0 apres la derniere note pour indiquer la fin*/

uint16_t berceuse[2][55] = {{FA,FA,LA,FA,FA,LA,FA,LA,RE*2,DO*2,SI,SI,LA,MI,FA,SOL,MI,MI,FA,SOL,MI,FA,DO*2,SI,LA,DO*2,RE*2,RE,RE,RE*2,SI,SOL,LA,FA,RE,SOL,LA,SI,LA,RE,RE,RE*2,SI,SOL,LA,FA,RE,SOL,LA,SOL,FA,MI,RE,1,0},	/*notes*/
				            {N ,N ,NP,C ,N ,B ,N ,N ,N   ,NP  ,C ,N ,N ,N ,N ,N  ,N ,N ,N ,B  ,N ,N ,N   ,N ,N ,N   ,B   ,N ,N ,B   ,N ,N  ,B ,N ,N ,N  ,N ,N ,B ,N ,N ,B   ,N ,N  ,B ,N ,N ,N  ,C ,C  ,N ,N ,B ,N,N}};	/* durees N,>Cs B,>Ns */
				 
uint16_t colas[2][39] = 
{{SI,LA,SOL,SOL,LA,SOL,LA,SI,SOL,SI,LA,SOL,SOL,LA,SI,LA,SOL,RE*2,RE*2,SI,RE*2,RE*2,RE*2,RE*2,SI,RE*2,RE*2,SI,SI,DO*2,RE*2,LA,SI,SI,DO*2,RE*2,LA,1,0},
 {B ,N ,B  ,N  ,N ,N  ,N ,B ,N  ,B ,N ,B  ,N  ,N ,N ,N ,B  ,N   ,N   ,N ,N   ,B   ,N   ,N   ,N ,N   ,B   ,N ,N ,N   ,N   ,B ,N ,N ,N   ,N   ,R ,N,N}};                              

uint16_t clair[2][46] =
{{DO,DO,DO,RE,MI,RE,DO,MI,RE,RE,DO,DO,DO,DO,RE,MI,RE,DO,MI,RE,RE,DO,RE,RE,RE,RE,LA/2,LA/2,RE,DO,SI/2,LA/2,SOL/2,DO,DO,DO,RE,MI,RE,DO,MI,RE,RE,DO,1,0},
 {N ,N ,N ,N ,B ,B ,N ,N ,N ,N ,R ,N ,N ,N ,N ,B ,B ,N ,N ,N ,N ,R ,N ,N ,N ,N ,B   ,B   ,N ,N ,N   ,N   ,R    ,N ,N ,N ,N ,B ,B ,N ,N ,N ,N ,R ,N,N}};

uint16_t salv[2][31] =
{{MI/2,MI/2,MI/2,MI/2,SOL/2,MI/2,FA/2,FA/2,FA/2,FA/2,LA/2,SOL/2,DO,N,MI/2,MI/2,MI/2,MI/2,SOL/2,MI/2,FA/2,FA/2,FA/2,FA/2,LA/2,RE/2,MI/2,1,0},
 {N   ,N   ,N   ,N   ,N    ,N   ,N   ,N   ,N   ,N   ,N   ,N    ,R ,N,N   ,N   ,N   ,N    ,N   ,N   ,N   ,N   ,N   ,N    ,N  ,N   ,R   ,N,N}};

uint16_t noel[2][77] =
{{SOL,DO*2,DO*2,DO*2,RE*2,DO*2,DO*2,RE*2,MI*2,MI*2,MI*2,FA*2,MI*2,RE*2,DO*2,DO*2,DO*2,DO*2,SI,LA,SOL,SOL,SOL,DO*2,DO*2,DO*2,SI,DO*2,RE*2,SOL,DO*2,DO*2,DO*2,RE*2,RE*2,DO*2,LA,LA,LA,LA,LA,LA,SI,DO*2,LA,LA,SOL,DO*2,DO*2,DO*2,DO*2,DO*2,SI,DO*2,RE*2,REd*2,REd*2,REd*2,REd*2,REd*2,RE*2,REd*2,FA*2,RE*2,DO*2,DOd*2,REd*2,REd*2,REd*2,REd*2,FA*2,FA*2,FA*2,SOL,SOL,1,0},
{N,N,N,N,N,R,N,N,N,N,N,N,R,N,NP,N,N,N,N,N,R,N,N,B,N,N,N,N,R,N,B,N,N,N,N,R,N,N,N,N,N,N,N,NP,N,N,N,N,N,N,N,N,N,N,R,N,N,N,N,N,N,N,NP,N,N,N,N,N,N,N,N,N,N,R,N,N}};                                                   

uint16_t marionette[2][27] = 
{{SI,SI,SOL,SI,RE*2,DO*2,SI,DO*2,LA,SOL,FA,SOL,SOL,SI,SI,SOL,SI,RE*2,DO*2,SI,DO*2,LA,SOL,FA,SOL,1,0},
 {N ,N ,N  ,N ,N   ,N   ,N ,N   ,N ,N  ,N ,N  ,N  ,N ,N ,N  ,N ,N   ,N   ,N ,N   ,N ,N  ,N ,N  ,N,N}};  
  
uint16_t dodo[2][27] = 
{{SI,SOL,SI,SI,SOL,LA,SI,DO*2,SI,LA,RE*2,SI,LA,SI,SOL,SI,SI,SOL,LA,SI,DO*2,SI,LA,RE*2,SOL,1,0},
 {N ,N  ,N ,N ,N  ,N ,N ,N   ,N ,N ,N   ,N ,N ,N ,N  ,N ,N ,N  ,N ,N ,N   ,N ,N ,N   ,N  ,N,N}}; 

uint16_t jacques[2][34] = 
{{FA,SOL,LA,FA,FA,SOL,LA,FA,LA,LAd,DO*2,LA,LAd,DO*2,DO*2,RE*2,DO*2,SI,LA,FA,DO*2,RE*2,DO*2,SI,LA,FA,FA,DO,FA,FA,DO,FA,1,0},
 {N ,N  ,N ,N ,N ,N  ,N ,N ,N ,N  ,B   ,N ,N  ,B   ,NP  ,N   ,N   ,N ,N ,N ,NP  ,N   ,N   ,N ,N ,N ,N ,N ,B ,N ,N ,B ,N,N}}; 
 
