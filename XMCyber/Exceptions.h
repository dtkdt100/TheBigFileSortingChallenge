#pragma once
#include "Defs.h"


ExceptionStatus NO_EXCEPTION = "";

ExceptionStatus MAX_FILE_SIZE_TOO_SMALL = "Max file size too small";
ExceptionStatus LINES_PER_SEGEMENT_GREATER_THEN_ONE = "Lines per segment must be greater than one";
ExceptionStatus FILE_SIZE_NOT_MULTIPLE_OF_LINES_PER_SEGMENT = "File size not multiple of lines per segment";

ExceptionStatus FILE_TOO_SMALL_EXCEPTION = "File is smaller then numberOfLinesPerSegment * lineSizeBytes";
ExceptionStatus FILE_TOO_BIG_EXCEPTION = "File is bigger then maxFileSizeBytes";

ExceptionStatus WRITE_TO_FILE_EXCEPTION = "Error writing to file";
ExceptionStatus RENAME_FILE_Exception = "Error renaming file";
ExceptionStatus DELETE_FILE_EXCEPTION = "Error deleting file";
ExceptionStatus SET_START_FILE_POINTER_EXCEPTION = "Error setting start file pointer";
ExceptionStatus READ_FROM_FILE_EXCEPTION = "Error reading from file";
ExceptionStatus FILE_LINES_NOT_THE_SAME_LEN = "File lines are not the same length";

ExceptionStatus INAVILD_HANDLE_EXCEPTION = "Invalid handle";
ExceptionStatus INVALID_FILE_NAME_EXCEPTION = "Invalid file name";