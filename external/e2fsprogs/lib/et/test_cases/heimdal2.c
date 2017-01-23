
#include <stdlib.h>

#define N_(a) a

static const char * const text[] = {
	N_("$Id: kadm_err.et,v 1.5 1998/01/16 23:11:27 joda Exp $"),
	N_("Cannot fetch local realm"),
	N_("Unable to fetch credentials"),
	N_("Bad key supplied"),
	N_("Can't encrypt data"),
	N_("Cannot encode/decode authentication info"),
	N_("Principal attemping change is in wrong realm"),
	N_("Packet is too large"),
	N_("Version number is incorrect"),
	N_("Checksum does not match"),
	N_("Unsealing private data failed"),
	N_("Unsupported operation"),
	N_("Could not find administrating host"),
	N_("Administrating host name is unknown"),
	N_("Could not find service name in services database"),
	N_("Could not create socket"),
	N_("Could not connect to server"),
	N_("Could not fetch local socket address"),
	N_("Could not fetch master key"),
	N_("Could not verify master key"),
	N_("Entry already exists in database"),
	N_("Database store error"),
	N_("Database read error"),
	N_("Insufficient access to perform requested operation"),
	N_("Data is available for return to client"),
	N_("No such entry in the database"),
	N_("Memory exhausted"),
	N_("Could not fetch system hostname"),
	N_("Could not bind port"),
	N_("Length mismatch problem"),
	N_("Illegal use of wildcard"),
	N_("Database is locked or in use--try again later"),
	N_("Insecure password rejected"),
	N_("Cleartext password and DES key did not match"),
	N_("Invalid principal for change srvtab request"),
	N_("Attempt do delete immutable principal"),
	N_("Reserved kadm error (36)"),
	N_("Reserved kadm error (37)"),
	N_("Reserved kadm error (38)"),
	N_("Reserved kadm error (39)"),
	N_("Reserved kadm error (40)"),
	N_("Reserved kadm error (41)"),
	N_("Reserved kadm error (42)"),
	N_("Reserved kadm error (43)"),
	N_("Reserved kadm error (44)"),
	N_("Reserved kadm error (45)"),
	N_("Reserved kadm error (46)"),
	N_("Reserved kadm error (47)"),
	N_("Reserved kadm error (48)"),
	N_("Reserved kadm error (49)"),
	N_("Reserved kadm error (50)"),
	N_("Reserved kadm error (51)"),
	N_("Reserved kadm error (52)"),
	N_("Reserved kadm error (53)"),
	N_("Reserved kadm error (54)"),
	N_("Reserved kadm error (55)"),
	N_("Reserved kadm error (56)"),
	N_("Reserved kadm error (57)"),
	N_("Reserved kadm error (58)"),
	N_("Reserved kadm error (59)"),
	N_("Reserved kadm error (60)"),
	N_("Reserved kadm error (61)"),
	N_("Reserved kadm error (62)"),
	N_("Reserved kadm error (63)"),
	N_("Null passwords are not allowed"),
	N_("Password is too short"),
	N_("Too few character classes in password"),
	N_("Password is in the password dictionary"),
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

const struct error_table et_kadm_error_table = { text, -1783126272L, 68 };

static struct et_list link = { 0, 0 };

void initialize_kadm_error_table_r(struct et_list **list);
void initialize_kadm_error_table(void);

void initialize_kadm_error_table(void) {
    initialize_kadm_error_table_r(&_et_list);
}

void initialize_kadm_error_table_r(struct et_list **list)
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
    et->table = &et_kadm_error_table;
    et->next = 0;
    *end = et;
}
