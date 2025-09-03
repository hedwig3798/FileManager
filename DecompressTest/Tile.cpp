#include "pch.h"
#include "Tile.h"

Tile::Tile()
{

}

Tile::~Tile()
{

}

void Tile::update()
{

}

void Tile::render(HDC _dc)
{
	Rectangle(_dc, GetPos().x, GetPos().y, GetPos().x + BOARD_TILE, GetPos().y + BOARD_TILE);
}

void Tile::OnCollision(CCollider* _pOther)
{
}

void Tile::OnCollisionEnter(CCollider* _pOther)
{
}

void Tile::OnCollisionExit(CCollider* _pOther)
{
}
