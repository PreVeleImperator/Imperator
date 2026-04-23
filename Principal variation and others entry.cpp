#include "Search.h"

void PrincipalVariationEntry (int ply, Move &move)
{
	princVar [ply] [ply] [FROM] = move.fromI;
	princVar [ply] [ply] [TO  ] = move.  toI;
	princVar [ply] [ply] [TYPE] = move. type;

	for (int i = ply + 1; i < pvLength [ply + 1]; i ++)
	{
		princVar [ply] [i] [FROM] = princVar [ply + 1] [i] [FROM];
		princVar [ply] [i] [TO  ] = princVar [ply + 1] [i] [TO  ];
		princVar [ply] [i] [TYPE] = princVar [ply + 1] [i] [TYPE];
	}

	pvLength [ply] = pvLength [ply + 1];
}

void KillerMovesEntry (int ply, Move &move)
{
	killerMoves [ply] [1] [FROM] = killerMoves [ply] [0] [FROM];
	killerMoves [ply] [1] [TO  ] = killerMoves [ply] [0] [TO  ];
	killerMoves [ply] [1] [TYPE] = killerMoves [ply] [0] [TYPE];

	killerMoves [ply] [0] [FROM] = move.fromI;
	killerMoves [ply] [0] [TO  ] = move.  toI;
	killerMoves [ply] [0] [TYPE] = move. type;
}