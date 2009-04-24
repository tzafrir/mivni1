/***************************************************************************/
/*                                                                         */
/* 234218 Data DSs 1, Spring 2009                                          */
/*                                                                         */
/* Homework : Wet 1                                                        */
/*                                                                         */
/***************************************************************************/

/***************************************************************************/
/*                                                                         */
/* File Name : main1.cpp                                                   */
/*                                                                         */
/* Holds the "int main()" function and the parser of the shell's           */
/* command line.                                                           */
/***************************************************************************/


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "library1.h"

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif




/* The command's strings */
typedef enum {
  NONE_CMD = -2,
  COMMENT_CMD = -1,
  INIT_CMD = 0,
  CHANGEBUDGET_CMD = 1,
  ADDBAND_CMD = 2,
  REMOVEBAND_CMD = 3,
  ADDVOTES_CMD = 4,
  CHANGEPRICE_CMD = 5,
  CHANGEALLPRICES_CMD = 6,
  GETPRICE_CMD = 7,
  MAXNEEDEDBUDGET_CMD = 8,
  BANDLIST_CMD = 9,
  QUIT_CMD = 10
} commandType;



static const int   numActions   = 11;
static const char *commandStr[] = {
  "Init",
  "ChangeBudget",
  "AddBand",
  "RemoveBand",
  "AddVotes",
  "ChangePrice",
  "ChangeAllPrices",
  "GetPrice",
  "MaxNeededBudget",
  "BandList",
  "Quit"
};


static const char* ReturnValToStr(int val) {
	switch (val) {
		case (SUCCESS):          return "Success";
		case (FAILURE):          return "Failure";
		case (INVALID_INPUT):    return "Invalid_input";
		case (ALLOCATION_ERROR): return "Allocation_error";
		default:                 return "";
	}
}
	





/* we assume maximum string size is not longer than 256  */
#define MAX_STRING_INPUT_SIZE (255)
#define MAX_BUFFER_SIZE       (255)

#define StrCmp(Src1,Src2) ( strncmp((Src1),(Src2),strlen(Src1)) == 0 )

typedef enum {error_free, error} errorType;
static errorType parser(const char* const command);



#define ValidateRead(read_parameters,required_parameters,ErrorString) \
if ( (read_parameters)!=(required_parameters) ) { printf(ErrorString); return error; }


static bool isInit = false;


/* Print an array */
string PrintIntArray(const int* arr, int size) {
	char buffer[MAX_BUFFER_SIZE];
	string str = "";

	for (int i=0; i < size; i++) {
		sprintf(buffer,"%d",arr[i]);
		str += string(buffer) + ((i == (size - 1)) ? "" : ",");
	}
	return str.c_str();
}




/***************************************************************************/
/* main                                                                    */
/***************************************************************************/

int main(int argc, const char**argv) {
  char buffer[MAX_STRING_INPUT_SIZE];
  // Reading commands
  while ( fgets(buffer, MAX_STRING_INPUT_SIZE, stdin) != NULL ) {
    fflush(stdout); 
    if ( parser(buffer) == error )
      break;
  };
  return 0;
};

/***************************************************************************/
/* Command Checker                                                         */
/***************************************************************************/

static commandType CheckCommand(const char* const command, const char** const command_arg) {
  if ( command == NULL || strlen(command) == 0 || StrCmp("\n", command) )
    return(NONE_CMD);
  if ( StrCmp("#", command) ) {
    if (strlen(command) > 1)
      printf("%s", command);
    return(COMMENT_CMD);
  };
  for (int index=0; index < numActions; index++) {
    if ( StrCmp(commandStr[index], command) ) {
      *command_arg = command + strlen(commandStr[index]) + 1;
      return((commandType)index);
    };
  };
  return(NONE_CMD);
};

/***************************************************************************/
/* Commands Functions                                                      */
/***************************************************************************/

static errorType OnInit(void** DS, const char* const command);
static errorType OnChangeBudget(void* DS, const char* const command);
static errorType OnAddBand(void* DS, const char* const command);
static errorType OnRemoveBand(void* DS, const char* const command);
static errorType OnAddVotes(void* DS, const char* const command);
static errorType OnChangePrice(void* DS, const char* const command);
static errorType OnChangeAllPrices(void* DS, const char* const command);
static errorType OnGetPrice(void* DS, const char* const command);
static errorType OnMaxNeededBudget(void* DS, const char* const command);
static errorType OnBandList(void* DS, const char* const command);
static errorType OnQuit(void** DS, const char* const command);




/***************************************************************************/
/* Parser                                                                  */
/***************************************************************************/

static errorType parser(const char* const command) { 
  static void *DS = NULL; /* The general data structure */
  const char* command_args = NULL;
  errorType rtn_val = error;

  commandType command_val = CheckCommand(command, &command_args);
 
  switch (command_val) {

	case (INIT_CMD):                   rtn_val = OnInit(&DS, command_args);	break;
	case (CHANGEBUDGET_CMD):           rtn_val = OnChangeBudget(DS, command_args);	break;
	case (ADDBAND_CMD):                rtn_val = OnAddBand(DS, command_args);	break;
	case (REMOVEBAND_CMD):             rtn_val = OnRemoveBand(DS, command_args);	break;
	case (ADDVOTES_CMD):               rtn_val = OnAddVotes(DS, command_args);	break;
	case (CHANGEPRICE_CMD):            rtn_val = OnChangePrice(DS, command_args);	break;
	case (CHANGEALLPRICES_CMD):        rtn_val = OnChangeAllPrices(DS, command_args);	break;
	case (GETPRICE_CMD):               rtn_val = OnGetPrice(DS, command_args);	break;
	case (MAXNEEDEDBUDGET_CMD):        rtn_val = OnMaxNeededBudget(DS, command_args);	break;
	case (BANDLIST_CMD):               rtn_val = OnBandList(DS, command_args);	break;
	case (QUIT_CMD):                   rtn_val = OnQuit(&DS, command_args);	break;
	
	case (COMMENT_CMD):                rtn_val = error_free;	break;
	case (NONE_CMD):                   rtn_val = error;	break;
	default: assert(false);
  };
  return(rtn_val);
};





