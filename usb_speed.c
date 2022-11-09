#include<winusb.h>
#include<Windows.h>
#include<stdio.h>

BOOL GetUSBDeviceSpeed(WINUSB_INTERFACE_HANDLE hDeviceHandle, const UCHAR* pDeviceSpeed) {
	if (!pDeviceSpeed || hDeviceHandle == INVALID_HANDLE_VALUE) {
		return FALSE;
	}

	BOOL bResult = TRUE;
	ULONG length = sizeof(UCHAR);

	bResult = WinUsb_QueryDeviceInformation(hDeviceHandle, DEVICE_SPEED, &length, pDeviceSpeed);

	if (bResult) {
		printf("Error getting device speed: %d.\n", (int)GetLastError());
	}

	if (*pDeviceSpeed == LowSpeed)
	{
		printf("Device speed: %d (Low speed).\n", *pDeviceSpeed);
		goto done;
	}

	if (*pDeviceSpeed == FullSpeed)
	{
		printf("Device speed: %d (Full speed).\n", *pDeviceSpeed);
		goto done;
	}

	if (*pDeviceSpeed == HighSpeed)
	{
		printf("Device speed: %d (High speed).\n", *pDeviceSpeed);
		goto done;
	}

done:
	return bResult;
}

//CONTINUE TMRW! https://learn.microsoft.com/en-us/windows-hardware/drivers/usbcon/using-winusb-api-to-communicate-with-a-usb-device