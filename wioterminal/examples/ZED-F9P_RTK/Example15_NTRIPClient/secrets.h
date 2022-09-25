//char* ssid = "MySSID";
//char* password =  "mySSIDpassword";

#ifdef CENTIPEDE
//Your CENTIPEDE mount point credentials

const char casterHost[] = "caster.centipede.fr"; 
const uint16_t casterPort = 2101;
const char casterUser[] = "didier.donsez@gmail.com"; //User must provide their own email address to use RTK2Go
const char casterUserPW[] = "centipde";
const char mountPoint[] = "CRO2"; //The mount point you want to get data from

#else
//Your RTK2GO mount point credentials
//RTK2Go works well and is free
const char casterHost[] = "rtk2go.com"; 
const uint16_t casterPort = 2101;
const char casterUser[] = "didier.donsez@gmail.com"; //User must provide their own email address to use RTK2Go
const char casterUserPW[] = "";
const char mountPoint[] = "bldr_SparkFun1"; //The mount point you want to get data from

#endif



//Emlid Caster also works well and is free
//const char casterHost[] = "caster.emlid.com";
//const uint16_t casterPort = 2101;
//const char casterUser[] = "u99696"; //User name and pw must be obtained through their web portal
//const char casterUserPW[] = "466zez";
//const char mountPoint[] = "MP1979"; //The mount point you want to get data from
