#include"generator.h"
static char buf[MAX];


void sudoku_generate(int n){
    int cot = n;
    buf[0] = '\0';
    int bit = 0;
    //char str[30];
    char line[9] = { '5','1','2','3','4','6','7','8','9' };
    char line1[19] = { '5',' ','1', ' ' ,'2', ' ','3',' ','4', ' ','6',' ','7',' ','8',' ','9','\n','\0' };
    int shift[9] = { 0,6,12,2,8,14,4,10,16 };

    int pos1[6][3] = { { 3,4,5 },{ 3,5,4 },{ 4,5,3 },{ 4,3,5 },{ 5,4,3 },{ 5,3,4 } };
    int pos2[6][3] = { { 6,7,8 },{ 6,8,7 },{ 7,6,8 },{ 7,8,6 },{ 8,6,7 },{ 8,7,6 } };

    char final[10][19];
    int flag = 0;
    char str[200];
    int i,j,k;

    //初始值置空格和\0
    for (i = 0; i < 9; i++){
        for (j = 0; j < 17; j++){
            final[i][j] = ' ';
        }
        final[i][17] = '\n';
        final[i][18] = '\0';
    }
    final[9][0] = '\n';//第10行只有一个空行
    final[9][1] = '\0';

    FILE *fp = fopen(SUDOKUPATH, "w");
    //生成第一行
    do{
        for (i = 0; i < 9; i++){
            line1[2 * i] = line[i];
        }
        memcpy(final[0], line1, sizeof(line1));
        //以第一行为基础，生成一个终局
        for (i = 1; i < 9; i++){
            for (j = 0; j < 18; j += 2){
                final[i][j] = line1[(j + shift[i]) % 18];
            }
        }
        //在一个终局的基础上改变4-6,7-9行的输出顺序即可
        for (i = 0; i < 6; i++){
            for (j = 0; j < 6; j++){
                str[0] = '\0';
                flag++;
                //前三行
                for (k = 0; k < 3; k++){
                    strcpy(buf + bit, final[k]);
                    bit += 18;
                }
                //3 4 5行
                for (k = 0; k < 3; k++){
                    strcpy(buf + bit, final[pos1[i][k]]);
                    bit += 18;
                }
                //6 7 8行
                for (k = 0; k < 3; k++){
                    strcpy(buf + bit, final[pos2[j][k]]);
                    bit += 18;
                }

                strcpy(buf + bit, "\n");
                bit++;
                if (n == 1){
                    buf[163 * (cot - 1) + 161] = '\0';
                    fputs(buf, fp);
                }
                n--;
                if (!n) { fclose(fp); return; }
            }
        }

    }
    while (next_permutation(line + 1, line + 9));
}

void ques_generate(int ques_num){
    std::random_device rd;
    std::default_random_engine randomEngine(rd());
    std::uniform_int_distribution<int> dis1(1,100);
    FILE *fpQues1;
    FILE *fpBase1;
    char str[200];

    fpBase1 = fopen(SUDOKUPATH, "r");
    fpQues1 = fopen(QUESPATH, "w");
    ques_board[9][0] = '\n';
    ques_board[9][1] = '\0';
    while (ques_num--){
        str[0] = '\0';
        for (int i = 0; i < 9; i++){
            fgets(ques_board[i], 20, fpBase1);
        }fgetc(fpBase1);

        //int base[9] = { 0,3,6,27,30,33,54,57,60 };
        int base[9] = { 0,6,12,54,60,66,108,114,120 };
        //int plus[9] = { 0,1,2,9,10,11,18,19,20 };
        int plus[9] = { 0,2,4,18,20,22,36,38,40 };
        //每个3*3随机掏空2个
        for (int k : base){
            int i, j, hole[2];//3*3里面掏的位置
            hole[0] = dis1(randomEngine)%9;
            hole[1] = dis1(randomEngine)%9;
            //防止重复
            while (hole[0] == hole[1]){
                hole[1] = dis1(randomEngine) % 9;
            }
            for (int t : hole) {
                int dot;
                dot = k + plus[t];
                i = dot / 18;
                j = dot % 18;
                ques_board[i][j] = '0';
            }
        }

        //已经掏空了18个
        int others;
        others = 12 + dis1(randomEngine) % 31;//再掏12-41个就可以了
        while (others--){
            int k = dis1(randomEngine) % 81;
            int i = k / 9;
            int j = k % 9;

            j *= 2;
            if (ques_board[i][j] != '0')
                ques_board[i][j] = '0';
            else others++;
        }
        for (auto & i : ques_board){
            strcat(str, i);
        }
        if (!ques_num)
            str[161] = '\0';
        fputs(str, fpQues1);
    }
    fclose(fpBase1);
    fclose(fpQues1);
}

