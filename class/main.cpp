#include"sudoku.h"
using namespace std;
static int settle_flag = 0;

void prune(int i, int j, bool point[10]) {
    //行排除
    for (int k = 0; k < 18; k += 2) {
        if (ques_board[i][k] != '0' && k != j)point[ques_board[i][k] - '0'] = true;
    }
    //列排除
    for (int k = 0; k < 9; k++) {
        if (ques_board[k][j] != '0' && k != i)point[ques_board[k][j] - '0'] = true;
    }
    int m = 0, n = 0;
    if (i / 3 == 0)m = 0;
    else if (i / 3 == 1)m = 3;
    else if (i / 3 == 2)m = 6;
    if (j / 6 == 0)n = 0;
    else if (j / 6 == 1)n = 6;
    else if (j / 6 == 2)n = 12;
    for (int c = m; c < m + 3; c++) {
        for (int d = n; d < n + 6; d += 2) {
            if (c != i && d != j && ques_board[c][d] != '0')point[ques_board[c][d] - '0'] = true;
        }
    }
}

void settle(int pos){
    if (pos == 162){
        settle_flag = 1;
        return;
    }
    int i, j, k;
    i = pos / 18;
    j = pos % 18;
    bool point[10] = { false };
    if (ques_board[i][j] == '0'){
        prune(i, j, point);
        for (k = 1; k <= 9; k++){
            if (point[k])continue;
            ques_board[i][j] = (char)(k + '0');
            settle(pos + 2);
            if (settle_flag) { return; }
            ques_board[i][j] = '0';
        }
    }
    else{
        settle(pos + 2);
    }
    if (settle_flag) { return; }
}


void settle_ques() {
    int begin = 0, end = 0;
    int total = 0;
    int num = 0;
    FILE *fpQues, *fpSolution;
    char strSolution[200];
    fpQues = fopen(AbsolutePath, "r");
    if (fpQues == nullptr){
        fpQues = fopen(QUESPATH, "r");
        if (fpQues == nullptr){
            cout<< "Question File does not exist. "
                << "Use"
                << "      sudoku -c number --> generate n sudoku finals. \n"
                << "      sudoku -p number --> produce sudoku problem \n"
                << endl;
        }
        else{
            cout<< "File path input is not exist, will execute " << QUESPATH << endl;
        }
    }
    fpSolution = fopen(SUDOKUPATH, "w");
    while (true) {
        for (int i = 0; i < 9; i++) {
            fgets(ques_board[i], 20, fpQues);
        }
        int flag = fgetc(fpQues);//读取中间的空行，判断是否文件尾
        begin = (int) clock();
        settle_flag = 0;
        settle(0);
        end = (int) clock();
        total += end - begin;
        strSolution[0] = '\0';
        for (int i = 0; i < 9; i++) {
            strcat(strSolution, ques_board[i]);
        }
        if (flag == EOF)
            strSolution[161] = '\0';
        else {
            strSolution[161] = '\n';
            strSolution[162] = '\n';
            strSolution[163] = '\0';
        }
        fputs(strSolution, fpSolution);
        num++;
        if (flag == EOF){
            break;
        }
    }
    cout<<"Last puzzle's solution is"<<endl<<strSolution<<endl;
    cout <<num<<" Puzzles "<< "solving time: " << total<<endl;
    fclose(fpQues);
    fclose(fpSolution);
}

void print_help(){
    cout << "Usage:\n"
         << "      sudoku -c number --> generate n sudoku finals. \n"
         << "      sudoku -p number --> produce sudoku problem into the given path(prepare for the sudoku game)\n"
         << "      sudoku -s path --> Read sudoku from file in the given path,and solve them.\n"
         << "      sudoku -s 0 --> Read sudoku from ques.txt\n"
         << "      The character should be itself:such as C is not equal to c.\n";
}

int main(int argc, char **argv) {


    if (argc != 3)//参数不等于3个
    {
        cout << "Illegal parameter number\n";
        print_help();
        return 1;
    }

    if ((strcmp(argv[1], "-c") != 0) && (strcmp(argv[1], "-s") != 0) && (strcmp(argv[1], "-p") != 0)) {
        cout << "Illegal parameter\n"
             << "The first parameter should be -c or -s or -p\n"
             << "-c means generating sudoku\n"
             << "-p meas generating sudoku problem\n"
             << "-s meas solve the problem read from the file\n";
        return 1;
    }

    if (!strcmp(argv[1], "-c"))//judge the second parameter when -c
    {
        int len = (int) strlen(argv[2]);
        for (int i = 0; i < len; i++) {
            if (argv[2][i] > '9' || argv[2][i] < '0') {
                cout << "Illegal parameter\n";
                cout << "The second parameter should be a positive integer\n";
                return 1;
            }
        }

        int number = 0;
        for (int i = 0; i < len; i++) {
            number = number * 10 + argv[2][i] - '0';
        }
        Solution solution;
        solution.sudoku_generate(number);
        cout << "The sudoku final generated is in the sudoku.txt\n"
             << "Have a check\n";
        return 0;
    }

    if (!strcmp(argv[1], "-s")) {
        strcpy(AbsolutePath, argv[2]);
        settle_ques();
        cout << "The answer you need is in the sudoku.txt\n"
             << "Have a check\n";
        return 0;
    }

    if (!strcmp(argv[1], "-p"))//default path ques.txt
    {
        int len = (int) strlen(argv[2]);
        for (int i = 0; i < len; i++) {
            if (argv[2][i] > '9' || argv[2][i] < '0') {
                cout << "Illegal parameter\n";
                cout << "The second parameter should be a positive integer\n";
                return 1;
            }
        }

        int number = 0;
        for (int i = 0; i < len; i++) {
            number = number * 10 + argv[2][i] - '0';
        }
        Question question;
        question.ques_generate(number);
        cout << "The sudoku question generated is in the ques.txt\n"
             << "Have a check\n";
        return 0;
    }

    system("pause");
    return 0;
}