#define STB_IMAGE_IMPLEMENTATION
# include "iGraphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <math.h>
#include <windows.h>

int maze[21][19] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1 },
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
        {1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1 },
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1 },
        {1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        {1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1 },
        {0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 },
        {1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1 },
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
        {1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1 },
        {0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 },
        {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1 },
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
        {1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1 },
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        {1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};


int dot[21][19] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        {1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1 },
        {1, 0, 0, 0, 0, 1, 0, 3, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
        {1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1 },
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1 },
        {1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        {1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1 },
        {1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1 },
        {1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1 },
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 3, 0, 0, 0, 2, 0 },
        {1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1 },
        {1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1 },
        {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1 },
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
        {1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1 },
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        {1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
        {1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }

};


int new_dot[21][19] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        {1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1 },
        {1, 0, 0, 0, 0, 1, 0, 3, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
        {1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1 },
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1 },
        {1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        {1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1 },
        {1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1 },
        {1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1 },
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 3, 0, 0, 0, 2, 0 },
        {1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1 },
        {1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1 },
        {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1 },
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
        {1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1 },
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        {1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
        {1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }

};

int dIndx = 1;
int t  = 0;
int score = 0;
char CmpHscore[55];
char s[20] = "Point: 00";
char watch[10];


int moveGhost = 30;


char temName[30] = "";



struct {
    int mode = 0;
    int rgb[3] = {233, 34, 60};
    int ready = 0;
    int button = 1;
    char btimg[50] = "assets/images/Pause.bmp";
    int winMode = 0;
    int lostMode = 0;
    int len = 0;
    char WLstr[100];
    int point = 25;
    int second = 0;
    int minute = 0;
    int freezParameter = 130;
    int freeze = 0;
} Game;




struct {
   int x = 5;
   int y = 10;
   int check = 2; // 1 for right, 2 for left , 3 for up, 4 for down
   int imgIndx = 2;
   int moveSmile = 5;

   char up[4][50] = { "assets/images/pd_full.bmp",
                      "assets/images/pd0.bmp",
                      "assets/images/pd1.bmp",
                      "assets/images/pd2.bmp",
                      };

    char down[4][50] ={ "assets/images/pd_full.bmp",
                      "assets/images/dpd0.bmp",
                      "assets/images/dpd1.bmp",
                      "assets/images/dpd2.bmp",
                      };

    char left[4][50] = { "assets/images/pd_full.bmp",
                      "assets/images/lpd0.bmp",
                      "assets/images/lpd1.bmp",
                      "assets/images/lpd2.bmp",
                      };

    char right[4][50] = { "assets/images/pd_full.bmp",
                      "assets/images/rpd0.bmp",
                      "assets/images/rpd1.bmp",
                      "assets/images/rpd2.bmp",
                      };
    char currentImage[50] = "assets/images/lpd1.bmp";

    int life[3] = {1, 1, 1};
    int lifecount = 3;

} Smile;


struct {
    int x;
    int y;
    int prev;
    char img[50];

} Pink, Blue, Green, Red;

typedef struct{
    char name[30];
    char score[7];
} Highscore;

Highscore hs[10];

void outHighscore()
{
    // Initialize with default values
    for(int i = 0; i < 10; i++)
    {
        strcpy(hs[i].name, "No Name");
        strcpy(hs[i].score, "0");
    }

    FILE *s = NULL;
    FILE *n = NULL;

    n = fopen("assets/data/Names.txt", "r");
    if (n != NULL) {
        for(int i = 0; i < 10; i++)
        {
            if(fgets(hs[i].name, 30, n) == NULL) {
                break;
            }
            hs[i].name[strcspn(hs[i].name, "\r\n")] = 0;
            // If name is empty, revert to default
            if (strlen(hs[i].name) == 0) {
                strcpy(hs[i].name, "No Name");
            }
        }
        fclose(n);
    }

    s = fopen("assets/data/Scores.txt", "r");
    if (s != NULL) {
        for(int i = 0; i < 10; i++)
        {
            if(fgets(hs[i].score, 7, s) == NULL) {
                break;
            }
            hs[i].score[strcspn(hs[i].score, "\r\n")] = 0;
            // If score is empty, revert to default
            if (strlen(hs[i].score) == 0) {
                strcpy(hs[i].score, "0");
            }
        }
        fclose(s);
    }
}

void inHighscore()
{
    FILE *s = fopen("assets/data/Scores.txt", "w");
    if (s) {
        for(int i = 0; i < 10; i++)
        {
            fprintf(s, "%s\n", hs[i].score);
        }
        fclose(s);
    }

    FILE *n = fopen("assets/data/Names.txt", "w");
    if (n) {
        for(int i = 0; i < 10; i++)
        {
            fprintf(n, "%s\n", hs[i].name);
        }
        fclose(n);
    }
}

void Sort_Highscore()
{
    char tempScore[7];
    char tempName[30];

    for(int i = 0; i < 9; i++) {
        for(int j = i + 1; j < 10; j++) {
            if(atoi(hs[i].score) < atoi(hs[j].score)) {
                strcpy(tempName, hs[i].name);
                strcpy(tempScore, hs[i].score);

                strcpy(hs[i].name, hs[j].name);
                strcpy(hs[i].score, hs[j].score);

                strcpy(hs[j].name, tempName);
                strcpy(hs[j].score, tempScore);
            }
        }
    }
}




void newGame();
void loadGame();
void saveGame();

int checkWin() {
    for(int i = 0; i< 21; i++) {
        for(int j = 0; j < 19; j++) {
            if(dot[i][j] == 0) return 0;
        }
    }

    return 1;
}



void iDraw()
{

    iClear();

    if(Game.mode == 0) { // Start Page
            iShowBMP(10, 10, (char*)"assets/images/Start.bmp");

            iText(600, 100, (char*)"Press ", GLUT_BITMAP_TIMES_ROMAN_24);
            iSetColor(Game.rgb[0], Game.rgb[1], Game.rgb[2]);
            iText(675, 100, (char*)"SPACE", GLUT_BITMAP_TIMES_ROMAN_24);
            iSetColor(255, 255, 255);
            iText(780, 100, (char*)" to start", GLUT_BITMAP_TIMES_ROMAN_24);

    } else if(Game.mode == 1) { //Menu page

            iShowBMP(0, 0, (char*)"assets/images/Menu.bmp");

            iSetColor(100, 100, 100);

            iFilledRectangle(1175, 585, 250, 50);
            iFilledRectangle(1175, 535, 250, 50);
            iFilledRectangle(1175, 485, 250, 50);
            iFilledRectangle(1175, 435, 250, 50);
            iFilledRectangle(1175, 385, 250, 50);
            iFilledRectangle(1175, 335, 250, 50);
            iFilledRectangle(1175, 285, 250, 50);

            iSetColor(175, 175, 175);

            iFilledRectangle(1180, 590, 240, 40);
            iFilledRectangle(1180, 540, 240, 40);
            iFilledRectangle(1180, 490, 240, 40);
            iFilledRectangle(1180, 440, 240, 40);
            iFilledRectangle(1180, 390, 240, 40);
            iFilledRectangle(1180, 340, 240, 40);
            iFilledRectangle(1180, 290, 240, 40);


            iSetColor(0, 0, 0);

            iText(1200, 600, (char*)"Continue", GLUT_BITMAP_TIMES_ROMAN_24);
            iText(1200, 550, (char*)"New Game", GLUT_BITMAP_TIMES_ROMAN_24);
            iText(1200, 500, (char*)"Save Game", GLUT_BITMAP_TIMES_ROMAN_24);
            iText(1200, 450, (char*)"Load Game", GLUT_BITMAP_TIMES_ROMAN_24);
            iText(1200, 400, (char*)"High Score", GLUT_BITMAP_TIMES_ROMAN_24);
            iText(1200, 350, (char*)"Help", GLUT_BITMAP_TIMES_ROMAN_24);
            iText(1200, 300, (char*)"Exit", GLUT_BITMAP_TIMES_ROMAN_24);

            iSetColor(255, 255, 255);


    } else if(Game.mode == 2 || Game.mode == 3 || Game.mode == 4) { //Continue Game + New Game + Load Game
            if(checkWin()) {
                iPauseTimer(0);

                iShowBMP(0, 0, (char*)"assets/images/Win.bmp");
                iSetColor(0,180, 0);
                sprintf(s, "Your Score : %d", score);

                iText(100, 480, s, GLUT_BITMAP_TIMES_ROMAN_24);

                iSetColor(50, 50, 50);

                iText(100, 350, (char*)"Enter your name here: ", GLUT_BITMAP_TIMES_ROMAN_24);
                iRectangle(100, 280, 400, 50);

                if(Game.winMode == 1) {
                    iText(130, 300, Game.WLstr, GLUT_BITMAP_TIMES_ROMAN_24);
                }


            } else if(Smile.lifecount != 0) {
            if(Game.button == 1) iResumeTimer(0);

            //DRAWING THE MAZE

            //Maze

            iSetColor(150, 150, 150);
            for(int i = 0; i < 21; i++) {
                for(int j = 0; j < 19; j++) {
                if(maze[i][j] == 1)
                    iFilledRectangle(25*j + 150, 25*i + 100, 25, 25);
                }
            }

            //Dot

            iSetColor(90, 90, 250);

            for(int i = 0; i < 21; i++) {
                for(int j = 0; j < 19; j++) {
                    if(dot[i][j] == 0) {
                        iFilledCircle(25*j + 150 + 13.5, 25*i + 100 + 13.5, 2);
                    } else if(dot[i][j] == 2) {
                        iShowBMP2(25*j + 145 , 25 * i + 95, (char*)"assets/images/cherry.bmp", 0);
                    } else if(dot[i][j] == 3) {
                        iShowBMP2(25*j + 145 , 25 * i + 95, (char*)"assets/images/candy.bmp", 0);
                    }
                }
            }

            //Smile

            iShowBMP2(25*Smile.y + 145, 25*Smile.x + 95, Smile.currentImage, 0);

            //Life

            for(int i = 0; i < 3; i++) {
                if(Smile.life[i] == 1) {
                    iShowBMP2(10 + i* 30, 10, (char*)"assets/images/lpd0.bmp" ,0);
                }
            }

            //Ghost

            if(Game.freeze) {
                strcpy(Pink.img, "assets/images/ghost_freeze.bmp");
                strcpy(Green.img, "assets/images/ghost_freeze.bmp");
                strcpy(Red.img, "assets/images/ghost_freeze.bmp");
                strcpy(Blue.img, "assets/images/ghost_freeze.bmp");
            } else {
                strcpy(Pink.img, "assets/images/ghost_pink.bmp");
                strcpy(Green.img, "assets/images/ghost_green.bmp");
                strcpy(Red.img, "assets/images/ghost_red.bmp");
                strcpy(Blue.img, "assets/images/ghost_blue.bmp");

            }

            iShowBMP2(25*Pink.y + 145, 25*Pink.x + 93, Pink.img, 0);
            iShowBMP2(25*Blue.y + 145, 25*Blue.x + 93, Blue.img, 0);
            iShowBMP2(25*Green.y + 145, 25*Green.x + 93, Green.img, 0);
            iShowBMP2(25*Red.y + 145, 25*Red.x + 93, Red.img, 0);


            iSetColor(255, 255, 255);
            iText(150, 642, s, GLUT_BITMAP_TIMES_ROMAN_24);
            sprintf(CmpHscore ,"High Score: %s", hs[0].score);
            iText(290, 642, CmpHscore, GLUT_BITMAP_TIMES_ROMAN_24);

            iShowBMP2(575, 630, Game.btimg, 0 );




            if(Game.ready <= 60) {
                iSetColor(255, 255, 255);
                iText(370, 430, (char*)"Ready!", GLUT_BITMAP_TIMES_ROMAN_24);
            }

            iRectangle(850, 590, 100, 50);
            iText(860, 610, (char*)"MENU", GLUT_BITMAP_TIMES_ROMAN_24);

            iText(860, 500, (char*)"Time :", GLUT_BITMAP_TIMES_ROMAN_24);

            sprintf(watch, "%d : %d", Game.minute, Game.second);
            iText(950, 500, watch, GLUT_BITMAP_TIMES_ROMAN_24);



        } else if(Smile.lifecount == 0) {
            iPauseTimer(0); //Game Over
            iShowBMP(0, 0, (char*)"assets/images/Game Over.bmp");
            sprintf(s, "Your Score : %d", score);

            iSetColor(205, 0, 0);

            iText(320, 425, s, GLUT_BITMAP_TIMES_ROMAN_24);

           iSetColor(250, 250, 250);

            iText(980, 530, (char*)"Enter your name here: ", GLUT_BITMAP_TIMES_ROMAN_24);

            iRectangle(980, 450, 400, 50);

            if(Game.lostMode == 1) {
                    iText(990, 465, Game.WLstr, GLUT_BITMAP_TIMES_ROMAN_24);
            }


        }

    } else if(Game.mode == 5) { //High Score

        //outHighscore();

        char tempShow[100] = "";
        iShowBMP(0, 0, (char*)"assets/images/highScore.bmp");


        int sX = 70, sY = 600;

        iSetColor(255, 255, 255);

        iText(50, 650, (char*)"SL.    Name ------> Score", GLUT_BITMAP_TIMES_ROMAN_24 );

        for(int i = 0; i < 10; i++) {

            char x[50] = "";
            strcpy(x, hs[i].name);
            if(x[strlen(x) - 1] == '\n') x[strlen(x) - 1] = ' ';
            strcat(x, "-----> ");
            strcat(x, hs[i].score);
             if(x[strlen(x) - 1] == '\n') x[strlen(x)-1] = ' ';

            sprintf(tempShow, "%d. %s", i+1, x);

            iText(sX, sY, tempShow);

            sY -= 50;
        }



    } else if(Game.mode == 6) { //Help
        iShowBMP(0, 0, (char*)"assets/images/Help.bmp");
    } else if(Game.mode == 7) {
        iShowBMP(0, 0, (char*)"assets/images/Help2.bmp");
    }

}





void iMouseMove(int mx, int my)
{
    //printf("x = %d, y= %d\n",mx,my);   7
    //place your codes here
}


void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(Game.mode == 2 || Game.mode == 3 || Game.mode == 4) {
            if(checkWin()) {
                if(mx < 500 && mx > 100 && my < 330 && my > 280) {
                    Game.winMode = 1;
                }
            } else if(Smile.lifecount == 0) {
                if(mx > 945 && mx < 1327 && my > 454 && my < 504) {
                    Game.lostMode = 1;
                }

            } else {
                 if((mx > 565 && mx < 643) && (my > 645 && my < 680)) {
                    if(Game.button == 1) {
                        strcpy(Game.btimg, "assets/images/Resume.bmp");
                        Game.button = 0;
                        iPauseTimer(0);
                    } else {
                        strcpy(Game.btimg, "assets/images/Pause.bmp");
                        Game.button = 1;
                        iResumeTimer(0);
                    }
                }

                if(mx > 850 && mx < 950 && my > 590 && my < 640) {
                        iPauseTimer(0);
                        Game.mode = 1;
                }

            }

        }

        if(Game.mode == 1) {
             if((mx > 1138 && mx < 1367) && (my > 588 &&  my < 628)) {
                Game.mode = 2; // Continue
                Game.ready = 0;
                //iResumeTimer(0);
            } else if((mx > 1138 && mx < 1367) && (my > 538 &&  my < 578)) {
                    Game.mode = 3; // New Game
                    Game.ready = 0;
                    newGame();
                    iResumeTimer(0);
            } else if((mx > 1138 && mx < 1367) && (my > 488 &&  my < 528)) {
                    iPauseTimer(0);
                    saveGame(); // Save Game

            } else if((mx > 1138 && mx < 1367) && (my > 438 &&  my < 478)) {
                    Game.mode = 4; // Load Game
                    Game.ready = 0;
                    loadGame();
                    iResumeTimer(0);
            } else if((mx > 1138 && mx < 1367) && (my > 388 &&  my < 428)) {
                    iPauseTimer(0);
                    Game.mode = 5; //High Score

            } else if((mx > 1138 && mx < 1367) && (my > 338 &&  my < 378)) {
                    iPauseTimer(0);
                    Game.mode = 6; // Help
            } else if((mx > 1138 && mx < 1367) && (my > 288 &&  my < 328)) {
                    exit(0);
            }

        }



        if(Game.mode == 5) {
            if(mx > 706 && mx < 920 && my > 90 && my < 160) {
                Game.mode = 1;
            }
        }

        if(Game.mode == 6) { //Help Menu first page

            if(mx > 50 && mx < 282 && my > 61 && my < 132) {
                Game.mode = 1;
            }

            if(mx > 650 && mx < 915 && my > 60 && my < 140) {
                Game.mode = 7;
            }
        }

        else if(Game.mode == 7) { //Help Menu Second Page
             if(mx > 50 && mx < 282 && my > 61 && my < 132) {
                Game.mode = 1;
            }

            if(mx > 650 && mx < 915 && my > 60 && my < 140) {
                Game.mode = 6;
            }

        }

        printf("%d %d\n", mx, my);

    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {


    }
}


