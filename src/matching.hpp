#ifndef MATCHING_H_
#define MATCHING_H_

// ============================↓↓↓編集可能↓↓↓========================== //

Point matching(unsigned char input[CHANNEL][INPUT_SIZE_H][INPUT_SIZE_W], unsigned char temp[CHANNEL][TMP_SIZE_H][TMP_SIZE_W]);
Point get_Min(double arr[INPUT_SIZE_H-TMP_SIZE_H+1][INPUT_SIZE_W-TMP_SIZE_W+1],int h,int w);

// ============================↑↑↑編集可能↑↑↑========================== //

#endif