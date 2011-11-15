/*****************************************************************************
*                                                                            *
*    i F B S p r o                                                           *
*   ###############                                                          *
*                                                                            *
*   © L T S o f t                                                            *
*   Agentur für Leittechnik Software GmbH                                    *
*   Brabanterstr. 13                                                         *
*   D-50171 Kerpen                                                           *
*   Tel : 02237/92869-0                                                      *
*   Fax : 02237/92869-9                                                      *
*   e-Mail   : ltsoft@ltsoft.de                                              *
*   Internet : http://www.ltsoft.de                                          *
*                                                                            *
******************************************************************************
*                                                                            *
*   F u n k t i o n s b a u s t e i n t y p                                  *
*                                                                            *
*   Datei      : DEMOLIB_RAMPE.C                                             *
*   Typmethode : RAMPE                                                       *
*                                                                            *
*****************************************************************************/


#include "demolib.h"
#include "libov/ov_macros.h"


/*	----------------------------------------------------------------------	*/

OV_DLLFNCEXPORT void demolib_Rampe_typemethod(
    OV_INSTPTR_fb_functionblock   pfb,
    OV_TIME                       *pltc
) {

    OV_INSTPTR_demolib_Rampe port = Ov_StaticPtrCast(demolib_Rampe, pfb);

    OV_INT        mitte;
    OV_DOUBLE     steigung;
    OV_INT        Abtast;
    

    switch(port->v_MaxPos) {
        case 0  :
                Abtast = port->v_Periode - 1;
                port->v_OutD = (OV_DOUBLE)port->v_Amplitude * (1 - (OV_DOUBLE)port->v_count/(OV_DOUBLE)Abtast);
                port->v_OutS = (OV_SINGLE)port->v_OutD;
                break;
        case 100:
                Abtast = port->v_Periode - 1;
                port->v_OutD = (OV_DOUBLE)port->v_Amplitude * port->v_count / Abtast;
                port->v_OutS = (OV_SINGLE)port->v_OutD;
                break;
        default :
                mitte = (OV_INT)( (port->v_Periode * port->v_MaxPos)/100 );
    
                if(port->v_count <= mitte) {
                    steigung = (OV_DOUBLE)(port->v_Amplitude * 100) / (port->v_Periode * port->v_MaxPos);
                    port->v_OutD = steigung * port->v_count;
                    port->v_OutS = (OV_SINGLE)port->v_OutD;
                } else {
                    steigung = (OV_DOUBLE)(port->v_Amplitude * 100) / ( port->v_Periode * (100 - port->v_MaxPos) );
                    port->v_OutD = steigung * (port->v_Periode - port->v_count);
                    port->v_OutS = (OV_SINGLE)port->v_OutD;
                }
                break;
    } /* case */

    port->v_count++ ;

    if(port->v_count == port->v_Periode) {
        port->v_count = 0;
    }
    
    return;
}


/*	----------------------------------------------------------------------	*/

OV_DLLFNCEXPORT OV_RESULT demolib_Rampe_constructor(
    OV_INSTPTR_ov_object pobj
) {
    /*
    *    local variables
    */
    OV_RESULT                    result;
    OV_INSTPTR_demolib_Rampe     port = Ov_StaticPtrCast(demolib_Rampe, pobj);

    result = fb_functionblock_constructor(pobj);
    if(Ov_Fail(result))
        return result;

    port->v_MaxPos = 50;
    port->v_Periode = 2;
    
    return OV_ERR_OK;  /* Return immer OV_ERR_OK ! */
}
    
/*	----------------------------------------------------------------------	*/

OV_RESULT OV_DLLFNCEXPORT demolib_Rampe_checkinit(
    OV_INSTPTR_ov_object pobj
) {
    
    /*
    *   In dieser Funktion kann man ueberpruefen, ob die Werte von "kritischen" Ports
    *   in den zulaessigen Bereichen liegen und entweder die Werte ueberschreiben oder
    *   Fehler-Code an Programm uebergeben ( in diesem Fall wird die Instanz nicht
    *   erzeugt)
    */
    
    /*
    *    local variables
    */
    OV_INSTPTR_demolib_Rampe     port = Ov_StaticPtrCast(demolib_Rampe, pobj);

    if(port->v_Periode < 2) {
        port->v_Periode = 2;
        // oder return OV_ERR_BADPARAM;
    }
    if( (port->v_MaxPos < 0) || (port->v_MaxPos > 100) ) {
        port->v_MaxPos = 50;
    }
    
    return OV_ERR_OK;
}


/*	----------------------------------------------------------------------	*/

OV_DLLFNCEXPORT OV_RESULT demolib_Rampe_Periode_set(
    OV_INSTPTR_demolib_Rampe    port,
    const OV_INT                wert
) {

    if( wert < 2 ) {
        return OV_ERR_BADVALUE;
    }

    port->v_count = 0;
    port->v_Periode = wert;

    return 0;
}


/*	----------------------------------------------------------------------	*/

OV_DLLFNCEXPORT OV_RESULT demolib_Rampe_Amplitude_set(
    OV_INSTPTR_demolib_Rampe    port,
    const OV_SINGLE             wert
) {

    port->v_count = 0;
    port->v_Amplitude = wert;

    return 0;
}


/*	----------------------------------------------------------------------	*/

OV_DLLFNCEXPORT OV_RESULT demolib_Rampe_MaxPos_set(
    OV_INSTPTR_demolib_Rampe    port,
    const OV_INT                wert
) {
    if( (wert < 0) || (wert > 100) ) {
        return OV_ERR_BADVALUE;
    }
    port->v_count = 0;
    port->v_MaxPos = wert;

    return 0;
}
