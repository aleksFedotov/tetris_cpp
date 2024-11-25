#include "block.h"
#include "position.h"

class LBLock: public Block {
    public: 
        LBLock() {
            id = 1;
            cells[0] = {Position(0,2), Position(1,0), Position(1,1), Position(1,2)};
            cells[1] = {Position(0,1), Position(1,1), Position(2,1), Position(2,2)};
            cells[2] = {Position(1,0), Position(1,1), Position(1,2), Position(2,0)};
            cells[3] = {Position(0,0), Position(0,1), Position(1,1), Position(2,1)};
        }
};
class JBLock: public Block {
    public: 
        JBLock() {
            id = 2;
            cells[0] = {Position(0,0), Position(1,0), Position(1,1), Position(1,2)};
            cells[1] = {Position(0,1), Position(1,2), Position(1,1), Position(2,1)};
            cells[2] = {Position(1,0), Position(1,1), Position(1,2), Position(2,2)};
            cells[3] = {Position(0,1), Position(1,1), Position(2,0), Position(2,1)};
        }
};
class IBLock: public Block {
    public: 
        IBLock() {
            id = 3;
            cells[0] = {Position(1,0), Position(1,1), Position(1,2), Position(1,3)};
            cells[1] = {Position(0,2), Position(1,2), Position(2,2), Position(3,2)};
            cells[2] = {Position(2,0), Position(2,1), Position(2,2), Position(2,3)};
            cells[3] = {Position(0,1), Position(1,1), Position(2,1), Position(3,1)};
        }
};
class OBLock: public Block {
    public: 
        OBLock() {
            id = 4;
            cells[0] = {Position(0,0), Position(0,1), Position(1,0), Position(1,1)};
            cells[1] = {Position(0,0), Position(0,1), Position(1,0), Position(1,1)};
            cells[2] = {Position(0,0), Position(0,1), Position(1,0), Position(1,1)};
            cells[3] = {Position(0,0), Position(0,1), Position(1,0), Position(1,1)};
         
        }
};
class SBLock: public Block {
    public: 
        SBLock() {
            id = 5;
            cells[0] = {Position(0,1), Position(0,2), Position(1,0), Position(1,1)};
            cells[1] = {Position(0,1), Position(1,1), Position(1,2), Position(2,2)};
            cells[2] = {Position(1,1), Position(1,2), Position(2,0), Position(2,1)};
            cells[3] = {Position(0,0), Position(0,0), Position(1,1), Position(2,1)};
         
        }
};
class TBLock: public Block {
    public: 
        TBLock() {
            id = 6;
            cells[0] = {Position(0,1), Position(1,0), Position(1,1), Position(1,2)};
            cells[1] = {Position(0,1), Position(1,1), Position(1,2), Position(2,1)};
            cells[2] = {Position(1,0), Position(1,1), Position(1,2), Position(2,1)};
            cells[3] = {Position(0,1), Position(1,0), Position(1,1), Position(2,1)};
         
        }
};
class ZBLock: public Block {
    public: 
        ZBLock() {
            id = 7;
            cells[0] = {Position(0, 0), Position(0, 1), Position(1, 1), Position(1, 2)};
            cells[1] = {Position(0, 2), Position(1, 1), Position(1, 2), Position(2, 1)};
            cells[2] = {Position(1, 0), Position(1, 1), Position(2, 1), Position(2, 2)};
            cells[3] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 0)};
         
        }
};