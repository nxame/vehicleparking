/*===============================================

  Developed by: Shekhar K. Sharma
                hello@shekhardesigner.com
                https://shekhar.net.np/

                CPG102 / 'C' Programming.
                Term 3, 2011. Final Project
                Informatics College, Kamalpokhari, Kathmandu, Nepal
                https://islington.edu.np/

                Project on:
                Vehicle Parking System

                Instructor: Prakash Shrestha

  ===============================================*/

/*===|================================================
  Table Of Content
  ---------------------------------------------------

  Line no.  Contents
  ---------------------------------------------------
    59.     System source build includes.
    68.     System variables
    83.     Functions prototypes
    113     Functions
    156     generic function to get error free single word (strings) from user.
    218     generic function to get error free words from user.
    281     generic function to get error free integers from user.
    343     eneric function to get error free passowrd from user  and showing * except real characters..
    405     function to get Y or N value
    422     creating splash screen footer.
    441     Creating Splash Screen
    498     creating inner header for rest of screen except splash.
    509     Creating user authentication system
    578     Generating the system's main menu.
    656     Printing system date, in American format.
    715     getting system curr time
    731     vehicle structure.
    745     new and unique key generation, automatically.
    769     Creating a form to get the vehicle data from user & store it.
    892     Two wheeler vehicle addtion gateway function.
    916     Four wheeler vehicle addtion gateway function.
    940     Vehicle search & release system & processigns
    1116    Calculating the applicable charge.
    1131    Generating the full report.
    1242    System termination processing function
    1304    All in one  Running the application.
  ===|==============================================*/




/*===|================================================
  System source build includes.
  ===|==============================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "conio_compat.h"
#include "datapath.h"

/*===|================================================
  System variables
  ===|==============================================*/
int i;
char esc;
char username[30];
char password[30];
int loggedIn = 0;
char menuKey;
char exitKey;
int invoiceNo;
int twoWheelerCharge = 10;
int fourWheelerCharge = 30;
FILE *fl;

/*===|================================================
  Functions prototypes
  ===|==============================================*/
void  createVertLines(int, int, int);
void  createHorzLines(int, int, int,char);
void  splashScreen();
void  createFooter(int);
void  innerHeader();
void  authenticateUsers();
void  scanString(char *);
void  scanWords(char *);
int   scanInt();
void  scanPassword(char *);
char  getYN();
void  systemMenu();
void  date();
float currTime();
float hour;
float mins;
int   autoKeyGenerate();
int   addVehicleForm(int);
void  addTwoWheelers();
void  addFourWheelers();
void  searchVehicle();
float calculateCharge(float,float,int);
void  generateReport();
void  exitApp();



/*===|================================================
  Functions
  ===|==============================================*/

void createVertLines(int min, int max, int x){
	for(i=min; i<=max; i++){
		gotoxy(x,i);
		cprintf("%c",186);
	}
}

void createHorzLines(int min, int max, int y, char pos){
	for(i=min; i<=max; i++){
		gotoxy(i, y);
		if(i==min){
			if(pos=='T'){
				cprintf("%c",201);
			}
			else if(pos=='B'){
				cprintf("%c",200);
			}
			else if(pos=='M'){
				cprintf("%c", 204);
			}

		}
		else if(i==max){
			if(pos=='T'){
				cprintf("%c", 187);
			}
			else if(pos=='B'){
				cprintf("%c",188);
			}
			else if(pos=='M'){
				cprintf("%c", 185);
			}
		}
		else{
			cprintf("%c",205);
		}
	}
}

/*===|================================================
  generic function to get error free single word (strings) from user.
  ===|==============================================*/
