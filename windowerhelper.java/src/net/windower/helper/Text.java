package net.windower.helper;

import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.charset.CharacterCodingException;
import java.util.EnumSet;
import java.util.logging.Level;
import java.util.logging.Logger;

public final class Text {
	private long handle;

	public Text(final Instance instance, final String name) {
		if (instance == null) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.null"), "instance")); //$NON-NLS-1$ //$NON-NLS-2$
		}

		if (name == null) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.null"), "name")); //$NON-NLS-1$ //$NON-NLS-2$
		}

		try {
			final ByteBuffer buffer = Instance.ASCII_ENCODER.encode(CharBuffer.wrap(name));
			final byte[] bytes = new byte[buffer.position()];
			buffer.get(bytes);
			final long[] result = new long[1];
			WindowerException.Check(Native.windower_text_create(instance.getHandle(), result, bytes));
			this.handle = result[0];
		} catch (final CharacterCodingException e) {
			throw new WindowerException(ErrorCode.ENCODING);
		}
	}

	@Override
	protected void finalize() throws Throwable {
		super.finalize();
		try {
			WindowerException.Check(Native.windower_text_delete(this.handle));
		} catch (final Throwable t) {
			final Logger logger = Logger.getLogger(Instance.class.getCanonicalName());
			logger.log(Level.SEVERE, null, t);
		}
	}

	public void dispose() {
		WindowerException.Check(Native.windower_text_delete(this.handle));
	}

	public void setText(final String text) {
		if (text == null) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.null"), "text")); //$NON-NLS-1$ //$NON-NLS-2$
		}

		try {
			final ByteBuffer buffer = Instance.UTF8_ENCODER.encode(CharBuffer.wrap(text));
			final byte[] bytes = new byte[buffer.position()];
			buffer.get(bytes);
			WindowerException.Check(Native.windower_text_set_text(this.handle, bytes));
		} catch (final CharacterCodingException e) {
			throw new WindowerException(ErrorCode.ENCODING);
		}
	}

	public void show() {
		WindowerException.Check(Native.windower_text_show(this.handle));
	}

	public void hide() {
		WindowerException.Check(Native.windower_text_hide(this.handle));
	}

	public void setLocation(final int x, final int y) {
		WindowerException.Check(Native.windower_text_set_location(this.handle, x, y));
	}

	public void setForeground(final int red, final int green, final int blue) {
		this.setForeground(red, green, blue, 255);
	}

	public void setForeground(final int red, final int green, final int blue, final int alpha) {
		if (red < 0 || red > 255) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.range"), "red", 0, 255)); //$NON-NLS-1$ //$NON-NLS-2$
		}

		if (green < 0 || green > 255) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.range"), "green", 0, 255)); //$NON-NLS-1$ //$NON-NLS-2$
		}

		if (blue < 0 || blue > 255) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.range"), "blue", 0, 255)); //$NON-NLS-1$ //$NON-NLS-2$
		}

		if (alpha < 0 || alpha > 255) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.range"), "alpha", 0, 255)); //$NON-NLS-1$ //$NON-NLS-2$
		}

		WindowerException.Check(Native.windower_text_set_foreground(this.handle, (byte) red, (byte) green, (byte) blue, (byte) alpha));
	}

	public void setBackground(final int red, final int green, final int blue) {
		this.setBackground(red, green, blue, 255);
	}

	public void setBackground(final int red, final int green, final int blue, final int alpha) {
		if (red < 0 || red > 255) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.range"), "red", 0, 255)); //$NON-NLS-1$ //$NON-NLS-2$
		}

		if (green < 0 || green > 255) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.range"), "green", 0, 255)); //$NON-NLS-1$ //$NON-NLS-2$
		}

		if (blue < 0 || blue > 255) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.range"), "blue", 0, 255)); //$NON-NLS-1$ //$NON-NLS-2$
		}

		if (alpha < 0 || alpha > 255) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.range"), "alpha", 0, 255)); //$NON-NLS-1$ //$NON-NLS-2$
		}

		WindowerException.Check(Native.windower_text_set_background(this.handle, (byte) red, (byte) green, (byte) blue, (byte) alpha));
	}

	public void showBackground() {
		WindowerException.Check(Native.windower_text_show_background(this.handle));
	}

	public void hideBackground() {
		WindowerException.Check(Native.windower_text_hide_background(this.handle));
	}

	public void setFont(final String typeface, final float size) {
		if (typeface == null) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.null"), "typeface")); //$NON-NLS-1$ //$NON-NLS-2$
		}

		byte[] typefaceBytes;
		try {
			final ByteBuffer buffer = Instance.UTF8_ENCODER.encode(CharBuffer.wrap(typeface));
			typefaceBytes = new byte[buffer.position()];
			buffer.get(typefaceBytes);
		} catch (final CharacterCodingException e) {
			throw new WindowerException(ErrorCode.ENCODING);
		}

		WindowerException.Check(Native.windower_text_set_font(this.handle, typefaceBytes, size));
	}

	public void setWeight(final FontWeight weight) {
		if (weight == null) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.null"), "weight")); //$NON-NLS-1$ //$NON-NLS-2$
		}

		WindowerException.Check(Native.windower_text_set_weight(this.handle, weight.intValue()));
	}

	public void setStyle(final EnumSet<FontStyle> styles) {
		if (styles == null) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.null"), "styles")); //$NON-NLS-1$ //$NON-NLS-2$
		}

		int value = 0;
		for (final FontStyle s : styles) {
			value |= s.intValue();
		}

		WindowerException.Check(Native.windower_text_set_style(this.handle, value));
	}

	public void setStyle(final FontStyle style, final FontStyle... styles) {
		if (style == null) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.null"), "style")); //$NON-NLS-1$ //$NON-NLS-2$
		}

		if (styles == null) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.null"), "styles")); //$NON-NLS-1$ //$NON-NLS-2$
		}

		int value = style.intValue();
		for (final FontStyle s : styles) {
			if (s == null) {
				throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.null"), "styles")); //$NON-NLS-1$ //$NON-NLS-2$
			}
			value |= s.intValue();
		}

		WindowerException.Check(Native.windower_text_set_style(this.handle, value));
	}

	public void setAlignment(final TextAlignment alignment) {
		if (alignment == null) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.null"), "align")); //$NON-NLS-1$ //$NON-NLS-2$
		}

		WindowerException.Check(Native.windower_text_set_alignment(this.handle, alignment.intValue()));
	}

	public void setPadding(final int padding) {
		if (padding < 0) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.greater"), "padding", 0)); //$NON-NLS-1$ //$NON-NLS-2$
		}

		WindowerException.Check(Native.windower_text_set_padding(this.handle, padding));
	}
}
