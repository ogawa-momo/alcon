#include"integration.hpp"
#include"staff_struct.hpp"
#include"matching.hpp"

// ============================↓↓↓編集可能↓↓↓========================== //
#include"luts.hpp"

Point matching(unsigned char input[CHANNEL][INPUT_SIZE_H][INPUT_SIZE_W], unsigned char temp[CHANNEL][TMP_SIZE_H][TMP_SIZE_W] ){

    // 変数の宣言
    int i, j, I, J, k,L,M;                                                  // カウンター
    double loss[INPUT_SIZE_H-TMP_SIZE_H+1][INPUT_SIZE_W-TMP_SIZE_W+1];  // 誤差保存用
    Point out_point;                                                    // 検出位置

    // 初期化
    out_point.x = out_point.y = 0;

    unsigned char r,g,b,gray,gray2;





//テンプレート画像のサイズによって4パターンに分ける


//標識

if(TMP_SIZE_H==130){


    int signred,signgreen,signblue,tmpgreen;
    signred=signgreen=signblue=tmpgreen=0;

    cv::Mat redimage(INPUT_SIZE_H,INPUT_SIZE_W,CV_8UC1);
    cv::Mat greenimage(INPUT_SIZE_H,INPUT_SIZE_W,CV_8UC1);
    cv::Mat blueimage(INPUT_SIZE_H,INPUT_SIZE_W,CV_8UC1);
    cv::Mat Tgreenimage(TMP_SIZE_H,TMP_SIZE_W,CV_8UC1);

        for(j=0;j<INPUT_SIZE_H;j++){
            for(i=0;i<INPUT_SIZE_W;i++){
                signred=input[2][j][i];
                signgreen=input[1][j][i];
                signblue=input[0][j][i];

                redimage.at<uchar>(j,i)=signred;
                greenimage.at<uchar>(j,i)=signgreen;
                blueimage.at<uchar>(j,i)=signblue;


            }
        }


        for(j=0;j<TMP_SIZE_H;j++){
            for(i=0;i<TMP_SIZE_W;i++){
                tmpgreen=temp[1][j][i];

                Tgreenimage.at<uchar>(j,i)=tmpgreen;
            }
        }

        cv::imwrite("Tgreen.bmp",Tgreenimage);


//赤いテンプレート画像はredimageで白くなる…　白所を探す
int signH,signW,n,m,redcount,flag;
signH=signW=redcount=0;
n=m=flag=0;

int Sad,SSad;
Sad=SSad=0;


            for(i=0;i<TMP_SIZE_W;i++){
                SSad+=Tgreenimage.at<uchar>(65,i);
            }
            cv::line(Tgreenimage,cv::Point(0,65),cv::Point(i,65),cv::Scalar(0,0,255),2,cv::LINE_AA);
            printf("SSad=%d",SSad);



for(j=23;j<INPUT_SIZE_H;j+=153){

    printf("j=%d\n",j);

    for(i=23;i<INPUT_SIZE_W-23;i+=153){

        printf("i=%d\n",i);

        Sad=0;
        
        for(I=0;I<TMP_SIZE_W;I++){
            Sad+=greenimage.at<uchar>(j+65,i+I);

        }
        printf("Sad=%d\n",Sad);
            cv::line(greenimage,cv::Point(i,j+65),cv::Point(i+I,j+65),cv::Scalar(0,0,255),2,cv::LINE_AA);


        if(SSad==Sad){
            printf("発見\n");
            out_point.x=i;
            out_point.y=j;
        }


    }



}


        cv::imwrite("linegreen.bmp",greenimage);
        cv::imwrite("Tlinegreen.bmp",Tgreenimage);





             /*   for(J=signH+15;J<signH+15+TMP_SIZE_H;J++){
                    for(I=signW+15;I<signW+15+TMP_SIZE_W;I++){


                        //テンプレートサイズずつ移動させる
                        if(redimage.at<uchar>(J,I)>5){
                            n++;
                            signH=160*n;


                            if(n==3){
                            m++;
                            signH=0;
                            signW=160*m;
                            } 

                        }


                        else{
                            redcount++;
                        }


                        //全部白かったら
                        if(redcount==130){

                            //SAD
                            for(j=J-130;j<J;j++){
                                for(i=I-130;i<I;i++){
                                    Sad+=greenimage.at<uchar>(j,i);
                                }
                            }


                            for(L=0;L<TMP_SIZE_H;L++){
                                for(M=0;M<TMP_SIZE_W;M++){
                                    SSad+=Tgreenimage.at<uchar>(L,M);
                                }
                            }


                            if(Sad==SSad){
                                out_point.x=I-130;
                                out_point.y=J-130;
                            }




                        }


                    }

                }




        cv::imwrite("signred.bmp",redimage);
        cv::imwrite("signgreen.bmp",greenimage);
        cv::imwrite("signblue.bmp",blueimage);
        
        imshow("Dispaly Image",redimage);
        cv::waitKey(0);
        imshow("Dispaly Image",greenimage);
        cv::waitKey(0);
        imshow("Dispaly Image",blueimage);
        cv::waitKey(0);

       //return out_point;*/

       return out_point;

}















//フルーツ
if(TMP_SIZE_H==159){
    int A=40;
    int B=30;

    int n,red,green,blue,tmpred;
    red=green=blue=tmpred=0;

    cv::Mat redimage(INPUT_SIZE_H,INPUT_SIZE_W,CV_8UC1);
    cv::Mat greenimage(INPUT_SIZE_H,INPUT_SIZE_W,CV_8UC1);
    cv::Mat blueimage(INPUT_SIZE_H,INPUT_SIZE_W,CV_8UC1);
    cv::Mat hyakuimage(INPUT_SIZE_H,INPUT_SIZE_W,CV_8UC1);
    cv::Mat hyakuimage2(INPUT_SIZE_H,INPUT_SIZE_W,CV_8UC1);
    cv::Mat Tredimage(TMP_SIZE_H,TMP_SIZE_W,CV_8UC1);
    cv::Mat Thyakuimage(TMP_SIZE_H,TMP_SIZE_W,CV_8UC1);

    cv::Mat grayImage2(TMP_SIZE_H,TMP_SIZE_W,CV_8UC1);



   


    
    cv::Mat grayImage(INPUT_SIZE_H,INPUT_SIZE_W,CV_8UC1);

     //unsigned char Gray[100][100];

        for(j=0;j<(INPUT_SIZE_H);j++){
            for(i=0;i<(INPUT_SIZE_W);i++){
                
                r=input[2][j][i];
                g=input[1][j][i];
                b=input[0][j][i];


                gray=(r+g+b)/3;

  
                grayImage.at<uchar>(j,i)=gray;
            }
        }



        for(j=0;j<INPUT_SIZE_H;j++){
            for(i=0;i<INPUT_SIZE_W;i++){
                red=input[2][j][i];
                green=input[1][j][i];
                blue=input[0][j][i];

                if(blue>red&&blue>green){
                    hyakuimage.at<uchar>(j,i)=255;
                }else{
                    hyakuimage.at<uchar>(j,i)=0;
                }

                redimage.at<uchar>(j,i)=red;
                greenimage.at<uchar>(j,i)=green;
                blueimage.at<uchar>(j,i)=blue;


            }
        }


        double sum=0.0;
        int p,q;
        for(j=0;j<INPUT_SIZE_H;j++){
            for(i=0;i<INPUT_SIZE_W;i++){
                sum=0.0;

                for(q=0;q<11;q++){
                    for(p=0;p<11;p++){
                        sum+=hyakuimage.at<uchar>(j+q,i+p)/121;
                    }
                }

                if(sum==0.0){
                    hyakuimage2.at<uchar>(j,i)=grayImage.at<uchar>(j,i);
                }else{
                    hyakuimage2.at<uchar>(j,i)=0;
                }

            }
        }


        for(j=0;j<TMP_SIZE_H;j++){
            for(i=0;i<TMP_SIZE_W;i++){

                tmpred=temp[2][j][i];
                Tredimage.at<uchar>(j,i)=tmpred;

            }
        }

            for(j=0;j<(TMP_SIZE_H);j++){
            for(i=0;i<(TMP_SIZE_W);i++){
                
                r=temp[2][j][i];
                g=temp[1][j][i];
                b=temp[0][j][i];


                gray2=(r+g+b)/3;

                grayImage2.at<uchar>(j,i)=gray2;
            }
        }







        cv::imwrite("red.bmp",redimage);
        cv::imwrite("green.bmp",greenimage);
        cv::imwrite("blue.bmp",blueimage);
        cv::imwrite("enter.bmp",hyakuimage2);
        
     /*   imshow("Dispaly Image",redimage);
        cv::waitKey(0);
        imshow("Dispaly Image",greenimage);
        cv::waitKey(0);
        imshow("Dispaly Image",blueimage);
        cv::waitKey(0);*/






     //自分で編集したところここまで
    

    

     //同時生起行列の作成
    
     FILE *fp1,*fp2,*fp3,*fp4;

     cv::Mat fruit1(256,256,CV_8UC1);// 同時生起のための画像
     cv::Mat fruit2(256,256,CV_8UC1);

     fp1=fopen("matrix.dat","w");
     fp2=fopen("matrix2.dat","w");
     fp3=fopen("matrixtmp.dat","w");
     fp4=fopen("matrix2tmp.dat","w");


     int tmpa[A];
     int tmpb[A];
 
     int fruit[256][256];
     int fruittmp[256][256];
     int mat[INPUT_SIZE_H][INPUT_SIZE_W];
     int mattmp[TMP_SIZE_H][TMP_SIZE_W];

     for(i=0;i<A;i++){
        tmpa[i]=0;
        tmpb[i]=0;
     }

     for(j=0;j<256;j++){
        for(i=0;i<256;i++){
            fruit[j][i]=0;
            fruittmp[j][i]=0;
        }
     }





     for(k=0;k<256;k++){
        for(j=0;j<INPUT_SIZE_H;j++){
            for(i=0;i<INPUT_SIZE_W;i++){

                if(redimage.at<uchar>(j,i)==k){
                    mat[j][i]=k;
                }
            }
        }
     }


    
    /*for(j=0;j<TMP_SIZE_H;j++){
        for(i=0;i<TMP_SIZE_W;i++){
            if(tmp_cv.at<uchar>(j,i)<120){
                tmp_cv.at<uchar>(j,i)+=1;
            }
        }
    }*/
     //テンプレート用の同時生起
      for(k=0;k<256;k++){
        for(j=0;j<TMP_SIZE_H;j++){
            for(i=0;i<TMP_SIZE_W;i++){
              

                if(Tredimage.at<uchar>(j,i)==k){
                    mattmp[j][i]=k;
                }
            }
        }
     }


        for(j=0;j<INPUT_SIZE_H;j++){
            for(i=0;i<INPUT_SIZE_W;i++){
                fprintf(fp1,"%d\t",mat[j][i]);
            }

                fprintf(fp1,"\n");
        }


        for(j=0;j<TMP_SIZE_H;j++){
            for(i=0;i<TMP_SIZE_W;i++){
                fprintf(fp3,"%d\t",mattmp[j][i]);
            }

                fprintf(fp3,"\n");
        }



        for(j=0;j<INPUT_SIZE_H;j++){
            for(i=0;i<INPUT_SIZE_W-1;i++){
                fruit[mat[j][i]][mat[j][i+1]]++;
            }

        }

        for(j=0;j<TMP_SIZE_H;j++){
            for(i=0;i<TMP_SIZE_W-1;i++){
                fruittmp[mattmp[j][i]][mattmp[j][i+1]]++;
            }

        }

    
        for(j=0;j<256;j++){
            for(i=0;i<256;i++){
                fprintf(fp2,"%d\t",fruit[j][i]);
                fprintf(fp4,"%d\t",fruittmp[j][i]);
            }

                fprintf(fp2,"\n");
                fprintf(fp4,"\n");
        }



        for(j=0;j<256;j++){
            for(i=0;i<256;i++){
                fruit1.at<uchar>(j,i)=fruit[j][i];
                fruit2.at<uchar>(j,i)=fruittmp[j][i];
            }
        }   







        //特徴的な画素の組み合わせを見つける
        int count=0;
        int ans=0;
        
       /* for(j=0;j<256;j++){
            for(i=0;i<256;i++){
                if(fruittmp[j][i]==1){
                    tmpa[count]=j;
                    tmpb[count]=i;
                    count++;
                }if(count==300){
                    ans=1;
                    break;
                }
             }
             if(ans==1){
                break;
             }
            }*/



        while(count<A){
            i=rand()%256;
            j=rand()%256;
            if(fruittmp[j][i]==1){
                    tmpa[count]=j;
                    tmpb[count]=i;
                   // printf("count=%d,tmpa=%d,tmpb=%d\n",count,tmpa[count],tmpb[count]);
                    count++;
            }
            
        }


        //テンプレート画像から組み合わせを見つけ出し、点を打っていく

        int pa[A];
        int pb[A];

        //座標保存用の配列
        for(j=0;j<A;j++){
            pa[j]=0;
            pb[j]=0;
        }




        for(k=0;k<A;k++){
         for(j=0;j<TMP_SIZE_H;j++){
            for(i=0;i<TMP_SIZE_W-1;i++){
                if(mattmp[j][i]==tmpa[k] && mattmp[j][i+1]==tmpb[k]){
                  //  printf("%d個目の画素の組み合わせは%d\t%d\n",k,tmpa[k],tmpb[k]);
                    cv::circle(grayImage2,cv::Point(i,j),3,cv::Scalar(0,0,0),-1);
                 //   printf("k=%d,j=%d,i=%d\n",k,j,i);
                    pa[k]=j;
                    pb[k]=i;
                }
            }
          }
        }

        printf("\n");
        printf("\n");


      /*  for(j=0;j<300;j++){
            printf("%d個目\n",j);
            printf("%d,%d\t",tmpa[j],tmpb[j]);
            printf("%d,%d\t",pa[j],pb[j]);
        }*/


        cv::imwrite("Falcon_2.bmp",grayImage2);

        cv::imwrite("Ffruit1.png",fruit1);
        cv::imwrite("Ffruit2.png",fruit2);


        int K;
        int dcount;
        int da,db,dc,dd,de,DD;
        da=db=dc=dd=de=DD=0;

        for(k=0;k<A;k++){
            //printf("%d\t",k);
          //  printf("%d\t%d\n",tmpa[k],tmpb[k]);
          for(j=0;j<INPUT_SIZE_H-TMP_SIZE_H+1;j++){
             for(i=0;i<INPUT_SIZE_W-TMP_SIZE_W+1;i++){

                dcount=0;

                //まずは画素のペアを見つける
                //見つかればいけそう
                if(mat[j][i]==(tmpa[k])&&mat[j][i+1]==(tmpb[k])){
                   // printf("見つけた座標は%d\t%d\t",i,j);
                   // printf("見つかった！");

                    //領域をテンプレートに変更する
                     for(J=j-pa[k];J<(j-pa[k]+TMP_SIZE_H);J++){
                        for(I=i-pb[k];I<(i-pb[k]+TMP_SIZE_W-1);I++){

                            for(K=0;K<A;K++){
                            //8個見つかるまで
                                if(mat[J][I]==(tmpa[K])&&mat[J][I+1]==(tmpb[K])){
                                    dcount++;
                                    
                                    //printf("みているのは%d\t",tmpb[K]);
                               //    printf("d=%d\tK=%d\t",dcount,K);
                                }
                            }


                                 if(dcount>B){
                                    out_point.x=i-pb[k];
                                    out_point.y=j-pa[k];
                                    da=1;
                                    printf("%d\t%d\t%d\t%d\n",i,j,pb[k],pa[k]);
                                    printf("break1\n");
                                    break;
                                    }
                        }


                                           if(da==1){
                                                 db=1;
                                                printf("break2\n");
                                                   break;
                                             }

                               }


                                            if(db==1){
                                                DD=1;
                                                printf("break2-2\n");
                                                break;
                                            }

                     }



                                          if(DD==1){
                                             dc=1;
                                           printf("break3\n");
                                             break;
                                         }


                 }
          

                              if(dc==1){
                                  dd=1;
                                    printf("break4\n");
                                  break;
                              }
             }
      
                              if(dd==1){
                              printf("break5\n");
                                  break;
                              }

         }

        fclose(fp1);
        fclose(fp2);
        fclose(fp3);
        fclose(fp4);


        return out_point;

}




      // 全画素全探索のテンプレートマッチング SAD
   /*    int lossans=0;
     for( j = 0; j < ( INPUT_SIZE_H - TMP_SIZE_H + 1 ); j++ ){

        for( i = 0; i < ( INPUT_SIZE_W - TMP_SIZE_W + 1 ); i++ ){

            // lossの初期化
            loss[j][i] = 0.0;

            // ラスタスキャン

                for( J = 0; J < TMP_SIZE_H ; J++ ){

                    for( I = 0; I < TMP_SIZE_W ; I++ ){

                        loss[j][i] += sqrt( ( grayImage.at<uchar>(J+j,I+i) - grayImage2.at<uchar>(J,I) ) * ( grayImage.at<uchar>(J+j,I+i) - grayImage2.at<uchar>(J,I) ) );
                    }
                }

                //画像が一致していた場合
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
            if(loss==0){

            }
        }
    }

    return min;*/
}