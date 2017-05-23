#ifndef GLUE_H
#define GLUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

typedef uint8_t u_int8_t;
typedef uint16_t u_int16_t;
typedef uint32_t u_int32_t;
typedef uint64_t db_alignp_t;


typedef struct __db_lsn {
        u_int32_t       file;           /* File ID. */
        u_int32_t       offset;         /* File offset. */
} DB_LSN;

typedef struct __db {
        u_int32_t pgsize;               /* Database logical page size. */
	char *fname;
	int flags;
#define DB_PFX_COMP           0x0000001
#define DB_SFX_COMP           0x0000002
#define DB_RLE_COMP           0x0000004
	uint8_t compression_flags;
	int offset_bias;
} DB;

typedef struct {
	void	 *data;
	u_int32_t size;
	u_int32_t flags;
} DBT;

typedef struct {
	DB *dbp;
	void *internal;
} DBC;

typedef u_int32_t       db_pgno_t;      /* Page number type. */
typedef u_int16_t       db_indx_t;      /* Page offset type. */
typedef u_int32_t       db_recno_t;     /* Record number type. */

#define DB_RENAMEMAGIC  0x030800        /* File has been renamed. */
#define DB_BTREEMAGIC   0x053162
#define DB_HASHMAGIC    0x061561
#define DB_QAMMAGIC     0x042253

#define DB_AM_CHKSUM            0x00000001 /* Checksumming. */
#define DB_AM_ENCRYPT           0x00000800 /* Encryption. */
#define DB_AM_SWAP              0x10000000 /* Pages need to be byte-swapped. */
#define DB_FILE_ID_LEN          20      /* Unique file ID length. */
#define DB_IV_BYTES     16              /* Bytes per IV */
#define DB_MAC_KEY      20              /* Bytes per MAC checksum */

#define SSZ(name, field)  P_TO_UINT16(&(((name *)0)->field))
#define SSZA(name, field) P_TO_UINT16(&(((name *)0)->field[0]))

/* Set, clear and test flags. */
#define FLD_CLR(fld, f)         (fld) &= ~(f)
#define FLD_ISSET(fld, f)       ((fld) & (f))
#define FLD_SET(fld, f)         (fld) |= (f)
#define F_CLR(p, f)             (p)->flags &= ~(f)
#define F_ISSET(p, f)           ((p)->flags & (f))
#define F_SET(p, f)             (p)->flags |= (f)
#define LF_CLR(f)               ((flags) &= ~(f))
#define LF_ISSET(f)             ((flags) & (f))
#define LF_SET(f)               ((flags) |= (f))

#define ISLEAF(p)       (TYPE(p) == P_LBTREE || TYPE(p) == P_LRECNO || TYPE(p) == P_LDUP)
#define P_TO_UINT16(p)  ((u_int16_t)(db_alignp_t)(p))

#include <dbinc/db_page.h>
#include <btree/bt_prefix.h>

typedef struct {
	PAGE *page;
	db_indx_t indx;
	DB_LSN pagelsn;
} BTREE_CURSOR;

//void inspect_page(DB *, PAGE *);
//const char *type2str(int type);

#define __bam_prefix_log(...) 1
#define __bam_bulk_overflow(...) 1

typedef unsigned long long db_align_t;
#define ALIGN(v, bound) (((v) + (bound) - 1) & ~(((db_align_t)bound) - 1))


typedef struct {
	DBT prvpfx;
	DBT newpfx;
	int ntype;
	int ptype;
} __bam_prefix_args;

#define __os_calloc(_, n, s, r) ((*(r) = calloc((n), (s))) ? 0 : 1)
#define __os_free(_, m) free(m)

#ifdef __cplusplus
}
#endif
#define __memp_fset(...)
#endif //GLUE_H
