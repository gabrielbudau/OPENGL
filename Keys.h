#ifndef KEYS_H
#define KEYS_H
void keyOperations(void);
void keySpecialOperations(void);
void keyPressed(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void keySpecial(int key, int x, int y);
void keySpecialUp(int key, int x, int y);
#endif