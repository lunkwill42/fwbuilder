/* $ANTLR 2.7.7 (20090306): "iptables.g" -> "IPTCfgParser.cpp"$ */
#line 44 "iptables.g"

    // gets inserted before the antlr generated includes in the cpp
    // file

#line 8 "IPTCfgParser.cpp"
#include "IPTCfgParser.hpp"
#include <antlr/NoViableAltException.hpp>
#include <antlr/SemanticException.hpp>
#include <antlr/ASTFactory.hpp>
#line 50 "iptables.g"

    // gets inserted after the antlr generated includes in the cpp
    // file
#include <antlr/Token.hpp>
#include <antlr/TokenBuffer.hpp>

#include "fwbuilder/TCPService.h"
#include "fwbuilder/Logger.h"

#include <algorithm>

#line 25 "IPTCfgParser.cpp"
#line 1 "iptables.g"
#line 27 "IPTCfgParser.cpp"
IPTCfgParser::IPTCfgParser(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf, int k)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(tokenBuf,k)
{
}

IPTCfgParser::IPTCfgParser(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(tokenBuf,2)
{
}

IPTCfgParser::IPTCfgParser(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer, int k)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(lexer,k)
{
}

IPTCfgParser::IPTCfgParser(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(lexer,2)
{
}

IPTCfgParser::IPTCfgParser(const ANTLR_USE_NAMESPACE(antlr)ParserSharedInputState& state)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(state,2)
{
}

void IPTCfgParser::cfgfile() {
	Tracer traceInOut(this, "cfgfile");
	
	try {      // for error handling
		{ // ( ... )+
		int _cnt3=0;
		for (;;) {
			switch ( LA(1)) {
			case NUMBER_SIGN:
			{
				comment();
				break;
			}
			case STAR:
			{
				start_table();
				break;
			}
			case COLON:
			{
				create_chain();
				break;
			}
			case ADD_RULE:
			{
				add_rule();
				break;
			}
			case COMMIT:
			{
				commit();
				break;
			}
			case NEWLINE:
			{
				match(NEWLINE);
				break;
			}
			default:
			{
				if ( _cnt3>=1 ) { goto _loop3; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
			}
			}
			_cnt3++;
		}
		_loop3:;
		}  // ( ... )+
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_0);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::comment() {
	Tracer traceInOut(this, "comment");
	
	try {      // for error handling
		match(NUMBER_SIGN);
		{ // ( ... )*
		for (;;) {
			if ((LA(1) == IPTABLES_SAVE_HEADER)) {
				match(IPTABLES_SAVE_HEADER);
				{
				switch ( LA(1)) {
				case THREE_COMPONENT_VERSION:
				{
					match(THREE_COMPONENT_VERSION);
					break;
				}
				case IPV4:
				{
					match(IPV4);
					break;
				}
				default:
				{
					throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
				}
				}
				}
				if ( inputState->guessing==0 ) {
#line 140 "iptables.g"
					
					importer->setCurrentLineNumber(LT(0)->getLine());
					std::string version = LT(0)->getText();
					importer->setDiscoveredVersion(version);
					*dbg << "VERSION " << version << std::endl;
					consumeUntil(NEWLINE);
					
#line 147 "IPTCfgParser.cpp"
				}
			}
			else {
				goto _loop7;
			}
			
		}
		_loop7:;
		} // ( ... )*
		if ( inputState->guessing==0 ) {
#line 148 "iptables.g"
			
			consumeUntil(NEWLINE);
			
#line 162 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::start_table() {
	Tracer traceInOut(this, "start_table");
	
	try {      // for error handling
		match(STAR);
		match(WORD);
		if ( inputState->guessing==0 ) {
#line 170 "iptables.g"
			
			if (!importer->current_table.empty())
			{
			// we did not see COMMIT
			*(importer->logger) << "********************************\n";
			*(importer->logger) << "Missing COMMIT for the table " << importer->current_table << "\n";
			*(importer->logger) << "Perhaps the file is broken ?" << "\n";
			*(importer->logger) << "********************************\n";
			
			*dbg << "Missing COMMIT for the table " << importer->current_table;
			*dbg << "Perhaps the file is broken ?";
			
			// push last rule
			importer->pushRule();
			// clear current table
			importer->current_table = "";
			}
			importer->current_table = LT(0)->getText();
			*dbg << "TABLE " << LT(0)->getText() << std::endl;
			
#line 203 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::create_chain() {
	Tracer traceInOut(this, "create_chain");
	
	try {      // for error handling
		match(COLON);
		chain_def();
		if ( inputState->guessing==0 ) {
#line 205 "iptables.g"
			
			importer->setCurrentLineNumber(LT(0)->getLine());
			if (importer->current_table=="nat")
			importer->newUnidirRuleSet(LT(0)->getText(),
			libfwbuilder::NAT::TYPENAME);
			else
			importer->newUnidirRuleSet(LT(0)->getText(),
			libfwbuilder::Policy::TYPENAME);
			*dbg << "NEW CHAIN " << LT(0)->getText() << std::endl;
			
#line 234 "IPTCfgParser.cpp"
		}
		{
		switch ( LA(1)) {
		case WORD:
		{
			match(WORD);
			break;
		}
		case MINUS:
		{
			match(MINUS);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 216 "iptables.g"
			
			importer->setDefaultAction(LT(0)->getText());
			*dbg << "DEFAULT ACTION " << LT(0)->getText() << std::endl;
			
#line 260 "IPTCfgParser.cpp"
		}
		{
		switch ( LA(1)) {
		case OPENING_SQUARE:
		{
			match(OPENING_SQUARE);
			match(INT_CONST);
			match(COLON);
			match(INT_CONST);
			match(CLOSING_SQUARE);
			break;
		}
		case ANTLR_USE_NAMESPACE(antlr)Token::EOF_TYPE:
		case NEWLINE:
		case NUMBER_SIGN:
		case COMMIT:
		case STAR:
		case COLON:
		case ADD_RULE:
		{
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::add_rule() {
	Tracer traceInOut(this, "add_rule");
	
	try {      // for error handling
		match(ADD_RULE);
		chain_def();
		if ( inputState->guessing==0 ) {
#line 226 "iptables.g"
			
			// push previous rule
			*dbg << std::endl;
			importer->pushRule();
			// start new one
			importer->setCurrentLineNumber(LT(0)->getLine());
			if (importer->current_table=="nat")
			importer->newNATRule();
			else
			importer->newPolicyRule();
			importer->current_chain = LT(0)->getText();
			*dbg << "add_rule: line=" << LT(0)->getLine()
			<< " chain=" << LT(0)->getText();
			
#line 322 "IPTCfgParser.cpp"
		}
		{ // ( ... )+
		int _cnt17=0;
		for (;;) {
			if ((_tokenSet_2.member(LA(1)))) {
				ipt_option();
			}
			else {
				if ( _cnt17>=1 ) { goto _loop17; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt17++;
		}
		_loop17:;
		}  // ( ... )+
		match(NEWLINE);
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::commit() {
	Tracer traceInOut(this, "commit");
	
	try {      // for error handling
		match(COMMIT);
		if ( inputState->guessing==0 ) {
#line 158 "iptables.g"
			
			// push last rule
			importer->pushRule();
			*dbg << " COMMIT" << std::endl;
			// clear current table
			importer->current_table = "";
			
#line 364 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::chain_def() {
	Tracer traceInOut(this, "chain_def");
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case INPUT:
		{
			match(INPUT);
			break;
		}
		case FORWARD:
		{
			match(FORWARD);
			break;
		}
		case OUTPUT:
		{
			match(OUTPUT);
			break;
		}
		case PREROUTING:
		{
			match(PREROUTING);
			break;
		}
		case POSTROUTING:
		{
			match(POSTROUTING);
			break;
		}
		case WORD:
		{
			match(WORD);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_3);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::ipt_option() {
	Tracer traceInOut(this, "ipt_option");
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case OPT_SRC:
		{
			src();
			break;
		}
		case OPT_DST:
		{
			dst();
			break;
		}
		case OPT_IN_INTF:
		{
			i_intf();
			break;
		}
		case OPT_OUT_INTF:
		{
			o_intf();
			break;
		}
		case OPT_PROTO:
		{
			proto();
			break;
		}
		case OPT_TARGET:
		{
			target();
			break;
		}
		case OPT_FRAGM:
		{
			fragm();
			break;
		}
		case MATCH_ICMP_TYPE:
		{
			icmp_type_spec();
			break;
		}
		case MATCH_SRC_PORT:
		case MATCH_SRC_PORT_SHORT:
		case MATCH_DST_PORT:
		case MATCH_DST_PORT_SHORT:
		{
			basic_tcp_udp_port_spec();
			break;
		}
		case MATCH_SRC_MULTIPORT:
		case MATCH_DST_MULTIPORT:
		case MATCH_BOTH_MULTIPORT:
		{
			multiport_tcp_udp_port_spec();
			break;
		}
		case EXCLAMATION:
		case MATCH_SYN:
		case MATCH_TCP_FLAGS:
		case MATCH_TCP_OPTION:
		{
			tcp_options();
			break;
		}
		case MATCH_LIMIT:
		{
			match_limit();
			break;
		}
		case MATCH_LIMIT_BURST:
		{
			match_limit_burst();
			break;
		}
		case MATCH_LENGTH:
		{
			match_length();
			break;
		}
		case MATCH_IPRANGE_SRC:
		{
			match_iprange_src();
			break;
		}
		case MATCH_IPRANGE_DST:
		{
			match_iprange_dst();
			break;
		}
		case MINUS:
		case UNSUPPORTED_OPTION:
		{
			unknown_option();
			break;
		}
		default:
			if ((LA(1) == OPT_MODULE) && (_tokenSet_4.member(LA(2)))) {
				module();
			}
			else if ((LA(1) == OPT_MODULE) && (LA(2) == M_MARK)) {
				match_mark();
			}
			else if ((LA(1) == OPT_MODULE) && (LA(2) == M_RECENT)) {
				match_recent();
			}
		else {
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::module() {
	Tracer traceInOut(this, "module");
	
	try {      // for error handling
		match(OPT_MODULE);
		{
		switch ( LA(1)) {
		case M_STATE:
		{
			m_state();
			break;
		}
		case M_MPORT:
		{
			m_mport();
			break;
		}
		case ICMP:
		{
			m_icmp();
			break;
		}
		case TCP:
		{
			m_tcp();
			break;
		}
		case UDP:
		{
			m_udp();
			break;
		}
		case M_LIMIT:
		{
			m_limit();
			break;
		}
		case M_LENGTH:
		{
			m_length();
			break;
		}
		case M_IPRANGE:
		{
			m_iprange();
			break;
		}
		case M_COMMENT:
		{
			m_comment();
			break;
		}
		case M_PKTTYPE:
		{
			m_pkttype();
			break;
		}
		case WORD:
		{
			m_unknown_module();
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::match_mark() {
	Tracer traceInOut(this, "match_mark");
	
	try {      // for error handling
		match(OPT_MODULE);
		m_mark();
		{
		switch ( LA(1)) {
		case EXCLAMATION:
		{
			match(EXCLAMATION);
			if ( inputState->guessing==0 ) {
#line 718 "iptables.g"
				importer->neg_match_mark = true;
#line 649 "IPTCfgParser.cpp"
			}
			break;
		}
		case MATCH_MARK:
		{
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		match(MATCH_MARK);
		{
		switch ( LA(1)) {
		case INT_CONST:
		{
			match(INT_CONST);
			break;
		}
		case HEX_CONST:
		{
			match(HEX_CONST);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 720 "iptables.g"
			
			importer->match_mark = LT(0)->getText();
			*dbg << " MATCH MARK " << LT(0)->getText();
			
#line 688 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::match_recent() {
	Tracer traceInOut(this, "match_recent");
	
	try {      // for error handling
		match(OPT_MODULE);
		m_recent();
		{ // ( ... )+
		int _cnt98=0;
		for (;;) {
			if (((LA(1) >= MATCH_RECENT_SET && LA(1) <= MATCH_RECENT_HITCOUNT))) {
				recent_opts();
			}
			else {
				if ( _cnt98>=1 ) { goto _loop98; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt98++;
		}
		_loop98:;
		}  // ( ... )+
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::src() {
	Tracer traceInOut(this, "src");
	
	try {      // for error handling
		match(OPT_SRC);
		if ( inputState->guessing==0 ) {
#line 361 "iptables.g"
			
			*dbg << " SRC=";
			
#line 742 "IPTCfgParser.cpp"
		}
		{
		switch ( LA(1)) {
		case EXCLAMATION:
		{
			match(EXCLAMATION);
			if ( inputState->guessing==0 ) {
#line 366 "iptables.g"
				
				importer->src_neg = true;
				
#line 754 "IPTCfgParser.cpp"
			}
			break;
		}
		case IPV4:
		case WORD:
		{
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		{
		{
		switch ( LA(1)) {
		case WORD:
		{
			match(WORD);
			break;
		}
		case IPV4:
		{
			match(IPV4);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 371 "iptables.g"
			
			importer->src_a = LT(0)->getText();
			*dbg << LT(0)->getText();
			
#line 794 "IPTCfgParser.cpp"
		}
		{
		switch ( LA(1)) {
		case SLASH:
		{
			match(SLASH);
			{
			switch ( LA(1)) {
			case IPV4:
			{
				match(IPV4);
				break;
			}
			case INT_CONST:
			{
				match(INT_CONST);
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			if ( inputState->guessing==0 ) {
#line 376 "iptables.g"
				
				importer->src_nm = LT(0)->getText();
				*dbg << "/" << LT(0)->getText();
				
#line 825 "IPTCfgParser.cpp"
			}
			break;
		}
		case NEWLINE:
		case MINUS:
		case UNSUPPORTED_OPTION:
		case OPT_MODULE:
		case OPT_SRC:
		case EXCLAMATION:
		case OPT_DST:
		case OPT_IN_INTF:
		case OPT_OUT_INTF:
		case OPT_PROTO:
		case OPT_TARGET:
		case OPT_FRAGM:
		case MATCH_LIMIT:
		case MATCH_LIMIT_BURST:
		case MATCH_IPRANGE_SRC:
		case MATCH_IPRANGE_DST:
		case MATCH_LENGTH:
		case MATCH_SRC_MULTIPORT:
		case MATCH_DST_MULTIPORT:
		case MATCH_BOTH_MULTIPORT:
		case MATCH_ICMP_TYPE:
		case MATCH_SRC_PORT:
		case MATCH_SRC_PORT_SHORT:
		case MATCH_DST_PORT:
		case MATCH_DST_PORT_SHORT:
		case MATCH_SYN:
		case MATCH_TCP_FLAGS:
		case MATCH_TCP_OPTION:
		{
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::dst() {
	Tracer traceInOut(this, "dst");
	
	try {      // for error handling
		match(OPT_DST);
		if ( inputState->guessing==0 ) {
#line 385 "iptables.g"
			
			*dbg << " DST=";
			
#line 888 "IPTCfgParser.cpp"
		}
		{
		switch ( LA(1)) {
		case EXCLAMATION:
		{
			match(EXCLAMATION);
			if ( inputState->guessing==0 ) {
#line 390 "iptables.g"
				
				importer->dst_neg = true;
				
#line 900 "IPTCfgParser.cpp"
			}
			break;
		}
		case IPV4:
		case WORD:
		{
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		{
		{
		switch ( LA(1)) {
		case WORD:
		{
			match(WORD);
			break;
		}
		case IPV4:
		{
			match(IPV4);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 395 "iptables.g"
			
			importer->dst_a = LT(0)->getText();
			*dbg << LT(0)->getText();
			
#line 940 "IPTCfgParser.cpp"
		}
		{
		switch ( LA(1)) {
		case SLASH:
		{
			match(SLASH);
			{
			switch ( LA(1)) {
			case IPV4:
			{
				match(IPV4);
				break;
			}
			case INT_CONST:
			{
				match(INT_CONST);
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			if ( inputState->guessing==0 ) {
#line 400 "iptables.g"
				
				importer->dst_nm = LT(0)->getText();
				*dbg << "/" << LT(0)->getText();
				
#line 971 "IPTCfgParser.cpp"
			}
			break;
		}
		case NEWLINE:
		case MINUS:
		case UNSUPPORTED_OPTION:
		case OPT_MODULE:
		case OPT_SRC:
		case EXCLAMATION:
		case OPT_DST:
		case OPT_IN_INTF:
		case OPT_OUT_INTF:
		case OPT_PROTO:
		case OPT_TARGET:
		case OPT_FRAGM:
		case MATCH_LIMIT:
		case MATCH_LIMIT_BURST:
		case MATCH_IPRANGE_SRC:
		case MATCH_IPRANGE_DST:
		case MATCH_LENGTH:
		case MATCH_SRC_MULTIPORT:
		case MATCH_DST_MULTIPORT:
		case MATCH_BOTH_MULTIPORT:
		case MATCH_ICMP_TYPE:
		case MATCH_SRC_PORT:
		case MATCH_SRC_PORT_SHORT:
		case MATCH_DST_PORT:
		case MATCH_DST_PORT_SHORT:
		case MATCH_SYN:
		case MATCH_TCP_FLAGS:
		case MATCH_TCP_OPTION:
		{
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::i_intf() {
	Tracer traceInOut(this, "i_intf");
	ANTLR_USE_NAMESPACE(antlr)RefToken  i = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		match(OPT_IN_INTF);
		{
		switch ( LA(1)) {
		case EXCLAMATION:
		{
			match(EXCLAMATION);
			if ( inputState->guessing==0 ) {
#line 411 "iptables.g"
				
				importer->intf_neg = true;
				
#line 1040 "IPTCfgParser.cpp"
			}
			break;
		}
		case WORD:
		{
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		i = LT(1);
		match(WORD);
		if ( inputState->guessing==0 ) {
#line 416 "iptables.g"
			
			importer->i_intf = LT(0)->getText();
			*dbg << " I_INTF=" << i->getText();
			
#line 1062 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::o_intf() {
	Tracer traceInOut(this, "o_intf");
	ANTLR_USE_NAMESPACE(antlr)RefToken  i = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		match(OPT_OUT_INTF);
		{
		switch ( LA(1)) {
		case EXCLAMATION:
		{
			match(EXCLAMATION);
			if ( inputState->guessing==0 ) {
#line 426 "iptables.g"
				
				importer->intf_neg = true;
				
#line 1091 "IPTCfgParser.cpp"
			}
			break;
		}
		case WORD:
		{
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		i = LT(1);
		match(WORD);
		if ( inputState->guessing==0 ) {
#line 431 "iptables.g"
			
			importer->o_intf = LT(0)->getText();
			*dbg << " O_INTF=" << i->getText();
			
#line 1113 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::proto() {
	Tracer traceInOut(this, "proto");
	
	try {      // for error handling
		match(OPT_PROTO);
		{
		switch ( LA(1)) {
		case EXCLAMATION:
		{
			match(EXCLAMATION);
			if ( inputState->guessing==0 ) {
#line 444 "iptables.g"
				
				importer->srv_neg = true;
				
#line 1141 "IPTCfgParser.cpp"
			}
			break;
		}
		case WORD:
		case INT_CONST:
		case TCP:
		case UDP:
		case ICMP:
		{
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		protocol_word();
		if ( inputState->guessing==0 ) {
#line 449 "iptables.g"
			
			std::string tmp_s = LT(0)->getText();
			importer->protocol.resize(tmp_s.size());
			std::transform(tmp_s.begin(), 
			tmp_s.end(),
			importer->protocol.begin(), 
			::tolower);
			*dbg << " PROTO=" << importer->protocol;
			
#line 1171 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::target() {
	Tracer traceInOut(this, "target");
	ANTLR_USE_NAMESPACE(antlr)RefToken  t = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		match(OPT_TARGET);
		t = LT(1);
		match(WORD);
		if ( inputState->guessing==0 ) {
#line 462 "iptables.g"
			
			importer->target = LT(0)->getText();
			*dbg << " TARGET=" << t->getText();
			
#line 1198 "IPTCfgParser.cpp"
		}
		{ // ( ... )*
		for (;;) {
			if ((_tokenSet_6.member(LA(1)))) {
				target_options();
			}
			else {
				goto _loop58;
			}
			
		}
		_loop58:;
		} // ( ... )*
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::fragm() {
	Tracer traceInOut(this, "fragm");
	
	try {      // for error handling
		match(OPT_FRAGM);
		if ( inputState->guessing==0 ) {
#line 667 "iptables.g"
			
			importer->fragments = true;
			*dbg << " FRAGM";
			
#line 1234 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::icmp_type_spec() {
	Tracer traceInOut(this, "icmp_type_spec");
	
	try {      // for error handling
		match(MATCH_ICMP_TYPE);
		{
		switch ( LA(1)) {
		case WORD:
		{
			match(WORD);
			if ( inputState->guessing==0 ) {
#line 950 "iptables.g"
				
				importer->icmp_spec = LT(0)->getText();
				*dbg << " ICMP_SPEC=" << LT(0)->getText();
				
#line 1263 "IPTCfgParser.cpp"
			}
			break;
		}
		case INT_CONST:
		{
			{
			match(INT_CONST);
			if ( inputState->guessing==0 ) {
#line 957 "iptables.g"
				
				importer->icmp_type = LT(0)->getText();
				importer->icmp_code = "-1";
				*dbg << " ICMP_TYPE=" << LT(0)->getText();
				
#line 1278 "IPTCfgParser.cpp"
			}
			{
			switch ( LA(1)) {
			case SLASH:
			{
				match(SLASH);
				match(INT_CONST);
				if ( inputState->guessing==0 ) {
#line 964 "iptables.g"
					
					importer->icmp_code = LT(0)->getText();
					*dbg << " ICMP_CODE=" << LT(0)->getText();
					
#line 1292 "IPTCfgParser.cpp"
				}
				break;
			}
			case NEWLINE:
			case MINUS:
			case UNSUPPORTED_OPTION:
			case OPT_MODULE:
			case OPT_SRC:
			case EXCLAMATION:
			case OPT_DST:
			case OPT_IN_INTF:
			case OPT_OUT_INTF:
			case OPT_PROTO:
			case OPT_TARGET:
			case OPT_FRAGM:
			case MATCH_LIMIT:
			case MATCH_LIMIT_BURST:
			case MATCH_IPRANGE_SRC:
			case MATCH_IPRANGE_DST:
			case MATCH_LENGTH:
			case MATCH_SRC_MULTIPORT:
			case MATCH_DST_MULTIPORT:
			case MATCH_BOTH_MULTIPORT:
			case MATCH_ICMP_TYPE:
			case MATCH_SRC_PORT:
			case MATCH_SRC_PORT_SHORT:
			case MATCH_DST_PORT:
			case MATCH_DST_PORT_SHORT:
			case MATCH_SYN:
			case MATCH_TCP_FLAGS:
			case MATCH_TCP_OPTION:
			{
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			}
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::basic_tcp_udp_port_spec() {
	Tracer traceInOut(this, "basic_tcp_udp_port_spec");
	
	try {      // for error handling
		switch ( LA(1)) {
		case MATCH_SRC_PORT:
		case MATCH_SRC_PORT_SHORT:
		{
			{
			switch ( LA(1)) {
			case MATCH_SRC_PORT:
			{
				match(MATCH_SRC_PORT);
				break;
			}
			case MATCH_SRC_PORT_SHORT:
			{
				match(MATCH_SRC_PORT_SHORT);
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			{
			switch ( LA(1)) {
			case EXCLAMATION:
			{
				match(EXCLAMATION);
				if ( inputState->guessing==0 ) {
#line 1048 "iptables.g"
					
					importer->srv_neg = true;
					
#line 1389 "IPTCfgParser.cpp"
				}
				break;
			}
			case WORD:
			case COLON:
			case INT_CONST:
			{
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			{
			switch ( LA(1)) {
			case WORD:
			case INT_CONST:
			{
				port_def_with_range();
				break;
			}
			case COLON:
			{
				port_def_with_incomplete_range();
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			if ( inputState->guessing==0 ) {
#line 1053 "iptables.g"
				
				importer->pushTmpPortSpecToSrcPortList();
				
#line 1429 "IPTCfgParser.cpp"
			}
			break;
		}
		case MATCH_DST_PORT:
		case MATCH_DST_PORT_SHORT:
		{
			{
			switch ( LA(1)) {
			case MATCH_DST_PORT:
			{
				match(MATCH_DST_PORT);
				break;
			}
			case MATCH_DST_PORT_SHORT:
			{
				match(MATCH_DST_PORT_SHORT);
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			{
			switch ( LA(1)) {
			case EXCLAMATION:
			{
				match(EXCLAMATION);
				if ( inputState->guessing==0 ) {
#line 1060 "iptables.g"
					
					importer->srv_neg = true;
					
#line 1464 "IPTCfgParser.cpp"
				}
				break;
			}
			case WORD:
			case COLON:
			case INT_CONST:
			{
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			{
			switch ( LA(1)) {
			case WORD:
			case INT_CONST:
			{
				port_def_with_range();
				break;
			}
			case COLON:
			{
				port_def_with_incomplete_range();
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			if ( inputState->guessing==0 ) {
#line 1065 "iptables.g"
				
				importer->pushTmpPortSpecToDstPortList();
				
#line 1504 "IPTCfgParser.cpp"
			}
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::multiport_tcp_udp_port_spec() {
	Tracer traceInOut(this, "multiport_tcp_udp_port_spec");
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case MATCH_SRC_MULTIPORT:
		{
			{
			match(MATCH_SRC_MULTIPORT);
			if ( inputState->guessing==0 ) {
#line 887 "iptables.g"
				
				importer->startSrcMultiPort();
				*dbg << " SRC MULTIPORT=";
				
#line 1540 "IPTCfgParser.cpp"
			}
			port_def_no_range();
			if ( inputState->guessing==0 ) {
#line 892 "iptables.g"
				
				importer->pushTmpPortSpecToSrcPortList();
				
#line 1548 "IPTCfgParser.cpp"
			}
			{ // ( ... )*
			for (;;) {
				if ((LA(1) == COMMA)) {
					match(COMMA);
					port_def_no_range();
					if ( inputState->guessing==0 ) {
#line 896 "iptables.g"
						
						importer->pushTmpPortSpecToSrcPortList();
						
#line 1560 "IPTCfgParser.cpp"
					}
				}
				else {
					goto _loop117;
				}
				
			}
			_loop117:;
			} // ( ... )*
			}
			break;
		}
		case MATCH_DST_MULTIPORT:
		{
			{
			match(MATCH_DST_MULTIPORT);
			if ( inputState->guessing==0 ) {
#line 903 "iptables.g"
				
				importer->startDstMultiPort();
				*dbg << " DST MULTIPORT=";
				
#line 1583 "IPTCfgParser.cpp"
			}
			port_def_no_range();
			if ( inputState->guessing==0 ) {
#line 908 "iptables.g"
				
				importer->pushTmpPortSpecToDstPortList();
				
#line 1591 "IPTCfgParser.cpp"
			}
			{ // ( ... )*
			for (;;) {
				if ((LA(1) == COMMA)) {
					match(COMMA);
					port_def_no_range();
					if ( inputState->guessing==0 ) {
#line 912 "iptables.g"
						
						importer->pushTmpPortSpecToDstPortList();
						
#line 1603 "IPTCfgParser.cpp"
					}
				}
				else {
					goto _loop120;
				}
				
			}
			_loop120:;
			} // ( ... )*
			}
			break;
		}
		case MATCH_BOTH_MULTIPORT:
		{
			{
			match(MATCH_BOTH_MULTIPORT);
			if ( inputState->guessing==0 ) {
#line 919 "iptables.g"
				
				importer->startBothMultiPort();
				*dbg << " MULTIPORT PORTS=";
				
#line 1626 "IPTCfgParser.cpp"
			}
			port_def_no_range();
			if ( inputState->guessing==0 ) {
#line 924 "iptables.g"
				
				importer->pushTmpPortSpecToBothPortList();
				
#line 1634 "IPTCfgParser.cpp"
			}
			{ // ( ... )*
			for (;;) {
				if ((LA(1) == COMMA)) {
					match(COMMA);
					port_def_no_range();
					if ( inputState->guessing==0 ) {
#line 928 "iptables.g"
						
						importer->pushTmpPortSpecToBothPortList();
						
#line 1646 "IPTCfgParser.cpp"
					}
				}
				else {
					goto _loop123;
				}
				
			}
			_loop123:;
			} // ( ... )*
			}
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::tcp_options() {
	Tracer traceInOut(this, "tcp_options");
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case EXCLAMATION:
		{
			match(EXCLAMATION);
			if ( inputState->guessing==0 ) {
#line 1094 "iptables.g"
				importer->srv_neg = true;
#line 1688 "IPTCfgParser.cpp"
			}
			break;
		}
		case MATCH_SYN:
		case MATCH_TCP_FLAGS:
		case MATCH_TCP_OPTION:
		{
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		{
		switch ( LA(1)) {
		case MATCH_SYN:
		{
			syn();
			break;
		}
		case MATCH_TCP_FLAGS:
		{
			tcp_flags();
			break;
		}
		case MATCH_TCP_OPTION:
		{
			tcp_option();
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::match_limit() {
	Tracer traceInOut(this, "match_limit");
	
	try {      // for error handling
		match(MATCH_LIMIT);
		limit_rate();
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::match_limit_burst() {
	Tracer traceInOut(this, "match_limit_burst");
	
	try {      // for error handling
		match(MATCH_LIMIT_BURST);
		match(INT_CONST);
		if ( inputState->guessing==0 ) {
#line 751 "iptables.g"
			
			importer->limit_burst = LT(0)->getText();
			*dbg << " LIMIT BURST " << LT(0)->getText();
			
#line 1767 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::match_length() {
	Tracer traceInOut(this, "match_length");
	
	try {      // for error handling
		match(MATCH_LENGTH);
		length_spec();
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::match_iprange_src() {
	Tracer traceInOut(this, "match_iprange_src");
	
	try {      // for error handling
		match(MATCH_IPRANGE_SRC);
		{
		switch ( LA(1)) {
		case WORD:
		{
			match(WORD);
			break;
		}
		case IPV4:
		{
			match(IPV4);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 774 "iptables.g"
			
			importer->iprange_src_from = LT(0)->getText();
			importer->using_iprange_src = true;
			
#line 1826 "IPTCfgParser.cpp"
		}
		match(MINUS);
		{
		switch ( LA(1)) {
		case WORD:
		{
			match(WORD);
			break;
		}
		case IPV4:
		{
			match(IPV4);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 779 "iptables.g"
			
			importer->iprange_src_to = LT(0)->getText();
			
#line 1852 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::match_iprange_dst() {
	Tracer traceInOut(this, "match_iprange_dst");
	
	try {      // for error handling
		match(MATCH_IPRANGE_DST);
		{
		switch ( LA(1)) {
		case WORD:
		{
			match(WORD);
			break;
		}
		case IPV4:
		{
			match(IPV4);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 785 "iptables.g"
			
			importer->iprange_dst_from = LT(0)->getText();
			importer->using_iprange_dst = true;
			
#line 1894 "IPTCfgParser.cpp"
		}
		match(MINUS);
		{
		switch ( LA(1)) {
		case WORD:
		{
			match(WORD);
			break;
		}
		case IPV4:
		{
			match(IPV4);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 790 "iptables.g"
			
			importer->iprange_dst_to = LT(0)->getText();
			
#line 1920 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::unknown_option() {
	Tracer traceInOut(this, "unknown_option");
	
	try {      // for error handling
		if ((LA(1) == MINUS) && (LA(2) == WORD)) {
			{
			match(MINUS);
			match(WORD);
			if ( inputState->guessing==0 ) {
#line 292 "iptables.g"
				
				importer->reportError(
				std::string("Unknown option: -")+LT(0)->getText());
				*dbg << " UNKNOWN OPTION=-" << LT(0)->getText();
				
#line 1948 "IPTCfgParser.cpp"
			}
			{
			switch ( LA(1)) {
			case WORD:
			case INT_CONST:
			case DIGIT:
			{
				unknown_parameter();
				break;
			}
			case NEWLINE:
			case MINUS:
			case UNSUPPORTED_OPTION:
			case OPT_MODULE:
			case OPT_SRC:
			case EXCLAMATION:
			case OPT_DST:
			case OPT_IN_INTF:
			case OPT_OUT_INTF:
			case OPT_PROTO:
			case OPT_TARGET:
			case OPT_FRAGM:
			case MATCH_LIMIT:
			case MATCH_LIMIT_BURST:
			case MATCH_IPRANGE_SRC:
			case MATCH_IPRANGE_DST:
			case MATCH_LENGTH:
			case MATCH_SRC_MULTIPORT:
			case MATCH_DST_MULTIPORT:
			case MATCH_BOTH_MULTIPORT:
			case MATCH_ICMP_TYPE:
			case MATCH_SRC_PORT:
			case MATCH_SRC_PORT_SHORT:
			case MATCH_DST_PORT:
			case MATCH_DST_PORT_SHORT:
			case MATCH_SYN:
			case MATCH_TCP_FLAGS:
			case MATCH_TCP_OPTION:
			{
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			}
		}
		else if ((LA(1) == MINUS) && (LA(2) == MINUS)) {
			{
			{
			match(MINUS);
			match(MINUS);
			match(WORD);
			}
			if ( inputState->guessing==0 ) {
#line 302 "iptables.g"
				
				importer->reportError(
				std::string("Unknown option: --")+LT(0)->getText());
				*dbg << " UNKNOWN OPTION=--" << LT(0)->getText();
				
#line 2012 "IPTCfgParser.cpp"
			}
			{
			switch ( LA(1)) {
			case WORD:
			case INT_CONST:
			case DIGIT:
			{
				unknown_parameter();
				break;
			}
			case NEWLINE:
			case MINUS:
			case UNSUPPORTED_OPTION:
			case OPT_MODULE:
			case OPT_SRC:
			case EXCLAMATION:
			case OPT_DST:
			case OPT_IN_INTF:
			case OPT_OUT_INTF:
			case OPT_PROTO:
			case OPT_TARGET:
			case OPT_FRAGM:
			case MATCH_LIMIT:
			case MATCH_LIMIT_BURST:
			case MATCH_IPRANGE_SRC:
			case MATCH_IPRANGE_DST:
			case MATCH_LENGTH:
			case MATCH_SRC_MULTIPORT:
			case MATCH_DST_MULTIPORT:
			case MATCH_BOTH_MULTIPORT:
			case MATCH_ICMP_TYPE:
			case MATCH_SRC_PORT:
			case MATCH_SRC_PORT_SHORT:
			case MATCH_DST_PORT:
			case MATCH_DST_PORT_SHORT:
			case MATCH_SYN:
			case MATCH_TCP_FLAGS:
			case MATCH_TCP_OPTION:
			{
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			}
		}
		else if ((LA(1) == UNSUPPORTED_OPTION)) {
			{
			match(UNSUPPORTED_OPTION);
			if ( inputState->guessing==0 ) {
#line 312 "iptables.g"
				
				importer->reportError(
				std::string("Unknown option: ")+LT(0)->getText());
				*dbg << " UNKNOWN OPTION=" << LT(0)->getText();
				
#line 2072 "IPTCfgParser.cpp"
			}
			{
			switch ( LA(1)) {
			case WORD:
			case INT_CONST:
			case DIGIT:
			{
				unknown_parameter();
				break;
			}
			case NEWLINE:
			case MINUS:
			case UNSUPPORTED_OPTION:
			case OPT_MODULE:
			case OPT_SRC:
			case EXCLAMATION:
			case OPT_DST:
			case OPT_IN_INTF:
			case OPT_OUT_INTF:
			case OPT_PROTO:
			case OPT_TARGET:
			case OPT_FRAGM:
			case MATCH_LIMIT:
			case MATCH_LIMIT_BURST:
			case MATCH_IPRANGE_SRC:
			case MATCH_IPRANGE_DST:
			case MATCH_LENGTH:
			case MATCH_SRC_MULTIPORT:
			case MATCH_DST_MULTIPORT:
			case MATCH_BOTH_MULTIPORT:
			case MATCH_ICMP_TYPE:
			case MATCH_SRC_PORT:
			case MATCH_SRC_PORT_SHORT:
			case MATCH_DST_PORT:
			case MATCH_DST_PORT_SHORT:
			case MATCH_SYN:
			case MATCH_TCP_FLAGS:
			case MATCH_TCP_OPTION:
			{
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			}
		}
		else {
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::unknown_parameter() {
	Tracer traceInOut(this, "unknown_parameter");
#line 321 "iptables.g"
	std::string s;
#line 2141 "IPTCfgParser.cpp"
	
	try {      // for error handling
		if ((LA(1) == INT_CONST || LA(1) == DIGIT) && (LA(2) == SLASH)) {
			{
			{
			{
			switch ( LA(1)) {
			case DIGIT:
			{
				match(DIGIT);
				if ( inputState->guessing==0 ) {
#line 327 "iptables.g"
					s+=LT(0)->getText();
#line 2155 "IPTCfgParser.cpp"
				}
				break;
			}
			case INT_CONST:
			{
				match(INT_CONST);
				if ( inputState->guessing==0 ) {
#line 329 "iptables.g"
					s+=LT(0)->getText();
#line 2165 "IPTCfgParser.cpp"
				}
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			match(SLASH);
			if ( inputState->guessing==0 ) {
#line 331 "iptables.g"
				s+=LT(0)->getText();
#line 2179 "IPTCfgParser.cpp"
			}
			match(WORD);
			if ( inputState->guessing==0 ) {
#line 332 "iptables.g"
				s+=LT(0)->getText();
#line 2185 "IPTCfgParser.cpp"
			}
			}
			if ( inputState->guessing==0 ) {
#line 334 "iptables.g"
				
				importer->reportError(
				std::string("Unknown parameter: ")+s);
				*dbg << " UNKNOWN PARMETER=" << s;
				
#line 2195 "IPTCfgParser.cpp"
			}
			}
		}
		else if ((LA(1) == WORD || LA(1) == INT_CONST || LA(1) == DIGIT) && (_tokenSet_5.member(LA(2)))) {
			{
			{
			switch ( LA(1)) {
			case DIGIT:
			{
				match(DIGIT);
				break;
			}
			case INT_CONST:
			{
				match(INT_CONST);
				break;
			}
			case WORD:
			{
				match(WORD);
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			if ( inputState->guessing==0 ) {
#line 343 "iptables.g"
				
				importer->reportError(
				std::string("Unknown parameter: ")+LT(0)->getText());
				*dbg << " UNKNOWN PARMETER=" << LT(0)->getText();
				
#line 2231 "IPTCfgParser.cpp"
			}
			}
		}
		else {
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::m_state() {
	Tracer traceInOut(this, "m_state");
	
	try {      // for error handling
		match(M_STATE);
		match(MATCH_STATE);
		if ( inputState->guessing==0 ) {
#line 688 "iptables.g"
			
			importer->current_state = "";
			
#line 2261 "IPTCfgParser.cpp"
		}
		state_word();
		if ( inputState->guessing==0 ) {
#line 692 "iptables.g"
			
			importer->current_state += LT(0)->getText();
			
#line 2269 "IPTCfgParser.cpp"
		}
		{
		switch ( LA(1)) {
		case COMMA:
		{
			match(COMMA);
			state_word();
			if ( inputState->guessing==0 ) {
#line 697 "iptables.g"
				
				importer->current_state += std::string(",") + LT(0)->getText();
				
#line 2282 "IPTCfgParser.cpp"
			}
			break;
		}
		case NEWLINE:
		case MINUS:
		case UNSUPPORTED_OPTION:
		case OPT_MODULE:
		case OPT_SRC:
		case EXCLAMATION:
		case OPT_DST:
		case OPT_IN_INTF:
		case OPT_OUT_INTF:
		case OPT_PROTO:
		case OPT_TARGET:
		case OPT_FRAGM:
		case MATCH_LIMIT:
		case MATCH_LIMIT_BURST:
		case MATCH_IPRANGE_SRC:
		case MATCH_IPRANGE_DST:
		case MATCH_LENGTH:
		case MATCH_SRC_MULTIPORT:
		case MATCH_DST_MULTIPORT:
		case MATCH_BOTH_MULTIPORT:
		case MATCH_ICMP_TYPE:
		case MATCH_SRC_PORT:
		case MATCH_SRC_PORT_SHORT:
		case MATCH_DST_PORT:
		case MATCH_DST_PORT_SHORT:
		case MATCH_SYN:
		case MATCH_TCP_FLAGS:
		case MATCH_TCP_OPTION:
		{
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 701 "iptables.g"
			
			*dbg << " STATE MATCH=" << importer->current_state;
			
#line 2328 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::m_mport() {
	Tracer traceInOut(this, "m_mport");
	
	try {      // for error handling
		match(M_MPORT);
		if ( inputState->guessing==0 ) {
#line 859 "iptables.g"
			
			*dbg << " MULTIPORT";
			
#line 2351 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::m_icmp() {
	Tracer traceInOut(this, "m_icmp");
	
	try {      // for error handling
		match(ICMP);
		if ( inputState->guessing==0 ) {
#line 940 "iptables.g"
			
			importer->protocol = "icmp";
			*dbg << " ICMP";
			
#line 2375 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::m_tcp() {
	Tracer traceInOut(this, "m_tcp");
	
	try {      // for error handling
		match(TCP);
		if ( inputState->guessing==0 ) {
#line 1083 "iptables.g"
			
			importer->protocol = "tcp";
			*dbg << " TCP";
			
#line 2399 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::m_udp() {
	Tracer traceInOut(this, "m_udp");
	
	try {      // for error handling
		match(UDP);
		if ( inputState->guessing==0 ) {
#line 1074 "iptables.g"
			
			importer->protocol = "udp";
			*dbg << " UDP";
			
#line 2423 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::m_limit() {
	Tracer traceInOut(this, "m_limit");
	
	try {      // for error handling
		match(M_LIMIT);
		if ( inputState->guessing==0 ) {
#line 729 "iptables.g"
			
			*dbg << " LIMIT";
			
#line 2446 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::m_length() {
	Tracer traceInOut(this, "m_length");
	
	try {      // for error handling
		match(M_LENGTH);
		if ( inputState->guessing==0 ) {
#line 824 "iptables.g"
			
			*dbg << " LENGTH";
			
#line 2469 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::m_iprange() {
	Tracer traceInOut(this, "m_iprange");
	
	try {      // for error handling
		match(M_IPRANGE);
		if ( inputState->guessing==0 ) {
#line 768 "iptables.g"
			
			*dbg << " IPRANGE";
			
#line 2492 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::m_comment() {
	Tracer traceInOut(this, "m_comment");
	
	try {      // for error handling
		match(M_COMMENT);
		match(MATCH_COMMENT);
		match(STRING);
		if ( inputState->guessing==0 ) {
#line 867 "iptables.g"
			
			*dbg << " COMMENT=" << LT(0)->getText();
			
#line 2517 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::m_pkttype() {
	Tracer traceInOut(this, "m_pkttype");
	
	try {      // for error handling
		match(M_PKTTYPE);
		match(MATCH_PKT_TYPE);
		pkt_type_spec();
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::m_unknown_module() {
	Tracer traceInOut(this, "m_unknown_module");
	
	try {      // for error handling
		match(WORD);
		if ( inputState->guessing==0 ) {
#line 675 "iptables.g"
			
			*dbg << " UNKNOWN MODULE=" << LT(0)->getText();
			importer->reportError(
			std::string("Unknown module: ")+LT(0)->getText());
			
#line 2560 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::protocol_word() {
	Tracer traceInOut(this, "protocol_word");
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case TCP:
		{
			match(TCP);
			break;
		}
		case UDP:
		{
			match(UDP);
			break;
		}
		case ICMP:
		{
			match(ICMP);
			break;
		}
		case WORD:
		{
			match(WORD);
			break;
		}
		case INT_CONST:
		{
			match(INT_CONST);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::target_options() {
	Tracer traceInOut(this, "target_options");
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case REJECT_WITH:
		{
			match(REJECT_WITH);
			match(WORD);
			if ( inputState->guessing==0 ) {
#line 473 "iptables.g"
				
				importer->action_params["reject_with"] = LT(0)->getText();
				*dbg << " REJECT WITH=" << LT(0)->getText();
				
#line 2637 "IPTCfgParser.cpp"
			}
			break;
		}
		case LOG_PREFIX:
		{
			match(LOG_PREFIX);
			{
			switch ( LA(1)) {
			case WORD:
			{
				match(WORD);
				break;
			}
			case STRING:
			{
				match(STRING);
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			if ( inputState->guessing==0 ) {
#line 479 "iptables.g"
				
				importer->action_params["log_prefix"] = LT(0)->getText();
				*dbg << " LOG PREFIX=" << LT(0)->getText();
				
#line 2668 "IPTCfgParser.cpp"
			}
			break;
		}
		case LOG_TCP_SEQ:
		{
			match(LOG_TCP_SEQ);
			if ( inputState->guessing==0 ) {
#line 485 "iptables.g"
				
				importer->action_params["log_tcp_seq"] = LT(0)->getText();
				*dbg << " LOG TCP SEQUENCE=";
				
#line 2681 "IPTCfgParser.cpp"
			}
			break;
		}
		case LOG_TCP_OPT:
		{
			match(LOG_TCP_OPT);
			if ( inputState->guessing==0 ) {
#line 491 "iptables.g"
				
				importer->action_params["log_tcp_options"] = LT(0)->getText();
				*dbg << " LOG TCP OPTIONS=";
				
#line 2694 "IPTCfgParser.cpp"
			}
			break;
		}
		case LOG_IP_OPT:
		{
			match(LOG_IP_OPT);
			if ( inputState->guessing==0 ) {
#line 497 "iptables.g"
				
				importer->action_params["log_ip_options"] = LT(0)->getText();
				*dbg << " LOG IP OPTIONS=";
				
#line 2707 "IPTCfgParser.cpp"
			}
			break;
		}
		case ULOG_PREFIX:
		{
			match(ULOG_PREFIX);
			{
			switch ( LA(1)) {
			case WORD:
			{
				match(WORD);
				break;
			}
			case STRING:
			{
				match(STRING);
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			if ( inputState->guessing==0 ) {
#line 503 "iptables.g"
				
				importer->action_params["log_prefix"] = LT(0)->getText();
				*dbg << " ULOG PREFIX=" << LT(0)->getText();
				
#line 2738 "IPTCfgParser.cpp"
			}
			break;
		}
		case LOG_LEVEL:
		{
			match(LOG_LEVEL);
			{
			switch ( LA(1)) {
			case INT_CONST:
			{
				match(INT_CONST);
				break;
			}
			case WORD:
			{
				match(WORD);
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			if ( inputState->guessing==0 ) {
#line 509 "iptables.g"
				
				importer->action_params["log_level"] = LT(0)->getText();
				*dbg << " LOG LEVEL=" << LT(0)->getText();
				
#line 2769 "IPTCfgParser.cpp"
			}
			break;
		}
		case SET_MARK:
		{
			match(SET_MARK);
			{
			switch ( LA(1)) {
			case INT_CONST:
			{
				match(INT_CONST);
				break;
			}
			case HEX_CONST:
			{
				match(HEX_CONST);
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			if ( inputState->guessing==0 ) {
#line 515 "iptables.g"
				
				importer->action_params["set_mark"] = LT(0)->getText();
				*dbg << " SET MARK=" << LT(0)->getText();
				
#line 2800 "IPTCfgParser.cpp"
			}
			break;
		}
		case SAVE_MARK:
		{
			match(SAVE_MARK);
			if ( inputState->guessing==0 ) {
#line 533 "iptables.g"
				
				importer->action_params["connmark_save_mark"] = "--save-mark";
				*dbg << " SAVE MARK";
				
#line 2813 "IPTCfgParser.cpp"
			}
			break;
		}
		case RESTORE_MARK:
		{
			match(RESTORE_MARK);
			if ( inputState->guessing==0 ) {
#line 539 "iptables.g"
				
				importer->action_params["connmark_restore_mark"] = "--restore-mark";
				*dbg << " RESTORE MARK";
				
#line 2826 "IPTCfgParser.cpp"
			}
			break;
		}
		case CONTINUE:
		{
			match(CONTINUE);
			if ( inputState->guessing==0 ) {
#line 545 "iptables.g"
				
				importer->action_params["route_continue"] = "--continue";
				*dbg << " CONTINUE";
				
#line 2839 "IPTCfgParser.cpp"
			}
			break;
		}
		case ROUTE_IIF:
		{
			match(ROUTE_IIF);
			match(WORD);
			if ( inputState->guessing==0 ) {
#line 551 "iptables.g"
				
				importer->action_params["route_iif"] = LT(0)->getText();
				*dbg << " ROUTE_IIF=" << LT(0)->getText();
				
#line 2853 "IPTCfgParser.cpp"
			}
			break;
		}
		case ROUTE_OIF:
		{
			match(ROUTE_OIF);
			match(WORD);
			if ( inputState->guessing==0 ) {
#line 557 "iptables.g"
				
				importer->action_params["route_oif"] = LT(0)->getText();
				*dbg << " ROUTE_OIF=" << LT(0)->getText();
				
#line 2867 "IPTCfgParser.cpp"
			}
			break;
		}
		case ROUTE_GW:
		{
			match(ROUTE_GW);
			match(IPV4);
			if ( inputState->guessing==0 ) {
#line 563 "iptables.g"
				
				importer->action_params["route_gw"] = LT(0)->getText();
				*dbg << " ROUTE_GW=" << LT(0)->getText();
				
#line 2881 "IPTCfgParser.cpp"
			}
			break;
		}
		case ROUTE_TEE:
		{
			match(ROUTE_TEE);
			if ( inputState->guessing==0 ) {
#line 569 "iptables.g"
				
				importer->action_params["route_tee"] = "--tee";
				*dbg << " ROUTE_TEE";
				
#line 2894 "IPTCfgParser.cpp"
			}
			break;
		}
		case TO_SOURCE:
		{
			match(TO_SOURCE);
			if ( inputState->guessing==0 ) {
#line 575 "iptables.g"
				
				*dbg << " TO-SOURCE";
				
#line 2906 "IPTCfgParser.cpp"
			}
			nat_spec();
			break;
		}
		case TO_DESTINATION:
		{
			match(TO_DESTINATION);
			if ( inputState->guessing==0 ) {
#line 581 "iptables.g"
				
				*dbg << " TO-DESTINATION";
				
#line 2919 "IPTCfgParser.cpp"
			}
			nat_spec();
			break;
		}
		case TO_PORTS:
		{
			match(TO_PORTS);
			redirect_spec();
			break;
		}
		case TO_NETMAP:
		{
			match(TO_NETMAP);
			if ( inputState->guessing==0 ) {
#line 589 "iptables.g"
				
				*dbg << " TO-NETMAP";
				
#line 2938 "IPTCfgParser.cpp"
			}
			{
			match(IPV4);
			if ( inputState->guessing==0 ) {
#line 594 "iptables.g"
				
				importer->nat_addr1 = LT(0)->getText();
				importer->nat_addr2 = LT(0)->getText();
				*dbg << LT(0)->getText();
				
#line 2949 "IPTCfgParser.cpp"
			}
			match(SLASH);
			{
			switch ( LA(1)) {
			case IPV4:
			{
				match(IPV4);
				break;
			}
			case INT_CONST:
			{
				match(INT_CONST);
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			if ( inputState->guessing==0 ) {
#line 600 "iptables.g"
				
				importer->nat_nm = LT(0)->getText();
				*dbg << "/" << LT(0)->getText();
				
#line 2976 "IPTCfgParser.cpp"
			}
			}
			break;
		}
		case CLAMP_MSS:
		{
			match(CLAMP_MSS);
			if ( inputState->guessing==0 ) {
#line 607 "iptables.g"
				
				importer->action_params["clamp-mss-to-pmtu"] = "--clamp-mss-to-pmtu";
				*dbg << " TO-NETMAP";
				
#line 2990 "IPTCfgParser.cpp"
			}
			break;
		}
		default:
			if ((LA(1) == SET_TOS) && (LA(2) == HEX_CONST)) {
				match(SET_TOS);
				match(HEX_CONST);
				if ( inputState->guessing==0 ) {
#line 521 "iptables.g"
					
					importer->action_params["set_tos"] = LT(0)->getText();
					*dbg << " SET TOS=" << LT(0)->getText();
					
#line 3004 "IPTCfgParser.cpp"
				}
			}
			else if ((LA(1) == SET_TOS) && (LA(2) == WORD)) {
				match(SET_TOS);
				match(WORD);
				if ( inputState->guessing==0 ) {
#line 527 "iptables.g"
					
					importer->action_params["set_tos"] = LT(0)->getText();
					*dbg << " SET TOS=" << LT(0)->getText();
					
#line 3016 "IPTCfgParser.cpp"
				}
			}
		else {
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::nat_spec() {
	Tracer traceInOut(this, "nat_spec");
	
	try {      // for error handling
		nat_addr_range();
		{
		switch ( LA(1)) {
		case COLON:
		{
			match(COLON);
			nat_port_def_with_range();
			break;
		}
		case NEWLINE:
		case MINUS:
		case UNSUPPORTED_OPTION:
		case OPT_MODULE:
		case OPT_SRC:
		case EXCLAMATION:
		case OPT_DST:
		case OPT_IN_INTF:
		case OPT_OUT_INTF:
		case OPT_PROTO:
		case OPT_TARGET:
		case REJECT_WITH:
		case LOG_PREFIX:
		case LOG_TCP_SEQ:
		case LOG_TCP_OPT:
		case LOG_IP_OPT:
		case ULOG_PREFIX:
		case LOG_LEVEL:
		case SET_MARK:
		case SET_TOS:
		case SAVE_MARK:
		case RESTORE_MARK:
		case CONTINUE:
		case ROUTE_IIF:
		case ROUTE_OIF:
		case ROUTE_GW:
		case ROUTE_TEE:
		case TO_SOURCE:
		case TO_DESTINATION:
		case TO_PORTS:
		case TO_NETMAP:
		case CLAMP_MSS:
		case OPT_FRAGM:
		case MATCH_LIMIT:
		case MATCH_LIMIT_BURST:
		case MATCH_IPRANGE_SRC:
		case MATCH_IPRANGE_DST:
		case MATCH_LENGTH:
		case MATCH_SRC_MULTIPORT:
		case MATCH_DST_MULTIPORT:
		case MATCH_BOTH_MULTIPORT:
		case MATCH_ICMP_TYPE:
		case MATCH_SRC_PORT:
		case MATCH_SRC_PORT_SHORT:
		case MATCH_DST_PORT:
		case MATCH_DST_PORT_SHORT:
		case MATCH_SYN:
		case MATCH_TCP_FLAGS:
		case MATCH_TCP_OPTION:
		{
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 618 "iptables.g"
			
			*dbg << " "
			<< importer->nat_addr1
			<< "-"
			<< importer->nat_addr2
			<< ":"
			<< importer->nat_port_range_start
			<< "-"
			<< importer->nat_port_range_end;
			
#line 3118 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::redirect_spec() {
	Tracer traceInOut(this, "redirect_spec");
	
	try {      // for error handling
		nat_port_def_with_range();
		if ( inputState->guessing==0 ) {
#line 653 "iptables.g"
			
			*dbg << " TO-PORTS "
			<< importer->nat_addr1
			<< "-"
			<< importer->nat_addr2
			<< ":"
			<< importer->nat_port_range_start
			<< "-"
			<< importer->nat_port_range_end;
			
#line 3148 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::nat_addr_range() {
	Tracer traceInOut(this, "nat_addr_range");
	ANTLR_USE_NAMESPACE(antlr)RefToken  a1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  a2 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		bool synPredMatched71 = false;
		if (((LA(1) == IPV4) && (LA(2) == MINUS))) {
			int _m71 = mark();
			synPredMatched71 = true;
			inputState->guessing++;
			try {
				{
				match(IPV4);
				match(MINUS);
				}
			}
			catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& pe) {
				synPredMatched71 = false;
			}
			rewind(_m71);
			inputState->guessing--;
		}
		if ( synPredMatched71 ) {
			{
			a1 = LT(1);
			match(IPV4);
			match(MINUS);
			a2 = LT(1);
			match(IPV4);
			if ( inputState->guessing==0 ) {
#line 634 "iptables.g"
				
				importer->nat_port_range_start = "";
				importer->nat_port_range_end = "";
				importer->nat_addr1 = a1->getText();
				importer->nat_addr2 = a2->getText();
				
#line 3199 "IPTCfgParser.cpp"
			}
			}
		}
		else if ((LA(1) == IPV4) && (_tokenSet_8.member(LA(2)))) {
			match(IPV4);
			if ( inputState->guessing==0 ) {
#line 643 "iptables.g"
				
				importer->nat_port_range_start = "";
				importer->nat_port_range_end = "";
				importer->nat_addr1 = LT(0)->getText();
				importer->nat_addr2 = LT(0)->getText();
				
#line 3213 "IPTCfgParser.cpp"
			}
		}
		else {
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_8);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::nat_port_def_with_range() {
	Tracer traceInOut(this, "nat_port_def_with_range");
	
	try {      // for error handling
		bool synPredMatched140 = false;
		if (((LA(1) == WORD || LA(1) == INT_CONST) && (LA(2) == MINUS))) {
			int _m140 = mark();
			synPredMatched140 = true;
			inputState->guessing++;
			try {
				{
				{
				switch ( LA(1)) {
				case WORD:
				{
					match(WORD);
					break;
				}
				case INT_CONST:
				{
					match(INT_CONST);
					break;
				}
				default:
				{
					throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
				}
				}
				}
				match(MINUS);
				}
			}
			catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& pe) {
				synPredMatched140 = false;
			}
			rewind(_m140);
			inputState->guessing--;
		}
		if ( synPredMatched140 ) {
			{
			{
			switch ( LA(1)) {
			case WORD:
			{
				match(WORD);
				break;
			}
			case INT_CONST:
			{
				match(INT_CONST);
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			if ( inputState->guessing==0 ) {
#line 1023 "iptables.g"
				
				importer->nat_port_range_start = LT(0)->getText();
				importer->nat_port_range_end = LT(0)->getText();
				*dbg << " PORT=" << LT(0)->getText();
				
#line 3296 "IPTCfgParser.cpp"
			}
			match(MINUS);
			{
			switch ( LA(1)) {
			case WORD:
			{
				match(WORD);
				break;
			}
			case INT_CONST:
			{
				match(INT_CONST);
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			if ( inputState->guessing==0 ) {
#line 1029 "iptables.g"
				
				importer->nat_port_range_end = LT(0)->getText();
				*dbg << ":" << LT(0)->getText();
				
#line 3323 "IPTCfgParser.cpp"
			}
			}
		}
		else if ((LA(1) == WORD || LA(1) == INT_CONST) && (_tokenSet_7.member(LA(2)))) {
			{
			switch ( LA(1)) {
			case WORD:
			{
				match(WORD);
				break;
			}
			case INT_CONST:
			{
				match(INT_CONST);
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			if ( inputState->guessing==0 ) {
#line 1036 "iptables.g"
				
				importer->nat_port_range_start = LT(0)->getText();
				importer->nat_port_range_end = LT(0)->getText();
				*dbg << " PORT=" << LT(0)->getText();
				
#line 3353 "IPTCfgParser.cpp"
			}
		}
		else {
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::state_word() {
	Tracer traceInOut(this, "state_word");
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case INVALID:
		{
			match(INVALID);
			break;
		}
		case NEW:
		{
			match(NEW);
			break;
		}
		case ESTABLISHED:
		{
			match(ESTABLISHED);
			break;
		}
		case RELATED:
		{
			match(RELATED);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_9);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::m_mark() {
	Tracer traceInOut(this, "m_mark");
	
	try {      // for error handling
		match(M_MARK);
		if ( inputState->guessing==0 ) {
#line 710 "iptables.g"
			
			*dbg << " MARK";
			
#line 3424 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_10);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::limit_rate() {
	Tracer traceInOut(this, "limit_rate");
	
	try {      // for error handling
		match(INT_CONST);
		if ( inputState->guessing==0 ) {
#line 740 "iptables.g"
			importer->limit_val = LT(0)->getText();
#line 3445 "IPTCfgParser.cpp"
		}
		match(SLASH);
		match(WORD);
		if ( inputState->guessing==0 ) {
#line 742 "iptables.g"
			importer->limit_suffix = LT(0)->getText();
#line 3452 "IPTCfgParser.cpp"
		}
		if ( inputState->guessing==0 ) {
#line 743 "iptables.g"
			
			*dbg << " MATCH LIMIT "
			<< importer->limit_val << "/"
			<< importer->limit_suffix;
			
#line 3461 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::m_recent() {
	Tracer traceInOut(this, "m_recent");
	
	try {      // for error handling
		match(M_RECENT);
		if ( inputState->guessing==0 ) {
#line 760 "iptables.g"
			
			*dbg << " RECENT";
			
#line 3484 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_11);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::recent_opts() {
	Tracer traceInOut(this, "recent_opts");
	
	try {      // for error handling
		switch ( LA(1)) {
		case MATCH_RECENT_SET:
		case MATCH_RECENT_RCHECK:
		case MATCH_RECENT_UPDATE:
		case MATCH_RECENT_REMOVE:
		case MATCH_RECENT_RTTL:
		case RSOURCE:
		case MATCH_RECENT_RDEST:
		{
			recent_args_no_param();
			break;
		}
		case MATCH_RECENT_NAME:
		case MATCH_RECENT_SECONDS:
		case MATCH_RECENT_HITCOUNT:
		{
			recent_args_param();
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_12);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::recent_args_no_param() {
	Tracer traceInOut(this, "recent_args_no_param");
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case MATCH_RECENT_SET:
		{
			match(MATCH_RECENT_SET);
			break;
		}
		case MATCH_RECENT_RCHECK:
		{
			match(MATCH_RECENT_RCHECK);
			break;
		}
		case MATCH_RECENT_UPDATE:
		{
			match(MATCH_RECENT_UPDATE);
			break;
		}
		case MATCH_RECENT_REMOVE:
		{
			match(MATCH_RECENT_REMOVE);
			break;
		}
		case MATCH_RECENT_RTTL:
		{
			match(MATCH_RECENT_RTTL);
			break;
		}
		case RSOURCE:
		{
			match(RSOURCE);
			break;
		}
		case MATCH_RECENT_RDEST:
		{
			match(MATCH_RECENT_RDEST);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 812 "iptables.g"
			importer->recent_match += LT(0)->getText() + " ";
#line 3586 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_12);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::recent_args_param() {
	Tracer traceInOut(this, "recent_args_param");
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case MATCH_RECENT_NAME:
		{
			match(MATCH_RECENT_NAME);
			break;
		}
		case MATCH_RECENT_SECONDS:
		{
			match(MATCH_RECENT_SECONDS);
			break;
		}
		case MATCH_RECENT_HITCOUNT:
		{
			match(MATCH_RECENT_HITCOUNT);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 816 "iptables.g"
			importer->recent_match += LT(0)->getText() + " ";
#line 3629 "IPTCfgParser.cpp"
		}
		{
		switch ( LA(1)) {
		case INT_CONST:
		{
			match(INT_CONST);
			break;
		}
		case WORD:
		{
			match(WORD);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 818 "iptables.g"
			importer->recent_match += LT(0)->getText() + " ";
#line 3652 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_12);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::length_spec() {
	Tracer traceInOut(this, "length_spec");
	
	try {      // for error handling
		match(INT_CONST);
		if ( inputState->guessing==0 ) {
#line 835 "iptables.g"
			importer->length_spec = LT(0)->getText();
#line 3673 "IPTCfgParser.cpp"
		}
		match(COLON);
		match(INT_CONST);
		if ( inputState->guessing==0 ) {
#line 837 "iptables.g"
			importer->length_spec += ":";
			importer->length_spec += LT(0)->getText();
#line 3681 "IPTCfgParser.cpp"
		}
		if ( inputState->guessing==0 ) {
#line 839 "iptables.g"
			
			*dbg << " MATCH LENGTH " << importer->length_spec;
			
#line 3688 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::pkt_type_spec() {
	Tracer traceInOut(this, "pkt_type_spec");
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case WORD_BROADCAST:
		{
			match(WORD_BROADCAST);
			break;
		}
		case WORD_MULTICAST:
		{
			match(WORD_MULTICAST);
			break;
		}
		case WORD_UNICAST:
		{
			match(WORD_UNICAST);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 850 "iptables.g"
			
			importer->pkt_type_spec = LT(0)->getText();
			*dbg << " PKT_TYPE " << importer->pkt_type_spec;
			
#line 3734 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::port_def_no_range() {
	Tracer traceInOut(this, "port_def_no_range");
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case WORD:
		{
			match(WORD);
			break;
		}
		case INT_CONST:
		{
			match(INT_CONST);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 976 "iptables.g"
			
			importer->tmp_port_range_start = LT(0)->getText();
			importer->tmp_port_range_end = LT(0)->getText();
			*dbg << " PORT=" << LT(0)->getText();
			
#line 3776 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_9);
		} else {
			throw;
		}
	}
}

/****************************************************************
 * port definition that allows for port range. That parser should
 * recognize constructs
 *
 * port1         ---> range_start = range_end = port1
 * port1:port2   ---> range_start = port1  range_end = port2
 * port1:        ---> range_start = port1  range_end = 65535
 * :port2        ---> range_start = 0      range_end = port2
 */
void IPTCfgParser::port_def_with_range() {
	Tracer traceInOut(this, "port_def_with_range");
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case WORD:
		{
			match(WORD);
			break;
		}
		case INT_CONST:
		{
			match(INT_CONST);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 994 "iptables.g"
			
			importer->tmp_port_range_start = LT(0)->getText();
			importer->tmp_port_range_end = LT(0)->getText();
			*dbg << " PORT=" << LT(0)->getText();
			
#line 3827 "IPTCfgParser.cpp"
		}
		{
		switch ( LA(1)) {
		case COLON:
		{
			match(COLON);
			{
			switch ( LA(1)) {
			case WORD:
			{
				match(WORD);
				break;
			}
			case INT_CONST:
			{
				match(INT_CONST);
				break;
			}
			case NEWLINE:
			case MINUS:
			case UNSUPPORTED_OPTION:
			case OPT_MODULE:
			case OPT_SRC:
			case EXCLAMATION:
			case OPT_DST:
			case OPT_IN_INTF:
			case OPT_OUT_INTF:
			case OPT_PROTO:
			case OPT_TARGET:
			case OPT_FRAGM:
			case MATCH_LIMIT:
			case MATCH_LIMIT_BURST:
			case MATCH_IPRANGE_SRC:
			case MATCH_IPRANGE_DST:
			case MATCH_LENGTH:
			case MATCH_SRC_MULTIPORT:
			case MATCH_DST_MULTIPORT:
			case MATCH_BOTH_MULTIPORT:
			case MATCH_ICMP_TYPE:
			case MATCH_SRC_PORT:
			case MATCH_SRC_PORT_SHORT:
			case MATCH_DST_PORT:
			case MATCH_DST_PORT_SHORT:
			case MATCH_SYN:
			case MATCH_TCP_FLAGS:
			case MATCH_TCP_OPTION:
			{
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			if ( inputState->guessing==0 ) {
#line 1001 "iptables.g"
				
				importer->tmp_port_range_end = LT(0)->getText();
				*dbg << ":" << LT(0)->getText();
				
#line 3889 "IPTCfgParser.cpp"
			}
			break;
		}
		case NEWLINE:
		case MINUS:
		case UNSUPPORTED_OPTION:
		case OPT_MODULE:
		case OPT_SRC:
		case EXCLAMATION:
		case OPT_DST:
		case OPT_IN_INTF:
		case OPT_OUT_INTF:
		case OPT_PROTO:
		case OPT_TARGET:
		case OPT_FRAGM:
		case MATCH_LIMIT:
		case MATCH_LIMIT_BURST:
		case MATCH_IPRANGE_SRC:
		case MATCH_IPRANGE_DST:
		case MATCH_LENGTH:
		case MATCH_SRC_MULTIPORT:
		case MATCH_DST_MULTIPORT:
		case MATCH_BOTH_MULTIPORT:
		case MATCH_ICMP_TYPE:
		case MATCH_SRC_PORT:
		case MATCH_SRC_PORT_SHORT:
		case MATCH_DST_PORT:
		case MATCH_DST_PORT_SHORT:
		case MATCH_SYN:
		case MATCH_TCP_FLAGS:
		case MATCH_TCP_OPTION:
		{
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::port_def_with_incomplete_range() {
	Tracer traceInOut(this, "port_def_with_incomplete_range");
	
	try {      // for error handling
		match(COLON);
		{
		switch ( LA(1)) {
		case WORD:
		{
			match(WORD);
			break;
		}
		case INT_CONST:
		{
			match(INT_CONST);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 1010 "iptables.g"
			
			importer->tmp_port_range_start = "0";
			importer->tmp_port_range_end = LT(0)->getText();
			*dbg << "PORT 0:" << LT(0)->getText();
			
#line 3971 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::syn() {
	Tracer traceInOut(this, "syn");
	
	try {      // for error handling
		match(MATCH_SYN);
		if ( inputState->guessing==0 ) {
#line 1099 "iptables.g"
			
			importer->tcp_flags_mask.clear();
			importer->tcp_flags_mask.push_back(libfwbuilder::TCPService::SYN);
			importer->tcp_flags_mask.push_back(libfwbuilder::TCPService::RST);
			importer->tcp_flags_mask.push_back(libfwbuilder::TCPService::ACK);
			
			importer->tcp_flags_comp.clear();
			importer->tcp_flags_comp.push_back(libfwbuilder::TCPService::SYN);
			
#line 4000 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::tcp_flags() {
	Tracer traceInOut(this, "tcp_flags");
	
	try {      // for error handling
		match(MATCH_TCP_FLAGS);
		tcp_flags_list();
		if ( inputState->guessing==0 ) {
#line 1150 "iptables.g"
			
			importer->tcp_flags_mask = importer->tmp_tcp_flags_list;
			importer->tmp_tcp_flags_list.clear();
			
#line 4025 "IPTCfgParser.cpp"
		}
		tcp_flags_list();
		if ( inputState->guessing==0 ) {
#line 1155 "iptables.g"
			
			importer->tcp_flags_comp = importer->tmp_tcp_flags_list;
			importer->tmp_tcp_flags_list.clear();
			*dbg << " TCP FLAGS=";
			foreach(int x, importer->tcp_flags_mask)
			*dbg << x << "|";
			*dbg << " ";
			foreach(int x, importer->tcp_flags_comp)
			*dbg << x << "|";
			
#line 4040 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::tcp_option() {
	Tracer traceInOut(this, "tcp_option");
	
	try {      // for error handling
		match(MATCH_TCP_OPTION);
		{
		switch ( LA(1)) {
		case INT_CONST:
		{
			match(INT_CONST);
			break;
		}
		case EXCLAMATION:
		{
			match(EXCLAMATION);
			match(INT_CONST);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::tcp_flag_word() {
	Tracer traceInOut(this, "tcp_flag_word");
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case SYN:
		{
			match(SYN);
			if ( inputState->guessing==0 ) {
#line 1112 "iptables.g"
				importer->tmp_tcp_flag_code = libfwbuilder::TCPService::SYN;
#line 4100 "IPTCfgParser.cpp"
			}
			break;
		}
		case ACK:
		{
			match(ACK);
			if ( inputState->guessing==0 ) {
#line 1114 "iptables.g"
				importer->tmp_tcp_flag_code = libfwbuilder::TCPService::ACK;
#line 4110 "IPTCfgParser.cpp"
			}
			break;
		}
		case FIN:
		{
			match(FIN);
			if ( inputState->guessing==0 ) {
#line 1116 "iptables.g"
				importer->tmp_tcp_flag_code = libfwbuilder::TCPService::FIN;
#line 4120 "IPTCfgParser.cpp"
			}
			break;
		}
		case RST:
		{
			match(RST);
			if ( inputState->guessing==0 ) {
#line 1118 "iptables.g"
				importer->tmp_tcp_flag_code = libfwbuilder::TCPService::RST;
#line 4130 "IPTCfgParser.cpp"
			}
			break;
		}
		case URG:
		{
			match(URG);
			if ( inputState->guessing==0 ) {
#line 1120 "iptables.g"
				importer->tmp_tcp_flag_code = libfwbuilder::TCPService::URG;
#line 4140 "IPTCfgParser.cpp"
			}
			break;
		}
		case PSH:
		{
			match(PSH);
			if ( inputState->guessing==0 ) {
#line 1122 "iptables.g"
				importer->tmp_tcp_flag_code = libfwbuilder::TCPService::PSH;
#line 4150 "IPTCfgParser.cpp"
			}
			break;
		}
		case ALL:
		{
			match(ALL);
			if ( inputState->guessing==0 ) {
#line 1124 "iptables.g"
				importer->tmp_tcp_flag_code = 99;
#line 4160 "IPTCfgParser.cpp"
			}
			break;
		}
		case NONE:
		{
			match(NONE);
			if ( inputState->guessing==0 ) {
#line 1126 "iptables.g"
				importer->tmp_tcp_flag_code = 98;
#line 4170 "IPTCfgParser.cpp"
			}
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_13);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::tcp_flags_list() {
	Tracer traceInOut(this, "tcp_flags_list");
	
	try {      // for error handling
		if ( inputState->guessing==0 ) {
#line 1131 "iptables.g"
			
			importer->tmp_tcp_flags_list.clear();
			importer->tmp_tcp_flag_code = 0;
			
#line 4201 "IPTCfgParser.cpp"
		}
		tcp_flag_word();
		if ( inputState->guessing==0 ) {
#line 1136 "iptables.g"
			
			importer->tmp_tcp_flags_list.push_back(importer->tmp_tcp_flag_code);
			
#line 4209 "IPTCfgParser.cpp"
		}
		{ // ( ... )*
		for (;;) {
			if ((LA(1) == COMMA)) {
				match(COMMA);
				tcp_flag_word();
				if ( inputState->guessing==0 ) {
#line 1141 "iptables.g"
					
					importer->tmp_tcp_flags_list.push_back(
					importer->tmp_tcp_flag_code);
					
#line 4222 "IPTCfgParser.cpp"
				}
			}
			else {
				goto _loop162;
			}
			
		}
		_loop162:;
		} // ( ... )*
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_14);
		} else {
			throw;
		}
	}
}

void IPTCfgParser::initializeASTFactory( ANTLR_USE_NAMESPACE(antlr)ASTFactory& )
{
}
const char* IPTCfgParser::tokenNames[] = {
	"<0>",
	"EOF",
	"<2>",
	"NULL_TREE_LOOKAHEAD",
	"NEWLINE",
	"NUMBER_SIGN",
	"IPTABLES_SAVE_HEADER",
	"THREE_COMPONENT_VERSION",
	"IPV4",
	"\"COMMIT\"",
	"STAR",
	"WORD",
	"\"INPUT\"",
	"\"FORWARD\"",
	"\"OUTPUT\"",
	"\"PREROUTING\"",
	"\"POSTROUTING\"",
	"COLON",
	"MINUS",
	"OPENING_SQUARE",
	"INT_CONST",
	"CLOSING_SQUARE",
	"ADD_RULE",
	"UNSUPPORTED_OPTION",
	"DIGIT",
	"SLASH",
	"OPT_MODULE",
	"OPT_SRC",
	"EXCLAMATION",
	"OPT_DST",
	"OPT_IN_INTF",
	"OPT_OUT_INTF",
	"\"tcp\"",
	"\"udp\"",
	"\"icmp\"",
	"OPT_PROTO",
	"OPT_TARGET",
	"REJECT_WITH",
	"LOG_PREFIX",
	"STRING",
	"LOG_TCP_SEQ",
	"LOG_TCP_OPT",
	"LOG_IP_OPT",
	"ULOG_PREFIX",
	"LOG_LEVEL",
	"SET_MARK",
	"HEX_CONST",
	"SET_TOS",
	"SAVE_MARK",
	"RESTORE_MARK",
	"CONTINUE",
	"ROUTE_IIF",
	"ROUTE_OIF",
	"ROUTE_GW",
	"ROUTE_TEE",
	"TO_SOURCE",
	"TO_DESTINATION",
	"TO_PORTS",
	"TO_NETMAP",
	"CLAMP_MSS",
	"OPT_FRAGM",
	"\"INVALID\"",
	"\"NEW\"",
	"\"ESTABLISHED\"",
	"\"RELATED\"",
	"\"state\"",
	"MATCH_STATE",
	"COMMA",
	"\"mark\"",
	"MATCH_MARK",
	"\"limit\"",
	"MATCH_LIMIT",
	"MATCH_LIMIT_BURST",
	"\"recent\"",
	"\"iprange\"",
	"MATCH_IPRANGE_SRC",
	"MATCH_IPRANGE_DST",
	"MATCH_RECENT_SET",
	"MATCH_RECENT_RCHECK",
	"MATCH_RECENT_UPDATE",
	"MATCH_RECENT_REMOVE",
	"MATCH_RECENT_RTTL",
	"RSOURCE",
	"MATCH_RECENT_RDEST",
	"MATCH_RECENT_NAME",
	"MATCH_RECENT_SECONDS",
	"MATCH_RECENT_HITCOUNT",
	"\"length\"",
	"MATCH_LENGTH",
	"\"pkttype\"",
	"MATCH_PKT_TYPE",
	"\"broadcast\"",
	"\"multicast\"",
	"\"unicast\"",
	"\"multiport\"",
	"\"comment\"",
	"MATCH_COMMENT",
	"MATCH_SRC_MULTIPORT",
	"MATCH_DST_MULTIPORT",
	"MATCH_BOTH_MULTIPORT",
	"MATCH_ICMP_TYPE",
	"MATCH_SRC_PORT",
	"MATCH_SRC_PORT_SHORT",
	"MATCH_DST_PORT",
	"MATCH_DST_PORT_SHORT",
	"MATCH_SYN",
	"\"SYN\"",
	"\"ACK\"",
	"\"FIN\"",
	"\"RST\"",
	"\"URG\"",
	"\"PSH\"",
	"\"ALL\"",
	"\"NONE\"",
	"MATCH_TCP_FLAGS",
	"MATCH_TCP_OPTION",
	"Whitespace",
	"IPV6",
	"MAC_ADDRESS",
	"NEG_INT_CONST",
	"HEXDIGIT",
	"NUM_3DIGIT",
	"NUM_HEX_4DIGIT",
	"NUMBER",
	"ULOG_QTHR",
	"ULOG_NLG",
	"ULOG_CPR",
	"PERCENT",
	"AMPERSAND",
	"APOSTROPHE",
	"OPENING_PAREN",
	"CLOSING_PAREN",
	"PLUS",
	"DOT",
	"SEMICOLON",
	"LESS_THAN",
	"EQUALS",
	"GREATER_THAN",
	"QUESTION",
	"COMMERCIAL_AT",
	"CARET",
	"UNDERLINE",
	"OPENING_BRACE",
	"CLOSING_BRACE",
	"TILDE",
	0
};

const unsigned long IPTCfgParser::_tokenSet_0_data_[] = { 2UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// EOF 
const ANTLR_USE_NAMESPACE(antlr)BitSet IPTCfgParser::_tokenSet_0(_tokenSet_0_data_,6);
const unsigned long IPTCfgParser::_tokenSet_1_data_[] = { 4326962UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// EOF NEWLINE NUMBER_SIGN "COMMIT" STAR COLON ADD_RULE 
const ANTLR_USE_NAMESPACE(antlr)BitSet IPTCfgParser::_tokenSet_1(_tokenSet_1_data_,6);
const unsigned long IPTCfgParser::_tokenSet_2_data_[] = { 4236509184UL, 268435480UL, 16783744UL, 787454UL, 0UL, 0UL, 0UL, 0UL };
// MINUS UNSUPPORTED_OPTION OPT_MODULE OPT_SRC EXCLAMATION OPT_DST OPT_IN_INTF 
// OPT_OUT_INTF OPT_PROTO OPT_TARGET OPT_FRAGM MATCH_LIMIT MATCH_LIMIT_BURST 
// MATCH_IPRANGE_SRC MATCH_IPRANGE_DST MATCH_LENGTH MATCH_SRC_MULTIPORT 
// MATCH_DST_MULTIPORT MATCH_BOTH_MULTIPORT MATCH_ICMP_TYPE MATCH_SRC_PORT 
// MATCH_SRC_PORT_SHORT MATCH_DST_PORT MATCH_DST_PORT_SHORT MATCH_SYN MATCH_TCP_FLAGS 
// MATCH_TCP_OPTION 
const ANTLR_USE_NAMESPACE(antlr)BitSet IPTCfgParser::_tokenSet_2(_tokenSet_2_data_,8);
const unsigned long IPTCfgParser::_tokenSet_3_data_[] = { 4236511232UL, 268435480UL, 16783744UL, 787454UL, 0UL, 0UL, 0UL, 0UL };
// WORD MINUS UNSUPPORTED_OPTION OPT_MODULE OPT_SRC EXCLAMATION OPT_DST 
// OPT_IN_INTF OPT_OUT_INTF OPT_PROTO OPT_TARGET OPT_FRAGM MATCH_LIMIT 
// MATCH_LIMIT_BURST MATCH_IPRANGE_SRC MATCH_IPRANGE_DST MATCH_LENGTH MATCH_SRC_MULTIPORT 
// MATCH_DST_MULTIPORT MATCH_BOTH_MULTIPORT MATCH_ICMP_TYPE MATCH_SRC_PORT 
// MATCH_SRC_PORT_SHORT MATCH_DST_PORT MATCH_DST_PORT_SHORT MATCH_SYN MATCH_TCP_FLAGS 
// MATCH_TCP_OPTION 
const ANTLR_USE_NAMESPACE(antlr)BitSet IPTCfgParser::_tokenSet_3(_tokenSet_3_data_,8);
const unsigned long IPTCfgParser::_tokenSet_4_data_[] = { 2048UL, 7UL, 3263169602UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// WORD "tcp" "udp" "icmp" "state" "limit" "iprange" "length" "pkttype" 
// "multiport" "comment" 
const ANTLR_USE_NAMESPACE(antlr)BitSet IPTCfgParser::_tokenSet_4(_tokenSet_4_data_,8);
const unsigned long IPTCfgParser::_tokenSet_5_data_[] = { 4236509200UL, 268435480UL, 16783744UL, 787454UL, 0UL, 0UL, 0UL, 0UL };
// NEWLINE MINUS UNSUPPORTED_OPTION OPT_MODULE OPT_SRC EXCLAMATION OPT_DST 
// OPT_IN_INTF OPT_OUT_INTF OPT_PROTO OPT_TARGET OPT_FRAGM MATCH_LIMIT 
// MATCH_LIMIT_BURST MATCH_IPRANGE_SRC MATCH_IPRANGE_DST MATCH_LENGTH MATCH_SRC_MULTIPORT 
// MATCH_DST_MULTIPORT MATCH_BOTH_MULTIPORT MATCH_ICMP_TYPE MATCH_SRC_PORT 
// MATCH_SRC_PORT_SHORT MATCH_DST_PORT MATCH_DST_PORT_SHORT MATCH_SYN MATCH_TCP_FLAGS 
// MATCH_TCP_OPTION 
const ANTLR_USE_NAMESPACE(antlr)BitSet IPTCfgParser::_tokenSet_5(_tokenSet_5_data_,8);
const unsigned long IPTCfgParser::_tokenSet_6_data_[] = { 0UL, 268418912UL, 0UL, 0UL, 0UL, 0UL };
// REJECT_WITH LOG_PREFIX LOG_TCP_SEQ LOG_TCP_OPT LOG_IP_OPT ULOG_PREFIX 
// LOG_LEVEL SET_MARK SET_TOS SAVE_MARK RESTORE_MARK CONTINUE ROUTE_IIF 
// ROUTE_OIF ROUTE_GW ROUTE_TEE TO_SOURCE TO_DESTINATION TO_PORTS TO_NETMAP 
// CLAMP_MSS 
const ANTLR_USE_NAMESPACE(antlr)BitSet IPTCfgParser::_tokenSet_6(_tokenSet_6_data_,6);
const unsigned long IPTCfgParser::_tokenSet_7_data_[] = { 4236509200UL, 536854392UL, 16783744UL, 787454UL, 0UL, 0UL, 0UL, 0UL };
// NEWLINE MINUS UNSUPPORTED_OPTION OPT_MODULE OPT_SRC EXCLAMATION OPT_DST 
// OPT_IN_INTF OPT_OUT_INTF OPT_PROTO OPT_TARGET REJECT_WITH LOG_PREFIX 
// LOG_TCP_SEQ LOG_TCP_OPT LOG_IP_OPT ULOG_PREFIX LOG_LEVEL SET_MARK SET_TOS 
// SAVE_MARK RESTORE_MARK CONTINUE ROUTE_IIF ROUTE_OIF ROUTE_GW ROUTE_TEE 
// TO_SOURCE TO_DESTINATION TO_PORTS TO_NETMAP CLAMP_MSS OPT_FRAGM MATCH_LIMIT 
// MATCH_LIMIT_BURST MATCH_IPRANGE_SRC MATCH_IPRANGE_DST MATCH_LENGTH MATCH_SRC_MULTIPORT 
// MATCH_DST_MULTIPORT MATCH_BOTH_MULTIPORT MATCH_ICMP_TYPE MATCH_SRC_PORT 
// MATCH_SRC_PORT_SHORT MATCH_DST_PORT MATCH_DST_PORT_SHORT MATCH_SYN MATCH_TCP_FLAGS 
// MATCH_TCP_OPTION 
const ANTLR_USE_NAMESPACE(antlr)BitSet IPTCfgParser::_tokenSet_7(_tokenSet_7_data_,8);
const unsigned long IPTCfgParser::_tokenSet_8_data_[] = { 4236640272UL, 536854392UL, 16783744UL, 787454UL, 0UL, 0UL, 0UL, 0UL };
// NEWLINE COLON MINUS UNSUPPORTED_OPTION OPT_MODULE OPT_SRC EXCLAMATION 
// OPT_DST OPT_IN_INTF OPT_OUT_INTF OPT_PROTO OPT_TARGET REJECT_WITH LOG_PREFIX 
// LOG_TCP_SEQ LOG_TCP_OPT LOG_IP_OPT ULOG_PREFIX LOG_LEVEL SET_MARK SET_TOS 
// SAVE_MARK RESTORE_MARK CONTINUE ROUTE_IIF ROUTE_OIF ROUTE_GW ROUTE_TEE 
// TO_SOURCE TO_DESTINATION TO_PORTS TO_NETMAP CLAMP_MSS OPT_FRAGM MATCH_LIMIT 
// MATCH_LIMIT_BURST MATCH_IPRANGE_SRC MATCH_IPRANGE_DST MATCH_LENGTH MATCH_SRC_MULTIPORT 
// MATCH_DST_MULTIPORT MATCH_BOTH_MULTIPORT MATCH_ICMP_TYPE MATCH_SRC_PORT 
// MATCH_SRC_PORT_SHORT MATCH_DST_PORT MATCH_DST_PORT_SHORT MATCH_SYN MATCH_TCP_FLAGS 
// MATCH_TCP_OPTION 
const ANTLR_USE_NAMESPACE(antlr)BitSet IPTCfgParser::_tokenSet_8(_tokenSet_8_data_,8);
const unsigned long IPTCfgParser::_tokenSet_9_data_[] = { 4236509200UL, 268435480UL, 16783752UL, 787454UL, 0UL, 0UL, 0UL, 0UL };
// NEWLINE MINUS UNSUPPORTED_OPTION OPT_MODULE OPT_SRC EXCLAMATION OPT_DST 
// OPT_IN_INTF OPT_OUT_INTF OPT_PROTO OPT_TARGET OPT_FRAGM COMMA MATCH_LIMIT 
// MATCH_LIMIT_BURST MATCH_IPRANGE_SRC MATCH_IPRANGE_DST MATCH_LENGTH MATCH_SRC_MULTIPORT 
// MATCH_DST_MULTIPORT MATCH_BOTH_MULTIPORT MATCH_ICMP_TYPE MATCH_SRC_PORT 
// MATCH_SRC_PORT_SHORT MATCH_DST_PORT MATCH_DST_PORT_SHORT MATCH_SYN MATCH_TCP_FLAGS 
// MATCH_TCP_OPTION 
const ANTLR_USE_NAMESPACE(antlr)BitSet IPTCfgParser::_tokenSet_9(_tokenSet_9_data_,8);
const unsigned long IPTCfgParser::_tokenSet_10_data_[] = { 268435456UL, 0UL, 32UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// EXCLAMATION MATCH_MARK 
const ANTLR_USE_NAMESPACE(antlr)BitSet IPTCfgParser::_tokenSet_10(_tokenSet_10_data_,8);
const unsigned long IPTCfgParser::_tokenSet_11_data_[] = { 0UL, 0UL, 8380416UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// MATCH_RECENT_SET MATCH_RECENT_RCHECK MATCH_RECENT_UPDATE MATCH_RECENT_REMOVE 
// MATCH_RECENT_RTTL RSOURCE MATCH_RECENT_RDEST MATCH_RECENT_NAME MATCH_RECENT_SECONDS 
// MATCH_RECENT_HITCOUNT 
const ANTLR_USE_NAMESPACE(antlr)BitSet IPTCfgParser::_tokenSet_11(_tokenSet_11_data_,8);
const unsigned long IPTCfgParser::_tokenSet_12_data_[] = { 4236509200UL, 268435480UL, 25164160UL, 787454UL, 0UL, 0UL, 0UL, 0UL };
// NEWLINE MINUS UNSUPPORTED_OPTION OPT_MODULE OPT_SRC EXCLAMATION OPT_DST 
// OPT_IN_INTF OPT_OUT_INTF OPT_PROTO OPT_TARGET OPT_FRAGM MATCH_LIMIT 
// MATCH_LIMIT_BURST MATCH_IPRANGE_SRC MATCH_IPRANGE_DST MATCH_RECENT_SET 
// MATCH_RECENT_RCHECK MATCH_RECENT_UPDATE MATCH_RECENT_REMOVE MATCH_RECENT_RTTL 
// RSOURCE MATCH_RECENT_RDEST MATCH_RECENT_NAME MATCH_RECENT_SECONDS MATCH_RECENT_HITCOUNT 
// MATCH_LENGTH MATCH_SRC_MULTIPORT MATCH_DST_MULTIPORT MATCH_BOTH_MULTIPORT 
// MATCH_ICMP_TYPE MATCH_SRC_PORT MATCH_SRC_PORT_SHORT MATCH_DST_PORT MATCH_DST_PORT_SHORT 
// MATCH_SYN MATCH_TCP_FLAGS MATCH_TCP_OPTION 
const ANTLR_USE_NAMESPACE(antlr)BitSet IPTCfgParser::_tokenSet_12(_tokenSet_12_data_,8);
const unsigned long IPTCfgParser::_tokenSet_13_data_[] = { 4236509200UL, 268435480UL, 16783752UL, 1048574UL, 0UL, 0UL, 0UL, 0UL };
// NEWLINE MINUS UNSUPPORTED_OPTION OPT_MODULE OPT_SRC EXCLAMATION OPT_DST 
// OPT_IN_INTF OPT_OUT_INTF OPT_PROTO OPT_TARGET OPT_FRAGM COMMA MATCH_LIMIT 
// MATCH_LIMIT_BURST MATCH_IPRANGE_SRC MATCH_IPRANGE_DST MATCH_LENGTH MATCH_SRC_MULTIPORT 
// MATCH_DST_MULTIPORT MATCH_BOTH_MULTIPORT MATCH_ICMP_TYPE MATCH_SRC_PORT 
// MATCH_SRC_PORT_SHORT MATCH_DST_PORT MATCH_DST_PORT_SHORT MATCH_SYN "SYN" 
// "ACK" "FIN" "RST" "URG" "PSH" "ALL" "NONE" MATCH_TCP_FLAGS MATCH_TCP_OPTION 
const ANTLR_USE_NAMESPACE(antlr)BitSet IPTCfgParser::_tokenSet_13(_tokenSet_13_data_,8);
const unsigned long IPTCfgParser::_tokenSet_14_data_[] = { 4236509200UL, 268435480UL, 16783744UL, 1048574UL, 0UL, 0UL, 0UL, 0UL };
// NEWLINE MINUS UNSUPPORTED_OPTION OPT_MODULE OPT_SRC EXCLAMATION OPT_DST 
// OPT_IN_INTF OPT_OUT_INTF OPT_PROTO OPT_TARGET OPT_FRAGM MATCH_LIMIT 
// MATCH_LIMIT_BURST MATCH_IPRANGE_SRC MATCH_IPRANGE_DST MATCH_LENGTH MATCH_SRC_MULTIPORT 
// MATCH_DST_MULTIPORT MATCH_BOTH_MULTIPORT MATCH_ICMP_TYPE MATCH_SRC_PORT 
// MATCH_SRC_PORT_SHORT MATCH_DST_PORT MATCH_DST_PORT_SHORT MATCH_SYN "SYN" 
// "ACK" "FIN" "RST" "URG" "PSH" "ALL" "NONE" MATCH_TCP_FLAGS MATCH_TCP_OPTION 
const ANTLR_USE_NAMESPACE(antlr)BitSet IPTCfgParser::_tokenSet_14(_tokenSet_14_data_,8);


