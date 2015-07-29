/*
 * Softcam plugin to VDR (C++)
 *
 * This code is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * Or, point your browser to http://www.gnu.org/copyleft/gpl.html
 */

#ifndef ___CUSTOMPMT_H
#define ___CUSTOMPMT_H

#include "data.h"

class cCustomPMT : public cStructItem
{
public:
	bool Parse(const char* line);

	int caid;
	int source, prgId, transponder;
	int vpid, txt, pmt;
	int apid[5];
};

class cCustomPMTs : public cStructList<cCustomPMT>
{
public:
	cCustomPMTs();
	virtual cCustomPMT *ParseLine(char *line);
	//virtual void PreLoad(void);
	//virtual void PostLoad(void);
};

extern cCustomPMTs custompmts;

#endif

