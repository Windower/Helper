package net.windower.helper;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.logging.Level;
import java.util.logging.Logger;

final class Native {
	private static final String VERSION = "4.0.0.0"; //$NON-NLS-1$

	private static boolean initialized = false;

	static synchronized void initialize() {
		if (!Native.initialized) {
			String arch = System.getProperty("os.arch"); //$NON-NLS-1$
			if ("amd64".equals(arch) || "x86_64".equals(arch)) { //$NON-NLS-1$ //$NON-NLS-2$
				arch = "x64"; //$NON-NLS-1$
			}

			try {
				final String tempPath = System.getProperty("java.io.tmpdir"); //$NON-NLS-1$
				File file = new File(new File(tempPath, String.format("windowerhelper.%s", Native.VERSION)), arch); //$NON-NLS-1$
				file.mkdirs();
				file = new File(file, "windowerhelper.java.dll"); //$NON-NLS-1$
				file.createNewFile();
				OutputStream out = null;
				InputStream in = null;
				try {
					try {
						out = new FileOutputStream(file);
					} catch (final FileNotFoundException e) {}

					if (out != null) {
						final String name = String.format("/native/%s/windowerhelper.dll", arch); //$NON-NLS-1$
						in = Instance.class.getResourceAsStream(name);
						final byte[] buffer = new byte[8192];
						int count;
						while ((count = in.read(buffer)) != -1) {
							out.write(buffer, 0, count);
						}
					}
				} finally {
					if (out != null) {
						out.close();
					}
					if (in != null) {
						in.close();
					}
				}
				System.load(file.getCanonicalPath());
			} catch (final Throwable t) {
				final Logger logger = Logger.getLogger(Native.class.getCanonicalName());
				logger.log(Level.SEVERE, t.getLocalizedMessage(), t);
				Native.<RuntimeException>uncheckedThrow(t);
			}
			Native.initialized = true;
		}
	}

	// Hack to rethrow Throwable from the initialize().
	@SuppressWarnings("unchecked")
	private static <T extends Throwable> void uncheckedThrow(final Throwable t) throws T {
		throw (T) t;
	}

	static native int windower_create(long[] result, int process);

	static native int windower_create_remote(long[] result, byte[] domain, int process);

	static native int windower_delete(long handle);

	static native int windower_get_version(long handle, int[] result);

	static native int windower_send_string(long handle, byte[] string);

	static native int windower_set_key_state(long handle, int key, int state);

	static native int windower_block(long handle, int input_kind);

	static native int windower_unblock(long handle, int input_kind);

	static native int windower_next_command(long handle, long[] result);

	static native int windower_command_delete(long handle);

	static native int windower_command_length(long handle, int[] result);

	static native int windower_command_string(long handle, byte[] result);

	static native int windower_text_create(long handle, long[] result, byte[] name);

	static native int windower_text_delete(long handle);

	static native int windower_text_set_text(long handle, byte[] text);

	static native int windower_text_show(long handle);

	static native int windower_text_hide(long handle);

	static native int windower_text_set_location(long handle, int x, int y);

	static native int windower_text_set_foreground(long handle, byte red, byte green, byte blue, byte alpha);

	static native int windower_text_set_background(long handle, byte red, byte green, byte blue, byte alpha);

	static native int windower_text_show_background(long handle);

	static native int windower_text_hide_background(long handle);

	static native int windower_text_set_font(long handle, byte[] typeface, float size);

	static native int windower_text_set_weight(long handle, int weight);

	static native int windower_text_set_style(long handle, int style);

	static native int windower_text_set_alignment(long handle, int alignment);

	static native int windower_text_set_padding(long handle, float pixels);
}
