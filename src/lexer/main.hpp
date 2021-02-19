#ifndef lexer
#define lexer
#include <vector>
#include <string>
using namespace std;
class Position{
	public:
	int idx = 0;
	int ln = 0;
	int col = 0;
	string fn = "";
	string ftxt = "";
	bool operator !=(const Position& p) {
		if (idx == p.idx && ln == p.ln && col == p.col && fn == p.fn && ftxt == p.ftxt){
			return false;
		}
		return true;
	}
	bool operator ==(const Position& p) {
		if (idx == p.idx && ln == p.ln && col == p.col && fn == p.fn && ftxt == p.ftxt){
			return true;
		}
		return false;
	}
	Position(int idx, int ln, int col, string fn, string ftxt){
		this->idx = idx;
		this->ln = ln;
		this->col = col;
		this->fn = fn;
		this->ftxt = ftxt;
	}
	Position advance (string current_char=NULL){
		idx += 1;
		col += 1;

		if (current_char.find('\n')<1){
		ln += 1;
		col = 0;
		}
		return Position(idx, ln, col, fn, ftxt);
	}
	Position & copy(){
		return Position(idx, ln, col, fn, ftxt);
	}
};
class Token{
	private:
		string _type;
		int id = 0;
		Position pos_start = Position(-1,0,-1,"","");
		Position pos_end = Position(-1,0,-1,"","");
		string valuestr = NULL;
		int valueint = NULL;
		float valuefloat = NULL;
	public:
	void testpos(Position posStart, Position posEnd){
		if (posStart != Position(-1,-1,-1,"","")){
			this->pos_start = posStart.copy();
			this->pos_end = posStart.copy();
			this->pos_end.advance();
		}
		if(posEnd != Position(-1,-1,-1,"","")){
			this->pos_end = posEnd.copy();
		}
	}
	Token(string type, Position posStart=Position(-1,-1,-1,"",""), Position posEnd=Position(-1,-1,-1,"","")){
		this->_type = type;
		this->id = 0;
	}
	Token(string type, int value, Position posStart=Position(-1,-1,-1,"",""), Position posEnd=Position(-1,-1,-1,"","")){
		this->_type = type;
		this->valueint = value;
		this->id = 1;
	}
	Token(string type, float value, Position posStart=Position(-1,-1,-1,"",""), Position posEnd=Position(-1,-1,-1,"","")){
		this->_type = type;
		this->valuefloat = value;
		this->id = 2;
	}
	Token(string type, string value, Position posStart=Position(-1,-1,-1,"",""), Position posEnd=Position(-1,-1,-1,"","")){
		this->_type = type;
		this->valuestr = value;
		this->id = 3;
	}
	string repr(){
		string i;
		switch (this->id)
		{
		case 0:
			i = "(type: " + _type + " )";
			return i;
			break;
		case 1:
			i = "(type: " + _type + ", value: " + to_string(this->valueint) + " )";
			return i;
		case 2:
			i = "(type: " + _type + ", value: " + to_string(this->valuefloat) + " )";
			return i;
		default:
			i = "(type: " + _type + ", value: " + this->valuestr + " )";
			return i;
		}

	}
};

//tokens types
const string t_com = "com"; // ,
const string t_dot = "dot"; // .
const string t_int = "int";
const string t_float = "float";
const string t_string = "string";
const string t_identifier = "id";//identifier
const string t_plus = "plus";
const string t_minus = "minus";
const string t_mult = "mult";
const string t_div = "div";
const string t_pow = "pow";
const string t_eq = "eq";//equals
const string t_lp = "lp";// (
const string t_rp = "rp";// )
const string t_lsq = "lsq"; // [
const string t_rsq = "rsq"; // ]
const string t_lcb = "lcb"; // {
const string t_rcb = "rcb"; // }
const string t_et = "et"; // ==
const string t_ne = "ne"; // !=
const string t_lt = "lt"; // <
const string t_gt = "gt"; // >
const string t_gte = "gte"; // >=
const string t_lte = "lte"; // <=
const string t_aa = "aa"; // +=
const string t_as = "as"; // -=
const string t_am = "am"; // *=
const string t_ad = "ad"; // /=
const string t_ap = "ap"; // **=
const string t_bta = "bta"; // &
const string t_bto = "bto"; // |
const string t_btx = "btx"; // ^
const string t_oc = "oc"; // ~
const string t_abta = "abta"; // &=
const string t_abto = "abto"; // |=
const string t_abtx = "abtx"; // ^=
const string t_aoc = "aoc"; // ~=
const string t_ls = "ls"; // <<
const string t_lrs = "lrs"; // >>
const string t_ars = "ars"; // >>>
const string t_als = "als"; // <<=
const string t_alrs = "alrs"; // >>=
const string t_aars = "aars"; // >>>=
const string t_fa = "fa"; // >+
const string t_ter = "ter"; // "?" (not an unknown char, the question mark)
const string t_nl = "nl"; // \n
const string t_eof = "eof";
const string numbers = "0123456789";
const string text = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