void iKeyboard(unsigned char key)
{
    if (Game.mode == 0 && key == ' ')
    {
        Game.mode = 1;
    }
    if(Game.mode == 2 || Game.mode == 3 || Game.mode == 4) {
        if(checkWin()) {
            if(Game.winMode) {
                 if(key == '\r')
                {
                    Game.winMode = 0;

                    if(score > atoi(hs[9].score)) {
                         strcpy(hs[9].name, Game.WLstr); //Saving the name
                        char t[10] = "";
                        sprintf(t, "%d", score);
                        strcpy(hs[9].score, t);//Saving the score
                        Sort_Highscore(); //Sorting  them
                        inHighscore(); //keeping them in file
                    }

                    //strcpy(Game.WLstr,"");
                    for (int i = 0; i < Game.len; i++)
                                Game.WLstr[i] = 0;
                    Game.len = 0;
                    Game.mode = 1;
                }
                else
                {
                    Game.mode = 2;
                    Game.WLstr[Game.len] = key;
                    Game.len++;
                }
            }
        } else if(Smile.lifecount == 0) {
                  if(Game.lostMode) {
                     if(key == '\r')
                    {
                        Game.lostMode = 0;

                        if(score > atoi(hs[9].score)) {
                            strcpy(hs[9].name, Game.WLstr); //Saving the name
                            char t[10] = "";
                            sprintf(t, "%d", score);
                            strcpy(hs[9].score, t);//Saving the score
                            Sort_Highscore(); //Sorting  them
                            inHighscore(); //keeping them in file
                        }

                        //strcpy(Game.WLstr,"");
                        for (int i = 0; i < Game.len; i++)
                                    Game.WLstr[i] = 0;
                        Game.len = 0;
                        Game.mode = 1;
                    }
                    else
                    {
                        Game.mode = 2;
                        Game.WLstr[Game.len] = key;
                        Game.len++;
                    }
                }

        }
    }

}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(int key)
{

    if(key == GLUT_KEY_END)
    {
        exit(0);
    } else if(key == GLUT_KEY_UP)
    {
        if(maze[Smile.x + 1][Smile.y ] == 0) {
            Smile.check = 3;
            Smile.imgIndx = 2;
        }

    } else if(key == GLUT_KEY_DOWN)
    {
        if(maze[Smile.x - 1][Smile.y] == 0) {
            Smile.check = 4;
            Smile.imgIndx = 2;
        }

    } else if(key == GLUT_KEY_RIGHT)
    {
         if(maze[Smile.x][Smile.y+1] == 0){
            Smile.check = 1;
            Smile.imgIndx = 2;
         }

    } else if(key == GLUT_KEY_LEFT)
    {
        if(maze[Smile.x][Smile.y - 1] == 0) {
            Smile.check = 2;
            Smile.imgIndx = 2;
        }

    }

}

double distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1 - x2 , 2) + pow(y1 - y2, 2));
}

void Red_move()
{
    double rd[5] = {-1, -1, -1, -1, -1};

    if(maze[Red.x][Red.y + 1] == 0) {
        rd[1] = distance(Red.x, Red.y + 1, Smile.x, Smile.y);
    }

    if(maze[Red.x][Red.y - 1] == 0) {
        rd[2] = distance(Red.x, Red.y - 1, Smile.x, Smile.y);
    }

    if(maze[Red.x + 1][Red.y] == 0) {
        rd[3] = distance(Red.x + 1, Red.y, Smile.x, Smile.y);
    }

    if(maze[Red.x - 1][Red.y] == 0) {
        rd[4] = distance(Red.x - 1, Red.y, Smile.x, Smile.y);
    }

    rd[Red.prev] = -1;

    int shortest_indx = Red.prev, min = 3000;

    for(int i = 1; i < 5; i++) {

        if(rd[i] >= 0)
            if(rd[i] < min) {
                min  = rd[i];
                shortest_indx = i;
            }
    }


    if(shortest_indx == 1) {
        Red.y++;
        Red.prev = 2;
    }
    else if(shortest_indx == 2) {
        Red.y--;
        Red.prev = 1;
    }
    else if(shortest_indx == 3) {
        Red.x++;
        Red.prev = 4;
    }
    else if(shortest_indx == 4) {
        Red.x--;
        Red.prev = 3;
    }

    if(Red.y == -1) Red.y = 18;
    if(Red.y == 19) Red.y = 0;
}