void scanString(char *input)
{
	char inputStr[50];
	char userinput;
	int i=0;
	int flag=0;

	do
	{
		userinput=getch();

		if(userinput==27)	// if escape key is pressed
		{
			flag=1;
			exitApp();
		}
		else if((userinput==13 || userinput==9) && i>0)
		{
			flag=1;
			break;
		}
		else if(userinput==8 && i>0)
		{
			cprintf("%c",8);
			cprintf("%c",32);
			cprintf("%c",8);
			i--;
		}
		else
		{
			if(userinput!=8 && i<20 && ((userinput>=65 && userinput<=90) || (userinput>=97 && userinput<=122)))
			{
				textbackground(WHITE);
				textcolor(BLUE);
				cprintf("%c",userinput);
				textbackground(CYAN);
				textcolor(WHITE);
				inputStr[i]=userinput;
				i++;
			}
		}
	}while(1);

	inputStr[i]='\0';

	if(flag!=1)
	{

		gotoxy(16,22);
		cprintf("Characters exceeded the limit of 20.");
		getch();
	}
	else
	{

		strcpy(input,inputStr);
	}
}

/*===|================================================
  generic function to get error free words from user.
  ===|==============================================*/
void scanWords(char *input)
{
	char inputStr[50];
	char userinput;
	int i=0;
	int flag=0;

	do
	{
		userinput=getch();

		if(userinput==27)	// if escape key is pressed
		{
			flag=1;
			systemMenu();
		}
		else if(userinput==13 && i>0) //if enter key is pressed
		{
			flag=1;
			break;
		}
		else if(userinput==8 && i>0)
		{
			cprintf("%c",8);
			cprintf("%c",32);
			cprintf("%c",8);
			i--;
		}
		else
		{
			if(userinput!=8 && i<20 && ((userinput>=65 && userinput<=90) || (userinput>=97 && userinput<=122) || (userinput==32) || (userinput>=48 && userinput<=57)))
			{
				textbackground(WHITE);
				textcolor(BLUE);
				cprintf("%c",userinput);
				textbackground(CYAN);
				textcolor(WHITE);
				inputStr[i]=userinput;
				i++;
			}
		}
	}while(1);

	inputStr[i]='\0';

	if(flag!=1)
	{

		gotoxy(16,22);
		cprintf("Characters exceeded the limit of 20.");
		getch();
	}
	else
	{

		strcpy(input,inputStr);
	}
}


/*===|================================================
  generic function to get error free integers from user.
  ===|==============================================*/
int scanInt()
{
	char inputStr[50];
	char userinput;
	int i=0;
	int flag=0;


	do
	{
		userinput=getch();

		if(userinput==27)	// if escape key is pressed
		{
			systemMenu();
		}
		else if(userinput==13 && i>0) //if enter key is pressed
		{
			flag=1;
			break;
		}
		else if(userinput==8 && i>0)
		{
			cprintf("%c",8);
			cprintf("%c",32);
			cprintf("%c",8);
			i--;
		}
		else
		{
			if(userinput!=8 && i<20 && (userinput>=48 && userinput<=57))
			{
				textbackground(WHITE);
				textcolor(BLUE);
				cprintf("%c",userinput);
				textbackground(CYAN);
				textcolor(WHITE);
				inputStr[i]=userinput;
				i++;
			}
		}
	}while(1);

	inputStr[i]='\0';

	if(flag!=1)
	{

		gotoxy(1,1);
		cprintf("Not a valid number!");
		exit(0);
	}
	else
	{
		return atoi(inputStr); /* Alpha to Integer conversion.  */
	}
}


/*===|================================================
  eneric function to get error free passowrd from user
  and showing * except real characters..
  ===|==============================================*/
