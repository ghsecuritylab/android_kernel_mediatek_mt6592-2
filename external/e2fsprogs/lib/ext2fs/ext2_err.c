
#include <stdlib.h>

#define N_(a) a

static const char * const text[] = {
	N_(	"EXT2FS Library version 1.42.9"),
	N_(	"Wrong magic number for ext2_filsys structure"),
	N_(	"Wrong magic number for badblocks_list structure"),
	N_(	"Wrong magic number for badblocks_iterate structure"),
	N_(	"Wrong magic number for inode_scan structure"),
	N_(	"Wrong magic number for io_channel structure"),
	N_(	"Wrong magic number for unix io_channel structure"),
	N_(	"Wrong magic number for io_manager structure"),
	N_(	"Wrong magic number for block_bitmap structure"),
	N_(	"Wrong magic number for inode_bitmap structure"),
	N_(	"Wrong magic number for generic_bitmap structure"),
	N_(	"Wrong magic number for test io_channel structure"),
	N_(	"Wrong magic number for directory block list structure"),
	N_(	"Wrong magic number for icount structure"),
	N_(	"Wrong magic number for Powerquest io_channel structure"),
	N_(	"Wrong magic number for ext2 file structure"),
	N_(	"Wrong magic number for Ext2 Image Header"),
	N_(	"Wrong magic number for inode io_channel structure"),
	N_(	"Wrong magic number for ext4 extent handle"),
	N_(	"Bad magic number in super-block"),
	N_(	"Filesystem revision too high"),
	N_(	"Attempt to write to filesystem opened read-only"),
	N_(	"Can't read group descriptors"),
	N_(	"Can't write group descriptors"),
	N_(	"Corrupt group descriptor: bad block for block bitmap"),
	N_(	"Corrupt group descriptor: bad block for inode bitmap"),
	N_(	"Corrupt group descriptor: bad block for inode table"),
	N_(	"Can't write an inode bitmap"),
	N_(	"Can't read an inode bitmap"),
	N_(	"Can't write a block bitmap"),
	N_(	"Can't read a block bitmap"),
	N_(	"Can't write an inode table"),
	N_(	"Can't read an inode table"),
	N_(	"Can't read next inode"),
	N_(	"Filesystem has unexpected block size"),
	N_(	"EXT2 directory corrupted"),
	N_(	"Attempt to read block from filesystem resulted in short read"),
	N_(	"Attempt to write block to filesystem resulted in short write"),
	N_(	"No free space in the directory"),
	N_(	"Inode bitmap not loaded"),
	N_(	"Block bitmap not loaded"),
	N_(	"Illegal inode number"),
	N_(	"Illegal block number"),
	N_(	"Internal error in ext2fs_expand_dir"),
	N_(	"Not enough space to build proposed filesystem"),
	N_(	"Illegal block number passed to ext2fs_mark_block_bitmap"),
	N_(	"Illegal block number passed to ext2fs_unmark_block_bitmap"),
	N_(	"Illegal block number passed to ext2fs_test_block_bitmap"),
	N_(	"Illegal inode number passed to ext2fs_mark_inode_bitmap"),
	N_(	"Illegal inode number passed to ext2fs_unmark_inode_bitmap"),
	N_(	"Illegal inode number passed to ext2fs_test_inode_bitmap"),
	N_(	"Attempt to fudge end of block bitmap past the real end"),
	N_(	"Attempt to fudge end of inode bitmap past the real end"),
	N_(	"Illegal indirect block found" ),
	N_(	"Illegal doubly indirect block found" ),
	N_(	"Illegal triply indirect block found" ),
	N_(	"Block bitmaps are not the same"),
	N_(	"Inode bitmaps are not the same"),
	N_(	"Illegal or malformed device name"),
	N_(	"A block group is missing an inode table"),
	N_(	"The ext2 superblock is corrupt"),
	N_(	"Illegal generic bit number passed to ext2fs_mark_generic_bitmap"),
	N_(	"Illegal generic bit number passed to ext2fs_unmark_generic_bitmap"),
	N_(	"Illegal generic bit number passed to ext2fs_test_generic_bitmap"),
	N_(	"Too many symbolic links encountered."),
	N_(	"The callback function will not handle this case"),
	N_(	"The inode is from a bad block in the inode table"),
	N_(	"Filesystem has unsupported feature(s)"),
	N_(	"Filesystem has unsupported read-only feature(s)"),
	N_(	"IO Channel failed to seek on read or write"),
	N_(	"Memory allocation failed"),
	N_(	"Invalid argument passed to ext2 library"),
	N_(	"Could not allocate block in ext2 filesystem"),
	N_(	"Could not allocate inode in ext2 filesystem"),
	N_(	"Ext2 inode is not a directory"),
	N_(	"Too many references in table"),
	N_(	"File not found by ext2_lookup"),
	N_(	"File open read-only"),
	N_(	"Ext2 directory block not found"),
	N_(	"Ext2 directory already exists"),
	N_(	"Unimplemented ext2 library function"),
	N_(	"User cancel requested"),
	N_(	"Ext2 file too big"),
	N_(	"Supplied journal device not a block device"),
	N_(	"Journal superblock not found"),
	N_(	"Journal must be at least 1024 blocks"),
	N_(	"Unsupported journal version"),
	N_(	"Error loading external journal"),
	N_(	"Journal not found"),
	N_(	"Directory hash unsupported"),
	N_(	"Illegal extended attribute block number"),
	N_(	"Cannot create filesystem with requested number of inodes"),
	N_(	"E2image snapshot not in use"),
	N_(	"Too many reserved group descriptor blocks"),
	N_(	"Resize inode is corrupt"),
	N_(	"Tried to set block bmap with missing indirect block"),
	N_(	"TDB: Success"),
	N_(	"TDB: Corrupt database"),
	N_(	"TDB: IO Error"),
	N_(	"TDB: Locking error"),
	N_(	"TDB: Out of memory"),
	N_(	"TDB: Record exists"),
	N_(	"TDB: Lock exists on other keys"),
	N_(	"TDB: Invalid parameter"),
	N_(	"TDB: Record does not exist"),
	N_(	"TDB: Write not permitted"),
	N_(	"Ext2fs directory block list is empty"),
	N_(	"Attempt to modify a block mapping via a read-only block iterator"),
	N_(	"Wrong magic number for ext4 extent saved path"),
	N_(	"Wrong magic number for 64-bit generic bitmap"),
	N_(	"Wrong magic number for 64-bit block bitmap"),
	N_(	"Wrong magic number for 64-bit inode bitmap"),
	N_(	"Wrong magic number --- RESERVED_13"),
	N_(	"Wrong magic number --- RESERVED_14"),
	N_(	"Wrong magic number --- RESERVED_15"),
	N_(	"Wrong magic number --- RESERVED_16"),
	N_(	"Wrong magic number --- RESERVED_17"),
	N_(	"Wrong magic number --- RESERVED_18"),
	N_(	"Wrong magic number --- RESERVED_19"),
	N_(	"Corrupt extent header"),
	N_(	"Corrupt extent index"),
	N_(	"Corrupt extent"),
	N_(	"No free space in extent map"),
	N_(	"Inode does not use extents"),
	N_(	"No 'next' extent"),
	N_(	"No 'previous' extent"),
	N_(	"No 'up' extent"),
	N_(	"No 'down' extent"),
	N_(	"No current node"),
	N_(	"Ext2fs operation not supported"),
	N_(	"No room to insert extent in node"),
	N_(	"Splitting would result in empty node"),
	N_(	"Extent not found"),
	N_(	"Operation not supported for inodes containing extents"),
	N_(	"Extent length is invalid"),
	N_(	"I/O Channel does not support 64-bit block numbers"),
	N_(	"Can't check if filesystem is mounted due to missing mtab file"),
	N_(	"Filesystem too large to use legacy bitmaps"),
	N_(	"MMP: invalid magic number"),
	N_(	"MMP: device currently active"),
	N_(	"MMP: fsck being run"),
	N_(	"MMP: block number beyond filesystem range"),
	N_(	"MMP: undergoing an unknown operation"),
	N_(	"MMP: filesystem still in use"),
	N_(	"MMP: open with O_DIRECT failed"),
	N_(	"Block group descriptor size incorrect"),
	N_(	"Inode checksum does not match inode"),
	N_(	"Inode bitmap checksum does not match bitmap"),
	N_(	"Extent block checksum does not match extent block"),
	N_(	"Directory block does not have space for checksum"),
	N_(	"Directory block checksum does not match directory block"),
	N_(	"Extended attribute block checksum does not match block"),
	N_(	"Superblock checksum does not match superblock"),
	N_(	"Unknown checksum algorithm"),
	N_(	"MMP block checksum does not match MMP block"),
	N_(	"Ext2 file already exists"),
    0
};

struct error_table {
    char const * const * msgs;
    long base;
    int n_msgs;
};
struct et_list {
    struct et_list *next;
    const struct error_table * table;
};
extern struct et_list *_et_list;

const struct error_table et_ext2_error_table = { text, 2133571328L, 156 };

static struct et_list link = { 0, 0 };

void initialize_ext2_error_table_r(struct et_list **list);
void initialize_ext2_error_table(void);

void initialize_ext2_error_table(void) {
    initialize_ext2_error_table_r(&_et_list);
}

void initialize_ext2_error_table_r(struct et_list **list)
{
    struct et_list *et, **end;

    for (end = list, et = *list; et; end = &et->next, et = et->next)
        if (et->table->msgs == text)
            return;
    et = malloc(sizeof(struct et_list));
    if (et == 0) {
        if (!link.table)
            et = &link;
        else
            return;
    }
    et->table = &et_ext2_error_table;
    et->next = 0;
    *end = et;
}