void Green_move()
{
    double gd[5] = {-1, -1, -1, -1, -1};

    if(maze[Green.x][Green.y + 1] == 0) {
        gd[1] = distance(Green.x, Green.y + 1, Smile.x + 3, Smile.y);
    }

    if(maze[Green.x][Green.y - 1] == 0) {
        gd[2] = distance(Green.x, Green.y - 1, Smile.x + 3, Smile.y);
    }

    if(maze[Green.x + 1][Green.y] == 0) {
        gd[3] = distance(Green.x + 1, Green.y, Smile.x + 3, Smile.y);
    }

    if(maze[Green.x - 1][Green.y] == 0) {
        gd[4] = distance(Green.x - 1, Green.y, Smile.x + 3, Smile.y);
    }

    gd[Green.prev] = -1;

    int shortest_indx = Green.prev, min = 3000;

    for(int i = 1; i < 5; i++) {

        if(gd[i] >= 0)
            if(gd[i] < min) {
                min  = gd[i];
                shortest_indx = i;
            }
    }


    if(shortest_indx == 1) {
        Green.y++;
        Green.prev = 2;
    }
    else if(shortest_indx == 2) {
        Green.y--;
        Green.prev = 1;
    }
    else if(shortest_indx == 3) {
        Green.x++;
        Green.prev = 4;
    }
    else if(shortest_indx == 4) {
        Green.x--;
        Green.prev = 3;
    }

    if(Green.y == -1) Green.y = 18;
    if(Green.y == 19) Green.y = 0;
}