void scanPassword(char *input)
{
	char inputStr[50];
	char userinput;
	int i=0;
	int flag=0;


	do
	{
		userinput=getch();

		if(userinput==27)	// if escape key is pressed
		{
			flag=1;
			break;
		}
		else if((userinput==13 || userinput==9) && i>0) //if enter key is pressed
		{
			flag=1;
			break;
		}
		else if(userinput==8 && i>0)
		{
			cprintf("%c",8);
			cprintf("%c",32);
			cprintf("%c",8);
			i--;
		}
		else if(i<20)
		{
			textbackground(WHITE);
			textcolor(BLUE);
			cprintf("*");
			textbackground(CYAN);
			textcolor(WHITE);
			inputStr[i]=userinput;
			i++;
		}
	}while(1);

	inputStr[i]='\0';

	if(flag!=1)
	{

		gotoxy(16,22);
		cprintf("Something went wrong. Please try again!");
		getch();
		exitApp();
	}
	else
	{

		strcpy(input,inputStr);
	}
}

/*===|================================================
  function to get Y or N value
  ===|==============================================*/
char getYN()
{
	char input;
	do{
		fflush(stdin);

		input=getch();

	}while(input!='y' && input!='Y' && input!='n' && input!='N');
	cprintf("%c",input);

	return input;
}

/*===|================================================
  creating splash screen footer.
  ===|==============================================*/
void createFooter(int y){
	textcolor(WHITE);
	createHorzLines(11,69,y,'M');
	gotoxy(13,(y+1));
	cprintf("Licensed to Shekhar K. Sharma");
	gotoxy(13,y+2);
	cprintf("(c) 2011, All rights reserved by the developer.");
	gotoxy(13,y+3);
	cprintf("Developed by: Shekhar K. Sharma");
	gotoxy(27,y+4);
	cprintf("CPG102, 'C' Project");
	createHorzLines(11,69,(y+5),'B');


}

/*===|================================================
  Creating Splash Screen
  ===|==============================================*/
void splashScreen(){

	clrscr();

	//creating first line
	createHorzLines(11,69,2, 'T');

	//Screen verticle lines
	createVertLines(3, 23, 11);
	createVertLines(3, 23, 69);

	//creating logo
	gotoxy(35,7);
	cprintf("%c%c%c %c %c  %c ",219,219,219,219,219,219);
	gotoxy(35,8);
	cprintf("%c %c  %c  %c%c%c",219,219,219,219,219,219);
	gotoxy(35,9);
	cprintf("%c %c %c %c %c %c",219,219,219,219,219,219);

	gotoxy(29,11);
	cprintf("Vehicle Parking System.");

	//printing footer.
	createFooter(19);

	//showing apps loading
	gotoxy(15,14);
	textcolor(RED);
	cprintf("LOADING");

	delay(500);
	gotoxy(23,14);
	cprintf(".");
	delay(500);
	gotoxy(24,14);
	cprintf(".");
	delay(500);
	gotoxy(25,14);
	cprintf(".");
	delay(500);
	gotoxy(26,14);
	cprintf(".");
	delay(500);
	gotoxy(27,14);
	cprintf(".");


	textcolor(WHITE);
	_setcursortype(_NOCURSOR);
	delay(500);
	gotoxy(15,14);
	cprintf("             ");
	gotoxy(15,14);
	cprintf("Press <ENTER> to login.");
	while(getch()!=13);

}

/*===|================================================
  creating inner header for rest of screen except splash.
  ===|==============================================*/
void innerHeader(){

	gotoxy(33,3);
	cprintf("PARKING SYSTEM");
	gotoxy(12,4);
	createHorzLines(11,69,4,'M');
}

/*===|================================================
  Creating user authentication system
  ===|==============================================*/
