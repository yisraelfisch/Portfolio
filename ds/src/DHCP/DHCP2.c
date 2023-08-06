/*********************************
 * Reviewer: 				
 * Author: Yisrael Fisch 			
 * File: DHCP.c					
 * ******************************/
 
 /**/

#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc & free, atoi*/
#include <arpa/inet.h>/*inet_network*/
#include <math.h> /* pow */
#include <stdio.h>
#include "DHCP.h"
/*******Defines******/
typedef struct dhcp_node dhcp_node_t;


/*******Structs******/
struct dhcp_node
{
    dhcp_node_t *child[2];
    int is_occupied;
};

struct dhcp
{
    dhcp_node_t *root;
    ip_address_t ip_address;
    int host_mask;
};



/*******Service Funcs******/
static dhcp_node_t *CreateNode();
static void RemoveNode(dhcp_node_t *dhcp_node);
static int TrieInit(dhcp_t *dhcp);
static void RecurDHCPNodeDestroy(dhcp_node_t *dhcp_node);
static ip_address_t RecursiveAlloc(dhcp_node_t *node,  int level, ip_address_t address);
static int IsChildrenOccupied(dhcp_node_t *node);
static size_t RecursiveCountFree(dhcp_node_t *node, int level);
static int RecursiveFreeIp(dhcp_node_t *node, ip_address_t ip, int level);
static dhcp_node_t *RecursiveRenewIP(dhcp_node_t *node, ip_address_t ip, int level);

/*******Funcs Funcs******/
dhcp_t *DHCPCreate(const char *net_address, int net_mask)
{
    dhcp_t *dhcp = NULL;
    ip_address_t ip_address = 0;

    dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
    if(!dhcp)
    {
        return NULL;
    }

    ip_address = inet_network(net_address);
    if(ip_address == (unsigned)-1)
    {
        return NULL;
    }

    dhcp->root = CreateNode();
    
    if(!dhcp->root)
    {
        free(dhcp);
        return NULL;
    }

    dhcp->ip_address = ip_address;
    dhcp->host_mask = (sizeof(unsigned int))*8 - net_mask;
    /*init tha base trie*/
    if(TrieInit(dhcp))
    {
        return NULL;
    }

    return dhcp;
}

void DHCPDestroy(dhcp_t *dhcp)
{
    assert(dhcp);
    RecurDHCPNodeDestroy(dhcp->root);

    dhcp->root = NULL;
    dhcp->host_mask = 0;
    dhcp->ip_address = 0;

    free(dhcp);
}

static void RecurDHCPNodeDestroy(dhcp_node_t *dhcp_node)
{
    if(!dhcp_node)
    {
        return;
    }
    RecurDHCPNodeDestroy(dhcp_node->child[0]);
    RecurDHCPNodeDestroy(dhcp_node->child[1]);

    RemoveNode(dhcp_node);
}

static dhcp_node_t *CreateNode()
{
        dhcp_node_t *dhcp_node = NULL;

        dhcp_node = (dhcp_node_t *)malloc(sizeof(dhcp_node_t));
        if(!dhcp_node)
        {
            return NULL;
        }

        dhcp_node->child[0]= NULL;
        dhcp_node->child[1]= NULL;
        dhcp_node->is_occupied = 0;

    return dhcp_node;
}

static void RemoveNode(dhcp_node_t *dhcp_node)
{
        dhcp_node->child[0]= NULL;
        dhcp_node->child[1]= NULL;
        dhcp_node->is_occupied = 0;

        free(dhcp_node);
        dhcp_node = NULL;
}

static int TrieInit(dhcp_t *dhcp)
{
    dhcp_node_t *dhcp_node = dhcp->root;
    int height = dhcp->host_mask;
    int i = 0;

    for(i = 0; i < height; ++i)
    {
        dhcp_node->child[0] = CreateNode();
        if(!dhcp_node->child[0])
        {
            DHCPDestroy(dhcp);
            return 1;
        }
        dhcp_node =  dhcp_node->child[0];
    }

    dhcp_node->is_occupied = 1;


    for(i = 0; i < height -1; ++i)
    {
        dhcp_node->child[1] = CreateNode();
        if(!dhcp_node->child[1])
        {
            DHCPDestroy(dhcp);
            return 1;
        }
        dhcp_node =  dhcp_node->child[1];
    }

    dhcp_node->is_occupied = 1;

    return 0;
}

