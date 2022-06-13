#include <Adafruit_NeoPixel.h>

//#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 14
#define WIDTH 9
#define COLLISION_TYPE_BOARD 1
#define COLLISION_TYPE_BLOCK 2
#define COLLISION_TYPE_NA 0

int tetris[HEIGHT][WIDTH] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 1, 1, 1},
    {1, 1, 0, 0, 0, 1, 1, 1, 1},
    {1, 1, 1, 0, 0, 1, 1, 1, 1},
    {1, 1, 1, 0, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1}
};

int blocks[7][16][4] = {
    // # 1 1
    // #   1
    // #   1
    {
        {0, 0, 0, 0},
        {0, 0, 0, 1},
        {0, 1, 1, 1},
        {0, 0, 0, 0},

        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},

        {0, 0, 0, 0},
        {0, 1, 1, 1},
        {0, 1, 0, 0},
        {0, 0, 0, 0},

        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
    },
    // # 1
    // # 1 1 1
    {
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 1, 1},
        {0, 0, 0, 0},
        
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        
        {0, 1, 1, 1},
        {0, 0, 0, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        
        {0, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
    },
    // # 1 1
    // # 1 1
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0},
        {0, 0, 1, 1},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
        
        {0, 0, 0, 0},
        {0, 0, 1, 1},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {0, 1, 1, 1},
        {0, 0, 0, 0},
        
        {0, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
        
        {0, 0, 0, 0},
        {0, 1, 1, 1},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
        
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 1},
        {0, 0, 0, 0},
        
        {0, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
        
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 1},
        {0, 0, 0, 0},
        
        {0, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
    }
};

int x = 2;
int y = 0;
int rotate = 0;
int shape = 3;
int score = 0;

void printTetris() {
  
  // 13
  Adafruit_NeoPixel stripa0 = Adafruit_NeoPixel(10, A0, NEO_GRB + NEO_KHZ800);
  // 1
  Adafruit_NeoPixel stripa1 = Adafruit_NeoPixel(10, A1, NEO_GRB + NEO_KHZ800);
  // 0
  Adafruit_NeoPixel stripa2 = Adafruit_NeoPixel(10, A2, NEO_GRB + NEO_KHZ800);
	for(int i = 0; i < 13; i ++) {
      Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, i, NEO_GRB + NEO_KHZ800);
      for(int t = 0; t < 10; t ++) {
        strip.setPixelColor(t, 0, 0, 0);
		stripa0.setPixelColor(t, 0, 0, 0);
        stripa1.setPixelColor(t, 0, 0, 0);
        stripa2.setPixelColor(t, 0, 0, 0);
      }
	  strip.show();
    }
  
  
    for(int _y = 0; _y < HEIGHT; _y ++) {
      Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, HEIGHT - 1 - _y, NEO_GRB + NEO_KHZ800);
        for(int _x = 0; _x < WIDTH; _x ++) {
            if (_x >= x && _y >= y && _x < x + 4 && _y < y + 4 && blocks[shape][_y - y + rotate * 4][_x - x] != 0) {
              Serial.print("#");
              
              if (1 <= _y && _y <= 11) {
                strip.setPixelColor(_x, 255, 0, 0);
              } else if (_y == 0) {
                stripa0.setPixelColor(_x, 255, 0, 0);
              } else if (_y == 12) {
                stripa1.setPixelColor(_x, 255, 0, 0);
              } else if (_y == 13) { 
                stripa2.setPixelColor(_x, 255, 0, 0);
              }
             
              
            } else if(tetris[_y][_x] != 0) {
              Serial.print("@");
              
              if (1 <= _y && _y <= 11) {
                strip.setPixelColor(_x, 0, 255, 0);
              } else if (_y == 0) {
                stripa0.setPixelColor(_x, 0, 255, 0);
              } else if (_y == 12) {
                stripa1.setPixelColor(_x, 0, 255, 0);
              } else if (_y == 13) { 
                stripa2.setPixelColor(_x, 0, 255, 0);
              }
              
            } else if (tetris[_y][_x] == 0) {
              Serial.print("O");
            }
        }
      Serial.println();
	  strip.show();
    }
  Serial.print("score : ");
  Serial.println(score);
  stripa0.show();
  stripa1.show();
  stripa2.show();
  delay(1000);
}

int isOutOfBoard(int x, int y, int shape, int rotate) {
    for(int _y = 0; _y < 4; _y ++) {
        for(int _x = 0; _x < 4; _x ++) {
            if (blocks[shape][_y + 4 * rotate][_x] != 0 && (x + _x < 0 || x + _x >= WIDTH || y + _y < 0 || y + _y >= HEIGHT)) {
                return COLLISION_TYPE_BOARD;
            }
        }
    }
    return COLLISION_TYPE_NA;
}

int isCollisionWithBlocks(int x, int y, int shape, int rotate) {
    for(int _y = 0; _y < 4; _y ++) {
        for (int _x = 0; _x < 4; _x ++) {
            if (blocks[shape][_y + 4 * rotate][_x] != 0 && (y + _y >= 0 && y + _y < HEIGHT && x + _x >= 0 && x + _x < WIDTH) && tetris[y + _y][x + _x] != 0) {
                return COLLISION_TYPE_BLOCK;
            }
        }
    }
    return COLLISION_TYPE_NA;
}

