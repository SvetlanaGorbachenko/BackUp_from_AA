#pragma once

enum FilErrorCode { ERR_FILE_NOT_EXISTS,
	FILE_OK, 
	ERR_ACCESS,
	ERR_EMPTY_FILE,
	ERR_BACK_UP_ISNT_INITIALIZED,
	ERR_NO_DATA_TO_WRITE            // client object has no data for example empty array
};
