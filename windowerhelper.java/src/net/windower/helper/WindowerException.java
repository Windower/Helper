package net.windower.helper;

public final class WindowerException extends RuntimeException {
	private static final long serialVersionUID = -8626786183429213238L;

	private final ErrorCode error;

	public WindowerException() {
		this.error = ErrorCode.UNKNOWN;
	}

	public WindowerException(final String message) {
		super(message);
		this.error = ErrorCode.UNKNOWN;
	}

	public WindowerException(final String message, final Throwable cause) {
		super(message, cause);
		this.error = ErrorCode.UNKNOWN;
	}

	public WindowerException(final ErrorCode error) {
		super(error.getMessage());
		this.error = error;
	}

	public WindowerException(final ErrorCode error, final String message) {
		super(message);
		this.error = error;
	}

	public WindowerException(final ErrorCode error, final Throwable cause) {
		super(error.getMessage(), cause);
		this.error = error;
	}

	public WindowerException(final ErrorCode error, final String message, final Exception cause) {
		super(message, cause);
		this.error = error;
	}

	public ErrorCode getErrorCode() {
		return this.error;
	}

	static void Check(final int error) {
		if (error != 0) {
			throw new WindowerException(ErrorCode.values()[error]);
		}
	}
}
