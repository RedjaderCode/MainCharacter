// MainCharacter

#include "main.h"

const char * Title = "Game Just for you";
const uint16_t nScreenWidth = 960;//640;
const uint16_t nScreenHeight = 630;//400;

SDL_Window * cWindow;
SDL_Renderer * cRender;
SDL_Event e;

const uint8_t NUM_OF_FRAMES_WALK = 5;// MOVEMENT FRAMES
const uint8_t NUM_OF_FRAMES_ATTACK = 2;// ATTACK FRAMES
const uint8_t NUM_OF_FRAMES_IDLE = 4;// IDLE FRAMES
const uint8_t NUM_OF_FRAMES_MAGIC = 75;// MAGIC FRAMES
const uint8_t FRAMES_ANIMATION = (NUM_OF_FRAMES_ATTACK + NUM_OF_FRAMES_IDLE + NUM_OF_FRAMES_WALK) * 2.5;

uint16_t IMGW;
uint16_t IMGH;

uint8_t MAP_IMGW;
uint8_t MAP_IMGH;

uint8_t GRASS_IMGW = 31;
uint8_t GRASS_IMGH = 47;

// ANIMATION FRAMES
TEXTURE _side_walk;
TEXTURE _down_walk;
TEXTURE _up_walk;
TEXTURE _right_walk;

// ATTACK FRAMES
TEXTURE _up_attack;
TEXTURE _down_attack;
TEXTURE _side_attack;
TEXTURE _right_attack;

// IDLE FRAMES
TEXTURE _side_idle;
TEXTURE _down_idle;
TEXTURE _up_idle;
TEXTURE _right_idle;

// PICK UP
TEXTURE _pick_up;

// MAGIC FRAMES
TEXTURE _magic_spell;

// MAP SPRITES
TEXTURE _Map_Sprite[ NUM_OF_MAP_SPRITES * 5 ];

// ANIMATION FRAMES
SDL_Rect SideWalkSpriteTexture[ NUM_OF_FRAMES_WALK ];
SDL_Rect DownWalkSpriteTexture[ NUM_OF_FRAMES_WALK ];
SDL_Rect UpWalkSpriteTexture[ NUM_OF_FRAMES_WALK ];
SDL_Rect RightWalkSpriteTexture[ NUM_OF_FRAMES_WALK ];

// ATTACK FRAMES
SDL_Rect UpAttackSpriteTexture[ NUM_OF_FRAMES_ATTACK ];
SDL_Rect DownAttackSpriteTexture[ NUM_OF_FRAMES_ATTACK ];
SDL_Rect SideAttackSpriteTexture[ NUM_OF_FRAMES_ATTACK ];
SDL_Rect RightAttackSpriteTexture[ NUM_OF_FRAMES_ATTACK ];

// IDLE FRAMES
SDL_Rect UpIdleSpriteTexture[ NUM_OF_FRAMES_IDLE ];
SDL_Rect DownIdleSpriteTexture[ NUM_OF_FRAMES_IDLE ];
SDL_Rect SideIdleSpriteTexture[ NUM_OF_FRAMES_IDLE ];
SDL_Rect RightIdleSpriteTexture[ NUM_OF_FRAMES_IDLE ];

// ACTION SPRITES
SDL_Rect PickUpSpriteTexture[ NUM_OF_FRAMES_IDLE ];
SDL_Rect MagicSpellSpriteTexture[ NUM_OF_FRAMES_MAGIC ];

// MAP SPRITES
SDL_Rect MapSpriteTexture[ NUM_OF_MAP_SPRITES ];

