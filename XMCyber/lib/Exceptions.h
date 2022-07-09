#pragma once
#include "Defs.h"


ExceptionStatus EMPTY = "";

ExceptionStatus FILE_TOO_SMALL_EXCEPTION = "File is smaller then numberOfLinesPerSegment * lineSizeBytes";
ExceptionStatus FILE_TOO_BIG_EXCEPTION = "File is too maxFileSizeBytes";

ExceptionStatus WRITE_TO_FILE_EXCEPTION = "Error writing to file";
ExceptionStatus RENAME_FILE_Exception = "Error renaming file";
ExceptionStatus DELETE_FILE_EXCEPTION = "Error deleting file";
ExceptionStatus SET_START_FILE_POINTER_EXCEPTION = "Error setting start file pointer";
ExceptionStatus READ_FROM_FILE_EXCEPTION = "Error reading from file";
ExceptionStatus FILE_LINES_NOT_THE_SAME_LEN = "File lines are not the same length";

ExceptionStatus INAVILD_HANDLE_EXCEPTION = "Invaild handle";
ExceptionStatus INVALID_FILE_NAME_EXCEPTION = "Invalid file name";