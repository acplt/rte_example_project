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
*   Datei      : DEMOLIB_SINUS.C                                             *
*   Typmethode : SINUS                                                       *
*                                                                            *
*****************************************************************************/


#include "demolib.h"
#include "libov/ov_macros.h"
#include <math.h>


/*	----------------------------------------------------------------------	*/

OV_DLLFNCEXPORT void demolib_Sinus_typemethod(
    OV_INSTPTR_fb_functionblock    pfb,
    OV_TIME                        *pltc
) {

    OV_INSTPTR_demolib_Sinus port = Ov_StaticPtrCast(demolib_Sinus, pfb);

    OV_SINGLE    ZweiPi = 6.283185;

    port->v_OutD = (OV_DOUBLE)port->v_Amplitude * sin(ZweiPi * port->v_count / port->v_Periode) + port->v_Offset;
    port->v_OutS = (OV_SINGLE)port->v_OutD;

    port->v_count += 1;

    if(port->v_count == port->v_Periode) {
        port->v_count = 0;
    }
    
    return;
}


/*	----------------------------------------------------------------------	*/

OV_DLLFNCEXPORT OV_RESULT demolib_Sinus_constructor(
    OV_INSTPTR_ov_object pobj
) {
    /*
    *    local variables
    */
    OV_RESULT                    result;
    OV_INSTPTR_demolib_Sinus     port = Ov_StaticPtrCast(demolib_Sinus, pobj);

    result = fb_functionblock_constructor(pobj);
    if(Ov_Fail(result))
        return result;

    port->v_Periode = 2;
    
    return OV_ERR_OK;  /* Return immer OV_ERR_OK ! */
}


/*	----------------------------------------------------------------------	*/

OV_DLLFNCEXPORT OV_RESULT demolib_Sinus_checkinit(
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
    OV_INSTPTR_demolib_Sinus     port = Ov_StaticPtrCast(demolib_Sinus, pobj);

    
    if(port->v_Periode <= 1) {
        port->v_Periode = 2;
        // oder return OV_ERR_BADPARAM;
    }
    
    return OV_ERR_OK;
}


/*	----------------------------------------------------------------------	*/

OV_DLLFNCEXPORT OV_RESULT demolib_Sinus_Periode_set(
    OV_INSTPTR_demolib_Sinus    port,
    const OV_INT                wert
) {
    if(wert < 2)
        return OV_ERR_BADVALUE;

    port->v_count = 0;
    port->v_Periode = wert;
    
    return 0;
}


/*	----------------------------------------------------------------------	*/

OV_DLLFNCEXPORT OV_RESULT demolib_Sinus_Amplitude_set(
    OV_INSTPTR_demolib_Sinus    port,
    const OV_SINGLE             wert
) {

    port->v_count = 0;
    port->v_Amplitude = wert;

    return 0;
}


/*	----------------------------------------------------------------------	*/

OV_DLLFNCEXPORT OV_RESULT demolib_Sinus_Offset_set(
    OV_INSTPTR_demolib_Sinus    port,
    const OV_SINGLE             wert
) {

    port->v_count = 0;
    port->v_Offset = wert;

    return 0;
}
