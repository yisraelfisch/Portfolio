#include <stdio.h> /*fopen*/
#include <sys/types.h> /*open*/
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> /*read*/
#include <ext2fs/ext2_fs.h>
#include <stdlib.h> /*malloc,free*/

typedef struct ext2_super_block super_block;
typedef struct ext2_group_desc bg_descriptor;
typedef struct ext2_inode inode;
typedef struct ext2_dir_entry_2 dir_entry;


#define BLOCK_OFFSET(block)  block*4096

static void ReadInode(int fd, int inode_no, struct ext2_group_desc *group, struct ext2_inode *inode)
{
	lseek(fd, BLOCK_OFFSET(group->bg_inode_table)+(inode_no)*sizeof(struct ext2_inode), SEEK_SET);
	read(fd, inode, sizeof(struct ext2_inode));
}

static void ReadFileInode(int fd, int inode_no, struct ext2_group_desc *group, struct ext2_inode *inode)
{
	lseek(fd, BLOCK_OFFSET(group->bg_inode_table)+(inode_no-1)*256, SEEK_SET);
	read(fd, inode, sizeof(struct ext2_inode));
}

int main()
{
    super_block sb_buff = {0};
    bg_descriptor bg_buff = {0};
    inode root_inode = {0};
    inode string_inode = {0};
    int fd_ram0 = 0;
    int block_size = 0;
    int i_node_size = 0;

    /*read super block*/
    fd_ram0 = open("/dev/ram0", O_RDONLY);
    lseek(fd_ram0, 1024, SEEK_SET);
    read(fd_ram0, &sb_buff, sizeof(super_block));
   
    block_size = 1024<<sb_buff.s_log_block_size;
    i_node_size = sb_buff.s_inode_size;
    printf("block size is: %d\n", block_size);
    printf("i node size is: %d\n", i_node_size);
    printf("operator system  is: %s\n", !sb_buff.s_creator_os ? "linux": "not linux");
    printf("number of free blocks is: %d\n", sb_buff.s_free_blocks_count);
    
    /*read file block-group discriptors*/
    lseek(fd_ram0, 1024*2, SEEK_CUR);
    read(fd_ram0, &bg_buff, sizeof(bg_descriptor));
    
    printf("number of free blocks is: %d\n", bg_buff.bg_free_blocks_count);
    printf("size of group duscriptor is:%ld\n", sizeof(bg_buff));
    printf("i_block bit map block starts at %d\n", bg_buff.bg_block_bitmap);
    printf("i_node bit map block starts at %d\n", bg_buff.bg_inode_bitmap);
    printf("i_node table block starts at %d\n", bg_buff.bg_inode_table);
    
    /*read root inode*/
    ReadInode(fd_ram0, 2, &bg_buff, &root_inode);
    
    dir_entry *entry = NULL;
    unsigned int size = 0;
    unsigned char block[block_size];
    
    printf("mode is %d\n", root_inode.i_mode );
    printf("uid is %d\n", root_inode.i_uid );
    printf("size is %d\n", root_inode.i_size );
    printf("block count is %d\n", root_inode.i_blocks );
    printf("%d\n", S_ISDIR(root_inode.i_mode));
    S_ISDIR(root_inode.i_mode);


    /*print file names*/
    lseek(fd_ram0, BLOCK_OFFSET(root_inode.i_block[0]), SEEK_SET);
    read(fd_ram0, block, block_size);
    entry = (dir_entry *)block;

    while(size < root_inode.i_size)
    {
        printf("%10u %.*s\n", entry->inode, entry->name_len, entry->name);
        size += entry->rec_len;
        entry = (dir_entry *)((char *)entry + entry->rec_len);
    }

    /*print a file's content(the first block)*/

    ReadFileInode(fd_ram0, 12, &bg_buff, &string_inode);
    lseek(fd_ram0, BLOCK_OFFSET(string_inode.i_block[0]), SEEK_SET);
    read(fd_ram0, block, block_size);
    printf("%s\n" ,(char*)block);
   


    return 0;
}