void Blue_move()
{
    double bd[5] = {-1, -1, -1, -1, -1};

    if(maze[Blue.x][Blue.y + 1] == 0) {
        bd[1] = distance(Blue.x, Blue.y + 1, Smile.x + 7, Smile.y - 5);
    }

    if(maze[Blue.x][Blue.y - 1] == 0) {
        bd[2] = distance(Blue.x, Blue.y - 1, Smile.x + 7, Smile.y - 5);
    }

    if(maze[Blue.x + 1][Blue.y] == 0) {
        bd[3] = distance(Blue.x + 1, Blue.y, Smile.x + 7, Smile.y - 5);
    }

    if(maze[Blue.x - 1][Blue.y] == 0) {
        bd[4] = distance(Blue.x - 1, Blue.y, Smile.x + 7, Smile.y - 5);
    }

    bd[Blue.prev] = -1;

    int shortest_indx = Blue.prev, min = 3000;

    for(int i = 1; i < 5; i++) {

        if(bd[i] >= 0)
            if(bd[i] < min) {
                min  = bd[i];
                shortest_indx = i;
            }
    }


    if(shortest_indx == 1) {
        Blue.y++;
        Blue.prev = 2;
    }
    else if(shortest_indx == 2) {
        Blue.y--;
        Blue.prev = 1;
    }
    else if(shortest_indx == 3) {
        Blue.x++;
        Blue.prev = 4;
    }
    else if(shortest_indx == 4) {
        Blue.x--;
        Blue.prev = 3;
    }

    if(Blue.y == -1) Blue.y = 18;
    if(Blue.y == 19) Blue.y = 0;
}

