#define or || 
#define and &&
#define not !=
#define keep keep_rec()
#define drop drop_rec()
#define keep_if_match(a,b) if(match(a,b)) keep_rec(); else drop_rec()
#define drop_if_match(a,b) if(match(a,b)) drop_rec() 
#define keep_if_substring(a,b) if(substring(a,b)) keep_rec(); else drop_rec()
#define drop_if_substring(a,b) if(substring(a,b)) drop_rec()
#define keep_if_pattern(a,b) if(pattern(a,b)) keep_rec(); else drop_rec()
#define drop_if_pattern(a,b) if(pattern(a,b)) drop()
