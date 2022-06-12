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
    for(int _y = 0; _y < HEIGHT; _y ++) {
        for(int _x = 0; _x < WIDTH; _x ++) {
            if (_x >= x && _y >= y && _x < x + 4 && _y < y + 4 && blocks[shape][_y - y + rotate * 4][_x - x] != 0) {
              Serial.print("#");
            } else if(tetris[_y][_x] != 0) {
              Serial.print("@");
            } else if (tetris[_y][_x] == 0) {
              Serial.print("O");
            }
        }
      Serial.println();
    }
  Serial.print("score : ");
  Serial.println(score);
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

// C++ code
//
void setup()
{
  Serial.begin(9600);

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
    printTetris();
    rotateBlock();
    printTetris();
    down();
    printTetris();

    // for(int i = 0; i < 9; i ++) {
    //     down();
    // }
    down(true);
    printTetris();
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
}