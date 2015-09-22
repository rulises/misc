#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int board [81] = { 0 };

void printBoard(){
    int i = 0;
    int j = 0;    
    
    printf("-------------------------\n");
    for (i = 0; i < 9; i ++)
    {
        printf("| ");
        for (j = 0; j < 9; j++)
        {
            if ( board[ i * 9 + j ] == 0) printf("  ");
            else printf("%d ", board[ i * 9 + j ]);
            if ( j % 3 == 2) printf("| "); 
        }
        printf("\n");
        if ( i % 3 == 2) printf("-------------------------\n");
    }
}

int checkRowCol(int digit, int i, int j){
    int n = 0;
    for (n = 0; n < 9 ; n++){
        if (board[i * 9 + n] == digit)
            return 0;
    }
    for (n = 0; n < 9 ; n++){
        if (board[n * 9 + j] == digit)
            return 0;
    }
    return 1;
}

int nextDigit(int i, int j)
{
    int digit = 1;
    int low_i = i / 3;
    int low_j = j / 3;
    int idx_i;
    int idx_j;
    int not_finished = 1;
    if(board[i * 9 + j])
        digit =  board[i * 9 + j] + 1;
    while(not_finished)
    {
        if (digit > 9) break;
        for(idx_i = 0; idx_i < 3; idx_i++)
        {
            for(idx_j = 0; idx_j < 3; idx_j++)
            {
                if ( board[low_i * 9 * 3 + idx_i * 9 + low_j * 3 + idx_j] == digit)
                {
                    digit++;
                    break;
                } 
            }
            if(idx_j != 3) idx_i = -1;
        }
        if(idx_i == 3 && idx_j == 3)
        {
            if(checkRowCol(digit, i, j))
                not_finished = 0;
            else{
                digit++;
            }
        }
    }
    return digit;
}

int findNextBlank(int i, int j){
    for ( ; i < 9; i++)
    {
        for ( ; j < 9; j++)
        {
            if (board[ i * 9 + j] == 0){
                return i * 9 +j;
            }
        }
        j = 0;
    }
    return 0;
}

int solveIndex(int i, int j)
{
    int d;
    while(1){
        d = nextDigit(i, j);
        //printf("Next Digit: %d\n",d);
        if (d > 9) return 0;
        board[ i * 9 + j] = d;
        int index = findNextBlank(i, j );
        if(index == 0) return 1;
        int index_i = index / 9;
        int index_j = index - index_i * 9;
        int ret = solveIndex(index_i, index_j);
        if(ret) return 1;
        else 
        {
            board[index_i * 9 + index_j] = 0;
        }
    }
    return 1;
}

int solve()
{
    int index = findNextBlank(0, 0);
    int index_i = index / 9;
    int index_j = index - index_i * 9;

    solveIndex(index_i, index_j);
    return 1;    
}


void parseBoard(const char* file){
    FILE *inFile;
    char *mode = "r";
    inFile = fopen(file, mode);
    if( inFile == NULL){
        fprintf(stderr, "Can't open input file in.list!\n");
        exit(1);
    }
    int i = 0;
    while ( fscanf(inFile, "%d %d %d %d %d %d %d %d %d", 
            (int *) (board + i + 0), (int *) (board + i + 1), (int *) (board + i + 2),
            (int *) (board + i + 3), (int *) (board + i + 4), (int *) (board + i + 5),
            (int *) (board + i + 6), (int *) (board + i + 7), (int *) (board + i + 8))
            != EOF) {
    i += 9;
    }
}


int main( int argc, const char* argv[] )
{
    if (argc < 2)
    {
        printf("Error: missing input file\n");
        return -1;
    }
    
    printf( "Input Board found at: %s\n", argv[1] );
    parseBoard(argv[1]);
    printBoard();
    printf("=======================================================\n");
    solve();
    printBoard();
}

