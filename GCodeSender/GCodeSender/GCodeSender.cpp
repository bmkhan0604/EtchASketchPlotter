#include "Header.h"

// application reads from the specified serial port and reports the collected data
int _tmain(int argc, _TCHAR* argv[])
{
	std::cout <<"		::Gcode Sender::\n\n";
	
	std::cout << "		--Reading File--\n";
	link ptr = readFile();
	
	std::cout << "		--Connecting to Arduino--\n";
	char comnum[] = "\\\\.\\COM ";    // adjust as needed;
	std::cout << "Enter Port Number: COM";
	std::cin >> comnum[7];
	Serial* Arduino = new Serial(comnum);    // adjust as needed
	if (Arduino->IsConnected())
		printf("We're connected");
	char incomingData[255];
	int j;
	Sleep(2000);

	while (Arduino->IsConnected())
	{
		std::cout << "\n\nPointer: " << ptr << "\n";
		std::cout << "Sending Info: " << ptr->data <<'\n';
		Arduino->WriteData(ptr->data, size(ptr->data,sizeof(ptr->data)));
		//Arduino->WriteData("X2000 Y2000 @\n", 14);
		char data[255];
		for (int i = 0; i < sizeof(incomingData); i++)	// clears the char array to minimize carry over form prev trans
			incomingData[i] = '\0';

		while (Data.find("Done") == -1)// -1 means did not find, 32 bit number, all 1's
		{
			j = Arduino->ReadData(incomingData, 255);
			if (j > 0)	// if data read was valid
			{
				Data.append(incomingData);
				//std::cout << Data;//<< " Find Data: " << Data.find("Done")<< '\n';
				for (int i = 0; i < sizeof(incomingData); i++)	// clears the char array to minimize carry over form prev trans
					incomingData[i] = '\0';
			}
		}
		if (ptr->nextptr == NULL)
			break;
		ptr = ptr->nextptr;
		Data = "";
		//Sleep(1000);
	}
	std::cout << "		--Done sending Commands--\n\n\n";
	return 0;
}