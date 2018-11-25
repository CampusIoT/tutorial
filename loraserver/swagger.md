# API Swagger
L’API Swagger est https://lora.campusiot.imag.fr/api 

Le JWT se recupère via
curl 'https://lora.campusiot.imag.fr/api/internal/login' --data '{"username":"admin","password":"XXXXXXX"}' --insecure
retourne
{"jwt":"XX.YY.ZZ"}

curl -X GET --header 'Accept: application/json' --header 'Grpc-Metadata-Authorization: Bearer XX.YY.ZZ' 'https://lora.campusiot.imag.fr/api/applications?limit=9999'  --insecure

