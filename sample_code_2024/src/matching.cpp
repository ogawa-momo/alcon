#include"integration.hpp"
#include"staff_struct.hpp"
#include"matching.hpp"

// ============================↓↓↓編集可能↓↓↓========================== //
#include"luts.hpp"

//入力画像のグレースケール化
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

Point matching(unsigned char input[CHANNEL][INPUT_SIZE_H][INPUT_SIZE_W], unsigned char temp[CHANNEL][TMP_SIZE_H][TMP_SIZE_W] ){

    // 変数の宣言
    int i, j, I, J, k,L,M;                                                  // カウンター
    double loss[INPUT_SIZE_H-TMP_SIZE_H+1][INPUT_SIZE_W-TMP_SIZE_W+1];  // 誤差保存用
    Point out_point;                                                    // 検出位置

    // 初期化
    out_point.x = out_point.y = 0;

    unsigned char r,g,b,gray,gray2;


    int red,green,blue,tmpred;
    red=green=blue=tmpred=0;


    cv::Mat fruit1(256,256,CV_8UC1);// 同時生起のための画像
    cv::Mat fruit2(256,256,CV_8UC1);



//テンプレート画像のサイズによって4パターンに分ける


//麻雀 ok
if(TMP_SIZE_W==110){


    cv::Mat redimage(INPUT_SIZE_H,INPUT_SIZE_W,CV_8UC1);
   // cv::Mat greenimage(INPUT_SIZE_H,INPUT_SIZE_W,CV_8UC1);
    //cv::Mat blueimage(INPUT_SIZE_H,INPUT_SIZE_W,CV_8UC1);
    cv::Mat Tredimage(TMP_SIZE_H,TMP_SIZE_W,CV_8UC1);

        
     //同時生起行列の作成
     int A=7;
     int B=3;
    
    //  FILE *fp1,*fp2,*fp3,*fp4;

   /* for(j=0;j<TMP_SIZE_H;j++){
        for(i=0;i<TMP_SIZE_W;i++){
            Tredimage.at<uchar>(j,i)=temp[2][j][i];
        }
    }*/



     int tmpa[A]={0};
     int tmpb[A]={0};
 
     int fruit[256][256]={0};
     int fruittmp[256][256]={0};
     int mat[INPUT_SIZE_H][INPUT_SIZE_W];
     int mattmp[TMP_SIZE_H][TMP_SIZE_W];






        /*for(j=0;j<INPUT_SIZE_H;j++){
            for(i=0;i<INPUT_SIZE_W-1;i++){

               
                fruit[input[2][j][i]][input[2][j][i+1]]++;
            }
        }*/

     
     //テンプレート用の同時生起
        for(j=0;j<TMP_SIZE_H;j++){
            for(i=0;i<TMP_SIZE_W-1;i++){
              

                fruittmp[temp[2][j][i]][temp[2][j][i+1]]++;
            }
        }




        //特徴的な画素の組み合わせを見つける
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



       /* while(count<A){
            i=rand()%256;
            j=rand()%256;
            if(fruittmp[j][i]==1){
                    tmpa[count]=j;
                    tmpb[count]=i;
                   // printf("count=%d,tmpa=%d,tmpb=%d\n",count,tmpa[count],tmpb[count]);
                    count++;
            }
            
        }*/


        //テンプレート画像から組み合わせを見つけ出し、点を打っていく

        int pa[A]={0};
        int pb[A]={0};

        //座標保存用の配列
        /*for(j=0;j<A;j++){
            pa[j]=0;
            pb[j]=0;
        }*/




       for(k=0;k<A;k++){
         for(j=0;j<TMP_SIZE_H;j++){
            for(i=0;i<TMP_SIZE_W-1;i++){
                if(temp[2][j][i]==tmpa[k] && temp[2][j][i+1]==tmpb[k]){
                  //  printf("%d個目の画素の組み合わせは%d\t%d\n",k,tmpa[k],tmpb[k]);
                  //    cv::circle(Tredimage,cv::Point(i,j),3,cv::Scalar(255,255,0),-1);
                  //   printf("k=%d,j=%d,i=%d\n",k,j,i);
                    pa[k]=j;
                    pb[k]=i;
                }
            }
          }
        }

        //printf("\n");
        //printf("\n");


       /* for(j=0;j<300;j++){
            printf("%d個目\n",j);
            printf("%d,%d\t",tmpa[j],tmpb[j]);
            printf("%d,%d\t",pa[j],pb[j]);
        }*/
    //   cv:: imwrite("1.bmp",Tredimage);

//       cv::imwrite("Falcon_1.bmp",Tredimage);
       

        int K;
        int dcount;
        int da,db,dc,dd,de,DD;
        k=da=db=dc=dd=de=DD=0;

        for(k=0;k<A;k++){
           // k=rand()%300;
           // printf("観るK%d\t",k);
          //  printf("%d\t%d\n",tmpa[k],tmpb[k]);
          for(j=0;j<INPUT_SIZE_H-TMP_SIZE_H+1;j++){
             for(i=0;i<INPUT_SIZE_W-TMP_SIZE_W+1;i++){

                dcount=0;

                //まずは画素のペアを見つける
                //見つかればいけそう
                if(input[2][j][i]==(tmpa[k])&&input[2][j][i+1]==(tmpb[k])){
                  //  printf("見つけた座標は%d\t%d\t",i,j);
                   // printf("見つかった！");

                    //領域をテンプレートに変更する
                     for(J=j-pa[k];J<(j-pa[k]+TMP_SIZE_H);J++){
                        for(I=i-pb[k];I<(i-pb[k]+TMP_SIZE_W-1);I++){

                            for(K=0;K<A;K++){
                            //8個見つかるまで
                                if(input[2][J][I]==(tmpa[K])&&input[2][J][I+1]==(tmpb[K])){
                                    dcount++;
                                    
                                    //printf("みているのは%d\t",tmpb[K]);
                                   // printf("d=%d\tK=%d\t",dcount,K);
                                }
                            }


                                 if(dcount>B){
                                    out_point.x=i-pb[k];
                                    out_point.y=j-pa[k];
                                    da=1;
                                  //  printf("%d\t%d\t%d\t%d\n",i,j,pb[k],pa[k]);
                                  //  printf("break1\n");
                                    break;
                                    }
                        }


                                           if(da==1){
                                                 db=1;
                                               // printf("break2\n");
                                                   break;
                                             }

                               }


                                            if(db==1){
                                                DD=1;
                                              //  printf("break2-2\n");
                                                break;
                                            }

                     }



                                          if(DD==1){
                                             dc=1;
                                          // printf("break3\n");
                                             break;
                                         }


                 }
          

                              if(dc==1){
                                  dd=1;
                                   // printf("break4\n");
                                  break;
                              }
             }
      
                              if(dd==1){
                              //printf("break5\n");
                                  break;
                              }

         }

      


        return out_point;

}






//標識
if(TMP_SIZE_H==130){


    int A=100;
    int B=80;

    cv::Mat redimage(INPUT_SIZE_H,INPUT_SIZE_W,CV_8UC1);
    cv::Mat greenimage(INPUT_SIZE_H,INPUT_SIZE_W,CV_8UC1);
    cv::Mat blueimage(INPUT_SIZE_H,INPUT_SIZE_W,CV_8UC1);
    cv::Mat Tredimage(TMP_SIZE_H,TMP_SIZE_W,CV_8UC1);

        for(j=0;j<INPUT_SIZE_H;j++){
            for(i=0;i<INPUT_SIZE_W;i++){
                red=input[2][j][i];
                green=input[1][j][i];
                blue=input[0][j][i];

                redimage.at<uchar>(j,i)=red;
                greenimage.at<uchar>(j,i)=green;
                blueimage.at<uchar>(j,i)=blue;


            }
        }


        for(j=0;j<TMP_SIZE_H;j++){
            for(i=0;i<TMP_SIZE_W;i++){

                tmpred=temp[2][j][i];
                Tredimage.at<uchar>(j,i)=tmpred;

            }
        }


        cv::imwrite("red.bmp",redimage);
        cv::imwrite("green.bmp",greenimage);

        cv::imwrite("blue.bmp",blueimage);
        
     cv::Mat grayImage(INPUT_SIZE_H,INPUT_SIZE_W,CV_8UC1);
     cv::Mat grayImage2(TMP_SIZE_H,TMP_SIZE_W,CV_8UC1);

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
    

        for(j=0;j<(TMP_SIZE_H);j++){
            for(i=0;i<(TMP_SIZE_W);i++){
                
                r=temp[2][j][i];
                g=temp[1][j][i];
                b=temp[0][j][i];


                gray2=(r+g+b)/3;

                grayImage2.at<uchar>(j,i)=gray2;
            }
        }





    

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

                if(grayImage.at<uchar>(j,i)==k){
                    mat[j][i]=k;
                }
            }
        }
     }


     //テンプレート用の同時生起
      for(k=0;k<256;k++){
        for(j=0;j<TMP_SIZE_H;j++){
            for(i=0;i<TMP_SIZE_W;i++){
              

                if(grayImage2.at<uchar>(j,i)==k){
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


       /* for(j=0;j<300;j++){
            printf("%d個目\n",j);
            printf("%d,%d\t",tmpa[j],tmpb[j]);
            printf("%d,%d\t",pa[j],pb[j]);
        }*/


        cv::imwrite("Falcon_1.bmp",grayImage);
        cv::imwrite("Falcon_2.bmp",grayImage2);

        cv::imwrite("Ffruit1.png",fruit1);
        cv::imwrite("Ffruit2.png",fruit2);


        int K;
        int dcount;
        int da,db,dc,dd,de,DD;
        k=da=db=dc=dd=de=DD=0;

        while(k<A){
            k=rand()%A;
           // printf("観るK%d\t",k);
          //  printf("%d\t%d\n",tmpa[k],tmpb[k]);
          for(j=0;j<INPUT_SIZE_H-TMP_SIZE_H+1;j++){
             for(i=0;i<INPUT_SIZE_W-TMP_SIZE_W+1;i++){

                dcount=0;

                //まずは画素のペアを見つける
                //見つかればいけそう
                if(mat[j][i]==(tmpa[k])&&mat[j][i+1]==(tmpb[k])){
                    printf("見つけた座標は%d\t%d\t",i,j);
                   // printf("見つかった！");

                    //領域をテンプレートに変更する
                     for(J=j-pa[k];J<(j-pa[k]+TMP_SIZE_H);J++){
                        for(I=i-pb[k];I<(i-pb[k]+TMP_SIZE_W-1);I++){

                            for(K=0;K<A;K++){
                            //8個見つかるまで
                                if(mat[J][I]==(tmpa[K])&&mat[J][I+1]==(tmpb[K])){
                                    dcount++;
                                    
                                    //printf("みているのは%d\t",tmpb[K]);
                                    printf("d=%d\tK=%d\t",dcount,K);
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




//フルーツok
if(TMP_SIZE_W==212){
  //  printf("%d\n",TMP_SIZE_H/2);
        
        int A,B,C,D;
        A=45;
        B=30;
        C=2;
        D=1;

    int red,green,blue,tmpred,tmpgreen,tmpblue,tmpblack;
    red=green=blue=tmpred=tmpgreen=tmpblue=tmpblack=0;




     int tmpa[A]={0};
     int tmpb[A]={0};
 
     int fruit[256][256]={0};
     int fruittmp[256][256]={0};
     int mat[INPUT_SIZE_H][INPUT_SIZE_W];
     int mattmp[TMP_SIZE_H][TMP_SIZE_W];

    





     

    
 
   
        for(j=0;j<TMP_SIZE_H/C-D;j++){
            for(i=0;i<TMP_SIZE_W-D;i++){
                fruittmp[temp[0][j+(TMP_SIZE_H/2)][i]][temp[0][j+(TMP_SIZE_H/2)+D][i+D]]++;
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
                }if(count==A){
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

        int pa[A]={0};
        int pb[A]={0};

      



        for(k=0;k<A;k++){
         for(j=0;j<TMP_SIZE_H/C-D;j++){
            for(i=0;i<TMP_SIZE_W-D;i++){
                if(temp[0][j+(TMP_SIZE_H/2)][i]==tmpa[k] && temp[0][j+(TMP_SIZE_H/2)+D][i+D]==tmpb[k]){
                  // printf("%d個目の画素の組み合わせは%d\t%d\n",k,tmpa[k],tmpb[k]);
                   // cv::circle(Tgreenimage,cv::Point(i,j),2,cv::Scalar(255,0,0),-1);
                 //   printf("k=%d,j=%d,i=%d\n",k,j,i);
                    pa[k]=j;
                    pb[k]=i;
                }
            }
          }
        }

 
        int K;
        int dcount;
        int da,db,dc,dd,de,DD;
        k=da=db=dc=dd=de=DD=0;

        for(k=0;k<A;k++){
            //k=rand()%A;
         //printf("観るK%d\t",k);
            //printf("%d\t%d\n",tmpa[k],tmpb[k]);
          for(j=0;j<INPUT_SIZE_H-(TMP_SIZE_H/C)-D;j++){
             for(i=0;i<INPUT_SIZE_W-D;i++){

                dcount=0;

                //まずは画素のペアを見つける
                //見つかればいけそう
                if(input[0][j][i]==tmpa[k]&&input[0][j+D][i+D]==tmpb[k]){
                //    printf("見つけた座標はi=%d\tj=%d\n",i,j);
                  //  cv::circle(greenimage,cv::Point(i,j),2,cv::Scalar(255,0,0),-1);
                   // printf("見つかった！");

                    //領域をテンプレートに変更する
                     for(J=j-pa[k];J<(j-pa[k]+(TMP_SIZE_H/C)-D);J++){
                        for(I=i-pb[k];I<(i-pb[k]+TMP_SIZE_W-D);I++){

                            for(K=0;K<A;K++){
                            //8個見つかるまで
                                if(input[0][J][I]==tmpa[K]&&input[0][J+D][I+D]==tmpb[K]){
                                //||abs((mat[J][I]-tmpa[K]))<1&&abs((mat[J][I+1]-tmpb[K]))<2||abs((mat[J][I]-tmpa[K]))<2&&abs((mat[J][I+1]-tmpb[K]))<1){
                                    dcount++;
                                    
                                    //printf("みているのは%d\t",tmpb[K]);
                                   // printf("d=%d\tK=%d\t",dcount,K);
                                }
                            }


                                 if(dcount>B){
                                    out_point.x=i-pb[k];
                                    out_point.y=j-pa[k]-(TMP_SIZE_H/2);
                                    da=1;
                                   // printf("%d\t%d\t%d\t%d\n",i,j,pb[k],pa[k]);
                                   // printf("%d,%d\n",out_point.x,out_point.y);
                                   // printf("break1\n");
                                    break;
                                    }
                        }


                                           if(da==1){
                                                 db=1;
                                                // printf("break2\n");
                                                   break;
                                             }

                               }


                                           /* if(db==1){
                                                dc=1;
                                                printf("break2-2\n");
                                                break;
                                            }*/

                     }



                                          if(db==1){
                                             dc=1;
                                        //    printf("break3\n");
                                             break;
                                         }


                 }
          

                              if(dc==1){
                                  dd=1;
                                    // printf("break4\n");
                                  break;
                              }
             }
      
                              if(dd==1){
                              printf("break5\n");
                                  break;
                              }

         }

      

        //printf("1\n");
        // cv::imwrite("FRUITgreen.bmp",greenimage);
        // cv::imwrite("1FRUITgreen.bmp",Tgreenimage);
        return out_point;

   }








}