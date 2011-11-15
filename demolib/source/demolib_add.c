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
*   Datei      : DEMOLIB_ADD.C                                               *
*   Typmethode : ADDIERER                                                    *
*                                                                            *
*****************************************************************************/

#include "demolib.h"
#include "libov/ov_macros.h"

OV_DLLFNCEXPORT void demolib_add_typemethod(
    OV_INSTPTR_fb_functionblock pfb,
    OV_TIME                     *pltc
) {

    OV_INSTPTR_demolib_add port = Ov_StaticPtrCast(demolib_add, pfb);

    port->v_out = port->v_in1 +  port->v_in2;

    /*
    *   versteckte Variable bearbeiten
    */
	port->v_zaehler = (port->v_zaehler+1)%10000;    /* Aufruf-Zähler*/

    /*
    *   Endebearbeitung
    */
    return;
}

