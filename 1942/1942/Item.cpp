#include "Item.h"

#include "default.h"

Item::Item(HGE* hge,ItemType t,float xx,float yy)
	:hgeSprite(0,0,0,0,0){
	//¼ÓÔØÍ¼Æ¬×ÊÔ´
	type=t;
	x=xx;
	y=yy;
	this->hge=hge;
	HTEXTURE tex;
	switch (type){
	case ItemType::HP_PLUS:
		tex=hge->Texture_Load("hp.png");
		SetTexture(tex);
		SetTextureRect(0,0,hge->Texture_GetWidth(tex),hge->Texture_GetHeight(tex));
		value=20;
		break;
	case ItemType::PROTECT:
		tex=hge->Texture_Load("protect.png");
		SetTexture(tex);
		SetTextureRect(0,0,hge->Texture_GetWidth(tex),hge->Texture_GetHeight(tex));
		value=3;
		break;
	case ItemType::POISON:
		tex=hge->Texture_Load("poison.png");
		SetTexture(tex);
		SetTextureRect(0,0,hge->Texture_GetWidth(tex),hge->Texture_GetHeight(tex));
		value=20;
		break;
	case ItemType::CLEAR:
		tex=hge->Texture_Load("clear.png");
		SetTexture(tex);
		SetTextureRect(0,0,hge->Texture_GetWidth(tex),hge->Texture_GetHeight(tex));
		value=0;
		break;
	case ItemType::UPGRADE:
		tex=hge->Texture_Load("upgrade.png");
		SetTexture(tex);
		SetTextureRect(0,0,hge->Texture_GetWidth(tex),hge->Texture_GetHeight(tex));
		value=5;
		break;
	}
}

void Item::Render(){
	hgeSprite::Render(x,y);
}

void Item::move(float dt){
	y+=50*dt/FPS;
}

bool Item::is_out(){
	return (y>=SCREENHEIGHT);
}