curl -v 127.0.0.1:8090/tasks

curl -v -X POST -H 'Content-Type: application/json' 127.0.0.1:8090/tasks -d '{"name":"Dmitry", "id":"0", "lastname":"Ivanov"}'

curl -v -X DELETE -H 'Content-Type: application/json' 127.0.0.1:8090/tasks?id=0

curl -v -X PUT -H 'Content-Type: application/json' 127.0.0.1:8090/tasks?id=0 -d '{"name":"Vasiliy", "id":"90", "lastname":"Petrov"}'

