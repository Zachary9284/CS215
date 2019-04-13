//Name: Zachary Lee
//Date: 3/25/2019
//Project Two
//Description: This project allows you to input a txt file with game settings and allow you to play that game
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "gameutils.h"

using namespace std;
//recieved help from Luke Durham

// PRINT LOGO
void printLogo()
{
	cout << "+--------------------------------------------+\n";
	cout << "|     0       Vv          0       (v   v)    |\n";
	cout << "|   o=|=o    (  )>      o=|=o   o==|___|==o  |\n";
	cout << "|    | |    [    ]       | |        | |      |\n";
	cout << "|            |_|_            By: Zachary Lee |\n";
	cout << "+--------------------------------------------+\n";
}


//GET INPUT FILE
string getInputFile()
{
	string gameN;
	
	cout <<"Enter file name of the game to play: ";
	cin >>gameN;
	cout << endl;
	
	return gameN;
}



//INITIALIZE ITEMS
void initItems(int &numItems,item Items[])
{
	for(int i=0;i <MAX_ITEMS;i++)
	{
		Items[i].shortDesc ="";
		
		Items[i].longDesc= "";
	}
	
	numItems= 0;
}



// INITIALIZE ROOMS
void initRooms(room Rooms[])
{
	for (int i= 0; i <MAX_ROOMS;i++)
	{
		Rooms[i].shortDesc ="";

		Rooms[i].longDesc= "";

		Rooms[i].north = NO_EXIT;

		Rooms[i].south = NO_EXIT;

		Rooms[i].east = NO_EXIT;

		Rooms[i].west = NO_EXIT;

		initItems(Rooms[i].numItems,Rooms[i].items);
	}
}



// INITIALIZE WIN DATA
void initWinData(winDataStruct &winData)
{
	winData.winMessage= "";

	winData.winRoom =NO_EXIT;

	initItems(winData.numWinItems,winData.winItem);
}





// REMOVE ITEM
item removeItem(int Index, item Items[], int & numItems)
{
	item remember;
	
	if ((Index< 0)|| (Index > MAX_ITEMS))
	{
		string errorMessage = "removeItem: Invlid index= " +Index;
		
		gameAbort(errorMessage);

	}

	else {
		remember= Items[Index];
		
		for (int i=Index; i < numItems;i++)
		{
			
			if (numItems!=MAX_ITEMS) {
				
				Items[i] =Items[i + 1];
			}
			
			else {
				
				if (i !=MAX_ITEMS -1) {
					
					Items[i] =Items[i + 1];
					
				}
				
				else {
					
					Items[i].longDesc = "";
					
					Items[i].shortDesc = "";
				}
			}
		}
	}
	
	numItems--;
	
	return remember;
}




//ADD ITEM
void addItem(item newItem, item Items[], int & numItems)
{
	if (numItems <= MAX_ITEMS)
	{
		Items[numItems] = newItem;
		
		numItems++;
	}
	else {
		string errorMessage ="addItem: max amount of items reached!!!";
		
		gameAbort(errorMessage);
	}
}




//ADD ITEM OVERLOAD
void addItem(string shortDescription,string longDescription,item Items[],int & numItems)
{
	//overload
	item newItem;
	newItem.shortDesc= shortDescription;

	newItem.longDesc = longDescription;

	addItem(newItem,Items,numItems);
}




// LOAD DATA
void loadData(room Rooms[],winDataStruct & winData, int & numRooms)
{
	ifstream f;               
	string tag;               
	string filename;       
	string data;           
	int roomNdx = -1;       
							
	initRooms(Rooms);
	initWinData(winData);

	filename = getInputFile() + ".txt";
	f.open(filename);
	
	if (f.fail())
	{
		string message = "File not found: " + filename;
		gameAbort(message);
	}

	f >> tag;
	
	while (tag != "END:") {
		
		if (tag == "ROOM:") {
			numRooms++;       
			roomNdx++;       
			
			cleanGetline(f, Rooms[roomNdx].shortDesc); 
			cleanGetline(f, Rooms[roomNdx].longDesc); 
		}
		
		else if (tag == "ITEM:") {
			string shortDesc, longDesc;
			
			cleanGetline(f, shortDesc);
			cleanGetline(f, longDesc);
			
			addItem(shortDesc, longDesc, Rooms[roomNdx].items, Rooms[roomNdx].numItems);
		}

		else if (tag == "WIN_ITEM:") {

			cleanGetline(f, data);
			addItem(data, "", winData.winItem, winData.numWinItems);
		}

		else if (tag == "NORTH:")
			f >> Rooms[roomNdx].north;

		else if (tag == "SOUTH:")
			f >> Rooms[roomNdx].south;

		else if (tag == "EAST:")
			f >> Rooms[roomNdx].east;

		else if (tag == "WEST:")
			f >> Rooms[roomNdx].west;

		else if (tag == "WIN_ROOM:")
			f >> winData.winRoom;

		else if (tag == "REMARK:")
			cleanGetline(f, data);  

		else if (tag == "WIN_TEXT:")
			cleanGetline(f, winData.winMessage);

		else if (tag == "END:")
			f.close();

		else
			gameAbort("Unknown tag in " + filename + ": " + tag);

		if (f.fail())
			gameAbort("Failure while reading input file " + filename);
		f >> tag;
	}
} 




