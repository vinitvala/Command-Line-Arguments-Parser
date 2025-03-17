#include "hw6.h"

int main(int argc, char *argv[]) {
	
	// For using getopt
	extern char *optarg;
	extern int optind;

	if(argc < 7)
		return MISSING_ARGUMENT; 

	char *search_text = NULL;
	char *replace_text = NULL;
	bool wildcard_enabled = false;
	long start_line = -1;
	long end_line = -1;
	char *infile = argv[argc - 2];
	char *outfile = argv[argc - 1];

	FILE *in = fopen(infile, "r");
	if(in == NULL)
		return INPUT_FILE_MISSING;

	FILE *out = fopen(outfile, "w");
	if(out == NULL)
	{
		fclose(in);
		return OUTPUT_FILE_UNWRITABLE;
	}

	char i;
	while(optind < argc - 2 && (i = getopt(argc, argv, "s:r:wl:")) != -1)
	{
		switch(i)
		{
			case 's':
			{
				if(search_text != NULL)
					return DUPLICATE_ARGUMENT;

				search_text = optarg;
				if(search_text[0] == '-')
					return S_ARGUMENT_MISSING;

				break;
			}
			case 'r':
			{
				if(replace_text != NULL)
					return DUPLICATE_ARGUMENT;

				replace_text = optarg;
				if(replace_text[0] == '-')
					return R_ARGUMENT_MISSING;

				break;
			}
			case 'w':
			{
				if(wildcard_enabled)
					return DUPLICATE_ARGUMENT;

				wildcard_enabled = true;
				break;
			}
			case 'l':
			{
				if(start_line != -1 || end_line != -1)
					return DUPLICATE_ARGUMENT;

				if(optarg[0] == '-')
					return L_ARGUMENT_INVALID;

				char *ptr;
				char *param = strtok(optarg, ",");

				if(param == NULL)
					return L_ARGUMENT_INVALID;

				start_line = strtol(param, &ptr, 10);

				param = strtok(NULL, ",");
				if(param == NULL)
					return L_ARGUMENT_INVALID;

				end_line = strtol(param, &ptr, 10);

				if(start_line * end_line == 0 || start_line > end_line)
					return L_ARGUMENT_INVALID;

				break;
			}
		}
	}

	if(search_text == NULL)
		return S_ARGUMENT_MISSING;

	if(replace_text == NULL)
		return R_ARGUMENT_MISSING;

	bool prefix = false;
	if(wildcard_enabled)
	{
		if(search_text[0] == '*' && search_text[strlen(search_text) - 1] == '*')
			return WILDCARD_INVALID;

		if(search_text[0] == '*')
		{
			prefix = false;
			search_text++;
		}
		else if(search_text[strlen(search_text) - 1] == '*')
		{
			prefix = true;
			search_text[strlen(search_text) - 1] = '\0';
		}
		else
			return WILDCARD_INVALID;
	}

	char line[MAX_LINE + 1];
	int l = 1;
	while(fgets(line, MAX_LINE + 1, in) != NULL)
	{
		if((l >= start_line && l <= end_line) || (start_line == -1 && end_line == -1))
		{
			char *search;
			char *temp = line;
			while((search = strstr(temp, search_text)) != NULL)
			{
				int s_len = strlen(search_text);
				if(wildcard_enabled)
				{
					if(prefix)
					{
						char *c = search - 1;
						if(search - line == 0 || isspace(*c) || ispunct(*c))
						{
							while(!isspace(search[s_len]) && !ispunct(search[s_len]) && search[s_len] != '\n' && search[s_len] != '\0')
								s_len++;
						}
						else
						{
							temp = search + s_len;
							continue;
						}
					}
					else
					{
						if(isspace(search[s_len]) || ispunct(search[s_len]) || search[s_len] == '\n' || search[s_len] == '\0')
						{
							char *c = search - 1;
							while(search - line != 0 && !isspace(*c) && !ispunct(*c))
							{
								search--;
								s_len++;
								c = search - 1;
							}
						}
						else
						{
							temp = search + s_len;
							continue;
						}
					}
				}

				char rest[MAX_LINE + 1];
				strcpy(rest, &search[s_len]);
				strcpy(search, replace_text);
				strcpy(&search[strlen(replace_text)], rest);
				temp = search + strlen(replace_text);
			}
		}

		fputs(line, out);
		l++;
	}

    return 0;
}
