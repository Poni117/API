#include "Datas.h"

datas_t* antiSound_datas_initializeDatas()
{
   datas_t* datas = malloc(sizeof(datas_t));

   datas->request = NULL;

   datas->root = NULL;

   datas->response = NULL;

   return datas;

}

messege_t* antiSound_datas_initializeMesseges()
{
   messege_t* messege = malloc(sizeof(messege_t));

   messege->key = -1;
   
   messege->message = "\0";

   return messege;
}
