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
*   Datei      : DEMOLIB_MUL.C                                               *
*   Typmethode : MULTIPLIZIERER                                              *
*                                                                            *
*****************************************************************************/

#include "demolib.h"
#include "libov/ov_macros.h"

OV_DLLFNCEXPORT void demolib_mul_typemethod(
    OV_INSTPTR_fb_functionblock  pfb,
    OV_TIME                      *pltc
) {

    OV_INSTPTR_demolib_mul pfbt = Ov_StaticPtrCast(demolib_mul, pfb);

    pfbt->v_out = pfbt->v_inp1 * pfbt->v_inp2;

/*
*   versteckte Variable bearbeiten
*/
    pfbt->v_zaehler = (pfbt->v_zaehler+1)%10000;	/* Aufruf-Zähler*/

/*
*   Endebearbeitung
*/
    return;

}