void Pink_move()
{
    double pd[5] = {-1, -1, -1, -1, -1};

    if(maze[Pink.x][Pink.y + 1] == 0) {
        pd[1] = distance(Pink.x, Pink.y + 1, Smile.x + (Smile.x - Red.x), Smile.y + (Smile.y - Red.y));
    }

    if(maze[Pink.x][Pink.y - 1] == 0) {
        pd[2] = distance(Pink.x, Pink.y - 1, Smile.x + (Smile.x - Red.x), Smile.y + (Smile.y - Red.y));
    }

    if(maze[Pink.x + 1][Pink.y] == 0) {
        pd[3] = distance(Pink.x + 1, Pink.y, Smile.x + (Smile.x - Red.x), Smile.y + (Smile.y - Red.y));
    }

    if(maze[Pink.x - 1][Pink.y] == 0) {
        pd[4] = distance(Pink.x - 1, Pink.y, Smile.x + (Smile.x - Red.x), Smile.y + (Smile.y - Red.y));
    }

    pd[Pink.prev] = -1;

    int shortest_indx = Pink.prev , min = 3000;

    for(int i = 1; i < 5; i++) {

        if(pd[i] >= 0)
            if(pd[i] < min) {
                min  = pd[i];
                shortest_indx = i;
            }
    }


    if(shortest_indx == 1) {
        Pink.y++;
        Pink.prev = 2;
    }
    else if(shortest_indx == 2) {
        Pink.y--;
        Pink.prev = 1;
    }
    else if(shortest_indx == 3) {
        Pink.x++;
        Pink.prev = 4;
    }
    else if(shortest_indx == 4) {
        Pink.x--;
        Pink.prev = 3;
    }

    if(Pink.y == -1) Pink.y = 18;
    if(Pink.y == 19) Pink.y = 0;
}


void change()
{
    if(Game.mode == 0) {
        Game.rgb[0] = (Game.rgb[0] + 20) % 256;
        Game.rgb[1] = (Game.rgb[1] + 5) % 256;
        Game.rgb[2] = (Game.rgb[2] + 75) % 256;
    }
    if(Game.mode == 2 || Game.mode == 3 || Game.mode == 4) {

            if(Game.ready <= 60) {
                Game.ready++;
            } else {

                    if(Smile.moveSmile == 5) {
                    if(Smile.check == 1) {
                        strcpy(Smile.currentImage,Smile.right[Smile.imgIndx]);
                    if(Smile.y == 18) {
                        Smile.y = 0;
                    }
                    if(maze[Smile.x][Smile.y+1] == 0) {
                            Smile.y++;
                            Smile.imgIndx += dIndx;

                    }
                } else if(Smile.check == 2) {
                    strcpy(Smile.currentImage,Smile.left[Smile.imgIndx]);
                    if(Smile.y == 0) {
                        Smile.y = 18;
                    }
                    if(maze[Smile.x][Smile.y - 1] == 0) {
                            Smile.y--;
                            Smile.imgIndx += dIndx;
                    }

                } else if(Smile.check == 3) {
                    strcpy(Smile.currentImage,Smile.up[Smile.imgIndx]);
                    if(maze[Smile.x + 1][Smile.y ] == 0) {
                            Smile.x++;
                            Smile.imgIndx += dIndx;
                    }
                } else if(Smile.check == 4) {
                    strcpy(Smile.currentImage,Smile.down[Smile.imgIndx]);
                    if(maze[Smile.x - 1][Smile.y] == 0) {
                            Smile.x--;
                            Smile.imgIndx += dIndx;
                    }
                }

                if(Smile.imgIndx < 0 ) {
                    dIndx = 1;
                    Smile.imgIndx = 0;
                }

                if(Smile.imgIndx > 3) {
                    dIndx = -1;
                    Smile.imgIndx = 3;
                }

                if(dot[Smile.x][Smile.y] == 0) {
                    score += Game.point;
                    dot[Smile.x][Smile.y] = 1;
                    sprintf(s, "Point : %d", score);
                } else if(dot[Smile.x][Smile.y] == 2) {
                    score += 300;
                    dot[Smile.x][Smile.y] = 1;
                    sprintf(s, "Point : %d", score);
                }  else if(dot[Smile.x][Smile.y] == 3) {
                    score += 100;
                    dot[Smile.x][Smile.y] = 1;
                    Game.freezParameter = 0;
                    Game.freeze = 1;
                    sprintf(s, "Point : %d", score);
                }
            }

            Smile.moveSmile = (Smile.moveSmile + 1) % 6;

            t++;
            Game.freezParameter++;

            if(Game.freezParameter > 120) Game.freeze = 0;


            if(t % moveGhost == 0 && Game.freeze == 0) {
                 Red_move();
                 Green_move();
                 Blue_move();
                 Pink_move();
            }

            if(t % 100 == 0 && moveGhost > 15) {
                moveGhost--;
            }

            if(t % 200 == 0 && Game.point > 5) {
                Game.point -= 2; //in every five seconds points will get lessen by two points for every dots.
            }

            if(t % 40 == 0) Game.second++;

            if(Game.second == 60) {
                Game.minute++;
                Game.second = 0;
            }

            double distanceRed = distance(Smile.x, Smile.y, Red.x, Red.y);
            double distanceGreen = distance(Smile.x, Smile.y, Green.x, Green.y);
            double distanceBlue = distance(Smile.x, Smile.y, Blue.x, Blue.y);
            double distancePink = distance(Smile.x, Smile.y, Pink.x, Pink.y);

            if(Game.freeze != 1) {
                  if(distanceBlue == 0 || distanceGreen == 0 || distancePink == 0 || distanceRed == 0) {
                    Smile.life[Smile.lifecount - 1] = 0;
                    Smile.lifecount--;

                    //  iPauseTimer(0);

                    Smile.x = 5;
                    Smile.y = 10;
                    Pink.prev = 2;

                    Blue.x = 11;
                    Blue.y = 10;
                    Blue.prev = 1;

                    Red.x = 13;
                    Red.y = 7;
                    Red.prev = 1;

                    Green.x = 12;
                    Green.y = 9;
                    Green.prev = 4;
                    Pink.x = 11;
                    Pink.y = 8;


                }
            }

        }


    }


}

