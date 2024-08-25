#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]){
    FILE *fp_in, *fp_out;
    int input;
    int count = 0;
    int max_data_size = 200;
    double data[max_data_size][2];
    double label[max_data_size];
    int i, j, g;
    double tmp;

    //input//
    fp_in = fopen(argv[1], "r");
    if (fp_in == NULL){
        printf("fail: cannot open the input-file. Change the name of input-file. \n");
        return -1;
    }

	while( (input=fscanf(fp_in, "%lf,%lf", &data[count][0], &data[count][1])) != EOF){
		//printf("%lf %lf\n", data[count][0], data[count][1]);
		count++;
	}

    fclose(fp_in);

    //LOF//
    int k;
    double N[max_data_size][k]; //Nk(A)配列
    double d[max_data_size][max_data_size];
    int indices[max_data_size][max_data_size]; // データの組み合わせのインデックス
    double reach[max_data_size]; //reach-distの配列
    double lrd[max_data_size]; //lrdの配列

    // コマンドライン引数から k の値を取得
    if (argc != 4) {
        printf("Usage: %s <input-file> <output-file> <k>\n", argv[0]);
        return -1;
    }

    k = atoi(argv[3]); // 第4引数を整数に変換

    // k の値の妥当性を確認
    if (k <= 0) {
        printf("k should be a positive integer.\n");
        return -1;
    }

    //各データの距離を配列に格納
    for(i = 0; i < max_data_size; i++){
        for(j = 0; j < max_data_size; j++){
            //注目したデータと他のデータの距離
            d[i][j] = sqrt(pow(data[i][0] - data[j][0], 2) + pow(data[i][1] - data[j][1], 2)); 
            // データの組み合わせを保存
            indices[i][j] = j;
        }
    }

    //d[i][j]配列をデータに対しての距離をソート
    for(i = 0; i < max_data_size; i++){
        for(j = 0; j < max_data_size; j++){
            for(g = j + 1; g < max_data_size; g++){
                if(d[i][j] > d[i][g]){
                    // ソート
                    tmp = d[i][j];
                    d[i][j] = d[i][g];
                    d[i][g] = tmp;
                    // 対応するデータの組み合わせもソート
                    tmp = indices[i][j];
                    indices[i][j] = indices[i][g];
                    indices[i][g] = tmp;
                }
            }
        }
    }

    // d[i][j]のk個をN[i][k]配列に格納する
    for (i = 0; i < max_data_size; i++) {
        int current_index = 0;  // 配列Nのインデックス
        for (j = 0; j < max_data_size && current_index < k; j++) {
            if (i != indices[i][j]) {  // 自分自身との距離は含めない
                N[i][current_index] = d[i][j];
                current_index++;
            }
        }
    }

    //reach-distの総和を求める
    for(i = 0; i < max_data_size; i++){
        for(j = 0; j < k; j++){
            if(N[i][j] < N[indices[i][j]][k - 1]){
                reach[i] += N[indices[i][j]][k - 1];
            }else{
                reach[i] += N[i][j];
            }
        }
    }

    //lrdを求める
    for(i = 0; i < max_data_size; i++){
        lrd[i] = k / reach[i];
    }

    // labelの初期化を行う
    for(i = 0; i < max_data_size; i++){
        label[i] = 0.0;
    }

    //LOFを求める
    double lrdB[i];
    for(i = 0; i < max_data_size; i++){
        for(j = 0; j < k; j++){
            lrdB[i] += lrd[indices[i][j]];
        }
    }

    for(i = 0; i < max_data_size; i++){
        label[i] = lrdB[i] / k / lrd[i];
    }


	//Output//
	fp_out = fopen(argv[2],"w");
	if(fp_out==NULL){
		printf("fail: cannot open the output-file. Change the name of output-file.  \n");
		return -1;
	}


	for(i=0;i<200;i++){
		fprintf(fp_out, "%lf,%lf,%f\n", data[i][0], data[i][1], label[i]);
	}

    return 0;
}
