#include"integration.hpp"
#include"staff_struct.hpp"
#include"matching.hpp"

// ============================↓↓↓編集可能↓↓↓========================== //
#include"luts.hpp"


cv::Mat entergrayskale(unsigned char input[CHANNEL][INPUT_SIZE_H][INPUT_SIZE_W]){
    uint i, j, k, num1;
    cv::Mat enter_gray(INPUT_SIZE_H, INPUT_SIZE_W, CV_8UC1);
    for(j = 0; j < INPUT_SIZE_H; j++){
        for(i = 0; i < INPUT_SIZE_W; i++){
            num1 = 0;
            for(k = 0; k < 3; k++){
                num1 += input[k][j][i];
            }
            enter_gray.at<uchar>(j, i) = num1 / 3;
                
        }
    }
    return enter_gray;
}

cv::Mat tempgrayskale(unsigned char temp[CHANNEL][TMP_SIZE_H][TMP_SIZE_W]){
    int i, j, k, num2;
    cv::Mat temp_gray(TMP_SIZE_H, TMP_SIZE_W, CV_8UC1);
    for(j = 0; j < TMP_SIZE_H; j++){
        for(i = 0; i < TMP_SIZE_W; i++){
            num2 = 0;
            for(k = 0; k < 3; k++){
                num2 += temp[k][j][i];
            }
            temp_gray.at<uchar>(j, i) = num2 / 3;
                
        }
    }
    return temp_gray;
}

cv::Mat temprate(cv::Mat temp_gray){

    cv::Mat value4(TMP_SIZE_H, TMP_SIZE_W, CV_8UC1);
    cv::Mat fea_temp(TMP_SIZE_H, TMP_SIZE_W, CV_8UC1);
    int i, j, p, count;

    //グレースケールのテンプレート画像を2値化
    for( j = 0; j < TMP_SIZE_H; j++ ){

        for( i = 0; i < TMP_SIZE_W; i++ ){

            if(temp_gray.at<uchar>(j, i) < 130){
                value4.at<uchar>(j,i) = 0;
            }
            else{
                value4.at<uchar>(j,i) = 255;
            }

        }
    }

    count = 0;

    //テンプレートの2値化画像から縦に画素が続いている箇所を抽出
    for(j = 0; j < TMP_SIZE_W; j++){
        for(i = 0; i < TMP_SIZE_H; i++){
            if(value4.at<uchar>(i, j) == 0){
                count ++;
            }else{
                if(count > 3 && count < 10 && value4.at<uchar>(i - count / 2, j - 1) == 255){
                    for(p = 0; p < count; p++){
                        fea_temp.at<uchar>(i - p, j) = 255;
                    }
                }
                count = 0;
            }
        }
    }

    return fea_temp;
}





