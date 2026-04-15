#include "Search.h"

void PrincipalVariationEntry (int ply, Move &move)
{
	principalVariation [ply] [ply] [FROM] = move.fromI;
	principalVariation [ply] [ply] [TO  ] = move.  toI;
	principalVariation [ply] [ply] [TYPE] = move. type;

	for (int i = ply + 1; i < pvLength [ply + 1]; i ++)
	{
		principalVariation [ply] [i] [FROM] = principalVariation [ply + 1] [i] [FROM];
		principalVariation [ply] [i] [TO  ] = principalVariation [ply + 1] [i] [TO  ];
		principalVariation [ply] [i] [TYPE] = principalVariation [ply + 1] [i] [TYPE];
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