ip_address_t DHCPAllocateIp(dhcp_t *dhcp)
{
    ip_address_t address = 0;
    address = RecursiveAlloc(dhcp->root, dhcp->host_mask, address);
    if(address == (ip_address_t)-1)
    {
        return (ip_address_t)-1;
    }

    return address | dhcp->ip_address;
}


static ip_address_t RecursiveAlloc(dhcp_node_t *node,  int level, ip_address_t address)
{
    if(!level)
    {
        node->is_occupied = 1;
        return address;
    }

    if(!node->child[0])
    {
        if(!(node->child[0] = CreateNode()))
        {
            return -1;
        }
        
        address <<= 1;

        address = RecursiveAlloc(node->child[0], --level, address);
        if(IsChildrenOccupied(node))
        {
            node->is_occupied = 1;
        }
        return address;
    }
    if(!(node->child[0]->is_occupied))
    {
        address <<= 1;
        address = RecursiveAlloc(node->child[0], --level, address);
        if(IsChildrenOccupied(node))
        {
            node->is_occupied = 1;
        }
        return address;
    }

    if(!node->child[1])
    {
        if(!(node->child[1] = CreateNode()))
        {
            return -1;
        }
        address <<= 1;
        address |= 1;

        address = RecursiveAlloc(node->child[1], --level, address);
        if(IsChildrenOccupied(node))
        {
            node->is_occupied = 1;
        }
        return address;
    }
    if(!(node->child[1]->is_occupied))
    {
        address <<= 1;
        address |= 1;
        address = RecursiveAlloc(node->child[1], --level, address);
        if(IsChildrenOccupied(node))
        {
            node->is_occupied = 1;
        }
        return address;
    }

    return -1;
}


static int IsChildrenOccupied(dhcp_node_t *node)
{
    if(node->child[0] && node->child[1])
    {
        return node->child[0]->is_occupied && node->child[1]->is_occupied; 
    }

    return 0;
}

size_t DHCPCountFree(dhcp_t *dhcp)
{
    return pow(2, dhcp->host_mask) - (RecursiveCountFree(dhcp->root, dhcp->host_mask) + 2);
}

static size_t RecursiveCountFree(dhcp_node_t *node, int level)
{
    if(!node)
    {
        return 0;
    }
    
    if(!level)
    {
        return 1;
    }
    
    return RecursiveCountFree(node->child[0], level - 1) + RecursiveCountFree(node->child[1], level - 1);
}


int DHCPRenewIP(dhcp_t *dhcp, ip_address_t ip)
{
    return !RecursiveRenewIP(dhcp->root, ip, dhcp->host_mask);
}

static dhcp_node_t *RecursiveRenewIP(dhcp_node_t *node, ip_address_t ip, int level)
{
    if(!node)
    {
        return NULL;
    }
    
    if(!level)
    {
        return node;
    }

    return RecursiveRenewIP(node->child[(ip >> (level - 1)) & 1], ip, level -1);
}


int DHCPFreeIp(dhcp_t *dhcp, ip_address_t ip)
{
    return RecursiveFreeIp(dhcp->root, ip, dhcp->host_mask);
}

static int RecursiveFreeIp(dhcp_node_t *node, ip_address_t ip, int level)
{
    int index = (ip >> (level - 1)) & 1;
    int res = 0;

    if(!node->child[index])
    {
        return 1;
    }
    
    if(level == 1)
    {

        RemoveNode(node->child[index]);
        node->child[index] = NULL;
    
        return 0;
    }

    res = RecursiveFreeIp(node->child[index], ip, level -1);
    
    if((node->child[index]->child[0] || node->child[index]->child[1]))
    {
        node->child[index]->is_occupied = 0;

        return res;
    }

    RemoveNode(node->child[index]);
    node->child[index] = NULL;

    return res;
}















