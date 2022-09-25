//Your WiFi credentials

//char* ssid = "MySSID";
//char* password =  "mySSIDpassword";

const char* mntpnt = "GrenobleTinyGS";
#ifdef CENTIPEDE
//Your CENTIPEDE mount point credentials
const char* mntpnt_pw = "centipede";
#else
// SNIP NTRIP: RTK2go - Caster Status Report http://rtk2go.com:2101/SNIP::MOUNTPT?baseName=GrenobleTinyGS

//Your RTK2GO mount point credentials
//const char* mntpnt_pw = "MyRTK2GOpassword";
//const char* mntpnt_pw = "WEEK2225"; 
#endif
