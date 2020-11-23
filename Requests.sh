curl 127.0.0.1:8090

curl -v -X POST -H 'Content-Type: application/json' 127.0.0.1:8090/AntiSound_API_Handler -d '{"name":"Dmitry"}, {"id":"0"}, {"lastname":"Ivanov"}'

curl -v -X DELETE -H 'Content-Type: application/json' '127.0.0.1:8090/AntiSound_API_Handler?id=0&name=Dmitry&lastname=Ivanov'

curl -v -X PUT -H 'Content-Type: application/json' 127.0.0.1:8090/AntiSound_API_Handler -d '{"name":"Dmitry"},{"id":"0"},{"lastname":"Ivanov"}'

