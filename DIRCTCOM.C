

#include "dos.h"
#include "unsigned.h"


#define DATA 0
#define INT_ENABLE 1
#define IINT_STATUS 2
#define LINE_CONTROL 3
#define MODEM_CONTROL 4
#define LINE_STATUS 5
#define MODEM_STATUS 6


struct int_enable {
	uchar recv	:1;
	uchar tbe	:1;
	uchar err	:1;
	uchar rsinp	:1;
	uchar 		;4;
	};

struct int_indent {
	uchar cause	:3;
	uchar 		:5;
	};

struct line_control {
	uchar data	:2;
	uchar stop	:1;
	uchar parity	:3;
	uchar break	:1;
	uchar dlab	:1;
	};

struct modem_control {
