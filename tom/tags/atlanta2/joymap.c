#include "ifi_aliases.h"
#include "user_routines.h"
#include "joymap.h"

const rom unsigned char lookup[256] = { 0,2,5,8,11,14,17,19,22,25,27,30,32,35,37,39,42,44,46,48,51,53,55,57,59,61,63,65,66,68,70,72,74,75,77,78,80,82,83,84,86,87,89,90,91,93,94,95,96,97,99,100,101,102,103,104,105,106,107,107,108,109,110,111,112,112,113,114,114,115,116,116,117,117,118,118,119,119,120,120,121,121,122,122,122,123,123,123,124,124,124,124,125,125,125,125,126,126,126,126,126,126,126,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,129,129,129,129,129,129,130,130,130,130,130,131,131,131,131,132,132,132,133,133,133,134,134,135,135,136,136,137,137,138,138,139,139,140,141,141,142,143,144,144,145,146,147,148,148,149,150,151,152,153,154,155,156,158,159,160,161,162,164,165,166,168,169,171,172,173,175,177,178,180,182,183,185,187,189,190,192,194,196,198,200,202,204,207,209,211,213,216,218,220,223,225,228,230,233,236,238,241,244,247,250,253 };

unsigned char joymap(unsigned char joy,int exp)
{
  if(exp==1)
    return lookup[joy];
  else
    return joy;
}