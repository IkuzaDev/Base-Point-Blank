
#include "Connect HDSN.h"
#include <windows.h>
#include <iostream>
#pragma warning(disable: 4172)
using namespace std;
char DiskInfo::VI [1024];
char DiskInfo::SN [1024];
char DiskInfo::MN [1024];
char DiskInfo::RN [1024];

void DiskInfo::getIDEInfo()
{
	strcpy( MN, ConvertToString(diskdata, 27, 46));
	strcpy( SN, ConvertToString(diskdata, 10, 19));
	strcpy( RN, ConvertToString(diskdata, 23, 26));
}

int DiskInfo::DriveReadSMART (void)
{
   int done = FALSE;
   //int drive = uDriveNum;
   
   HANDLE hPhysicalDriveIOCTL = 0;
   
   char driveName [256];
   sprintf  (driveName, "\\\\.\\PhysicalDrive%d", uDriveNum);

   //  Windows NT, Windows 2000, Windows Server 2003, Vista
   hPhysicalDriveIOCTL = CreateFile (driveName,
                               GENERIC_READ | GENERIC_WRITE, 
                               FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, 
							   NULL, OPEN_EXISTING, 0, NULL);

   if (hPhysicalDriveIOCTL == INVALID_HANDLE_VALUE)
   {

   }
   else
   {
	   GETVERSIONINPARAMS GetVersionParams;
	   DWORD cbBytesReturned = 0;
	   memset ((void*) & GetVersionParams, 0, sizeof(GetVersionParams));
	   if (  DeviceIoControl (hPhysicalDriveIOCTL, SMART_GET_VERSION,
		   NULL, 
		   0,
		   &GetVersionParams, sizeof (GETVERSIONINPARAMS),
		   &cbBytesReturned, NULL) )
	   {         
		   ULONG CommandSize = sizeof(SENDCMDINPARAMS) + IDENTIFY_BUFFER_SIZE;
		   PSENDCMDINPARAMS Command = (PSENDCMDINPARAMS) malloc (CommandSize);

#define ID_CMD          0xEC            // Returns ID sector for ATA

		   Command -> irDriveRegs.bCommandReg = ID_CMD;
		   DWORD BytesReturned = 0;
		   if ( DeviceIoControl (hPhysicalDriveIOCTL, 
			   SMART_RCV_DRIVE_DATA, Command, sizeof(SENDCMDINPARAMS),
			   Command, CommandSize,
			   &BytesReturned, NULL) )

		   {
			   USHORT *pIdSector = (USHORT *)(PIDENTIFY_DATA) ((PSENDCMDOUTPARAMS) Command) -> bBuffer;
			   for (int haa = 0; haa < 256; haa++) diskdata [haa] = pIdSector [haa];
			   getIDEInfo();
			   done = TRUE;
		   }
		   CloseHandle (hPhysicalDriveIOCTL);
		   free (Command);
	   }
   }
   return done;
}