/***************************************************************************/
/* OnInit                                                                  */
/***************************************************************************/
static errorType OnInit(void** DS, const char* const command) {
	if(isInit) {
		printf("Init was already called.\n");
		return(error_free);
	};
	isInit = true;

	int	budget;	
	ValidateRead( sscanf(command, "%d" ,&budget), 1, "Init failed.\n" );
		
	*DS = Init(budget);
	if( *DS == NULL ) {
		printf("Init failed.\n");
		return(error);
	};
	printf("Init done.\n");

	return error_free;
}


/***************************************************************************/
/* OnChangeBudget                                                          */
/***************************************************************************/
static errorType OnChangeBudget(void* DS, const char* const command) {
	int budget;
	ValidateRead( sscanf(command, "%d",&budget), 1, "ChangeBudget failed.\n" );
	StatusType res = ChangeBudget(DS,budget);

	printf("ChangeBudget: %s\n", ReturnValToStr(res));

	return error_free;
}


/***************************************************************************/
/* OnAddBand                                                               */
/***************************************************************************/
static errorType OnAddBand(void* DS, const char* const command) {
	int bandID;
	int price;
	ValidateRead( sscanf(command, "%d %d",&bandID,&price), 2, "AddBand failed.\n" );
	StatusType res = AddBand(DS,bandID,price);

	printf("AddBand: %s\n", ReturnValToStr(res));

	return error_free;
}


/***************************************************************************/
/* OnRemoveBand                                                            */
/***************************************************************************/
static errorType OnRemoveBand(void* DS, const char* const command) {
	int bandID;
	ValidateRead( sscanf(command, "%d",&bandID), 1, "RemoveBand failed.\n" );
	StatusType res = RemoveBand(DS,bandID);

	printf("RemoveBand: %s\n", ReturnValToStr(res));

	return error_free;
}


/***************************************************************************/
/* OnAddVotes                                                              */
/***************************************************************************/
static errorType OnAddVotes(void* DS, const char* const command) {
	int bandID;
	int numVotes;
	ValidateRead( sscanf(command, "%d %d",&bandID,&numVotes), 2, "AddVotes failed.\n" );
	StatusType res = AddVotes(DS,bandID,numVotes);
	
	printf("AddVotes: %s\n", ReturnValToStr(res));

	return error_free;
}


/***************************************************************************/
/* OnChangePrice                                                           */
/***************************************************************************/
static errorType OnChangePrice(void* DS, const char* const command) {
	int bandID;
	int price;
	ValidateRead( sscanf(command, "%d %d",&bandID,&price), 2, "ChangePrice failed.\n" );
	StatusType res = ChangePrice(DS,bandID,price);

	printf("ChangePrice: %s\n", ReturnValToStr(res));

	return error_free;
}


/***************************************************************************/
/* OnChangeAllPrices                                                       */
/***************************************************************************/
static errorType OnChangeAllPrices(void* DS, const char* const command) {
	int discount;
	ValidateRead( sscanf(command, "%d",&discount), 1, "ChangeAllPrices failed.\n" );
	StatusType res = ChangeAllPrices(DS,discount);
	
	printf("ChangeAllPrices: %s\n", ReturnValToStr(res));

	return error_free;
}


/***************************************************************************/
/* OnGetPrice                                                              */
/***************************************************************************/
static errorType OnGetPrice(void* DS, const char* const command) {
	int bandID;
	ValidateRead( sscanf(command, "%d",&bandID), 1, "GetPrice failed.\n" );
	int	price;
	StatusType res = GetPrice(DS,bandID,&price);
	
	if (res != SUCCESS) {
		printf("GetPrice: %s\n",ReturnValToStr(res));
	}
	else {
		printf("GetPrice: %s %d\n", ReturnValToStr(res),price);
	}

	return error_free;
}


/***************************************************************************/
/* OnMaxNeededBudget                                                       */
/***************************************************************************/
static errorType OnMaxNeededBudget(void* DS, const char* const command) {
	int	maxBudget;
	StatusType res = MaxNeededBudget(DS,&maxBudget);
	
	if (res != SUCCESS) {
		printf("MaxNeededBudget: %s\n",ReturnValToStr(res));
	}
	else {
		printf("MaxNeededBudget: %s %d\n", ReturnValToStr(res),maxBudget);
	}

	return error_free;
}


/***************************************************************************/
/* OnBandList                                                              */
/***************************************************************************/
static errorType OnBandList(void* DS, const char* const command) {
	int*	bandList;
	int	size;
	StatusType res = BandList(DS,&bandList,&size);
	
	if (res != SUCCESS) {
		printf("BandList: %s\n",ReturnValToStr(res));
	}
	else {
		printf("BandList: %s %s %d\n", ReturnValToStr(res),PrintIntArray(bandList,size).c_str(),size);
	}

	free(bandList);
	return error_free;
}


/***************************************************************************/
/* OnQuit                                                                  */
/***************************************************************************/
static errorType OnQuit(void** DS, const char* const command) {
	Quit(DS);
	if( *DS != NULL ) {
		printf("Quit failed.\n");
		return(error);
	};
	isInit = false;
	printf("Quit done.\n");

	return error_free;
}




#ifdef __cplusplus
}
#endif


