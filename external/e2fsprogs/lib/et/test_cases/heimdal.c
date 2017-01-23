
#include <stdlib.h>

#define N_(a) a

static const char * const text[] = {
	N_("Kerberos successful"),
	N_("Kerberos principal expired"),
	N_("Kerberos service expired"),
	N_("Kerberos auth expired"),
	N_("Incorrect kerberos master key version"),
	N_("Incorrect kerberos master key version"),
	N_("Incorrect kerberos master key version"),
	N_("Kerberos error: byte order unknown"),
	N_("Kerberos principal unknown"),
	N_("Kerberos principal not unique"),
	N_("Kerberos principal has null key"),
	N_("Reserved krb error (11)"),
	N_("Reserved krb error (12)"),
	N_("Reserved krb error (13)"),
	N_("Reserved krb error (14)"),
	N_("Reserved krb error (15)"),
	N_("Reserved krb error (16)"),
	N_("Reserved krb error (17)"),
	N_("Reserved krb error (18)"),
	N_("Reserved krb error (19)"),
	N_("Generic error from Kerberos KDC"),
	N_("Can't read Kerberos ticket file"),
	N_("Can't find Kerberos ticket or TGT"),
	N_("Reserved krb error (23)"),
	N_("Reserved krb error (24)"),
	N_("Reserved krb error (25)"),
	N_("Kerberos TGT Expired"),
	N_("Reserved krb error (27)"),
	N_("Reserved krb error (28)"),
	N_("Reserved krb error (29)"),
	N_("Reserved krb error (30)"),
	N_("Kerberos error: Can't decode authenticator"),
	N_("Kerberos ticket expired"),
	N_("Kerberos ticket not yet valid"),
	N_("Kerberos error: Repeated request"),
	N_("The kerberos ticket isn't for us"),
	N_("Kerberos request inconsistent"),
	N_("Kerberos error: delta_t too big"),
	N_("Kerberos error: incorrect net address"),
	N_("Kerberos protocol version mismatch"),
	N_("Kerberos error: invalid msg type"),
	N_("Kerberos error: message stream modified"),
	N_("Kerberos error: message out of order"),
	N_("Kerberos error: unauthorized request"),
	N_("Reserved krb error (44)"),
	N_("Reserved krb error (45)"),
	N_("Reserved krb error (46)"),
	N_("Reserved krb error (47)"),
	N_("Reserved krb error (48)"),
	N_("Reserved krb error (49)"),
	N_("Reserved krb error (50)"),
	N_("Kerberos error: current PW is null"),
	N_("Kerberos error: Incorrect current password"),
	N_("Kerberos protocol error"),
	N_("Error returned by Kerberos KDC"),
	N_("Null Kerberos ticket returned by KDC"),
	N_("Kerberos error: Retry count exceeded"),
	N_("Kerberos error: Can't send request"),
	N_("Reserved krb error (58)"),
	N_("Reserved krb error (59)"),
	N_("Reserved krb error (60)"),
	N_("Kerberos error: not all tickets returned"),
	N_("Kerberos error: incorrect password"),
	N_("Kerberos error: Protocol Error"),
	N_("Reserved krb error (64)"),
	N_("Reserved krb error (65)"),
	N_("Reserved krb error (66)"),
	N_("Reserved krb error (67)"),
	N_("Reserved krb error (68)"),
	N_("Reserved krb error (69)"),
	N_("Other error"),
	N_("Don't have Kerberos ticket-granting ticket"),
	N_("Reserved krb error (72)"),
	N_("Reserved krb error (73)"),
	N_("Reserved krb error (74)"),
	N_("Reserved krb error (75)"),
	N_("No ticket file found"),
	N_("Couldn't access ticket file"),
	N_("Couldn't lock ticket file"),
	N_("Bad ticket file format"),
	N_("tf_init not called first"),
	N_("Bad Kerberos name format"),
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

const struct error_table et_krb_error_table = { text, 39525376L, 82 };

static struct et_list link = { 0, 0 };

void initialize_krb_error_table_r(struct et_list **list);
void initialize_krb_error_table(void);

void initialize_krb_error_table(void) {
    initialize_krb_error_table_r(&_et_list);
}

void initialize_krb_error_table_r(struct et_list **list)
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
    et->table = &et_krb_error_table;
    et->next = 0;
    *end = et;
}