void mergeBlock() {
    for(int _y = 0; _y < 4; _y ++) {
        for(int _x = 0; _x < 4; _x ++) {
            if (blocks[shape][_y + rotate * 4][_x] != 0 && !(_x + x < 0 || _x + x >= WIDTH || _y + y < 0 || _y + y >= HEIGHT)) {
                tetris[y + _y][x + _x] = blocks[shape][_y + rotate * 4][_x];
            }
        }
    }
}

int randomRange(int min, int max) {
    int range = max - min;
    return rand() % range + min;
}

void randomNewBlock() {
    x = 2;
    y = 0;
    rotate = 0;
    shape = randomRange(0, 7);
    printf("shape: %d\n", shape);
}

void removeLine(int _y) {
    for(int _x = 0; _x < WIDTH; _x ++) {
        tetris[_y][_x] = 0;
    }
}

void shiftLine(int _y) {
    for (int __y = _y; __y > 0; __y --) {
        for (int _x = 0; _x < WIDTH; _x ++) {
            tetris[__y][_x] = tetris[__y - 1][_x];
        }
    }
}

void addScore(int increaseScore = 0) {
    score += increaseScore;
}

void removeLineChecker() {
    bool removeAvaliable = true;
    for(int _y = 0; _y < HEIGHT; _y ++) {
        removeAvaliable = true;
        for(int _x = 0; _x < WIDTH; _x ++) {
            if (tetris[_y][_x] == 0) {
                removeAvaliable = false;
                break;
            }
        }
        if (removeAvaliable) {
            addScore(1000);
		    printTetris();
          
            removeLine(_y);
            shiftLine(_y);
        }
    }
}

void down(bool shoot = false) {
    while (isOutOfBoard(x, y + 1, shape, rotate) == COLLISION_TYPE_NA && isCollisionWithBlocks(x, y + 1, shape, rotate) == COLLISION_TYPE_NA) {
        y += 1;
        addScore(10);
        if (!shoot) {
            break;
        }
    }

    if (isCollisionWithBlocks(x, y + 1, shape, rotate) == COLLISION_TYPE_BLOCK || isOutOfBoard(x, y + 1, shape, rotate) == COLLISION_TYPE_BOARD) {
        mergeBlock();
        removeLineChecker();
        randomNewBlock();
    }
}

void left() {
    if (isCollisionWithBlocks(x - 1, y, shape, rotate) == COLLISION_TYPE_NA && isOutOfBoard(x - 1, y, shape, rotate) == COLLISION_TYPE_NA) {
        x -= 1;
    }
}

void right() {
    if (isCollisionWithBlocks(x + 1, y, shape, rotate) == COLLISION_TYPE_NA && isOutOfBoard(x + 1, y, shape, rotate) == COLLISION_TYPE_NA) {
        x += 1;
    }
}

void rotateBlock() {
    if (isCollisionWithBlocks(x, y, shape, (rotate + 1) % 4) == COLLISION_TYPE_NA && isOutOfBoard(x, y, shape, (rotate + 1) % 4) == COLLISION_TYPE_NA) {
        rotate = (rotate + 1) % 4;
    }
}

void ledTest() {
  Adafruit_NeoPixel stripa0 = Adafruit_NeoPixel(10, A0, NEO_GRB + NEO_KHZ800);
  Adafruit_NeoPixel stripa1 = Adafruit_NeoPixel(10, A1, NEO_GRB + NEO_KHZ800);
  Adafruit_NeoPixel stripa2 = Adafruit_NeoPixel(10, A2, NEO_GRB + NEO_KHZ800);
	for(int i = 0; i < 13; i ++) {
      Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, i, NEO_GRB + NEO_KHZ800);
      for(int t = 0; t < 10; t ++) {
        strip.setPixelColor(t, 255, 20 * t, 0);
		stripa0.setPixelColor(t, 255, 20 * t, 0);
        stripa1.setPixelColor(t, 255, 20 * t, 0);
        stripa2.setPixelColor(t, 255, 20 * t, 0);
      }
	  strip.show();
    }
  stripa0.show();
  stripa1.show();
  stripa2.show();
}

// C++ code
//
void setup()
{
  Serial.begin(9600);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  
  ledTest();
  
    printTetris();
  Serial.print("collision check ");
  Serial.println(isOutOfBoard(5, 11, 3, 0));
  Serial.print("collision check");
  Serial.print(isCollisionWithBlocks(2, 8, 3, 0));
  Serial.print(" ");
  Serial.println(isCollisionWithBlocks(2, 7, 3, 0));

    x = 2;
    y = 0;
    rotate = 0;
    shape = 5;
    score = 0;
    rotateBlock();
    printTetris();
    /*down();
    printTetris();

     for(int i = 0; i < 9; i ++) {
         down();
    printTetris();
     }
    //down(true);
    printTetris();*/
}

void loop()
{
    down();
    printTetris();
  
  if(digitalRead(A3)) {
    left();
    printTetris();
  }
  
  if (digitalRead(A4)) {
    rotateBlock();
    printTetris();
  }
  
  if (digitalRead(A5)) {
    right();
    printTetris();
  }
}