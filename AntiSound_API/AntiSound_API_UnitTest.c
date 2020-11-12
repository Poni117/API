#include "AntiSound_API.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    system("../AntiSound_API/Compile_AntiSound_API_TestConnect.sh");
    antiSound_api_newServer();
}