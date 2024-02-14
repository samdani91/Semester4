#include<stdio.h>

#define SQLITE_N_KEYWORD 147

static const char zKWText[666] = {
  'R','E','I','N','D','E','X','E','D','E','S','C','A','P','E','A','C','H',
  'E','C','K','E','Y','B','E','F','O','R','E','I','G','N','O','R','E','G',
  'E','X','P','L','A','I','N','S','T','E','A','D','D','A','T','A','B','A',
  'S','E','L','E','C','T','A','B','L','E','F','T','H','E','N','D','E','F',
  'E','R','R','A','B','L','E','L','S','E','X','C','L','U','D','E','L','E',
  'T','E','M','P','O','R','A','R','Y','I','S','N','U','L','L','S','A','V',
  'E','P','O','I','N','T','E','R','S','E','C','T','I','E','S','N','O','T',
  'N','U','L','L','I','K','E','X','C','E','P','T','R','A','N','S','A','C',
  'T','I','O','N','A','T','U','R','A','L','T','E','R','A','I','S','E','X',
  'C','L','U','S','I','V','E','X','I','S','T','S','C','O','N','S','T','R',
  'A','I','N','T','O','F','F','S','E','T','R','I','G','G','E','R','A','N',
  'G','E','N','E','R','A','T','E','D','E','T','A','C','H','A','V','I','N',
  'G','L','O','B','E','G','I','N','N','E','R','E','F','E','R','E','N','C',
  'E','S','U','N','I','Q','U','E','R','Y','W','I','T','H','O','U','T','E',
  'R','E','L','E','A','S','E','A','T','T','A','C','H','B','E','T','W','E',
  'E','N','O','T','H','I','N','G','R','O','U','P','S','C','A','S','C','A',
  'D','E','F','A','U','L','T','C','A','S','E','C','O','L','L','A','T','E',
  'C','R','E','A','T','E','C','U','R','R','E','N','T','_','D','A','T','E',
  'I','M','M','E','D','I','A','T','E','J','O','I','N','S','E','R','T','M',
  'A','T','C','H','P','L','A','N','A','L','Y','Z','E','P','R','A','G','M',
  'A','T','E','R','I','A','L','I','Z','E','D','E','F','E','R','R','E','D',
  'I','S','T','I','N','C','T','U','P','D','A','T','E','V','A','L','U','E',
  'S','V','I','R','T','U','A','L','W','A','Y','S','W','H','E','N','W','H',
  'E','R','E','C','U','R','S','I','V','E','A','B','O','R','T','A','F','T',
  'E','R','E','N','A','M','E','A','N','D','R','O','P','A','R','T','I','T',
  'I','O','N','A','U','T','O','I','N','C','R','E','M','E','N','T','C','A',
  'S','T','C','O','L','U','M','N','C','O','M','M','I','T','C','O','N','F',
  'L','I','C','T','C','R','O','S','S','C','U','R','R','E','N','T','_','T',
  'I','M','E','S','T','A','M','P','R','E','C','E','D','I','N','G','F','A',
  'I','L','A','S','T','F','I','L','T','E','R','E','P','L','A','C','E','F',
  'I','R','S','T','F','O','L','L','O','W','I','N','G','F','R','O','M','F',
  'U','L','L','I','M','I','T','I','F','O','R','D','E','R','E','S','T','R',
  'I','C','T','O','T','H','E','R','S','O','V','E','R','E','T','U','R','N',
  'I','N','G','R','I','G','H','T','R','O','L','L','B','A','C','K','R','O',
  'W','S','U','N','B','O','U','N','D','E','D','U','N','I','O','N','U','S',
  'I','N','G','V','A','C','U','U','M','V','I','E','W','I','N','D','O','W',
  'B','Y','I','N','I','T','I','A','L','L','Y','P','R','I','M','A','R','Y',
};

static const unsigned short int aKWOffset[148] = {
    0,    0,   2,   2,   8,   9,  14,  16,  20,  23,  25,  25,  29,  33,
    36,  41,  46,  48,  53,  54,  59,  62,  65,  67,  69,  78,  81,
    86,  90,  90,  94,  99, 101, 105, 111, 119, 123, 123, 123, 126,
   129, 132, 137, 142, 146, 147, 152, 156, 160, 168, 174, 181, 184,
   184, 187, 189, 195, 198, 206, 211, 216, 219, 222, 226, 236, 239,
   244, 244, 248, 252, 259, 265, 271, 277, 277, 283, 284, 288, 295,
   299, 306, 312, 324, 333, 335, 341, 346, 348, 355, 359, 370, 377,
   378, 385, 391, 397, 402, 408, 412, 415, 424, 429, 433, 439, 441,
   444, 453, 455, 457, 466, 470, 476, 482, 490, 495, 495, 495, 511,
   520, 523, 527, 532, 539, 544, 553, 557, 560, 565, 567, 571, 579,
   585, 588, 597, 602, 610, 610, 614, 623, 628, 633, 639, 642, 645,
   648, 650, 655, 659,
};

static const unsigned char aKWLen[148] = {0,
     7,   7,   5,   4,   6,   4,   5,   3,   6,   7,   3,   6,   6,
     7,   7,   3,   8,   2,   6,   5,   4,   4,   3,  10,   4,   7,
     6,   9,   4,   2,   6,   5,   9,   9,   4,   7,   3,   2,   4,
     4,   6,  11,   6,   2,   7,   5,   5,   9,   6,  10,   4,   6,
     2,   3,   7,   5,   9,   6,   6,   4,   5,   5,  10,   6,   5,
     7,   4,   5,   7,   6,   7,   7,   6,   5,   7,   3,   7,   4,
     7,   6,  12,   9,   4,   6,   5,   4,   7,   6,  12,   8,   8,
     2,   6,   6,   7,   6,   4,   5,   9,   5,   5,   6,   3,   4,
     9,  13,   2,   2,   4,   6,   6,   8,   5,  17,  12,   7,   9,
     4,   4,   6,   7,   5,   9,   4,   4,   5,   2,   5,   8,   6,
     4,   9,   5,   8,   4,   3,   9,   5,   5,   6,   4,   6,   2,
     2,   9,   3,   7,
};

int sqlite3_keyword_count(void);
int sqlite3_keyword_name(int i,const char **pzName,int *pnName);

int main()
{
    int totalKeyWord;
    int index,numOfBytes;
    const char *zName;
    printf("Enter the number of your keyword: ");
    scanf("%d", &index);
    

    printf("Total Keywords: %d\n", sqlite3_keyword_count());
    
    int res = sqlite3_keyword_name(index, &zName, &numOfBytes);

    if (res==1){
        char keyWord[numOfBytes];
        for(int i=0; i<numOfBytes; i++){
            keyWord[i] = zName[i];
        }
        
        printf("%dth  Keyword name: %s\n",index, keyWord);
        printf("Length of keyword name: %d\n", numOfBytes);
    }else{
        printf("Error!");
    }
}

int sqlite3_keyword_count(void)
{ 
    return SQLITE_N_KEYWORD; 
}

int sqlite3_keyword_name(int i,const char **pzName,int *pnName)
{
    if( i<0 || i>=SQLITE_N_KEYWORD ) return 0;
    i++;
    *pzName = zKWText + aKWOffset[i];
    *pnName = aKWLen[i];
    return 1;
}
