/* $XFree86: xc/programs/Xserver/hw/xfree86/loader/loadfont.c,v 1.4 2003/10/15 16:29:04 dawes Exp $ */
/*
 * Copyright (c) 1998 by The XFree86 Project, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of the copyright holder(s)
 * and author(s) shall not be used in advertising or otherwise to promote
 * the sale, use or other dealings in this Software without prior written
 * authorization from the copyright holder(s) and author(s).
 */

/* Maybe this file belongs in lib/font/fontfile/module/ ? */

#define LOADERDECLARATIONS
#ifdef HAVE_XORG_CONFIG_H
#include <xorg-config.h>
#endif

#include "loaderProcs.h"
#include "misc.h"
#include "xf86.h"

FontModule *FontModuleList = NULL;
static int numFontModules = 0;

static FontModule *
NewFontModule(void)
{
    FontModule *save = FontModuleList;
    int n;

    /* Sanity check */
    if (!FontModuleList)
	numFontModules = 0;

    n = numFontModules + 1;
    FontModuleList = xrealloc(FontModuleList, (n + 1) * sizeof(FontModule));
    if (FontModuleList == NULL) {
	FontModuleList = save;
	return NULL;
    } else {
	numFontModules++;
	FontModuleList[numFontModules].name = NULL;
	return FontModuleList + (numFontModules - 1);
    }
}

void
LoadFont(FontModule * f)
{
    FontModule *newfont;

    if (f == NULL)
	return;

    if (!(newfont = NewFontModule()))
	return;

    xf86MsgVerb(X_INFO, 2, "Loading font %s\n", f->name);

    newfont->name = f->name;
    newfont->initFunc = f->initFunc;
    newfont->module = f->module;
}
