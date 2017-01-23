
#include <et/com_err.h>

#define PROF_VERSION                             (-1429577728L)
#define PROF_MAGIC_NODE                          (-1429577727L)
#define PROF_NO_SECTION                          (-1429577726L)
#define PROF_NO_RELATION                         (-1429577725L)
#define PROF_ADD_NOT_SECTION                     (-1429577724L)
#define PROF_SECTION_WITH_VALUE                  (-1429577723L)
#define PROF_BAD_LINK_LIST                       (-1429577722L)
#define PROF_BAD_GROUP_LVL                       (-1429577721L)
#define PROF_BAD_PARENT_PTR                      (-1429577720L)
#define PROF_MAGIC_ITERATOR                      (-1429577719L)
#define PROF_SET_SECTION_VALUE                   (-1429577718L)
#define PROF_EINVAL                              (-1429577717L)
#define PROF_READ_ONLY                           (-1429577716L)
#define PROF_SECTION_NOTOP                       (-1429577715L)
#define PROF_SECTION_SYNTAX                      (-1429577714L)
#define PROF_RELATION_SYNTAX                     (-1429577713L)
#define PROF_EXTRA_CBRACE                        (-1429577712L)
#define PROF_MISSING_OBRACE                      (-1429577711L)
#define PROF_MAGIC_PROFILE                       (-1429577710L)
#define PROF_MAGIC_SECTION                       (-1429577709L)
#define PROF_TOPSECTION_ITER_NOSUPP              (-1429577708L)
#define PROF_INVALID_SECTION                     (-1429577707L)
#define PROF_END_OF_SECTIONS                     (-1429577706L)
#define PROF_BAD_NAMESET                         (-1429577705L)
#define PROF_NO_PROFILE                          (-1429577704L)
#define PROF_MAGIC_FILE                          (-1429577703L)
#define PROF_FAIL_OPEN                           (-1429577702L)
#define PROF_EXISTS                              (-1429577701L)
#define PROF_BAD_BOOLEAN                         (-1429577700L)
#define PROF_BAD_INTEGER                         (-1429577699L)
#define PROF_MAGIC_FILE_DATA                     (-1429577698L)
extern const struct error_table et_prof_error_table;
extern void initialize_prof_error_table(void);

extern void initialize_prof_error_table_r(struct et_list **list);

#define ERROR_TABLE_BASE_prof (-1429577728L)

#define init_prof_err_tbl initialize_prof_error_table
#define prof_err_base ERROR_TABLE_BASE_prof
