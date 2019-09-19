#include <cstdio>
#include "cJSON.h"

const char* jsonstr = "{ \"r\" : {\"r1\":1, \"r2\":2} , \"a\":\"a1\", \"b\": [ {\"b11\":\"b11v\", \"b12\":\"b12v\", \"b13\":\"b13v\"} , {\"b21\":\"b21v\", \"b22\":\"b22v\", \"b23\":\"b23v\"}]}";

void paresJson(cJSON* j, char* s)
{
	cJSON* jsobj = NULL;
	if (j)
	{
		jsobj = j;
	}
	else
	{
		if (s)
		{
			jsobj = cJSON_Parse(s);
		}
	}
	
	while (jsobj)
	{
		int t = jsobj->type;
		switch (t)
		{
			case cJSON_Number:
			{
				printf("json: type:cJSON_Number , value:%d\n", jsobj->valueint);
			}
			break;
		case cJSON_String:
		case cJSON_Raw:
			{
				printf("json: type:cJSON_String , value:%s\n", jsobj->valuestring);
			}
			break;
		case cJSON_Object:
		case cJSON_Array:
			{
				printf("json: type:cJSON_Object %s----- \n", jsobj->string);
				paresJson(jsobj->child, NULL);
				
			}
			break;
		default:
			printf("json: type:others \n");
			break;
		}
		jsobj = jsobj->next;
	}
}

int main()
{
//	paresJson(NULL, (char *)jsonstr);

	cJSON* j = cJSON_Parse((char*)jsonstr);
	cJSON* jo = cJSON_GetObjectItem(j, "r");
	cJSON* s = cJSON_CreateString("ss");
	cJSON_AddItemToObject(jo, "ns", s);
	cJSON_AddItemToObject(jo, "ns2", s);

	char* dump = cJSON_Print(j);
	
	printf(dump);
	printf("\n");
	printf("process exit\n");

	getchar();
	return 0;
}