void Init(){

	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);

	cWindow = SDL_CreateWindow(Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, nScreenWidth, nScreenHeight, SDL_WINDOW_SHOWN);
	cRender = SDL_CreateRenderer(cWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void TEXTURE::free(){

	SDL_DestroyTexture(cTexture);

	IMG_Width = 0;
	IMG_Height = 0;
}

void TEXTURE::LoadTexture(const char * PTH){

	free();
	SDL_Surface * IMG = IMG_Load(PTH);
	SDL_SetColorKey(IMG, SDL_TRUE, SDL_MapRGB(IMG->format, 0x00, 0xFF, 0xFF));
	cTexture = SDL_CreateTextureFromSurface(cRender, IMG);

	IMG_Width = IMG->w;
	IMG_Height = IMG->h;

	IMGW = IMG_Width;
	IMGH = IMG_Height;

	SDL_FreeSurface(IMG);
}

void TEXTURE::render(int x, int y, SDL_Rect * clip){

	SDL_Rect rec = {x, y, IMG_Width, IMG_Height};

	if(cTexture != NULL){
	
		rec.w = clip->w * 1.9;
		rec.h = clip->h * 1.9;
	}

	SDL_RenderCopy(cRender, cTexture, clip, &rec);
}

void LoadDims(){

	TEXTURE::sGET_TIME s;
	
	// MAGIC SPELL ANIMATION
	_magic_spell.LoadTexture("assets/magic/magicspell.png"); // Use a 2 dimensional loop to initialize

	float n1 = 0.11111111111111111111111111111111;
	float n2 = 0.22222222222222222222222222222222;
	float n3 = 0.33333333333333333333333333333333;
	float n4 = 0.44444444444444444444444444444444;
	float n5 = 0.55555555555555555555555555555556;
	float n6 = 0.66666666666666666666666666666667;
	float n7 = 0.77777777777777777777777777777778;
	float n8 = 0.88888888888888888888888888888889;	

	MagicSpellSpriteTexture[0] = {0, 0, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[1] = {IMGW * n1, 0, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[2] = {IMGW * n2, 0, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[3] = {IMGW * n3, 0, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[4] = {IMGW * n4, 0, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[5] = {IMGW * n5, 0, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[6] = {IMGW * n6, 0, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[7] = {IMGW * n7, 0, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[8] = {IMGW * n8, 0, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[9] = {0, IMGH * n1, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[10] = {IMGW * n1, IMGH * n1, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[11] = {IMGW * n2, IMGH * n1, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[12] = {IMGW * n3, IMGH * n1, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[13] = {IMGW * n4, IMGH * n1, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[14] = {IMGW * n5, IMGH * n1, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[15] = {IMGW * n6, IMGH * n1, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[16] = {IMGW * n7, IMGH * n1, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[17] = {IMGW * n8, IMGH * n1, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[18] = {0, IMGH * n2, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[19] = {IMGW * n1, IMGH * n2, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[20] = {IMGW * n2, IMGH * n2, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[21] = {IMGW * n3, IMGH * n2, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[22] = {IMGW * n4, IMGH * n2, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[23] = {IMGW * n5, IMGH * n2, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[24] = {IMGW * n6, IMGH * n2, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[25] = {IMGW * n7, IMGH * n2, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[26] = {IMGW * n8, IMGH * n2, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[27] = {0, IMGH * n3, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[28] = {IMGW * n1, IMGH * n3, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[29] = {IMGW * n2, IMGH * n3, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[30] = {IMGW * n3, IMGH * n3, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[31] = {IMGW * n4, IMGH * n3, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[32] = {IMGW * n5, IMGH * n3, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[33] = {IMGW * n6, IMGH * n3, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[34] = {IMGW * n7, IMGH * n3, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[35] = {IMGW * n8, IMGH * n3, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[36] = {0, IMGH * n4, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[37] = {IMGW * n1, IMGH * n4, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[38] = {IMGW * n2, IMGH * n4, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[39] = {IMGW * n3, IMGH * n4, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[40] = {IMGW * n4, IMGH * n4, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[41] = {IMGW * n5, IMGH * n4, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[42] = {IMGW * n6, IMGH * n4, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[43] = {IMGW * n7, IMGH * n4, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[44] = {IMGW * n8, IMGH * n4, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[45] = {0, IMGH * n5, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[46] = {IMGW * n1, IMGH * n5, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[47] = {IMGW * n2, IMGH * n5, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[48] = {IMGW * n3, IMGH * n5, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[49] = {IMGW * n4, IMGH * n5, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[50] = {IMGW * n5, IMGH * n5, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[51] = {IMGW * n6, IMGH * n5, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[52] = {IMGW * n7, IMGH * n5, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[53] = {IMGW * n8, IMGH * n5, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[54] = {0, IMGH * n6, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[55] = {IMGW * n1, IMGH * n6, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[56] = {IMGW * n2, IMGH * n6, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[57] = {IMGW * n3, IMGH * n6, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[58] = {IMGW * n4, IMGH * n6, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[59] = {IMGW * n5, IMGH * n6, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[60] = {IMGW * n6, IMGH * n6, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[61] = {IMGW * n7, IMGH * n6, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[62] = {IMGW * n8, IMGH * n6, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[63] = {0, IMGH * n7, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[64] = {IMGW * n1, IMGH * n7, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[65] = {IMGW * n2, IMGH * n7, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[66] = {IMGW * n3, IMGH * n7, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[67] = {IMGW * n4, IMGH * n7, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[68] = {IMGW * n5, IMGH * n7, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[69] = {IMGW * n6, IMGH * n7, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[70] = {IMGW * n7, IMGH * n7, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[71] = {IMGW * n8, IMGH * n7, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[72] = {0, IMGH * n8, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[73] = {IMGW * n1, IMGH * n8, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[74] = {IMGW * n2, IMGH * n8, IMGW * n1, IMGH * n1};
	MagicSpellSpriteTexture[75] = {IMGW * n3, IMGH * n8, IMGW * n1, IMGH * n1};

	for(int i=0; i<NUM_OF_MAP_SPRITES; i++){
		_Map_Sprite[i].LoadTexture("assets/map/grasstileset.png");
	}

	MapSpriteTexture[ RIGHT_TREE ] = {0, 177, 48, 63};
	MapSpriteTexture[ BULB_TREE ] = {48, 177, 47, 63};
	MapSpriteTexture[ SLANT_TREE ] = {95, 177, 59, 63};
	MapSpriteTexture[ TRI_TREE ] = {154, 177, 58, 63};

	MapSpriteTexture[ GRASS_GROUND ] = {81, 65, 31, 47};
	MapSpriteTexture[ GRASS_CYCLOPS ] = {113, 81, 47, 15};
	MapSpriteTexture[ GRASS_SNAKEEYES ] = {0, 65, 32, 47};
	MapSpriteTexture[ GRASS_GRASSBLOCK ] = {33, 65, 47, 47};

	MAP_IMGW = IMGW;
	MAP_IMGH = IMGH;

	// ANIMATION FRAMES
	_side_walk.LoadTexture("assets/_side_walk.png");

	SideWalkSpriteTexture[0] = {0, 0, IMGW * 0.25, IMGH * 0.5};
	SideWalkSpriteTexture[1] = {IMGW * 0.25, 0, IMGW * 0.25, IMGH * 0.5};
	SideWalkSpriteTexture[2] = {IMGW * 0.5, 0, IMGW * 0.25, IMGH * 0.5};
	SideWalkSpriteTexture[3] = {IMGW * 0.75, 0, IMGW * 0.25, IMGH * 0.5};
	SideWalkSpriteTexture[4] = {0, IMGH * 0.5, IMGW * 0.25, IMGH * 0.5};
	SideWalkSpriteTexture[5] = {IMGW * 0.25, IMGH * 0.5, IMGW * 0.25, IMGH * 0.5};

	_down_walk.LoadTexture("assets/_down_walk.png");

	DownWalkSpriteTexture[0] = {0, 0, IMGW * 0.25, IMGH * 0.5};
	DownWalkSpriteTexture[1] = {IMGW * 0.25, 0, IMGW * 0.25, IMGH * 0.5};
	DownWalkSpriteTexture[2] = {IMGW * 0.5, 0, IMGW * 0.25, IMGH * 0.5};
	DownWalkSpriteTexture[3] = {IMGW * 0.75, 0, IMGW * 0.25, IMGH * 0.5};
	DownWalkSpriteTexture[4] = {0, IMGH * 0.5, IMGW * 0.25, IMGH * 0.5};
	DownWalkSpriteTexture[5] = {IMGW * 0.25, IMGH * 0.5, IMGW * 0.25, IMGH * 0.5};

	_up_walk.LoadTexture("assets/_up_walk.png");

	UpWalkSpriteTexture[0] = {0, 0, IMGW * 0.25, IMGH * 0.5};
	UpWalkSpriteTexture[1] = {IMGW * 0.25, 0, IMGW * 0.25, IMGH * 0.5};
	UpWalkSpriteTexture[2] = {IMGW * 0.5, 0, IMGW * 0.25, IMGH * 0.5};
	UpWalkSpriteTexture[3] = {IMGW * 0.75, 0, IMGW * 0.25, IMGH * 0.5};
	UpWalkSpriteTexture[4] = {0, IMGH * 0.5, IMGW * 0.25, IMGH * 0.5};
	UpWalkSpriteTexture[5] = {IMGW * 0.25, IMGH * 0.5, IMGW * 0.25, IMGH * 0.5};

	_right_walk.LoadTexture("assets/_right_walk.png");

	RightWalkSpriteTexture[0] = {0, 0, IMGW * 0.25, IMGH * 0.5};
	RightWalkSpriteTexture[1] = {IMGW * 0.25, 0, IMGW * 0.25, IMGH * 0.5};
	RightWalkSpriteTexture[2] = {IMGW * 0.5, 0, IMGW * 0.25, IMGH * 0.5};
	RightWalkSpriteTexture[3] = {IMGW * 0.75, 0, IMGW * 0.25, IMGH * 0.5};
	RightWalkSpriteTexture[4] = {IMGW * 0.5, IMGH * 0.5, IMGW * 0.25, IMGH * 0.5};
	RightWalkSpriteTexture[5] = {IMGW * 0.75, IMGH * 0.5, IMGW * 0.25, IMGH * 0.5};

	// ATTACK FRAMES
	_up_attack.LoadTexture("assets/_up_attack.png");

	UpAttackSpriteTexture[0] = {0, 0, IMGW * 0.5, IMGH * 0.5};
	UpAttackSpriteTexture[1] = {IMGW * 0.5, 0, IMGW * 0.5, IMGH * 0.5};
	UpAttackSpriteTexture[2] = {0, IMGH * 0.5, IMGW * 0.5, IMGH * 0.5};

	_down_attack.LoadTexture("assets/_down_attack.png");

	DownAttackSpriteTexture[0] = {0, 0, IMGW * 0.5, IMGH * 0.5};
	DownAttackSpriteTexture[1] = {IMGW * 0.5, 0, IMGW * 0.5, IMGH * 0.5};
	DownAttackSpriteTexture[2] = {0, IMGH * 0.5, IMGW * 0.5, IMGH * 0.5};

	_side_attack.LoadTexture("assets/_side_attack.png");

	SideAttackSpriteTexture[0] = {0, 0, IMGW * 0.5, IMGH * 0.5};
	SideAttackSpriteTexture[1] = {IMGW * 0.5, 0, IMGW * 0.5, IMGH * 0.5};
	SideAttackSpriteTexture[2] = {0, IMGH * 0.5, IMGW * 0.5, IMGH * 0.5};

	_right_attack.LoadTexture("assets/_right_attack.png");

	RightAttackSpriteTexture[0] = {0, 0, IMGW * 0.5, IMGH * 0.5};
	RightAttackSpriteTexture[1] = {IMGW * 0.5, 0, IMGW * 0.5, IMGH * 0.5};
	RightAttackSpriteTexture[2] = {IMGW * 0.5, IMGH * 0.5, IMGW * 0.5, IMGH * 0.5};

	// IDLE ANIMATIONS
	_up_idle.LoadTexture("assets/_up_idle.png");

	UpIdleSpriteTexture[0] = {0, 0, IMGW * 0.25, IMGH * 0.5};
	UpIdleSpriteTexture[1] = {IMGW * 0.25, 0, IMGW * 0.25, IMGH * 0.5};
	UpIdleSpriteTexture[2] = {IMGW * 0.5, 0, IMGW * 0.25, IMGH * 0.5};
	UpIdleSpriteTexture[3] = {IMGW * 0.75, 0, IMGW * 0.25, IMGH * 0.5};
	UpIdleSpriteTexture[4] = {0, IMGH * 0.5, IMGW * 0.25, IMGH * 0.5};

	_down_idle.LoadTexture("assets/_down_idle.png");

	DownIdleSpriteTexture[0] = {0, 0, IMGW * 0.25, IMGH * 0.5};
	DownIdleSpriteTexture[1] = {IMGW * 0.25, 0, IMGW * 0.25, IMGH * 0.5};
	DownIdleSpriteTexture[2] = {IMGW * 0.5, 0, IMGW * 0.25, IMGH * 0.5};
	DownIdleSpriteTexture[3] = {IMGW * 0.75, 0, IMGW * 0.25, IMGH * 0.5};
	DownIdleSpriteTexture[4] = {0, IMGH * 0.5, IMGW * 0.25, IMGH * 0.5};
	
	_side_idle.LoadTexture("assets/_side_idle.png");

	SideIdleSpriteTexture[0] = {0, 0, IMGW * 0.25, IMGH * 0.5};
	SideIdleSpriteTexture[1] = {IMGW * 0.25, 0, IMGW * 0.25, IMGH * 0.5};
	SideIdleSpriteTexture[2] = {IMGW * 0.5, 0, IMGW * 0.25, IMGH * 0.5};
	SideIdleSpriteTexture[3] = {IMGW * 0.75, 0, IMGW * 0.25, IMGH * 0.5};
	SideIdleSpriteTexture[4] = {0, IMGH * 0.5, IMGW * 0.25, IMGH * 0.5};

	_right_idle.LoadTexture("assets/_right_idle.png");

	RightIdleSpriteTexture[0] = {0, 0, IMGW * 0.25, IMGH * 0.5};
	RightIdleSpriteTexture[1] = {IMGW * 0.25, 0, IMGW * 0.25, IMGH * 0.5};
	RightIdleSpriteTexture[2] = {IMGW * 0.5, 0, IMGW * 0.25, IMGH * 0.5};
	RightIdleSpriteTexture[3] = {IMGW * 0.75, 0, IMGW * 0.25, IMGH * 0.5};
	RightIdleSpriteTexture[4] = {IMGW * 0.75, IMGH * 0.5, IMGW * 0.25, IMGH * 0.5};

	// PICK UP ANIMATION
	_pick_up.LoadTexture("assets/_pick_up.png");

	PickUpSpriteTexture[0] = {0, 0, IMGW * 0.25, IMGH * 0.5};
	PickUpSpriteTexture[1] = {IMGW * 0.25, 0, IMGW * 0.25, IMGH * 0.5};
	PickUpSpriteTexture[2] = {IMGW * 0.5, 0, IMGW * 0.25, IMGH * 0.5};
	PickUpSpriteTexture[3] = {IMGW * 0.75, 0, IMGW * 0.25, IMGH * 0.5};
	PickUpSpriteTexture[4] = {0, IMGH * 0.5, IMGW * 0.25, IMGH * 0.5};
}

void close(){

	SDL_DestroyWindow(cWindow);
	SDL_DestroyRenderer(cRender);

	_side_walk.free();
	_down_walk.free();
	_up_walk.free();
	_right_walk.free();

	_up_attack.free();
	_down_attack.free();
	_side_attack.free();
	_right_attack.free();

	_down_idle.free();
	_side_idle.free();
	_up_idle.free();
	_right_idle.free();

	SDL_Quit();
	IMG_Quit();
}

int main(int s, char * z[]){

	printf("Controls:\n\n    w\n   asd\n\n Left Alt: Magic Powers \n E: Pick up\n F: Attack -> it needs work lol. You have to move for it to work\n\n\t");

	bool running = true;
	uint8_t nFrame = 0;
	uint8_t nFrameMagic = 0;
	const uint8_t * input = SDL_GetKeyboardState(NULL);
	uint16_t nMapGrassIteration = 4;
	uint8_t TREES = 10;

	uint16_t RandomWidth[ NUM_OF_MAP_SPRITES ];
	uint16_t RandomHeight[ NUM_OF_MAP_SPRITES ];
	uint8_t RandomTree[ NUM_OF_MAP_SPRITES ];

	for(int i=0; i<TRI_TREE + TREES; i++){
		RandomWidth[i] = rand() % (int)(nScreenWidth * 0.75) + (int)(nScreenWidth * 0.10);
		for(int i=0; i<TRI_TREE + 1; i++){
			for(int y=0; y<TRI_TREE + 1; y++){

				if(RandomWidth[i] + (MAP_IMGW * 0.5) >= RandomWidth[i + y] + (MAP_IMGW * 0.5) && RandomWidth[i] + (MAP_IMGW * 0.5) <= RandomWidth[i + y] + MAP_IMGW 
				|| RandomWidth[i] + (MAP_IMGW * 0.5) <= RandomWidth[i + y] + (MAP_IMGW * 0.5) && RandomWidth[i] + (MAP_IMGW * 0.5) >= RandomWidth[i + y])
					{RandomWidth[i] - 100;}
			}
		}
			
		RandomHeight[i] = rand() % (int)(nScreenHeight * 0.65) + (int)(nScreenHeight * 0.05);
		for(int i=0; i<TRI_TREE + 1; i++){
			for(int y=0; y<TRI_TREE + 1; y++){

				if(RandomHeight[i] + (MAP_IMGH * 0.5) >= RandomHeight[i + y] + (MAP_IMGH * 0.5) && RandomHeight[i] + (MAP_IMGH * 0.5) <= RandomHeight[i + y] + MAP_IMGH
				|| RandomHeight[i] + (MAP_IMGH * 0.5) <= RandomHeight[i + y] + (MAP_IMGH * 0.5) && RandomHeight[i] + (MAP_IMGH * 0.5) >= RandomHeight[i + y])
					{RandomHeight[i] + 100;}
			}
		}

		RandomTree[i] = rand() % (TRI_TREE + 1) + RIGHT_TREE;
	}

	Init();
	LoadDims();

	char key = ' ';

	uint16_t WALK_IMG_POS_X = ((nScreenWidth - /*TEXTURE::Width()*/IMGW*0.25) * 0.5);
	uint16_t WALK_IMG_POS_Y = ((nScreenHeight - /*TEXTURE::Height()*/IMGH*0.5) * 0.5);

	uint16_t WALK_IMG_POS_MAGIC_X = 0;
	uint16_t WALK_IMG_POS_MAGIC_Y = ((nScreenHeight - IMGH*0.5) * 0.5);

	while(running){

		SDL_SetRenderDrawColor(cRender, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(cRender);

		while(SDL_PollEvent(&e)){
		
			switch(e.type){
			
				case SDL_QUIT:
					close();
					running = false;
					break;
			}
					if(input[ SDL_SCANCODE_A ] || input[ SDL_SCANCODE_LEFT ]){ key = 'a'; }
					else if(input[ SDL_SCANCODE_S ] || input[ SDL_SCANCODE_DOWN ]){ key = 's'; }
					else if(input[ SDL_SCANCODE_W ] || input[ SDL_SCANCODE_UP ]){ key = 'w'; }
					else if(input[ SDL_SCANCODE_D ] || input[ SDL_SCANCODE_RIGHT ]){ key = 'd'; }
					else if(input[ SDL_SCANCODE_E ]){ key = 'e'; }

					else{
						key = ' ';
					}
		}

		// GRASS LAYER
		for(int y=0; y <= nScreenHeight - GRASS_IMGH; y += GRASS_IMGH){
			for(int x=0; x <= nScreenWidth - GRASS_IMGW; x += GRASS_IMGW){
				_Map_Sprite[ nMapGrassIteration ].render(x, y, &MapSpriteTexture[ GRASS_GROUND ]);
			}
		}

		// TREES
		for(int i=0; i<TRI_TREE + TREES; i++){
			_Map_Sprite[ RandomTree[i] ].render(RandomWidth[i], RandomHeight[i], &MapSpriteTexture[ RandomTree[i] ]);
		}
		
		if(key == 'a'){ _side_walk.render(WALK_IMG_POS_X, WALK_IMG_POS_Y, &SideWalkSpriteTexture[(nFrame + 1) / NUM_OF_FRAMES_WALK]);

			nFrame++;
			if((nFrame + 1) / NUM_OF_FRAMES_WALK > NUM_OF_FRAMES_WALK)
				nFrame = 0;

			WALK_IMG_POS_X -= NUM_OF_FRAMES_WALK / 1.5;
			if((WALK_IMG_POS_X - NUM_OF_FRAMES_WALK) < nScreenWidth * 0.10)
				WALK_IMG_POS_X = nScreenWidth * 0.10;

			if(input[ SDL_SCANCODE_F]){

				nFrame = 0;

				for(int i=0; i < NUM_OF_FRAMES_ATTACK; i++){

					nFrame++;
					if((nFrame + 1) / NUM_OF_FRAMES_ATTACK < NUM_OF_FRAMES_ATTACK){
						_side_attack.render(WALK_IMG_POS_X, WALK_IMG_POS_Y, &SideAttackSpriteTexture[(nFrame + 1) / NUM_OF_FRAMES_ATTACK]);
					SDL_RenderPresent(cRender);
					}
				}
			}
		}
		else if(key == 's'){ _down_walk.render(WALK_IMG_POS_X, WALK_IMG_POS_Y, &DownWalkSpriteTexture[(nFrame + 1) / NUM_OF_FRAMES_WALK]);

			nFrame++;
			if((nFrame + 1) / NUM_OF_FRAMES_WALK > NUM_OF_FRAMES_WALK)
				nFrame = 0;

			WALK_IMG_POS_Y += NUM_OF_FRAMES_WALK / 1.5;
			if((WALK_IMG_POS_Y + NUM_OF_FRAMES_WALK) > nScreenHeight * 0.65)
				WALK_IMG_POS_Y = nScreenHeight * 0.65;
			
			if(input[ SDL_SCANCODE_F]){
				
				nFrame = 0;

				for(int i=0; i < NUM_OF_FRAMES_ATTACK; i++){

					nFrame++;
					if((nFrame + 1) / NUM_OF_FRAMES_ATTACK < NUM_OF_FRAMES_ATTACK){
						_down_attack.render(WALK_IMG_POS_X, WALK_IMG_POS_Y, &DownAttackSpriteTexture[(nFrame + 1) / NUM_OF_FRAMES_ATTACK]);
					SDL_RenderPresent(cRender);
					}
				}
			}
		}
		else if(key == 'w'){ _up_walk.render(WALK_IMG_POS_X, WALK_IMG_POS_Y, &UpWalkSpriteTexture[(nFrame + 1) / NUM_OF_FRAMES_WALK]);

			nFrame++;
			if((nFrame + 1) / NUM_OF_FRAMES_WALK > NUM_OF_FRAMES_WALK)
				nFrame = 0;

			WALK_IMG_POS_Y -= NUM_OF_FRAMES_WALK / 1.5;
			if((WALK_IMG_POS_Y - NUM_OF_FRAMES_WALK) < nScreenHeight * 0.05)
				WALK_IMG_POS_Y = nScreenHeight * 0.05;

			if(input[ SDL_SCANCODE_F]){
						
				nFrame = 0;

				for(int i=0; i < NUM_OF_FRAMES_ATTACK; i++){

					nFrame++;
					if((nFrame + 1) / NUM_OF_FRAMES_ATTACK < NUM_OF_FRAMES_ATTACK){
						_up_attack.render(WALK_IMG_POS_X, WALK_IMG_POS_Y, &UpAttackSpriteTexture[(nFrame + 1) / NUM_OF_FRAMES_ATTACK]);
					SDL_RenderPresent(cRender);
					}
				}
			}
		}
		else if(key == 'd'){ _right_walk.render(WALK_IMG_POS_X, WALK_IMG_POS_Y, &RightWalkSpriteTexture[(nFrame + 2) / NUM_OF_FRAMES_WALK]);

			nFrame++;
			if((nFrame + 1) / NUM_OF_FRAMES_WALK > NUM_OF_FRAMES_WALK)
				nFrame = 0;

			WALK_IMG_POS_X += NUM_OF_FRAMES_WALK / 1.5;
			if((WALK_IMG_POS_X + NUM_OF_FRAMES_WALK) > nScreenWidth * 0.75)
				WALK_IMG_POS_X = nScreenWidth * 0.75;

			if(input[ SDL_SCANCODE_F]){
						
				nFrame = 0;

				for(int i=0; i < NUM_OF_FRAMES_ATTACK; i++){

					nFrame++;
					if((nFrame + 1) / NUM_OF_FRAMES_ATTACK < NUM_OF_FRAMES_ATTACK){
						_right_attack.render(WALK_IMG_POS_X, WALK_IMG_POS_Y, &RightAttackSpriteTexture[(nFrame + 1) / NUM_OF_FRAMES_ATTACK]);
					SDL_RenderPresent(cRender);
					}
				}
			}
		}
		else if(key == 'e'){

			bool LastFrame = false;
			nFrame = 0;
		
			while(!LastFrame){

				nFrame++;
				if((nFrame + 1) / NUM_OF_FRAMES_IDLE < NUM_OF_FRAMES_IDLE){

					_pick_up.render(WALK_IMG_POS_X, WALK_IMG_POS_Y, &PickUpSpriteTexture[(nFrame + 1) / NUM_OF_FRAMES_IDLE]);

					SDL_Delay(FRAMES_ANIMATION);
					SDL_RenderPresent(cRender);
				}
				else{

					LastFrame = true;
					key = ' ';
				}
			}
		
			SDL_Delay(300);
		}

		else{
			_down_idle.render(WALK_IMG_POS_X, WALK_IMG_POS_Y, &DownIdleSpriteTexture[(nFrame + 1) / 4]);
			nFrame++;
			if((nFrame + 1) / 4 > NUM_OF_FRAMES_IDLE)
				nFrame = 0;
		}

		_magic_spell.render(WALK_IMG_POS_MAGIC_X, WALK_IMG_POS_MAGIC_Y, &MagicSpellSpriteTexture[(nFrameMagic + 1) / 2]);
		nFrameMagic++;
		if((nFrameMagic + 1) / 2 > NUM_OF_FRAMES_MAGIC)
			nFrameMagic = 0;
		WALK_IMG_POS_MAGIC_X++;

		if(WALK_IMG_POS_MAGIC_X + 1 > nScreenWidth * 0.75)
			WALK_IMG_POS_MAGIC_X = nScreenWidth * 0.75;

		SDL_Delay(FRAMES_ANIMATION);
		SDL_RenderPresent(cRender);
	}

	return 0;
}