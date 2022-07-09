#pragma once
#include "Defs.h"


Exception NO_EXCEPTION = "";

Exception MAX_FILE_SIZE_TOO_SMALL = "Max file size too small";
Exception LINES_PER_SEGEMENT_GREATER_THEN_ONE = "Lines per segment must be greater than one";
Exception FILE_SIZE_NOT_MULTIPLE_OF_LINES_PER_SEGMENT = "File size not multiple of lines per segment";

Exception FILE_TOO_SMALL_EXCEPTION = "File is smaller then numberOfLinesPerSegment * lineSizeBytes";
Exception FILE_TOO_BIG_EXCEPTION = "File is bigger then maxFileSizeBytes";

Exception WRITE_TO_FILE_EXCEPTION = "Error writing to file";
Exception RENAME_FILE_Exception = "Error renaming file";
Exception DELETE_FILE_EXCEPTION = "Error deleting file";
Exception SET_START_FILE_POINTER_EXCEPTION = "Error setting start file pointer";
Exception READ_FROM_FILE_EXCEPTION = "Error reading from file";
Exception FILE_LINES_NOT_THE_SAME_LEN = "File lines are not the same length";

Exception INAVILD_HANDLE_EXCEPTION = "Invalid handle";
Exception INVALID_FILE_NAME_EXCEPTION = "Invalid file name";

Exception WAITING_FOR_THREADS_EXCEPTION = "Error waiting for threads";