Point matching(unsigned char input[CHANNEL][INPUT_SIZE_H][INPUT_SIZE_W], unsigned char temp[CHANNEL][TMP_SIZE_H][TMP_SIZE_W] ){

    // 変数の宣言
    int i, j, I, J, k;                                              
    Point out_point;                                                   

    // 初期化
    out_point.x = out_point.y = 0;



if(TMP_SIZE_W==110){
        
     int A=12;
     int B=3;

     int tmpa[A]={0};
     int tmpb[A]={0};
 
     int fruittmp[256][256]={0};


     
        for(j=0;j<TMP_SIZE_H;j++){
            for(i=0;i<TMP_SIZE_W-1;i++){
              
                fruittmp[temp[2][j][i]][temp[2][j][i+1]]++;
            }
        }


        int count=0;
        int ans=0;
        
       for(j=0;j<256;j++){
            for(i=0;i<256;i++){
                if(fruittmp[j][i]==1){
                    tmpa[count]=j;
                    tmpb[count]=i;
                    count++;
                }if(count==A){
                    ans=1;
                    break;
                }
             }
             if(ans==1){
                break;
             }
            }

        int pa[A]={0};
        int pb[A]={0};

   
       for(k=0;k<A;k++){
         for(j=0;j<TMP_SIZE_H;j++){
            for(i=0;i<TMP_SIZE_W-1;i++){
                if(temp[2][j][i]==tmpa[k] && temp[2][j][i+1]==tmpb[k]){
                    pa[k]=j;
                    pb[k]=i;
                }
            }
          }
        }

        int K,L,M;
        int dcount;
        int da,db,dc,dd,de,DD;
        k=L=M=da=db=dc=dd=de=DD=0;

        for(k=0;k<A;k++){
 
          for(j=0;j<INPUT_SIZE_H;j++){
             for(i=0;i<INPUT_SIZE_W-1;i++){

                dcount=0;

                if(input[2][j][i]==(tmpa[k])&&input[2][j][i+1]==(tmpb[k])){
                    L=j-pa[k];
                    M=i-pb[k];
                     for(J=L;J<(L+TMP_SIZE_H);J++){
                        for(I=M;I<(M+TMP_SIZE_W-1);I++){

                            for(K=0;K<A;K++){
                                if(input[2][J][I]==(tmpa[K])&&input[2][J][I+1]==(tmpb[K])){
                                    dcount++;

                                }

                                     if(dcount>B){
                                    out_point.x=M;
                                    out_point.y=L;
                                    da=1;

                                    break;
                                    }
                            }


                                 if(da==1){
                                    de=1;

                                    break;
                                    }
                        }


                                           if(de==1){
                                                 db=1;
                                                   break;
                                             }

                               }


                                            if(db==1){
                                                DD=1;
                                                break;
                                            }

                     }



                                          if(DD==1){
                                             dc=1;
                                             break;
                                         }


                 }
          

                              if(dc==1){
                                  dd=1;
                                  break;
                              }
             }
      
                              if(dd==1){
                                  break;
                              }

         }

        return out_point;

}






//標識　青画素
if(TMP_SIZE_H==130){


    int tmp_x,w,value,y,tmp_y;
    int sum=0;
    tmp_x=value=y=tmp_y=w=0;


   for(j=0;j<TMP_SIZE_H;j++){
        for(i=0;i<TMP_SIZE_W;i++){

           if(temp[0][j][i]!=255){
                value=temp[0][j][i];
                tmp_y=j;
                tmp_x=i;
                for(int J=0; J<TMP_SIZE_H/4;J++){
                    sum+=temp[0][J][i];
                }


                y=1;
                break;
           }
        }
        if(y==1){
            break;
        }
    }


    for(j=0;j<INPUT_SIZE_H;j++){
        for(i=0;i<INPUT_SIZE_W;i++){

            int sum1=0;
            if(input[0][j][i]==value){
                for(int J=j-tmp_y;J<j-tmp_y+TMP_SIZE_H/4;J++){
                    sum1+=input[0][J][i];
                }

                  if(sum==sum1){
                  out_point.x=i-tmp_x;
                  out_point.y=j-tmp_y;
                  w=1;
                  break;
               }else{
                i+=TMP_SIZE_W;
               }
            }

        
        }
        if(w==1){
            break;
        }
    }


       return out_point;

}




//フルーツok　青画素
if(TMP_SIZE_W==212){
        
        int A,B,C,D;
        A=45;
        B=25;
        C=2;
        D=1;

     int tmpa[A]={0};
     int tmpb[A]={0};
 
     int fruittmp[256][256]={0};


   
        for(j=0;j<TMP_SIZE_H/C-D;j++){
            for(i=0;i<TMP_SIZE_W-D;i++){
                fruittmp[temp[0][j+(TMP_SIZE_H/C)][i]][temp[0][j+(TMP_SIZE_H/C)+D][i+D]]++;
            }

        }

    
        int count=0;
        

        while(count<A){
            i=rand()%256;
            j=rand()%256;
            if(fruittmp[j][i]==1){
                    tmpa[count]=j;
                    tmpb[count]=i;
                    count++;
            }
            
        }



        int pa[A]={0};
        int pb[A]={0};


        for(k=0;k<A;k++){
         for(j=0;j<TMP_SIZE_H/C-D;j++){
            for(i=0;i<TMP_SIZE_W-D;i++){
                if(temp[0][j+(TMP_SIZE_H/C)][i]==tmpa[k] && temp[0][j+(TMP_SIZE_H/C)+D][i+D]==tmpb[k]){
                    pa[k]=j;
                    pb[k]=i;
                }
            }
          }
        }
 
        int K,L,M;
        int dcount;
        int da,db,dc,dd,de,DD;
        k=L=M=da=db=dc=dd=de=DD=0;

        for(k=0;k<A;k++){
  
          for(j=0;j<INPUT_SIZE_H-(TMP_SIZE_H/C)-D;j++){
             for(i=0;i<INPUT_SIZE_W-D;i++){

                dcount=0;

                if(input[0][j][i]==tmpa[k]&&input[0][j+D][i+D]==tmpb[k]){
                    L=j-pa[k];
                    M=i-pb[k];
      
                     for(J=L;J<(L+(TMP_SIZE_H/C)-D);J++){
                        for(I=M;I<(M+TMP_SIZE_W-D);I++){

                            for(K=0;K<A;K++){
                                if(input[0][J][I]==tmpa[K]&&input[0][J+D][I+D]==tmpb[K]){
                                    dcount++;
                                    

                                }
                            }


                                 if(dcount>B){
                                    out_point.x=M;
                                    out_point.y=L-(TMP_SIZE_H/C);
                                    da=1;

                                    break;
                                    }
                        }


                                           if(da==1){
                                                 db=1;
                                                   break;
                                             }

                               }



                     }



                                          if(db==1){
                                             dc=1;
                                             break;
                                         }


                 }
          

                              if(dc==1){
                                  dd=1;
                                  break;
                              }
             }
      
                              if(dd==1){
                                  break;
                              }

         }

      
        return out_point;

   }

  



    //百人一首
 if(TMP_SIZE_W == 117){


// 変数の宣言
    int i, j, p ,q;
    int red, blue, green, count, ans, num, num0, num1, num2;
    double sum;                                                         // カウンター
    Point out_point;                                                    // 検出位置

    cv::Mat value1(INPUT_SIZE_H, INPUT_SIZE_W, CV_8UC1);
    cv::Mat value2(INPUT_SIZE_H, INPUT_SIZE_W, CV_8UC1);
    cv::Mat fea_input(INPUT_SIZE_H, INPUT_SIZE_W, CV_8UC1);

    // 初期化
    out_point.x = out_point.y = 0;
    num1 = TMP_SIZE_H * TMP_SIZE_W * 0.6;
    num2 = TMP_SIZE_H * TMP_SIZE_W * 0.4;

    //入力画像のグレースケール
    cv::Mat enter_gray = entergrayskale(input);
    //テンプレート画像のグレースケール
    cv::Mat temp_gray = tempgrayskale(temp);

    cv::Mat fea_temp = temprate(temp_gray);

    //画像中で青色成分が最も多い画素を選択した2値化画像を作成し，画像中で札がどの位置にあるかを示す

    for( j = 0; j < INPUT_SIZE_H; j++ ){

        for( i = 0; i < INPUT_SIZE_W; i++ ){

            blue = input[0][j][i];//青成分
            green = input[1][j][i];//緑成分
            red = input[2][j][i];//赤成分

            if(blue > red && blue > green){
                value1.at<uchar>(j,i) = 255;
            }else{
                value1.at<uchar>(j,i) = 0;
            }

        }
    }

    //入力画像に平滑化フィルタをかける
    for( j = 0; j < INPUT_SIZE_H; j++ ){

        for( i = 0; i < INPUT_SIZE_W; i++ ){

                // sumの初期化
                sum = 0.0;

                for( q = 0; q < 11; q++ ){

                    for( p = 0; p < 11 ; p++ ){

                        sum += value1.at<uchar>(j+q,i+p) / 121;

                    }
                }

                if((sum == 0 && enter_gray.at<uchar>(j,i) < 130) || sum > 10){
                    value2.at<uchar>(j,i) = 0;
                }else{
                    value2.at<uchar>(j,i) = 255;
                }

        }
    }


    count = 0;

    //2値化の入力画像から縦に画素が続いている箇所を抽出
    for(j = 0; j < INPUT_SIZE_W; j++){
        for(i = 0; i < INPUT_SIZE_H; i++){

            fea_input.at<uchar>(i, j) = 0;

            if(value2.at<uchar>(i, j) == 0){
                count ++;

            }else{
                if(count > 3 && count < 10 && value2.at<uchar>(i - count / 2, j - 1) == 255){
                    for(p = 0; p < count; p++){
                        fea_input.at<uchar>(i - p, j) = 255;
                    }
                }
                count = 0;
            }
        }
    }

    //2枚の特徴量を抽出した画像からマッチングを行う
    ans = 0;
    count = 0;


    for(j = 0; j < INPUT_SIZE_H - TMP_SIZE_H; j++){
        for(i = 0; i < INPUT_SIZE_W - TMP_SIZE_W; i++){

            //札の領域内のみ
            if(value2.at<uchar>(j + TMP_SIZE_H / 2, i + TMP_SIZE_W / 2) == 255){

                num0 = 0;

                for(p = 0; p < 20; p++){

                    if(value2.at<uchar>(j - 10, i - 10 + p) == 255){
                        num0 ++;
                    }

                    if(value2.at<uchar>(j - 10 + p, i + 10) == 255){
                        num0 ++;
                    }

                    if(value2.at<uchar>(j + 10, i + 10 - p) == 255){
                        num0 ++;
                    }

                    if(value2.at<uchar>(j + 10 - p, i - 10) == 255){
                        num0 ++;
                    }
                }

                if(num0 > 20){

                    num = 0;
                    count = 0;

                    for(p = 0; p < TMP_SIZE_H; p++){
                        for(q = 0; q < TMP_SIZE_W; q++){

                            if(fea_input.at<uchar>(j + q, i + p) == 255 && fea_temp.at<uchar>(q, p) == 255){
                                count++;
                            }

                            if(value2.at<uchar>(j, i) == 0){
                                num++;
                            }
                        }
                    }

                    if(count > ans){
                        ans = count;
                        out_point.x = i;
                        out_point.y = j;
                    }

                    if(ans > 100){
                        break;
                    }
                
                    if(num > num1){
                        i += TMP_SIZE_W / 2;
                    }else if(num > num2){
                        i += TMP_SIZE_W / 4;
                    }
                }
            }
        }
        if(ans > 100){
            break;
        }
    }

    return out_point;

  }



}

