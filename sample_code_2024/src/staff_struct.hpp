#ifndef STAFFSTRUCT_H_
#define STAFFSTRUCT_H_

// ハイパーパラメータ /////////////////////////////////////////////////////////
#define INPUT_SIZE_H 480  //480という値は編集しないでください
#define INPUT_SIZE_W 640  //640という値は編集しないでください
#define TMP_SIZE_H 159 //ここの値はdataによって修正してください
#define TMP_SIZE_W 212 //ここの値はdataによって修正してください
#define CHANNEL 3      //CHANNELは編集しないでください
#define TOTAL_N 5
//////////////////////////////////////////////////////////////////////////////////////



// x,y座標を保存する構造体
typedef struct Point{
    int x;
    int y;
}Point;

#endif