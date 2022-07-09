#pragma once
#include "Defs.h"

Exception EMPTY = "";

Exception FILE_TOO_SMALL_EXCEPTION = "File is smaller then numberOfLinesPerSegment * lineSizeBytes";
Exception FILE_TOO_BIG_EXCEPTION = "File is too maxFileSizeBytes";

Exception WRITE_TO_FILE_EXCEPTION = "Error writing to file";
Exception RENAME_FILE_Exception = "Error renaming file";
Exception DELETE_FILE_EXCEPTION = "Error deleting file";
Exception SET_START_FILE_POINTER_EXCEPTION = "Error setting start file pointer";
Exception READ_FROM_FILE_EXCEPTION = "Error reading from file";

Exception INAVILD_HANDLE_EXCEPTION = "Invaild handle";
Exception INVALID_FILE_NAME_EXCEPTION = "Invalid file name";