int DiskInfo::DriveReadAdmin (void)
{
	int done = FALSE;
	BYTE IdOutCmd [sizeof (SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1];
	HANDLE hPhysicalDriveIOCTL = 0;

	TCHAR driveName [256];

	sprintf (driveName, "\\\\.\\PhysicalDrive%d", uDriveNum);

	//  Windows NT, Windows 2000, run as admin 
	hPhysicalDriveIOCTL = CreateFile (driveName,
		GENERIC_READ | GENERIC_WRITE, 
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
		OPEN_EXISTING, 0, NULL);

	if (hPhysicalDriveIOCTL != INVALID_HANDLE_VALUE)
	{
		GETVERSIONOUTPARAMS VersionParams;
		DWORD               cbBytesReturned = 0;

		memset ((void*) &VersionParams, 0, sizeof(VersionParams));

		if (  DeviceIoControl (hPhysicalDriveIOCTL, DFP_GET_VERSION,
			NULL, 
			0,
			&VersionParams,
			sizeof(VersionParams),
			&cbBytesReturned, NULL) )
		{         

			if (VersionParams.bIDEDeviceMap > 0)
			{
				BYTE             bIDCmd = 0;   // IDE or ATAPI IDENTIFY cmd
				SENDCMDINPARAMS  scip;
				bIDCmd = (VersionParams.bIDEDeviceMap >> uDriveNum & 0x10) ? \
IDE_ATAPI_IDENTIFY : IDE_ATA_IDENTIFY;

				memset (&scip, 0, sizeof(scip));
				memset (IdOutCmd, 0, sizeof(IdOutCmd));

				if ( DoIDENTIFY (hPhysicalDriveIOCTL, 
					&scip, 
					(PSENDCMDOUTPARAMS)&IdOutCmd, 
					(BYTE) bIDCmd,
					(BYTE) uDriveNum,
					&cbBytesReturned))
				{
					USHORT *pIdSector = (USHORT *)((PSENDCMDOUTPARAMS) IdOutCmd) -> bBuffer;
					for (int aa = 0; aa < 256; aa++) diskdata [aa] = pIdSector [aa];  
					getIDEInfo();
					done = TRUE;
				}
			}
		}

		CloseHandle (hPhysicalDriveIOCTL);
	}
	return done;
}

#pragma pack(4)


#define IOCTL_STORAGE_QUERY_PROPERTY   CTL_CODE(IOCTL_STORAGE_BASE, 0x0500, METHOD_BUFFERED, FILE_ANY_ACCESS)

char * DiskInfo::flipAndCodeBytes (char * str)
{
	static char flipped [1000];
	int num = strlen (str);
	strcpy (flipped, "");
	for (int i = 0; i < num; i += 4)
	{
		for (int j = 1; j >= 0; j--)
		{
			int sum = 0;
			for (int k = 0; k < 2; k++)
			{
				sum *= 16;
				switch (str [i + j * 2 + k])
				{
				case '0': sum += 0; break;
				case '1': sum += 1; break;
				case '2': sum += 2; break;
				case '3': sum += 3; break;
				case '4': sum += 4; break;
				case '5': sum += 5; break;
				case '6': sum += 6; break;
				case '7': sum += 7; break;
				case '8': sum += 8; break;
				case '9': sum += 9; break;
				case 'a': sum += 10; break;
				case 'b': sum += 11; break;
				case 'c': sum += 12; break;
				case 'd': sum += 13; break;
				case 'e': sum += 14; break;
				case 'f': sum += 15; break;
				}
			}
			if (sum > 0) 
			{
				char sub [2];
				sub [0] = (char) sum;
				sub [1] = 0;
				strcat (flipped, sub);
			}
		}
	}

	return flipped;
}

char * flipAndCodeBytes2 (const char * str,
						 int pos,
						 int flip,
						 char * buf)
{
	int i;
	int j = 0;
	int k = 0;

	buf [0] = '\0';
	if (pos <= 0) return buf;
	if ( ! j)
	{
		char p = 0;

		// First try to gather all characters representing hex digits only.
		j = 1;
		k = 0;
		buf[k] = 0;
		for (i = pos; j && str[i] != '\0'; ++i)
		{

			char c = tolower(str[i]);
			if (isspace(c))	    c = '0';
			++p;
			buf[k] <<= 4;

			if (c >= '0' && c <= '9')
				buf[k] |= (unsigned char) (c - '0');
			else if (c >= 'a' && c <= 'f')
				buf[k] |= (unsigned char) (c - 'a' + 10);
			else
			{
				j = 0;
				break;
			}

			if (p == 2)
			{
				if (buf[k] != '\0' && ! isprint(buf[k]))
				{
					j = 0;
					break;
				}
				++k;
				p = 0;
				buf[k] = 0;
			}

		}
	}

	if ( ! j)
	{
		// There are non-digit characters, gather them as is.
		j = 1;
		k = 0;
		for (i = pos; j && str[i] != '\0'; ++i)
		{
			char c = str[i];

			if ( ! isprint(c))
			{
				j = 0;
				break;
			}

			buf[k++] = c;
		}
	}

	if ( ! j)
	{
		// The characters are not there or are not printable.
		k = 0;
	}

	buf[k] = '\0';

	if (flip)
		// Flip adjacent characters
		for (j = 0; j < k; j += 2)
		{
			char t = buf[j];
			buf[j] = buf[j + 1];
			buf[j + 1] = t;
		}
		// Trim any beginning and end space
		i = j = -1;
		for (k = 0; buf[k] != '\0'; ++k)
		{
			if (! isspace(buf[k]))
			{
				if (i < 0)
					i = k;
				j = k;
			}
		}

		if ((i >= 0) && (j >= 0))
		{
			for (k = i; (k <= j) && (buf[k] != '\0'); ++k)
				buf[k - i] = buf[k];
			buf[k - i] = '\0';
		}
		return buf;
}


typedef struct _MEDIA_SERAL_NUMBER_DATA {
  ULONG  SerialNumberLength; 
  ULONG  Result;
  ULONG  Reserved[2];
  UCHAR  SerialNumberData[1];
} MEDIA_SERIAL_NUMBER_DATA, *PMEDIA_SERIAL_NUMBER_DATA;

int DiskInfo::DriveReadNoAdmin (void)
{
	int done = FALSE;
	//int drive = 0;

	HANDLE hPhysicalDriveIOCTL = 0;
	char driveName [256];
	sprintf_s(driveName, "\\\\.\\PhysicalDrive%d", uDriveNum);

	//  Windows NT, Windows 2000, Windows XP - admin rights not required
	hPhysicalDriveIOCTL = CreateFile (driveName, 0,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
		OPEN_EXISTING, 0, NULL);
	if (hPhysicalDriveIOCTL == INVALID_HANDLE_VALUE)
	{
	}
	else
	{
		STORAGE_PROPERTY_QUERY query;
		DWORD cbBytesReturned = 0;
		char buffer [10000];

		memset ((void *) & query, 0, sizeof (query));
		query.PropertyId = StorageDeviceProperty;
		query.QueryType = PropertyStandardQuery;

		memset (buffer, 0, sizeof (buffer));


		if ( DeviceIoControl (hPhysicalDriveIOCTL, 
			IOCTL_STORAGE_QUERY_PROPERTY,
			& query,
			sizeof (query),
			& buffer,
			sizeof (buffer),
			& cbBytesReturned, (LPOVERLAPPED)NULL) )
		{         
			STORAGE_DEVICE_DESCRIPTOR * descrip = (STORAGE_DEVICE_DESCRIPTOR *) & buffer;
			char serialNumber [1000];
			char modelNumber [1000];
			char vendorId [1000];
			char productRevision [1000];
			flipAndCodeBytes2 (buffer, 
				descrip -> VendorIdOffset,
				0, vendorId );
			flipAndCodeBytes2 (buffer,
				descrip -> ProductIdOffset,
				0, modelNumber );
			flipAndCodeBytes2 (buffer,
				descrip -> ProductRevisionOffset,
				0, productRevision );

			flipAndCodeBytes2 (buffer,
				descrip -> SerialNumberOffset,
				1, serialNumber );

			if (0 == SN [0] &&
				//  serial number must be alphanumeric
				//  (but there can be leading spaces on IBM drives)
				(isalnum (serialNumber [0]) || isalnum (serialNumber [19])))
			{
				strcpy (VI, vendorId);
				strcpy (MN, modelNumber);
				strcpy (SN, serialNumber);
				strcpy (RN, productRevision);
				done = TRUE;
			}
			memset (buffer, 0, sizeof(buffer));
			if ( ! DeviceIoControl (hPhysicalDriveIOCTL,
				IOCTL_DISK_GET_DRIVE_GEOMETRY_EX,
				NULL,
				0,
				&buffer,
				sizeof(buffer),
				&cbBytesReturned,
				NULL))
			{

			}
			else
			{         
				DISK_GEOMETRY_EX* geom = (DISK_GEOMETRY_EX*) &buffer;
				int fixed = (geom->Geometry.MediaType == FixedMedia);
				__int64 size = geom->DiskSize.QuadPart;

			}
		}
		else
		{
			DWORD err = GetLastError ();

		}

		CloseHandle (hPhysicalDriveIOCTL);
	}

	return done;
}


   // DoIDENTIFY
   // FUNCTION: Send an IDENTIFY command to the drive
   // bDriveNum = 0-3
   // bIDCmd = IDE_ATA_IDENTIFY or IDE_ATAPI_IDENTIFY
BOOL DiskInfo::DoIDENTIFY (HANDLE hPhysicalDriveIOCTL, PSENDCMDINPARAMS pSCIP,
                 PSENDCMDOUTPARAMS pSCOP, BYTE bIDCmd, BYTE bDriveNum,
                 PDWORD lpcbBytesReturned)
{
      // Set up data structures for IDENTIFY command.
   pSCIP -> cBufferSize = IDENTIFY_BUFFER_SIZE;
   pSCIP -> irDriveRegs.bFeaturesReg = 0;
   pSCIP -> irDriveRegs.bSectorCountReg = 1;
   pSCIP -> irDriveRegs.bSectorNumberReg = 1;
   pSCIP -> irDriveRegs.bCylLowReg = 0;
   pSCIP -> irDriveRegs.bCylHighReg = 0;

      // Compute the drive number.
   pSCIP -> irDriveRegs.bDriveHeadReg = 0xA0 | ((bDriveNum & 1) << 4);

      // The command can either be IDE identify or ATAPI identify.
   pSCIP -> irDriveRegs.bCommandReg = bIDCmd;
   pSCIP -> bDriveNumber = bDriveNum;
   pSCIP -> cBufferSize = IDENTIFY_BUFFER_SIZE;

   return ( DeviceIoControl (hPhysicalDriveIOCTL, DFP_RECEIVE_DRIVE_DATA,
               (LPVOID) pSCIP,
               sizeof(SENDCMDINPARAMS) - 1,
               (LPVOID) pSCOP,
               sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1,
               lpcbBytesReturned, NULL) );
}


//  ---------------------------------------------------

   // (* Output Bbuffer for the VxD (rt_IdeDinfo record) *)
typedef struct _rt_IdeDInfo_
{
    BYTE IDEExists[4];
    BYTE DiskExists[8];
    WORD DisksRawInfo[8*256];
} rt_IdeDInfo, *pt_IdeDInfo;


   // (* IdeDinfo "data fields" *)
typedef struct _rt_DiskInfo_
{
   BOOL DiskExists;
   BOOL ATAdevice;
   BOOL RemovableDevice;
   WORD TotLogCyl;
   WORD TotLogHeads;
   WORD TotLogSPT;
   char SerialNumber[20];
   char FirmwareRevision[8];
   char ModelNumber[40];
   WORD CurLogCyl;
   WORD CurLogHeads;
   WORD CurLogSPT;
} rt_DiskInfo;


#define  m_cVxDFunctionIdesDInfo  1


//  ---------------------------------------------------

int DiskInfo::DriveReadPort9x (void)
{
   int done = FALSE;
   unsigned long int i = 0;

   HANDLE VxDHandle = 0;
   pt_IdeDInfo pOutBufVxD = 0;
   DWORD lpBytesReturned = 0;

   BOOL status = SetPriorityClass (GetCurrentProcess (), REALTIME_PRIORITY_CLASS);

   rt_IdeDInfo info;
   pOutBufVxD = &info;


   ZeroMemory (&info, sizeof(info));
 
   VxDHandle = CreateFile ("\\\\.\\IDE21201.VXD", 0, 0, 0, 0, FILE_FLAG_DELETE_ON_CLOSE, 0);

   if (VxDHandle != INVALID_HANDLE_VALUE)
   {
      DeviceIoControl (VxDHandle, m_cVxDFunctionIdesDInfo,
					0, 0, pOutBufVxD, sizeof(pt_IdeDInfo), &lpBytesReturned, 0);

      CloseHandle (VxDHandle);
   }
   else
   for (i=0; i<8; i++)
   {
      if((pOutBufVxD->DiskExists[i]) && (pOutBufVxD->IDEExists[i/2]))
      {
			for (int j = 0; j < 256; j++) diskdata [j] = pOutBufVxD -> DisksRawInfo [i * 256 + j];
			getIDEInfo();
			done = TRUE;
      }
   }

   SetPriorityClass (GetCurrentProcess (), NORMAL_PRIORITY_CLASS);

   return done;
}

#define  SENDIDLENGTH  sizeof (SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE


int DiskInfo::DriveReadAsSCSI (void)
{
   int done = FALSE;
   int controller = 0;

   for (controller = 0; controller < 16; controller++)
   {
      HANDLE hScsiDriveIOCTL = 0;
      TCHAR   driveName [256];

      sprintf (driveName, "\\\\.\\Scsi%d:", controller);
      //  Windows NT, Windows 2000
      hScsiDriveIOCTL = CreateFile (driveName,
                               GENERIC_READ | GENERIC_WRITE, 
                               FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                               OPEN_EXISTING, 0, NULL);


      if (hScsiDriveIOCTL != INVALID_HANDLE_VALUE)
      {
         int drive = 0;

         for (drive = 0; drive < 2; drive++)
         {
            char buffer [sizeof (SRB_IO_CONTROL) + SENDIDLENGTH];
            SRB_IO_CONTROL *p = (SRB_IO_CONTROL *) buffer;
            SENDCMDINPARAMS *pin =
                   (SENDCMDINPARAMS *) (buffer + sizeof (SRB_IO_CONTROL));
            DWORD dummy;
   
            memset (buffer, 0, sizeof (buffer));
            p -> HeaderLength = sizeof (SRB_IO_CONTROL);
            p -> Timeout = 10000;
            p -> Length = SENDIDLENGTH;
            p -> ControlCode = IOCTL_SCSI_MINIPORT_IDENTIFY;
            strncpy ((char *) p -> Signature, "SCSIDISK", 8);
  
            pin -> irDriveRegs.bCommandReg = IDE_ATA_IDENTIFY;
            pin -> bDriveNumber = drive;

            if (DeviceIoControl (hScsiDriveIOCTL, IOCTL_SCSI_MINIPORT, 
                                 buffer,
                                 sizeof (SRB_IO_CONTROL) +
                                         sizeof (SENDCMDINPARAMS) - 1,
                                 buffer,
                                 sizeof (SRB_IO_CONTROL) + SENDIDLENGTH,
                                 &dummy, NULL))
            {
               SENDCMDOUTPARAMS *pOut =
                    (SENDCMDOUTPARAMS *) (buffer + sizeof (SRB_IO_CONTROL));
               IDSECTOR *pId = (IDSECTOR *) (pOut -> bBuffer);
               if (pId -> sModelNumber [0])
               {
                  USHORT *pIdSector = (USHORT *) pId;
                  for (int ii = 0; ii < 256; ii++) diskdata [ii] = pIdSector [ii];
				  getIDEInfo();
                  done = TRUE;
               }
            }
         }
         CloseHandle (hScsiDriveIOCTL);
      }
   }

   return done;
}

char* DiskInfo::ModelNumber ()
{
	//return ConvertToString(diskdata, 27, 46);
	return MN;
}

char* DiskInfo::SerialNumber ()
{
	//return ConvertToString(diskdata, 10, 19);
	return SN;
}

char* DiskInfo::RevisionNumber ()
{
	//return ConvertToString(diskdata, 23, 26);
	return RN;
}

char* DiskInfo::DriveType ()
{
   if (diskdata[0] & 0x0080)
      return "Removable";
   else if (diskdata[0] & 0x0040)
      return "Fixed";
   else return "Unknown";
}

char * DiskInfo::ConvertToString (DWORD diskdatax [256], int firstIndex, int lastIndex)
{
   char string [1024];
   int index = 0;
   int position = 0;

   for (index = firstIndex; index <= lastIndex; index++)
   {
      string [position] = (unsigned char) (diskdatax [index] / 256);
      position++;

      string [position] = (unsigned char) (diskdatax [index] % 256);
      position++;
   }
   string [position] = '\0';
   
   for (index = position - 1; index > 0 && isspace(string [index]); index--)
      string [index] = '\0';
   
   return string;
}

unsigned __int64 DiskInfo::DriveSize ()
{
	unsigned __int64 bytes = 0,sectors =0;
	if (diskdata [83] & 0x400) 
		sectors = diskdata[103] * 65536I64 * 65536I64 * 65536I64 + 
					diskdata[102] * 65536I64 * 65536I64 + 
					diskdata[101] * 65536I64 + 
					diskdata[100];
	else
		sectors = diskdata[61] * 65536 +diskdata[60];
		//  there are 512 bytes in a sector
		bytes = sectors * 512;
	return bytes;
}

DiskInfo::DiskInfo(UINT driveNum)
{
	//m_DriveCount = 0;
	uDriveNum = driveNum;
}

DiskInfo::~DiskInfo(void)
{
}

long DiskInfo::LoadDiskInfo ()
{
	int done = FALSE;
	__int64 id = 0;
	OSVERSIONINFO version;
	memset (&version, 0, sizeof (version));
	version.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
	GetVersionEx (&version);
	if (version.dwPlatformId == VER_PLATFORM_WIN32_NT)
	{
		if (!done)
		{
			//printf("\nTes 1. Admin: ");
			done = DriveReadAdmin ();
		}
		//  this should work in WinNT or Win2K if previous did not work
		//  this is kind of a backdoor via the SCSI mini port driver into
		//     the IDE drives
		
		if (!done)
		{
			//printf("FAILED.\n");
			//printf("\nTes 2. SCSI: ");
			done = DriveReadAsSCSI ();
		}
		//this works under WinNT4 or Win2K or WinXP if you have any rights
		
		if (!done) 
		{
			//printf("FAILED.\n");
			//printf("\nTes 3. No Admin/XP :");
			done = DriveReadNoAdmin ();
		}
		if (!done)
		{
			//printf("FAILED.\n");
			//printf("\nTes 4. Smart :");
			done = DriveReadSMART();
			//if (!done) printf("FAILED.");
		}
	}
	else
	{
		int attempt = 0;
		for (attempt = 0;
			attempt < 10 && !done ;
			attempt++)
			done = DriveReadPort9x ();
	}
	return (long) done;
}

UINT DiskInfo::BufferSize ()
{
	return diskdata[21] * 512;
}