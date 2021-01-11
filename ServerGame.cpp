#ifdef _WIN32
#include "../stdafx.h"
#endif

#include "ServerGame.h"
#include "Servernetwork.h"
#include <fstream>
#include <iostream>
#include "strucwebuser.h"
#include "Basproc.h"
#include "clstijd.h"
#include "Statvars.h"
using namespace std;

extern clswbusr* p_clswbusr;
extern clstijd* p_clstijd;
ServerGame * server;
extern statvars* p_statvars;
//WEBWEB
bool delayGelezen = false;
int aantbufferclient;
uint8_t bufferclient[100];
bool lezen[500];
bool adresls[500];
bool statverzlees[500];
char lees[32];
char lees2[32];
int lees2length = 0;
int leeslength = 0;
int leestel[150];
uint8_t adres[100];
unsigned int toevoegenid;
bool adresvervangen;
void tijdadresproc();
void stuurbericht();
void zetleesbestandtxtproc();



char leesbestandtxt[32];
int leesvanweblength;
int leesbestandtxtlength;
int leesbestandlength;
char leesbestand[32];
unsigned int ServerGame::client_id; 
bool statusvar[900];
uint8_t statusdimvar[900];
bool zendallen; 
unsigned int zendid;
char stuurlees[32];
unsigned int stuurleeslength;
char webstuurlees[1000000];
unsigned int webstuurleeslength;
char leesbestandmap[32];
int leesbestandmaplength;
char leesfiletxt[64]; int leesfiletxtlength;
bool webgestuurd;
char stuurweb[32];
//unsigned int stuurweblength;
 int8_t watuitvoeren = 0;
 int8_t watuitvoerenr = 0;
  
 unsigned int gavervadr;

 char recvBuff[1000];

 uint8_t dedimwaarde;

 

// extern void webserverloop(unsigned int id);
 unsigned int webadressluit;
 extern void webserverloop(unsigned int id);




ServerGame::ServerGame(void)
{
    // id's to assign clients for our table
    client_id = 0;
	// set up the server network to listen 
    network = new ServerNetwork(); 
}

ServerGame::~ServerGame(void)
{
}

void ServerGame::update(char* network_data, unsigned int data_length, uint8_t mpNo, uint8_t& adrs)
{
	
}
// packet.deserialize(&(network_data[i]));
// i += sizeof(Packet);

// switch (packet.packet_type) {

//  case INIT_CONNECTION:

//       printf("server received init packet from client\n");

//       sendActionPackets();

//       break;

//   case ACTION_EVENT:

//        printf("server received action event packet from client\n");

//      sendActionPackets();
//	stuurbericht();

//      break;

//  default:

//       printf("error in packet types\n");

//      break;
//   }

void ServerGame::receiveFromClients() {
	
}


void ServerGame::sendActionPackets()
{
}

void ServerGame::temppr(char* ls) {
	
}

void stuurbericht()
{
	p_clswbusr = new clswbusr;
	server = new ServerGame();
	p_clstijd = new clstijd;
	aantbufferclient = 0;
	leesbestandtxtlength = 0;
	leesbestandlength = 0;
	leeslength = 0;
	adresvervangen = 0;
	zendallen = 0;
	zendid = 255;
	stuurleeslength = 0;
	leesbestandmaplength = 0;
	leesfiletxtlength = 0;
//	varsstat = new destatvars;
	for (int tol = 0; tol < 900; tol++) {
		statusvar[tol] = 0;
		if (tol < 100) {
			bufferclient[tol] = 0;
			adres[tol] = 255;
			
		}
	}
	strncpy_s(lees, 5, "VR01", 4);
	p_statvars = new statvars;
	tijdadresproc();

}

extern uint8_t* LEDPL_ADR; extern uint8_t* LEDPL_StripCnt;
extern uint8_t LEDPL_CNT;

