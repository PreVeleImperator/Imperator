#include "Search.h"

void PvEntry (int ply, int fromI, int toI, int type)
{
	pv [ply] [ply] [FROM] = fromI;
	pv [ply] [ply] [TO  ] =   toI;
	pv [ply] [ply] [TYPE] =  type;

	for (int i = ply + 1; i < pvLength [ply + 1]; i ++)
	{
		pv [ply] [i] [FROM] = pv [ply + 1] [i] [FROM];
		pv [ply] [i] [TO  ] = pv [ply + 1] [i] [TO  ];
		pv [ply] [i] [TYPE] = pv [ply + 1] [i] [TYPE];
	}

	pvLength [ply] = pvLength [ply + 1];
}