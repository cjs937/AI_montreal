#include "DebugDisplay.h"
#include <allegro5/allegro_ttf.h>
#include "GraphicsBuffer.h"
#include "DebugContent.h"
#include "Color.h"
#include "GameApp.h"
#include "GridPathfinder.h"
#include "Grid.h"
#include "Path.h"
#include "Node.h"

using namespace std;

DebugDisplay::DebugDisplay( const Vector2D& pos, DebugContent* pContent )
	:mPos(pos)
	,mpContent(pContent)
{
	//actually load the font
	mpFont = al_load_ttf_font( "cour.ttf", 12, 0 );
	if( mpFont == NULL )
	{
		printf( "ttf font file not loaded properly!\n" ); 
		assert(0);
	}
}

DebugDisplay::~DebugDisplay()
{
	al_destroy_font(mpFont);
	delete mpContent;
}

void DebugDisplay::draw( GraphicsBuffer* pBuffer )
{
	Color textColor = Color(BLACK);
	string toDisplay = mpContent->getDebugString();
	al_draw_text( mpFont, textColor.color, mPos.getX(), mPos.getY(), ALLEGRO_ALIGN_LEFT, toDisplay.c_str() );


	//display "S" and "G"
	GameApp* game = static_cast<GameApp*>(gpGame);
	GridPathfinder* pathfinder = game->getPathfinder();

	if (pathfinder == NULL)
		return;

	Path currentPath = pathfinder->getPath();

	if (currentPath.getNumNodes() == 0)
		return;


	Vector2D startPos = game->getGrid()->getULCornerOfSquare(currentPath.peekNode(0)->getId()) + (game->getGrid()->getSquareSize() / 2);
	Vector2D endPos = game->getGrid()->getULCornerOfSquare(currentPath.peekNode(currentPath.getNumNodes() - 1)->getId()) + (game->getGrid()->getSquareSize() / 2);

	al_draw_text(mpFont, textColor.color, startPos.getX(), startPos.getY(), ALLEGRO_ALIGN_CENTER, "S");
	al_draw_text(mpFont, textColor.color, endPos.getX(), endPos.getY(), ALLEGRO_ALIGN_CENTER, "G");
}
