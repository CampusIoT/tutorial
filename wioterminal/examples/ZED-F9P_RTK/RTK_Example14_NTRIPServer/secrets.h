//Your WiFi credentials

char* ssid = "MySSID";
char* password =  "mySSIDpassword";


const char* mntpnt = "GrenobleTinyGS";
#ifdef CENTIPEDE
//Your CENTIPEDE mount point credentials
const char* mntpnt_pw = "centipede";
#else
//Your RTK2GO mount point credentials
const char* mntpnt_pw = "MyRTK2GOpassword";
//const char* mntpnt_pw = "WEEK2225"; 
#endif
