#include"integration.hpp"
#include"staff_struct.hpp"
#include"matching.hpp"

// ============================↓↓↓編集可能↓↓↓========================== //
#include"luts.hpp"

Point matching(unsigned char input[CHANNEL][INPUT_SIZE_H][INPUT_SIZE_W], unsigned char temp[CHANNEL][TMP_SIZE_H][TMP_SIZE_W]){

    // 変数の宣言
    int i, j, I, J, k;                                                  // カウンター
    double loss[INPUT_SIZE_H-TMP_SIZE_H+1][INPUT_SIZE_W-TMP_SIZE_W+1];  // 誤差保存用
    Point out_point;                                                    // 検出位置

    // 初期化
    out_point.x = out_point.y = 0;

    // 全画素全探索のテンプレートマッチング SAD
    for( j = 0; j < ( INPUT_SIZE_H - TMP_SIZE_H + 1 ); j++ ){

        for( i = 0; i < ( INPUT_SIZE_W - TMP_SIZE_W + 1 ); i++ ){

            // lossの初期化
            loss[j][i] = 0.0;

            // ラスタスキャン
            for( k = 0; k < CHANNEL; k++ ){

                for( J = 0; J < TMP_SIZE_H ; J++ ){

                    for( I = 0; I < TMP_SIZE_W ; I++ ){

                        loss[j][i] += sqrt( ( input[k][J+j][I+i] - temp[k][J][I] ) * ( input[k][J+j][I+i] - temp[k][J][I] ) );
                    }
                }
            }
        }
    }

    // 相違度の最小値を求める
    out_point = get_Min(loss, (INPUT_SIZE_H-TMP_SIZE_H+1), (INPUT_SIZE_W-TMP_SIZE_W+1));

    return out_point;
}

Point get_Min(double arr[INPUT_SIZE_H-TMP_SIZE_H+1][INPUT_SIZE_W-TMP_SIZE_W+1],int h,int w){

    // 変数の宣言
    int i,j;                    // カウンター
    Point min;                  // 相違度マップの最小値を保存
    double loss;                // 相違度保存用の変数

    // 初期化
    min.x = 0; min.y = 0; loss = arr[0][0];

    // ラスタスキャン
    for(j=0;j<h;j++){

        for(i=0;i<w;i++){

            if(loss > arr[j][i]){

                // 最小値の更新
                loss = arr[j][i]; min.x = i; min.y = j;
            }
        }
    }

    return min;
}
// ============================↑↑↑編集可能↑↑↑========================== //