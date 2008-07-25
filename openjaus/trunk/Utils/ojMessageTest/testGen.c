#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	FILE *outfile;
	FILE *inFile;
	char buf[1024] = {0};
	char *token;
	char *messageType[1000] = {NULL};
	char *messageName[1000] = {NULL};
	char *prepackCode[1000] = {NULL};
	char *postpackCheck[1000] = {NULL};
	int i = 0;
	int messageCount = 0;

	inFile = fopen("MessageList.csv", "r");
	if(!inFile)
	{
		printf("Could not open: MessageList.csv\n");
		return;
	}

	outfile = fopen("messageTest.c", "w");
	
	fprintf(outfile, "#include <stdio.h>\n");
	fprintf(outfile, "#include <stdlib.h>\n");
	fprintf(outfile, "#include <jaus.h>\n\n");
	fprintf(outfile, "int main(void)\n");
	fprintf(outfile, "{\n");
	fprintf(outfile, "\tJausMessage jausMessage;\n");

	// Pull off header row
	fgets(buf, 1024, inFile);

	while(fgets(buf, 1024, inFile))
	{
		token =  strtok(buf, ",");
		messageType[i] = (char *)malloc(strlen(token) + 1); 
		strcpy(messageType[i], token);

		token =  strtok(NULL, ",");
		messageName[i] = (char *)malloc(strlen(token) + 1); 
		strcpy(messageName[i], token);

		token =  strtok(NULL, ",");
		prepackCode[i] = (char *)malloc(strlen(token) + 1); 
		strcpy(prepackCode[i], token);

		token =  strtok(NULL, ",");
		postpackCheck[i] = (char *)malloc(strlen(token) + 1); 
		strcpy(postpackCheck[i], token);

		fprintf(outfile, "\t%s %s1;\n", messageType[i], messageName[i]);
		fprintf(outfile, "\t%s %s2;\n", messageType[i], messageName[i]);

		i++;
	}
	messageCount = i;

	for(i=0; i<messageCount; i++)
	{
		fprintf(outfile, "\n\tprintf(\"Testing %s\\n\");\n", messageType[i]);
		fprintf(outfile, "\t%s1 = %sCreate();\n", messageName[i], messageName[i]);
		fprintf(outfile, "\tjausMessage = %sToJausMessage(%s1);\n", messageName[i], messageName[i]);
		fprintf(outfile, "\tif(%s)\n", postpackCheck[i]);
		fprintf(outfile, "\t{\n");
		fprintf(outfile, "\t\tprintf(\"\\t%sToJausMessage failed\\n\");\n", messageName[i]);
		fprintf(outfile, "\t}\n");
		fprintf(outfile, "\telse\n");
		fprintf(outfile, "\t{\n");
		fprintf(outfile, "\t\t%s2 = %sFromJausMessage(jausMessage);\n", messageName[i], messageName[i]);
		fprintf(outfile, "\t\tif(%s2 == NULL)\n", messageName[i]);
		fprintf(outfile, "\t\t{\n");
		fprintf(outfile, "\t\t\tprintf(\"\\t%sFromJausMessage failed\\n\");\n", messageName[i]);
		fprintf(outfile, "\t\t}\n");
		fprintf(outfile, "\t\telse\n");
		fprintf(outfile, "\t\t{\n");
		fprintf(outfile, "\t\t\t%sDestroy(%s2);\n", messageName[i], messageName[i]);
		fprintf(outfile, "\t\t}\n");
		fprintf(outfile, "\t}\n");
		fprintf(outfile, "\t%sDestroy(%s1);\n", messageName[i], messageName[i]);
		fprintf(outfile, "\tjausMessageDestroy(jausMessage);\n");
	}

	fprintf(outfile, "\n\treturn 0;\n");
	fprintf(outfile, "}\n");

	fclose(outfile);
	
	return 0;
}

