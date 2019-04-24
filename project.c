#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DEFAULTFILENAME "data.txt"

void shuffle(int *array, size_t n);
void generateVotes(int c, int v, const char *fileName);

void initializeArray(int *result, int siz);
void electionProcess(int *votes, int c, int *result);
void readInitialization(const char *fileName,int *c,int *v);

bool* whoIsM3ana;
void shuffle(int *array, size_t n)
{
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

void generateVotes(int c, int v, const char *fileName)
{
    FILE *fp = fopen(fileName, "w");
    fprintf(fp,"%d\n",c);
    fprintf(fp,"%d\n",v);

    int* vote = malloc(c*sizeof(int));
    int i;

    for(i=0;i<c;i++)
    {
        vote[i] = i+1;
    }
    while(v--)
    {
        shuffle(vote,c);
        fprintf(fp,"%d",vote[0]);
        for(i=1;i<c;i++)
        {
            fprintf(fp," %d",vote[i]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}

void initializeArray(int *result, int siz)
{
    int i;
    for(i=0;i<siz;i++)
        result[i]=0;
}

void initializeArrayTrue(bool *result, int siz)
{
    int i;
    for(i=0;i<siz;i++)
        result[i]=true;
}

void electionProcess(int *vote,int c, int *result)
{
    int cCounter, voteTo;
//    for(vCounter=0; vCounter<v; vCounter++)
//    {
        for(cCounter=0;cCounter<c;cCounter++)
        {
            if(whoIsM3ana[vote[cCounter]-1])
            {
                voteTo = vote[cCounter] - 1;
                break;
            }
        }
        result[voteTo] += 1;
//    }
}

void readInitialization(const char *fileName,int *c,int *v)
{
    FILE *fp = fopen(fileName, "r");
    fscanf(fp,"%d\n%d\n", c, v);
    fclose(fp);
}

int getRecordSize(const char *fileName, int startByteOfRecord)
{
    static long lineSize = -1;
    if(lineSize != -1)
        return lineSize;

    FILE *fp = fopen(fileName, "r");
    // calculating the line size
    char line[256];
    fseek(fp,startByteOfRecord,0);
    fgets(line, sizeof line, fp);
    lineSize = strlen(line) + 1; // 1 is the \n character
    fclose(fp);
    return lineSize;
}

int countLength(int e)
{
    if(e == 0)
        return 1;

    int counter = 0;
    while(e > 0)
    {
        e /= 10;
        counter++;
    }
    return counter;
}
int calcStartByte(const char *fileName)
{
    static int start = -1;
    if(start != -1)
        return start;


    FILE *fp = fopen(fileName, "r");
    char line[256];
    fgets(line, sizeof line, fp);
    char lineTwo[256];
    fgets(lineTwo, sizeof lineTwo, fp);
    start = ftell(fp);
    fclose(fp);
    return start;
}
void readRecord(const char *fileName, int recordIndex,int c, int v,int *vote)
{
    int startByteOfRecord = calcStartByte(fileName);

    // calculating the line size
    int lineSize = getRecordSize(fileName, startByteOfRecord);

    // seek to the line required
    long firstByteInRecord = startByteOfRecord + lineSize * recordIndex;

    FILE *fp = fopen(fileName, "r");
    fseek(fp,firstByteInRecord,0);

    // read that line
    int i;
    fscanf(fp,"%d",&vote[0]);
    for(i=1;i<c;i++)
    {
        fscanf(fp," %d",&vote[i]);
    }
    fclose(fp);
}

void printArray(int* arr, int siz)
{
    int i;
    for(i=0 ;i<siz;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}


int main()
{
    int c = 5 , v, option, partition = 3, i;
    char fileName[256];

    printf("0 = generate\n1 = read from file\nanyNumber = exit\n$ ");
    scanf("%d",&option);
    switch(option)
    {
    case 0:
        printf("Enter # of candidates and # of voters like 'c v': $ ");
        scanf("%d %d",&c,&v);
        generateVotes(c,v,DEFAULTFILENAME);
        break;
    case 1:
        printf("Enter File Name: $ ");
        scanf("%s",fileName);
        readInitialization(fileName, &c, &v);
        break;
    default:
        return 0;
    }
    printf("\n%d %d\n", c, v);

    int *vote   = malloc(c*sizeof(int));
    int *result = malloc(c * sizeof(int));
    whoIsM3ana  = malloc(c * sizeof(bool));
    initializeArray(result,c);
    initializeArrayTrue(whoIsM3ana,c);

    whoIsM3ana[2] = false;

    for(i=0 ;i<c;i++)
    {
        printf("%s ", whoIsM3ana[i] ? "true" : "false");
    }

    printf("\n");
    printf("\n");

    readRecord(DEFAULTFILENAME, 0 , c, v, vote);

    printf("Vote #%d: ",0);
    printArray(vote,c);

    electionProcess(vote,c,result);

    printf("Result: ");

    printArray(result,c);

    printf("\n");

    readRecord(DEFAULTFILENAME, 1 , c, v, vote);
    printf("Vote #%d: ",1);
    printArray(vote,c);

    electionProcess(vote,c,result);
    electionProcess(vote,c,result);
    printf("Result: ",0);
    printArray(result,c);
    printf("\n");
    printf("\n");


    /** A simple main for the reading operation in the beginning

    **/

    /**
        logic function
            - election function electionProcess(votes, c, *result);
            // c is number of candidates and v is number of votes in the votes send
            - file operations 35 mins
                = readInitialization(fileName, *c, *v)
                = generateVotes(c, v, fileName) (random)
                = readRecord(startVoteNumber, recordIndex, c, *vote): vote[c]


        parallel process
            - divide to processes
            - sum the result

    **/

    /// ask for read or generate

    /// read the initialize ones (C,V)

    /// declare the arrays needed with c,v and calculate partitions and the reminder

    /**
        the master process will send for each process the partition range it will work for

        we should have an array of booleans called whoIsM3ana[] describes which one is still m3ana or left (true = m3ana, false = me4M3ana)
        initial all of them are true

        each process should do the following:
            - read its partition
            - electing the first round
                you should have a function called
                electionProcess(votes)
                {
                    for each vote
                        loop on it to the first one who is m3ana
                }

        master sum all the results to one and select the winner (more than 50%) or go to the next round
            if we went to the next round
                we should update the array whoIsM3ana[] with how is still m3ana and who is not
                nextRoundCounterArray[2] counters for the next two candidates

                each process should do the following:
                    - if the read is gone read it again
                    - electing the second round (call the electionProcess function )
                    you should have a function called
                    electionProcess(votes)
                    {
                        for each vote
                            loop on it to the first one who is m3ana
                    }

                master sum all the results to one and select the winner and output it

    **/
    return 0;
}
