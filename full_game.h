#define ACCEL 30
#define DECEL 50
#define GRAVITY 0x4c
#define MAX_SPEED 0x240
#define JUMP_VEL -0x600
#define MAX_RIGHT 0x9000



#pragma bss-name(push, "ZEROPAGE")

// GLOBAL VARIABLES
unsigned char pad1;
unsigned char pad1_new;
unsigned char collision;
unsigned char collision_L;
unsigned char collision_R;
unsigned char collision_U;
unsigned char collision_D;
unsigned char coordinates;
unsigned char temp1;
unsigned char temp2;
unsigned char temp3;
unsigned char temp4;
unsigned int temp5;
unsigned int temp6;
unsigned char eject_L; // from the left
unsigned char eject_R; // remember these from the collision sub routine
unsigned char eject_D; // from below
unsigned char eject_U; // from up
unsigned char direction; //facing left or right?
#define LEFT 0
#define RIGHT 1

int address;
unsigned char x; // room loader code
unsigned char y;
unsigned char nt;
unsigned char index;
unsigned char index2;
unsigned char room;
unsigned char map;
unsigned int scroll_x;
unsigned int scroll_y;
unsigned char scroll_count;
unsigned int pseudo_scroll_x;
//unsigned int pseudo_scroll_y;
unsigned char L_R_switch;
unsigned int old_x;
//unsigned char old_y;
unsigned char temp_x;
unsigned char temp_y;
unsigned char song;
#define MAX_SONGS 2
enum {SONG_GAME, SONG_PAUSE};
enum {SFX_JUMP, SFX_DING, SFX_NOISE};

unsigned char game_mode;
enum {MODE_TITLE, MODE_GAME, MODE_PAUSE, MODE_SWITCH, MODE_END, 
MODE_GAME_OVER, MODE_RESET};

unsigned char coins;
unsigned char lives;
const unsigned char * pointer;
unsigned char level;
unsigned char offset;
unsigned char level_up;
unsigned char bright;
unsigned char bright_count;
unsigned char death;
unsigned char timer;
unsigned char enemy_frames; //in case of skipped frames
unsigned char map_loaded; //only load it once
unsigned char short_jump_count;

unsigned char temp_room;


#pragma bss-name(push, "BSS")

unsigned char c_map[240];
unsigned char c_map2[240];

struct Base {
	unsigned char x;
	unsigned char y;
	unsigned char width;
	unsigned char height;
};

struct Base Generic; 
struct Base Generic2; 

struct Hero {
	unsigned int x; // low byte is sub-pixel
	unsigned int y;
	signed int vel_x; // speed, signed, low byte is sub-pixel
	signed int vel_y;
};

struct Hero BoxGuy1;
// the width and height should be 1 less than the dimensions (14x12)
// note, I'm using the top left as the 0,0 on x,y

#define HERO_WIDTH 13
#define HERO_HEIGHT 11


#define MAX_COINS 16
unsigned char coin_x[MAX_COINS];
unsigned char coin_y[MAX_COINS];
unsigned char coin_active[MAX_COINS];
unsigned char coin_room[MAX_COINS];
unsigned char coin_actual_x[MAX_COINS];
unsigned char coin_type[MAX_COINS];


#define TURN_OFF 0xff
#define COIN_WIDTH 7
#define COIN_HEIGHT 11
#define BIG_COIN 13


#define MAX_ENEMY 16
unsigned char enemy_x[MAX_ENEMY];
unsigned char enemy_y[MAX_ENEMY];
unsigned char enemy_active[MAX_ENEMY];
unsigned char enemy_room[MAX_ENEMY];
unsigned char enemy_actual_x[MAX_ENEMY];
unsigned char enemy_type[MAX_ENEMY];
const unsigned char * enemy_anim[MAX_ENEMY];

#define ENEMY_WIDTH 13
#define ENEMY_HEIGHT 13


//for shuffling 16 enemies
const unsigned char shuffle_array[]={
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,
0,2,4,6,8,10,12,14,1,3,5,7,9,11,13,15,
15,13,11,9,7,5,3,1,14,12,10,8,6,4,2,0	
};


const unsigned char palette_title[]={
// A deep space background, with a glowing, slightly softer title text
0x0F,0x01,0x11,0x28, // Black, Deep Blue, Dark Purple, Soft Gold/Orange (for glowing title)
0, 0, 0, 0,          // Keep unused palettes black
0, 0, 0, 0,
0, 0, 0, 0
}; 


const unsigned char title_color_rotate[]={
    0x28,0x18,0x08,0x01 // Rotate between Soft Gold, Light Orange, Dark Orange, Deep Blue
};


const unsigned char palette_bg[]={
// Palette 0: Deep space/night sky with more subtle dark variations
0x0F,0x01,0x11,0x0C, // Black (space), Deep Blue, Dark Purple, Dark Cyan/Teal (for subtle nebula)
// Palette 1: Asteroids/metallic structures - softer greys, hint of blue
0x0F,0x00,0x10,0x20, // Black, Dark Grey, Mid Grey, Light Grey (for rocks/metal) - *unchanged, as this looked good*
// Palette 2: Alien ground/glowing elements - softened brights
0x0F,0x03,0x13,0x23, // Black, Dark Green/Cyan, Mid Green/Cyan, Softer Green/Cyan (alien ground/energy)
// Palette 3: More distinct space objects/starry sky - brighter blues, some sparkle
0x0F,0x01,0x12,0x22 // Black, Deep Blue, Medium Blue, Bright Blue (for stars, distant gas, more vibrant)
}; 


const unsigned char palette_sp[]={
// Sprite Palette 0: Player Character (your blue guy)
0x0F, 0x01, 0x11, 0x30, // Transparent, Deep Blue, Dark Gray, Bright Yellow (suit accents/glow)
// Sprite Palette 1: Coins/Collectibles - still good, glowing gold
0x0F, 0x07, 0x17, 0x27, // Transparent, Dark Gold, Mid Gold, Bright Gold (metallic coins)
// Sprite Palette 2: Enemies / General Light Elements - Muted light blue/cyan for visibility
0x0F, 0x0B, 0x1B, 0x2B, // Transparent (0x0F), Dark Gray (0x0B), Mid Blue-Gray (0x1B), Light Blue/Cyan (0x2B)
// Sprite Palette 3: Projectiles/Effects - still good
0x0F, 0x0C, 0x1C, 0x2C, // Transparent, Dark Cyan, Mid Cyan, Bright Cyan
};






const unsigned char TITLE_TEXT1[]="Void Jumper";
const unsigned char TITLE_TEXT2[]="Press Start";
const unsigned char TITLE_TEXT3[]="A Game By William";

const unsigned char END_TEXT[]="end of the game.";
const unsigned char END_TEXT2[]="you won!";
const unsigned char END_TEXT3[]="Coins: ";

const unsigned char DEAD_TEXT[]="death";



#include "NES_ST/title.h"



// PROTOTYPES
void load_title(void);
void load_room(void);
void draw_sprites(void);
void movement(void);	
void draw_screen_R(void);
void new_cmap(void);
char bg_collision_sub(void);
char get_position(void);
void enemy_moves(void);
void sprite_collisions(void);
void check_spr_objects(void);
void sprite_obj_init(void);
void set_sprite_zero(void);
void update_hud(void);
void bg_collision_fast(void);

char bg_coll_L(void);
char bg_coll_R(void);
char bg_coll_U(void);
char bg_coll_D(void);
char bg_coll_D2(void);

