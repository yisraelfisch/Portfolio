/*********************************
 * Reviewer: 				
 * Author: Yisrael Fisch			
 * File: DHCP_test.c				
 * ******************************/

#include <stdio.h> /* printf */
#include <arpa/inet.h> /* inet_network */
#include "DHCP.h" 


void TestCreate();

int main()
{
	TestCreate();

	return 0;
}

void TestCreate()
{
	dhcp_t *dhcp = NULL;
	ip_address_t test = 0;
	int return_value = 0;


	dhcp = DHCPCreate("192.168.1.0", 24);

	test = DHCPAllocateIp(dhcp);

	if (test != inet_network("192.168.1.1"))
	{
		printf("TestCreate failed (alloc) on line %d\n", __LINE__);
		printf("test = %u inet_network = %u\n", test, inet_network("192.168.1.1"));
	}

	if (!DHCPRenewIP(dhcp, inet_network("192.168.1.2")))
	{
		printf("TestCreate failed (renew not found) on line %d\n", __LINE__);
	}

	if (252 != DHCPCountFree(dhcp))
	{
		printf("TestCreate failed (count free) on line %d\n", __LINE__);
	}

	while (DHCPCountFree(dhcp))
	{
		test = DHCPAllocateIp(dhcp);

		if (test == inet_network("255.255.255.255"))
		{
			printf("TestCreate failed (alloc) on line %d\n", __LINE__);
		}

	}

	if (test != inet_network("192.168.1.253"))
	{
		printf("TestCreate failed (alloc) on line %d\n", __LINE__);
		printf("test = %u inet_network = %u\n", test, inet_network("192.168.1.253"));
	}

	if (!DHCPRenewIP(dhcp, inet_network("192.168.1.255")))
	{
		printf("TestCreate failed (renew found) on line %d\n", __LINE__);
	}

	test = DHCPAllocateIp(dhcp);

	if (test != inet_network("255.255.255.255"))
	{
		printf("TestCreate failed (alloc) on line %d\n", __LINE__);
		printf("test = %u inet_network = %u\n", test, inet_network("255.255.255.255"));
	}

	if (0 != DHCPCountFree(dhcp))
	{
		printf("TestCreate failed (count free) on line %d\n", __LINE__);
	}

	if ((return_value = DHCPFreeIp(dhcp, inet_network("192.168.1.17"))))
	{
		printf("TestCreate failed (free) on line %d\n", __LINE__);
	}

	if (!(return_value = DHCPFreeIp(dhcp, inet_network("192.168.1.17"))))
	{
		printf("TestCreate failed (free) on line %d\n", __LINE__);
	}

	if (!DHCPRenewIP(dhcp, inet_network("192.168.1.17")))
	{
		printf("TestCreate failed (free) on line %d\n", __LINE__);
	}

	if (1 != DHCPCountFree(dhcp))
	{
		printf("TestCreate failed (count free after free) on line %d\n", __LINE__);
	}

	test = DHCPAllocateIp(dhcp);

	if (test != inet_network("192.168.1.17"))
	{
		printf("TestCreate failed (alloc) on line %d\n", __LINE__);
		printf("test = %u inet_network = %u\n", test, inet_network("192.168.1.17"));
	}

	if (DHCPCountFree(dhcp))
	{
		printf("TestCreate failed (count free after free) on line %d\n", __LINE__);
	}

	DHCPDestroy(dhcp);
}