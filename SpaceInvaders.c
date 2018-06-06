#include "..//tm4c123gh6pm.h"
#include "Nokia5110.h"
#include "Random.h"
#include "TExaS.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"
#include "UART.h"

#define BOARD_ROWS 175
#define BOARD_ROW 175
#define ind 0

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Delay100ms(unsigned long count); // time delay in 0.1 seconds
unsigned long TimerCount;
unsigned long Semaphore;
void PortF_Init(void);
void printScreen();
void draw();
void draw_tie();
void draw_win(int );
void win(void);
void Lose(void);
void view ();
void Screen1();
void mode1();
void mode2();
void HIDE_SHOW_X();
void HIDE_SHOW_O();
void Master_Slave();
void First_Second();
void HIDE();
int check_win1(int ,int);
int check_win2(int ,int);
int valid(int ,int );
void generate_ply2();
void mode();
void SHOW();
int valid_Position(int );
int tie();
void generate_mode2();

struct image
{
    unsigned int ro, co, w, h;
    unsigned char* imagePtr;
    unsigned char* imagePtr2;
};
typedef struct image img;
typedef struct image img2;
img imag[100];
img2 imag2[100];
//int i;

// ************************* Images *************************

const unsigned char Red[] =
{
    0x42, 0x4D, 0x96, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x20, 0x01, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
    0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0x0F, 0xFF, 0x0F, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF,
    0x0F, 0xF0, 0xFF, 0x0F, 0xFF, 0x0F, 0xF0, 0xFF, 0xF0, 0xFF, 0xFF, 0x0F, 0xF0, 0xFF, 0x0F, 0xFF, 0x0F, 0xFF, 0x0F, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0x0F, 0xF0, 0xFF, 0x0F, 0xFF, 0x0F, 0xF0, 0xFF,
    0xF0, 0xFF, 0xFF, 0x0F, 0xF0, 0xFF, 0x0F, 0xFF, 0x0F, 0xFF, 0x0F, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0x0F, 0xFF, 0x0F, 0xF0, 0xFF, 0xF0, 0xFF, 0xFF, 0x0F, 0xF0, 0xFF, 0x0F, 0xFF,
    0x0F, 0xFF, 0x0F, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0x0F, 0xFF, 0x0F, 0xF0, 0xFF, 0xF0, 0xFF, 0xFF, 0x0F, 0xF0, 0xFF, 0x0F, 0xFF, 0x0F, 0xFF, 0x0F, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0xFF, 0x0F, 0xFF, 0x0F, 0xF0, 0xFF, 0xF0, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 0x0F, 0xFF, 0x0F, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x0F, 0xF0, 0xFF, 0x0F, 0xFF, 0x0F, 0xF0, 0xFF,
    0xF0, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xF0, 0xFF, 0x00, 0x00, 0x0F, 0xF0, 0xFF, 0xF0, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 0x0F, 0xFF,
    0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,

};