void authenticateUsers(){
	_setcursortype(_SOLIDCURSOR);
	clrscr();
	//creating box boundary lines
	createHorzLines(11,69,2, 'T');
	createVertLines(3, 23, 11);
	createVertLines(3, 23, 69);
	createHorzLines(11,69,24,'B');

	//showing inner header
	innerHeader();

	gotoxy(36,10);
	cprintf("WELCOME");
	gotoxy(33,11);
	cprintf("PLEASE LOGIN");
	gotoxy(16,12);
	cprintf("-------------------------------------------------");
	gotoxy(16,14);
	cprintf("USERNAME:   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(16,16);
	cprintf("PASSWORD:   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(28,18);
	cprintf("Press <ENTER> to login.");

	gotoxy(28,14);
	fflush(stdin);
	scanString(username);

	gotoxy(28,16);
	fflush(stdin);
	scanPassword(password);


	if(stricmp(username,"admin")==0 && strcmp(password,"admin")==0)
	{
		loggedIn = 1;
		clrscr();
		gotoxy(30,10);
		textcolor(YELLOW);
		cprintf("Wait. Logging in.");
		delay(200);
		cprintf(".");
		delay(200);
		cprintf(".");
		delay(200);
		cprintf(".");
		delay(200);
		textcolor(WHITE);
		systemMenu();
	}
	else
	{
		 gotoxy(16,22);
		 textcolor(RED);
		 cprintf("Invalid username or password!");
		 textcolor(WHITE);
		 gotoxy(16,23);
		 cprintf("Press any key and type again.");
		 getch();
		 authenticateUsers();
	}

	getch();
}

/*===|================================================
  Generating the system's main menu.
  ===|==============================================*/
void systemMenu(){

	do{
        _setcursortype(_SOLIDCURSOR);
        clrscr();

        //creating box boundary lines
        createHorzLines(11,69,2, 'T');
        createVertLines(3, 23, 11);
        createVertLines(3, 23, 69);
        createHorzLines(11,69,24,'B');

        //showing inner header
        innerHeader();

        gotoxy(14,7);
        cprintf("Welcome to Parking System");
        gotoxy(14,8);
        cprintf("-------------------------");
        gotoxy(14,9);
        cprintf("Please choose what you want to do.");
        gotoxy(14,10);
        cprintf("[Press the MENU KEY of desired task]");

        //printing the menu

        gotoxy(14,13);
        cprintf("KEY | TASK");
        gotoxy(14,14);
        cprintf(" 1.   ADD TWO WHEELERS.");
        gotoxy(14,15);
        cprintf(" 2.   ADD FOUR WHEELERS.");
        gotoxy(14,16);
        cprintf(" 3.   RELEASE VEHICLE.");
        gotoxy(14,17);
        cprintf(" 4.   SHOW DAILY REPORT.");
        gotoxy(14,18);
        cprintf(" 5.   LOGOUT");
        gotoxy(14,19);
        cprintf(" Q.   QUIT");
        gotoxy(14,21);
        cprintf("Press menu key:");
        gotoxy(30,21);
        cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);

        _setcursortype(_SOLIDCURSOR);

        gotoxy(30,21);
        fflush(stdin);
        menuKey = getch();
	}
	while(menuKey!='1' && menuKey!='2' && menuKey!='3' && menuKey!='4' && menuKey!='5' && menuKey!='q' && menuKey!='Q');

	switch(menuKey){
		case '1':
		addTwoWheelers();
		break;

		case '2':
		addFourWheelers();
		break;

		case '3':
		searchVehicle();
		break;

		case '4':
		generateReport();
		break;

		case '5':
		loggedIn = 0;
		authenticateUsers();
		break;

		case 'q':
		case 'Q':
		exitApp();
		break;
	}
}


/*===|================================================
  Printing system date, in American format.
  ===|==============================================*/
void date()
{
	struct date dt;
	getdate(&dt);
	switch (dt.da_mon){
		case 1:
		cprintf("Jan");
		break;

		case 2:
		cprintf("Feb");
		break;

		case 3:
		cprintf("Mar");
		break;

		case 4:
		cprintf("Apr");
		break;

		case 5:
		cprintf("May");
		break;

		case 6:
		cprintf("Jun");
		break;

		case 7:
		cprintf("Jul");
		break;

		case 8:
		cprintf("Aug");
		break;

		case 9:
		cprintf("Sep");
		break;

		case 10:
		cprintf("Oct");
		break;

		case 11:
		cprintf("Nov");
		break;

		default :
		cprintf ("Dec");

	}
	cprintf(" %d, %d",dt.da_day,dt.da_year);
}

/*===|================================================
  getting system curr time
  ===|==============================================*/
float currTime(){

	struct time tm;
	gettime(&tm);
	hour = tm.ti_hour;
	if(hour >= 12){
		hour = hour-12;
	}
	mins = tm.ti_min;
	return hour+(mins/100);

}

/*===|================================================
  vehicle structure.
  ===|==============================================*/
struct vehicles{
	int id;
	float entry;
	char num[32];
	float exit;
	int charge;
	char user[32];
	int status;  /* 0 for parked, 1 for released */

}vehicle;

/*===|================================================
  new and unique key generation, automatically.
  ===|==============================================*/
int autoKeyGenerate()
{
	i=0;

	fl=fopen(dataFile(), "rb+");

	if(fl==NULL)
	{
		return 1;
	}

	while(fread(&vehicle,sizeof(vehicle),1,fl)!=0)
	{
	       i++;
	}

	fclose(fl);
	return i+1;
}

/*===|================================================
  Creating a form to get the vehicle data from user &
  store it.
  ===|==============================================*/
int addVehicleForm(int vType){

	//showing vehicle addition form.
	gotoxy(14,10);
	cprintf("Invoice No  : ");
	gotoxy(14,12);
	cprintf("Date        : ");
	gotoxy(14,14);
	cprintf("Entry time  : ");
	gotoxy(14,16);
	cprintf("Vehicle no  :");
	gotoxy(14,19);
	cprintf("Type vehicle NO. and press ENTER.");

	//text box design.
	gotoxy(28,16);
	cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	textbackground(CYAN);
	textcolor(WHITE);

    textcolor(YELLOW);
	//adding new & uniquie id.
	gotoxy(28,10);
	vehicle.id=autoKeyGenerate();
	cprintf("%i", vehicle.id);

	//adding date
	gotoxy(28,12);
	date();


	//adding system current time.
	gotoxy(28,14);
	vehicle.entry = currTime();
	cprintf("%2.2f", vehicle.entry);

    textcolor(WHITE);

	//taking vehicle num.
	gotoxy(28,16);
	scanWords(vehicle.num);

	//adding default charge
	if(vType==2){
		vehicle.charge = twoWheelerCharge;
	}
	else if(vType==4){
		vehicle.charge = fourWheelerCharge;
	}

	//adding staff name
	strcpy(vehicle.user,username);

	//adding default status "Parked==0"
	vehicle.status=0;

    //Writing into file
    fl = fopen(dataFile(), "ab+");

    if(fl==NULL){
        clrscr();
        gotoxy(8,10);
        cprintf("Couldn't write to file. Something went wrong. Please try again.");
        gotoxy(27,12);
        cprintf("Press <ANY> key to go back.");
        getch();
        systemMenu();
    }
    else{
		fwrite(&vehicle,sizeof(vehicle),1,fl);
		fclose(fl);

        delay(200);
        gotoxy(14,21);
        cprintf("Record added successfully.");
        delay(200);
    }

	//creating 'Park Entry Card'
	clrscr();

	//creating box boundary lines
	createHorzLines(11,69,2, 'T');
	createVertLines(3, 23, 11);
	createVertLines(3, 23, 69);
	createHorzLines(11,69,24,'B');

	innerHeader();
	gotoxy(14,6);
	cprintf("PARK ENTRY CARD");
	gotoxy(14,7);
	cprintf("---------------");
	gotoxy(14,8);
	date();

	//creating report boundaries.
	createHorzLines(14,66,9,'T');
	createVertLines(10,18,14);
	createVertLines(10,18,66);

	gotoxy(16,11);
	cprintf("Invoice No   : %i", vehicle.id);
	gotoxy(16,13);
	cprintf("Entry time   : %2.2f",vehicle.entry);
	gotoxy(16,15);
	cprintf("Vehicle No   : %s", vehicle.num);
	gotoxy(16,17);
	cprintf("Vehicle Type : %i Wheeler", vType);
	createHorzLines(14,66,19,'B');
	gotoxy(14,20);
	cprintf("Regards: %s", vehicle.user);
	gotoxy(14,23);
	cprintf("Press <ANY KEY> to return to main menu.");

	getch();
	systemMenu();
	return  0;
}

/*===|================================================
  Two wheeler vehicle addtion gateway function.
  ===|==============================================*/
void addTwoWheelers(){
	clrscr();
	//creating box boundary lines
	createHorzLines(11,69,2, 'T');
	createVertLines(3, 23, 11);
	createVertLines(3, 23, 69);
	createHorzLines(11,69,24,'B');

	//showing inner header
	innerHeader();
	gotoxy(14,7);
	cprintf("1. ADD TWO WHEELERS");
	gotoxy(14,8);
	cprintf("-------------------");

	//showing data addition form.
	addVehicleForm(2);


}

/*===|================================================
  Four wheeler vehicle addtion gateway function.
  ===|==============================================*/
void addFourWheelers(){
	clrscr();
	//creating box boundary lines
	createHorzLines(11,69,2, 'T');
	createVertLines(3, 23, 11);
	createVertLines(3, 23, 69);
	createHorzLines(11,69,24,'B');

	//showing inner header
	innerHeader();
	gotoxy(14,7);
	cprintf("2. ADD FOUR WHEELERS");
	gotoxy(14,8);
	cprintf("--------------------");

	//Showing data addition form.
	addVehicleForm(4);


}

/*===|================================================
  Vehicle search & release system & processigns
  ===|==============================================*/
void searchVehicle(){

	int found=0;
	int recordSize;

	while(1){

	found=0;

	clrscr();
	//creating box boundary lines
	createHorzLines(11,69,2, 'T');
	createVertLines(3, 23, 11);
	createVertLines(3, 23, 69);
	createHorzLines(11,69,24,'B');

	//showing inner header
	innerHeader();
	gotoxy(14,7);
	cprintf("3. RELEASE VEHICLE");
	gotoxy(14,8);
	cprintf("------------------");
	gotoxy(14,9);
	cprintf("Please enter 'park entry card' no. to search.");

	gotoxy(14,12);
	cprintf("Invoice no: ");
	gotoxy(26,14);
	cprintf("(Type number and press ENTER to search.)");

	//styling text box:
	gotoxy(26,12);
	cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	textcolor(WHITE);


	//returing to main menu from 'ESC' key.
	fflush(stdin);
	gotoxy(26,12);
	invoiceNo = scanInt();

    clrscr();
    //creating box boundary lines
    createHorzLines(11,69,2, 'T');
    createVertLines(3, 23, 11);
    createVertLines(3, 23, 69);
    createHorzLines(11,69,24,'B');

    //showing inner header
    innerHeader();
    gotoxy(14,7);
    cprintf("3.1 RELEASE VEHICLE");
    gotoxy(14,8);
    cprintf("-------------------");

    //Opening file in RB mode to enable readonly & safe search.
    fl=fopen(dataFile(), "rb+");

    if(fl==NULL){
        clrscr();
        gotoxy(8,10);
        cprintf("Couldn't read the data. Something went wrong. Please try again.");
        gotoxy(27,12);
        cprintf("Press <ANY> key to go back.");
        fflush(stdin);
        getch();
        continue;
    }

    while(fread(&vehicle,sizeof(vehicle),1,fl)!=0)
    {
        if(vehicle.id==invoiceNo)
        {
             found=1;
             break;
        }
    }

    if(found==1){

        gotoxy(14,9);
        textcolor(YELLOW);
        cprintf("Vehicle Found. Details are shown below");
        textcolor(WHITE);
        gotoxy(14,11);
        cprintf("Invoice No  : %i", vehicle.id);
        gotoxy(14,13);
        cprintf("Entry time  : %2.2f", vehicle.entry);
        gotoxy(14,15);
        cprintf("Exit time   :");
        gotoxy(28,15);
        cprintf("%2.2f", currTime());
        gotoxy(14,17);
        cprintf("Vehicle NO  : %s", vehicle.num);
        gotoxy(14,19);
        cprintf("Charge      : Rs.%2.2f/-", calculateCharge(vehicle.entry, currTime(), vehicle.charge));

        if(vehicle.status==1){

            gotoxy(14,9);
            textcolor(YELLOW);
            cprintf("THIS VEHICLE HAS ALREADY BEEN RELEASED. ");
            textcolor(WHITE);

            gotoxy(14,22);
            cprintf("Press <ANY KEY> to return back.");
            _setcursortype(_NOCURSOR);
            getch();
            fclose(fl);
            continue;

        }

        gotoxy(14,22);
        cprintf("Press Y to release or N to return back.");

        menuKey = getYN();

        if(menuKey=='y' || menuKey=='Y')
        {

            //setting exit time
            vehicle.exit=currTime();
            //Changing status to released;
            vehicle.status=1;
            //adding newly calculated chage.
            vehicle.charge= calculateCharge(vehicle.entry, currTime(), vehicle.charge);


            recordSize=sizeof(vehicle);
            fseek(fl,-recordSize,SEEK_CUR); //seek one step up and fwrite
            fwrite(&vehicle,sizeof(vehicle),1,fl);
            fclose(fl);

            gotoxy(14,23);
            textcolor(RED);
            cprintf("DONE.");
            textcolor(WHITE);

            delay(500);
            continue;
        }
        else{
            fclose(fl);
            continue;
        }
    }
    else{
            //Search result not found report showing.

            clrscr();
            //creating box boundary lines
            createHorzLines(11,69,2, 'T');
            createVertLines(3, 23, 11);
            createVertLines(3, 23, 69);
            createHorzLines(11,69,24,'B');

            //showing inner header
            innerHeader();

            textcolor(YELLOW);
            gotoxy(39,10);
            cprintf(":(");
	    gotoxy(35,12);
	    cprintf("ERROR !!!");
            gotoxy(30,13);
            cprintf("VEHICLE NOT FOUND");
            gotoxy(21,15);
            cprintf("Press any key to return to search again.");
            textcolor(WHITE);
            _setcursortype(_NOCURSOR);
            getch();
            fclose(fl);
            continue;

    }

	}

}

/*===|================================================
  Calculating the applicable charge.
  ===|==============================================*/
float calculateCharge(float entryTime, float exitTime, int rate){
    float totalCharge;
    float parkedTime = exitTime - entryTime;

    totalCharge = parkedTime * rate;

    if(totalCharge < rate){
        totalCharge = rate;
    }
    return totalCharge;
}

/*===|================================================
  Generating the full report.
  ===|==============================================*/
void generateReport(){
	int line=1;
	float totalIncome = 0;

	clrscr();
	//creating box top boundary lines
	createHorzLines(11,69,2, 'T');

	//showing inner header
	innerHeader();
	gotoxy(14,5);
	cprintf("4. DAILY REPORT");
	gotoxy(14,6);
	cprintf("---------------");
	gotoxy(14,7);
	date();

    //hiding blinkced cursor.
    _setcursortype(_NOCURSOR);

	//Creating report table header.
	createHorzLines(14,66,9,'T');
	gotoxy(15,10);
	cprintf(" NO | VEHICLE NO   | ENTRY | EXIT | CHARGE | USER");
	createHorzLines(14,66,11,'M');

    //adding lines of data
	fl=fopen(dataFile(), "rb+");
	if(fl==NULL)
	{
		gotoxy(15,12);
		textcolor(RED);
		cprintf(" COULDN'T READ THE RECORD !!!");
        textcolor(WHITE);

        //packing box when no file found.
        createHorzLines(14,66,line+13,'B');
        createVertLines(10,line+12,14);
        createVertLines(10,line+12,66); /* closing box bondaries. */
        gotoxy(14,line+16);
        cprintf("Press <ANY KEY> to return.");

        //creating box bottom boundary lines
        createVertLines(3, line+17, 11);
        createVertLines(3, line+17, 69);
        createHorzLines(11,69,line+17,'B');

        getch();
		systemMenu();
	}

	while(fread(&vehicle,sizeof(vehicle),1,fl)!=0)
	{
		gotoxy(16,11+line);
		cprintf("%i.",vehicle.id);

		gotoxy(19,11+line);
		cprintf("| %s",vehicle.num);

		gotoxy(34,11+line);
		cprintf("| %2.2f",vehicle.entry);

		gotoxy(42,11+line);
		cprintf("| %2.2f",vehicle.exit);//exit time.

		gotoxy(49,11+line);
		cprintf("| Rs. %i",vehicle.charge);

		gotoxy(58,11+line);
		cprintf("| %s",vehicle.user);

		totalIncome+=vehicle.charge;

		line+=1;
	}

	if(line==1){
		gotoxy(15,12);
		textcolor(YELLOW);
		cprintf(" NO RECORDS ADDED YET !!!");
        textcolor(WHITE);
        line+=1;
	}

	createHorzLines(14,66,line+11,'M');
	gotoxy(43,line+12);
	cprintf("Total:| Rs. %2.2f", totalIncome);
	createHorzLines(14,66,line+13,'B');
	createVertLines(10,line+12,14);
	createVertLines(10,line+12,66); /* closing box bondaries. */
	gotoxy(14,line+16);
	cprintf("Press <ANY KEY> to return.");

	//creating box bottom boundary lines
	createVertLines(3, line+17, 11);
	createVertLines(3, line+17, 69);
	createHorzLines(11,69,line+17,'B');

	//closing the recently opened file
	fclose(fl);

    //takign user back to main menu.
	fflush(stdin);
    getch();
    systemMenu();

}

/*===|================================================
  System termination processing function
  ===|==============================================*/
void exitApp(){
	clrscr();
	//creating box boundary lines
	createHorzLines(11,69,2, 'T');
	createVertLines(3, 23, 11);
	createVertLines(3, 23, 69);
	createHorzLines(11,69,24,'B');

	//showing inner header
	innerHeader();
	textcolor(YELLOW);
	gotoxy(36,11);
	cprintf("EXIT !!!");
	if(loggedIn==1){
		gotoxy(19,13);
		cprintf("Are you sure you want to EXIT the system?");
		gotoxy(22,14);
		cprintf("Press any key to return to main menu");
		gotoxy(32,15);
		cprintf("or press 'Y' to exit.");
		textcolor(WHITE);

		_setcursortype(_NOCURSOR);

		fflush(stdin);
		exitKey = getch();

		if(exitKey==121 || exitKey==89){
			exit(1);

		}
		else{
			systemMenu();
		}
	}
	else{
		gotoxy(22,13);
		cprintf("System is being closed.");

		delay(200);
		gotoxy(45,13);
		cprintf(".");
		delay(200);
		gotoxy(46,13);
		cprintf(".");
		delay(200);
		gotoxy(47,13);
		cprintf(".");
		delay(200);
		gotoxy(48,13);
		cprintf(".");
		delay(500);
		gotoxy(49,13);
		cprintf(".");
		exit(0);
	}

}

/*===|================================================
  All in one
  Running the application.
  ===|==============================================*/
int main(){
	//default screen styles
	textbackground(CYAN);
	clrscr();
	textcolor(WHITE);

	//showing splash screen
	splashScreen();

	//showing user login screen
	authenticateUsers();

	return 0;
}