void ghostinitialize()
{
    Pink.x = 11;
    Pink.y = 8;
    Pink.prev = 2;
    strcpy(Pink.img ,"assets/images/ghost_pink.bmp");

    Blue.x = 11;
    Blue.y = 10;
    Blue.prev = 1;
    strcpy(Blue.img, "assets/images/ghost_blue.bmp");

    Red.x = 13;
    Red.y = 7;
    Red.prev = 1;
    strcpy(Red.img, "assets/images/ghost_red.bmp");

    Green.x = 12;
    Green.y = 9;
    Green.prev = 4;
    strcpy(Green.img, "assets/images/ghost_green.bmp");
}


void newGame() {
    for(int i = 0 ; i < 21; i++) {
        for(int j = 0; j < 19; j++) {
            dot[i][j] = new_dot[i][j];
        }
    }


    Smile.x = 5;
    Smile.y = 10;
    Smile.check = 2;
    Smile.imgIndx = 2;


    ghostinitialize();

    Smile.lifecount = 3;
    Smile.life[0] = 1;
    Smile.life[1] = 1;
    Smile.life[2] = 1;

    score = 0;
    t = 0;
    moveGhost = 23;
    Game.point = 25;
    Game.second = 0;
    Game.minute = 0;

    Game.freezParameter = 130;
    Game.freeze = 0;

}