//GET CMD
string getCmd(string & remander)
{
	string input;

	cout << "===> ";

	if (cin.peek() == '\n') cin.ignore();

	getline(cin, input);

	input = split(input, remander);

	return input;
}





//MAKE EXIT LIST
string makeExitList(room thisRoom) 
{
	string exitList = "You can go:";

	if (thisRoom.north != NO_EXIT) exitList += " north,";

	if (thisRoom.south != NO_EXIT) exitList += " south,";

	if (thisRoom.east != NO_EXIT) exitList += " east,";

	if (thisRoom.west != NO_EXIT) exitList += " west.";

	exitList[exitList.length() - 1] = '.'; 

	return exitList;
}






// DO LOOK
void doLook(room Room, bool showShort)
{
	if (showShort)
	{
		cout <<Room.shortDesc << endl;
	}
	
	else
	{
		cout << Room.longDesc << endl;
	}

	if (Room.numItems == 1)
	{
		cout << "You notice the following items: " << Room.items[0].shortDesc << "." << endl;
	}

	else if (Room.numItems > 1)
	{
		cout << "You notice the following items: ";
		for (int i = 0; i < Room.numItems - 1; i++)
		{
			cout << Room.items[i].shortDesc <<", ";
		}
		cout << Room.items[Room.numItems - 1].shortDesc << "." << endl;
	}

	cout <<makeExitList(Room) << endl;
}





// DO LOOK OVERLOAD
void doLook(room Room)
{
	doLook(Room, false);
}




//START UP
void startup(item inventory[], winDataStruct & winData, room Rooms[], int & numRooms, int & numItems)
{
	printLogo();

	cout << endl;

	printHelp();

	loadData(Rooms, winData, numRooms);

	initItems(numItems, inventory);

	cout << "You now awake in a land unknown to you:" << endl;

	doLook(Rooms[START_ROOM], false);
}





// GO NORTH
void goNorth(int & currentRoom, room rooms[]) {
	
	if (rooms[currentRoom].north == NO_EXIT)
		cout << "You can't go north.\n";
	
	else {
		currentRoom = rooms[currentRoom].north;
		doLook(rooms[currentRoom], true);
	}
} 




// GO SOUTH
void goSouth(int & currentRoom, room rooms[]) {
	if (rooms[currentRoom].south == NO_EXIT)
		cout << "You can't go south.\n";
	
	else {
		currentRoom = rooms[currentRoom].south;
		doLook(rooms[currentRoom], true); 
	}
} 




//GO EAST
void goEast(int & currentRoom, room rooms[]) {
	if (rooms[currentRoom].east == NO_EXIT)
		cout << "You can't go east.\n";
	
	else {
		currentRoom = rooms[currentRoom].east;
		doLook(rooms[currentRoom], true); 
	}
}




//GO WEST
void goWest(int & currentRoom, room rooms[]) {
	if (rooms[currentRoom].west == NO_EXIT)
		cout << "You can't go west.\n";
	
	else {
		currentRoom = rooms[currentRoom].west;
		doLook(rooms[currentRoom], true); 
	}
}





//FIND ITEM
int findItem(string itemName,int numItems, item Items[])
{
	for (int i =0; i <=numItems; i++)
	{
		if (Items[i].shortDesc ==itemName)
		{

			return i;
		}
	}
	
	return NOT_FOUND;
}





// DO EXAMINE
void doExamine(string itemName, item playerInventory[], int numItems, item roomInventory[], int numRoomItems)
{
	int itemNdx= findItem(itemName, numRoomItems, roomInventory);

	if (itemNdx > -1)
		cout <<roomInventory[itemNdx].longDesc << endl;
	
	else
	{
		itemNdx = findItem(itemName, numRoomItems, roomInventory);
		
		if (itemNdx!= -1)
			cout << playerInventory[itemNdx].longDesc << endl;
		
		else
			cout<< "You dont see " <<itemName << endl;
	}

}






