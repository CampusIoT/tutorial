# Grove LoRa E5

* https://wiki.seeedstudio.com/Grove_LoRa_E5_New_Version/
* https://files.seeedstudio.com/products/317990687/res/LoRa-E5%20AT%20Command%20Specification_V1.0%20.pdf


## Utilisation avec un adaptateur USB Série (aka FTDI)

```
AT+ID                                                                   
+INFO: Input timeout                                                            
+ID: DevAddr, 32:30:A5:01                                                       
+ID: DevEui, 2C:F7:F1:20:32:30:00:01                                            
+ID: AppEui, 80:00:00:00:00:00:00:06                                            

AT+DR=EU868
+INFO: Input timeout                                                            
+DR: EU868                                                                      
                                                                                
AT+CH=NUM,0-2
+INFO: Input timeout                                                            
+CH: NUM, 0-2                                                                   

AT+KEY=APPKEY,2B7E151628AED2A6ABF7158809CF4F3C
+INFO: Input timeout                                                            
+KEY: APPKEY 2B7E151628AED2A6ABF7158809CF4F3C                                   

AT+MODE=LWOTAA
+INFO: Input timeout                                                            
+MODE: LWOTAA                                                                   
                                                                               
AT+CLASS=A
+INFO: Input timeout                                                            
+CLASS: A                                                                       
                                                                                
AT+PORT=8
+INFO: Input timeout                                                            
+PORT: 8                                                                        
                                                                                
AT+JOIN
+INFO: Input timeout                                                            
+JOIN: Start                                                                    
+JOIN: NORMAL                                                                   
+JOIN: Join failed                                                              
+JOIN: Done                                                                     
                                                                                
AT+JOIN
+INFO: Input timeout                                                            
+JOIN: Start                                                                    
+JOIN: NORMAL                                                                   
+JOIN: Network joined                                                           
+JOIN: NetID C0002B DevAddr FC:00:AC:2C                                         
+JOIN: Done                                                                     

AT+ID
+INFO: Input timeout                                                            
+ID: DevAddr, FC:00:AC:2C                                                       
+ID: DevEui, 2C:F7:F1:20:32:30:00:01                                            
+ID: AppEui, 80:00:00:00:00:00:00:06                                            

AT+CMSGHEX=2122232421222324
+INFO: Input timeout                                                            
+CMSGHEX: Start                                                                 
+CMSGHEX: Wait ACK                                                              
+CMSGHEX: FPENDING                                                              
+CMSGHEX: ACK Received                                                          
+CMSGHEX: RXWIN1, RSSI -72, SNR 6.0                                             
+CMSGHEX: Done                                                                  
                                                                                
AT+CMSGHEX=2122232421222324
+INFO: Input timeout                                                            
+CMSGHEX: Start                                                                 
+CMSGHEX: Wait ACK                                                              
+CMSGHEX: FPENDING                                                              
+CMSGHEX: ACK Received                                                          
+CMSGHEX: RXWIN1, RSSI -72, SNR 13.0                                            
+CMSGHEX: Done                                                                  

AT+DR
+INFO: Input timeout                                                            
+DR: DR0 (ADR DR5)                                                              
+DR: EU868 DR5  SF7  BW125K                                                     
+DR: EU868 DR0  SF12 BW125K                                                     
                                                                         
AT+ADR
+INFO: Input timeout                                                            
+ADR: ON                                                                        
                                                                                
AT+POWER
+INFO: Input timeout                                                            
+POWER: 12                                                                      
                                                                                
AT+VDD
+INFO: Input timeout                                                            
+VDD: 3.27V                                                                     
                                                                                
AT+WDT
+INFO: Input timeout                                                            
+WDT: ON                                                                        
                                                                                
AT+LOG
+INFO: Input timeout                                                            
+LOG: QUIET                                                                     

AT+LOG=DEBUG
+INFO: Input timeout                                                                                            
+LOG: DEBUG                                                                                                     
                                                                                
AT+CMSGHEX=2122232421222324
+INFO: Input timeout                                                            
+LOG: DEBUG                                                                     
+LOG: DEBUG   971961 LW      MACCMD, TX, 030706FF06                             
+LOG: DEBUG   971961 LW      MACCMD, RX, 0352FF0001                             
+LOG: DEBUG   971962 LW      ch 02                                              
+LOG: DEBUG   971962 LORA    RX, 868500000, SF7, 125KHz, 24                     
                                                                                
AT+CMSGHEX=2122232421222324
+INFO: Input timeout                                                            
+LOG:  WARN   988473 LW      tx 8, 2122232421222324(8)                          
+CMSGHEX: Start                                                                 
+CMSGHEX: Wait ACK                                                              
+LOG: DEBUG   988474 LW      MACCMD, TX, 0307                                   
+LOG: DEBUG   988474 LW      ch 00                                              
+LOG: DEBUG   988474 LORA    TX, 868100000, SF7, 125KHz, 8, 12                  
+LOG: DEBUG   988475 LORA    TX, 802CAC00FC82020003070897084ED874A8279461E7AFC3 
+LOG: DEBUG   989535 LORA    RX, 868100000, SF7, 125KHz, 24                     
+LOG: DEBUG   989594 LORA    RX, 602CAC00FCA502000354FF00012067D51D, -70, 14    
+LOG: DEBUG   989595 LW      MACCMD, RX, 0354FF0001                             
+CMSGHEX: FPENDING                                                              
+CMSGHEX: ACK Received                                                          
+CMSGHEX: RXWIN1, RSSI -70, SNR 14.0                                            
+CMSGHEX: Done

AT+CMSGHEX=2122232421222324
+INFO: Input timeout
+LOG:  WARN  1049959 LW      tx 8, 2122232421222324(8)
+CMSGHEX: Start
+CMSGHEX: Wait ACK
+LOG: DEBUG  1049960 LW      MACCMD, TX, 0307
+LOG: DEBUG  1049960 LW      ch 06
+LOG: DEBUG  1049960 LORA    TX, 867700000, SF7, 125KHz, 8, 8
+LOG: DEBUG  1049961 LORA    TX, 802CAC00FC8203000307082B4272553CA9F9726F527E7A
+LOG: DEBUG  1051021 LORA    RX, 867700000, SF7, 125KHz, 24
+LOG: DEBUG  1052062 LORA    RX, 869525000, SF12, 125KHz, 6
+LOG: DEBUG  1052975 LORA    TX, 867500000, SF7, 125KHz, 8, 8
+LOG: DEBUG  1052975 LORA    TX, 802CAC00FC8203000307082B4272553CA9F9726F527E7A
+LOG: DEBUG  1052976 LW      ch 05
+LOG: DEBUG  1054037 LORA    RX, 867500000, SF7, 125KHz, 24
+LOG: DEBUG  1055078 LORA    RX, 869525000, SF12, 125KHz, 6
+LOG: DEBUG  1055993 LORA    TX, 868100000, SF8, 125KHz, 8, 8
+LOG: DEBUG  1055993 LORA    TX, 802CAC00FC8203000307082B4272553CA9F9726F527E7A
+LOG: DEBUG  1055994 LW      ch 00
+LOG: DEBUG  1057109 LORA    RX, 868100000, SF8, 125KHz, 14
+LOG: DEBUG  1058147 LORA    RX, 869525000, SF12, 125KHz, 6
+CMSGHEX: Done

```

## Sketch Arduino sur Wio Terminal



## Sketch Arduino sur TinyGS 2G4 (connecteur Grove UART)



