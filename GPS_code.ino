#define GpsSerial  Serial
#define DebugSerial Serial
int L = 13; //LED

struct
{
	char GPS_Buffer[80];
	bool isGetData;		
	bool isParseData;	
	char UTCTime[11];		
	char latitude[11];		
	char N_S[2];		
	char longitude[12];		
	char E_W[2];		
  char Speed[5];
  char Direction[5];
	bool isUsefull;		
} Save_Data;

struct
{
  double latitude;  
  double longitude; 
  //double Direction; 
} GPS_Data;



const unsigned int gpsRxBufferLength = 600;
char gpsRxBuffer[gpsRxBufferLength];
unsigned int ii = 0;


void setup()	
{
	GpsSerial.begin(9600);			
	DebugSerial.begin(9600);
	
	DebugSerial.println("Wating...");

	Save_Data.isGetData = false;
	Save_Data.isParseData = false;
	Save_Data.isUsefull = false;
}

void loop()		
{
	gpsRead();	
	parseGpsBuffer();
	getGps();
      

}

void errorLog(int num)
{
	DebugSerial.print("ERROR");
	DebugSerial.println(num);
	while (1)
	{
		digitalWrite(L, HIGH);
		delay(300);
		digitalWrite(L, LOW);
		delay(300);
	}
}

void getGps()
{
	if (Save_Data.isParseData)
	{
		Save_Data.isParseData = false;
		if(Save_Data.isUsefull)
		{
			Save_Data.isUsefull = false;
  
      GPS_Data.latitude = double(Save_Data.latitude[0]-48)*10+double(Save_Data.latitude[1]-48)+double(Save_Data.latitude[2]-48)/6+double(Save_Data.latitude[3]-48)/60+double(Save_Data.latitude[5]-48)/600+double(Save_Data.latitude[6]-48)/6000+double(Save_Data.latitude[7]-48)/60000+double(Save_Data.latitude[8]-48)/600000;
      if(Save_Data.N_S == "S"){
        GPS_Data.latitude = -GPS_Data.latitude;
      } 
      GPS_Data.longitude = double(Save_Data.longitude[0]-48)*100+double(Save_Data.longitude[1]-48)*10+double(Save_Data.longitude[2]-48)+double(Save_Data.longitude[3]-48)/6+double(Save_Data.longitude[4]-48)/60+double(Save_Data.longitude[6]-48)/600+double(Save_Data.longitude[7]-48)/6000+double(Save_Data.longitude[8]-48)/60000+double(Save_Data.longitude[9]-48)/600000+double(Save_Data.longitude[10]-48)/6000000;
      if(Save_Data.E_W == "W"){
        GPS_Data.longitude = -GPS_Data.longitude;
      }  		
      //GPS_Data.Direction = double(Save_Data.Direction[0]-'0')*100+double(Save_Data.Direction[1]-'0')*10+double(Save_Data.Direction[2]-'0')+double(Save_Data.Direction[4]-'0')/10;
      
      DebugSerial.print("GPS_Data.latitude= ");
      DebugSerial.println(GPS_Data.latitude,8);
      DebugSerial.print("GPS_Data.longitude= ");
      DebugSerial.println(GPS_Data.longitude,8);
      //DebugSerial.print(" GPS_Data.Direction= ");
      //DebugSerial.println( GPS_Data.Direction,8);
      
		}
		else
		{
			DebugSerial.println("GPS DATA is not usefull!");
		}
		
	}
  else{
    DebugSerial.println("did not parse data");
  }
  
}

void parseGpsBuffer()
{
	char *subString;
	char *subStringNext;
	if (Save_Data.isGetData)
	{
		Save_Data.isGetData = false;
    //test data
		//DebugSerial.println("**************");
		//DebugSerial.println(Save_Data.GPS_Buffer);

		
		for (int i = 0 ; i <= 6 ; i++)
		{
			if (i == 0)
			{
				if ((subString = strstr(Save_Data.GPS_Buffer, ",")) == NULL)
					errorLog(1);	
			}
			else
			{
				subString++;
				if ((subStringNext = strstr(subString, ",")) != NULL)
				{
					char usefullBuffer[2]; 
					switch(i)
					{
						case 1:memcpy(Save_Data.UTCTime, subString, subStringNext - subString);break;	//获取UTC时间
						case 2:memcpy(usefullBuffer, subString, subStringNext - subString);break;	//获取UTC时间
						case 3:memcpy(Save_Data.latitude, subString, subStringNext - subString);break;	//获取纬度信息
						case 4:memcpy(Save_Data.N_S, subString, subStringNext - subString);break;	//获取N/S
						case 5:memcpy(Save_Data.longitude, subString, subStringNext - subString);break;	//获取纬度信息
						case 6:memcpy(Save_Data.E_W, subString, subStringNext - subString);break;	//获取E/W
            case 7:memcpy(Save_Data.Speed, subString, subStringNext - subString);break;  //获取地面速率
            case 8:memcpy(Save_Data.Direction, subString, subStringNext - subString);break; //获取地面航向

						default:break;
					}

					subString = subStringNext;
					Save_Data.isParseData = true;
					if(usefullBuffer[0] == 'A')
						Save_Data.isUsefull = true;
					else if(usefullBuffer[0] == 'V')
						Save_Data.isUsefull = false;

				}
				else
				{
					errorLog(2);	
				}
			}


		}
	}
}


void gpsRead() {
	while (GpsSerial.available())
	{
		gpsRxBuffer[ii++] = GpsSerial.read();
		if (ii == gpsRxBufferLength)clrGpsRxBuffer();
	}

	char* GPS_BufferHead;
	char* GPS_BufferTail;
	if ((GPS_BufferHead = strstr(gpsRxBuffer, "$GPRMC,")) != NULL || (GPS_BufferHead = strstr(gpsRxBuffer, "$GNRMC,")) != NULL )
	{
		if (((GPS_BufferTail = strstr(GPS_BufferHead, "\r\n")) != NULL) && (GPS_BufferTail > GPS_BufferHead))
		{
			memcpy(Save_Data.GPS_Buffer, GPS_BufferHead, GPS_BufferTail - GPS_BufferHead);
			Save_Data.isGetData = true;

			clrGpsRxBuffer();
		}
	}
}

void clrGpsRxBuffer(void)
{
	memset(gpsRxBuffer, 0, gpsRxBufferLength);      
	ii = 0;
}
