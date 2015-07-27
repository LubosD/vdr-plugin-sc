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

#include "custompmt.h"
#include <vdr/sources.h>
#include <vdr/channels.h>
#include <cstring>

cCustomPMTs custompmts;

bool cCustomPMT::Parse(const char *line)
{
	char srcBuf[16];
	char apidBuf[32];
	int num, freq;
	char pol;

	if (sscanf(line, "%d:%c:%15[^:]:%d%n", &freq, &pol, srcBuf, &prgId, &num) == 4)
	{
		source = cSource::FromString(srcBuf);
		line += num;
		txt = 0;

		transponder=freq;
		while (transponder > 20000) transponder /= 1000;
		if (cSource::IsSat(source)) transponder=cChannel::Transponder(transponder, pol);

		if (sscanf(line, "%04x:%d:%31[^:]:%d", &caid, &vpid, apidBuf, &txt) >= 2 && apidBuf[0] != '\0')
		{
			char* apidPtr = apidBuf;
			int count = 0;

			memset(apid, 0, sizeof(apid));

			while (true)
			{
				int n = strtol(apidPtr, &apidPtr, 10);
				apid[count++] = n;

				if (*apidPtr != ',')
					break;
			}
			return true;
		}
	}

	return false;
}

cCustomPMTs::cCustomPMTs()
	: cStructList<cCustomPMT>("custompmts", "pmt.conf", SL_MISSINGOK|SL_WATCH|SL_VERBOSE)
{
}

cCustomPMT* cCustomPMTs::ParseLine(char *line)
{
	cCustomPMT* pmt = new cCustomPMT;

	if (pmt->Parse(line))
		return pmt;
	else
	{
		delete pmt;
		return 0;
	}
}

/*
void cCustomPMTs::PreLoad(void)
{
}

void cCustomPMTs::PostLoad(void)
{
}
*/