class Lexer{
	private:
	string fn;
	string text;
	Position pos = Position(-1,0,-1, "", "");
	string current_char;
	public:
	Lexer(string fn, string txt){
		this->fn = fn;
		this->text = text;
		this->pos = Position(-1, 0, -1, fn, text);
		this->current_char = "";
		this->advance();
	}
	void advance(){
		pos.advance(current_char);
		if (pos.idx < text.size()){
			current_char = text[pos.idx];
		} else {
			current_char = "\0";
		}
	}
	Token makeText(){

	}
	Token makeIdentifier(){

	}
	Token makeNumber(){

	}
	void skip_comment(){

	}
	vector<Token> makeTokens(){
		vector<Token> tokens;
		while (current_char != "\0"){
			if (string(" \t").find(current_char)){
				this->advance();
			} 
			else if (!(current_char.compare(string("#")))){
				this->skip_comment();
			} 
			else if (string(";\n").find(current_char)){
				tokens.push_back((Token(t_nl, this->pos)));
				this->advance();
			} 
			else if (numbers.compare(current_char)){
				tokens.push_back((this->makeNumber()));
			} 
			else if (text.compare(current_char)){
				tokens.push_back((this->makeIdentifier()));
			} 
			else if (!(current_char.compare(string("\"")))){
				tokens.push_back(this->makeText());
			} 
			else if (!(current_char.compare(string("+")))){
				tokens.push_back(this->make_plus());
			} 
			else if (!(current_char.compare(string("-")))){
				tokens.push_back(this->make_minus());
			} 
			else if (!(current_char.compare(string("*")))){
				tokens.push_back(this->make_mul());
			} 
			else if (!(current_char.compare(string("/")))){
				tokens.push_back(this->make_div());
			} 
			else if (!(current_char.compare(string("^")))){
				tokens.push_back(this->make_caret());
			} 
			else if (!(current_char.compare(string("(")))){
				tokens.push_back(Token(t_lp, this->pos));
				this->advance();
			} 
			else if (!(current_char.compare(string(")")))){
				tokens.push_back(Token(t_rp, this->pos));
				this->advance();
			} 
			else if (!(current_char.compare(string("[")))){
				tokens.push_back(Token(t_lsq, this->pos));
				this->advance();
			} 
			else if (!(current_char.compare(string("]")))){
				tokens.push_back(Token(t_rsq, this->pos));
				this->advance();
			} 
			else if (!(current_char.compare(string("{")))){
				tokens.push_back(Token(t_lcb, this->pos));
				this->advance();
			} 
			else if (!(current_char.compare(string("}")))){
				tokens.push_back(Token(t_rcb, this->pos));
				this->advance();
			} 
			else if (!(current_char.compare(string("!")))){
				tokens.push_back(this->make_expoint());
			} 
			else if (!(current_char.compare(string("=")))){
				tokens.push_back(this->make_equals());
			} 
			else if (!(current_char.compare(string("<")))){
				tokens.push_back(this->make_less_than());
			} 
			else if (!(current_char.compare(string(">")))){
				tokens.push_back(this->make_greater_than());
			} 
			else if (!(current_char.compare(string(",")))){
				tokens.push_back(Token(t_com, this->pos));
				this->advance();
			} 
			else if (!(current_char.compare(string("|")))){
				tokens.push_back(this->make_pipe());
			}
			else if (!(current_char.compare(string("&")))){
				tokens.push_back(this->make_e());
			}
			else if (!(current_char.compare(string("~")))){
				tokens.push_back(this->make_tilde());
			}
			else {

			}
		}
	}
};
#endif