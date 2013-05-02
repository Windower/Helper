package net.windower.helper;

import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.charset.CharacterCodingException;
import java.nio.charset.Charset;
import java.nio.charset.CharsetDecoder;
import java.nio.charset.CharsetEncoder;
import java.nio.charset.CodingErrorAction;
import java.util.EnumSet;
import java.util.logging.Level;
import java.util.logging.Logger;

public final class Instance {
	static final CharsetEncoder ASCII_ENCODER = Charset.forName("US-ASCII").newEncoder() //$NON-NLS-1$
			.onMalformedInput(CodingErrorAction.REPORT).onUnmappableCharacter(CodingErrorAction.REPORT);
	static final CharsetEncoder UTF8_ENCODER = Charset.forName("UTF-8").newEncoder() //$NON-NLS-1$
			.onMalformedInput(CodingErrorAction.REPORT).onUnmappableCharacter(CodingErrorAction.REPORT);
	static final CharsetDecoder UTF8_DECODER = Charset.forName("UTF-8").newDecoder() //$NON-NLS-1$
			.onMalformedInput(CodingErrorAction.REPORT).onUnmappableCharacter(CodingErrorAction.REPORT);

	private final long handle;

	public Instance(final int process) {
		Native.initialize();

		final long[] result = new long[1];
		WindowerException.Check(Native.windower_create(result, process));
		this.handle = result[0];
	}

	public Instance(final String domain, final int process) {
		Native.initialize();

		final long[] result = new long[1];
		try {
			final ByteBuffer buffer = Instance.UTF8_ENCODER.encode(CharBuffer.wrap(domain));
			final byte[] bytes = new byte[buffer.position()];
			buffer.get(bytes);
			WindowerException.Check(Native.windower_create_remote(result, bytes, process));
		} catch (final CharacterCodingException e) {
			throw new WindowerException(ErrorCode.ENCODING);
		}
		this.handle = result[0];
	}

	@Override
	protected void finalize() throws Throwable {
		super.finalize();

		try {
			WindowerException.Check(Native.windower_delete(this.handle));
		} catch (final Throwable t) {
			final Logger logger = Logger.getLogger(Instance.class.getCanonicalName());
			logger.log(Level.SEVERE, null, t);
		}
	}

	public void dispose() {
		WindowerException.Check(Native.windower_delete(this.handle));
	}

	public Version getVersion() {
		final int[] result = new int[1];
		WindowerException.Check(Native.windower_get_version(this.handle, result));
		return new Version(result[0]);
	}

	public void sendString(final String string) {
		if (string == null) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.null"), "string")); //$NON-NLS-1$ //$NON-NLS-2$
		}

		try {
			final ByteBuffer buffer = Instance.UTF8_ENCODER.encode(CharBuffer.wrap(string));
			final byte[] bytes = new byte[buffer.position()];
			buffer.get(bytes);
			WindowerException.Check(Native.windower_send_string(this.handle, bytes));
		} catch (final CharacterCodingException e) {
			throw new WindowerException(ErrorCode.ENCODING);
		}
	}

	public void setKeyState(final Key key, final KeyState state) {
		if (key == null) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.null"), "key")); //$NON-NLS-1$ //$NON-NLS-2$
		}

		if (state == null) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.null"), "state")); //$NON-NLS-1$ //$NON-NLS-2$
		}

		WindowerException.Check(Native.windower_set_key_state(this.handle, key.intValue(), state.intValue()));
	}

	public void block(final EnumSet<InputKind> kinds) {
		if (kinds == null) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.null"), "kinds")); //$NON-NLS-1$ //$NON-NLS-2$
		}

		int value = 0;
		for (final InputKind k : kinds) {
			value |= k.intValue();
		}
		WindowerException.Check(Native.windower_block(this.handle, value));
	}

	public void block(final InputKind kind, final InputKind... kinds) {
		if (kind == null) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.null"), "kind")); //$NON-NLS-1$ //$NON-NLS-2$
		}

		if (kinds == null) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.null"), "kinds")); //$NON-NLS-1$ //$NON-NLS-2$
		}

		int value = kind.intValue();
		for (final InputKind k : kinds) {
			if (k == null) {
				throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.null"), "kinds")); //$NON-NLS-1$ //$NON-NLS-2$
			}
			value |= k.intValue();
		}
		WindowerException.Check(Native.windower_block(this.handle, value));
	}

	public void unblock(final EnumSet<InputKind> kinds) {
		if (kinds == null) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.null"), "kinds")); //$NON-NLS-1$ //$NON-NLS-2$
		}

		int value = 0;
		for (final InputKind k : kinds) {
			value |= k.intValue();
		}
		WindowerException.Check(Native.windower_unblock(this.handle, value));
	}

	public void unblock(final InputKind kind, final InputKind... kinds) {
		if (kind == null) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.null"), "kind")); //$NON-NLS-1$ //$NON-NLS-2$
		}

		if (kinds == null) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.null"), "kinds")); //$NON-NLS-1$ //$NON-NLS-2$
		}

		int value = kind.intValue();
		for (final InputKind k : kinds) {
			if (k == null) {
				throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.null"), "kinds")); //$NON-NLS-1$ //$NON-NLS-2$
			}
			value |= k.intValue();
		}
		WindowerException.Check(Native.windower_unblock(this.handle, value));
	}

	public String nextCommand() {
		final long[] command_handle = new long[1];
		WindowerException.Check(Native.windower_next_command(this.handle, command_handle));
		try {
			final int[] length = new int[1];
			WindowerException.Check(Native.windower_command_length(command_handle[0], length));
			final byte[] bytes = new byte[length[0]];
			WindowerException.Check(Native.windower_command_string(command_handle[0], bytes));
			final CharBuffer buffer = Instance.UTF8_DECODER.decode(ByteBuffer.wrap(bytes));
			return buffer.toString();
		} catch (final CharacterCodingException e) {
			throw new WindowerException(ErrorCode.ENCODING);
		} finally {
			WindowerException.Check(Native.windower_command_delete(command_handle[0]));
		}
	}

	long getHandle() {
		return this.handle;
	}
}
