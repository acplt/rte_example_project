
/******************************************************************************
*
*   FILE
*   ----
*   Rampe.c
*
*   History
*   -------
*   2017-05-18   File created
*
*******************************************************************************
*
*   This file is generated by the 'acplt_builder' command
*
******************************************************************************/


#ifndef OV_COMPILE_LIBRARY_demolib
#define OV_COMPILE_LIBRARY_demolib
#endif


#include "demolib.h"
#include "ov_macros.h"


OV_DLLFNCEXPORT OV_RESULT demolib_Rampe_periode_set(
    OV_INSTPTR_demolib_Rampe          pobj,
    const OV_INT  value
) {
    if( value < 2 ) {
        return OV_ERR_BADVALUE;
    }

    pobj->v_count = 0;
    pobj->v_periode = value;

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT demolib_Rampe_amplitude_set(
    OV_INSTPTR_demolib_Rampe          pobj,
    const OV_SINGLE  value
) {
	pobj->v_count = 0;
	pobj->v_amplitude = value;

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT demolib_Rampe_maxPos_set(
    OV_INSTPTR_demolib_Rampe          pobj,
    const OV_INT  value
) {
    if( (value < 0) || (value > 100) ) {
        return OV_ERR_BADVALUE;
    }
    pobj->v_count = 0;
    pobj->v_maxPos = value;

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT demolib_Rampe_constructor(
	OV_INSTPTR_ov_object 	pobj
) {
    /*    
    *   local variables
    */
    OV_INSTPTR_demolib_Rampe pinst = Ov_StaticPtrCast(demolib_Rampe, pobj);
    OV_RESULT    result;

    /* do what the base class does first */
    result = fb_functionblock_constructor(pobj);
    if(Ov_Fail(result))
         return result;

    /* do what */
    pinst->v_maxPos = 50;
    pinst->v_periode = 2;

    return OV_ERR_OK;  /* Return immer OV_ERR_OK ! */
}

OV_DLLFNCEXPORT OV_RESULT demolib_Rampe_checkinit(
	OV_INSTPTR_ov_object 	pobj
) {
    /*    
    *   local variables
    */
    OV_INSTPTR_demolib_Rampe pinst = Ov_StaticPtrCast(demolib_Rampe, pobj);
    OV_RESULT    result;

    /* do what the base class does first */
    result = fb_functionblock_checkinit(pobj);
    if(Ov_Fail(result))
         return result;

    /* do what */
    /*
    *   In dieser Funktion kann man ueberpruefen, ob die Werte von "kritischen" Ports
    *   in den zulaessigen Bereichen liegen und entweder die Werte ueberschreiben oder
    *   Fehler-Code an Programm uebergeben (in diesem Fall wird die Instanz nicht
    *   erzeugt).
    */
    if(pinst->v_periode < 2) {
    	pinst->v_periode = 2;
        // oder return OV_ERR_BADPARAM;
    }
    if( (pinst->v_maxPos < 0) || (pinst->v_maxPos > 100) ) {
    	pinst->v_maxPos = 50;
    }

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT void demolib_Rampe_typemethod(
	OV_INSTPTR_fb_functionblock	pfb,
	OV_TIME						*pltc
) {
    /*    
    *   local variables
    */
    OV_INSTPTR_demolib_Rampe pinst = Ov_StaticPtrCast(demolib_Rampe, pfb);

    OV_INT        mitte;
    OV_DOUBLE     steigung;
    OV_INT        Abtast;


    switch(pinst->v_maxPos) {
        case 0  :
                Abtast = pinst->v_periode - 1;
                pinst->v_outD = (OV_DOUBLE)pinst->v_amplitude * (1 - (OV_DOUBLE)pinst->v_count/(OV_DOUBLE)Abtast);
                pinst->v_outS = (OV_SINGLE)pinst->v_outD;
                break;
        case 100:
                Abtast = pinst->v_periode - 1;
                pinst->v_outD = (OV_DOUBLE)pinst->v_amplitude * pinst->v_count / Abtast;
                pinst->v_outS = (OV_SINGLE)pinst->v_outD;
                break;
        default :
                mitte = (OV_INT)( (pinst->v_periode * pinst->v_maxPos)/100 );

                if(pinst->v_count <= mitte) {
                    steigung = (OV_DOUBLE)(pinst->v_amplitude * 100) / (pinst->v_periode * pinst->v_maxPos);
                    pinst->v_outD = steigung * pinst->v_count;
                    pinst->v_outS = (OV_SINGLE)pinst->v_outD;
                } else {
                    steigung = (OV_DOUBLE)(pinst->v_amplitude * 100) / ( pinst->v_periode * (100 - pinst->v_maxPos) );
                    pinst->v_outD = steigung * (pinst->v_periode - pinst->v_count);
                    pinst->v_outS = (OV_SINGLE)pinst->v_outD;
                }
                break;
    } /* case */

    pinst->v_count++ ;

    if(pinst->v_count == pinst->v_periode) {
        pinst->v_count = 0;
    }

    return;
}