void loadGame() {
    FILE *dt = NULL;
    FILE *ot = NULL;

    dt = fopen("assets/data/PrevDot.txt", "r");
    ot = fopen("assets/data/Others.txt", "r");

    if (dt == NULL || ot == NULL) {
        // Handle file opening error, maybe show a message to the user
        return;
    }

    for(int i = 0; i < 21; i++) {
        for(int j = 0; j < 19; j++) {
            if (fscanf(dt, "%d", &dot[i][j]) != 1) {
                // Handle read error or end of file
                fclose(dt);
                fclose(ot);
                return;
            }
        }
    }

    if (fscanf(ot, "%d", &Smile.x) != 1) { fclose(dt); fclose(ot); return; }
    if (fscanf(ot, "%d", &Smile.y) != 1) { fclose(dt); fclose(ot); return; }
    if (fscanf(ot, "%d", &Smile.check) != 1) { fclose(dt); fclose(ot); return; }
    if (fscanf(ot, "%d", &Smile.imgIndx) != 1) { fclose(dt); fclose(ot); return; }

    if (fscanf(ot, "%d", &Pink.x) != 1) { fclose(dt); fclose(ot); return; }
    if (fscanf(ot, "%d", &Pink.y) != 1) { fclose(dt); fclose(ot); return; }
    if (fscanf(ot, "%d", &Pink.prev) != 1) { fclose(dt); fclose(ot); return; }

    if (fscanf(ot, "%d", &Blue.x) != 1) { fclose(dt); fclose(ot); return; }
    if (fscanf(ot, "%d", &Blue.y) != 1) { fclose(dt); fclose(ot); return; }
    if (fscanf(ot, "%d", &Blue.prev) != 1) { fclose(dt); fclose(ot); return; }

    if (fscanf(ot, "%d", &Red.x) != 1) { fclose(dt); fclose(ot); return; }
    if (fscanf(ot, "%d", &Red.y) != 1) { fclose(dt); fclose(ot); return; }
    if (fscanf(ot, "%d", &Red.prev) != 1) { fclose(dt); fclose(ot); return; }

    if (fscanf(ot, "%d", &Green.x) != 1) { fclose(dt); fclose(ot); return; }
    if (fscanf(ot, "%d", &Green.y) != 1) { fclose(dt); fclose(ot); return; }
    if (fscanf(ot, "%d", &Green.prev) != 1) { fclose(dt); fclose(ot); return; }

    if (fscanf(ot, "%d", &Smile.lifecount) != 1) { fclose(dt); fclose(ot); return; }
    if (fscanf(ot, "%d", &Smile.life[0]) != 1) { fclose(dt); fclose(ot); return; }
    if (fscanf(ot, "%d", &Smile.life[1]) != 1) { fclose(dt); fclose(ot); return; }
    if (fscanf(ot, "%d", &Smile.life[2]) != 1) { fclose(dt); fclose(ot); return; }

    if (fscanf(ot, "%d", &score) != 1) { fclose(dt); fclose(ot); return; }
    if (fscanf(ot, "%d", &t) != 1) { fclose(dt); fclose(ot); return; }
    if (fscanf(ot, "%d", &moveGhost) != 1) { fclose(dt); fclose(ot); return; }

    if (fscanf(ot, "%d", &Game.point) != 1) { fclose(dt); fclose(ot); return; }
    if (fscanf(ot, "%d", &Game.second) != 1) { fclose(dt); fclose(ot); return; }
    if (fscanf(ot, "%d", &Game.minute) != 1) { fclose(dt); fclose(ot); return; }

    if (fscanf(ot, "%d", &Game.freezParameter) != 1) { fclose(dt); fclose(ot); return; }
    if (fscanf(ot, "%d", &Game.freeze) != 1) { fclose(dt); fclose(ot); return; }

    sprintf(s, "Point : %d", score);

    fclose(dt);
    fclose(ot);

}

void saveGame()
{

    FILE *dt = NULL;
    FILE *ot = NULL;

    dt = fopen("assets/data/PrevDot.txt", "w");
    ot = fopen("assets/data/Others.txt", "w");

    for(int i = 0; i < 21; i++) {
        for(int j = 0; j < 19; j++) {
            fprintf(dt, "%d\n", dot[i][j]);
        }
    }

    fprintf(ot, "%d\n", Smile.x);
    fprintf(ot, "%d\n", Smile.y);
    fprintf(ot, "%d\n", Smile.check);
    fprintf(ot, "%d\n", Smile.imgIndx);

    fprintf(ot, "%d\n", Pink.x);
    fprintf(ot, "%d\n", Pink.y);
    fprintf(ot, "%d\n", Pink.prev);

    fprintf(ot, "%d\n", Blue.x);
    fprintf(ot, "%d\n", Blue.y);
    fprintf(ot, "%d\n", Blue.prev);

    fprintf(ot, "%d\n", Red.x);
    fprintf(ot, "%d\n", Red.y);
    fprintf(ot, "%d\n", Red.prev);

    fprintf(ot, "%d\n", Green.x);
    fprintf(ot, "%d\n", Green.y);
    fprintf(ot, "%d\n", Green.prev);

    fprintf(ot, "%d\n", Smile.lifecount);
    fprintf(ot, "%d\n", Smile.life[0]);
    fprintf(ot, "%d\n", Smile.life[1]);
    fprintf(ot, "%d\n", Smile.life[2]);

    fprintf(ot, "%d\n", score);
    fprintf(ot, "%d\n", t);
    fprintf(ot, "%d\n", moveGhost);

    fprintf(ot, "%d\n", Game.point);
    fprintf(ot, "%d\n", Game.second);
    fprintf(ot, "%d\n", Game.minute);

    fprintf(ot, "%d\n", Game.freezParameter);
    fprintf(ot, "%d\n", Game.freeze);

    fclose(dt);
    fclose(ot);


}


int main()
{

    ghostinitialize();
    outHighscore();

    iSetTimer(25, change);

    PlaySound("assets/sounds/bg.wav", NULL, SND_LOOP | SND_ASYNC);

    iInitialize(1600, 800, "Pacman!");



    return 0;
}