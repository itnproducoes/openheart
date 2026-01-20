/*
   Lightweight, standalone driver for ssd1306 displays on Raspberry Pi Pico.
   Author: Irineu Teza Nunes
   This code was written from scratch based on public.

   License
   Source-Available Freeware License
   License Grant The Licensor grants the Licensee a non-exclusive, non-transferable right to access and view the Software’s source code, as well as use it internally, exclusively for personal or corporate purposes, under the terms of this agreement.
   Rights and Restrictions Unless expressly authorized in writing by the Licensor, the Licensee may not:
   (a) commercially use the Software or any derivative work (including selling, renting, offering as a service/SaaS, or consulting involving distribution of the Software);
   (b) redistribute, publish, make available, or sublicense the Software or its source code, in whole or in part;
   (c) modify or create derivative works for external distribution;
   (d) remove or alter copyright notices, trademarks, or credits;
   (e) circumvent technical protection mechanisms.

    Internal Modification Permission The Licensee may modify the source code only for internal use, without distribution to third parties. Any external distribution requires prior written authorization from the Licensor.
    Intellectual Property The Software and its source code remain the property of the Licensor. No ownership rights are transferred to the Licensee.
    Warranty and Liability The Software is provided “as is,” without warranties of any kind. The Licensor shall not be liable for any damages arising from the use or inability to use the Software.
    Termination and Compliance The Licensor may revoke this license in case of violation. The Licensee agrees to provide reasonable information to verify compliance upon request.
    Governing Law and Jurisdiction This agreement is governed by Brazilian law, and the courts of the Licensor’s city shall have jurisdiction over any disputes.
    
    The bitmap arrays were generated using the "image2cpp" tool,  whose source code is licensed under GPLv3. As per FSF guidelines, 
    the output of GPL tools does not inherit the GPL, as it does not include GPL code.
    Therefore, this data is not considered a derivative work.
    https://javl.github.io/image2cpp/
    Draw mode: Vertical 1 bit per pixel
*/


#pragma once

#include "pico/stdlib.h"

extern const uint8_t * ssd16bitlogo_bitmap;
extern const uint8_t * ssdsegalogo_bitmap;
extern const uint8_t * ssdextreme_bitmap;
extern const uint8_t * ssdsoniclogo_bitmap;
extern const uint8_t * ssdopenheart_bitmap;
extern const uint8_t * ssdlicense_bitmap;

