#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    FILE *fp_in, *fp_out;
    int input;
    int count = 0;
    int max_data_size = 200;
    double data[max_data_size][2];
    int label[max_data_size];
    int i, j;

    //input//
    fp_in = fopen(argv[1], "r");
    if (fp_in == NULL) {
        printf("fail: cannot open the input-file. Change the name of input-file. \n");
        return -1;
    }

	while( (input=fscanf(fp_in, "%lf,%lf", &data[count][0], &data[count][1])) != EOF){
		//printf("%lf %lf\n", data[count][0], data[count][1]);
		count++;
	}

    fclose(fp_in);

    // k-means //
    int k;
    double centroids[k][2];
    int data_size = count;

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

    //各クラスタの重心の初期値を決定する
    for (j = 0; j < k; j++) {
        int random_index = rand() % data_size;
        centroids[j][0] = data[random_index][0];
        centroids[j][1] = data[random_index][1];
    }

    while (1) {
        int flg = 1;

        //クラスタの更新
        double d[k];
        double min_d;
        int min_k;
        double sum[k][2];
        int count[k];

        double centroids2[k][2];

        for (i = 0; i < data_size; i++) {
            min_d = sqrt(pow(centroids[0][0] - data[i][0], 2) + pow(centroids[0][1] - data[i][1], 2));
            min_k = 0;

            for (j = 0; j < k; j++) {
                d[j] = sqrt(pow(centroids[j][0] - data[i][0], 2) + pow(centroids[j][1] - data[i][1], 2));

                if (d[j] < min_d) {
                    min_d = d[j];
                    min_k = j;
                }
            }

            label[i] = min_k;
        }

        // クラスタの重心を計算する
        for (j = 0; j < k; j++) {
            sum[j][0] = 0;
            sum[j][1] = 0;
            count[j] = 0;
        }

        for (i = 0; i < data_size; i++) {
            sum[label[i]][0] += data[i][0];
            sum[label[i]][1] += data[i][1];
            count[label[i]]++;
        }

        for (j = 0; j < k; j++) {
            if (count[j] > 0) {
                centroids2[j][0] = sum[j][0] / count[j];
                centroids2[j][1] = sum[j][1] / count[j];
            } else {
                centroids2[j][0] = centroids[j][0];
                centroids2[j][1] = centroids[j][1];
            }
        }

        // クラスタの重心が変化したら更新
        for (j = 0; j < k; j++) {
            if (centroids2[j][0] != centroids[j][0] || centroids2[j][1] != centroids[j][1]) {
                flg = 0;
                break;
            }
        }

        // クラスタの重心を新しい重心に更新
        for (j = 0; j < k; j++) {
            centroids[j][0] = centroids2[j][0];
            centroids[j][1] = centroids2[j][1];
        }

        if (flg != 0) {
            break;
        }
    }

	//Output//
	fp_out = fopen(argv[2],"w");
	if(fp_out==NULL){
		printf("fail: cannot open the output-file. Change the name of output-file.  \n");
		return -1;
	}


	for(i=0;i<200;i++){
		fprintf(fp_out, "%lf,%lf,%d\n", data[i][0], data[i][1], label[i]);
	}

    return 0;
}