void tijdadresproc() {
//	char thisBestand = '~';
//	int8_t tels = 0;
	memFileObj lsFile(fileData);
	leesbestandmap[0] = 'O'; leesbestandmap[1] = 'v'; leesbestandmap[2] = 'e'; leesbestandmap[3] = 'r'; leesbestandmap[4] = 'i'; leesbestandmap[5] = 'g'; leesbestandmap[6] = 'e'; leesbestandmaplength = 7; leesbestandtxt[0] = 'T'; leesbestandtxt[1] = 'i'; leesbestandtxt[2] = 'j'; leesbestandtxt[3] = 'd'; leesbestandtxt[4] = 'a'; leesbestandtxt[5] = 'd'; leesbestandtxt[6] = 'r'; leesbestandtxt[7] = 'e'; leesbestandtxt[8] = 's'; leesbestandtxtlength = 9;
	//zetleesbestandtxtproc();
	//lsFile.open(leesfiletxt + 5);
	leesbestandlength = 0;
	//thisBestand = lsFile.get();
	//while (thisBestand != '\n') {
		/*leesbestand[leesbestandlength++] = thisBestand;
			thisBestand = lsFile.get();
		}
	leesbestand[leesbestandlength] = '\0';
	while (leesbestand[0] != 'G' || leesbestand[1] != 'G') {
		tijdadres.insert(pair<int8_t, int8_t>(tels++, (leesbestand[0] - '0') * 10 + (leesbestand[1] - '0')));
		leesbestandlength = 0;
		leesbestand[0] = '1'; leesbestand[1] = '1';
		thisBestand = lsFile.get();
		while (thisBestand != '\n' && (leesbestand[0] != 'G' || leesbestand[1] != 'G')) {
				leesbestand[leesbestandlength++] = thisBestand;
				thisBestand = lsFile.get();				
		}
		leesbestand[leesbestandlength] = '\0';
	}	
	*/
	strncpy_s(leesbestandtxt, 8, "LedPlaf", leesbestandtxtlength = 7); zetleesbestandtxtproc(); lsFile.open(leesfiletxt + 5);
	char* fl_ = lsFile.file; unsigned long & sk_ = lsFile.loc; LEDPL_ADR = new uint8_t[LEDPL_CNT = strbasprc::cvintcharStr(strbasprc::charPLsR(leesbestandtxt, fl_, sk_))]; LEDPL_StripCnt = new uint8_t[LEDPL_CNT]; uint8_t tt = 0; 
	while (*strbasprc::charPLsR(leesbestandtxt, fl_, sk_)) LEDPL_ADR[tt] = strbasprc::cvintcharint(*leesbestandtxt), LEDPL_StripCnt[tt++] = strbasprc::cvintcharint(leesbestandtxt[1]);
		leesbestandtxtlength = 0; leesbestandlength = 0;
}

void zetleesbestandtxtproc() {
	leesfiletxtlength = leesbestandtxtlength;
	for (int tel = 0; tel < 32; tel++) {
		leesfiletxt[tel] = leesbestandtxt[tel];
	}

	// eerste (achterste) toevoeging map

	if (leesbestandmaplength > 0) {
		for (int tel = leesfiletxtlength - 1; tel >= 0; tel--) {
			leesfiletxt[tel + leesbestandmaplength + 1] = leesfiletxt[tel];
		}
		leesfiletxtlength = leesbestandtxtlength + leesbestandmaplength + 1;
		for (int tel = 0; tel < leesbestandmaplength; tel++) {
			leesfiletxt[tel] = leesbestandmap[tel];
		}
		leesfiletxt[leesbestandmaplength] = '/';
	}


	// tweede toevoeging

	for (int tel = leesfiletxtlength - 1; tel >= 0; tel--) {
		leesfiletxt[tel + 5] = leesfiletxt[tel];
	}
	leesfiletxtlength = leesfiletxtlength + 5;
	leesfiletxt[0] = 'D';
	leesfiletxt[1] = 'a';
	leesfiletxt[2] = 't';
	leesfiletxt[3] = 'a';
	leesfiletxt[4] = '/';

	leesfiletxt[leesfiletxtlength++] = '.';
	leesfiletxt[leesfiletxtlength++] = 't';
	leesfiletxt[leesfiletxtlength++] = 'x';
	leesfiletxt[leesfiletxtlength++] = 't';
	leesfiletxt[leesfiletxtlength] = '\0';
	
}