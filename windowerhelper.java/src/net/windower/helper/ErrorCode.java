package net.windower.helper;

public enum ErrorCode {
	NONE,
	UNKNOWN,
	OUT_OF_MEMORY,
	INVALID_ARGUMENT,
	OUT_OF_RANGE,
	INVALID_HANDLE,
	CONNECTION_FAULT,
	CONNECTION_CLOSED,
	INTERRUPT,
	INVALID_REPLY,
	NOT_FOUND,
	ENCODING;

	static ErrorCode getValue(final int value) {
		switch (value) {
		case 0x00: return NONE;
		case 0x01: return UNKNOWN;
		case 0x02: return OUT_OF_MEMORY;
		case 0x03: return INVALID_ARGUMENT;
		case 0x04: return OUT_OF_RANGE;
		case 0x05: return INVALID_HANDLE;
		case 0x06: return CONNECTION_FAULT;
		case 0x07: return CONNECTION_CLOSED;
		case 0x08: return INTERRUPT;
		case 0x09: return INVALID_REPLY;
		case 0x0A: return NOT_FOUND;
		case 0x0B: return ENCODING;
		}
		return UNKNOWN;
	}

	public String getMessage() {
		return WindowerHelperConstants.getString(String.format("error.%s", this.toString()).toLowerCase()); //$NON-NLS-1$
	}
}
