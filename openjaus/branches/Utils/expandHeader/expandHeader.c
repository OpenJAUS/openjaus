#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ignoreList[32][128] = {0};
char expandedList[512][128] = {0};
int ignoreListSize = 0;
int expandedListSize = 0;

int isFileOnIgnoreList(char *testFile)
{
	int i;

	for(i=0; i<ignoreListSize; i++)
	{
		if(strcmp(testFile, ignoreList[i])==0)
		{
			return 1;
		}
	}

	return 0;
}

int isFileOnExpandedList(char *testFile)
{
	int i;

	for(i=0; i<expandedListSize; i++)
	{
		if(strcmp(testFile, expandedList[i])==0)
		{
			return 1;
		}
	}

	return 0;
}

void expandHeader(char *exDir, char *exFileName, FILE *outfile)
{
	FILE *exFile;
	char buf[1024] = {0};
	char nextFileString[128] = {0};
	char nextFile[128] = {0};
	char nextDir[128] = {0};
	char *nextToken;
	char temp[128] = {0};

	sprintf(temp, "%s%s", exDir, exFileName);

	printf("Expanding file: %s\n", temp);

	exFile = fopen(temp, "r");
	if(!exFile)
	{
		printf("Could not open: %s\n", temp);
		return;
	}

	sprintf(expandedList[expandedListSize++], exFileName);
	
	while(fgets(buf, 1024, exFile))
	{
		if(strncmp(buf, "#include", 8))
		{
			if( !( strncmp(buf, "//", 2) && strncmp(buf, " *", 2) && strncmp(buf, "/*", 2) ) )
			{
				continue;
			}
			fputs(buf, outfile);
		}
		else
		{
			memset(nextFileString, 0, 128);
			memset(nextFile, 0, 128);
			memset(nextDir, 0, 128);
			memset(temp, 0, 128);

			if(sscanf(buf, "#include \"%[^\"]", nextFileString))
			{
				nextToken = strtok(nextFileString, "/");
			}
			else if(sscanf(buf, "#include <%[^>]", nextFileString))
			{
				nextToken = strtok(nextFileString, "/");
			}
			else
			{
				printf("Unrecognized line: %s\n", buf);
			}

			while(nextToken)
			{
				strcpy(nextFile, nextToken);

				nextToken = strtok(NULL, "/");
				
				if(nextToken)
				{
					strcat(nextDir, nextFile);
					strcat(nextDir, "/");
				}
			}
			//printf("Next Dir: %s, Next File: %s\n", nextDir, nextFile);

			if(isFileOnIgnoreList(nextFile))
			{
				printf("Not expanding: %s\n", nextFile);
				fputs(buf, outfile);
			}
			else 
			{
				if(!isFileOnExpandedList(nextFile))
				{
					sprintf(temp, "%s%s", exDir, nextDir);
					expandHeader(temp, nextFile, outfile);
				}
			}
		}
	}

	fclose(exFile);
}

void main(void)
{
	FILE *outfile;

	sprintf(ignoreList[ignoreListSize++], "time.h");
	sprintf(ignoreList[ignoreListSize++], "string.h");
	sprintf(ignoreList[ignoreListSize++], "stdio.h");

	outfile = fopen("test.txt", "w");

	expandHeader("include/", "jaus.h", outfile);

	fclose(outfile);

	system("pause");
}