// DO TAKE
void doTake(string itemName, item playerInventory[], int numItems, item roomInventory[], int numRoomItems)
{
	int itemNdx = findItem(itemName, numRoomItems, roomInventory);
	item Item;
	
	cout << "Item is in: " << itemNdx << endl;
	
	if (itemNdx!= -1) 
	{
		
		cout<< "Item is found" << endl;
		
		if (numItems < MAX_ITEMS) 
		{
			Item = removeItem(itemNdx, roomInventory, numRoomItems);
			
			addItem(Item, playerInventory, numItems);
			
			cout << "You pick up the " << itemName << endl;
		}
		
		else
		{
			cout << "You are overburdened you cannot pick up anything, anymore." << endl;
		}
	}
	
	else 
	{
		itemNdx = findItem(itemName, numRoomItems, roomInventory);
		if (itemNdx != -1)
		{
			cout << "You already have the " << itemName << endl;
		}
		
		else
		{
			cout << "You dont see " << itemName << endl;
		}
	}
}





//DO DROP
void doDrop(string itemName, item playerInventory[], int numItems, item roomInventory[], int numRoomItems)
{
	int itemNdx = findItem(itemName, numRoomItems, roomInventory);
	item Item;
	if (itemNdx!= -1) 
	{
		if (numRoomItems<= MAX_ITEMS)
		{
			Item = removeItem(itemNdx,playerInventory, numItems);
			addItem(Item.shortDesc, Item.longDesc, roomInventory, numRoomItems);
			cout << "You drop the " << itemName << endl;
		}
		
		else
		{
			cout << "The room is full, cannot drop that item." << endl;
		}
	}
	else
	{
		itemNdx = findItem(itemName, numRoomItems, roomInventory);
		if (itemNdx != -1) 
		{
			cout << "You don't have a/an" << itemName << endl;
		}
		else
		{
			cout << "You do not have " << itemName << endl;
		}
	}
}






//GAME WON
bool gameWon(winDataStruct winData, room Rooms[])
{
	int itemNdex = -1;
	int collected = 0;
	for (int i = 0; i < winData.numWinItems; i++)
	{
		itemNdex =findItem(winData.winItem[i].shortDesc, Rooms[winData.winRoom].numItems, Rooms[winData.winRoom].items);
		
		if (itemNdex != -1)
		{
			collected++;
		}

	}
	
	if (collected == winData.numWinItems)
		return true;
	
	else
		return false;
}




//DO INVENTORY
void doInventory(item item[], int numItems) {
	if (numItems == 0)
		cout << "You don't have anything.\n";
	
	else {
		cout << "You are holding: ";
		
		for (int i = 0; i < (numItems - 1); i++)
			cout << item[i].shortDesc << ", ";
		
		cout << item[numItems - 1].shortDesc << ".\n";
	}
}






// MAIN
int main() {

	room Rooms[MAX_ROOMS];
	item Items[MAX_ITEMS];
	winDataStruct winData;

	string cmd;
	string remainder;
	bool gameWasWon = false;
	int numItems, numRooms = 0, roomNdx = 0;

	startup(Items, winData,Rooms, numRooms, numItems);

	cmd = getCmd(remainder);
	
	while (cmd != "exit" && !gameWasWon) {
		if (cmd == "help")
			printHelp();
		
		else if (cmd =="look" ||cmd == "l")
			doLook(Rooms[roomNdx], false);
		
		else if (cmd == "inv"||cmd == "i")
			doInventory(Items, numItems);
		
		else if (cmd =="exa" || cmd == "x")
			doExamine(remainder, Items,  numItems, Rooms[roomNdx].items, Rooms[roomNdx].numItems);
		
		else if (cmd == "take"||cmd== "t")
			doTake(remainder, Items, numItems, Rooms[roomNdx].items, Rooms[roomNdx].numItems);
		
		else if (cmd =="drop" ||cmd == "t")
		{
			doDrop(remainder, Items, numItems, Rooms[roomNdx].items, Rooms[roomNdx].numItems);
		}
		
		
		else if (cmd =="north"||cmd == "n")
			goNorth(roomNdx, Rooms);
		
		else if (cmd== "south" ||cmd =="s")
			goSouth(roomNdx, Rooms);
		
		else if (cmd == "east"||cmd =="e")
			goEast(roomNdx, Rooms);
		
		else if (cmd=="west" ||cmd == "w")
			goWest(roomNdx, Rooms);
		
		else 
			cout << "What??\n";

		gameWasWon = gameWon(winData, Rooms);

		if (gameWasWon)
			cout << winData.winMessage<< endl;
		
		else
			cmd =getCmd(remainder);

	}

	
	system("pause");
	return 0;
}