const unsigned char lose[] =
{
    0x42, 0x4D, 0x96, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x20, 0x01, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
    0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xF0, 0x00, 0x00, 0xF0, 0x00, 0x0F, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
    0x0F, 0xF0, 0xFF, 0x0F, 0xFF, 0x0F, 0xF0, 0xFF, 0xF0, 0xFF, 0xFF, 0x0F, 0xFF, 0xF0, 0xFF, 0xF0, 0xFF, 0xFF, 0x0F, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xF0, 0xFF, 0x0F, 0xFF, 0x0F, 0xF0, 0xFF,
    0xF0, 0xFF, 0xFF, 0x0F, 0xFF, 0xF0, 0xFF, 0xF0, 0xFF, 0xFF, 0x0F, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0x0F, 0xFF, 0x0F, 0xF0, 0xFF, 0xF0, 0xFF, 0xFF, 0x0F, 0xFF, 0xF0, 0xFF, 0xF0,
    0xF0, 0x00, 0x0F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0x0F, 0xFF, 0x0F, 0xF0, 0xFF, 0xF0, 0xFF, 0xFF, 0x0F, 0xFF, 0xF0, 0xFF, 0xF0, 0xF0, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0xFF, 0x0F, 0xFF, 0x0F, 0xF0, 0xFF, 0xF0, 0xFF, 0xFF, 0x0F, 0xFF, 0xF0, 0xFF, 0xF0, 0xF0, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xF0, 0xFF, 0x0F, 0xFF, 0x0F, 0xF0, 0xFF,
    0xF0, 0xFF, 0xFF, 0x0F, 0xFF, 0xF0, 0xFF, 0xF0, 0xF0, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xF0, 0xFF, 0x00, 0x00, 0x0F, 0xF0, 0xFF, 0xF0, 0xFF, 0xFF, 0x0F, 0xFF, 0xF0, 0x00, 0x00,
    0xF0, 0x00, 0x0F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

const unsigned char yo[] =
{
    0x42, 0x4D, 0x96, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x80, 0xFF, 0x00, 0x80,
    0x00, 0xFF, 0x00, 0x80, 0x80, 0xFF, 0x80, 0x00, 0x00, 0xFF, 0x80, 0x00, 0x80, 0xFF, 0x80, 0x80, 0x00, 0xFF, 0x80, 0x80, 0x80, 0xFF, 0xC0, 0xC0, 0xC0, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF,
    0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x0F, 0xF0, 0x00,
    0x00, 0x0F, 0xF0, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

unsigned char temp1[] =
{
    0x42, 0x4D, 0x8E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
    0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x0F, 0xFF,
    0xF0, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,

};




// blank space to cover a laser after it hits something
// width=2 x height=9

//175
unsigned char player11[] =
{
    0x42, 0x4D, 0xAE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
    0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x08, 0x88, 0x88, 0x88, 0x80, 0x00, 0x00, 0x00, 0x7F, 0xFF,
    0xFF, 0xFF, 0xF7, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xF7, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xF7, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xF7, 0x00, 0x00, 0x00, 0x7F, 0xFF,
    0xFF, 0xFF, 0xF7, 0x00, 0x00, 0x00, 0x07, 0x77, 0x77, 0x77, 0x70, 0x00, 0x00, 0x00, 0xFF,

};

//175
unsigned char player22[] =
{
    0x42, 0x4D, 0xAE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
    0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x07, 0x77, 0x77, 0x77, 0x70, 0x00, 0x00, 0x00, 0x7F, 0xFF,
    0xFF, 0xFF, 0xF7, 0x00, 0x00, 0x00, 0x7F, 0x80, 0x00, 0x0F, 0xF7, 0x00, 0x00, 0x00, 0x7F, 0xF0, 0x00, 0x0F, 0xF7, 0x00, 0x00, 0x00, 0x7F, 0x80, 0x00, 0x0F, 0xF7, 0x00, 0x00, 0x00, 0x7F, 0xFF,
    0xFF, 0xFF, 0xF7, 0x00, 0x00, 0x00, 0x07, 0x77, 0x77, 0x77, 0x70, 0x00, 0x00, 0x00, 0xFF,

};

const unsigned char Black[] =
{
    0x42, 0x4D, 0x9E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
    0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0xF0,
    0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,

};

unsigned char player1[] =
{
    0x42, 0x4D, 0x8E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
    0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x0F, 0xFF,
    0xF0, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,

};

unsigned char player2[] =
{
    0x42, 0x4D, 0x8E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
    0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x0F, 0x00,
    0xF0, 0x00, 0x0F, 0x00, 0xF0, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,

};


unsigned char temp[] =
{
    0x42, 0x4D, 0x8E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
    0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x0F, 0x00,
    0xF0, 0x00, 0x0F, 0x00, 0xF0, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,

};

const unsigned char Yellow[] =
{
    0x42, 0x4D, 0x36, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
    0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00,
    0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00,
    0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00,
    0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00,
    0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00,
    0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00,
    0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xFF,

};










// ************************* Capture image dimensions out of BMP**********

#define PLAYER1W                ((unsigned char)player1[18])
#define PLAYER1H                ((unsigned char)player1[22])
#define PLAYER2W                ((unsigned char)player2[18])
#define PLAYER2H                ((unsigned char)player2[22])
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
unsigned int o=0,i=0,SW1,SW2 , j=0;
unsigned int y=0,d=0 ,y2=37, d2= 47, flag=0,w,z,indexx,in,a=0 ,p1,p2 ,p0 ,p ,r =0 ,c=0,k,k1,k2,k3,k4,win1=0,win2=0,jj=0,t1=1,t2=0,m1=1,m2=0,master=1,first=1;
unsigned int row=0,column=0 , z=0;
unsigned long SW=1;
unsigned int check [6][7];
// int pl1 [6][7];
//int pl2 [6][7];
int dx[]= {1,-1,-1,1,0,0,1,-1};
int dy[]= {-1,1,-1,1,1,-1,0,0};
void Screen1();
//char [] player1 ,player2;
int main(void)
{
    PortF_Init();
    TExaS_Init(SSI0_Real_Nokia5110_Scope);  // set system clock to 80 MHz
    Random_Init(1);
    Nokia5110_Init();
    UART_Init();
    Delay100ms(3);
    Nokia5110_ClearBuffer();
    Nokia5110_Clear();

    while(1)
    {
        SW1 = GPIO_PORTF_DATA_R&0x10;
        SW2 = GPIO_PORTF_DATA_R&0x01;
			
			// select mode
        if(t1)
        {
            mode();
            Nokia5110_SetCursor(3, 3);
            Nokia5110_OutString(">>");
            t1=0;
        }
        while(!SW1)
        {
            SW1 = GPIO_PORTF_DATA_R&0x10;
            if(SW1 && m1==1 && m2==0)
            {
                mode();
                Nokia5110_SetCursor(3, 5);
                Nokia5110_OutString(">>");
                m2=1;
                m1=0;
            }
            else if(SW1 && m2==1 && m1==0)
            {
                mode();
                Nokia5110_SetCursor(3, 3);
                Nokia5110_OutString(">>");
                m2=0;
                m1=1;
            }
        }
        while(!SW2)
        {
            SW2 = GPIO_PORTF_DATA_R&0x01;
            if(SW2)
            {
                t2=1;
                break;
            }
        }
        if(t2==1)break;
    }
    Nokia5110_ClearBuffer();
    Nokia5110_Clear();

		
		// mode 1
    if(m1==1 && m2==0)
    {
        SHOW();

        SW1 = GPIO_PORTF_DATA_R&0x10;
        SW2 = GPIO_PORTF_DATA_R&0x01;
        while(1)
        {
					// select shape
            SW1 = GPIO_PORTF_DATA_R&0x10;
            SW2 = GPIO_PORTF_DATA_R&0x01;
            if(!SW1)
            {
                HIDE_SHOW_X();
                break;
            }
            if(!SW2)
            {
                HIDE_SHOW_O();
                o=1;
                break;
            }

        }
				
				//swap between plater2 and player2 if you selected shape 2
        if(o)
        {
            for( i=0; i< BOARD_ROW; i++)
            {
                player2 [i] = player1[i];
            }
            for( i=0; i< BOARD_ROWS; i++)
            {
                player1 [i] = temp[i];
            }
        }

        d=PLAYER1H;
        i = 0;
        check[5][3]=2;

				//play code
        while(1)
        {
            SW1 = GPIO_PORTF_DATA_R&0x10;
            SW2 = GPIO_PORTF_DATA_R&0x01;
            Nokia5110_Clear();
            Nokia5110_ClearBuffer();
            Nokia5110_PrintBMP(y, d, player1, 0);

            printScreen();
            view ();
            //Screen1();
            Nokia5110_ClearBuffer();
            Delay100ms(1);
            if(flag)
            {
							//check if player2 win 
                win1= check_win1(c,k);        
                c=0;
                if(win1)
                {
                    Nokia5110_PrintBMP(y, d, player1, 0);
                    Nokia5110_DisplayBuffer();    // draw buffer
                    draw_win(1);
                    break;
                }
                flag=0;
								//player2 play
                generate_ply2();
                if(column==0)y2=0;
                else y2=(column*(12))+3;
                d2=(row*8)+7;
                Nokia5110_PrintBMP(y2, d2, player2, 0);
                Nokia5110_DisplayBuffer();    // draw buffer
                printScreen();
                //Screen1();
                view ();
                Delay100ms(2);
								
								//check if player2 win 
                win2= check_win2(row,column);
                if(win2)
                {
                    draw_win(0);
                    break;
                }
                row=0;
                column=0;
                imag[i].ro = y;
                imag[i].co = d;
                imag[i++].imagePtr = player1;
                imag2[a].ro = y2;
                imag2[a].co = d2;
                imag2[a++].imagePtr2 = player2;
                y=0;
                d=PLAYER1H;
            }
						
						//choose column for player1 to play
            while(!SW1)
            {
                SW1 = GPIO_PORTF_DATA_R&0x10;
                if( SW1 )
                {
                    if(y+10<=83 )
                    {
                        y+=13;
                        c++;
                    }
                    else
                    {
                        y=0;
                        c=0;
                    }
                }
                //	Delay100ms(1);
            }
						
						//player1 play
            while(!SW2)
            {
                SW2 = GPIO_PORTF_DATA_R&0x01;
                if(SW2)
                {
                    for( k=5; k>0; k--)
                    {
                        if(check[k][c]==0)
                        {
                            check[k][c]=1;
                            d=47-((5-k)*8);

                            jj++;
                            break;
                        }
                    }
                    flag=1;
                }
            }
        }
    }

		// mode 2
    else if(m2==1 && m1==0)
    {
        unsigned int valid=1,Tie=0,master_row,master_column,coun=1;
        unsigned int slave,confirm=0,second,position_Slave,row_position,respond;

        Master_Slave();     // select either master or slave
        while(1)
        {
						// played as master
            if(master==1)
            {
                //UART_OutChar(17);
                //GPIO_PORTF_DATA_R =0x02;
                //Delay100ms(2);
                //while(confirm!=200){
                // GPIO_PORTF_DATA_R =0x04;
                // Delay100ms(2);
                UART_OutChar(17);
                GPIO_PORTF_DATA_R=0x02;
                Delay100ms(2);
                confirm = UART_InChar();
                //GPIO_PORTF_DATA_R|=0x08;
                //Delay100ms(2);


                //confirm = UART_InChar();

                if(confirm == 200)
                {
                    // GPIO_PORTF_DATA_R|=0x02;
                    //Delay100ms(2);
                    First_Second();
                    confirm=0;
                    printScreen();
                    view();
                    //Screen1();
                    if(first)
                    {
                        UART_OutChar(31);  /////////////////////////
                        //	GPIO_PORTF_DATA_R =0x08;
                        //		Delay100ms(2);
                    }
                    else
                        UART_OutChar(32);
                    while(1)
                    {
                        // confirm = UART_InChar();
                        //if(confirm == 200)
                        //{
                        //GPIO_PORTF_DATA_R =0x04;   ////////////////////////////
                        //	Delay100ms(2);
                        confirm=0;
                        if(first != 1)
                        {
                            position_Slave = UART_InChar();
                            row_position=valid_Position(position_Slave);
                            if(row_position == 0)
                            {
                                UART_OutChar(24);
                                valid=0;
                            }
                            else
                            {
                                check[row_position][position_Slave]=2;
                                win2=check_win2(row_position,position_Slave);
                                if(win2==1)
                                {
                                    UART_OutChar(22);
                                    confirm = UART_InChar();
                                    if(confirm == 200)
                                    {
                                        confirm=0;
                                        draw(row_position,position_Slave,0);
                                        draw_win(0);
                                    }
                                }
                                else
                                {
                                    Tie=tie();
                                    if(Tie == 1)
                                    {
                                        UART_OutChar(23);
                                        confirm = UART_InChar();
                                        if(confirm == 200)
                                        {
                                            confirm=0;
                                            draw(row_position,position_Slave,0);
                                            draw_tie();
                                        }
                                    }
                                    else
                                    {
                                        UART_OutChar(20);
                                        confirm = UART_InChar();
                                        if(confirm == 200)
                                        {
                                            GPIO_PORTF_DATA_R|=0x04;
                                            Delay100ms(2);
                                            confirm=0	;
                                            draw(row_position,position_Slave,0);
                                        }
                                    }
                                }

                            }
                            first=1;
                        }
                        else
                        {
                            generate_mode2();
                            UART_OutChar(column);
                            row=valid_Position(column);
                            win1=check_win1(row,column);
                            if(win1==1)
                            {  
                                UART_OutChar(21);
                                confirm = UART_InChar();
                                if(confirm == 200)
                                {   check[row][column]=1;
                                    confirm=0;
                                    draw(row,column,1);
                                    draw_win(1);
                                }
                            }
                            else
                            {
                                Tie=tie();
                                if(Tie==1)
                                {
                                    UART_OutChar(23);
                                    confirm = UART_InChar();
                                    if(confirm == 200)
                                    {   check[row][column]=1;
                                        confirm=0;
                                        draw(row,column,1);
                                        draw_tie();
                                    }
                                }
                                else
                                {
                                    UART_OutChar(20);
                                    //GPIO_PORTF_DATA_R =0x02;
                                    //	GPIO_PORTF_DATA_R =0x04;
                                    //Delay100ms(2);
                                    confirm = UART_InChar();
                                    if(confirm == 200)
                                    {
                                         check[row][column]=1;
                                        //	GPIO_PORTF_DATA_R =0x02;
                                        //	GPIO_PORTF_DATA_R =0x08;
                                        //Delay100ms(2);
                                        confirm=0;
                                        draw(row,column,1);
                                        row=0;
                                        column=0;
                                    }
                                }
                            }
                            first=0;
                        }
                        //}
                    }

                }
                row=0;
                column=0;
            }/////////

						// play as slave
            else
            {
                second=100;

                slave = UART_InChar();
                //while(slave!=17){slave = UART_InChar();}
                if(slave==17)
                {
                    //GPIO_PORTF_DATA_R|=0x02;
                    //Delay100ms(2);
                    UART_OutChar(200);

                    printScreen();
                    view();
                    //Screen1();
                    while(second==100)
                    {
                        //GPIO_PORTF_DATA_R|=0x08;
                        //Delay100ms(2);

                        second = UART_InChar();
                    }
                }
                if(second ==31)
                {
                    first=1;
                    UART_OutChar(200);

                }
                else
                {
                    first =0;
                    UART_OutChar(200);
                }
                while(1)
                {
                    if(first == 0)
                    {
                        generate_mode2();
                        UART_OutChar(column);
                        respond=UART_InChar();
                        if(respond==22)
                        {   check[row][column]=1;
                            UART_OutChar(200);
                            draw(row,column,1);
                            draw_win(1);
                        }
                        else if(respond==23)
                        {   check[row][column]=1;
                            UART_OutChar(200);
                            draw(row,column,1);
                            draw_tie();
                        }
                        else if(respond==24)
                        {
                            UART_OutChar(200);
                        }
                        else
                        {   check[row][column]=1;
                            UART_OutChar(200);
                            draw(row,column,1);
                        }

                    }
                    else if(first == 1)
                    {

                        master_column = UART_InChar();
                        master_row = valid_Position(master_column);
											check[master_row][master_column]=2;
                        respond=UART_InChar();
                        if(respond==23)
                        {
                            UART_OutChar(200);
                            draw(master_row,master_column,0);
                            draw_tie();
                        }
                        else if(respond==21)
                        {
                            UART_OutChar(200);
                            draw(master_row,master_column,0);
                            draw_win(0);
                        }
                        else
                        {
                            UART_OutChar(200);
                            draw(master_row,master_column,0);
                        }
                    }
                }
                row=0;
                column=0;
            }
        }
    }


}
//choose master or slave
void Master_Slave()
{
    t1=1;
    t2=0;
    while(1)
    {
        SW1 = GPIO_PORTF_DATA_R&0x10;
        SW2 = GPIO_PORTF_DATA_R&0x01;
        if(t1)
        {
            mode1();
            Nokia5110_SetCursor(3, 3);
            Nokia5110_OutString(">>");
            t1=0;
        }
        while(!SW1)
        {
            SW1 = GPIO_PORTF_DATA_R&0x10;
            if(SW1 && master == 1)
            {
                mode1();
                Nokia5110_SetCursor(3, 5);
                Nokia5110_OutString(">>");
                master = 0;
            }
            else if(SW1 && master == 0)
            {
                mode1();
                Nokia5110_SetCursor(3, 3);
                Nokia5110_OutString(">>");
                master=1;
            }
        }
        while(!SW2)
        {
            SW2 = GPIO_PORTF_DATA_R&0x01;
            if(SW2)
            {
                t2=1;
                break;
            }
        }
        if(t2==1)break;
    }
    Nokia5110_ClearBuffer();
    Nokia5110_Clear();
    t1=1;
    t2=0;
}

// select that play first or second 
void First_Second()
{
    while(1)
    {
        SW1 = GPIO_PORTF_DATA_R&0x10;
        SW2 = GPIO_PORTF_DATA_R&0x01;
        if(t1)
        {
            mode2();
            Nokia5110_SetCursor(3, 3);
            Nokia5110_OutString(">>");
            t1=0;
        }
        while(!SW1)
        {
            SW1 = GPIO_PORTF_DATA_R&0x10;
            if(SW1 && first == 1)
            {
                mode2();
                Nokia5110_SetCursor(3, 5);
                Nokia5110_OutString(">>");
                first = 0;
            }
            else if(SW1 && first == 0)
            {
                mode2();
                Nokia5110_SetCursor(3, 3);
                Nokia5110_OutString(">>");
                first=1;
            }
        }
        while(!SW2)
        {
            SW2 = GPIO_PORTF_DATA_R&0x01;
            if(SW2)
            {
                t2=1;
                break;
            }
        }
        if(t2==1)break;
    }
    Nokia5110_ClearBuffer();
    Nokia5110_Clear();
}

// check if the position is valid or invalid
int valid_Position(int pos)
{
    int s1;
    for(s1=5; s1>0; s1--)
    {
        if(check[s1][pos] ==0)return s1;
    }
    return 0;
}

// check if the game is tie
int tie()
{
    int i1,i2;
    for(i1=1; i1<=5; i1++)
    {
        for(i2=0; i2<7; i2++)
        {
            if(check[i1][i2]==0)return 0;
        }
    }
    return 1;
}


// save all images that played 
void draw(int r,int c,int pl)
{

    if(c==0)y2=0;
    else y2=(c*15)-2;//d2=PLAYER1H-1+4;
    d2=(r*8)+7;
    if(pl==1)
    {
        imag[i].ro = y2;
        imag[i].co = d2;
        imag[i++].imagePtr = player1;
        GPIO_PORTF_DATA_R|=0x08;

    }
    else
    {
        imag[i].ro = y2;
        imag[i].co = d2;
        imag[i++].imagePtr = player2;
        GPIO_PORTF_DATA_R|=0x02;
    }
    printScreen();
    //Screen1();
    view();
}

// know who win the game
void draw_win(int wi)
{
    Delay100ms(2);
    Nokia5110_Clear();
    Nokia5110_SetCursor(1, 3);
    if(wi==1)
    {
        Nokia5110_OutString("YOU WIN!");
        win();
    }
    else
    {
        Nokia5110_OutString("YOU LOSE!");
        Lose();
    }
}

void win(void)
{
    Nokia5110_PrintBMP(18, 23, Red, 0);
    Nokia5110_DisplayBuffer();
}

void Lose(void)
{
		Nokia5110_Clear();
		Nokia5110_ClearBuffer();
    Nokia5110_PrintBMP(18, 23, lose, 0);
    Nokia5110_DisplayBuffer();
}

void draw_tie()
{
    Delay100ms(2);
    Nokia5110_Clear();
    Nokia5110_SetCursor(1, 3);

    Nokia5110_OutString("WE TIE!");
}

// show the screen of the shape to choose shape
void SHOW()
{
    Nokia5110_PrintBMP(2, 29, player1, 0);
    Nokia5110_PrintBMP(2, 45, player2, 0);
    Nokia5110_DisplayBuffer();    // draw buffer
    Nokia5110_SetCursor(1, 1);
    Nokia5110_OutString("Select Shape");
    Nokia5110_SetCursor(15, 3);
    Nokia5110_OutString(" >> SW1");
    Nokia5110_SetCursor(15, 5);
    Nokia5110_OutString(" >> SW2");
}

void HIDE_SHOW_X()
{
    Nokia5110_Clear();
    Nokia5110_ClearBuffer();
    Nokia5110_PrintBMP(2, 45, player2, 0);
    Nokia5110_DisplayBuffer();    // draw buffer
    Nokia5110_SetCursor(1, 1);
    Nokia5110_OutString("Select Shape");
    Nokia5110_SetCursor(15, 5);
    Nokia5110_OutString(" >> SW2");
    Delay100ms(1);
    Nokia5110_Clear();
    Nokia5110_ClearBuffer();
    SHOW();
    Delay100ms(1);
    Nokia5110_Clear();
    Nokia5110_ClearBuffer();
    Nokia5110_PrintBMP(2, 45, player2, 0);
    Nokia5110_DisplayBuffer();    // draw buffer
    Nokia5110_SetCursor(1, 1);
    Nokia5110_OutString("Select Shape");
    Nokia5110_SetCursor(15, 5);
    Nokia5110_OutString(" >> SW2");
    Delay100ms(1);
    Nokia5110_Clear();
    Nokia5110_ClearBuffer();
    SHOW();
    Delay100ms(1);
    Nokia5110_Clear();
    Nokia5110_ClearBuffer();
}

void HIDE_SHOW_O()
{
    Nokia5110_Clear();
    Nokia5110_ClearBuffer();
    Nokia5110_PrintBMP(2, 29, player1, 0);
    Nokia5110_DisplayBuffer();    // draw buffer
    Nokia5110_SetCursor(1, 1);
    Nokia5110_OutString("Select Shape");
    Nokia5110_SetCursor(15, 3);
    Nokia5110_OutString(" >> SW1");
    Delay100ms(1);
    Nokia5110_Clear();
    Nokia5110_ClearBuffer();
    SHOW();
    Delay100ms(1);
    Nokia5110_Clear();
    Nokia5110_ClearBuffer();
    Nokia5110_PrintBMP(2, 29, player1, 0);
    Nokia5110_DisplayBuffer();    // draw buffer
    Nokia5110_SetCursor(1, 1);
    Nokia5110_OutString("Select Shape");
    Nokia5110_SetCursor(15, 3);
    Nokia5110_OutString(" >> SW1");
    Delay100ms(1);
    Nokia5110_Clear();
    Nokia5110_ClearBuffer();
    SHOW();
    Delay100ms(1);
    Nokia5110_Clear();
    Nokia5110_ClearBuffer();
}

void PortF_Init()
{
    volatile unsigned long delay;
    SYSCTL_RCGC2_R |= 0x00000020;     // 1) F clock
    delay = SYSCTL_RCGC2_R;           // delay
    GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0
    GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
    GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog function
    GPIO_PORTF_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL
    GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 input, PF3,PF2,PF1 output
    GPIO_PORTF_AFSEL_R = 0x00;        // 6) no alternate function
    GPIO_PORTF_PUR_R = 0x11;          // enable pullup resistors on PF4,PF0
    GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital pins PF4-PF0

}



void printScreen()
{

    for(p=10; p<=63; p+=9)
    {
        Nokia5110_PrintBMP(71,p, Black, 0);
        Nokia5110_DisplayBuffer();    // draw buffer

    }
    for(j=0; j<i; j++)
    {
        Nokia5110_PrintBMP(imag[j].ro, imag[j].co , imag[j].imagePtr, 0);
    }
    for(j=0; j<a; j++)
    {
        Nokia5110_PrintBMP(imag2[j].ro, imag2[j].co , imag2[j].imagePtr2, 0);
    }
    if(m1==1)
    {
        Nokia5110_PrintBMP(39, 47, player2, 0);
    }
    Nokia5110_DisplayBuffer();    // draw buffer

    //Delay100ms(1);
}


void Screen1(void)
{
    int x;
    Nokia5110_Clear();
    Nokia5110_ClearBuffer();
    for (i=0; i<6; i++)
    {
        x=0;
        for (j=0; j<7; j++)
        {
            Nokia5110_PrintBMP(14+x, 47-z, yo, 0);
            x+=8	;
            Nokia5110_DisplayBuffer();
        }
        z+= 8;
    }
    Nokia5110_DisplayBuffer();

}

void view ()
{
    p1=6;
    p2=0;

    for(p0=0; p0<6 ; p0++)
    {
        for(p=0; p<5 ; p++)
        {

            Nokia5110_SetCursor(p1, p2);
            Nokia5110_OutString("|");
            p1+=13;
        }
        p1=6;
        p2+=1;
    }
}

int valid(int u,int v)
{
    if(0<u && u<=5 && 0<=v && v<7)return 1;
    return 0;
}
int check_win1(int col , int raw )
{
    int x=raw, y=col,q=0;
    for(k1=0; k1<8; k1++)
    {
        for(k2=0; k2<7; k2++)
        {
            x+=dx[k1];
            y+=dy[k1];
            if(valid(x,y)&& check[x][y]==1)
            {
                q++;
            }
            else break;
        }
        x=raw;
        y=col;
        if(k1==1||k1==3||k1==5||k1==7)
        {
            if(q>=3)
            {
                return 1;
            }
            q=0;
        }
    }
    return 0;
}

int check_win2(int raw , int col )
{
    int x=raw, y=col,q=0;
    for(k1=0; k1<8; k1++)
    {
        for(k2=0; k2<7; k2++)
        {
            x+=dx[k1];
            y+=dy[k1];
            if(valid(x,y)&& check[x][y]==2)
            {
                q++;
            }
            else break;
        }
        x=raw;
        y=col;
        if(k1==1||k1==3||k1==5||k1==7)
        {
            if(q>=3)
            {
                return 1;
            }
            q=0;
        }
    }
    return 0;
}


void generate_ply2()
{
    int x,y,q=0,ar[4],a1=0,a2,a3,b=1,m1=0,u=0, r1 , r2,bo1=0 ,bo2=0;
    for(k3=1; k3<=5; k3++)
    {
        for(k4=0; k4<7; k4++)
        {
            if(check[k3][k4]==2)
            {
                x=k3;
                y=k4;
                for(k1=0; k1<8; k1++)
                {
                    for(k2=0; k2<7; k2++)
                    {
                        x+=dx[k1];
                        y+=dy[k1];
                        if(valid(x,y)&& check[x][y]==2)
                        {
                            q++;
                        }
                        else
                        {
                            if(valid(x,y) && check[x][y]==0)
                            {
                                ar[a1++]=x;
                                ar[a1++]=y;
                            }
                            break;
                        }
                    }
                    x=k3;
                    y=k4;
                    if(k1==1||k1==3||k1==5||k1==7)
                    {
                        for(a3=0; a3<a1-1; a3+=2)
                        {
                            for(a2=5; a2>=ar[a3]; a2--)
                            {
                                if(check[a2][ar[a3+1]]==0 && a2 == ar[a3] )
                                {
                                    ar[0]=a2;
                                    ar[1]=ar[a3+1];
                                    bo1=1;
																	m1=1;
                                    break;
                                }
                                else if(check[a2][ar[a3+1]]==0 &&(a2-ar[a3]) % 2==0 )
                                {
                                    u=1;
                                    r1=a2;
                                    r2=ar[a3+1];
                                    ar[0]=a2;
                                    ar[1]=ar[a3+1];
                                    break;
                                }
                                else if (check[a2][ar[a3+1]]==0 &&u==0)
                                {
                                    ar[0]=a2;
                                    ar[1]=ar[a3+1];
                                    break;
                                }
                                //else if (u==1){ar[0]=r1;ar[1]=r2;}
                            }
                            if(m1==1)break;
                        }
                        m1=0;
                        u=0;
                        if(q==2 && a1!=0)
                        {
                           if(bo2==0||bo1==1){
                           
                            row=ar[0];
                            column=ar[1];}
													  if(bo1==1){ 
                             check[ar[0]][ar[1]]=2;															
													return ;}
														
                             
                        }
                        else if(q==1 && a1!=0)
                        {
                            row=ar[0];
                            column=ar[1];
                            b=0;bo2=1;
                        }
                        else if(q==0 && a1!=0 && b==1)
                        {   bo2=1;
                            row=ar[0];
                            column=ar[1];
                        }
                        q=0;
                        a1=0;

                    }
                }
            }
						////
						
					/*	else if(check[k3][k4]==0){q=0;a1=0;
						    x=k3;
                y=k4;
                for(k1=0; k1<8; k1++)
                {
                    for(k2=0; k2<7; k2++)
                    {
                        x+=dx[k1];
                        y+=dy[k1];
                        if(valid(x,y)&& check[x][y]==2)
                        {
                            q++;
                        }
                        else
                        {
                            break;
                        }
                    }
                    x=k3;
                    y=k4;
                    if(k1==1||k1==3||k1==5||k1==7)
                    {
                        //for(a3=0; a3<a1-1; a3+=2)
                        //{
                            for(a2=5; a2>=k3; a2--)
                            {
                                if(check[a2][k4]==0 && a2 == k3 )
                                {
                                    ar[0]=a2;
                                    ar[1]=k4;
                                    break;
                                }
                                else if(check[a2][k4]==0 &&(a2-k3) % 2==0 )
                                {
                                    u=1;
                                    r1=a2;
                                    r2=k4;
                                    ar[0]=a2;
                                    ar[1]=k4;
                                    break;
                                }
                                else if (check[a2][k4]==0 &&u==0)
                                {
                                    ar[0]=a2;
                                    ar[1]=k4;
                                    break;
                                }
                                //else if (u==1){ar[0]=r1;ar[1]=r2;}
                            }
                            
                        u=0;
                        if(q==3 && a1!=0)
                        {
                            //pl2[k3][k4]=1;
                            check[k3][k4]=2;
                            row=k3;
                            column=k4;
                            return ;
                        }
                        q=0;

                    }
                }
            }*/
						}
						
						
          //////
        }
    
    a1=0;
    q=0;
    m1=0;
    u=0;
    for(k3=1; k3<=5; k3++)
    {
        for(k4=0; k4<7; k4++)
        {
            if(check[k3][k4]==1)
            {
                x=k3;
                y=k4;
                for(k1=0; k1<8; k1++)
                {
                    for(k2=0; k2<7; k2++)
                    {
                        x+=dx[k1];
                        y+=dy[k1];
                        if(valid(x,y)&& check[x][y]==1)
                        {
                            q++;
                        }
                        else
                        {
                            if(valid(x,y) && check[x][y]==0)
                            {
                                ar[a1++]=x;
                                ar[a1++]=y;
                            }
                            break;
                        }
                    }
                    x=k3;
                    y=k4;
                    if(k1==1||k1==3||k1==5||k1==7)
                    {
                        for(a3=0; a3<a1-1; a3+=2)
                        {
                            for(a2=5; a2>=ar[a3]; a2--)
                            {
                                if(check[a2][ar[a3+1]]==0 && a2 == ar[a3] )
                                {
                                    ar[0]=a2;
                                    ar[1]=ar[a3+1];
                                    m1=1;
                                    break;
                                }
                                else if(check[a2][ar[a3+1]]==0 &&(a2-ar[a3]) % 2==0 )
                                {
                                    u=1;
                                    ar[0]=a2;
                                    ar[1]=ar[a3+1];
                                    break;
                                }
                                else if (check[a2][ar[a3+1]]==0 &&u==0)
                                {
                                    ar[0]=a2;
                                    ar[1]=ar[a3+1];
                                    break;
                                }
                            }
                            if(m1==1)break;
                        }
                        m1=0;u=0;
                        if(q==2 && a1!=0)
                        {
                           
                            check[ar[0]][ar[1]]=2;
                            row=ar[0];
                            column=ar[1];
                            return ;
                        }
                        else if(row == 0  && a1!=0)
                        {
                            row=ar[0];
                            column=ar[1];
                        }
                        q=0;
                        a1=0;
                    }


                }

            }
						//
						/*
						
						
						else if(check[k3][k4]==0){q=0;a1=0;m1=0;
						    x=k3;
                y=k4;
                for(k1=0; k1<8; k1++)
                {
                    for(k2=0; k2<7; k2++)
                    {
                        x+=dx[k1];
                        y+=dy[k1];
                        if(valid(x,y)&& check[x][y]==1)
                        {
                            q++;
                        }
                        else
                        {
                            break;
                        }
                    }
                    x=k3;
                    y=k4;
                    if(k1==1||k1==3||k1==5||k1==7)
                    {
                        //for(a3=0; a3<a1-1; a3+=2)
                        //{
                            for(a2=5; a2>=k3; a2--)
                            {
                                if(check[a2][k4]==0 && a2 == k3 )
                                {
                                    ar[0]=a2;
                                    ar[1]=k4;m1=1;
                                    break;
                                }
                                else if(check[a2][k4]==0 &&(a2-k3) % 2==0 )
                                {
                                    u=1;
                                    r1=a2;
                                    r2=k4;
                                    ar[0]=a2;
                                    ar[1]=k4;
                                    break;
                                }
                                else if (check[a2][k4]==0 &&u==0)
                                {
                                    ar[0]=a2;
                                    ar[1]=k4;
                                    break;
                                }
                                //else if (u==1){ar[0]=r1;ar[1]=r2;}
                            }
                            
                        u=0;
                        if(q==3 && a1!=0&&m1==1)
                        {
                            //pl2[k3][k4]=1;
                            check[k3][k4]=2;
                            row=k3;
                            column=k4;
                            return ;
                        }
                        q=0;

                    }
                }
            }
						
						
						
						*/
						//
        }
    }
  
    check[row][column]=2;
}

void generate_mode2()
{
int x,y,q=0,ar[4],a1=0,a2,a3,b=1,m1=0,u=0, r1 , r2,bo1=0 ,bo2=0;
    for(k3=1; k3<=5; k3++)
    {
        for(k4=0; k4<7; k4++)
        {
            if(check[k3][k4]==1)
            {
                x=k3;
                y=k4;
                for(k1=0; k1<8; k1++)
                {
                    for(k2=0; k2<7; k2++)
                    {
                        x+=dx[k1];
                        y+=dy[k1];
                        if(valid(x,y)&& check[x][y]==1)
                        {
                            q++;
                        }
                        else
                        {
                            if(valid(x,y) && check[x][y]==0)
                            {
                                ar[a1++]=x;
                                ar[a1++]=y;
                            }
                            break;
                        }
                    }
                    x=k3;
                    y=k4;
                    if(k1==1||k1==3||k1==5||k1==7)
                    {
                        for(a3=0; a3<a1-1; a3+=2)
                        {
                            for(a2=5; a2>=ar[a3]; a2--)
                            {
                                if(check[a2][ar[a3+1]]==0 && a2 == ar[a3] )
                                {
                                    ar[0]=a2;
                                    ar[1]=ar[a3+1];
                                    bo1=1;
																	m1=1;
                                    break;
                                }
                                else if(check[a2][ar[a3+1]]==0 &&(a2-ar[a3]) % 2==0 )
                                {
                                    u=1;
                                    r1=a2;
                                    r2=ar[a3+1];
                                    ar[0]=a2;
                                    ar[1]=ar[a3+1];
                                    break;
                                }
                                else if (check[a2][ar[a3+1]]==0 &&u==0)
                                {
                                    ar[0]=a2;
                                    ar[1]=ar[a3+1];
                                    break;
                                }
                                //else if (u==1){ar[0]=r1;ar[1]=r2;}
                            }
                            if(m1==1)break;
                        }
                        m1=0;
                        u=0;
                        if(q==2 && a1!=0)
                        {
                           if(bo2==0||bo1==1){
                           
                            row=ar[0];
                            column=ar[1];}
													  if(bo1==1){ 
                             check[ar[0]][ar[1]]=1;															
													return ;}
														
                             
                        }
                        else if(q==1 && a1!=0)
                        {
                            row=ar[0];
                            column=ar[1];
                            b=0;bo2=1;
                        }
                        else if(q==0 && a1!=0 && b==1)
                        {   bo2=1;
                            row=ar[0];
                            column=ar[1];
                        }
                        q=0;
                        a1=0;

                    }
                }
            }
						////
						
					/*	else if(check[k3][k4]==0){q=0;a1=0;
						    x=k3;
                y=k4;
                for(k1=0; k1<8; k1++)
                {
                    for(k2=0; k2<7; k2++)
                    {
                        x+=dx[k1];
                        y+=dy[k1];
                        if(valid(x,y)&& check[x][y]==2)
                        {
                            q++;
                        }
                        else
                        {
                            break;
                        }
                    }
                    x=k3;
                    y=k4;
                    if(k1==1||k1==3||k1==5||k1==7)
                    {
                        //for(a3=0; a3<a1-1; a3+=2)
                        //{
                            for(a2=5; a2>=k3; a2--)
                            {
                                if(check[a2][k4]==0 && a2 == k3 )
                                {
                                    ar[0]=a2;
                                    ar[1]=k4;
                                    break;
                                }
                                else if(check[a2][k4]==0 &&(a2-k3) % 2==0 )
                                {
                                    u=1;
                                    r1=a2;
                                    r2=k4;
                                    ar[0]=a2;
                                    ar[1]=k4;
                                    break;
                                }
                                else if (check[a2][k4]==0 &&u==0)
                                {
                                    ar[0]=a2;
                                    ar[1]=k4;
                                    break;
                                }
                                //else if (u==1){ar[0]=r1;ar[1]=r2;}
                            }
                            
                        u=0;
                        if(q==3 && a1!=0)
                        {
                            //pl2[k3][k4]=1;
                            check[k3][k4]=2;
                            row=k3;
                            column=k4;
                            return ;
                        }
                        q=0;

                    }
                }
            }*/
						}
						
						
          //////
        }
    
    a1=0;
    q=0;
    m1=0;
    u=0;
    for(k3=1; k3<=5; k3++)
    {
        for(k4=0; k4<7; k4++)
        {
            if(check[k3][k4]==2)
            {
                x=k3;
                y=k4;
                for(k1=0; k1<8; k1++)
                {
                    for(k2=0; k2<7; k2++)
                    {
                        x+=dx[k1];
                        y+=dy[k1];
                        if(valid(x,y)&& check[x][y]==2)
                        {
                            q++;
                        }
                        else
                        {
                            if(valid(x,y) && check[x][y]==0)
                            {
                                ar[a1++]=x;
                                ar[a1++]=y;
                            }
                            break;
                        }
                    }
                    x=k3;
                    y=k4;
                    if(k1==1||k1==3||k1==5||k1==7)
                    {
                        for(a3=0; a3<a1-1; a3+=2)
                        {
                            for(a2=5; a2>=ar[a3]; a2--)
                            {
                                if(check[a2][ar[a3+1]]==0 && a2 == ar[a3] )
                                {
                                    ar[0]=a2;
                                    ar[1]=ar[a3+1];
                                    m1=1;
                                    break;
                                }
                                else if(check[a2][ar[a3+1]]==0 &&(a2-ar[a3]) % 2==0 )
                                {
                                    u=1;
                                    ar[0]=a2;
                                    ar[1]=ar[a3+1];
                                    break;
                                }
                                else if (check[a2][ar[a3+1]]==0 &&u==0)
                                {
                                    ar[0]=a2;
                                    ar[1]=ar[a3+1];
                                    break;
                                }
                            }
                            if(m1==1)break;
                        }
                        m1=0;u=0;
                        if(q==2 && a1!=0)
                        {
                           
                            check[ar[0]][ar[1]]=1;
                            row=ar[0];
                            column=ar[1];
                            return ;
                        }
                        else if(row == 0  && a1!=0)
                        {
                            row=ar[0];
                            column=ar[1];
                        }
                        q=0;
                        a1=0;
                    }


                }

            }
						//
						/*
						
						
						else if(check[k3][k4]==0){q=0;a1=0;m1=0;
						    x=k3;
                y=k4;
                for(k1=0; k1<8; k1++)
                {
                    for(k2=0; k2<7; k2++)
                    {
                        x+=dx[k1];
                        y+=dy[k1];
                        if(valid(x,y)&& check[x][y]==1)
                        {
                            q++;
                        }
                        else
                        {
                            break;
                        }
                    }
                    x=k3;
                    y=k4;
                    if(k1==1||k1==3||k1==5||k1==7)
                    {
                        //for(a3=0; a3<a1-1; a3+=2)
                        //{
                            for(a2=5; a2>=k3; a2--)
                            {
                                if(check[a2][k4]==0 && a2 == k3 )
                                {
                                    ar[0]=a2;
                                    ar[1]=k4;m1=1;
                                    break;
                                }
                                else if(check[a2][k4]==0 &&(a2-k3) % 2==0 )
                                {
                                    u=1;
                                    r1=a2;
                                    r2=k4;
                                    ar[0]=a2;
                                    ar[1]=k4;
                                    break;
                                }
                                else if (check[a2][k4]==0 &&u==0)
                                {
                                    ar[0]=a2;
                                    ar[1]=k4;
                                    break;
                                }
                                //else if (u==1){ar[0]=r1;ar[1]=r2;}
                            }
                            
                        u=0;
                        if(q==3 && a1!=0&&m1==1)
                        {
                            //pl2[k3][k4]=1;
                            check[k3][k4]=2;
                            row=k3;
                            column=k4;
                            return ;
                        }
                        q=0;

                    }
                }
            }
						
						
						
						*/
						//
        }
    }
  
    check[row][column]=1;
    }
  

void mode()
{
    Delay100ms(1);
    Nokia5110_Clear();
    Nokia5110_ClearBuffer();
    Nokia5110_SetCursor(1, 1);
    Nokia5110_OutString("Select mode");

    Nokia5110_SetCursor(20, 3);
    Nokia5110_OutString("P1 VS AI");

    Nokia5110_SetCursor(20, 5);
    Nokia5110_OutString("P1 VS P2");

}

void mode1()
{
    Delay100ms(1);
    Nokia5110_Clear();
    Nokia5110_ClearBuffer();
    Nokia5110_SetCursor(1, 1);
    Nokia5110_OutString("Hand shake");

    Nokia5110_SetCursor(20, 3);
    Nokia5110_OutString("Master");

    Nokia5110_SetCursor(20, 5);
    Nokia5110_OutString("Slave");

}

void mode2()
{
    Delay100ms(1);
    Nokia5110_Clear();
    Nokia5110_ClearBuffer();
    Nokia5110_SetCursor(1, 1);
    Nokia5110_OutString("Select Turn");

    Nokia5110_SetCursor(20, 3);
    Nokia5110_OutString("First");

    Nokia5110_SetCursor(20, 5);
    Nokia5110_OutString("Second");

}

void Delay100ms(unsigned long count)
{
    unsigned long volatile time;
    while(count>0)
    {
        time = 727240;  // 0.1sec at 80 MHz
        while(time)
        {
            time--;
        }
        count--;
    }
}
