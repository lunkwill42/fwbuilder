#ifndef INC_PIXCfgParserTokenTypes_hpp_
#define INC_PIXCfgParserTokenTypes_hpp_

/* $ANTLR 2.7.7 (20090306): "pix.g" -> "PIXCfgParserTokenTypes.hpp"$ */

#ifndef CUSTOM_API
# define CUSTOM_API
#endif

#ifdef __cplusplus
struct CUSTOM_API PIXCfgParserTokenTypes {
#endif
	enum {
		EOF_ = 1,
		NEWLINE = 4,
		IP = 5,
		QUIT = 6,
		COMMUNITY_LIST = 7,
		CRYPTO = 8,
		WORD = 9,
		CERTIFICATE = 10,
		PIX_WORD = 11,
		ASA_WORD = 12,
		VERSION_WORD = 13,
		NUMBER = 14,
		HOSTNAME = 15,
		STRING = 16,
		ACCESS_LIST = 17,
		INT_CONST = 18,
		PERMIT = 19,
		DENY = 20,
		ICMP = 21,
		TCP = 22,
		UDP = 23,
		P_EQ = 24,
		P_GT = 25,
		P_LT = 26,
		P_NEQ = 27,
		P_RANGE = 28,
		HOST = 29,
		IPV4 = 30,
		ANY = 31,
		LOG = 32,
		LOG_INPUT = 33,
		ESTABLISHED = 34,
		FRAGMENTS = 35,
		TIME_RANGE = 36,
		CONTROLLER = 37,
		INTRFACE = 38,
		VLAN = 39,
		SEC_LEVEL = 40,
		NAMEIF = 41,
		DESCRIPTION = 42,
		REMARK = 43,
		SHUTDOWN = 44,
		ADDRESS = 45,
		DHCP = 46,
		STANDBY = 47,
		SWITCHPORT = 48,
		ACCESS = 49,
		ACCESS_GROUP = 50,
		EXIT = 51,
		LINE_COMMENT = 52,
		COLON_COMMENT = 53,
		SECONDARY = 54,
		SETROUTE = 55,
		EXTENDED = 56,
		STANDARD = 57,
		Whitespace = 58,
		HEX_CONST = 59,
		NEG_INT_CONST = 60,
		DIGIT = 61,
		HEXDIGIT = 62,
		PIPE_CHAR = 63,
		NUMBER_SIGN = 64,
		PERCENT = 65,
		AMPERSAND = 66,
		APOSTROPHE = 67,
		OPENING_PAREN = 68,
		CLOSING_PAREN = 69,
		STAR = 70,
		PLUS = 71,
		COMMA = 72,
		MINUS = 73,
		DOT = 74,
		SLASH = 75,
		COLON = 76,
		SEMICOLON = 77,
		LESS_THAN = 78,
		EQUALS = 79,
		GREATER_THAN = 80,
		QUESTION = 81,
		COMMERCIAL_AT = 82,
		OPENING_SQUARE = 83,
		CLOSING_SQUARE = 84,
		CARET = 85,
		UNDERLINE = 86,
		OPENING_BRACE = 87,
		CLOSING_BRACE = 88,
		TILDE = 89,
		NULL_TREE_LOOKAHEAD = 3
	};
#ifdef __cplusplus
};
#endif
#endif /*INC_PIXCfgParserTokenTypes_hpp_*/
